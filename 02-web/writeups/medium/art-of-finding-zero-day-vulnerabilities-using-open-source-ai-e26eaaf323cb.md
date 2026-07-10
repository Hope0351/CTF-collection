# :globe_with_meridians: Art Of Finding Zero Day Vulnerabilities Using Open Source Ai E26Eaaf323Cb

> **Original Source:** [Art Of Finding Zero Day Vulnerabilities Using Open Source Ai E26Eaaf323Cb](https://infosecwriteups.com/art-of-finding-zero-day-vulnerabilities-using-open-source-ai-e26eaaf323cb)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

In the above example! I entered go code snippet vulnerble to LDAP injection into CodeAstra Model as input and CodeAstra Model has identified vulnerabilty sucessfully


Observations and AnalysisCodeAstra-7B model was able to find common vulnerabilities such as SQL Injection , XSS etc easily compared to business logic vulnerabilities when I am prompting it using single shot prompting.


When I am using few shot prompts it tend to find vulnerability with more accuracy compared to single shot prompting


Note: In case if you are using GPT-4 or any LLM for finding vulnerabilities always use few shot prompting with examples for more accuracy


Comparing with Semgrep and other static analysis tools


Semgrep and other static analysis uses some rule based engines to detect the vulnerable patterns. They will be super fast in detection of common vulnerabilities which occurs known code patterns but it will not able to detect the timing based vulnerabilities , otp bypass kind of bussiness logic vulnerabilities. To find business logic vulnerabilities such as OTP bypass , privilege escalation , IDOR etc we need to understand the context of the code. So an AI model can easily understand this code and find business logic vulnerabilities but they will be slower compared to rule engine based static analysis tools


Why Opensource AI model when GPT4 do the code review better ?


most of companies have a policy which does not allow employees to send the sensitive information such as Source Code etc to third pary APIs of the companies hosting closed AI model unless they have some partnership with them such as OpenAI Enterprise Subscription where they don’t train the ML models with user data. In this case we need an Open Source AI model which can be deployed in the our environment which we control.


How to build an tool which can find vulnerabilities with more efficiency using static analysis tools and AI model.

---

*Originally published on [Medium](https://infosecwriteups.com/art-of-finding-zero-day-vulnerabilities-using-open-source-ai-e26eaaf323cb). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
