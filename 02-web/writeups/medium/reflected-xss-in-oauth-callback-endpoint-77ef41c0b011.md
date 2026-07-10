# :globe_with_meridians: Reflected XSS in OAuth Callback Endpoint

---

# Reflected XSS in OAuth Callback Endpoint

Free Article Link: Click for free!

Hello readers,

While testing an OAuth implementation on target.com, I came across a reflected XSS vulnerability that I found interesting and worth sharing. Even though XSS is one of the older web security issues, it still pops up in modern applications — and when it hits authentication flows like OAuth, it can have serious consequences.

In this article, I’ll walk you through what I found, why it’s important, and how it could be exploited if left unpatched.

## Understanding Reflected XSS

Reflected cross-site scripting happens when an application takes user-supplied input and includes it in the page without proper validation or encoding. The input is then interpreted by the browser as executable code.

Unlike stored XSS, which persists on the server, reflected XSS is “instantaneous” — it executes as soon as someone clicks a crafted link. Because it’s often delivered via URLs, it’s especially dangerous in phishing attacks: a malicious URL can appear to be part of a trusted site, tricking users into executing scripts in their browser.

When this kind of vulnerability appears in sensitive endpoints like OAuth callbacks, attackers could potentially hijack sessions, steal tokens, or…

---
