## What's in the Box?

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution

This challenge provides us a Makeself self extracting bash script:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

For such scripts, we can carve out the archive itself skipping the first 715 lines because we can see the bytes starting from line 716.  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```bash
 tail -n +715 thebox > archive
```
And now we've taken it ou manually. I had to do this because I kept getting python related errors and I was too lazy to resolve them. But we confirmed we extracted the archive:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The archive contains a python script that starts with a lot of flags:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Then ends with some more, but based on the code, we don't need to do anything other than run it, give it the hardcoded pin code and it should spit out the correct flag:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And we are correct:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`flag{da0a0a25f5b35fbf99e3351997bfc4c8}`
