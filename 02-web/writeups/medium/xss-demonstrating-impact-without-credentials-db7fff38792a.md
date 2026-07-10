# :globe_with_meridians: XSS: Demonstrating Impact Without Credentials

> **Original Source:** [XSS: Demonstrating Impact Without Credentials](https://infosecwriteups.com/xss-demonstrating-impact-without-credentials-db7fff38792a)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# XSS: Demonstrating Impact Without Credentials


Hello, fellow hackers and tech enthusiasts. In this write-up, I will demonstrate how I used a Layer 1 authentication bypass to showcase the impact of an XSS vulnerability, even when the program did not provide credentials for testing.


Let’s get started.


The program does not allow disclosure, so I am redacting the details. We’ll refer to the target as: `docs.redacted.com`. This was a public program on Bugcrowd with a very confined scope.


Hacking within such a confined scope is challenging, but the program had zero accepted reports, which made it an enticing target for me.


I chose a random target from the six available and accessed it.


It was a documentation page. I explored all the links and landed on this page:


`[https://docs.redacted.com/support](https://docs.redacted.com/support.)`[.](https://docs.redacted.com/support.)


The best part was that the site was open source. As the saying goes, “I can hack the world if I have the source code.” ,


So, I got into analyzing the source code. It took time, but it was all worth it.


Here is the interesting code I found:


Take a look at these lines:


```
if (!token || !(await validateFusionFeedToken(token))) {
return {
redirect: {
destination: '/login#destination=' + encodeURIComponent(dest),
permanent: false,
},
};
}
```


If the supplied token value is correct, it redirects the user to the destination, which is specified in the GET parameter as `/login#destination=`.


There is no input validation for the destination value, confirming a P4 vulnerability "Open Redirect" in this domain.


However, this is an action-specific vulnerability.


Hence, even for the Open redirect, we will need the credentials or the token value to at least pass the function for the redirection to take place. However, the program had no credentials provided. I did reach out to the tech support of the domain and they said :


:/ . Nvm, I respect the company’s policy.


## Get Shlok K’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Let's get back to the open redirect.


The chain of open redirects can lead to a very effective XSS attack. Using the `javascript:` URI, we can supply arbitrary JavaScript that will be executed when the user logs in.


For example, `javascript:alert(1)` would pop an alert box saying "1".


I accessed the URL to make a final attempt to bypass the login and prove the impact:


URL : https://docs.redacted.com/login#destination=javascript:alert(1)


I entered random credentials and captured the request using Burp.


```
POST /v2/graphql HTTP/2
Host: xxx.xxxx.redacted.com
Content-Length: 12
Sec-Ch-Ua: "Google Chrome";v="125", "Chromium";v="125", "Not.A/Brand";v="24"
Content-Type: application/graphql
Sec-Ch-Ua-Mobile: ?0
Authorization: token abcd
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/125.0.0.0 Safari/537.36
Sec-Ch-Ua-Platform: "Windows"
Accept: /
Origin: https://docs.redacted.com
Sec-Fetch-Site: same-site
Sec-Fetch-Mode: cors
Sec-Fetch-Dest: empty
Referer: https://docs.redacted.com/
Accept-Encoding: gzip, deflate, br
Accept-Language: en-GB,en-US;q=0.9,en;q=0.8
Dnt: 1
Sec-Gpc: 1
Priority: u=1, i

{__typename}
```


A GraphQL POST request was being made to a different subdomain and our supplied credential was being parsed as an Authorization Token value. E.g.; abcd in this case.


Response:


```
HTTP/2 401 Unauthorized
Date: Sat, 15 Jun 2024 18:48:30 GMT
Content-Type: application/json
Content-Length: 64
Cf-Ray: 8944bc11abef9a78-NAG Cf-Cache-Status: DYNAMIC
Access-Control-Allow-Origin: *
Cache-Control: max-age=1
Vary: Accept-Encoding, Authorization
Content-Security-Policy: default-src 'none'
X-Content-Type-Options: nosniff
Server: cloudflare
{"message":"You are not authorized to perform this operation."}
```


So we got a 401 Unauthorized error.


The best and the only thing I could try at this point was to change the Response code from 401 to 200. New response:


```
HTTP/2 200 OK
Date: Sat, 15 Jun 2024 18:48:30 GMT
Content-Type: application/json
Content-Length: 64
Cf-Ray: 8944bc11abef9a78-NAG
Cf-Cache-Status: DYNAMIC
Access-Control-Allow-Origin: *
Cache-Control: max-age=1
Vary: Accept-Encoding, Authorization
Content-Security-Policy: default-src 'none'
X-Content-Type-Options: nosniff
Server: cloudflare

{"message":"You are not authorized to perform this operation."}
```


And it did work. The XSS was executed.


Further analysis led me to discover that the supplied authorization token value or the pass supplied was being passed as the cookie value and the HTTP-only flag was not set.


Attack scenario :


```

1. The malicious URL would be sent to the victim.
2. The victim logs in with the correct pass and the XSS gets executed.
3. Since the password is directly being passed on as a cookie value,
the attacker will use the cookie value as the pass and log into the victim's account.
```


I created a well-written report and was paid $$$ + 10 points for the finding. Also, I was the first Hall of Fame of the program. 😈


Until the next time, keep growing, keep hacking.


Bye!

---

*Originally published on [Medium](https://infosecwriteups.com/xss-demonstrating-impact-without-credentials-db7fff38792a). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
