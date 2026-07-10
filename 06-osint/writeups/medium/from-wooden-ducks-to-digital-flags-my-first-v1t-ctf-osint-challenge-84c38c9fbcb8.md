# :sleuth_or_spy: From Wooden Ducks to Digital Flags: My First v1t CTF OSINT Challenge

> **Original Source:** [From Wooden Ducks to Digital Flags: My First v1t CTF OSINT Challenge](https://infosecwriteups.com/from-wooden-ducks-to-digital-flags-my-first-v1t-ctf-osint-challenge-84c38c9fbcb8)
> **Platform:** infosecwriteups.com | **Category:** `OSINT`

---

## 🔍 My Approach: The OSINT Methodology


Here’s the thing about OSINT challenges — they’re like detective work, but instead of a magnifying glass, you’ve got browser tabs. Lots of them.

## Step 1: Check the Metadata (Because Why Not?)


My first instinct with any image-based OSINT challenge is to check for hidden metadata. You’d be surprised how often people leave GPS coordinates, camera info, or other juicy details in their photos.


Tool of choice: `exiftool`


```
exiftool duck_image.jpg
```


I ran this expecting… well, *something*. But nope — nothing particularly useful jumped out. No hidden coordinates, no secret messages in the EXIF data. Just a regular image file.


Lesson learned: Always check metadata first, but don’t be disappointed when it’s a dead end. It’s about eliminating possibilities.

---

*Originally published on [Medium](https://infosecwriteups.com/from-wooden-ducks-to-digital-flags-my-first-v1t-ctf-osint-challenge-84c38c9fbcb8). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of osint CTF writeups.*
