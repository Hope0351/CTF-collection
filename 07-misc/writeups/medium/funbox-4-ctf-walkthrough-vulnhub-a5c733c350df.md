# :game_die: Funbox-4: CTF Walkthrough (Vulnhub)

---

# Funbox-4: CTF Walkthrough (Vulnhub)

Groundhog Day: Boot2Root! Created by [@0815R2d2](https://twitter.com/@0815R2d2).The initial footstep is a bit flawed, but really not difficult. After getting access to Funbox: CTF, its necessary to find, read, and understand the (2 and easy to find) hints. Be smart and combine… and always be careful from the rabbit holes. To download the machine visit [https://www.vulnhub.com/entry/funbox-ctf,546/](https://www.vulnhub.com/entry/funbox-ctf,546/)

My recommendation for solving this machine is on Virtualbox but as stated “Curiosity keeps leading us down new paths — Walt Disney” So, you can try VMware, also you can redo the challenge and find your own way gaining root access.

>

Knowledge Gained:-

- Enumeration

- Reverse shell

- Creating a unique wordlist

- Bypass rbash

- Searching and using an exploit

>

Port Scanning

After identifying the intended victim let’s run a Nmap scan to find the open ports and services running.

>

Web Reconnaissance

Visiting the home page of the victim on port 80 shows a default page of Ubuntu and has nothing useful. So, I tried gobuster…

---
