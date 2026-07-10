# :globe_with_meridians: Cookie Jar Overflow: A New Threat to HttpOnly Cookies in XSS Vulnerable Applications

> **Original Source:** [Cookie Jar Overflow: A New Threat to HttpOnly Cookies in XSS Vulnerable Applications](https://infosecwriteups.com/cookie-jar-overflow-a-new-threat-to-httponly-cookies-in-xss-vulnerable-applications-9ceac4041082)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## Get sushil phuyal’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Let’s try to replicate the attack in the lab created by me:


When you log in to the system, the PHP session ID (`PHPSESSID`) is stored in your browser’s cookies to maintain the session state. This session ID is crucial for the application to link your authenticated session with your actions.


*before exploit*


Before we can exploit this, we need to find a vulnerability in the application. In this case, the search feature on the dashboard page is vulnerable to Reflected XSS. Reflected XSS occurs when user-supplied input is immediately included in the output response, allowing an attacker to inject malicious scripts into the page.


```
https://example.com/dashboard.php?search=<img src="x" onerror="for(let i=999;i--;)document.cookie=`c${i}=${i};Secure`;document.cookie='PHPSESSID=1337mickey';">
```


What this payload does is generate a large number of cookies using a loop. After 999 cookies are generated, it sets the session cookie `PHPSESSID=1337mickey`. The key part here is that the `PHPSESSID` cookie will override the session ID stored in the browser, and the session ID used by the attacker is now set to `1337mickey`.


At this point, the victim may be logged out of the application and might think it’s a glitch or session timeout. They log in again, but now something crucial has happened: the browser has stored the session ID (`1337mickey`) in its cookies.


Now, as the attacker, you can use the `PHPSESSID=1337mickey` session ID stored in your browser to authenticate as the victim. With this session ID, you effectively have full access to the victim's account, and the attack is complete.


*account takeover successful*

---

*Originally published on [Medium](https://infosecwriteups.com/cookie-jar-overflow-a-new-threat-to-httponly-cookies-in-xss-vulnerable-applications-9ceac4041082). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
