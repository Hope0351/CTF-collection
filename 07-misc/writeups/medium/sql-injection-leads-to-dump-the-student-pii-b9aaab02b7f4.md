# :game_die: SQL Injection Leads to dump the Student PII

> **Original Source:** [SQL Injection Leads to dump the Student PII](https://infosecwriteups.com/sql-injection-leads-to-dump-the-student-pii-b9aaab02b7f4)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# SQL Injection Leads to dump the Student PII


Hello Friend…!


In this writeup I will tell you how I found the SQLi in the educational website.


Let’s begin,


I was testing one educational website where I found the one endpoint like *down.html* where student need university number to download the receipts. I searched online about the college and found the university number of top students, which I used to download the receipts.


*download receipt page*


after entering the university number I can see the student fees history and I clicked the one receipt number which is opened in url with parameter


## Get Cyb3rV0lt’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


*?no=52*


*receipt*


so I just put the special characters to see the response of the page where I got mysql error while using the apostrophe(‘).


*mysql error*


after getting this error I didn’t wasted the time, used sqlmap to automate the task and dumped the database and got the students PII.


*database names*


*Students PII*


I tried for os-shell injection but didn’t have permission to WRITE FILE.


that it, Thank you.


Subscribe my [youtube channel](https://youtube.com/@cybervolt07?si=VEaOW8Oevzn6Ld7p)

---

*Originally published on [Medium](https://infosecwriteups.com/sql-injection-leads-to-dump-the-student-pii-b9aaab02b7f4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
