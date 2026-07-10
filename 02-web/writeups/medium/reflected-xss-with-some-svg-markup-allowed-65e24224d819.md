# :globe_with_meridians: Reflected XSS with Some SVG Markup Allowed

---

# Reflected XSS with Some SVG Markup Allowed

Learn how reflected cross-site scripting (XSS) vulnerabilities still succeed in filtered environments using SVG tags.

🔓 [Free Link](https://bashoverflow.com/65e24224d819?sk=cf2f7866571fea3bd5d5d23c1f41be0a)

*Reflected XSS with Some SVG Markup Allowed*

>

Disclaimer:
The techniques described in this document are intended solely for ethical use and educational purposes. Unauthorized use of these methods outside approved environments is strictly prohibited, as it is illegal, unethical, and may lead to severe consequences.

It is crucial to act responsibly, comply with all applicable laws, and adhere to established ethical guidelines. Any activity that exploits security vulnerabilities or compromises the safety, privacy, or integrity of others is strictly forbidden.

## Table of Contents

- Summary of the Vulnerability

- Steps to Reproduce & Proof of Concept (PoC)

- Impact

## Summary of the Vulnerability

In this scenario, the web application is vulnerable to Reflected XSS, where untrusted input is reflected directly in the response without proper sanitization. The key twist? The application tries to block common HTML tags like `<script>`, `<img>`, and `<iframe>`, but some SVG markup is still allowed.

---
