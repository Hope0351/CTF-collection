# Pursue the Tracks

## Enumeration
This one starts with an MFT file:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can use [MFT Explorer](https://f001.backblazeb2.com/file/EricZimmermanTools/MFTExplorer.zip) to read these and can see some interesting folders already:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution
Let's start the challenge by connecting to the provided IP and Port. Question one can be answered directly as it is clear what we can see:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Second question:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can find this answer by enumerating and looking carefully at the creation dates:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Third question:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Deleted files are flagged as such in MFT Explorer:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Fourth question:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Not sure how to identify hidden mode for files in MFT Explorer, this was just easier to guess.

Fifth question:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This file looks important for sure and it's the only .txt file:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Sixth question:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Copied files are also flagged and as such are easy to find:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Seventh question:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

This one requires careful enumeration again by looking at the creation date vs modified date:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Eighth question:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Record numbers for files show up in the top left corner of the Overview in HEX format. 0x2d is 45 in decimal:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Ninth question:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Record number 40 is 0x28 in HEX. The total file size is mentioned in the `Allocated size` for the file. In this case file with Record Number `0x28` in HEX is the one we are interested in and the size is `0xE000`.   
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can convert that to decimal [online](https://www.rapidtables.com/convert/number/hex-to-decimal.html):  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{p4rs1ng_mft_1s_v3ry_1mp0rt4nt_s0m3t1m3s}`

