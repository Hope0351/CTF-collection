# :mag: FAT CAT (Forensics)- KJSSE CTF 3.0

---

# FAT CAT (Forensics)— KJSSE CTF 3.0

*Challenge*

This challenge was given in Round 2 of KJSSE CTF 3.0 by K.J. Somaiya College of Engineering, Vidyavihar.
Challenge Description:
*A butterfly shouldn’t make a cat feels this heavy. There is more to this image than meets the eye. If you dig deep enough into the structure, you’ll uncover the flag hidden underneath the heavy load.
*File: chall.png

*chall.png*

This was one of the first challenges that I completed in the CTF. From the description and file given, it was pretty clear that it was more of a Steganography challenge.

For steganography challenges, I usually prefer to use tools mentioned in the website below. It includes a handpicked list of relevant steganography tools that can help you solve the issues.
[Steganography — A list of useful tools and resources — 0xRick’s Blog](https://0xrick.github.io/lists/stego/#steganography)

For png files, the tools that come in handy are mostly strings, zsteg, binwalk and foremost. I prefer to use zsteg first to find any hidden useful strings or clue in a png file.

```
Command:
zsteg -a chall.png
```

*zsteg output*

Clearly, there are no hidden strings, but we found that it has a “ZIP Archive file” in it. We can extract that using Binwalk.

```
Command:
binwalk -e chall.png
```

*First binwalk output*

On opening the folder, it seems that there is another png file named “lited.png”. From the first binwalk output, it is clear that we have multiple image files archived inside one another. So, I performed binwalk command on every png file and extracted them.

*lited.png*

After a total of 10 binwalk commands, I finally got to the last image.

*Finally😩!!!*

*b3duIA.png (last image)*

I tried strings on this image, but didn’t get much except a text saying: “*NOTHING HERE, DID YOU LEAVE THE ANSWER BEHIND?*”

*strings output*

Clearly, I felt the need of backtracing all my steps and checking on all of the images and find if I left something behind. Next, I went back to all the images and tried strings on them, but they gave me no clue whatsoever. After spending around a nice 10–15 minutes on this, I was completely clueless on what did I left behind. Even zsteg couldn’t give any useful output on the final image.

## Get Vedant Pillai’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

When I was about to give up and go to next challenge, I thought of using one last technique — Extracting data through LSB techniques.

I used the following tool for this:
[StegOnline](https://www.georgeom.net/StegOnline/upload)

*Stegonline — George Om*

On uploading the final image, we get an option to check it on different bit planes.

On checking it for “Red 0”, we can see the flag written on it clearly.

*Flag found😇*

Let’s Connect:
Linkedin: [Vedant Pillai | LinkedIn](https://www.linkedin.com/in/vedant-pillai-842ba625a/)
Github: [Codewith-Vedant (Vedant Pillai)](https://github.com/Codewith-Vedant)

---
