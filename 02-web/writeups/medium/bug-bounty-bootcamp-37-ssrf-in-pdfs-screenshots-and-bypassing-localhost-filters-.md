# :globe_with_meridians: Bug Bounty Bootcamp #37: SSRF in PDFs, Screenshots, and Bypassing Localhost Filters

---

# Bug Bounty Bootcamp #37: SSRF in PDFs, Screenshots, and Bypassing Localhost Filters

## You found a PDF generator that fetches URLs. The developer blocked `localhost` and `127.0.0.1`. Game over? Not even close. Learn the art of representing the same IP address in a dozen ways – and watch the firewall crumble.

Free Link

Welcome back to the Bug Bounty Bootcamp. You’ve learned the basics of SSRF: confirm server-side requests with an external monitor, then probe localhost and internal networks. But what happens when the application *knows* about SSRF and blocks obvious addresses like `127.0.0.1` and `localhost`? That’s when the real fun begins. This lesson focuses on two advanced SSRF scenarios: PDF/screenshot generation services (where input is a URL that gets rendered into a document) and bypassing common localhost blacklists using alternative representations, custom domains, and clever services.

## The Hidden SSRF Goldmine: PDF, Screenshot, and Media Generation

Any feature that takes a URL and produces a server-side artifact — PDF, screenshot, video thumbnail, image — is a prime SSRF candidate. The course highlights:

- PDF generators: “Convert this webpage to PDF” tools.

- Screenshot services: “Capture a preview of this site” widgets.

---
