# :locked_with_key: Known-Plaintext Attack on PHP-Proxy: From Broken Encryption to FastCGI RCE

> **Original Source:** [Known-Plaintext Attack on PHP-Proxy: From Broken Encryption to FastCGI RCE](https://infosecwriteups.com/known-plaintext-attack-on-php-proxy-from-broken-encryption-to-fastcgi-rce-4942523c7955)
> **Platform:** infosecwriteups.com | **Category:** `CRYPTO`

---

# Known-Plaintext Attack on PHP-Proxy: From Broken Encryption to FastCGI RCE


## How a Caesar cipher implementation turned URL encryption into a complete server compromise through known-plaintext attack and FastCGI protocol exploitation


## Introduction


I discovered [PHP-Proxy](https://www.php-proxy.com/) while researching web proxy implementations. The project caught my attention because, despite being abandoned by its developers, I noticed numerous active deployments still running in production environments. What started as a routine security assessment turned into an analysis of how a single cryptographic weakness could unravel an application’s entire security model.


This is the story of how I traced a path from weak encryption to complete server compromise.

## First Encounter with PHP-Proxy


I started by examining how PHP-Proxy handles user input. When a user submits a URL through the form interface, something interesting happens. The application doesn’t simply pass the URL through — it encrypts it and performs a redirect to `/?q=<ENCRYPTED_URL>`. This GET parameter contains the Base64-encoded ciphertext of the target URL.


My initial instinct was to test for SSRF by submitting `file:///etc/passwd`. But the application had a defense mechanism. The `add_http` function automatically prepends `http://` to any URL that doesn't already start with `https://` or `http://`. This function acts as a scheme enforcement layer.


When I submitted `file:///etc/passwd`, the function transformed it into `http://file:///etc/passwd`. The cURL library would interpret this as a malformed HTTP URL rather than a file protocol request. The SSRF attack failed before it began. I needed a different approach.


I continued mapping the application’s internals. The `proxify_url` function builds the redirect URL and initiates the proxying process. This function handles the encryption step before constructing the final redirect location.


After the form submission completes, the application enters its core logic — fetching the remote resource. The URL arrives at this stage already decrypted from the `q` parameter.


I discovered that the `forward` method in the `Proxy` class uses cURL internally to perform requests. The implementation relies on PHP's `curl_exec()` function with `CURLOPT_URL` set to the user-supplied value.


At this point, I had mapped the complete request flow. No URL filtering existed anywhere in the chain. The application never validates the URL scheme, hostname, or port. cURL supports multiple protocols beyond HTTP/HTTPS by default, including `file://` for local filesystem access, `gopher://` for raw TCP socket communication, `dict://` for dictionary server queries, and `ftp://` for file transfers. The application would happily process these dangerous protocols—if only I could bypass the `add_http` function.


*Two request paths in PHP-Proxy: protected form submission vs vulnerable direct encrypted parameter that bypasses URL scheme validation*


The solution became clear: I needed to submit my payload directly to `/?q=` with a properly encrypted value. To do that, I had to break the encryption.

## Breaking the Cryptography


I examined how PHP-Proxy handles encryption. The encryption key comes from `Config::get("encryption_key")`, which is loaded during application initialization.


The `encryption_key` is set to `md5(app_key + URL_MODE)`, producing a 32-character hexadecimal string (128 bits). The `app_key` is generated using `openssl_random_pseudo_bytes(100)`, which should produce 100 bytes of cryptographically strong random data from the operating system's random number generator.


But then I saw something that changed everything. The encryption algorithm was Caesar cipher, implemented through the `str_rot_pass()` function.


Caesar cipher. A monoalphabetic substitution cipher from ancient Rome. An algorithm that performs character-by-character rotation based on a key. The `str_rot_pass()` implementation uses the MD5 hash as a rotation key, applying different rotation values to each character position based on the corresponding byte in the key.


I had stumbled onto a critical weakness. The developers had generated a strong random key using `openssl_random_pseudo_bytes`, only to use it with an encryption algorithm that provides no semantic security, no confusion, and no diffusion—the fundamental properties required of modern ciphers. Caesar cipher variants are vulnerable to frequency analysis, known-plaintext attacks, and chosen-plaintext attacks. The rotation-based substitution preserves patterns in the plaintext, making cryptanalysis straightforward.


I chose the known-plaintext approach. The attack works because Caesar cipher has a fundamental property: if you know both the plaintext P and ciphertext C, you can derive the key K directly. In a proper encryption scheme like AES-256-GCM, knowing plaintext-ciphertext pairs provides no information about the key. Caesar cipher has no such protection.


I submitted a URL through the normal form interface — `https://example.com`—and captured the encrypted result from the redirect. The encrypted value appeared in the `Location` header as the `q` parameter. Now I had both the plaintext and its corresponding ciphertext.


Using the `str_rot_pass` function with `$str=ENCRYPTED_URL` and `key=KNOWN_URL`, I reversed the rotation operation. The function applies the inverse rotation to each character, effectively running the cipher backward. Because Caesar cipher is symmetric in this implementation, the same function that encrypts also decrypts when you swap the plaintext and ciphertext positions.


```
$ php exploit.php
KEY : c96442dc36b61ebce28b02c537b9ad7c
```


*Known-plaintext attack sequence on Caesar cipher implementation. The attacker submits a known URL, captures its encrypted form, reverses the rotation algorithm to recover the encryption key, then uses that key to encrypt and submit SSRF payloads*


The key fell out in seconds. The 128-bit MD5 hash that should have provided 2¹²⁸ possible keys was recovered with a single known plaintext-ciphertext pair. I now had everything I needed to craft arbitrary encrypted payloads.

## Exploiting SSRF


With the encryption key in hand, I could bypass the `add_http` function entirely. I would encrypt my malicious URLs directly using the recovered key and submit them to `/?q=`, avoiding the form submission path completely.


*Complete attack chain from Caesar cipher key recovery to RCE: file disclosure via SSRF confirms vulnerability, FastCGI exploitation via gopher:// achieves code execution*

## Reading Local Files


I started with local file disclosure. The `file://` URI scheme allows accessing the local filesystem through cURL when `CURLOPT_PROTOCOLS` is not restricted. I encrypted `file:///etc/passwd` using the recovered key, applying the same `str_rot_pass()` function with the key I had extracted.


## Get Muh. Fani Akbar’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The encrypted payload went directly to the `q` parameter. The application decrypted it, extracted `file:///etc/passwd`, and passed it to cURL's `curl_setopt()` with `CURLOPT_URL`. cURL opened the file and returned its contents as if it were an HTTP response body:


```
❯ php exploit.php read '/etc/passwd'
KEY : c96442dc36b61ebce28b02c537b9ad7c
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
bin:x:2:2:bin:/bin:/usr/sbin/nologin
sys:x:3:3:sys:/dev:/usr/sbin/nologin
sync:x:4:65534:sync:/bin:/bin/sync
games:x:5:60:games:/usr/games:/usr/sbin/nologin
man:x:6:12:man:/var/cache/man:/usr/sbin/nologin
lp:x:7:7:lp:/var/spool/lpd:/usr/sbin/nologin
mail:x:8:8:mail:/var/mail:/usr/sbin/nologin
news:x:9:9:news:/var/spool/news:/usr/sbin/nologin
uucp:x:10:10:uucp:/var/spool/uucp:/usr/sbin/nologin
proxy:x:13:13:proxy:/bin:/usr/sbin/nologin
www-data:x:33:33:www-data:/var/www:/usr/sbin/nologin
```


The application returned the file contents without question. No access controls. No validation. The server’s filesystem was now readable through the proxy interface.

## Achieving Remote Code Execution


I wanted to push further. Reading files was useful, but I needed to demonstrate the full impact. I turned my attention to FastCGI.


FastCGI is a binary protocol that web servers use to communicate with application servers like PHP-FPM. The protocol operates over TCP sockets or Unix domain sockets. When FastCGI runs on a TCP socket — commonly port 9000 — instead of a Unix domain socket, it becomes accessible through SSRF attacks.


The `gopher://` protocol in cURL allows sending arbitrary TCP data to any host and port. By crafting a valid FastCGI binary packet, I could send commands directly to PHP-FPM through the SSRF vulnerability.


A FastCGI request consists of several record types:


- `FCGI_BEGIN_REQUEST` (type 1): Initiates a new request

- `FCGI_PARAMS` (type 4): Sends CGI environment variables as key-value pairs

- `FCGI_STDIN` (type 5): Sends the request body


The key to code execution lies in the `FCGI_PARAMS` variables. By setting `PHP_VALUE` to `auto_prepend_file = php://input` and sending PHP code in `FCGI_STDIN`, I could force PHP-FPM to execute arbitrary code.


I built a FastCGI request packet that would execute the `id` command. The packet structure included:


- Version: 1

- Type: FCGI_BEGIN_REQUEST

- Request ID: 1

- Role: FCGI_RESPONDER

- Flags: FCGI_KEEP_CONN


Then I added FCGI_PARAMS records containing:


- `SCRIPT_FILENAME=/var/www/html/index.php`

- `PHP_VALUE=auto_prepend_file = php://input`

- `REQUEST_METHOD=POST`


Finally, I sent the PHP payload `<?php system('id'); ?>` in an FCGI_STDIN record.


I encoded this entire binary payload as a gopher URL: `gopher://127.0.0.1:9000/_[binary_data]`, encrypted it with the recovered key, and submitted it:


```
❯ php exploit.php fastcgi 'id'
uid=33(www-data) gid=33(www-data) groups=33(www-data)
```


The command executed. cURL connected to localhost:9000, sent the FastCGI packet to PHP-FPM, and PHP-FPM executed the system command. I had achieved remote code execution with the privileges of the web server user (www-data).

## What I Learned


This analysis revealed how a single cryptographic mistake can compromise an entire application. The developers used `openssl_random_pseudo_bytes` to generate a strong 100-byte random seed, hashed it with MD5 to produce a 128-bit key, but paired it with Caesar cipher—a substitution cipher that offers no protection against known-plaintext attacks. The strong key generation gave a false sense of security while the weak cipher left the door wide open.


The vulnerability exists because Caesar cipher lacks fundamental cryptographic properties:


- No semantic security: Knowing plaintext-ciphertext pairs reveals the key

- No confusion: The relationship between key, plaintext, and ciphertext is linear

- No diffusion: Each plaintext character affects only one ciphertext character

- Deterministic encryption: Same plaintext always produces the same ciphertext


A proper implementation would use authenticated encryption like AES-256-GCM with a random IV for each encryption operation. This would prevent key recovery even with millions of known plaintext-ciphertext pairs.


The attack chain was straightforward: recover the encryption key through known-plaintext attack on Caesar cipher, encrypt SSRF payloads using the recovered key, read local files via `file://` protocol, and execute arbitrary code through FastCGI protocol exploitation via `gopher://`. Each step built on the previous one, enabled by the cryptographic weakness at the foundation.


Organizations still running PHP-Proxy should migrate to maintained alternatives that implement proper cryptographic controls and input validation. The combination of abandoned software and weak cryptography creates conditions where exploitation becomes not just possible, but trivial.

---

*Originally published on [Medium](https://infosecwriteups.com/known-plaintext-attack-on-php-proxy-from-broken-encryption-to-fastcgi-rce-4942523c7955). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
