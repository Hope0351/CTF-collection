# :globe_with_meridians: PortSwigger Academy Lab: Source code disclosure via backup files

> **Original Source:** [PortSwigger Academy Lab: Source code disclosure via backup files](https://infosecwriteups.com/portswigger-academy-lab-source-code-disclosure-via-backup-files-5f5e6ad3db30)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# PortSwigger Academy Lab: Source code disclosure via backup files


Description: This lab leaks its source code via backup files in a hidden directory. To solve the lab, identify and submit the database password, which is hard-coded in the leaked source code.


Upon accessing the lab, we come across a shopping website:


Since, we can find backup files in a hidden directory, I tried to fuzz for the directory:


```
ffuf -u https://0a0c0028030991b480fefd0a0003002f.web-security-academy.net/FUZZ -w /usr/share/seclists/Discovery/Web-Content/raft-small-directories.txt
```


*Note: I didn’t get any results the first time as I used http:// website instead of https resulting in uniform response which was “This lab is not accessible over HTTP”. Thus, keep in mind that http instead of https could affect ffuf results.*


On trying, I got these directories:


In these directories, the one relevant is backup and all the similar directories would automatically go lowercase resulting in the same result, which will be shown after another method.


Additionally, another place to search for directories of the website would be robots.txt where the developer lists the directories they want to be indexed by google crawler and other search engine crawler and also lists the directories which they don’t want the crawlers to index.


This can guide us to directories which might contain sensitive info.


## Get VISCID’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Robots.txt file:


From here, we can see that /backup is disallowed to be indexed.


On accessing /backup directory ([https://0a0c0028030991b480fefd0a0003002f.web-security-academy.net/backup](https://0a0c0028030991b480fefd0a0003002f.web-security-academy.net/backup)):


Here, directory listing is enabled which could be harmful as they reveal files which are publicly accessible, potentially exposing configuration files, passwords, and other sensitive data.


In this case, it’s revealing a .bak file which is a generic backup file. Because it’s java.bak, it likely contains java code.


On clicking it:


This is basically a java code which is probably related to some functionality behind the website.


Most importantly, in the readObject method, it tries to connect to postgresql with these details:
ConnectionBuilder connectionBuilder = ConnectionBuilder.from(
“org.postgresql.Driver”,
“postgresql”,
“localhost”,
5432,
“postgres”,
“postgres”,
“dpe5bpxhymadrrkj2gjyvot9w0lhxpxm”
).withAutoCommit();


Here, we can tell that it is likely connecting to the postgresql on localhost (same machine is hosting the web server and hosting sql together) at port 5432.


Also, username and password is:
“postgres”,
“dpe5bpxhymadrrkj2gjyvot9w0lhxpxm”


*IMPORTANT: Thus, when we receive some source code, it is important to look for code which is making a connection with another service which could allow us to get hardcoded credentials.
Additionally, with the source code, it would be easier to use it as a reference to find vulnerabilities like XSS.*

---

*Originally published on [Medium](https://infosecwriteups.com/portswigger-academy-lab-source-code-disclosure-via-backup-files-5f5e6ad3db30). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
