# :globe_with_meridians: Rate Limit? I Barely Know Her: How I Brute-Forced OTPs Like a Gentleman 🚦🚨

> **Original Source:** [Rate Limit? I Barely Know Her: How I Brute-Forced OTPs Like a Gentleman 🚦🚨](https://infosecwriteups.com/rate-limit-i-barely-know-her-how-i-brute-forced-otps-like-a-gentleman-6f1235c559cc)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Rate Limit? I Barely Know Her: How I Brute-Forced OTPs Like a Gentleman 🚦🚨


Free [Link](https://medium.com/@iski/rate-limit-i-barely-know-her-how-i-brute-forced-otps-like-a-gentleman-6f1235c559cc?sk=d948e6683b5c8841ce925fcfbc1d0061)🎈


Hey there!😁


*Image by Gemini AI*

### 🌟 Life Lesson #147: If a system sends OTPs without limits, it deserves to be tested by someone with patience, Python, and poor sleep cycles. 😅


So there I was — late at night, wrapped in my blanket, watching anime while sipping expired Red Bull (I swear it still gives wings). But instead of catching sleep, I caught a vulnerable OTP implementation that almost let me hijack *any account*.


And like any proper gentleman, I brute-forced it with elegance. 🤓

## 🕵️‍♂️ Recon Mode: OTPville Awaits


During a wide-scope bug bounty recon, I stumbled on a login portal that looked suspiciously basic:


```
https://secure.target.com/login
```


On attempting a login, it immediately sent an OTP to the registered mobile/email:

---

*Originally published on [Medium](https://infosecwriteups.com/rate-limit-i-barely-know-her-how-i-brute-forced-otps-like-a-gentleman-6f1235c559cc). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
