# :game_die: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/sans-offensive-ctf-taskist-01-04-56452aa43905)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# SANS Offensive CTF - Taskist:: 01–04


>

S**ummary:**


This Write Up outlines several vulnerabilities discovered within the application, including **IDOR** (Insecure Direct Object Reference), **privilege escalation**, **SSRF** (Server-Side Request Forgery), and **unauthorized file access issues**.


>

**Taskist::01- IDOR Vulnerability in “/api/tasks/<ID>”Description:** The application has an Insecure Direct Object Reference vulnerability in the ***/api/tasks/64*** endpoint, allowing unauthorized access to admin’s tasks information.


**Impact:** Admin notes containing confidential information, including the flag, are exposed to unauthorized users.


**Recommendation:** Implement proper access controls and authorization mechanisms to restrict access to sensitive data based on user roles and permissions.

>

**POC:**


1. Now after logging into the application you can see the source code (ctrl + u), observe the endpoints/paths.


2. After observing you can find the only endpoint which is potential to IDOR. Sending the request to Intruder along with the first 100 numbers as payloads and start the attack.


*Intruder*


*flag-1*

>

**Taskist::02: Privilege Escalation via Update Password FeatureDescription:** The application allows changing the ***user_id*** parameter to an admin user’s user_id during the update password feature, leading to unauthorized privilege escalation.


**Impact:** Unauthorized users can change the admin’s password, compromising the admin account’s security.


**Recommendation:** Implement strict validation checks to ensure that only authorized users can update passwords, and enforce proper authentication mechanisms to prevent privilege escalation attacks.

>

**POC:**


- Navigate to Password Reset Functionality, Intercept the request and observe that ***“user_id”*** is being passed. Change the ***“user_id” ***value to ***admin’s**user_id***


*admin-password*


*Flag-2*

>

**Taskist::03: SSRF Vulnerability leads to Unauthorized File Read AccessDescription:** By exploiting a vulnerability in the application’s handling of the ***proc/self/environ*** path. The main code ususally lies within ***app.js.***


You can see an attacker can gain unauthorized access to sensitive files, such as* /app/index.js***.


*flag-3*


**Impact:** Attackers can read sensitive application files containing configuration details or other critical information.


## Get Prasanth Bodepu’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


**Recommendation:** Implement proper input validation and sanitization to prevent directory traversal attacks, and restrict access to sensitive files to authorized users only.

>

**POC:**


1. After logging in as an admin, we can observe that there are **`site configuration`** settings along with import and export features.


2. Now by analyzing the source code of *`site_config.js`*, we can observe that the import feature is validating to variables not to be as ‘undefined’.


3. Now after exploring the export functionality we are able to download ***`site-config.json`***. When we look at the variables of the json file, the validating variables of import feature and export json file are the same for the first 2 variables. Here we can conclude that the vulnerability should be exploited over here.


4. By Uploading the dummy file and intercepting the request, replace the url with burp collaborator. We got a hit!, SSRF Confirmed.


5. We should look for sensitive information files which disclose the endpoints of the server function. By analyzing the tasks list in the admin dashboard we can say that 2 out 3 are pending. A Hint to the ***“/app”*** directory, which is not accomplished by admin.


6. Brute forcing with common LFI Payloads!??no, we should look for sensitive endpoints, some of sensitive endpoints are ***“/proc/*/*”***.


*flag — 3*

>

**Taskist::04: SSRF Vulnerability leads to chaining access to the root directory.Description:** The application’s file upload functionality is vulnerable to Server-Side Request Forgery (SSRF), allowing attackers to initiate requests to arbitrary URLs, including local files such as **‘*file:///*’**.


**Impact:** Attackers can exploit this vulnerability to read sensitive files on the server, such as ***/root/flag.txt***, leading to unauthorized disclosure of sensitive information.


**Recommendation:** Implement strict input validation and filtering mechanisms to prevent SSRF attacks, and restrict file upload functionality to trusted sources only.

>

*Note: The Taskist-4 should have been deployed at the user level to gain chain further to get flag{} at root level. Maybe it’s not a bug but a Feature Who Knows what kind of rabbit hole it might be misleading us with other things.*


**POC: (unintentional solution, by directly reading the root flag)**


1. Send a Request to ***“file:///etc/*”*** to know whether we are able to access the root files, after conclusion we are able to access the root directory files. Send request for ***“file:///root/flag.txt”***

*flag-4*


*Unintentional soltuion — Admin*

>

A**uthors:** [0xPb](https://twitter.com/_0xPb), [daniel1895](https://www.linkedin.com/in/danielthotapalli/)

---

*Originally published on [Medium](https://infosecwriteups.com/sans-offensive-ctf-taskist-01-04-56452aa43905). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
