# Opposable Thumbs

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
In this case, running a file command doesn't really help as we only get that it contains data:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In such cases, I revert to manually looking at the file header using a hexeditor. In some cases it may simply be wrong or missing. In this case however, we see an unfamiliar header called `CMMM`:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

A quick google search indicates that this is a Windows cache file:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I'm sure that there are several ways of reading this file, however, the way I did it is by using this tool:  
humbCacheViewer

This tool sees the other cache files in my VM as well but the one we are interested in is the one with 256 in the name and we get the flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{human_after_all}
