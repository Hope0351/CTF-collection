# :globe_with_meridians: When Reading The Source Code Is The Real Hack A Web Challenge Story V1T Ctf B6Ad

---

## What This Challenge Taught Me

### 1. Client-Side Security Is Not Security

Storing credentials (even hashed ones) in client-side JavaScript is a massive security flaw. Anyone can view the source code and extract sensitive information. This challenge is a perfect example of what *not* to do in real-world applications.

Real-world lesson: Always validate and authenticate on the server-side, never trust the client.

### 2. Reading > Tools (Sometimes)

I could’ve gone straight to automated tools, but taking 2 minutes to read and understand the code saved me time and gave me the exact information I needed. In CTFs and real pentesting, understanding the logic is often more valuable than throwing tools at the problem.

### 3. Rainbow Tables Are Your Friend

Services like CrackStation maintain massive databases of pre-computed hashes. For common passwords, they’re instant. For CTF challenges, they’re often all you need.

## Get Chetan Chinchulkar’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

When to use what:

- CrackStation/Online databases — First try for common hashes

- Hashcat — When you need custom wordlists or rules

- John the Ripper — Alternative to Hashcat, great for various hash types

### 4. Default Credentials Are Still Worth Trying

Even though they didn’t work here, checking default credentials takes 30 seconds and works surprisingly often. Never skip the basics!

---
