# :globe_with_meridians: Bypassing File Upload Restrictions to Achieve XSS in a Crypto Application

> **Original Source:** [Bypassing File Upload Restrictions to Achieve XSS in a Crypto Application](https://infosecwriteups.com/bypassing-file-upload-restrictions-to-achieve-xss-in-a-crypto-application-3319e8b527e1)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Bypassing File Upload Restrictions to Achieve XSS in a Crypto Application


*Image by Pixashow*


During a routine internal security assessment of a crypto-based web application within our company, I encountered a file upload functionality that, at first glance, seemed well-restricted. The user interface was designed to only accept image files such as .png, .jpg, and .jpeg formats, and it clearly blocked files like .pdf, .docx, .exe, and other potentially malicious formats.


However, upon deeper inspection and testing, I discovered a vulnerability that allowed me to upload a crafted .html file containing a cross-site scripting (XSS) payload, which successfully executed in a browser. This blog details the complete methodology, technical steps, and mitigation recommendations from this internal penetration test.


The scope of the assessment was an internal web-based platform related to a cryptocurrency product. The application included functionalities such as user registration, profile management, wallet integration, and image uploads. My task was to test for common web vulnerabilities, focusing specifically on file upload components.


Initial Observation: Validated Upload Field


The image upload field was located within the user profile section. On the frontend, the form only allowed files with .jpg, .jpeg, or .png extensions. The upload field…

---

*Originally published on [Medium](https://infosecwriteups.com/bypassing-file-upload-restrictions-to-achieve-xss-in-a-crypto-application-3319e8b527e1). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
