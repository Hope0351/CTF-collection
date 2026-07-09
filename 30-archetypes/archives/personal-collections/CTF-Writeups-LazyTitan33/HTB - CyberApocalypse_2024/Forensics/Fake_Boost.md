# Fake Boost

## Enumeration
For this challenge, we have a wireshark capture to deal with:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Usually, the first thing I do with wireshark captures is go to `Statistics` -> `Protocol Hierarchy` to see what protocols I'm dealing with, how much data each has etc:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can notice some TCP traffic so let's start following that.

## Solution

On the 3rd TCP Stream, we see a large Base64 blob:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

A bit further down, we can see it is reversing and then decoding it:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We do that ourselves in Cyberchef and scroll down a bunch until we find part1 of the flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Decoded it in the terminal and set it aside until we find the rest:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Looking through the rest of the script, we can see an Encryption function:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Several AES modes are available but CBC is first in the list:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And also a hardcoded AES key:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```text
AES Key: Y1dwaHJOVGs5d2dXWjkzdDE5amF5cW5sYUR1SWVGS2k=
```

Towards the end of the wireshark capture, we notice another Base64 blob but no other options. Unlike the previous one, this doesn't seem reversed nor can we simply decode it:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This must be where the previous encryption we found comes into play. Because only the Key is passed to the encryption function, we can reuse it as the IV and pass these to Cyberchef and decode then decrypt the Base64 blob:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Weird, this doesn't look like an email address, in fact, it looks Base64 encoded:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

So we decode it and get our second part of the flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{fr33_N17r0G3n_3xp053d!_b3W4r3_0f_T00_g00d_2_b3_7ru3_0ff3r5}`
