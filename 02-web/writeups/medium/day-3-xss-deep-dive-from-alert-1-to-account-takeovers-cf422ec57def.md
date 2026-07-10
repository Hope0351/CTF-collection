# :globe_with_meridians: Day 3: XSS Deep Dive - From Alert(1) to Account Takeovers”

---

# Day 3: XSS Deep Dive — From Alert(1) to Account Takeovers”

Two months ago, I found a reflected XSS in a startup’s contact form. “Big deal,” I thought — until I turned it into a full account takeover chain that paid $5,000. Today, I’m breaking down my entire XSS playbook — from basic alerts to stealing sessions and bypassing WAFs.

free link

## Part 1: XSS Hunting — Where to Actually Look

Most tutorials tell you to “test all inputs.” That’s lazy. Here’s where I consistently find XSS in 2024:

### 1. Forgotten Inputs Everyone Misses

- HTTP Headers (Yes, really)

- Try:

```
GET / HTTP/1.1
Host: target.com
User-Agent: <script>alert(1)</script>
Referer: javascript:alert(1)
```

- Real Find: A fintech app reflected the `User-Agent` in their admin panel. $2,500.

- PDF Generators

- Upload a PDF with:

```
/Title ("><script>alert(1)</script>)
```

- Why It Works: Many sites parse PDF metadata unsafely.

### 2. The API Blindspot

APIs that return user-controlled data in JSON responses often get overlooked:

```
GET…
```

---
