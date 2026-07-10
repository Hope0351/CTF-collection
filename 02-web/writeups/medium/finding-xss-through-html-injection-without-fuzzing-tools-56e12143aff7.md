# :globe_with_meridians: Finding XSS Through HTML Injection - Without Fuzzing Tools

> **Original Source:** [Finding XSS Through HTML Injection - Without Fuzzing Tools](https://infosecwriteups.com/finding-xss-through-html-injection-without-fuzzing-tools-56e12143aff7)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Finding XSS Through HTML Injection — Without Fuzzing Tools


>

Note: All sensitive information has been redacted


When hunting for XSS, most people immediately reach for fuzzing tools. But sometimes, slowing down and simply observing how an application behaves can uncover just as much — if not more.

### Where did the HTML Injection come from?


While testing the application, I wasn’t actively fuzzing inputs at that time. Instead, I was following normal business logic, trying to understand how the system works and whether any logical flaws existed.


During this process, I noticed something interesting while inspecting the page source.


```
<a href="http://redacted.com/redacted.php?parameter={email name}">
```


This immediately stood out.


Why? Because the application is built on a modern framework where routing is handled cleanly — no `.php` files are exposed anywhere else. Every page follows a consistent route-based structure. Yet here was a direct reference to a `.php` endpoint.


That inconsistency is often a signal worth investigating.


—

### Testing for Injection


Naturally, the next step was to test whether the parameter was injectable. I started with a harmless payload:


```
<h1>Hello</h1>
```


The result? It rendered successfully — not escaped, not sanitized. That confirmed HTML injection.


## Get Windasunny’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Next, I tried a classic XSS payload:


```
<script>alert(1)</script>
```


Blocked.


At first glance, it looked like a WAF was doing its job. But the filtering behavior suggested something superficial — likely keyword-based blocking.


So I adjusted the payload slightly:


```
<svg onload=confirm(1)>
```


And… it worked.

### Why did it work?


The WAF appeared to block obvious patterns like `script` and `alert`, but failed to account for alternative event-based payloads. This is a common weakness in naive filtering mechanisms.


By leveraging an SVG element with an `onload` event, I was able to bypass the filter and achieve JavaScript execution.


—


Finally


- Report: Accepted

- Result: Fixed

---

*Originally published on [Medium](https://infosecwriteups.com/finding-xss-through-html-injection-without-fuzzing-tools-56e12143aff7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
