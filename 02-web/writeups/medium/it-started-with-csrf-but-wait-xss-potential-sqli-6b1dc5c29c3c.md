# :globe_with_meridians: It Started with CSRF, But Wait… (XSS & Potential SQLi)

> **Original Source:** [It Started with CSRF, But Wait… (XSS & Potential SQLi)](https://infosecwriteups.com/it-started-with-csrf-but-wait-xss-potential-sqli-6b1dc5c29c3c)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# **It Started with CSRF, But Wait… (XSS & Potential SQLi)**


## In the Name of Allah, the Most Beneficent, the Most Merciful.
All the praises and thanks be to Allah, the Lord of the ‘Alamin (mankind, jinns and all that exists).


It’s been a while since I last posted, so I’m back with a write-up of a CSRF lab from the [TCM Bug Bounty Course](https://youtu.be/wS2z5lt34Cc?si=pRzxDiXLPZHVyPl-).


I was testing for CSRF vulnerability in one of TCM Bug Bounty Lab. So I fired up my browser and [Burp Suite CE](https://portswigger.net/burp/communitydownload). We have two users, Jeremy and Jessamy.


*Users*


I log in as Jeremy, then I am welcomed with a new window to update my email address. I input a dummy email: attacker@gmail.com, then I intercepted the request with Burp Suite CE. I noticed that in the cookie header, the username is specified.


Then my hacker sense tickled, “What about if I change the username from Jeremy to Jessamy?” So I changed the name. I got 200, and Jessamy’s email was updated without logging in. It actually logged me in as Jessamy.


WOW. What could I do again?
Let’s check for XSS, so I inputted this simple payload:


```
<script>alert('callgh0st')</script>
```


And I got this reflective response: **There was an error. Data too long for column ‘email’ at row 1.**


Could it be it is vulnerable to SQLi. How I wish it was a BBP. Let me shorten my XSS payload to:


```
<script>alert('Hubb')</script>
```


and i got a reflective XSS.


Vulnerable to :


- XSS

- CSRF, let test for SQLi.


Input random characters in the email field and intercept with Burp Suite CE. I am a newbie to SQLi… little knowledge about it.
I decided to check if I can get anything using Burp Suite Intruder and SQLi Wordlists, I just have to check the length of the response if the payloads are successful.


Burp Suite wasn’t successful, so it’s time for sqlmap. I tried SQLmap by copying the request into a file, then running it using:


```
sqlmap - os-shell - risk=2 - level=2 -r s.txt
```


While it was running, sqlmap also indicated that the email parameter is likely vulnerable to XSS.


SQLMAP Response:


```
Sqlmap : [CRITICAL] all tested parameters do not appear to be injectable.
Try to increase values for ' - level'/' - risk' options if you wish to perform
more tests. If you suspect that there is some kind of protection mechanism
involved (e.g. WAF) maybe you could try to use option ' - tamper'
(e.g. ' - tamper=space2comment') and/or switch ' - random-agent' .
```


Could I be wrong? Is it not vulnerable to SQLi?

## Impact


I could try updating my email address and changing the cookie to another username. I can take over the user account by resetting the password.


## Get callgh0st’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Thanks for sticking to the end.

>

For any suggestions or Correction, Kindly reach out to me:


Twitter — [callgh0st](https://twitter.com/callgh0st)

---

*Originally published on [Medium](https://infosecwriteups.com/it-started-with-csrf-but-wait-xss-potential-sqli-6b1dc5c29c3c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
