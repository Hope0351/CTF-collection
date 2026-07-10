# :globe_with_meridians: 🚧 CSP? More Like Can’t Stop Payloads 🫸🧠 - Bypassing CSP to XSS Like a Pro

> **Original Source:** [🚧 CSP? More Like Can’t Stop Payloads 🫸🧠 - Bypassing CSP to XSS Like a Pro](https://infosecwriteups.com/csp-more-like-cant-stop-payloads-bypassing-csp-to-xss-like-a-pro-90d27c2c3a40)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# 🚧 CSP? More Like Can’t Stop Payloads 🫸🧠 — Bypassing CSP to XSS Like a Pro


Free [Link](https://medium.com/@iski/csp-more-like-cant-stop-payloads-bypassing-csp-to-xss-like-a-pro-90d27c2c3a40?sk=6e6f48289bd8fef8e2b6878afdb3353d) 🎈


Hey there!😁


*Image by Ai*

>

“I only wanted to test some subdomains… but instead, I ended up karate-chopping CSP into submission and walked away with an XSS that paid for my entire caffeine addiction.”


## 😅 When Life Gives You Headers, Inject Some Payloads


It started like every lazy Sunday: hoodie on, hoodie off, tabs full of Shodan, and a caffeine-fueled terminal session that could fry a data center. I wasn’t even *trying* to find an XSS.


I was running my usual recon script:


```
subfinder -d target.com -silent > subs.txt
httpx -l subs.txt -mc 200,403 -title -tech-detect -x GET > live.txt
gau target.com >> all_urls.txt
waybackurls target.com >> all_urls.txt
```


Then I stumbled upon this juicy endpoint:


```
https://admin-assets.target.com/config/app.viewer?theme=<user-defined>
```


At first glance, it screamed: *“Hi, I reflect parameters, maybe I’m dangerous, maybe I’m not.”* So I poked it.

---

*Originally published on [Medium](https://infosecwriteups.com/csp-more-like-cant-stop-payloads-bypassing-csp-to-xss-like-a-pro-90d27c2c3a40). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
