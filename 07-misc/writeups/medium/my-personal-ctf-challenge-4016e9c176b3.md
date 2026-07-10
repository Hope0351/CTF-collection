# :game_die: HTTP Archive file

> **Original Source:** [HTTP Archive file](https://infosecwriteups.com/my-personal-ctf-challenge-4016e9c176b3)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

I opened the console to see GET requests with the source image request URLs. Awesome! I can download the images now,… but should I? They were NINE images, NINE links to be clicked and saved manually using more clicks. The math is too much! I decided to look for a more automated solution in case there’s ever a need to scale up. Enter HAR.


*never used it for its original purpose but this is a good start*


This HTTP Archive file, which can be exported from the Networks tab, is a JSON file containing [detailed performance data](https://confluence.atlassian.com/kb/generating-har-files-and-analyzing-web-requests-720420612.html) of the browser about the webpage it loads. This would include the image requests URLs I’m interested in. I’ve been looking for a way to collect request URLs like this for ever, and I’ve finally found it during this engagement.


*the servers keep changing so this HAR becomes obsolete in a few days*


After analyzing the JSON structure, I found which request URL values I need. It’s the one with host as ‘instagram.fdel11–1.fna.fbcdn.net’. I used jq for parsing through this JSON data, all 15,566 lines of it. I thought about using grep or awk or sed but I suppose they would have required a lot more tweaking. Plus I wanted to get better at jq, since I’ve only used it once before.


*finding string matching techniques*


I spent some time reading up on [how to traverse arrays](https://www.baeldung.com/linux/jq-command-json), creating a regex for [string matching the URL](https://zerokspot.com/weblog/2013/07/18/processing-json-with-jq/), also trying to resolve a recurring “error: test is not defined” . Let me know if you managed to solve this because I couldn’t get it working on my terminal. So I resorted to using their [online playground](https://jqplay.org/) for testing… A one-line bash command for extracting direct image URLs from the HAR file. And another one to download them.

---

*Originally published on [Medium](https://infosecwriteups.com/my-personal-ctf-challenge-4016e9c176b3). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
