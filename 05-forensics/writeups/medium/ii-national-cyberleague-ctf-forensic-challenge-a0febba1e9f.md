# :mag: CTF Forensic challenge. A forensic challenge from a national…

> **Original Source:** [CTF Forensic challenge. A forensic challenge from a national…](https://infosecwriteups.com/ii-national-cyberleague-ctf-forensic-challenge-a0febba1e9f)
> **Platform:** infosecwriteups.com | **Category:** `FORENSICS`

---

# CTF Forensic challenge


## A forensic challenge from a national CTF in Spain


*Photo by [Mika Baumeister](https://unsplash.com/@mbaumi?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText) on [Unsplash](https://unsplash.com/s/photos/hacking?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText)*


Last week a CTF event organized by the Spanish Guardia Civil was organized, the II NATIONAL CYBERLEAGUE GC. This challenge is oriented to students, due to that reason I could not participate. But I have I friend who participate, He knows I love forensic challenges so He sent me one of the challenges that were part of the competition. Their team did not manage to solve this challenge so let’s see what was about and how to solve it.

## Evidence


There are two files:


If you have played other CTF challenges this seems a little obvious but let it break into parts. The container seems to be an encrypted container and snap.vmem it is a RAM acquisition.


Secrets in live memory have been always a problem. Having a RAM acquisition can give us a lot of information in a digital forensics investigation. We can discover processes running, dump files, secrets, connections and a lot of useful information. The most popular tool for memory analysis is [Volatility](https://www.volatilityfoundation.org/). Volatility is an Open Source project with a great and active community behind it, there are alternatives like [Rekall](http://www.rekall-forensic.com/) but I personally prefer Volatility.

---

*Originally published on [Medium](https://infosecwriteups.com/ii-national-cyberleague-ctf-forensic-challenge-a0febba1e9f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of forensics CTF writeups.*
