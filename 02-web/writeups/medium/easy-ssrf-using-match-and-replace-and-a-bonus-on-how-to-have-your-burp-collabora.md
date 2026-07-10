# :globe_with_meridians: Easy SSRF using Match and Replace, and a bonus on how to have your burp collaborator/server go crazy

> **Original Source:** [Easy SSRF using Match and Replace, and a bonus on how to have your burp collaborator/server go crazy](https://infosecwriteups.com/easy-ssrf-using-match-and-replace-and-a-bonus-on-how-to-have-your-burp-collaborator-server-go-b5210037a101)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Easy SSRF using Match and Replace, and a bonus on how to have your burp collaborator/server go crazy


Match and Replace part is present in both paid and free editions of burp, and combined with the below link this should be useful for everyone.


Here’s one of the free alternatives to burp collaborator:


Now, there are two ways to go about it, and one of them is pretty dumb, but it might still work :)


The smart way — Part 1
So, I registered at the target website, and it had an area with templates. You could either upload your own logos or use the ones provided by the target website. Now, I usually don’t really care about those, mostly because it’s just images and it’s usually hard coded inside img src so even getting an interesting text file, it wouldn’t result in a readable result. But, I wanted to challenge myself to see if I could get something like gopher ssrf even with having control over img src and nothing else (as per h1 reports[]). But, I first had to determine if there was a “regular” pingback through img src that was coming from internal ip or any ip related to the target instead of it coming from my own ip.
In order to determine what exactly to use for Match and Replace website, I chose one of the website provided logos…

---

*Originally published on [Medium](https://infosecwriteups.com/easy-ssrf-using-match-and-replace-and-a-bonus-on-how-to-have-your-burp-collaborator-server-go-b5210037a101). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
