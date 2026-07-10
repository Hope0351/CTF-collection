# :globe_with_meridians: An exciting journey to find SSRF , Bypass Cloudflare , and extract AWS metadata !

> **Original Source:** [An exciting journey to find SSRF , Bypass Cloudflare , and extract AWS metadata !](https://infosecwriteups.com/an-exciting-journey-to-find-ssrf-bypass-cloudflare-and-extract-aws-metadata-fdb8be0b5f79)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# An exciting journey to find SSRF , Bypass Cloudflare , and extract AWS metadata !


In the name of God.


Hi researchers,


This is my first write-up, and in this write-up i’m gonna share with you my recent exciting finding which led me to extract aws metadata !

## What is ssrf ?


I already know that most readers know what is ssrf but for a brief explanation let’s look at portswigger:

>

Server-side request forgery (also known as SSRF) is a web security vulnerability that allows an attacker to induce the server-side application to make HTTP requests to an arbitrary domain of the attacker’s choosing.


## The story:


I was working on a program and since I have no permission to disclosure the name of the target , let’s call it redacted.com .


after a little bit working around this program I came to an endpoint which was some thing like this ~> [https://redacted.com/api/download-pdf?url=](https://api.onupkeep.com/api/download-pdf?url=http%3A%2F%2Fc1ef8684bfb2.ngrok.io)”http://SomeThing.com”.


After seeing this url I was like :


I immediately fired up my burp collaborator and replace the default url with mine , fortunately my burp collaborator received HTTP and DNS requests and I got the burp page in response.


After , first thing came to my mind was, let’s put [http://localhost](http://localhost) there to get interesting response !


## Get hosein vita’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


but I got :


*Sad :(*


There was a protection for this one , but i didn’t give up and i went through all the way’s to bypass localhost restriction , I tried all of these payloads :

>

[http://127.0.0.1:80](http://127.0.0.1:80)


[http://127.0.0.1:443](http://127.0.0.1:443)


[http://127.0.0.1:22](http://127.0.0.1:22)


[http://127.1:80](http://127.1:80)


[http://0](http://0)


[http://0.0.0.0:80](http://0.0.0.0:80)


[http://localhost:80](http://localhost:80)


[http://[::]:80/](http://[::]:80/)


[http://[::]:25/](http://[::]:25/) SMTP


[http://[::]:3128/](http://[::]:3128/) Squid


[http://[0000::1]:80/](http://[0000::1]:80/)


[http://[0:0:0:0:0:ffff:127.0.0.1]/thefile](http://[0:0:0:0:0:ffff:127.0.0.1]/thefile)


And lot’s of other’s which you can find in ~> [https://book.hacktricks.xyz/pentesting-web/ssrf-server-side-request-forgery](https://book.hacktricks.xyz/pentesting-web/ssrf-server-side-request-forgery).


Even i tried other protocols like : “file:///” , “sftp://” , “gopher://” and so on .


None of them works ! :(


After a while something triggers my mind , that why not trying “http://169.254.169.254/” for retrieving AWS metadata instances ?.


So i did that and i got :


*Cloudflare everywhere ! :@*

## Time to make something happen


I continued researching till i found this one :

>

It might be possible that the server is filtering the original request of a SSRF but not a possible redirect response to that request. For example, a server vulnerable to SSRF via: `url=https://www.google.com/` might be filtering the url param. But if you uses a [python server to respond with a 302](https://pastebin.com/raw/ywAUhFrv) to the place where you want to redirect, you might be able to access filtered IP addresses like 127.0.0.1 or even filtered protocols like gopher.


So i fired up my django server and insert this code to my server :


*I used ngrok to connect to my server.*


I sent this request and i got the prod then i put the prod in my django server after “[http://169.254.169.254/latest/meta-data/iam/security-credentials/](http://169.254.169.254/latest/meta-data/iam/security-credentials/')YOUR-PROD-HERE”,


And Finally I got :


After this I :


This is the end , Thank you for reading my article hope you learned something, and wish me to find more bugs like this to share with you ! ❤


My twitter : [https://twitter.com/HoseinVita](https://twitter.com/HoseinVita)

---

*Originally published on [Medium](https://infosecwriteups.com/an-exciting-journey-to-find-ssrf-bypass-cloudflare-and-extract-aws-metadata-fdb8be0b5f79). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
