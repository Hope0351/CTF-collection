# :globe_with_meridians: How to leverage LFI to achieve RCE - OSCP Tactics for Code Execution and Gaining a Foothold on a System

> **Original Source:** [How to leverage LFI to achieve RCE - OSCP Tactics for Code Execution and Gaining a Foothold on a System](https://infosecwriteups.com/rce-via-lfi-oscp-tactics-for-code-execution-and-gaining-a-foothold-on-a-system-b35d0655f3c7)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# How to leverage LFI to achieve RCE — OSCP Tactics for Code Execution and Gaining a Foothold on a System


PEN200 PWK Web Tactics


🔥 FREE VERSION — Click here for Free Article 🔥


Today going through the OffSec course material, I decided I would share a simple way to gain remote code execution via Local File Inclusion or LFI from the web application to the host.


I’ll use a simple example of a PHP web application, where we have located an LFI vulnerability which allows us to interact with files on the host.


A common misconception is that Local File Inclusion or LFI is the same as Path or Directory Traversal. The difference, is that when you’re able to access a file via path traversal, it typically just reads the file and displays it’s contents such as accessing the /etc/passwd file. LFI will actually run the file in question. So if you’re trying to get a reverse shell, you can’t actually achieve that with path traversal, but you definitely can using LFI techniques.


Let’s take a look at an example where we’ve located an LFI vulnerability within the index.php?page= parameter on a wordpress site. Leveraging this exploit, we can access the /etc/passwd file:


*Reading the /etc/passwd file*


A classic proof of concept is to read the /etc/passwd file, which you can see in the screenshot…

---

*Originally published on [Medium](https://infosecwriteups.com/rce-via-lfi-oscp-tactics-for-code-execution-and-gaining-a-foothold-on-a-system-b35d0655f3c7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
