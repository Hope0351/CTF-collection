## Buggy Jumper 1

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Enumeration

While looking through the source code, we see multiple mentions of Godot and find this `flag.gdc` file.  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

But it seems to be a binary file so we can't just read it. I asked ChatGPT for some clarification and it confirmed what I thought:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We are dealing with a Godot compiled code that we need to decompile. 

## Solution

I found this great precompiled tool on github. I ran it and opened the `flag.gdc` and selected the latest bytecode version from the drop down list:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

It decompiled it and now we can read it and get the flag:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`flag{c2d5a0c9cae9857a3cfa662cd2869835}`
