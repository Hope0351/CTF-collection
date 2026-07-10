# :globe_with_meridians: Understanding JSON Web Token (JWT) Security

---

# Understanding JSON Web Token (JWT) Security

From Basics to Breaking Authentication

JSON Web Tokens (JWTs) have become the backbone of modern authentication systems. If you’re a penetration tester or bug bounty hunter, understanding JWT vulnerabilities isn’t just useful; it’s essential. This blog will walk you through the very basics that you need to know about JWT security testing.

*JWT Security*

## What is JWT? A quick refresherJWT is a standard as specified in RFC 7519, which can be implemented in either of three ways: JSON Web Signature (JWS) or JSON Web Encryption (JWE), or Unsecured JWT. JWS is widely and majorly used where it preserves the integrity of the claims made by using the signature, while in JWE, it ensures confidentiality by encrypting the entire content, which is only accessible to parties with the decryption keys. In an unsecured JWT implementation, ‘alg’ is set to none.

JSON Web Token (JWT) consists of 3 parts: JOSE (JSON Object Signing and Encryption) header, Payload, and Signature.

A JWT = `HEADER.PAYLOAD.SIGNATURE` (base64url parts).

> Header: tells alg (HS256, RS256), typ, kid.

> Payload: claims (sub, iss, aud, exp, role…). Not encrypted-anyone can read it. The payload of a JSON Web Token (JWT) contains claims, which store information…

---
