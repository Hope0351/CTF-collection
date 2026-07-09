# fake-add

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

# Solution

We can use [dogbolt](https://dogbolt.org/) to decompile small binaries and with this one, we find some interesting looking bytes in it:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I've copied these locally:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Removed the null bytes:  
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Added the two HEX strings together and decoded the resulting string in Cyberchef:  
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We get our non-standardly formatted flag, but at least this time, it was mentioned in the challenge description:  

`CTF{th1s_is_ju5T_ADD}`
