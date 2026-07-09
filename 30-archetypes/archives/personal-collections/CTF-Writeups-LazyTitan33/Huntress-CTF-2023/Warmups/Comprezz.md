# Comprezz

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
Running the file command on this, we get a strange message:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

A quick Google search seems to indicate this is a `.z` file:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

On this link, we can find this information:  
https://stackoverflow.com/questions/12168081/how-can-i-uncompress-z-file-under-ubuntu
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

So let's go ahead and rename the file and try to uncompress it:

```bash
mv comprezz comprezz.z
uncompress comprezz.z
```
It works, and we get a file that we can read:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{196a71490b7b55c42bf443274f9ff42b}
