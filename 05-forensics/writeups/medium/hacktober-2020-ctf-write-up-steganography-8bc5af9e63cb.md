# :mag: Hacktober 2020 Ctf Write Up Steganography 8Bc5Af9E63Cb

---

## Boney Boi Breakdance

>

“We intercepted this image from a known DEADFACE affiliate. Some kind of tool was used to hide a file in this image. Unlike some of the other, easier images that used steganography, this one appears to require a passphrase. I bet it’s somehow related to the image used to hide the file.”

This challenge was specially frustrating to my team and I and it was simpler that we thought. This will be a short write-up, but I will explain the struggle and hopefully you can learn not to make the same mistakes.

We quickly learned that this file contains a secret with steghide :

Now, how in the world would we find this password? The hint in the description of the challenge says it must have something to do with the picture.

Now , here is our mistake : OVERTHINKING!

I lost a couple hours in this challenge because I was overthinking it. First step was to find who created the picture. Easy enough, search “Dance of Death “ (name of the file), and you will find that Michael Wolgemut is the painter of that image. There you have it ! However, we decided the scrape the WHOLE Wikipedia website about Michael Wolgemut and use every word to brute force the steghide, which in theory would have work, but it didn’t for one reason : lowercase .

The brute force failed, and we though the challenge was broken or we were just going in the wrong direction. I talked to another player who have solved , and said that we were in the right direction, but we were overthinking it too much.

Simple enough, I tried his first and last name , and his last name was the password. Now I thought : How the in the hell the brute force failed if his name was in the wordlist? IT WASN’T LOWERCASE .

Interesting enough, even with the password, we still cannot extract the secret file because it does not have a name. So, we can just extract with an output name and retrieve the flag :

flag{d4n53_m4c4b3_nuremberg}

Cheers and Happy Hacking :)

---
