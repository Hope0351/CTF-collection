# :game_die: HackTheBox Writeup — Blocky

> **Original Source:** [HackTheBox Writeup — Blocky](https://infosecwriteups.com/oswe-like-boxes-series-0x01-htb-blocky-write-up-1ac98e50dee7)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HackTheBox Writeup — Blocky


Hi guys, today we will be looking at Blocky Box from Hackthebox. It was very easy machine with two solutions. One is intended other one unintended. Summary part for intended way.

### Summary


- There are 4 open ports 21, 22, 80 and 25565.

- Head on to port 80, there is a wordpress page, get username notch.

- Find directory named /plugins using ffuf or any other web fuzzer.

- Download BlockyCore.jar and inspect it using JD-GUI, get password.

- SSH into box with username notch and password you found.

- Basic sudo -i for privilege escalation.

### Scan Ports


As always we will start with nmap scan, my way of using nmap is first scanning all ports then making a service scan and running default scripts for the open ports that i have found.


```
nmap -p- -vv -T5 10.10.10.37 -oN nmapscan
```


I have used -vv because if nmap finds open ports on lower numbers it shows us immediately so while it is scanning, I can take a look at that ports. I think scanning this way is faster.


```
nmap -p21,22,80,8192,25565 -sVC -vv -T4 -oN nmapscan2 10.10.10.37
```


There are ftp and ssh ports, since there is no anonymous login on ftp and we don’t have credentials yet we will take a look at port 80. There is also a Minecraft server but not exploitable.

### Getting Username


When we go to port 80, we can see this wordpress page, by clicking one of the posts we can see the username of our user.


You can also enumerate users on wordpress using ?author=1 parameter.

### Web Fuzzing


On main directory we got wordpress but let’s fuzz and find out if there are other directories or files. I’m using ffuf and directory-list-2.3-medium.txt as a wordlist for this purpose.


```
ffuf -u "[http://10.10.10.37/FUZZ](http://10.10.10.37/FUZZ)" -w ~/gitClones/SecLists/Discovery/Web-Content/directory-list-2.3-medium.txt -e .php,.txt
```


There is nothing on wiki page, there are some wordpress related pages and the plugins page. Keep in mind that phpmyadmin and wp-login.php also as we will deal with them later in unintended solution.


We have two files on plugins directory, I have downloaded both but there is nothing interesting on griefprevention file, actually it is a patch or something like that for minecraft.


## Get Mutlu Dönmez’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


You can inspect it with JD-GUI but I extracted it using 7z and used our almighty tool “strings” :p


Realize the password “8YsqfCTnvxAUeduzjNSXe22”. After some trial and error I was able to connect SSH with notch user and with this password.

### Privilege Escalation


After getting shell with user notch, I checked if its one of the sudoers as always. Indeed it is;


There is nothing special for this priv esc part it was very easy.


### Unintended Way


Remember phpmyadmin, wp-login.php pages and the BlockyCore credentials. When I first saw that credentials I thought I should go and enter phpmyadmin because there were sqlUser, sqlPass values.


When I enter with the credentials, I saw wordpress database.


First I tried to crack it but couldn’t so changed it with a custom password. To change it, we have to get our password’s hashed version of course.


I learned that hash type is phpass so generated it using this online generator.

### Accessing Machine with Web Shell


We have changed the notch’s password on wordpress so we can access wp-admin after logged in. The process after that is simple and very well-known. Wordpress using themes, you can edit theme php pages and gain shell easily. You can use plugins to achieve this as well.


From Appearance -> Editor, I changed 404.php page and edited with p0wny shell. That is what i prefer, you can choose other page or other web shell of course.


You can access 404.php on


```
http://10.10.10.37/wp-content/themes/twentyseventeen/404.php
```


We got shell as www-data user. Since the box is very old, I was trying to avoid using kernel exploits so I tried to find another way.


We were able to see notch user home directory and there was a minecraft folder and inside it there was some .jar files.


On TJnull’s list, there is a note for the box saying “Good practice with JD-GUI”, Since the BlockyCore.jar was too easy I thought that I have to deal with them. After struggling some time I found nothing.

### Kernel Exploitation


Our last resort was searching for a kernel exploit since kernel version is 4.4.0-62-generic there could be one.


As you can see on the searchsploit results there are some exploits but when you inspect the DCCP Double-Free is tested on exactly our kernel version.


It works but very unstable, I had to try several times and it crashes the box so I don’t recommend using it.

>

That’s all Folks! Have a nice day :)

---

*Originally published on [Medium](https://infosecwriteups.com/oswe-like-boxes-series-0x01-htb-blocky-write-up-1ac98e50dee7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
