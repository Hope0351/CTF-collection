# :game_die: Bug on ParrotCTF. In this write-up I have mentioned how I…

> **Original Source:** [Bug on ParrotCTF. In this write-up I have mentioned how I…](https://infosecwriteups.com/bug-on-parrotctf-e64424b0d043)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

*ParrotCTF*


Hello fellas, how are you guys doing!! Well, I am here with another bug write-up.


A little background details about me. I am a new bug bounty hunter still learning about the bugs and trying up new things. For which I am solving THM rooms, HTB rooms, and newly came across a website named, [parrotctf](https://parrot-ctfs.com) which is a great room for intermediate hackers.


Now coming back to how I got the bug on their website.

## DotGit


This is a Firefox extension used by hackers/hunters to get the hidden .git directory of the website if it is present.


Link to download: [https://addons.mozilla.org/en-US/firefox/addon/dotgit/](https://addons.mozilla.org/en-US/firefox/addon/dotgit/)


## Get Sidharth Panda’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Once downloaded just pin it to your extension bar, and the next time you will visit any site it will directly show if any is .git directory is present.

## Bug Details


Exposed .git directory is considered as a security misconfiguration. It is significant because it can reveal sensitive information and lead to potential security vulnerabilities such as:-


- Source Code Access.

- Commit History and Sensitive Information.

- Usernames and internal information.

- Information on dependencies and deployment details.

## How I found it


So, when I was reading on Active Directory (AD), I got a notification on dotgit extension mentioning about 2.git directories.


I decided to look it up over web, and got the following response.


and


Once I found it, I submitted it on discord server and the founder looked an confirmed that it was exposed. within 2–3 hours he updated me that it is mitigated and the site has patched.


So yup that is it. This is how I found a security information exposure on parrotctf.


Bug Found: 13–10–2024


Bug Reported: 13–10–2024


Bug Patched: 13–10–2024


I would like to end this write-up here I hope this write-up may come into some help of yours.


Keep learning, keep hacking.


0xkalki signing out.


Radhe Radhe

---

*Originally published on [Medium](https://infosecwriteups.com/bug-on-parrotctf-e64424b0d043). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
