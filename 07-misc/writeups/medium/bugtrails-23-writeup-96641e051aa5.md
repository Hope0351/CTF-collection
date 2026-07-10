# :game_die: BugTrails-23 Writeup

> **Original Source:** [BugTrails-23 Writeup](https://infosecwriteups.com/bugtrails-23-writeup-96641e051aa5)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# BugTrails-23 Writeup


### 1. Challenge Name: admin panel


The challenge provides us with a website URL. The screenshot for the same is given below.


Analyzing the website to understand the tech stack being used on it. PHP is used in the backend which can be identified by looking at the client source code. Along with this, we can see some unusual comment being written beside the *username *field.


The goal of this challenge is to get admin access on the application. The application is disclosing admin’s username via client source code which is *tuhin1729*. Trying default credentials for this particular user doesn’t work.


There’s another page for resetting the user’s password.


Upon intercepting the password reset request in Burp Suite, we can see in the response some unusual comments.


It looks like the server is filtering requests based on the IP address. In order to request for a password reset, we need to forge our IP address with the server’s IP address. (specified in the screenshot given above)


We can try to forge the IP address using a HTTP header. We need to bruteforce the headers using one of the wordlist from SecLists named *lowercase-headers. (Command given below)*


```
ffuf -w /opt/SecLists/Discovery/Web-Content/BurpSuite-ParamMiner/lowercase-headers -H "FUZZ: 13.127.95.30" -H "Content-Type: application/x-www-form-urlencoded" -u http://13.127.95.30/passwordreset.php -d "uname=admin" -c -fs 311
```


The command given above will give us the result.


So, it is possible to forge the IP Address using *X-Client-Ip* header. Let’s see that in action using the Burp Suite’s repeater Tab.


Now this response is something new than what we were getting before. The comment also said that in order to reset the password, we need to send a curl request to the server. Let’s change the *User-Agent* value to *curl *and send the request.


Remember the username disclosed in the client source code, let’s enter that instead of *admin*.


*Password reset functionality is working perfectly*


Now we somehow need access to that link to reset the user’s password. There’s a well known attack called as *Password reset poisoning* that we can try.


Password reset poisoning is a technique whereby an attacker manipulates a vulnerable website into generating a password reset link pointing to a domain under their control. This behavior can be leveraged to steal the secret tokens required to reset arbitrary users’ passwords and, ultimately, compromise their accounts.


## Get Akshay Shinde’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


In order to perform this attack, make sure you have ngrok or a VPS instance to get the link (Use linode, DO or vultr). Now to trigger this attack, we need to add a new header called X-Fowarded-Host and set its value to the IP address of a VPS instance that we control.


*Received the password reset link on my VPS instance.*


Now visit the webpage appending the password reset link and make sure to add the *X-Client-Ip* header and change the *User-Agent* value to curl.


*Adding password parameter in the GET request.*


Let’s try to login into the admin account using the updated password.


*Admin panel access achieved*

### 2. Challenge Name: BugFile


The challenge provides us with a website URL. The screenshot for the same is given below.


Nothing can be seen on website. Intercepting the request in Burp Suite to identify the response headers.


*Flask web server running in the backend*


Let’s perform content discovery for the application using ffuf.


```
ffuf -w /opt/SecLists/Discovery/Web-Content/raft-medium-words.txt -u http://3.110.186.17/FUZZ -c -t 10
```


Let’s not waste time bruteforcing the pin for the Werkzeug debug console located at the */console* endpoint.


*message endpoint*


Looks like some path that might contain our flag. Accessing another endpoint.


*download endpoint*


So, this endpoint doesn’t allow any GET requests. We can try to change the HTTP Verb to POST, PUT or PATCH.


*PUT is the valid HTTP verb over here*


This endpoint looks like upon providing a valid path/file, it will download that file from the system. Let’s try to bruteforce the valid parameter using ffuf. (Command given below)


```
ffuf -w /opt/SecLists/Discovery/Web-Content/raft-medium-words.txt -X PUT -H "Content-Type: application/x-www-form-urlencoded" -u http://3.110.186.17/download -d "FUZZ=/etc/passwd" -c -fs 29
```


*Identified valid parameter for the download endpoint*


Input random path in the *filename *parameter and send the request to the server.


The directroy traversal payload (../) is getting filtered over here. We can bypass that by using another payload that looks somewhat like this,


```
..././..././..././..././etc/passwd
```


The ../ in the above payload will get removed by the filter and the final payload will look like,


```
../../../../etc/passwd
```


Now that we have successfully bypassed the LFI filter, we can try to access that *secret.txt* that we discovered earlier. (*message endpoint*)


*Contents of secret.txt file*


The file says that the developer of this challenge has leaked some information on pastebin. Visit [pastebin.com](https://pastebin.com) and search for the challenge name (BugFile) on it.


Using this debugger PIN against the Werkzeug console to execute system commands.


*Retrieved flag for the challenge*


Thank you so much for taking the time to read my article :)

---

*Originally published on [Medium](https://infosecwriteups.com/bugtrails-23-writeup-96641e051aa5). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
