# :globe_with_meridians: 📝 Title: Filter Failure: From HTML Injection to Full-Blown XSS via Rich Text Editors 🔥

---

# 📝 Title: Filter Failure: From HTML Injection to Full-Blown XSS via Rich Text Editors 🔥

Free Link 🎈

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
