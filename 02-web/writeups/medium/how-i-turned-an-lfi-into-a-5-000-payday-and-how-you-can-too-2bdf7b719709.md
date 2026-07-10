# :globe_with_meridians: “How I Turned an LFI into a $5,000 Payday (And How You Can Too)”

---

# “How I Turned an LFI into a $5,000 Payday (And How You Can Too)”

Hey, I’m Aman Sharma, a cybersecurity enthusiast always hunting for real-world exploits. After reading about LFI vulnerabilities, I decided to test my skills — and ended up finding a critical flaw that earned me a sweet bounty. Here’s my no-fluff guide to finding and exploiting LFI like a pro.

free link

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
