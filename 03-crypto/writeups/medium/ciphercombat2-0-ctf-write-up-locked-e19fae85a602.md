# :locked_with_key: CipherCombat2.0 CTF write-up : Locked

---

# CipherCombat2.0 CTF write-up : Locked

Reverse Engineering Challenge of Hacker Earth CipherCombat2.0

## What we get ?

We get a zip file with our binary in it with password hackerearth.

After unzipping the file, we can start looking at the binary.

Important stuff : it’s Linux Executable and not stripped… This makes task easier.

## Solving the challenge

Let’s make the file executable by chmod.

now let’s run it once and see what it actually does…

So seems like some type password check, and the name of challenge checks out !

Let’s Disassemble it and try to understand the checking mechanism.

doing Strings on the file we get something interesting…

Looks like good password? Also if we see the disassembly we see main calls the fun2() function before test eax,eax at 0x000012d7 which controls the flow of program… and see what it compares! the same string !

Let’s just try this as password…

And that works ! submit the flag and get them points…

## About CTF

Hacker Earth’s CipherCombat2.0 was great CTF for beginners in the security field. Overall great experience

---
