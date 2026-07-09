 Photo Gallery CTF Challenge Writeup 🚀

 CTF Details

- CTF Name: Photo Gallery
- Resource: Hacker101 CTF
- Difficulty: Moderate
- Number of Flags: 3

📢 Note: NO, I won’t be posting my found FLAGS, but I will be posting the methods I used.

---

 Introduction

Hey everyone! I'm Divyanshu Kumar, a cybersecurity enthusiast. In this post, I’ll walk you through my experience solving the Photo Gallery CTF challenge. This is part of my series where I explore cybersecurity concepts through CTF (Capture The Flag) walkthroughs.

⚠️ Disclaimer: I’m still learning, and these posts are meant to document and share my knowledge as I grow in the cybersecurity field. Now, let’s dive into the challenge! 🕵️‍♂️

---

 Understanding SQLMap 🛠️

`sqlmap` is a powerful open-source penetration testing tool that automates the process of detecting and exploiting SQL injection vulnerabilities. It helps security researchers and ethical hackers extract database information, dump data, and even gain administrative access if misconfigurations exist.

In this challenge, I leveraged `sqlmap` to exploit an SQL injection vulnerability and retrieve critical information. Let's go step by step!

 Steps to Use SQLMap

1. Identify a Potential SQL Injection Point
   - The challenge had a `fetch` endpoint that took an `id` parameter, making it a great candidate for SQL injection.

2. Run SQLMap with Basic Enumeration
   - I ran the following command to test if the endpoint was vulnerable:
     
     ```
     sqlmap -u https://<IP>/fetch?id=1 --dbs --batch
     ```
   - This command attempts to extract database names.

3. Increase the Level and Risk for More Aggressive Testing
   - To dig deeper, I used:
     
     ```
     sqlmap -u https://<IP>/fetch?id=1 -dump --level=5 --risk=3 --banner --batch --dbs
     ```
   - `--level=5` increases the number of payloads tested.
   - `--risk=3` increases the risk level to perform more intrusive tests.
   - `--banner` extracts database information.
   - `--dbs` lists all available databases.
   - `-dump` dumps the contents of the database.

4. Extract Data and Find the Flag
   - The enumeration revealed two tables: `albums` and `photos`.
   - Dumping the `photos` table led me to discover Flag 0.

 Flag 0 🏴

To extract data and retrieve the flag, I used the following `sqlmap` command:

```
sqlmap -u https://<IP>/fetch?id=1 -dump --level=5 --risk=3 --banner --batch --dbs
```

Executing the `sqlmap` command successfully enumerated the database and revealed two tables: `albums` and `photos`. Dumping data from the `photos` table, I discovered the first flag.

![image](https://github.com/user-attachments/assets/8bd5e962-7870-4741-afe3-5dcd9489d0e7)


---

 Flag 1 🏴

Initially, I attempted several `UNION` payloads without success. Checking the given hint led me to a GitHub repository containing the `uwsgi` configuration:

Hint:

[https://github.com/tiangolo/uwsgi-nginx-flask-docker](https://github.com/tiangolo/uwsgi-nginx-flask-docker)

From this repository, I found that `module = main` pointed to a file named `main.py`. I then used the following payload to retrieve the file:

```
fetch?id=0+UNION+SELECT+'main.py'
```

Executing this payload revealed the second flag.



---

 Flag 2 🏴

This challenge was particularly difficult. After multiple failed attempts and significant time spent, I decided to move on and learn from the available solutions rather than continuing blindly.

Flag 2: Unsolved (Will revisit for learning purposes)

---

 Conclusion 🎯

This challenge provided an insightful experience in SQL injection exploitation, understanding `uwsgi` configurations, and analyzing server-side file structures. While Flag 2 remained unsolved, it was a valuable learning opportunity that I will revisit in the future.

Stay tuned for more CTF write-ups and ethical hacking adventures! 🕵️‍♂️💻

