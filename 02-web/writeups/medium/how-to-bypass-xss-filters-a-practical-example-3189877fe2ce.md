# :globe_with_meridians: How to Bypass XSS Filters: A Practical Example

> **Original Source:** [How to Bypass XSS Filters: A Practical Example](https://infosecwriteups.com/how-to-bypass-xss-filters-a-practical-example-3189877fe2ce)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# How to Bypass XSS Filters: A Practical Example


*Photo by [David Pupaza](https://unsplash.com/@dav420?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText) on [Unsplash](https://unsplash.com/@dav420?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText)*


Cross-site scripting (XSS) is a common web application vulnerability that allows attackers to inject malicious scripts into web pages. XSS can be used for various purposes, such as stealing cookies, session hijacking, phishing, defacement, and more.


However, many web applications have implemented XSS filters to prevent or mitigate XSS attacks. XSS filters are mechanisms that scan user input and output for suspicious strings or characters that may indicate an XSS attempt. They may block, encode, sanitize, or remove such input or output.


But XSS filters are not perfect. They can be bypassed by using various techniques that exploit their weaknesses or limitations. In this blog post, we will show you a practical example of how to bypass an XSS filter using character encoding tricks.


Character Encoding Tricks


To bypass filters that rely on scanning text for specific suspicious strings, attackers can encode any number of characters in a variety of ways:


- HTML encoding: This involves using HTML entities to represent characters. For example, `<` can be encoded as `&lt;`, `>` as `&gt;`, and `”` as `&quot;`.

- - URL encoding: This involves using percent signs followed by hexadecimal values to represent characters. For example, `<` can be encoded as…

---

*Originally published on [Medium](https://infosecwriteups.com/how-to-bypass-xss-filters-a-practical-example-3189877fe2ce). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
