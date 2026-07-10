# :game_die: CAT Reloaded CTF - CATF 2025-DFIR Challenges

> **Original Source:** [CAT Reloaded CTF - CATF 2025-DFIR Challenges](https://infosecwriteups.com/cat-reloaded-ctf-catf-2025-dfir-challenges-ff403f100504)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2025

---

Challenge 4 “Erased Traces”:

### The easy yet the difficult Challenge


Solving this challenge almost drove me crazy. opening the hard image on FTK Imager, we can easily detect 4 deleted files that need to be recovered. (hard image was too small, so finding these deleted files wasn’t challenging)

*open with FTK Imager*


Now we need to do file carving on the disk, to restore files correctly.


Here’s all tools i used that didn’t work properly to recover the deleted files correctly:


- photorec

- scalpel

- winfr (Windows File Recovery)

- MyRecover

- recuva

- etc…


i was so close to giving up.


i know that recuva is almost the best tool to recover deleted files (as i always use it personally). file was irrecoverable as you can see, and i tried to recover them, but i got 4 files full of null bytes🫠


NOTE: most tools need the image disk to be mounted to do file carving correctly, so we’ll use Arsenal Image Mounter to mount that image “download [link](https://arsenalrecon.com/downloads)”, just a few easy clicks to mount the image file.


before giving up, I tried to see if there is a powerful tool instead of “recuva”, or “recuva professional”, so i found this amazing reddit post that answered my question. “[link](https://www.reddit.com/r/datarecovery/comments/11cm6bd/how_to_recover_unrecoverable_files_from_usb_drive/)”


*Disk Drill*


just download Disk Drill from this [link](https://www.cleverfiles.com/data-recovery-software.html), we can attach the disk image


Search for lost data → Universal Scan, “after scan finished” → review found items


check yes on “hide duplicates”


check 4 deleted files and recover them (CAT1, CAT2, CAT3, CAT4)


hop on HxD “download [link](https://mh-nexus.de/en/downloads.php?product=HxD20)”, to check if file data still null or not🫠

*CAT1*


FINALLY, PDF magic bytes found in CAT1!!


Now let’s view last hex values for CAT4 file:

*CAT4*


Now we can see that CAT1 has first magic bytes for a PDF file
and CAT4 has EOF marker for (End Of File), now we know that all 4 files are actually one PDF file, but divided into 4 files.


construct them easily using very simple piece of powershell code:


```
Get-Content CAT1, CAT2, CAT3, CAT4 -Encoding Byte -ReadCount 0 | Set-Content combined.pdf -Encoding Byte
```


now we can open the final PDF file to get the flag:


```
CATF{whip1@$h_iz_da_b3$t_m0v13_3va!}
```

---

*Originally published on [Medium](https://infosecwriteups.com/cat-reloaded-ctf-catf-2025-dfir-challenges-ff403f100504). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
