# 📖 Glossary — CTF Jargon Reference

> Part of **CTF-collection** — see [`99-appendix/full-repo-index.md`](full-repo-index.md) for the corpus.

A reference for common CTF jargon. Organized alphabetically.

## A

- **AD (Attack-Defense)** — A CTF format where each team runs identical services and scores points by attacking other teams' services while defending their own. DEF CON CTF Finals is the canonical example.
- **Angstrom CTF** — A well-established CTF organized by the Angstrom team at Carnegie Mellon University West.
- **angr** — A Python-based symbolic execution framework commonly used for reverse engineering and pwn challenges.
- **APK** — Android Package. The archive format for Android apps; commonly reverse-engineered in mobile CTF challenges.
- **Aperi'Solve** — An online steganography solver that runs multiple tools automatically.

## B

- **Block cipher** — A symmetric encryption algorithm that operates on fixed-size blocks of data. AES is the dominant example.
- **Blockchain CTF** — CTF category focused on smart contract exploitation. Includes reentrancy, integer overflow, access control flaws, and flash loan attacks.
- **Burp Suite** — The dominant web proxy tool for web exploitation challenges.

## C

- **Canary (stack canary)** — A value placed on the stack between local variables and the return address to detect stack buffer overflows. Bypassing canaries is a common pwn challenge.
- **Capture The Flag (CTF)** — A security competition where participants solve challenges to find hidden "flags".
- **CBC (Cipher Block Chaining)** — A block cipher mode vulnerable to padding oracle attacks.
- **checksec** — A tool that checks binary security mitigations (NX, PIE, RELRO, stack canary, FORTIFY).
- **corCTF** — A top-tier CTF organized by Crusaders-of-Rust.
- **CryptoHack** — A free, comprehensive crypto CTF learning platform.
- **CSAW CTF** — A long-running CTF organized by osirislab at NYU.

## D

- **DEF CON CTF** — The world's longest-running and most-prestigious CTF. Organized by Nautilus Institute since 2024 (DEF CON 32).
- **DeFi** — Decentralized Finance. Smart-contract-based financial protocols; common target in blockchain CTFs.
- **DEF CON CTF Quals** — The qualifier for DEF CON CTF Finals.
- **DiceCTF** — A top-tier CTF organized by dicegang.
- **DLL injection** — Injecting code into a process by loading a DLL. Common in Windows exploitation.

## E

- **ECB (Electronic Codebook)** — A block cipher mode that produces identical ciphertext for identical plaintext blocks. Vulnerable to block-reordering attacks.
- **ECDSA** — Elliptic Curve Digital Signature Algorithm. Used in Ethereum and many other systems.
- **Ethernaut** — OpenZeppelin's progressively harder smart-contract CTF; the canonical entry point for Solidity exploitation.
- **Exploit development** — The process of constructing a working exploit for a vulnerability.

## F

- **Flag** — The target string in a CTF challenge, typically of the form `flag{...}` or `picoCTF{...}`.
- **Format String Vulnerability** — A class of bug arising from improper use of printf-family functions (printf, sprintf, fprintf) with user-controlled format strings. Exploitable for arbitrary memory read/write, often leading to code execution.
- **Forensics** — CTF category involving disk images, memory dumps, packet captures, and steganography.
- **Foundry** — A Rust-based exploit development framework for blockchain CTFs; has displaced Hardhat since 2022.
- **Frida** — A dynamic instrumentation framework; dominant for mobile RE.

## G

- **Ghidra** — NSA's free reverse-engineering suite. The dominant free RE tool.
- **gdb-gef** — GDB Enhanced Features. The dominant GDB frontend for CTF.
- **Google CTF** — Google's annual CTF, run since 2017.

## H

