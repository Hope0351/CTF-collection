# :skull: Tutorial: Shellcode Injection (+ Crafting them like an artist)

> **Original Source:** [Tutorial: Shellcode Injection (+ Crafting them like an artist)](https://infosecwriteups.com/tutorial-understanding-shellcode-crafting-like-an-artist-b3279465dcbf)
> **Platform:** infosecwriteups.com | **Category:** `PWN`

---

# Tutorial: Shellcode Injection (+ Crafting them like an artist)


## A Casual Guide to Cybersecurity’s Perennial Challenges


>

[Free version here](https://medium.com/system-weakness/tutorial-understanding-shellcode-crafting-like-an-artist-b3279465dcbf?sk=bd16c3e341bf8692bceb2c9c4554e47e)


Hello there! As someone deeply immersed in the field, I’m here to guide you through two critical cybersecurity concepts: Shellcode and Buffer Overflow. Let’s unravel quickly these topics together in a way that’s engaging and informative like I do with my student at my University.

## Theoretical Part


### I. Exploring Buffer OverflowsBuffer Overflows in a Nutshell*: *A Buffer Overflow is a classic software bug where a program writes more data to a buffer than it can hold. This can cause the program to behave unexpectedly or crash, and in some cases, allow an attacker to take control.


How Buffer Overflows Occur*: *This typically happens in languages that don’t automatically manage memory, like C and C++.


Here’s a simple C code example to illustrate:


```
#include <stdio.h>
#include <string.h>

void vulnerableFunction() {
char buffer[10];
strcpy(buffer, "This string is way too long for the buffer!");
}

int main() {
vulnerableFunction();
return 0;
}
```


*Buffer Overflow: Beyond the Basics*


A Buffer Overflow occurs when more data is written to a buffer than it can handle, causing data to overflow into adjacent memory. This can corrupt or overwrite the…

---

*Originally published on [Medium](https://infosecwriteups.com/tutorial-understanding-shellcode-crafting-like-an-artist-b3279465dcbf). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of pwn CTF writeups.*
