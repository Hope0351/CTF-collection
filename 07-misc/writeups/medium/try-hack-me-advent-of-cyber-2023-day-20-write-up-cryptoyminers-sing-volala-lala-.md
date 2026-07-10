# :game_die: Try Hack me - Advent Of Cyber 2023 Day 20 Write Up - Advent of Frostlings

> **Original Source:** [Try Hack me - Advent Of Cyber 2023 Day 20 Write Up - Advent of Frostlings](https://infosecwriteups.com/try-hack-me-advent-of-cyber-2023-day-20-write-up-cryptoyminers-sing-volala-lala-latility-726e314b5868)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2023

---

Room: [Advent of Cyber 2023 Day](https://tryhackme.com/room/adventofcyber2023)20


*[Try Hack me — Advent Of Cyber 2023 Day 20 Write Up](https://medium.com/@leendertcoenen/try-hack-me-advent-of-cyber-2023-day-1-write-up-a163ed214858) — Advent of Frostlings*


Similar to Jenkins on day 12, I touch on Gitlab for the first time. VCS’s like Github are familiar to me. But I haven’t yet worked in a big team that used Gitlab.


## Get Leendert Coenen’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Learning about Gitlab and CI/CD, we find that there has been some poison pipeline execution in the automation of Antarticraft.

### Task 1: What is the handle of the developer responsible for the merge changes?


Looking in the merge requests overview we can find the handle of the developer.


*Handle of Frostlino*

### Task 2: What port is the defaced calendar site server running on?


Given the port number in de docker command, we can find the defaced website. And it is also the answer to Task 2.


*Gitlab config file*


And what a treat this website is.


*Defaced website*

### Task 3: What server is the malicious server running on?


I didn’t blur this answer out, so it’s right there in the write up. TryHackMe mentioned this popular server software aswell!

### Task 4: What message did the Frostlings leave on the defaced site?


Again, I didn’t blur this answer out, so it’s right there in the write up. A real treat.

### Task 5: What is the commit ID of the original code for the Advent Calendar site?


Checking all commits we can see that on the sixth of december we have a commit by Delf Lead. An account we trust.


*Commits in Gitlab*


In this specific commit we see that almost all of the original code was added.


*Commit from Delf Lead*


Which means this commit’s ID will be the answer to Task 5.


Happy Hacking!


*💡 If you want to stay updated with what I’m working on. Follow me and Subscribe! 🔔*


[Medium](https://medium.com/@leendertcoenen/subscribe)— [LinkedIn](https://www.linkedin.com/in/coenenleendert/) — [Twitter](https://twitter.com/LeendertCoenen)— [Substack](https://leendert.substack.com/)

---

*Originally published on [Medium](https://infosecwriteups.com/try-hack-me-advent-of-cyber-2023-day-20-write-up-cryptoyminers-sing-volala-lala-latility-726e314b5868). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
