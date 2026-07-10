# :game_die: Ieee Victoris 4 0 Ctf 2025 Finals Dfir Challenges D1943C9A6Eb4

> **Original Source:** [Ieee Victoris 4 0 Ctf 2025 Finals Dfir Challenges D1943C9A6Eb4](https://infosecwriteups.com/ieee-victoris-4-0-ctf-2025-finals-dfir-challenges-d1943c9a6eb4)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2025

---

after extracting the downloadable image, i got soo lucky tbh that my AVG antivirus caught 2 exe files as malicious files`system_patch.exe `and`notepad++.exe`


thanks to AVG it helped me a lot, without digging or investigating each file or directory, we only to investigate these 2 malicious file paths, so let’s go.


first file deserve to investigate is `system_patch.exe`in `C:\ProgramData\sysbackup\` directory:


by reading this powershell file “`watchdog.ps1`”, we can understand that the script backs up the real `notepad++.exe`, drops a fake executable (`system_patch.exe`) in its place, and then runs an endless watchdog that checks every 10 seconds. If the target file gets changed back to the original or anything else, the script copies the fake back effectively forcing the fake binary to stay in place.
At the top it tries to add Windows Defender exclusions for the backup folder, `notepad++.exe`, and the fake process so antivirus might ignore those files.
with easy investigation on the `system_patch.exe`, run the most powerful tool “strings” , or reading hex data of the file, we can get the hidden flag.

---

*Originally published on [Medium](https://infosecwriteups.com/ieee-victoris-4-0-ctf-2025-finals-dfir-challenges-d1943c9a6eb4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
