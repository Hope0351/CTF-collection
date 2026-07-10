# :game_die: SQL Injection in The HTTP Custom Header

> **Original Source:** [SQL Injection in The HTTP Custom Header](https://infosecwriteups.com/sql-injection-in-the-http-custom-header-fd117ba1435e)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# SQL Injection in The HTTP Custom Header


It has been a long time since my last write-up. in this short write up I wanna share my last year's findings about SQL Injection that I found in the custom HTTP header request.


## Get yoshi m lutfi’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


So, I was doing my API penetration testing for a target. let's say redacted.com and after successful login, the request has one more HTTP header in the request, User header, and the value is a username that login to the application.


```
POST /abcd/abcd
Authorization: token
Host: redacted.com
User: user.abc
Postman-Token: token
...

{body request}
```


Now, I try to change the username for IDOR possibility but the server validates it by giving a message with a 500 internal error code and an error message that cannot get this API access.


*Error message when changing the User value*


Because this parameter is validated it is potential also for SQL Injection, so I put basic SQL Injection to the request ‘ OR 1=1- - and send the request and with ease, the server accepts the request and gives valid information. No way :D


*The request was accepted by the server*


Okay, we got a valid SQL Injection and of course sqlmap will do the rest. But with this vulnerability, it turns out that we can also request to the server without an authorization token.


*Successful request without Authorization token*


I hope you can take some points from my write-up, and I am sorry for being inactive for a couple of months. Have a nice day and keep learning!

---

*Originally published on [Medium](https://infosecwriteups.com/sql-injection-in-the-http-custom-header-fd117ba1435e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
