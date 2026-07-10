# :skull: Tutorial: Shellcode Injection when the buffer is small

> **Original Source:** [Tutorial: Shellcode Injection when the buffer is small](https://infosecwriteups.com/tutorial-shellcode-injection-when-the-buffer-is-small-ee3a29dcb955)
> **Platform:** infosecwriteups.com | **Category:** `PWN`

---

# Tutorial: Shellcode Injection when the buffer is small


## A deep dive into mastering shellcode injection when space is not on your side — inspired by a real university cybersecurity project.


>

[Free version of this article](https://medium.com/system-weakness/tutorial-shellcode-injection-when-the-buffer-is-small-ee3a29dcb955?sk=d07d50b9f31fb810d2b03ef826ebef59)


Before we delve into the nitty-gritty of shellcode injection in scenarios where buffer space is a luxury we don’t have, let me share a bit of a personal backstory.


This exploration into the depths of buffer overflow and shellcode techniques is inspired by a project I tackled during my cybersecurity course at university.


It was one of those challenges that was as thrilling as it was enlightening. The task demanded creativity, a deep understanding of system vulnerabilities, and an almost artistic touch in crafting a solution that worked within the tightest of constraints.


It was not just an academic exercise but a real-world puzzle that tested the limits of what I thought was possible. This article is a reflection of that journey — a testament to the fun and the fight in facing down cyber vulnerabilities head-on.


Now, let’s dive into how we can overcome the challenge of small buffer sizes in shellcode injection, turning constraints into launchpads for sophisticated exploits.

## Theoretical Part


In this case, we face a local shellcodeinjection since we have access to the binary itself that…

---

*Originally published on [Medium](https://infosecwriteups.com/tutorial-shellcode-injection-when-the-buffer-is-small-ee3a29dcb955). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of pwn CTF writeups.*
