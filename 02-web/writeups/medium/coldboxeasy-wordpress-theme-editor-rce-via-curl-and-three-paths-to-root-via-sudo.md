# :globe_with_meridians: XML-RPC server accepts POST requests only.

> **Original Source:** [XML-RPC server accepts POST requests only.](https://infosecwriteups.com/coldboxeasy-wordpress-theme-editor-rce-via-curl-and-three-paths-to-root-via-sudo-offsec-pg-71bde0374470)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## 1.2 Web Enumeration — curl & Gobuster


Confirm the WordPress install via curl:


```
curl -s http://<TARGET_IP>
```


Page source confirms the site title “ColddBox” and a WordPress generator meta tag. Run Gobuster to map out what else is there:


```
gobuster dir -u http://<TARGET_IP>/ -w /usr/share/dirb/wordlists/common.txt
```


Gobuster Results:


Path Status Notes `/hidden/` 301 Custom page — lore hint `/wp-admin/` 301 WordPress admin panel `xmlrpc.php` 200 XML-RPC enabled `/wp-content/` 301 — `/wp-includes/` 301 —


Hit the interesting ones:


```
curl http://<TARGET_IP>/xmlrpc.php
# XML-RPC server accepts POST requests only.
```


```
curl http://<TARGET_IP>/hidden/
```


`/hidden/` drops this message:

>

“Coldd, you changed Hugo’s password, when you can send it to him so he can continue uploading his articles. Philip”


That tells you exactly who the users are — c0ldd, hugo, and philip — and hints that credentials are being shuffled around carelessly. Password reuse is almost guaranteed.

---

*Originally published on [Medium](https://infosecwriteups.com/coldboxeasy-wordpress-theme-editor-rce-via-curl-and-three-paths-to-root-via-sudo-offsec-pg-71bde0374470). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
