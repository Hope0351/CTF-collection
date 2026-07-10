# :globe_with_meridians: #4 RFI: From an External URL Into your Application

---

# #4 RFI: From an External URL Into your Application

Understanding RFI isn’t just about finding a bug; it’s about recognizing a critical design flaw that, if exploited, hands an attacker the keys to your server. Let’s explore what RFI is, how to confirm its presence, and the devastating impact it can have.

## What is Remote File Inclusion (RFI)?

Remote File Inclusion (RFI) occurs when a web application allows a user to specify a remote URL as input, and the application’s underlying code (like PHP’s `include()` or `require()`) then fetches and executes the content of that URL.

Imagine your application is supposed to load a template file. With RFI, instead of loading `header.php` from its own server, it's tricked into loading `http://attacker.com/malicious_shell.php`. If the server is configured to execute included files, your attacker's code runs with the privileges of your web server.

FriendLink🔗

### RFI vs. LFI: The Key Differences

- LFI: Allows including files that are already on the server’s local file system. This often requires directory traversal (`../../`) and relies on finding or uploading malicious content locally (e.g., log poisoning, file upload).

- RFI: Allows including files from any remote URL(e.g., `http://`, `ftp://`)…

---
