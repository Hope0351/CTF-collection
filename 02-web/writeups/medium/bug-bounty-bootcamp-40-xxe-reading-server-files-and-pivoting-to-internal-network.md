# :globe_with_meridians: “Bug Bounty Bootcamp #40: XXE - Reading Server Files and Pivoting to Internal Networks Through XML”

---

# “Bug Bounty Bootcamp #40: XXE — Reading Server Files and Pivoting to Internal Networks Through XML”

## That innocent XML import feature could be a direct line to your `/etc/passwd` and internal cloud metadata. Learn to spot XML parsing vulnerabilities and weaponize external entities for file disclosure and SSRF.

Friend link

Welcome back. You’ve mastered SSRF and chaining. Now we turn to a vulnerability that often flies under the radar: XML External Entity (XXE) injection. When an application parses user‑supplied XML without disabling external entities, an attacker can read local files, perform SSRF, and in some cases achieve remote code execution. Even when the response is blind — no data reflected — you can exfiltrate files via an external DTD and a remote server. This lesson covers the full XXE arsenal: from basic file read to blind exfiltration using base64 encoding.

## What Is XXE? The XML Parser’s Fatal Feature

XML, like HTML, supports entities — placeholders that get replaced with content. An external entity pulls data from a file, URL, or other resource using a `SYSTEM` identifier. If the parser resolves it without restrictions, an…

---
