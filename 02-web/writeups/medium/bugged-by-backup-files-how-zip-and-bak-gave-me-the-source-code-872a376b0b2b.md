# :globe_with_meridians: Bugged by Backup Files: How .zip and .bak Gave Me the Source Code 📦📜

---

# Bugged by Backup Files: How .zip and .bak Gave Me the Source Code 📦📜

Free Link🎈

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
