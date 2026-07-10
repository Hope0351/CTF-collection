# :globe_with_meridians: Bypassing Email Verification Through Http Response Interception 7644A907899A

> **Original Source:** [Bypassing Email Verification Through Http Response Interception 7644A907899A](https://infosecwriteups.com/bypassing-email-verification-through-http-response-interception-7644a907899a)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

>

Note: I’ll be using `gaza.com` and `palestine.com` as placeholders for the actual hostnames.


### Summary


While testing the signup process on gaza.com, I was directed to https://palestine.com/account/dashboard/?utm_source=gaza&utm_medium=banner&utm_campaign=valentine2024&utm_content=email&ref=2276&visit_id=1054793, I discovered that the email verification code is being sent back in the HTTP response after submitting the signup form. At first, I thought, *“Is this real, or are you kidding me?”* So, I checked my temporary email to confirm if the verification code in the HTTP response matched the one sent to the email and it did!
This allows me to intercept the request and retrieve the verification code without needing to check the associated email account, potentially bypassing the verification step.


### Steps to Reproduce:


- Navigate to the signup page.

- Fill out the required fields (name, email, password, etc.).

- Intercept the request when clicking the “Signup” button using Burp Suite or any other HTTP proxy tool.

- Forward the intercepted request to the server.

- In the server’s response, observe that the verification code sent to the user’s email is included in the response.


Observed Behavior: The server sends the verification code both to the user’s email and within the HTTP response body. This allows anyone with access to the HTTP response to retrieve the verification code and complete the signup process without checking their email.


## Get callgh0st’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Expected Behavior: The verification code should only be sent to the email address provided during signup. It should not be disclosed in any HTTP responses or be accessible via the client-side application.


Impact: This issue can allow an attacker to:


- Bypass email verification by capturing the verification code directly from the response.

- Automate account creation using fake or unverified email addresses.

---

*Originally published on [Medium](https://infosecwriteups.com/bypassing-email-verification-through-http-response-interception-7644a907899a). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
