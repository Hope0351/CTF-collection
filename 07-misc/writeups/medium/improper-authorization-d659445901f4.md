# :game_die: Improper Authorization. This blog will demonstrate an…

> **Original Source:** [Improper Authorization. This blog will demonstrate an…](https://infosecwriteups.com/improper-authorization-d659445901f4)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

This blog will demonstrate an interesting case where authorization was not implemented properly. Successful exploitation of this issue leads to privilege escalation (horizontal and vertical both) and IDOR in the web application.

### Normal Flow


This is the summary of what the normal flow of the application is:


Basically, when a user-A logs into the application he/she receives a JWT token which is then used to authorize his/her identity for subsequent requests. So, when that user-A tries to access resources of other users (for example-> user-B’s profile details), the application responds with an unauthorized error message.

### Vulnerability in Application


Please Note: For demonstration purposes only I have used [the juice-shop application](https://juice-shop.herokuapp.com/)


## Get PSDooM’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Step-By-Step Flow -> user-A clicks on his basket to view items inside it.


Below is the screenshot of the intercepted request using Burpsuite to fetch basket details. Here, you can observe the JWT token is being sent in HTTP GET request with the “Authorization” HTTP header.


I send the intercepted request to the “Repeater” tab inside Burpsuite to observe the normal response. Here you can observe a successful response in the repeater tab when the JWT token is valid and the user-A is authorized to view his/her basket.


Now, when the JWT token in the request is replaced with that of some other user-B (which is not authorized to view user-A’s basket in vulnerable application) the server responds with an Unauthorized Message.


But, when the request is slightly modified as shown (Replacing the Bearer keyword with Basic and JWT token after that with base64 encoded credentials in format “username:password” in the Authorization HTTP header).


I get a successful response that is similar to the one we saw before (this is just the screenshot of the previous request to demonstrate the same)


That’s It. Thanks for reading!


For feedback/suggestions please e-mail: psdoom@protonmail.com

---

*Originally published on [Medium](https://infosecwriteups.com/improper-authorization-d659445901f4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
