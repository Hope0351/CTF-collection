# Dumpster Fire

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
We seem to have a dump of a Linux filesystem. As always, I start by looking in the folders of the user:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

What draws my attention immediately is the `.mozilla` folder. This guy may have accessed some websites containing flags. We can use the following tool to decrypt a Firefox profile and all of its contents, including stored credentials.

irefox_decrypt

Indeed, when we run the tool and give it the specific profile we want decrypted, we get the flag as part of a password used at some point.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{35446041dc161cf5c9c325a3d28af3e3}
