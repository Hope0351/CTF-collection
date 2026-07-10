# :game_die: Recruit - THM Writeup. By: Kavin Jindal (@Klevr)

> **Original Source:** [Recruit - THM Writeup. By: Kavin Jindal (@Klevr)](https://infosecwriteups.com/recruit-thm-writeup-e8e865de647d)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

By: Kavin Jindal ([@Klevr](https://klevrbook.gitbook.io/home))


## Get Avyukt Security’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


[https://tryhackme.com/room/recruitwebchallenge](https://tryhackme.com/room/recruitwebchallenge)


- Recruit is a newly released medium-rated challenge on TryHackMe. It is based on Path Traversal and SQL Injection to gain user and administrator access respectively, to a hiring dashboard. The following is a detailed write-up of the room where both manual and automated SQLi exploitation using SQLMAP have been explained.

## User Flag


## -0x01: Recon


- I started by running a TCP scan on the target via Nmap. Ports 53,22 and 80 were found to be open.


```
nmap -sC -sV -p 53,22,80 10.49.150.247
```


```
Starting Nmap 7.95 ( https://nmap.org ) at 2026-04-26 21:18 IST
Nmap scan report for 10.49.150.247
Host is up (0.019s latency).

PORT STATE SERVICE VERSION
22/tcp open ssh OpenSSH 8.2p1 Ubuntu 4ubuntu0.7 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey:
| 3072 e7:e4:f1:13:f7:ce:54:31:54:bb:8c:69:e7:2b:79:38 (RSA)
| 256 07:c4:23:b3:1d:a1:cb:90:cd:7e:4e:14:b2:30:6b:0d (ECDSA)
|_ 256 c9:ad:aa:f6:7e:11:d4:6b:e4:ad:00:d4:2d:ad:ae:b8 (ED25519)
53/tcp open domain ISC BIND 9.16.1 (Ubuntu Linux)
| dns-nsid:
|_ bind.version: 9.16.1-Ubuntu
80/tcp open http Apache httpd 2.4.41 ((Ubuntu))
| http-cookie-flags:
| /:
| PHPSESSID:
|_ httponly flag not set
|_http-title: Recruit
|_http-server-header: Apache/2.4.41 (Ubuntu)
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 15.00 seconds
```


- I visited the website running on port 80, which opened to a login page.


- I ran basic common credentials on the login page like `admin:admin` , `admin:password123` etc., but found nothing of use.

- There was a `api.php` page that had information on using the Recruit API.


- According to the information given, `/file.php?cv=<URL>` could be used to access any candidate's CVs. This thing reeked of a potential path traversal vulnerability to me.

- I tested several payloads on the `cv` parameter to test for SSRF (Server-Side Request Forgery) but nothing worked. The following error message persisted every time.


- I then ran a directory enumeration scan on the target via Gobuster.


```
gobuster dir -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt -u 10.49.150.247 -x php,txt,js,pdf
```


- The following subdirectories were found.


- `/mail` seemed an interesting find which led me to enumerate it further.

- It had a log file named `mail.log`


- The contents of `mail.log` were as follows.


- This appeared to be a log file that had an email sent from HR to the IT team. The email body revealed that the HR login credentials had `username: hr` and the password was stored inside `config.php`

- The administrator credentials were stored within a backend database.

- I checked out `config.php` but it returned no data. I tried accessing the file using path traversal in `/file.php?cv=` but the same error persisted even though it was a local file.

- After looking around on the internet, I found a bypass to this error using the `file://` wrapper to read local files. Using `file://config.php` worked like a charm.


- The config.php had the password for `hr`as mentioned previously. I used the credentials to log in and access the dashboard as follows.


- The user flag was obtained successfully!

## Admin Flag


- At this point, I knew that the admin credentials were stored securely in a backend database. The question was, how secure was it?

- The only entry point I could think of was the dashboard, where there was a search bar to look up candidates.

- My first instinct was to test it for SQL Injection and it worked right away.


- The error message revealed that the backend was running MySQL. Next, I used the UNION payload to check for the number of columns. This was a classic example of Error-based In-band SQL Injection.


- Using the following payload confirmed that there were four columns.


```
' union select 1,2,3,4-- -
```


- Next, I fetched the tables from the database.


```
' union select table_name,2,3,4 from information_schema.tables-- -
```


- In the long list of values returned, I found the table named `users` .


- Note that there were two other tables named `user` and `accounts` but none of them had anything of use.

- To find the columns in `users` table, I used the following `UNION SELECT`payload.


```
' union select column_name,2,3,4 from information_schema.columns where table_name='users'-- -
```


- The `password` column was found, and it could be used to get the administrator credentials.

- The following payload successfully fetched the password as shown.


```
' union select 1,password,3,username from users-- -
```


- As you can see, the password `admin@001admin` was successfully obtained for the `admin` username.

- I used these credentials to log in to the dashboard and obtain the final flag as follows.


(PS: I will highly recommend this [blog post](https://dev.to/deoxys/sql-injection-all-concepts-all-payloads-all-in-one-4ch5) for anyone who wants to understand the SQL Injection payloads for MySQL right from detecting injection to retrieving data)

## Using SQLMAP


- The whole process of manual exploitation of the SQLi vulnerability can be skipped by using SQLMAP.

- I captured the search request on `/dashboard.php` on the target via BurpSuite and copied it to a text file.


- I then used the following command in SQLMAP to expose all the databases.


```
sqlmap -r req.txt --dbs
```


- `recruit_db` was our database of interest.

- I dumped `recruit_db` using `--dump-all`.

- The admin password was revealed as follows.


- And with that, both the user and admin flags were obtained successfully, marking the completion of this room.


I hope you found this walkthrough informative. Don’t forget to follow Avyukt Security for more quality cybersecurity content.


Happy Hacking!

---

*Originally published on [Medium](https://infosecwriteups.com/recruit-thm-writeup-e8e865de647d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
