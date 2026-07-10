# :globe_with_meridians: “Bug Bounty Bootcamp #36: SSRF Hands-On - Confirming the Server Makes the Request and Reading Local Files”

---

# “Bug Bounty Bootcamp #36: SSRF Hands-On — Confirming the Server Makes the Request and Reading Local Files”

## You think you found an SSRF. But how do you prove the request came from the server and not your browser? And once confirmed, how do you turn that into a critical finding? This hands-on guide walks you through the exact steps.

Free Link

Welcome back to the Bug Bounty Bootcamp. You’ve learned the theory of Server-Side Request Forgery. Now, we get practical. SSRF can be one of the most impactful vulnerabilities, but also one of the hardest to demonstrate impact for. This lesson will show you the exact methodology to confirm an SSRF, differentiate server-side requests from client-side, and then pivot to reading local files or port-scanning internal networks. By the end, you’ll have a repeatable process to turn a potential SSRF into a critical bug bounty report.

## The Two Golden Rules of SSRF

Before exploiting any SSRF, you must answer two questions:

- Is the request coming from the server or my browser? If it’s from your browser, it’s not SSRF — it’s just a normal external request. True SSRF means the *server*…

---
