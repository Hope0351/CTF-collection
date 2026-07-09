# Book By Its Cover

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
This is a challenge that indicates the importance of common commands such as `file`. This doesn't apply just in CTFs.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Because we now know that the "archive" is in fact a picture, we rename it.

```bash
mv book.rar book.png
```
Opening the picture, we get the flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

To make it easier on us, we can use `tesseract`, a great OCR tool, to get the text out of the picture since we don't want to make any mistakes when manually transcribing it:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This creates a flag.txt file containg our flag.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{f8d32a346745a6c4bf4e9504ba5308f0}
