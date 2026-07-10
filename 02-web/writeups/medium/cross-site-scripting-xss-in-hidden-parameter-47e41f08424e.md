# :globe_with_meridians: Cross Site Scripting(XSS) In Hidden Parameter.

> **Original Source:** [Cross Site Scripting(XSS) In Hidden Parameter.](https://infosecwriteups.com/cross-site-scripting-xss-in-hidden-parameter-47e41f08424e)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Cross Site Scripting(XSS) In Hidden Parameter.


Hello All amazing Hackers out there…!!


My name is[Shantanu Kulkarni](https://twitter.com/0xShantanuKul). I am working as *Security Consultant* and *Lead penetration Tester* at a Security Consultancy firm in India. Also am a part time Bug Bounty Hunter. Today I am writing about one of the interesting XSS bug I found while Bug hunting. So let’s get started..!!


Consider the target name as domain.com . Usually, I follows the approach for Recon as Subdomain Enumeration → Live Targets → URLs → Looking for bugs but this time I Decided to go for finding parameters rather than looking for URLs. So I tried few tools like *Arjun* and *ParamSpider* to collect parameters. After collecting output from them a parameter ‘failure’ took my attention so I decided to test it further.


After few tries, I observed as the failure parameter is accepting only two values 1 or 0 and other inputs are just displaying at the bottom of web page on the red Box. When we input it as 0 the page goes blank and if we input there as 1 the page gets loaded properly. So I started it with experimenting on user registration page, admin login, support login and also for login bypass which may leads to internal dashboard access but no luck…!!


## Get Shantanu Kulkarni’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


So even if the page was not loading properly but the input on failure parameter is displaying on web Page so why not look for XSS? so I started Checking the Source code. Grabbed few payloads from PortSwigger/BruteLogic and started crafting it for pop-up. Again it was blocking alert keyword but accepting confirm and prompt. so got a pop-up finally..!!


Reported it with POC and showed an impact for cookie stealing. report is triaged as of now.

---

*Originally published on [Medium](https://infosecwriteups.com/cross-site-scripting-xss-in-hidden-parameter-47e41f08424e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
