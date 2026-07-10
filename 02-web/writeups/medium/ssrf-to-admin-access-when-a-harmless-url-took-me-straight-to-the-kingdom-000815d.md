# :globe_with_meridians: SSRF to Admin Access: When a “Harmless URL” Took Me Straight to the Kingdom 👑🌐

> **Original Source:** [SSRF to Admin Access: When a “Harmless URL” Took Me Straight to the Kingdom 👑🌐](https://infosecwriteups.com/ssrf-to-admin-access-when-a-harmless-url-took-me-straight-to-the-kingdom-000815d0725d)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# SSRF to Admin Access: When a “Harmless URL” Took Me Straight to the Kingdom 👑🌐


Free [Link](https://medium.com/@iski/ssrf-to-admin-access-when-a-harmless-url-took-me-straight-to-the-kingdom-000815d0725d?sk=d553f09e35df4396e078522340de0e5c)🎈


Hey there!😁


*Image by AI*


Life lesson #1: Never trust URLs that look innocent.
Life lesson #2: Never trust developers who say “it’s just fetching data.”
Life lesson #3: If it says `uri=`, it probably says “hack me.” 😏
Life lesson #4: Sometimes… even the best findings don’t end the way you expect.

## 🎯 The Target That Looked Too Simple


It started like any other bug bounty day — caffeine ☕, Burp Suite open, and my recon scripts humming like a hacker’s lullaby.


While digging through endpoints, I stumbled upon something that looked *too clean*:


```
http://site.com/users/view/data?uri=
```


At first glance, it screamed *“I fetch external resources”*.
And to a bug bounty hunter… that’s basically a love letter 💌.

## 🔍 Phase 1: Mass Recon & Pattern Hunting


Before touching the parameter, I went full recon mode:


```
gau site.com | grep -i "uri="
waybackurls site.com | grep "fetch\|url\|uri"
```

---

*Originally published on [Medium](https://infosecwriteups.com/ssrf-to-admin-access-when-a-harmless-url-took-me-straight-to-the-kingdom-000815d0725d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
