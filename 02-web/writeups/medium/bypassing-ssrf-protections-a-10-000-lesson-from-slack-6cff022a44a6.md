# :globe_with_meridians: Bypassing SSRF Protections: A $10,000 Lesson from Slack

---

# Bypassing SSRF Protections: A $10,000 Lesson from Slack

## How a Simple DNS Rebinding Attack Led to Internal Network Access

Server-Side Request Forgery (SSRF) vulnerabilities remain one of the most critical security issues in modern web applications. Today, I’m breaking down a fascinating SSRF report that earned a researcher $10,000 from Slack’s bug bounty program, and the valuable lessons we can all learn from it.

## The Vulnerability Overview

Severity: High
Free Read: Click

This report demonstrates how an attacker could bypass Slack’s SSRF protections using DNS rebinding techniques to access internal network resources that should have been completely isolated from external access.

## Understanding the Attack Surface

Slack, like many modern applications, needs to fetch external resources — think profile images, link previews, or webhook callbacks. However, allowing a server to make arbitrary HTTP requests opens the door to SSRF attacks, where an attacker tricks the server into making requests to internal resources.

---
