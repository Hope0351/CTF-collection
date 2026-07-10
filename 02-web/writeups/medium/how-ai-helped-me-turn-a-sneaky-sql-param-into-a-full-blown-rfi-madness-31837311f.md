# :globe_with_meridians: How AI Helped Me Turn a Sneaky SQL Param into a Full-Blown RFI Madness 🤯💻

> **Original Source:** [How AI Helped Me Turn a Sneaky SQL Param into a Full-Blown RFI Madness 🤯💻](https://infosecwriteups.com/how-ai-helped-me-turn-a-sneaky-sql-param-into-a-full-blown-rfi-madness-31837311f6bd)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# How AI Helped Me Turn a Sneaky SQL Param into a Full-Blown RFI Madness 🤯💻


Free [Link](https://medium.com/@iski/how-ai-helped-me-turn-a-sneaky-sql-param-into-a-full-blown-rfi-madness-31837311f6bd?sk=4492116a90610a9cb9addc4137a8122d)🎈


Hey there!🙌


“When life gave me semicolons, I turned them into shell access.”


While most folks used AI to write poems or pass exams, I weaponized it. 😎 My friends were busy asking ChatGPT how to get a girlfriend (spoiler: even AI gave up), and I was asking it how to escalate an SQLi to a critical RFI bug. And guess what? And oh mannn… it delivered better than Amazon Prime. 📦


Let me take you on a rollercoaster ride of how AI turned my recon into revenue — all from one overlooked parameter.

## The Recon Phase: More URLs, More Pain 😩


I was doing mass recon like any bug bounty hunter — chaos, httpx, waybackurls, and gau screaming in my terminal like a death metal band. After a few hours of digital dumpster diving, I stumbled across an endpoint like this:


```
https://example.com/products/details?itemRef=412C9EFD&lang=en
```


Nothing fancy, right? But I saw that weird `itemRef` parameter and something about the value screamed, “I’m hiding something!”


I copied it into Burp Suite and the real game began.

---

*Originally published on [Medium](https://infosecwriteups.com/how-ai-helped-me-turn-a-sneaky-sql-param-into-a-full-blown-rfi-madness-31837311f6bd). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
