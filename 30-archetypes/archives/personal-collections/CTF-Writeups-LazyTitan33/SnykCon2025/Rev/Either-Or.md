# Either Or


Attachment: [either-or](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Writeup

I decompiled this quickly in [dogbolt](https://dogbolt.org/) and saw a string the main function that I recognized to be rotated. Specifically ROT13. 



Copied the value and rotated it in Cyberchef:  



Now that I know the secret password, I give it to the binary and get the flag:  



flag{f074d38932164b278a508df11b5eff89}
