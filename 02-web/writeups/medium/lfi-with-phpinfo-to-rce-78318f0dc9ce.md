# :globe_with_meridians: LFI WITH PHPINFO TO RCE. LFI vulnerabilities when testing PHP…

> **Original Source:** [LFI WITH PHPINFO TO RCE. LFI vulnerabilities when testing PHP…](https://infosecwriteups.com/lfi-with-phpinfo-to-rce-78318f0dc9ce)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

### Introduction


During assessments it is still common to find LFI vulnerabilities when testing PHP applications. Depending on the server configuration it is often possible to convert these into code execution primitives through known techniques such as;


- */proc/self/environ*

- */proc/self/fd/…*

- */var/log/…*

- */var/lib/php/session/ (PHP Sessions)*

- */tmp/ (PHP Sessions)*

- *php://input wrapper*

- *php://filter wrapper*

- *data: wrapper*


There is a paper where the author documents information related to how the PHP file upload feature works. In particular he notes that if file_uploads = on is set in the PHP configuration file, then PHP will accept a file upload post to any PHP file. He also notes that the upload file will be stored in the *tmp* location, until the requested PHP page is fully processed.


This is also included in the PHP documentation;

---

*Originally published on [Medium](https://infosecwriteups.com/lfi-with-phpinfo-to-rce-78318f0dc9ce). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
