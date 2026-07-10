# :globe_with_meridians: How I Bypassed 2FA and Took Over Accounts with a Simple Brute Force Attack

> **Original Source:** [How I Bypassed 2FA and Took Over Accounts with a Simple Brute Force Attack](https://infosecwriteups.com/how-i-bypassed-2fa-and-took-over-accounts-with-a-simple-brute-force-attack-68ffc5cf5bd0)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# How I Bypassed 2FA and Took Over Accounts with a Simple Brute Force Attack


I’ve been learning web security for the past few weeks, and during this time, I’ve developed a habit of analyzing how different websites handle their security mechanisms. One day, while booking a concert ticket, something caught my attention. The login process required me to enter my email, followed by an OTP sent to my inbox. Accidentally, I entered the wrong OTP, which made me curious: what if I kept entering incorrect OTPs? Would the system lock me out or allow unlimited attempts? Out of curiosity, I entered around 10 wrong OTPs, and to my surprise, the website kept accepting my attempts without any restrictions — there was no rate limiting in place.


Setting Up the Attack


As a security enthusiast, I started wondering if it was possible to brute-force the correct OTP and gain access to the account without having access to the victim’s email. To test this, I created two accounts on the website, one as the attacker and the other as the victim.


I returned to the login page, entered the victim account’s email ID, requested an OTP, and submitted a random 6-digit code. Meanwhile, I opened Burp Suite and intercepted the OTP submission request.


I forwarded this request to Burp Suite Intruder, selected the OTP parameter, and launched a brute-force attack to guess the correct OTP. This is the payload set I used:


Identifying the Correct OTP


Once the attack was complete, I went through the responses in Burp Suite. Almost all of them had identical response sizes, clearly indicating failed OTP attempts. But then, one response caught my attention, it had a different length. And there it was! The correct OTP had been cracked.


After identifying the correct OTP, I replayed the request in the browser and retrieved the following response:


The Real Impact — Account Takeover


Now I had to figure out how to use this information to access the victim’s account. I logged back into my attacker account and inspected the browser cookies. One cookie immediately caught my attention — it was labeled “currentUserSB”


I copied the cookie and asked ChatGPT to analyze it. I realized that the cookie was actually an url encoded JSON string, which matched the data I saw in the server’s response after brute-forcing the victim’s OTP. Now everything made sense.


## Get Rishant Arora’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


I took the JSON data from that response, encoded it back into the format used for the cookie, and replaced the cookie in my attacker’s account using a browser extension called Cookie Editor, then refreshed the page and I was successfully logged into the victim’s account.


What a Simple Missing Rate Limit Allowed Me to Achieve:


- Full Account Takeover (ATO): I was able to completely access any user’s account without needing their credentials or email access.

- Sensitive Data Exposure: Personal information like email, mobile number, country, profile ID, and JWT token were exposed in the API response.

- Session Hijacking: With the leaked cookie data, I could maintain persistent access to the victim’s account.


How This Could Have Been Prevented


- Implement Rate Limiting: Strictly limit the number of OTP attempts per user/IP to prevent brute-force attacks.

- Account Lockout Mechanism: Temporarily block OTP verification after multiple failed attempts.

- Short Expiry for OTPs: Make OTPs valid only for a very short time (e.g., 30–60 seconds).


Conclusion


This was a fun experience that helped me think a bit more out of the box. Even with 2FA, one small mistake in implementation was enough to take over accounts. It’s a reminder that security is all about getting the details right.


Disclaimer:


This blog post is for educational purposes only. All testing was done on my own accounts without causing harm to any users or systems. The vulnerability was responsibly disclosed by me to the concerned team.


That’s it for this blog! If you have any questions, feel free to ask in the comments.


You can also connect with me on LinkedIn here: [www.linkedin.com/in/rishant-arora-92498422b](http://www.linkedin.com/in/rishant-arora-92498422b)

---

*Originally published on [Medium](https://infosecwriteups.com/how-i-bypassed-2fa-and-took-over-accounts-with-a-simple-brute-force-attack-68ffc5cf5bd0). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
