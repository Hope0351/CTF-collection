# Writing on the Wall

## Solution 
In this binary, when opened in Ghidra, we can see it is assigning `6` bytes to local_le, local_18 is `8` bytes ending in a space and it actually reads just `7` bytes from our input which is local_le. 

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This means that when it reads our input, the [strcmp](https://www.programiz.com/cpp-programming/library-function/cstring/strcmp) stops at a null byte and compares it with a null byte. So we can just pass 7 null bytes to the program and the strcmp should be true:

```bash
python -c 'print("\x00"*7)'|nc 94.237.56.26 56996
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{3v3ryth1ng_15_r34d4bl3}`
