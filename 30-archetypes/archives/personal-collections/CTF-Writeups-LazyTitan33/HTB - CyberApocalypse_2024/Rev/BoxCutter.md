# BoxCutter

## Solution 
Trying to run the binary directly, we get an error about a box not being found:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

If we run it with `strace` however, we can see it is trying to access a file or directory that doesn't exist... because it's our flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can also get it with `strace`:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{tr4c1ng_th3_c4ll5}`
