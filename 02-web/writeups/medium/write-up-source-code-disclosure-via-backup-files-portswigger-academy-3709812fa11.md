# :globe_with_meridians: Write-up: Source code disclosure via backup files @ PortSwigger Academy

> **Original Source:** [Write-up: Source code disclosure via backup files @ PortSwigger Academy](https://infosecwriteups.com/write-up-source-code-disclosure-via-backup-files-portswigger-academy-3709812fa111)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Write-up: Source code disclosure via backup files @ PortSwigger Academy


This write-up for the lab *Source code disclosure via backup files* is part of my walkthrough series for [PortSwigger’s Web Security Academy](https://portswigger.net/web-security).


Learning path: Server-side topics → Information disclosure


Python script: [script.py](https://github.com/frank-leitner/portswigger-websecurity-academy/blob/main/06_information_disclosure/Source_code_disclosure_via_backup_files/script.py)

## Lab description


## Steps


When analyzing a web page, one of the first steps is always to check for the existence of a `robots.txt` file.


It is a file that requests search engine crawlers to either include or exclude certain parts of the site from their index. Sometimes, interesting locations are revealed that way.


## Get Frank Leitner’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


It is up to the crawler whether they obey these wishes or ignore them. As the file is plain text, the same applies to any human reading it.


In this case, it points straight to the subdirectory `/backup` (other means to discover it would be tools like Burp Content Discovery, gobuster, wfuzz, ...)


Checking the directory shows a backup file for some Java code:


In the code, the credentials for the database connections can be found:


After submitting the solution time, the lab updates to


---

*Originally published on [Medium](https://infosecwriteups.com/write-up-source-code-disclosure-via-backup-files-portswigger-academy-3709812fa111). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
