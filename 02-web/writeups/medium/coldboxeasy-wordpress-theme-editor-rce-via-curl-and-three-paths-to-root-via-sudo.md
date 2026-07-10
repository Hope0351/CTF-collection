# :globe_with_meridians: XML-RPC server accepts POST requests only.

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
