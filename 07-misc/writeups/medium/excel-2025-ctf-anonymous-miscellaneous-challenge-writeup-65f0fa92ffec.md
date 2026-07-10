# :game_die: Excel 2025 CTF | “Anonymous” (Miscellaneous) Writeup

> **Original Source:** [Excel 2025 CTF | “Anonymous” (Miscellaneous) Writeup](https://infosecwriteups.com/excel-2025-ctf-anonymous-miscellaneous-challenge-writeup-65f0fa92ffec)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2025

---

# Excel 2025 CTF | “Anonymous” (Miscellaneous) Writeup


The challenge ‘Anoymous’ was one of the interesting challenge in Excel 2025 CTF. It was a miscellaneous challenge and mostly it includes Web based attacks, and I used a combination of my own skills, web search, and AI to solve it. My performance in the CTF earned me the 24th position with a score of 2260 points.


This challenge involved a chain of vulnerabilities, starting with an XXE injection to gain a foothold, followed by discovering a hidden host, and finally bypassing a complex, multi layered file upload filter to achieve Remote Code Execution (RCE).


The challenge started by accessing the website, which presented a simple webpage with a “Join Us” form. Viewing the page’s source code it revealed a Javascript function that constructed an XML payload and sending it to the notify.php. From my analysis using AI and web search I undestood it points to a potential XML External Entity (XXE) vulnerabilty.


*Source code which shows the vulnerabilty*


So then I used CURL tool to send a payload to the notify.php endpoint to confirm the vulnerability by reading the /etc/passwd file.


Then with file-read access, I enumerated system configuration files. Reading /etc/apache2/sites-enabled/000-default.conf and revealed a second hidden website or host : anonupload.cyberquest


*system configuration files and hidden host name*


So I added 35.200.207.70 anonupload.cyberquest to the /etc/hosts file, then I accessed a new file which was a password protected file upload page.


Then I used the same XXE vulnerability again to read the source code of /var/www/anonupload.cyberquest/index.php and found the password is supersecret1234564_niceeeee132213.


*password showing on the source code of index.php*


After logging in, we can see a strict file upload form. This is where the challenge involved more trial and error.


*Screenshot of the File upload form*


On my inital attempts to upload a PHP shell failed, but each failure gave us a clue.


- > Attempt 1: MIMEType Bypass: I tried uploading a .php file while setting the Content-Type header to image/jpeg intercepting using Burpsuite.


This error showed that the server wasn’t just trusting the header; it was checking the file’s actual content, by it’s Magic number’s maybe.


- > Attempt 2 : Magic Number & Extension Mismatch : So I tried uploading a file with a vaild PNG signature but a .php extension. It also got failed.


This error revealed the server is strict, the file’s content and it’s extension had to match one of the allowed types.


## Get Shibzzz’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Then I re-examine the index.php source code, where I found the critical vulnerability in the validation logic. The code used a flawed explode() function to check the extension but a secure pathinfo() function to save the file.


*vulnerable code*


So then I tried for a bypass. By making a filename into shell.jpeg.php, the validation check will see jpeg and pass, but the server would save the file with it’s true final extension .php .


To pass the content check, the file needed to be a valid JPEG. I tried adding the payload to the file and it caused error. Then I edited the metadata of the file by adding a PHP payload into the JPEG’s comment using exiftool.


So I intercepted and modified, Uploaded image.jpeg to renaming it to shell.jpeg.php .


Success !!


With the shell uploaded, I accessed it via the browser to execute commands.


First I listed the files in the root directory to find the flag :


*http://anonupload.cyberquest/uploads/2a9526f0dd3382db.php?cmd=ls =la /*


*got the root files*


This revealed the flag file, fl444g_11d854d6a9c9341e8af155128bf74362.txt .


Now we have to read the content inside to read the flag and complete the challenge.


[http://anonupload.cyberquest/uploads/2a9526f0dd3382db.php?cmd=cat/fl444g_11d854d6a9c9341e8af155128bf74362.txt](http://anonupload.cyberquest/uploads/2a9526f0dd3382db.php?cmd=cat%2Ffl444g_11d854d6a9c9341e8af155128bf74362.txt)


*flag*


Yep… We got the flag…

---

*Originally published on [Medium](https://infosecwriteups.com/excel-2025-ctf-anonymous-miscellaneous-challenge-writeup-65f0fa92ffec). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
