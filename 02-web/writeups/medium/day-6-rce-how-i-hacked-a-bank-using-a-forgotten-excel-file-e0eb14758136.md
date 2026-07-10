# :globe_with_meridians: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/day-6-rce-how-i-hacked-a-bank-using-a-forgotten-excel-file-e0eb14758136)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# “Day 6: RCE — How I Hacked a Bank Using a Forgotten Excel File”


I was testing a banking portal when I stumbled upon an “Export to Excel” feature. What looked harmless turned into a full Remote Code Execution (RCE) chain that gave me root access to their internal servers. The bank paid me $200 for this critical find. Today, I’ll break down exactly how I did it, with real code snippets you can test yourself.


[free link](https://amannsharmaa.medium.com/day-6-rce-how-i-hacked-a-bank-using-a-forgotten-excel-file-e0eb14758136?sk=63a93e5a1177fdc8f2cb66383445a0bf)


## The Forgotten Attack Vector: Malicious Document Generators


Most hackers focus on web inputs. The real goldmine? Document processing (Excel, PDF, Word).

### How the Bank’s System Worked:


- Users could export transaction logs to Excel.

- The server used an old Apache POI library (CVE-2021–27568) to generate files.

- No sandboxing — the parser ran with full system privileges.

## Step-by-Step Exploit (From Excel to Shell)


### Step 1: Found the Vulnerable Endpoint


Intercepted a request with Burp:


```
POST /export_transactions
{ "format": "xlsx", "data": [/* transaction data */] }
```


### Step 2: Crafted a Malicious Excel…

---

*Originally published on [Medium](https://infosecwriteups.com/day-6-rce-how-i-hacked-a-bank-using-a-forgotten-excel-file-e0eb14758136). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
