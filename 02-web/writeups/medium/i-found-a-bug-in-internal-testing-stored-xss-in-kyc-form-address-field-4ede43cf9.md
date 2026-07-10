# :globe_with_meridians: I Found a Bug in Internal Testing: Stored XSS in KYC Form Address Field

---

# I Found a Bug in Internal Testing: Stored XSS in KYC Form Address Field

*Image by Pixabay*

### When an Address Field Became an XSS Bug Bounty

It was just another Tuesday of internal testing on our trading platform when I stumbled on something unexpected. I was filling out the KYC form for a test user — you know, the usual Name, Address, ID number — and I thought, “What if I try putting some HTML or script into the *Address* field?” To my surprise, the app accepted it! Later, when I viewed that user’s profile, the hidden test script I entered popped up an alert. I had discovered a Stored Cross-Site Scripting (XSS) vulnerability in the address field.

This hit me as a reminder of why input validation is so important. Simply put, input validation means checking user-provided data before using it in the application. It’s often called the “first line of defense” in secure development. By validating input (for example, ensuring an address field contains only normal characters and not HTML tags), we prevent *malicious* code from being injected into our system.

The OWASP Secure Coding guide even advises using a whitelist approach (an *allow-list*) to define what good input looks like, rather than trying to block bad input, which attackers can often bypass. In short, when we *don’t* validate inputs properly, we leave openings for all sorts of attacks —…

---
