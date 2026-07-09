# easy-hide

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

# Solution

Running foremost on this PNG, we notice there's a `JPG` hiding inside and the tool extracts it for us:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In the output directory, we find a `.zip` that we can decompress and get the .jpg:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

However, if we open it with [ghex](https://wiki.gnome.org/Apps/Ghex), we can notice that it has a broken header:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

From within kali, I just opened a known good .jpeg with a proper header to use as an example:  

```bash
ghex /usr/lib/python3/dist-packages/docx/templates/default-docx-template/docProps/thumbnail.jpeg
```
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Modified the first line of bytes to fix the jpeg header and then I could open the picture and get the flag:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`UNR{sunIZZsunshine}`

Note: It's a bit annoying when the flag format changes unexpectedly in the middle of the CTF but it makes sense for this challenge since we don't want to manually copy a lot of characters. However, it would've been nice if any CTF format changes are specified in the challenge description.
