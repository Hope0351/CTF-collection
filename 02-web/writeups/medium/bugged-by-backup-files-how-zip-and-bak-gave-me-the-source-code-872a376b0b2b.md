# :globe_with_meridians: Bugged by Backup Files: How .zip and .bak Gave Me the Source Code 📦📜

> **Original Source:** [Bugged by Backup Files: How .zip and .bak Gave Me the Source Code 📦📜](https://infosecwriteups.com/bugged-by-backup-files-how-zip-and-bak-gave-me-the-source-code-872a376b0b2b)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Bugged by Backup Files: How .zip and .bak Gave Me the Source Code 📦📜


Free [Link](https://medium.com/@iski/bugged-by-backup-files-how-zip-and-bak-gave-me-the-source-code-872a376b0b2b?sk=d7e82a13f3d444d762d5a322a2b14aad)🎈


Hey there!


*image by Gemini AI*


Ever had that moment where your WiFi dies, your coffee spills, and Burp Suite crashes all at once?


Yeah, that was my morning. But then… my recon script pinged a wild `.bak` file into my terminal like a gift from the hacker gods. 🧙‍♂️


Friends were outside touching grass.
I was inside touching `.env` files hidden in backup zips. 😌


And that’s how a small mistake by a dev made a BIG payday for me. Let’s dive in. 🚀

## 📦 Chapter 1: Recon First, Profit Later


Like any good hunter, I started with mass recon — because who has time to poke sites one by one? 😤

## 🔧 Recon Stack:


```
subfinder -d target.com -silent > subs.txt
httpx -l subs.txt -mc 200 -silent > live.txt
gau -subs target.com | tee urls.txt
```


Now, instead of looking for regular parameters like `?id=` or `?q=`, I filtered for interesting file extensions:


```
cat urls.txt | grep -Ei "\.zip$|\.tar$|\.bak$|\.tar\.gz$|\.rar$" > backups.txt
```


💥 And there it was:


```
https://dev.target.com/backup-site.bak…
```

---

*Originally published on [Medium](https://infosecwriteups.com/bugged-by-backup-files-how-zip-and-bak-gave-me-the-source-code-872a376b0b2b). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
