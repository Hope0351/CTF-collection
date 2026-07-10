# :globe_with_meridians: Why strip_tags() Does Not Protect You From XSS in PHP/Laravel

> **Original Source:** [Why strip_tags() Does Not Protect You From XSS in PHP/Laravel](https://infosecwriteups.com/why-strip-tags-does-not-protect-you-from-xss-in-php-laravel-c97d0e805213)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Why strip_tags() Does Not Protect You From XSS in PHP/Laravel


## A False Sense of Security That Your Code Probably Has Right Now


Developers in countless PHP applications believe that sanitizing user input with `strip_tags()` prevents XSS attacks. It doesn't. The function removes HTML and PHP tags from a string, but it leaves attributes intact. An attacker doesn't need script tags to execute JavaScript. They just need an event handler, a javascript: protocol in a URL, or an SVG element with embedded code. Most developers never discover this vulnerability until something goes wrong.


`strip_tags()` gives you a false sense of security while leaving the door wide open. This article explains why, shows you real payloads that `strip_tags()` misses, and walks you through the proper defenses.

## What strip_tags() Actually Does


The PHP function `strip_tags()` removes HTML and PHP tags from a string. If you pass it the whitelist parameter, it removes everything except the tags you explicitly allow. That seems reasonable on the surface.


Here’s the problem: it only removes tags. It does not process, validate, or escape HTML attributes.


```
$userInput = '<img src=x onerror="alert(\'XSS\')">';
echo strip_tags($userInput);
// Output: (empty…
```

---

*Originally published on [Medium](https://infosecwriteups.com/why-strip-tags-does-not-protect-you-from-xss-in-php-laravel-c97d0e805213). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
