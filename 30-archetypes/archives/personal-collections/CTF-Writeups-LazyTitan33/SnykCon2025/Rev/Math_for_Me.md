# Math for Me


Attachment: [math4me](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Writeup

I decompiled the binary and gave the code to chatGPT asking it to solve it for me. Cause I'm lazy.



This AI is getting better every day. I was surprised to see it was right. I was very sure it is lying to me.



Another way to get the flag, in a less dumb way, would be to patch the binary, just like I did in [Rock Paper Psychic](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33) where it is making the check for the special number:  



Now that I changed the JZ to JNZ, I can pass any value:  



And get the flag:  



flag{h556cdd`=ag.c53664:45569368391gc}