- **Hardhat** — A TypeScript-based exploit development framework for blockchain CTFs. Older than Foundry.
- **Hardware CTF** — CTF category involving firmware extraction, JTAG/SWD debugging, side-channel analysis, and radio analysis.
- **Heap Exploitation** — A class of binary exploitation attacks targeting dynamic memory allocators (e.g., glibc's ptmalloc). Common techniques include use-after-free, double-free, fastbin attacks, tcache poisoning, and House of Force/Spirit/Einherjar.
- **HitCon CTF** — A top-tier CTF co-organized by the HITCON community and Taiwanese teams.
- **House of Force / Spirit / Einherjar** — Named heap exploitation techniques for older glibc versions.

## I

- **IDA Pro** — Industry-standard commercial reverse engineering tool.
- **InsomniHack** — A well-established European CTF.
- **Integer overflow** — A common vulnerability class in both native code (signed/unsigned confusion) and smart contracts (pre-0.8.0 Solidity).

## J

- **Jeopardy-style CTF** — A CTF format where participants solve standalone challenges in any order, scored by difficulty. Most practice platforms and online qualifiers use this format.
- **justCTF** — A top-tier CTF organized by justcatthefish (Poland).
- **jadx** — A free APK decompiler for Android reverse engineering.

## K

- **Kernel pwn** — A sub-category of pwn focused on Linux kernel exploitation. Common targets: SLUB allocator, msg_msg, pipe_buffer, struct-file abuse.

## L

- **LSB (Least Significant Bit)** — The least significant bit of each byte; commonly used for steganography.
- **LACTF** — A well-established CTF organized by the LA CTF team.

## M

- **Medium** — A popular publishing platform for CTF writeups; many CTF players maintain blogs there.
- **Memory forensics** — Analysis of memory dumps using tools like Volatility.
- **Mobile CTF** — CTF category focused on Android (APK) and iOS (IPA) reverse engineering and Frida-based dynamic instrumentation.

## N

- **Nautilus Institute** — The organizers of DEF CON CTF since 2024 (DEF CON 32). Publishes full source for both qualifier and finals.
- **Network forensics** — Analysis of packet captures using Wireshark or tshark.
- **NX (No-Execute)** — A binary mitigation that marks stack and heap as non-executable, preventing shellcode execution. Bypassed via ROP.

## O

- **One-gadget** — A single gadget in libc that spawns a shell when register/stack constraints are satisfied. Found via the `one_gadget` tool.
- **OSINT** — Open-Source Intelligence. CTF category focused on investigating public sources.
- **OverTheWire** — A free wargames platform with Linux command-line fundamentals (Bandit) and other tracks.

## P

- **Paradigm CTF** — The premier blockchain/Web3 CTF, organized by Paradigm.
- **pcap** — Packet capture file format. Analyzed with Wireshark/tshark.
- **picoCTF** — Carnegie Mellon University's beginner CTF. The canonical entry point for new CTF players.
- **PIE (Position Independent Executable)** — A binary mitigation that randomizes the base address of the executable. Bypassed via info leaks.
- **pwn** — CTF category focused on binary exploitation. From the hacker term "pwn" (to compromise).
- **pwn.college** — Arizona State University's structured pwn learning platform.
- **pwntools** — The de facto standard Python library for CTF exploit development.
- **pwnable.kr / pwnable.tw** — Two classic pwn practice platforms.

## R

- **RealWorldCTF** — A top-tier CTF organized by Chaitin Tech (China). Challenges based on real-world vulnerabilities.
- **Reentrancy** — The canonical Solidity vulnerability; recursive calls that drain contract balance.
- **RELRO (Relocation Read-Only)** — A binary mitigation that marks the GOT as read-only after relocation. Full RELRO prevents GOT overwrite attacks.
- **Reverse Engineering (RE)** — CTF category focused on analyzing binaries, obfuscated scripts, custom VMs, and exotic architectures.
- **RingZer0CTF** — A training-focused CTF platform.
- **ROP (Return-Oriented Programming)** — An exploitation technique that chains small code fragments (gadgets) already present in the executable's memory to bypass DEP/NX protections. Each gadget ends in a ret instruction, allowing sequential execution of unintended behavior.

## S

- **SageMath** — The dominant computational algebra system for crypto CTFs.
- **SekaiCTF** — A top-tier CTF organized by Project Sekai.
- **SECCON CTF** — Japan's premier CTF.
- **Shellcode** — Assembly instructions that spawn a shell; commonly injected in pwn exploits.
- **SLUB allocator** — The Linux kernel's heap allocator; common target in kernel pwn.
- **SQL Injection (SQLi)** — A web vulnerability allowing SQL command injection.
- **SSRF (Server-Side Request Forgery)** — A web vulnerability allowing server-side requests to internal services.
- **SSTI (Server-Side Template Injection)** — A web vulnerability allowing code execution via template engines (Jinja2, Twig, Freemarker).
- **Steganography (stego)** — Hiding data within other data; common in forensics challenges.
- **Stego-toolkit** — A Docker image pre-loaded with steganography tools.

## T

- **TryHackMe** — A structured learning platform with browser-based labs. Best on-ramp for absolute beginners.
- **Tcache** — Thread-local caching in modern glibc malloc; common target in heap exploitation.

## U

- **UAF (Use-After-Free)** — A vulnerability class where freed memory is accessed. Common in heap exploitation.
- **UIUCTF** — A top-tier CTF organized by SIGPwny at UIUC.

## V

- **Volatility** — The dominant memory forensics framework.

## W

- **Web CTF** — CTF category focused on web exploitation.
- **Wireshark** — The dominant packet-capture analysis tool.
- **Wiener's attack** — An RSA attack effective when the private exponent `d` is small.

## X

- **XSS (Cross-Site Scripting)** — A web vulnerability allowing JavaScript injection. Reflected, stored, and DOM-based variants.

## Y

- **yafu** — An advanced factorization tool. Uses SIQS and GNFS.

## Z

- **zsteg** — A PNG/BMP steganography detector. Detects LSB steganography.
