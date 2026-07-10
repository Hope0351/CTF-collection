# :game_die: Breaking down — Command Injections

> **Original Source:** [Breaking down — Command Injections](https://infosecwriteups.com/breaking-down-command-injections-97d1029576)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Breaking down — Command Injections


Command Injection or OS Command Injection is a category of injection vulnerabilities, where an attacker is able to exploit an unsanitized user input further to run default OS commands in the server.

>

Code Injection: allows the attacker to add their own code that is then executed by the application.


Command Injection: the attacker extends the default functionality of the application, which executes system commands, without injecting code.


### What actually is a Command Injection attack - according to OWASP?


Command injection is an attack in which the goal is the execution of arbitrary commands on the host operating system via a vulnerable application. Command injection attacks are possible when an application passes unsafe user-supplied data (forms, cookies, HTTP headers, etc.) to a system shell. In this attack, the attacker-supplied operating system commands are usually executed with the privileges of the vulnerable application. Command injection attacks are possible largely due to insufficient input validation.

### Identifying CIs in Application Source-Code: OWASP


- In PHP based applications: Vulnerable Code


```
<?php
print("Specify the file to delete");
print("<p>")…
```

---

*Originally published on [Medium](https://infosecwriteups.com/breaking-down-command-injections-97d1029576). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
