# :globe_with_meridians: Stored Xss To Admin In Unauthenticated Wordpress Cb76Bae66623

> **Original Source:** [Stored Xss To Admin In Unauthenticated Wordpress Cb76Bae66623](https://infosecwriteups.com/stored-xss-to-admin-in-unauthenticated-wordpress-cb76bae66623)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

### Keywords:


### Introduction:


The [All in One SEO Pack](https://aioseo.com/) plugin, a widely-used SEO tool for *WordPress* with over 1 million active installs, has a critical security vulnerability in one of its feature. This vulnerability, identified as Unauthenticated Stored Cross-Site Scripting (XSS), allows attackers to inject malicious JavaScript code through the headers, leading to execution of harmful scripts on WordPress administrator pages.


This vulnerability expose websites to attacks where an attacker can execute arbitrary JavaScript on the site simply by visiting the public-facing pages.

### Blocker Functionalities


In the case of the All in One SEO Pack plugin, the stored XSS vulnerability is triggered by its Blocker functionality. While this feature can help prevent malicious bots from accessing the site, the issue arises when the Track Blocked Bots setting is enabled. When this setting is turned on and a bot requests is detected based on a matching header predefined list of bot names such as [bots](https://gist.github.com/dvlop/fca36213ad6237891609e1e038a3bbc1), the plugin blocks the request and logs the event. This information…

---

*Originally published on [Medium](https://infosecwriteups.com/stored-xss-to-admin-in-unauthenticated-wordpress-cb76bae66623). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
