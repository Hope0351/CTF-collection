# :globe_with_meridians: Reflected XSS on Gaming Blog Website

> **Original Source:** [Reflected XSS on Gaming Blog Website](https://infosecwriteups.com/reflected-xss-on-gaming-blog-website-edc448d613a3)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Reflected XSS on Gaming Blog Website


I found a reflected XSS vulnerability on a website I used to frequent when playing a text-based MUD (multi user dungeon).


This website had a calculator of sorts, that would determine how much skill you needed to progress to a given level that you would enter into a text input box. I decided to test this and see if it was vulnerable.


Upon inspecting the source code, I see that the javascript shows I’m within a “textarea” tag. So I decided to test this by escaping it.


```
</textarea>
```


I also learned that modern websites are typically defended against the alert() method. We now use the print() method to demonstrate XSS on most modern websites according to Portswigger.

## XSS proof of concept


>

You can confirm most kinds of XSS vulnerability by injecting a payload that causes your own browser to execute some arbitrary JavaScript. It’s long been common practice to use the `alert()` function for this purpose because it's short, harmless, and pretty hard to miss when it's successfully called. In fact, you solve the majority of our XSS labs by invoking `alert()` in a simulated victim's browser.


Unfortunately, there’s a slight hitch if you use…

---

*Originally published on [Medium](https://infosecwriteups.com/reflected-xss-on-gaming-blog-website-edc448d613a3). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
