# Where am I?

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
This one seemed closer to Stego than OSINT but indeed, for OSINT situations where you have some pictures to analyze, you would look at the metadata first. There was a lot of metadata in this picture, including GPS coordinates which I wasted some time on.

But then I scrolled up and saw the `Image Description`:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Now we can get the flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

A bash oneliner like this would do it:

```bash
exiftool -ImageDescription PXL_*.jpg|awk '{print $4}'|base64 -d
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{b11a3f0ef4bc170ba9409c077355bba2)
