# :globe_with_meridians: THM - Anonforce. boot2root machine for FIT and bsides…

> **Original Source:** [THM - Anonforce. boot2root machine for FIT and bsides…](https://infosecwriteups.com/thm-anonforce-874016c34a0f)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# THM — Anonforce


## boot2root machine for FIT and bsides guatemala CTF


*Photo by [Matt Walsh](https://unsplash.com/@two_tees?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

## Enumeration


## Nmap


```
# nmap -T5 -p 21,22 -A 10.10.24.206

Starting Nmap 7.80 ( <https://nmap.org> ) at 2025-01-21 18:22 GMT
Nmap scan report for 10.10.24.206
Host is up (0.00034s latency).
PORT STATE SERVICE VERSION
21/tcp open ftp vsftpd 3.0.3
| ftp-anon: Anonymous FTP login allowed (FTP code 230)
| drwxr-xr-x 2 0 0 4096 Aug 11 2019 bin
| drwxr-xr-x 3 0 0 4096 Aug 11 2019 boot
| drwxr-xr-x 17 0 0 3700 Jan 21 10:02 dev
| drwxr-xr-x 85 0 0 4096 Aug 13 2019 etc
| drwxr-xr-x 3 0 0 4096 Aug 11 2019 home
| lrwxrwxrwx 1 0 0 33 Aug 11 2019 initrd.img -> boot/initrd.img-4.4.0-157-generic
| lrwxrwxrwx 1 0 0 33 Aug 11 2019 initrd.img.old -> boot/initrd.img-4.4.0-142-generic
| drwxr-xr-x 19 0 0 4096 Aug 11 2019 lib
| drwxr-xr-x 2 0 0 4096 Aug 11 2019 lib64
| drwx------ 2 0 0 16384 Aug 11 2019 lost+found…
```

---

*Originally published on [Medium](https://infosecwriteups.com/thm-anonforce-874016c34a0f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
