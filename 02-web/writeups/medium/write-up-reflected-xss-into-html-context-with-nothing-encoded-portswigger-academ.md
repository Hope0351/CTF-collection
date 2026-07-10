# :globe_with_meridians: Write-up: Reflected XSS into HTML context with nothing encoded @ PortSwigger Academy

> **Original Source:** [Write-up: Reflected XSS into HTML context with nothing encoded @ PortSwigger Academy](https://infosecwriteups.com/write-up-reflected-xss-into-html-context-with-nothing-encoded-portswigger-academy-c45e7e53c775)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Write-up: Reflected XSS into HTML context with nothing encoded @ PortSwigger Academy


This write-up for the lab *Reflected XSS into HTML context with nothing encoded* is part of my walkthrough series for [PortSwigger’s Web Security Academy](https://portswigger.net/web-security).


Learning path: Client-side topics → Cross-site scripting


Python script: [script.py](https://github.com/frank-leitner/portswigger-websecurity-academy/blob/main/11_cross_site_scripting_XSS/Reflected_XSS_into_HTML_context_with_nothing_encoded/script.py)

## Lab description


## Steps


As usual, the first step is to analyze the application. In this case, it is the blog website with search functionality.


When searching for a term, it is reflected back in the result:


This behavior can cause issues if the search string is not sanitized correctly.


## Get Frank Leitner’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


I try by including simple HTML tags within my search input. These tags are embedded into the HTML source of the response without any escaping:


The most trivial XSS is to simply use `<script>` tags within the search term and hope that they, too, are embedded in the HTML:


Sure enough, this raises the alert box confirming the XSS vulnerability on the domain:


At the same time, the lab updates to


---

*Originally published on [Medium](https://infosecwriteups.com/write-up-reflected-xss-into-html-context-with-nothing-encoded-portswigger-academy-c45e7e53c775). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
