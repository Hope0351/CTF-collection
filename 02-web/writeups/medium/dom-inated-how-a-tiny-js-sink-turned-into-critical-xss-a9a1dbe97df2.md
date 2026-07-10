# :globe_with_meridians: DOM-inated! How a Tiny JS Sink Turned Into Critical XSS 🚨🧬

---

# DOM-inated! How a Tiny JS Sink Turned Into Critical XSS 🚨🧬

Free Link🎈



![img_1.jpeg](images/dom-inated-how-a-tiny-js-sink-turned-into-critical-xss-a9a1dbe97df2/img_1.jpeg)
Hey there!😁

*Image by Gemini AI*

Every morning, normal people stretch, yawn, and make coffee. ☕
Meanwhile, I’m stretching my Burp Suite, yawning at React apps, and sniffing around JavaScript sinks. 🔍👃

When my friends buy concert tickets, I buy VPN upgrades for better recon. 😂
They talk about “investments” in stocks.
I invest in bug bounty dreams fueled by broken web apps. 💻❤️

Today, let me tell you how one tiny overlooked JavaScript sink almost gave me a heart attack (and later, a Critical bounty).

Grab your coffee — this is a wild ride! 🚀

## 🔥 Phase 1: Recon Like a Mad Scientist

First rule: Mass recon is life.

I started like this:

```
subfinder -d target.com -silent > subs.txt
httpx -l subs.txt -mc 200 -silent > live_hosts.txt
gau -subs target.com | grep -iE "\.js$" | tee js_files.txt
```

👀 After an hour of fishing `.js` files, one particular file caught my eye:

```
https://app.target.com/static/main.bundle.js
```

---
