# :game_die: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/episode-2-os-command-injection-talking-directly-to-the-servers-brain-7fdb828aaae3)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Episode 2: OS Command Injection — Talking Directly to the Server’s Brain


Command Injection is a type of security flaw where a program accidentally lets an attacker run system commands. In simple terms, it happens when user input goes into an operating system command without proper checks. For example, a web form might take a filename and run`cat <filename>`, but a hacker could enter `file.txt; rm -rf /` instead.


This makes the server execute both `cat file.txt` and the dangerous `rm -rf /` command. In other words, the application “injects” extra commands into the shell. OWASP explains that command injection means the attacker achieves


**“execution of arbitrary commands on the host operating system via a vulnerable application”.**


Any site or app that passes user data to the system shell is at risk – this includes web forms, APIs, and even command-line interfaces that include user input in OS calls.


Command injection is very dangerous. Because the injected commands run with the application’s privileges, an attacker can **take control of the server**.


They might upload malware, add new users, or steal configuration files. For example, as OWASP notes, an attacker who can execute OS commands might ***“upload malicious programs or even obtain passwords”*** from the server.

---

*Originally published on [Medium](https://infosecwriteups.com/episode-2-os-command-injection-talking-directly-to-the-servers-brain-7fdb828aaae3). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
