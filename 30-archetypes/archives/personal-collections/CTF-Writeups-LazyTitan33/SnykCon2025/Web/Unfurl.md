# Unfurl


Attachment: [challenge.zip](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Writeup

In the source code I can see that there is a filter for the clientIP to ensure only the localhost would access it:  



This would give me command execution but it also means I need to find an SSRF vulnerability. The internal app is also running on a random port but we know the range which would make it easy to enumerate:  



The functionality of the website itself is basically just an SSRF, there is no filter that we need to bypass or anything. I've sent the request to Intruder specifying the port range we want to hit to find the internal app:  



I also used grep to find the request that has the flag:  



flag{e1c96ccca8777b15bd0b0c7795d018ed}
