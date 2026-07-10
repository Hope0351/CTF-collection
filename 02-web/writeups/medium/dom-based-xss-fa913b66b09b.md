# :globe_with_meridians: Dom Based Xss Fa913B66B09B

> **Original Source:** [Dom Based Xss Fa913B66B09B](https://infosecwriteups.com/dom-based-xss-fa913b66b09b)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

An overlooked JavaScript plugin led to a dangerous DOM-based Cross-Site Scripting flaw exploitable across major browsers


## Introduction


Uber has been at the forefront of tech innovation for years, but even giants can stumble. In 2016, security researcher e3xpl0it reported a DOM-based Cross-Site Scripting (XSS) vulnerability on Uber’s `eng.uber.com` subdomain. The culprit? A popular jQuery plugin called `prettyPhoto`, widely used for creating image lightboxes — but also known for its outdated and unsafe code handling.


This bug was not only functional across Chrome, Firefox, and Internet Explorer, but also triggered instantly with a single malicious link. Let’s walk through the vulnerability, the vectors used, and how this simple bug could have led to a serious security impact.

---

*Originally published on [Medium](https://infosecwriteups.com/dom-based-xss-fa913b66b09b). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
