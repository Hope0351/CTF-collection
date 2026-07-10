# :globe_with_meridians: All About Attacking JWT. JWT: The Weak Link in Your Security…

> **Original Source:** [All About Attacking JWT. JWT: The Weak Link in Your Security…](https://infosecwriteups.com/all-about-attacking-jwt-9770f2b9d087)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

Hello Hackers, I Hope you guys are doing well and hunting lots of bugs and Dollars !


Our today’s agenda is very concerning and trending topics that are related to attack vectors on JSON Web Token ( JWT ). let’s jump on the subject and understand the concept.

## What is JWT ?


JSON web token is an Open standard to transmit authentication details between two parties. They are often used for authorization purposes, but also it can be utilized for authentication purposes too. JWT is stateless, therefore there is no need to manage a session. which makes it an effective choice for large scalable websites in which users must interact with multiple back-end servers flawlessly.

## JWT Structure


JWT consists of three parts which are separately encoded and connected together with dots.


Header :- It defines token types and algorithm which is used for signing.


Payload :- This represents claims, which will denote information about logged-in users. Although owners can configure it according to their needs, there are some registered claims in it.


- iss- Issuer

- sub- Subject

- aud- Audience

- exp- Expiration time

- jti- JWT ID

- nbf- Not before

- iat- Issued at


Signature :- It contains primarily all the previous messages but is encoded to assure integrity checks with the help of a secret key.


As of now, we are aware of its structure and usage of it. Let’s understand the back-end mechanism of generating and validating JWT tokens.


Generating Token


- The server creates the JSON Header (Algorithm + Type of token) and encodes it with base64.

- Then the server will create a payload ( User Information) and encode it with base 64. After this, it will tie with the dot.

- At last, it will sign the final value i.e (Header + payload), and again encode it with base64. add a dot and then the signature.


Validating Token


- Once the server will receive the token, it will split into three parts and Decode individual parts.

- Then simply parse the JSON for the header and payload, in terms of retrieving the algorithm and data which is claimed by the logged-in user.

- At the last, it will confirm the integrity with the help of a signature and also verify the claims.


*[https://cdn.hashnode.com/res/hashnode/image/upload/v1616225393075/v2TJSq1Hb.png?auto=compress,format&format=webp](https://cdn.hashnode.com/res/hashnode/image/upload/v1616225393075/v2TJSq1Hb.png?auto=compress%2Cformat&format=webp)*

>

Take a look at this for a more in-depth understanding of it. ([https://medium.com/cyberverse/five-easy-steps-to-understand-json-web-tokens-jwt-7665d2ddf4d5](https://medium.com/cyberverse/five-easy-steps-to-understand-json-web-tokens-jwt-7665d2ddf4d5) )


## JWT Attacking Scope


Even though it is secure enough to protect the data it holds or uses, this only applies when it is properly configured. Developers sometimes ignore or unknowingly end up leaving this vulnerable. So let’s explore the possible attacks we could launch against it.


## Get Xcheater’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Accepting arbitrary signatures :- Verifying a JWT signature helps to ensure the integrity of data by verifying that information passing through payload and headers has not been tampered with. However, sometimes developers don’t configure tasks accurately.
Since the back-end system is currently not checking the signature, an attacker can tamper with the information and use it for various purposes.


None Algorithm attack :- Sometimes applications accept tokens with no signature, i.e the algorithm parameter is set to NONE.


The “none” algorithm is used when no encryption or signing is applied to the JWT, making it vulnerable to tampering and replay attacks. An attacker can easily modify the contents of the JWT and use it to gain unauthorized access to protected resources.
This feature was originally developed for debugging. The developer should make sure to push it off in a production environment. Since the back-end system is accepting the NONE algorithm, so attackers can tamper with information and use it for various purposes.


Weak Secret key :- JWT uses a symmetric signing algorithm that uses the same secret key to sign and verify the signature.


The secret key is a string of characters that is used to encrypt and decrypt the JWT. An attacker can easily guess the secret key if it is weak. This means that an attacker could generate their own JWT using their own information and gain access to the unauthorized access materials. The secret key can be cracked offline by brute forcing with just one valid token.


Information Disclosure :- Sometimes a JWT token stores a large amount of data about the logged-in user, which may be configured for any purpose by the developer. Keeping sensitive data in the payload section is insecure because it is encoded in base64, which is not a cryptographic algorithm and can be read by any other user who intercepts it.


Insufficient session expiry :- In general, the server should terminate the session after logout, but because JWT contains no session information, the developer must define a “exp” claim in the payload section to set an expiry time for the token.


As a pentester you should revalidate it by using the same set of token and check is it terminated by the server end or not.
*Note *:- While replaying the session, you can also play around JWT Id.


Algorithm Confusion Attack :- A JWT Algorithm Confusion vulnerability occurs when an attacker manipulates the algorithm used in a JSON Web Token (JWT) in such a way that the receiver of the JWT is unable to properly validate the JWT’s signature.


When the attacker is able to modify the “alg” claim of the JWT header, which specifies the algorithm used to sign the JWT, the attack can occur.


In simpler terms, the attacker can trick the application into accepting a JWT that was signed with a different algorithm than the one the application is actually expecting.


For example, if the web application is configured to accept only JWT that are signed with the “HS256” algorithm, an attacker could create a JWT that is signed with the “HS512” algorithm and send it to the application. If the algorithm used to sign the JWT is not properly checked, the application will accept the attacker’s JWT as valid and grant the attacker access to protected resources.

## KID manipulation :-


kid is an extra header claim that holds a key identifier, which is especially useful when signing tokens with multiple keys and need to look for the right one to verify the signature.


Because this field is controlled by the user, attackers can modify it and end up causing different consequences.


Revealing Key


It is possible that it will reveal other keys as well, so it is worthwhile to search the web directory for that file or a variant of it.
For example, if “kid”:”key/12345", search the web root for /key/12345 and /key/12345.pem.


Directory traversal


When an application uses the Key ID field as part of a file path and fails to properly validate or sanitize the field, an attacker can change the Key ID to a value that contains “../” (dot-dot-slash) sequences, which can be used to navigate up the directory tree.


Injection’s


The “KID” (Key ID) parameter identifies the cryptographic key that was used to sign the JWT. Because the KID parameter can be supplied by the user, it opens the door to a wide range of injection attacks. If the KID is retrieved from the database, SQL injection is possible; in other cases, OS command injection is possible.


Some Reports for reference :-


[https://hackerone.com/reports/638635](https://hackerone.com/reports/638635)


[https://hackerone.com/reports/896649](https://hackerone.com/reports/896649)


[https://hackerone.com/reports/638635](https://hackerone.com/reports/638635)


I hope this article has provided you with a better understanding of how to approach for application which is using JWT as an attacker. If you want more information and updates on various Application security related topics, please follow me on Twitter at [https://twitter.com/Xch_eater](https://twitter.com/Xch_eater).

---

*Originally published on [Medium](https://infosecwriteups.com/all-about-attacking-jwt-9770f2b9d087). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
