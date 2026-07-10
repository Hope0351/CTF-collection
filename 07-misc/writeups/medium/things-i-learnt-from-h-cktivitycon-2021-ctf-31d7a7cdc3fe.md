# :game_die: Things I Learnt From H Cktivitycon 2021 Ctf 31D7A7Cdc3Fe

> **Original Source:** [Things I Learnt From H Cktivitycon 2021 Ctf 31D7A7Cdc3Fe](https://infosecwriteups.com/things-i-learnt-from-h-cktivitycon-2021-ctf-31d7a7cdc3fe)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2021

---

## \n is the not newline character


this one came to my surprise… integrity, “medium” web, had an input box with filters for a few of the special characters, i tried submitting a few including ‘\n’, and got the error: ‘\’ is not allowed


later a writeup did the exact same thing and i couldn’t understand the difference — until i played around in burpsuite and copy-pasted the newline character i got from the non-printable chars, turns out both have different use cases


NewLine (\n) is 10 (0xA) and CarriageReturn (\r) is 13 (0xD) — in other words, \n is the printable version(?) somebody correct me on this, please!


to read more on this, here’s [an old non-HTTPS blog from 2009](http://hayne.net/MacDev/Notes/unixFAQ.html#endOfLine) and [a modern day Q&A website](https://stackoverflow.com/questions/3267311/what-is-newline-character-n).

---

*Originally published on [Medium](https://infosecwriteups.com/things-i-learnt-from-h-cktivitycon-2021-ctf-31d7a7cdc3fe). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
