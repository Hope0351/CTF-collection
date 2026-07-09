# An Offset Among Friends


Attachment: [an-offset](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Writeup

A quick decompiling in [dogbolt](https://dogbolt.org/) and we can see what looks like a jumbled flag:  



I recognize this as being rotated, but unlike ROT13, the special characters of curly braces are rotated as well so we can use ROT47 from Cyberchef:  



https://gchq.github.io/CyberChef/#recipe=ROT47(-1)&input=Z21iaHxkNjU0MjY1OTM2NDJkMjJiODdiZmJiOTM5ZjU0OTE4ZH4&oeol=VT

flag{c54315482531c11a76aeaa828e43807c}
