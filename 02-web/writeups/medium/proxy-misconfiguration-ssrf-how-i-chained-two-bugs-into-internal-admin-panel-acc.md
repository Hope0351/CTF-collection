# :globe_with_meridians: Proxy Misconfiguration + SSRF: How I Chained Two Bugs Into Internal Admin Panel Access

> **Original Source:** [Proxy Misconfiguration + SSRF: How I Chained Two Bugs Into Internal Admin Panel Access](https://infosecwriteups.com/proxy-misconfiguration-ssrf-how-i-chained-two-bugs-into-internal-admin-panel-access-cf0e43bf79e4)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Proxy Misconfiguration + SSRF: How I Chained Two Bugs Into Internal Admin Panel Access


## From harmless URL fetchers to internal service compromise — a deep dive into a high-severity bug bounty chain


>

Introduction


In the world of bug bounty hunting, finding a single bug is great. But chaining two low-to-medium issues into a critical vulnerability? That’s where the magic (and the big bounties) happen.


In this article, I’ll walk you through a unique vulnerability chain:


How a misconfigured reverse proxy combined with a server-side request forgery (SSRF) led to unauthorized access to internal admin panels — and how you can spot similar issues in the wild.


Whether you’re just getting started or you’re looking to level up your bug hunting game, this chain will give you ideas to test modern infrastructures effectively.

>

The Core Idea


Let’s break down the two weaknesses that come together in this chain:


- Proxy Misconfiguration


Many applications sit behind reverse proxies (e.g., NGINX, HAProxy, Envoy) that handle incoming requests. These proxies might:


- Trust X-Forwarded-For, X-Forwarded-Host, or Host headers

- Route requests to internal services based on headers or paths

- Accidentally expose internal routes when configured improperly


If we can influence how the proxy routes traffic, we might trick it into giving us access to internal admin panels.


2. Server-Side Request Forgery (SSRF)


SSRF happens when the server lets you provide a URL, and it goes and fetches that URL on your behalf. Examples:


- Image or file fetchers

- Webhooks and integrations

- PDF/thumbnail generators


If you can send requests from the server to internal services (e.g., [http://localhost](http://localhost), [http://127.0.0.1](http://127.0.0.1), or cloud metadata endpoints), you can reach places you normally couldn’t.

>

The Chain: From External Input to Internal Access


Here’s the flow that can turn these two issues into a critical report:


- Find a feature that lets you provide a URL (image upload, webhook, etc.) → SSRF injection point.

- Use SSRF to send requests to internal services (e.g., [http://127.0.0.1:8080/admin](http://127.0.0.1:8080/admin)).

- Add crafted headers to SSRF requests:


```
X-Forwarded-For: 127.0.0.1
X-Forwarded-Host: internal.service.local
Host: internal.service.local
```


4. Proxy trusts these headers → forwards your request as if it came from inside the network → internal admin panel responds.


5. Access sensitive dashboards, configs, or APIs meant only for trusted sources.

>

Where to Look for This Chain


- Features that accept URLs:


- Profile picture importers

- Webhook URLs

- RSS feed importers

- PDF/image generators


2. Tech stack clues:


- NGINX / HAProxy / Envoy / Traefik in front of the app

- Microservices with internal APIs

- Apps with internal dashboards at 127.0.0.1, localhost, or subdomains like admin.internal


3. Headers to try injecting:


```
X-Forwarded-For: 127.0.0.1
X-Forwarded-Host: admin.internal
Host: admin.internal
Forwarded: for=127.0.0.1
```


>

My Methodology


Step 1: Find SSRF


## Get Monika sharma’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Test all URL-based features:


```
http://yourburp.collaborator.net
http://requestbin.net/endpoint
```


Confirm if the server makes the request.


Step 2: Pivot to Internal


Use SSRF to request:


```
http://127.0.0.1/
http://localhost/
http://internal-api.local/
http://169.254.169.254/ (cloud metadata)
```


Check status codes, response times, error messages.


Step 3: Add headers + target admin routes


Inject headers via SSRF:


```
X-Forwarded-Host: internal.panel.local
X-Forwarded-For: 127.0.0.1
```


Target common admin paths:


```
/admin
/dashboard
/metrics
/debug
```


>

Real Impact Example


Imagine this:


- You find an image upload that fetches URLs.

- You use SSRF to hit [http://127.0.0.1:8080/admin](http://127.0.0.1:8080/admin).

- You inject X-Forwarded-For: 127.0.0.1.

- The proxy forwards your request thinking it’s internal traffic

- You access the admin panel without authentication.


Such a chain can lead to:


- Reading internal config files

- Changing admin settings

- Remote code execution

- Exfiltrating sensitive data

>

Real-World Cases


Several bug bounty reports have used this chain:


- Tesla (2020): SSRF + proxy header abuse → internal tool access

- Uber (2023): SSRF via webhook + proxy trust → admin API access

- Yahoo (2019): SSRF + NGINX trusted X-Forwarded-For → sensitive internal endpoints

>

Final Tips for Hunters


- Always test SSRF endpoints with and without crafted headers.

- Fuzz internal paths once you get a response difference.

- Combine this with other chains — e.g., SSRF + open redirect + proxy abuse.

- Think like the proxy — where would it mistakenly route you?

>

Conclusion


Bug bounty success often lies in chaining small misconfigurations into something powerful.


- A lonely SSRF might be a P3.

- A proxy misconfig might be a P3.

- But together? Critical.


Next time you spot an SSRF or suspicious proxy config, think about this chain — and you might just land your next critical report.

### Bonus: Payload Cheat Sheet


```
http://127.0.0.1/
http://localhost/
http://internal/admin
http://169.254.169.254/latest/meta-data/

Headers:
X-Forwarded-For: 127.0.0.1
X-Forwarded-Host: admin.local
Host: admin.local
Forwarded: for=127.0.0.1
```


>

✉️ What’s next?
Want a detailed recon plan, payload automation script, or custom Burp macro for this chain? Drop a comment — let’s hunt!


THANK YOU ✨

---

*Originally published on [Medium](https://infosecwriteups.com/proxy-misconfiguration-ssrf-how-i-chained-two-bugs-into-internal-admin-panel-access-cf0e43bf79e4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
