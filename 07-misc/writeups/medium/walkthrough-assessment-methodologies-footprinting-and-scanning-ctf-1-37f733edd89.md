# :game_die: Walkthrough - Assessment Methodologies: Footprinting and Scanning CTF 1

> **Original Source:** [Walkthrough - Assessment Methodologies: Footprinting and Scanning CTF 1](https://infosecwriteups.com/walkthrough-assessment-methodologies-footprinting-and-scanning-ctf-1-37f733edd89d)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Walkthrough — Assessment Methodologies: Footprinting and Scanning CTF 1


Welcome, folks! Today, we will be discussing the EJPT CTF-2 (Footprinting and scanning )walkthrough, how I solved it, and how I was able to collect all the flags. Keep in mind that I won’t be sharing the flags directly because I want you to learn, rather than just submit flags on the platform. However, I will share the commands that I used and explain my methodology.


## Get Mohammed Ali Mistry’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Let’s get started:


- Flag 1: The server proudly announces its identity in every response. Look closely; you might find something unusual.


Firstly, as always I pinged the target and did an nmap scan and guess what? I found my first flag!. Also I got the ports opened and hints for rest of the flags. If you notice the nmap output carefully.


- Flag 2: The gatekeeper’s instructions often reveal what should remain unseen. Don’t forget to read between the lines.


Naturally, I would go the webpage since ports 80 or 443 were open and look for basic files such as robots.txt, sitemap.xml, security.txt, etc. And if you notice in the above nmap result there are some directories listed which aren’t allowed little bit suspicious …… I mean it scratch that part of my brain.


So I went to each path specified but apart from `secret-info`, the other two paths returned 404 errors. And I was stuck on this one for a while I was wondering what to do. I checked the cookies, network tabs, request responses, etc., but found nothing then I notice the file type was a document, so I appended `flag.txt` to the path and boom got the flag.


- Flag 3: Anonymous access sometimes leads to forgotten treasures. Connect and explore the directory; you might stumble upon something valuable.


Anonymous hmmm, well there is only on protocol that allows anonymous that is FTP. And if you would carefully look at the nmap result of ftp there is anonymous access allowed.


To access FTP anonymously, I used this command (with the password also set as `anonymous`):


```
ftp anonymous@<ip>
```


After logging in, I found the flag and another file with credentials. I downloaded both files using the `get` command and displayed their contents with `cat`.


- Flag 4: A well-named database can be quite revealing. Peek at the configurations to discover the hidden treasure.


From the FTP we download two files — one contained the flag, and the other provided credentials for something. Based on the question, this was for a MySQL database. So, I logged into the database using the following command:


```
mysql -h <target> -u <username> -p
show databases; //to list databases
```


Hurray we got all the flags, congratulations.
Happy hacking!


---

*Originally published on [Medium](https://infosecwriteups.com/walkthrough-assessment-methodologies-footprinting-and-scanning-ctf-1-37f733edd89d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
