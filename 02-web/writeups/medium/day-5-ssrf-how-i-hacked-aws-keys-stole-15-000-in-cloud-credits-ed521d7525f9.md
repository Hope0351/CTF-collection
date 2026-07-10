# :globe_with_meridians: “Day 5: SSRF — How I Hacked AWS Keys & Stole $15,000 in Cloud Credits”

---

# “Day 5: SSRF — How I Hacked AWS Keys & Stole $15,000 in Cloud Credits”

Three months ago, I found a “low-severity” SSRF (Server-Side Request Forgery) in a SaaS company’s API. What started as a simple internal port scan turned into full AWS access, stolen credentials, and $15,000 in free cloud credits. Today, I’m revealing the full exploit chain — exactly how I did it, with code snippets you can use right now.

![img_1.png](images/day-5-ssrf-how-i-hacked-aws-keys-stole-15-000-in-cloud-credits-ed521d7525f9/img_1.png)


free link

## What is SSRF? (The $500,000 Vulnerability)

SSRF lets attackers trick a server into making unauthorized requests (e.g., accessing internal systems, cloud metadata).

### Real-World Analogy:

Imagine a hotel concierge who will fetch anything you ask for — even if you request “the master key to every room.” That’s SSRF.

## How I Found the SSRF (Step-by-Step Exploit)

### Step 1: Found a Vulnerable API Endpoint

While testing a document converter SaaS, I noticed:

```
POST /api/convert
{ "url": "https://example.com/resume.pdf" }
```

Hypothesis: What if I change the URL to something internal?

### Step 2: Tested for Basic SSRF

---
