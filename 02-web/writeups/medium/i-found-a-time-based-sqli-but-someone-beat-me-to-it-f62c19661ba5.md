# :globe_with_meridians: I Found A Time Based Sqli But Someone Beat Me To It F62C19661Ba5

> **Original Source:** [I Found A Time Based Sqli But Someone Beat Me To It F62C19661Ba5](https://infosecwriteups.com/i-found-a-time-based-sqli-but-someone-beat-me-to-it-f62c19661ba5)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

*You Know*

## What I did


So I intercepted the request in Burp Suite and changed the value to


```
accountID=IN-1'+(select*from(select(sleep(10)))a)+'
```


Sent it, and boom — the server took like 10 full seconds to respond.


Tried again with `sleep(5)` → 5 second delay.


Then sent the normal value again → instant response.


Repeated it a few times just to be sure and yeah — this was definitely a time-based blind SQL injection.

---

*Originally published on [Medium](https://infosecwriteups.com/i-found-a-time-based-sqli-but-someone-beat-me-to-it-f62c19661ba5). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
