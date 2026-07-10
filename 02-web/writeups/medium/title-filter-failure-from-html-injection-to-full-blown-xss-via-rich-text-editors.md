# :globe_with_meridians: 📝 Title: Filter Failure: From HTML Injection to Full-Blown XSS via Rich Text Editors 🔥

> **Original Source:** [📝 Title: Filter Failure: From HTML Injection to Full-Blown XSS via Rich Text Editors 🔥](https://infosecwriteups.com/title-filter-failure-from-html-injection-to-full-blown-xss-via-rich-text-editors-af6809e248b4)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# 📝 Title: Filter Failure: From HTML Injection to Full-Blown XSS via Rich Text Editors 🔥


Free [Link](https://medium.com/@iski/title-filter-failure-from-html-injection-to-full-blown-xss-via-rich-text-editors-af6809e248b4?sk=b07447cdc942cc53748dd2ac89c00b94) 🎈


Hey there!😁


*Image by Gemini AI*

## Life Tip #47:


Never trust a coffee machine before 9 AM, a JavaScript function before sanitization, and a rich text editor to protect your users. ☕💻💣


This is a story about how a seemingly innocent WYSIWYG editor turned into my personal printing press for bounty bucks. 💰 And no, this isn’t your basic `<script>alert(1)</script>` tale. This was a journey through misconfigured filters, broken sanitizers, and a glorious client-side RCE.

## 🕵️‍♂️ Reconnaissance: The Rich Editor That Got Too Fancy


While running a mass recon across dozens of programs, I stumbled upon a juicy endpoint that screamed *“edit your profile”* with rich text formatting enabled. It used `tinymce`, one of the most popular WYSIWYG editors.


I noticed this endpoint:


```
POST /user/update-bio
Host: target.com
Content-Type…
```

---

*Originally published on [Medium](https://infosecwriteups.com/title-filter-failure-from-html-injection-to-full-blown-xss-via-rich-text-editors-af6809e248b4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
