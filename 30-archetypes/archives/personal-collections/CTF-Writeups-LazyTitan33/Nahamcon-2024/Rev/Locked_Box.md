## Locked Box

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution

This challenge provides us a Makeself self extracting bash script:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

For such scripts, we can carve out the archive itself skipping the first 715 lines because we can see the bytes starting from line 716. 

```bash
 tail -n +715 thebox > archive
```

We confirm that we extracted the archive:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)


The python script from within the archive again contains a lot of flags:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

But we just need to run it and it will print the flag:  

`flag{3a50c5e41a1c3eee6dcddca9e04992e0}`
