# :globe_with_meridians: Reflected XSS Leads to 3,000$ Bug Bounty Rewards from Microsoft Forms

---

## Introduction

In this blog post, I will discuss the details of a reflected cross-site scripting (XSS) vulnerability in Microsoft Forms.

Additionally, in my last blog post, I disclosed a vulnerability report on Microsoft Power Apps and dove into the processes of reporting. You can refer to my previous post on: Microsoft bug reports lead to ranking on Microsoft MSRC Quarterly Leaderboard (Q3 2022)for more detailed information on the process of reporting and claiming rewards through MSRC platform.

## Background

>

Microsoft Forms is a popular web-based tool for creating surveys, quizzes, and other forms. It allows users to create forms and surveys, share them with others, and collect responses in a centralized location. However, we discovered that it is possible to inject malicious JavaScript code into the forms, which can be executed by unsuspecting users.

I followed the MSRC’s guidelines for reporting vulnerabilities and submitted my findings. For more information, please refer to:

## Details of the Vulnerability:

The vulnerability lies in the way Microsoft Forms processes user input. Specifically, it fails to properly validate user input, allowing an attacker to inject malicious JavaScript code into the id parameter. An attacker can generate a malicious link with injected XSS Payload, they can take advantage of this vulnerability to take over authenticated accounts or perform state-changing actions with authenticated users’ sessions in the application, or even use a vulnerable domain to make a phishing page and etc.

Vulnerable product: `Microsoft Forms`

Vulnerable URL: `https://forms.office.com/pages/responsepage.aspx`

## Get Supakiad S. (m3ez)’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Vulnerable Parameter: `id`

>

Reflected XSS (Cross-Site Scripting) is a type of web vulnerability that allows an attacker to inject malicious code into a website, which is then executed by the victim’s browser. This happens when the website includes untrusted user input in its pages without proper validation or encoding. The attacker crafts a special link or form that, when clicked or submitted by the victim, causes the victim’s browser to execute the malicious code. The victim’s browser is tricked into thinking the code is part of the website, allowing the attacker to steal sensitive information or perform other malicious actions

## Exploitation:

To exploit this vulnerability, an attacker would need to craft a specially-crafted link that contains the malicious JavaScript code. The attacker would then need to trick the user into clicking on the link, which would cause the code to be executed. This could be done through social engineering tactics, such as phishing emails or instant messaging.

### Proof of Concept:

Here is an example of a proof of concept that demonstrates the vulnerability:

1. Navigated to URL:

```
https://forms.office.com/Pages/ResponsePage.aspx
```

2. Injected XSS payload into `id` parameter value and added to a vulnerable URL from step 1.

The payload was used:

```
d1bvs%3c%2fscript%3e%3cscript%3ealert(`XSS`)%3c%2fscript%3ec579g
```

Example injected Link:

```
https://forms.office.com/pages/responsepage.aspx?id=d1bvs%3c%2fscript%3e%3cscript%3ealert(`XSS`)%3c%2fscript%3ec579g
```

3. Open the URL in step 2.

4. When users open the XSS inject link, the XSS payload will be triggered and executed as shown below.

---
