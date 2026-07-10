# :globe_with_meridians: “Bug Bounty Bootcamp #39: PDF SSRF and Blind Exfiltration - When Headless Browsers Become Your Data Mule”

---

# “Bug Bounty Bootcamp #39: PDF SSRF and Blind Exfiltration — When Headless Browsers Become Your Data Mule”

## The invoice generator doesn’t show errors. The image fetcher hangs on invalid IPs. But with a single `<iframe>` and a JavaScript redirect, you can turn a blind SSRF into a full file read – no response needed.

Friend link | free link

Welcome back. You’ve conquered SSRF with open redirects and localhost bypasses. Now we tackle the trickiest scenarios: SSRF in PDF generation where you have no direct output, and blind SSRF where the application never returns the fetched data. The solution? Inject JavaScript that forces the headless browser to exfiltrate data back to you — using `window.location`, `fetch`, and base64 encoding. This lesson will give you a repeatable playbook for turning blind SSRF into a full data extraction channel.

## The PDF Generator: A Hidden SSRF Goldmine

Many applications generate invoices, receipts, or reports as PDFs using your profile data. The server uses a headless browser (like Chrome) or a PDF library (like PrinceXML) to render HTML to PDF. If you can inject HTML into your profile — address, company name, notes —…

---
