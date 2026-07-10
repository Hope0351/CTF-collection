# :globe_with_meridians: Bypassing AWS WAF CRS with Cross-Site-Scripting (XSS) payload

---

# Bypassing AWS WAF CRS with Cross-Site-Scripting (XSS) payload

Earlier this year my colleague has identified an application which was clearly vulnerable to Cross-Site-Scripting as special characters were not encoded.

However, he quickly learned that the application is behind a WAF as attempts to exploit XSS resulted in HTTP 403 error message.

*Standard AWS WAF error message*

After talking to application owners we learned that in fact application is behind an AWS WAF with Core Rule Set enabled.

Taking into account how many web applications use AWS WAF with CRS, bypassing it seemed quite challenging. However, we decided to spend some extra time attempting to do so.

We started with checking what is available on Twitter just to find this post from early 2019:

*Unfortunately this payload did not work for us*

So we updated our payloads and learned that WAF is in fact bypassed, but script is not executed as major web browsers treat this payload as a comment.

*Script is not executed in the web browser*

However, it was clear now that prepending actual payload with some other characters may result in WAF bypass.

Having this in mind I launched Burp’s Intruder trying to replace “!” (%21) character with some other hexadecimal value, which would allow to bypass WAF.

## Get Marcin Szydlowski’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

After a while I had a full list of values which did not return an error. However, most of the characters ([a-z][A-Z]) following “<” character were interpreted by the web browser as an unclosed tag and did not result in script’s execution. Attempts to close the tag resulted in standard WAF error message (403).

*WAF Bypass — script not executed*

Best was yet to come though, as my list had also some special characters which went through the WAF unnoticed: ! *(%21)*, / *(%2F)*, ?*(%3F)*and % *(%25).*

Seconds later it was clear that out of this four payloads there is a one lucky winner, which allows for AWS WAF bypass and script execution in the web browser.

*AWS WAF bypass and script execution*

WAF bypass was also clearly visible in AWS WAF logs

*WAF logs confirm that XSS payload was not blocked*

After spending a while thinking how much money I can earn by using this payload in various bug bounty programs I decided to disclose it to AWS (which is currently not running any bug bounty program at all).

*Good boy…*Disclosure timeline:
23/05/2020 — Report sent to AWS Security Team
24/05/2020 — First response from AWS Security Team
04/06/2020 — Finding confirmed as a vulnerability

*Vulnerability is confirmed*

10/07/2020 — Fix announced
13/07/2020 — Write-up published

---
