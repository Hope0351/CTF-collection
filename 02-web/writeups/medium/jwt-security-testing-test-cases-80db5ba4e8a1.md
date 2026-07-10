# :globe_with_meridians: ✅ JWT Security Testing Test Cases

---

# ✅ JWT Security Testing Test Cases

These test cases are essential when assessing applications using JSON Web Tokens (JWT) for authentication or session management. Grouped by categories for logical flow and comprehensive coverage.

Disclaimer: This document is for educational purposes only. Exploiting systems without authorization is illegal and punishable by law.

Stay ethical. Stay legal. Secure responsibly.

*Thanks, Everyone for reading. Enjoy Happy Ethical Hacking!Support me if you like my work!*

[Buy me a coffee](https://buymeacoffee.com/Ajaynaik/e/311011)

🔐 1. Token Validation & Signature

## 🔐 1. Token Validation & Signature Attacks

## ✅ JWT-01 / JWT-03 — alg: none

- Intercept token in Burp or via browser.

- Decode with [jwt.io](https://jwt.io) or CyberChef.

- Change header:

```
{ "alg": "none", "typ": "JWT" }
```

4. Remove signature (leave the third segment empty).

5. Reconstruct token:

```
base64url(header).base64url(payload).
```

---
