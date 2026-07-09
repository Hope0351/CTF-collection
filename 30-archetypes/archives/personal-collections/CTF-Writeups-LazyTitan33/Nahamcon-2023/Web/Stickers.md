# Stickers

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We have a simple sticker shop with some fields we can fill out:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I tried this challenge early on and it was broken, it was supposed to generate a PDF but didn't. I struggled for a while then left it alone.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

But I knew based on the error message that this was a DOMPDF RCE exploit:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Luckily at some point I saw this message in the Discord channel.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Good thing I started searching for other people talking about Stickers otherwise I wouldn't have seen this and probably wouldn't have gone back to the challenge. Perhaps a better idea is to also leave such a note in the challenge description or pinned to the discord channel.

We can see that now PDFs are generated:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

DOMPDF has a known RCE vulnerability detailed here and [here](https://positive.security/blog/dompdf-rce). I used a stylesheet href.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And indeed we get a hit on our python webserver for the files we prepared.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can easily find the path of the dompdf fonts due to the Forbidden error message:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The `.css` file we prepare will grab our php webshell:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can get the md5um of our path because we'll need it to find our webshell:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The webshell is inserted into a renamed font file:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And we have our code execution and our flag:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{a4d52beabcfdeb6ba79fc08709bb5508}

