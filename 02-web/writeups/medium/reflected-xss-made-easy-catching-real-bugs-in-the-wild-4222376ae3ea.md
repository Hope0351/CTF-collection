# :globe_with_meridians: Reflected Xss Made Easy Catching Real Bugs In The Wild 4222376Ae3Ea

> **Original Source:** [Reflected Xss Made Easy Catching Real Bugs In The Wild 4222376Ae3Ea](https://infosecwriteups.com/reflected-xss-made-easy-catching-real-bugs-in-the-wild-4222376ae3ea)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

### Real Bug: MTN Group Reflected XSS (Report ID: [1779447](https://hackerone.com/reports/1779447))


Submitted By: mathara


Platform: MTN Group


Vulnerability Type: Reflected XSS

## Steps to Reproduce:


- Navigate to:`[https://www.mtn.bj/](https://www.mtn.bj/)`

- Go to the Messages section of the website.

- Inject the payload below in an input or URL parameter:


```
<h1 onauxclick=confirm(document.domain)>RIGHT CLICK HERE
```


4. The payload reflects in the response and executes — showing a confirm prompt with the current domain.

## Impact:


This payload successfully triggered JavaScript execution in the browser, meaning:


- An attacker could craft malicious links and send them to MTN users.

- If clicked, these links could steal cookies, perform session hijacking, or even redirect users to malicious sites.

- When combined with social engineering, this can lead to serious compromise of user accounts and internal portals.

### Lessons & How You Can Find Similar Bugs


Reflected XSS vulnerabilities like this are very common, especially on login pages, search fields, contact forms, and even in error messages. Here’s how to look for them:

## Step-by-Step Methodology:


- Automated Crawling:


Use tools like:


## Get Monika sharma’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


`ParamSpider`


`waybackurls`


`gau`


To collect all parameters from a domain.


2. Test Common Payloads:


Send payloads using Burp Suite Repeater or directly in the browser:


```
<svg onload=alert(1)>
"><script>alert(1)</script>
<h1 onauxclick=confirm(document.domain)>
```


3. Manual Interaction:


Try injecting the payload into URL params and check if it reflects in the HTML response.


Look for:


- `<input value="">`

- `<script>` tags containing your input

- Inline HTML events like `onclick`, `onmouseover`, `onauxclick`


4. Bypass Filters:


Try payload encoding:


- HTML Entities: `&lt;script&gt;alert(1)&lt;/script&gt;`

- URL Encoding: `%3Cscript%3Ealert(1)%3C%2Fscript%3E`

### Why This Report Stands Out


- The bug was found using a simple static payload.

- No login or complex recon was required — just pure observation.

- The payload used `onauxclick` (right-click event) which is often underrated and bypasses some filters.

- It’s a perfect example of how even minimal testing on public websites can yield real bounties.

---

*Originally published on [Medium](https://infosecwriteups.com/reflected-xss-made-easy-catching-real-bugs-in-the-wild-4222376ae3ea). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
