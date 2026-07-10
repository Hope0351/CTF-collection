# :globe_with_meridians: “Beyond the Obvious: How a Dead-End XXE Led to a Critical SQLi Goldmine”

> **Original Source:** [“Beyond the Obvious: How a Dead-End XXE Led to a Critical SQLi Goldmine”](https://infosecwriteups.com/beyond-the-obvious-how-a-dead-end-xxe-led-to-a-critical-sqli-goldmine-d368f5ddaadc)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# “Beyond the Obvious: How a Dead-End XXE Led to a Critical SQLi Goldmine”


## From a frustrating file upload to a database of a million records, the path to a critical bug is rarely a straight line.


We’ve all been there. You find an endpoint that makes your hacker senses tingle. A file upload form. Your mind races with possibilities — PHP shells, malicious PDFs, the works. You fire up Burp Suite, eager to claim your bounty, only to hit a wall. The error messages are clear: it’s not a file upload. It’s something else entirely.


[FREE LINK](https://amannsharmaa.medium.com/beyond-the-obvious-how-a-dead-end-xxe-led-to-a-critical-sqli-goldmine-d368f5ddaadc?sk=6895345c5774605c7f272320121bf25e)


This is the story of one such target. It’s a masterclass in persistence, adaptability, and why you should never, ever delete a tab in Burp.

### The First Look: A Promising Door That Slammed Shut


My journey started like many others: with subdomain enumeration. Amass, Subfinder, the usual tools. One subdomain stood out: `invoices.corp-target.com`. It hosted a single, sleek HTML form for uploading files. Jackpot, right?


I started with the classic tests. Uploading a `shell.php`. The server responded, not with a generic error, but with a verbose one: "Error: File processed as XML. Root element is missing."

---

*Originally published on [Medium](https://infosecwriteups.com/beyond-the-obvious-how-a-dead-end-xxe-led-to-a-critical-sqli-goldmine-d368f5ddaadc). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
