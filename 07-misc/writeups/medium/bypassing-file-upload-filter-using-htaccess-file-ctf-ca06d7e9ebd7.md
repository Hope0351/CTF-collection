# :game_die: Bypassing file upload filter using .htaccess file(CTF)

> **Original Source:** [Bypassing file upload filter using .htaccess file(CTF)](https://infosecwriteups.com/bypassing-file-upload-filter-using-htaccess-file-ctf-ca06d7e9ebd7)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Bypassing file upload filter using .htaccess file(CTF)


Hello Friend!


This is my first writeup about how I bypass the file upload filters by using “.htaccess” file.


*overview of file upload vulnerability*


***File upload Vulnerability:***


*File upload vulnerability is a security flaw that arises when an application improperly handles user-uploaded files. This type of vulnerability can allow attackers to upload malicious files, which can lead to various exploits, such as executing arbitrary code, data theft, or even full server compromise.*


This is CTF challenge held by metactf.


*challenge*


This challenge contain the file upload functionality.


normally I uploaded the “.txt” file it gives the path, when I visit that path it display the content of the file.

*.txt file*


then I tried to upload “.php” file, but it not allowing PHP and it’s variations. so, I opened my burp, intercept the request and send to the repeater and tried double extension, null bytes, changing content but nothing works.


In the response we can see it reveals the backend server is running on Apache/2.4.62


*black listed php file*


I thought this can be bypass using “.htaccess” configuration file.


## Get Cyb3rV0lt’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


you can read more about .htaccess file using below link


lets come back to story, I created **.htaccess **file with content of


```
AddType application/x-httpd-php .evil
```


It means any arbitary file with extention “.evil” can run as PHP.


*.htaccess file*


so, I created **backdoor.evil **file which contain the simple PHP backdoor code and uploaded it. and also it was successfully uploaded.


*backdoor.evil file uploaded successfully*


now time to execute the commands on the web server by using the backdoor, go to file path with parameter `uploads/backdoor.evil?cmd=` and result is


*listing files*


*displaying /etc/passwd file*


*final flag*


finally I got the flag.


Thank you…


Subscribe my YouTube : [https://youtube.com/@cybervolt07](https://www.youtube.com/@cybervolt07)

---

*Originally published on [Medium](https://infosecwriteups.com/bypassing-file-upload-filter-using-htaccess-file-ctf-ca06d7e9ebd7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
