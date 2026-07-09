## Ring Cycle 1 - Basics

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Enumeration

This challenge is the first one in the Ring Cycle Challenge Group which is focused on reversing. I'm not much into reverse engineering but I will often take a quick look at the dangling fruits. 

I took the provided binary and uploaded it into [dogbolt](https://dogbolt.org/). I was too lazy to start up ghidra for this so I used this online webservice. It's great for quick and small binaries.

We can already see some hex values that should be interesting:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The binary is expecting a passphrase from us and it is comparing it with this value. I slapped the values into Cyberchef, swapped endianess and hex decoded it:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```text
You are ready to start your safe cracking journey
```

## Solution

Gave the passphrase to the binary and got the flag:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`flag{8562e979f1f754537a4e872cc20a73e8}`
