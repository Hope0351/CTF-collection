# :globe_with_meridians: 🚧 CSP? More Like Can’t Stop Payloads 🫸🧠 - Bypassing CSP to XSS Like a Pro

---

# 🚧 CSP? More Like Can’t Stop Payloads 🫸🧠 — Bypassing CSP to XSS Like a Pro

Free Link 🎈

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
