# :globe_with_meridians: One Time Code Bypass With An Inverted Brute-Force Attack

---

# One Time Code Bypass With An Inverted Brute-Force Attack

“We’ve sent a six-digit code to your email address. Enter it below to login.”

![img_1.png](images/one-time-code-bypass-with-an-inverted-brute-force-attack-7c5a270196d1/img_1.png)




*Photo by [Alvin Lenin](https://unsplash.com/@alenin99?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText) on [Unsplash](https://unsplash.com/s/photos/glass-ball?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText)*

We see them all the time while testing web applications. In order to verify your identity, the application sends a 6 digit numerical code to your registered email address or phone number. The purpose is to prove that the person performing the action is also in possession of the phone or mailbox attached to it. No access, no authorisation. It’s a useful second factor to apply a little extra security to a process.

If you try to guess the code it expires after 5 or so attempts. The odds of guessing correctly are 5/1,000,000, or 1/200,000 (0.0005%). Any guesses after the first 5 are invalid. This prevents you from brute-forcing all 1,000,000 combinations from 000000 to 999999.

Sounds pretty safe, right? Well, it can be. But sometimes developers make mistakes in their assumptions. Here’s one of my favourite bugs to test for and how to exploit it.

## Standard Use of One Time Codes or Pins (OTCs or OTPs)

In normal usage, a user performs an action that generates a one time code which is sent to their email address or phone number. They pick up their phone, read the code and enter it correctly on the first attempt. Job done.

---
