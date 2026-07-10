# :globe_with_meridians: A story about a not-so-direct SSRF

> **Original Source:** [A story about a not-so-direct SSRF](https://infosecwriteups.com/a-story-about-a-not-so-direct-ssrf-b2b98e128af0)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# A story about a not-so-direct SSRF


## Hi all, hope you are keeping well and staying safe. This blog is about my recent SSRF finding.


### Introduction and Recon


I was testing a target that had a decent scope. After doing some basic google dorking to find domains/subdomains about the target, I ended up finding a subdomain which was a “demo-testing” site that is related to some smart authentication.


For those of you interested, this is the dork I’ve used.

>

site:target.com -inurl:”https://target.com”


Right off the bat, we had a basic page with three fields and one of them was a URL. We had a drop-down menu to select a URL through which authentication has to happen (remember smart-auth).


After supplying dummy data and intercepting the request, we see that the application is trying to authenticate with the help of the “token” value provided. Since the token is invalid (dummy value), the end server was returning a 401 error.


Interestingly, the application is requesting “/some-other-endpoint” to the end-point server.

### Exploitation


Noticing the URL parameter and supplying burp collaborator location, we get both a DNS and HTTP request and also the burp…

---

*Originally published on [Medium](https://infosecwriteups.com/a-story-about-a-not-so-direct-ssrf-b2b98e128af0). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
