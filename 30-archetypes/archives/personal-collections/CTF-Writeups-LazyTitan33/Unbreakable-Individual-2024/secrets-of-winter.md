# secrets-of-winter

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

# Solution

At least on this challenge, we know that the flag is not in the usual format:  
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Running `exiftool` on the image, we can find two base64 strings:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```bash
echo Y2g0bDF9|base64 -d
```

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```bash
echo ZjFuaSRoLXRoMy0=|base64 -d
```
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

So it looks like we have the last 3 words for now. I also ran stegoveritas on the picture and it extracted all the different colored layers of the picture in a folder. I went through them several times looking for hidden characters/words, zooming in and out, until I found the beginning of the flag on a building off in the distance with very small font:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

It's very difficult to see but we eventually build our full flag: `ctf{g3t-3xiftool-to-f1ni$h-th3-ch4l1}`
