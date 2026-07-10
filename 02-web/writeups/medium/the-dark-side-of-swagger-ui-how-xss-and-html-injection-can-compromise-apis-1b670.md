# :globe_with_meridians: The Dark Side of Swagger UI: How XSS and HTML Injection Can Compromise APIs

> **Original Source:** [The Dark Side of Swagger UI: How XSS and HTML Injection Can Compromise APIs](https://infosecwriteups.com/the-dark-side-of-swagger-ui-how-xss-and-html-injection-can-compromise-apis-1b670972a443)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# The Dark Side of Swagger UI: How XSS and HTML Injection Can Compromise APIs


## A hunter’s guide to finding XSS and HTML injection in Swagger UIs


## Introduction


Swagger UI is an open-source tool that helps developers visualize and interact with API endpoints defined by the OpenAPI Specification. While it’s great for testing and documentation, exposed or misconfigured Swagger instances can lead to serious security issues like DOM XSS, HTML injection and open redirects. With bug bounty platforms rewarding such vulnerabilities, securing Swagger UI isn’t just critical. it’s also a valuable target for ethical hackers.

## Why Swagger UI Can Be Dangerous


The problem isn’t Swagger itself. It’s the way developers deploy it sometimes publicly, sometimes with sensitive endpoints and often without authentication and input sanitization

### Common issues include:


- Swagger UI exposed on the internet with production endpoints.

- Lack of access control on documentation.

- Improper input sanitization, allowing for XSS and HTML injection.

## Recon Phase: Finding Swagger UIs

---

*Originally published on [Medium](https://infosecwriteups.com/the-dark-side-of-swagger-ui-how-xss-and-html-injection-can-compromise-apis-1b670972a443). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
