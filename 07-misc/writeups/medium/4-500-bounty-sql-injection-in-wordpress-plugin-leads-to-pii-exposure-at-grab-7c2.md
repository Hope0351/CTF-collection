# :game_die: $4,500 Bounty: SQL Injection in WordPress Plugin Leads to PII Exposure at Grab

> **Original Source:** [$4,500 Bounty: SQL Injection in WordPress Plugin Leads to PII Exposure at Grab](https://infosecwriteups.com/4-500-bounty-sql-injection-in-wordpress-plugin-leads-to-pii-exposure-at-grab-7c26aa7beff6)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# $4,500 Bounty: SQL Injection in WordPress Plugin Leads to PII Exposure at Grab


## How a Plugin Preview Feature Exposed User Data and Nearly Enabled Admin Dashboard Pivoting


In a bug report that earned a $4,500 bounty from Grab security researcher jouko uncovered a critical SQL Injection vulnerability in the Formidable Pro WordPress plugin used on [www.drivegrab.com](http://www.drivegrab.com). This flaw gave unauthorized users read access to the WordPress database revealing sensitive partner data and nearly opened a path to Remote Code Execution (RCE).

### Vulnerability Overview


The plugin’s AJAX preview function meant for administrators designing forms was mistakenly exposed to unauthenticated users. It accepted parameters like after_html that could include WordPress shortcodes including the plugin’s [display-frm-data] which could be manipulated to perform SQL Injection through parameters like order_by and order.

### Proof of Concept (PoC)


Using cURL, the researcher was able to demonstrate:


```
curl -s -i 'https://www.drivegrab.com/wp-admin/admin-ajax.php' \
--data 'action=frm_forms_preview&after_html=XXX[display-frm-data id=835 order_by=id limit=1 order=zzz]YYY'
```


This allowed the attacker to inject payloads into SQL queries specifically in the ORDER BY clause which manipulated the ordering of database entries a bit-by-bit data exfiltration channel.


To go further the researcher used a customized sqlmap payload that bypassed the plugin’s shortcode parsing quirks and retrieved data from the WordPress database.

### What Was Exposed?


During Grab’s internal investigation, it was confirmed that about 0.6% of partner PII data was exposed due to this vulnerability. This included names and personal details of driver partners.

### Near Pivot to Admin Access?


The researcher also discovered that the iThemes-Sync authentication key was stored in plaintext in the WordPress database, theoretically enabling Remote Code Execution via admin dashboard access.


## Get Monika sharma’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


However due to server hardening and iThemes’ use of per-site random salts the hash validation step failed:

>

The hash could not be validated as a correct hash.


Thus RCE could not be confirmed but the attempt showcased the high potential impact of the vulnerability chain.

### Credit


- Hunter: [jouko](https://hackerone.com/jouko)

- Bounty: $4,500

- Report ID: #273946

### Key Takeaways


- Preview endpoints and plugin shortcodes can be high-risk entry points.

- Always treat unauthenticated endpoints accepting rich parameters (HTML, shortcodes, JSON, etc.) as potential injection targets.

- Combining plugin behavior quirks, sqlmap tampering and deep analysis can uncover serious vulnerabilities.

- Even when RCE is not achieved impact based bounty programs may still reward significantly.

### Tools & Techniques Used


sqlmap with:


- — param-del

- — eval

- — tamper=commalesslimit


Custom payload crafting to bypass shortcode parsing logic

### How to Find This Vulnerability


This vulnerability was hiding in plain sight. Here’s a practical process to discover such issues:


- Identify Plugins Used on the Target


- Use tools like WPScan, BuiltWith or WhatRuns to identify installed WordPress plugins.

- Alternatively, check browser DevTools or source code for hints (/wp-content/plugins/).


2. Locate AJAX Endpoints


- WordPress plugins often expose functionality via AJAX calls at:


```
/wp-admin/admin-ajax.php
```


- Bruteforce or observe common parameters like action=:


```
curl -X POST https://target.com/wp-admin/admin-ajax.php \
-d 'action=some_plugin_action'
```


3. Analyze Shortcodes and Parameters


- Look for features that let users insert content like HTML or shortcodes. These often allow dynamic plugin functionality, which is a hotspot for injections.

- Test shortcode-related features (e.g., [display-frm-data]) with unusual or malformed inputs.


4. Fuzz for SQLi


- Inject special characters in shortcode parameters like order_by, order, id, etc.


```
curl -X POST https://target.com/wp-admin/admin-ajax.php \
-d 'action=frm_forms_preview&after_html=[display-frm-data id=1 order=zzz]'
```


- Check for errors, anomalies or backend crashes in the response.


5. Use SQLMap (with Modifications)


- If the injection is tricky due to syntax, shortcode parsing or plugin logic use tamper scripts and custom eval functions:


```
sqlmap -u 'https://target.com/wp-admin/admin-ajax.php' \
--data 'action=frm_forms_preview&after_html=[display-frm-data id=1 order="%2a(true=true)"]' \
--param-del ' ' -p true --technique B \
--tamper=commalesslimit \
--eval='true=true.replace(",",",-it.id%2b")' \
--string 'expected_string'
```


6. Chain with Other Discovered Secrets


- Look inside exposed databases for credentials, auth tokens or plugin keys like iThemes-Sync.

- Consider pivoting opportunities like using these keys for RCE or privilege escalation.

### Final Thoughts


This case shows the real world risk of poorly implemented plugins and how a creative researcher can turn obscure shortcode behavior into a powerful attack vector. Grab’s decision to award a fair bounty despite the partial nature of the exploit reflects the value of transparent bug bounty programs that focus on impact, not just exploitation.

>

Thank you ✨

---

*Originally published on [Medium](https://infosecwriteups.com/4-500-bounty-sql-injection-in-wordpress-plugin-leads-to-pii-exposure-at-grab-7c26aa7beff6). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
