# Screaming Crying Throwing up


Attachment: [screaming.bin](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Writeup

The title of the challenge as well as the description points us to the scream cipher. We can use [this](https://scream-cipher.netlify.app/) online tool in order to convert our payload.  

However, it is important to open the file in a proper text editor. When read from a powershell terminal or bash, the strange characters are not outputted correctly and won't decode to our flag. I opened it in Sublime Text:  



Now I can "translate" it and get the flag:  



flag{edabfbafedcbbfbadcafbdaefdadfaac}
