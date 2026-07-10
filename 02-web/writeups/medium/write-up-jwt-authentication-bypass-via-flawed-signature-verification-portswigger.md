# :globe_with_meridians: Write-up: JWT authentication bypass via flawed signature verification @ PortSwigger Academy

> **Original Source:** [Write-up: JWT authentication bypass via flawed signature verification @ PortSwigger Academy](https://infosecwriteups.com/write-up-jwt-authentication-bypass-via-flawed-signature-verification-portswigger-academy-2107eddec3b7)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Write-up: JWT authentication bypass via flawed signature verification @ PortSwigger Academy


This write-up for the lab *JWT authentication bypass via flawed signature verification* is part of my walk-through series for [PortSwigger’s Web Security Academy](https://portswigger.net/web-security).


Learning path: Advanced topics → JWT attacks


Python script: [script.py](https://github.com/frank-leitner/portswigger-websecurity-academy/blob/main/23_JWT_attacks/JWT_authentication_bypass_via_flawed_signature_verification/script.py)

## Lab description


## Steps


The lab application deals with JWTs. I use the extension `JSON Web Tokens (JWT4B)` to avoid having to deal with manual de- and encoding of the JWTs all the time.

## Analysis


As usual, the first step is to analyze the functionality of the lab application. In this lab, it is a blog page.


The lab description refers to authenticated functionality, so I log in with the credentials of `wiener`. Right away, Burp Proxy notifies me that the response contains a JWT:


*JWT shown in the response to my login*


When I try to access the `/admin` page as user `wiener`, I am greeted by the message `Admin interface only available if logged in as an administrator`.

---

*Originally published on [Medium](https://infosecwriteups.com/write-up-jwt-authentication-bypass-via-flawed-signature-verification-portswigger-academy-2107eddec3b7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
