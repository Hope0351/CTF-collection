# :game_die: Soccer - HTB Walkthrough. This blog is about a machine named…

> **Original Source:** [Soccer - HTB Walkthrough. This blog is about a machine named…](https://infosecwriteups.com/soccer-htb-walkthrough-13f4dc0ba0aa)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

Hello all,


This blog is about a machine named “*soccer*” in hackthebox. The difficulty level of this box is marked as easy. Although it is one of the easy boxes, I learned a few things about web sockets. Without any delays, Let’s get started with the recon.

### Initial Reconnaissance


Running the nmap scan on the box, we get 3 ports as open, 22 (ssh), 80 (http), and 9091. This also shows that the nginx server is running and most probably it’s a Ubuntu box.


*Nmap scan*


**Port 80**


We will start with the web server first. Going to the browser and entering the IP redirects us to the *soccer.htb*. I have to add that in the ‘*/etc/hosts*’ file before the browser can reach it. After adding that in the hosts file, we can visit the server now


There are no other tabs on the page and the source also doesn’t reveal much. Let’s run the feroxbuster to find new directories.

>

feroxbuster -u [http://soccer.htb](http://soccer.htb) -w /usr/share/seclists/Discovery/Web-Content/raft-large-directories-lowercase.txt


It found 1 more directory called *tiny*. Visiting that in the browser presents us with a Tiny File Manager login page.


The source of this page shows the version of this software as v2.4.3.


There is a file upload vulnerability present in this software and the blog explaining that is [here](https://febinj.medium.com/tiny-file-manager-authenticated-rce-ad768d49fa0). But, this exploit is after we are authenticated to the software, which we don’t have right now. After doing a quick google search for the default creds of this software, I got this admin/admin@123. And it worked,


Now, we can try the file upload exploit. I used the PHP reverse shell and started the nc listener. Once started, I uploaded that file in *tiny/uploads* folder present in the UI (In other places, it doesn’t allow it).


Once uploaded, just visit that URL with the name of your file and get the shell as www-data.


After that, I upgraded the shell using the python method.


```
python3 -c 'import pty;pty.spawn("/bin/bash")'
```


### Lateral Movement


Looking around, I can see that there are only 2 users who can log in with shell, *player* and *root. *Also, it is an Ubuntu box.


Checking the open ports, it shows a few interesting ones, like 3000 which I don’t have any idea of as of now. 3306 is for mysql.


We know that the server was running on nginx (nmap shows this), so I checked the config file and it revealed what’s running on port 3000. Another server with the name *soc-player.soccer.htb* and it’s source code is present in the root directory which we can’t access. After adding the server name to hosts file, I visited the web server. It’s again the same home page as before, but now we have many other tabs as well.


Sign-up was required to use some of the features so, I signed up with a random username and password and logged in.


There is a *Tickets* option at the top which lets us check if the ticket number exists or not. Its URL is *check*


Sending the traffic through burp shows that this *check* is performed using the web sockets. PortSwigger has one module on WebSockets [here](https://portswigger.net/web-security/websockets/what-are-websockets#how-are-websocket-connections-established).


## Get Manish Kumar’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


We can see the protocol switching traffic in burp and the web socket traffic as well.

---

*Originally published on [Medium](https://infosecwriteups.com/soccer-htb-walkthrough-13f4dc0ba0aa). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
