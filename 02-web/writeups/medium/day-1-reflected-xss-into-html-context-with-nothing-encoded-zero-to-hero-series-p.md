# :globe_with_meridians: Day 1: Reflected XSS into HTML context with nothing encoded: Zero to Hero Series- Portswigger

---

What is Reflected XSS?

## Get RayofHope’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

*Reflected XSS arises when an application receives data from an untrusted source and includes that data within immediate responses in an unsafe way.*

Impact of Reflected XSS:

>

Reflected XSS can have serious consequences, including but not limited to Data Theft, Account Hijacking or Malware Installation.Data Theft: Attackers can steal sensitive user information, such as login credentials, credit card details, or personal data.

Account Hijacking: By compromising a user’s account, attackers can perform unauthorised actions or steal valuable assets.

Malware Installation: Attackers can use XSS to install malicious software, such as viruses, spyware, or ransomware, on the user’s device.

Mitigating Reflected XSS Attacks:

>

Input Validation: Validate all user inputs by ensuring that they are of the correct type, length, and format.

Output Encoding: Encode user-supplied data before it is displayed on the website, preventing it from being interpreted as HTML.

Content Security Policy (CSP): Use CSP to control the resources that are allowed to be loaded on the website, restricting the execution of malicious scripts.

## Let's solve the lab:

---
