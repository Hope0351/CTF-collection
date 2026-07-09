### Challenge description

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We start off this challenge with a simple email file:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

However, something jumped out at me. There is an attachment with a double extension, `.pdf.html` with a large Base64 blob.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

DISCLAIMER: _The following few steps are a bit dangerous if you don't know what you are doing or are doing it in an insecured environment as it involves some dynamic forensics._

I first saved this HTML file locally:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And hosted it using a python webserver. When accessed, the browser immediately downloads the next stage which is an apparent .zip file.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Indeed it is a zip file which we can decompress and find another stage. Another file with a double extension of .pdf.js.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The javascript file contains a lot of comments/garbage and obfuscated variables.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I cleaned it up a bit by removing the comments and renaming some variables until it made more sense to me and realised what it is doing.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The next stage is concatenating all the parts, then replacing the `s` with nothing, the `V` with nothing and the `sV` with nothing. I did that manually using `sed` and noticed that the resulted blob looked like hex so I hex decoded it using this oneliner:

```bash
cat stage4|sed 's/s//g'|sed 's/V//g'|sed 's/sV//g'|xxd -r -p > stage5
```

This stage has a lot of variables. By a lot, I mean a lot.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Thanks to the preview window in Sublime, I noticed some larger blobs which turns out are base64 blobs that are concatenated.  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I put them all together and decoded them in Cyberchef to find a Powershell command execution.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

It was piping everything to IEX to detonate so I replaced IEX with a harmless `echo` and ran it which revealed yet another stage. I lost track of stages at this point.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I stared at this code for a while trying to understand it. A closer look shows that it is doing some XOR operations on some HEX bytes:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Realising this I took each byte array, unhexed it and XORed it with the specified Decimal using Cyberchef until I found the one hiding the flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

HTB{l0ts_of_l4Y3rs_iN_th4t_1}




