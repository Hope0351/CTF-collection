# :globe_with_meridians: Reflected XSS on Admin Login Page

> **Original Source:** [Reflected XSS on Admin Login Page](https://infosecwriteups.com/reflected-xss-on-admin-login-page-94960596ec88)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Reflected XSS on Admin Login Page


Hi! I’m Aswin,security researcher and a penetration tester.Here we are discussing reflected XSS in a private bug bounty program.


On the website [https://xyz.redacted.com/a6,](https://xyz.redacted.com/a6,) when you attempt to access secret sections,The URL on the parameter “win” redirects you to a login page with values from the URL mirrored in the DOM.


*Reflect XSS- Admin Login page*

>

A cross-site scripting attack might be launched against the application since there is no adequate handle for the data reflected, making it susceptible.


## What is reflected cross-site scripting?


Reflected Cross-Site Scripting occurs when the injected script is mirrored off the website, such as an error message, search result, or other response.
Reflected type assaults are given to victims or targets through another channel, such as email or phishing.
When the user is duped into clicking the malicious script or link, the browser is triggered.
The search field is a basic example of Reflected XSS.


To launch a successful Reflected XSS attack, an attacker looks for instances where user input is utilised directly to create a response.
This frequently includes the inclusion of event attributes such as onload and onmouseover to elements that are not supposed to host scripts, such as image tags (img>).

## Proof of Concept:


When you visit the current URL, an alert with your cookie will appear on the screen.


## Get Aswin KV’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in

---

*Originally published on [Medium](https://infosecwriteups.com/reflected-xss-on-admin-login-page-94960596ec88). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
