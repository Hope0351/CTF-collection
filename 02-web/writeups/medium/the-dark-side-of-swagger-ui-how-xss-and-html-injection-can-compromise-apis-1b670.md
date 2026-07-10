# :globe_with_meridians: The Dark Side of Swagger UI: How XSS and HTML Injection Can Compromise APIs

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
