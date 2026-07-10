# :globe_with_meridians: Write Up Jwt Authentication Bypass Via Jwk Header Injection Portswigger Academy 

> **Original Source:** [Write Up Jwt Authentication Bypass Via Jwk Header Injection Portswigger Academy ](https://infosecwriteups.com/write-up-jwt-authentication-bypass-via-jwk-header-injection-portswigger-academy-a08975256e8c)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## The theory


The server uses `RS256` as the algorithm for the token. There are multiple options that I can follow


- None algorithm / strip signature

- Inject my own key

- Obtain the private key (and password if it is protected)


The first option is the easiest to test. In theory, the next step would be to check whether I can remove the signature or change the algorithm to *none*. However, there are dedicated labs for these two issues so I skip the checks here. Refer to my write-ups for JWT authentication bypass via flawed signature verification and [JWT authentication bypass via unverified signature](https://systemweakness.com/write-up-jwt-authentication-bypass-via-unverified-signature-portswigger-academy-a890510bff1d) for details.


## Get Frank Leitner’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The second option has two flavors. I can either change the algorithm to HS256 and inject a secret key or I keep the algorithm and inject an RSA key. It is always best to change as little as possible, so trying to inject an RSA key changes only one variable. I also do not know whether the backend uses the algorithm provided in the token or enforces RS256.


Option (3) is unlikely and also the most difficult, so I skip this for now until everything else fails.


I now generate a new *RSA key* in the *JWT Editor key store*:


*Generation of a new RSA key pair*


In the Burp Proxy, I send the request to `/my-account` to Repeater and select the `Attack -> Embedd JWK` option. I select the RSA signing key I just generated:


*Embedding JWK and signing with it*


After clicking `OK`, the signature is updated automatically. If the request contains an invalid or no JWT as the session cookie, the application redirects to the `/login` page.


I send the request and the response contains my account page, confirming that the signature verification on the backend used the RSA public key information I injected in the JWT header.


*Backend accepts my own signature using injected public key*

---

*Originally published on [Medium](https://infosecwriteups.com/write-up-jwt-authentication-bypass-via-jwk-header-injection-portswigger-academy-a08975256e8c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
