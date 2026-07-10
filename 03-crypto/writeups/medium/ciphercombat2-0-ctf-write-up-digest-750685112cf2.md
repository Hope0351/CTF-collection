# :locked_with_key: CipherCombat2.0 CTF Write-up : Digest

---

# CipherCombat2.0 CTF Write-up : Digest

Reverse Engineering Challenge of Hacker Earth CipherCombat2.0

## What we get?

A zip file with password “hackerearth”… unzip it and we get a Linux Executable

*Notice I highlighted LSB(Least Significant Bit) ? We will see why later…*

## Solving the challenge

Let’s do strings …

With strings we found some Texts but nothing like our flag.

Important thing to see here is MD5 function calls and use of libcrypto.so.1.1 points at use of MD5 hash algorithm.

Further we can check this by listing all imports by RABIN2

And we see that MD5 global functions are important.

Let’s check the disassembly now…

We can see that it compares the MD5 digest of string supplied with a hard coded MD5 value. We can also see it has moved hard-coded hex string to stack at 0x000011ad

Any ways, it is comparing with something in stack, and my favorite way is to fire up GDB and check the stack in real-time to get the data.

Let’s have a look at GDB disassembly…

We can see that string compare function is at *main+186 so we will put break point there.

Now let’s run the program and provide random input.

We hit our breakpoints ! Let’s check registers, STRNCMP compares values stored in [R/ESI] with [R/EDI]…

So get address of our hard-coded hash loaded in stack, lets check it out how it’s doing.

And we get our values now let’s reconstruct the MD5

Remember about LSB? these values are stored like that, we need to convert it into MSB and then we can continue.

Copy the values in any text editor and rearrange them as following…

so at last we have our hash : 53a167c8d4dc964f7d7838dd4ce2d137

Only thing left to do is brute force it, we can use online services, the one I used and which they later provided in their free hint is [https://hashes.org/](https://hashes.org/)

And we have our flag : HE{iamalmighty9}

< And here is a cross check with the challenge binary.

Another Fun challenge! Done.

NOTE: we could have done it in 3–4 less steps by just converting the strings found in MOVABS instructions,

But what’s the fun in that, also i wanted to show you the dynamic analysis path. :-)

## About CTF

Hacker Earth’s CipherCombat2.0 was great CTF for beginners in the security field. Overall great experience

---
