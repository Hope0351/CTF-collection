# :game_die: Writeup Advent Of Cyber 2023 Day 5 A Christmas Doscovery Tapes Of Yule Tide Past

> **Original Source:** [Writeup Advent Of Cyber 2023 Day 5 A Christmas Doscovery Tapes Of Yule Tide Past](https://infosecwriteups.com/writeup-advent-of-cyber-2023-day-5-a-christmas-doscovery-tapes-of-yule-tide-past-dd1ea403cebb)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2023

---

### Answer the questions below


Q1) How large (in bytes) is the AC2023.BAK file?


Open the `DOSBox-X`


use `dir` cmd to list the contents

>

ANS: 12,704


Q2) What is the name of the backup program?


go to `TOOLS` folder using `cd TOOLS`
Then list the content using `dir` command
Then go to `BACKUP` folder using `cd BACKUP`
Then use `edit README.TXT` to view the content of readme file


TO exit enter `ALT + F` and exit

>

ANS: BackupMaster3000


Q3) What should the correct bytes be in the backup’s file signature to restore the backup properly?


use `BUMASTER.EXE` to run `AC2023.bak` file. which gives us error and tells to check troubleshooting notes inside `README.TXT` so again open the readme.txt file


TO exit enter `ALT + F` and exit

>

ANS: 41 43


Q.4) What is the flag after restoring the backup successfully?


we have to convert `41 43` from hexadecimal to ASCII. which is `AC`


## Get dollarboysushil’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


now open the `AC2023.BAK` and replace 1st two character from `XX` to `AC`


Then again run the `AC2023.BAK` file using `BUMASTER.EXE` . This time there will not be any error.


And we got the flag.

>

ANS: THM{0LD_5CH00L_C00L_d00D}

---

*Originally published on [Medium](https://infosecwriteups.com/writeup-advent-of-cyber-2023-day-5-a-christmas-doscovery-tapes-of-yule-tide-past-dd1ea403cebb). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
