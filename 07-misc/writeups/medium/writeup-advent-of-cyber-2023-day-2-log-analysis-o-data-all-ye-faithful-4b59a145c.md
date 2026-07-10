# :game_die: Writeup Advent Of Cyber 2023 Day 2 Log Analysis O Data All Ye Faithful 4B59A145C

> **Original Source:** [Writeup Advent Of Cyber 2023 Day 2 Log Analysis O Data All Ye Faithful 4B59A145C](https://infosecwriteups.com/writeup-advent-of-cyber-2023-day-2-log-analysis-o-data-all-ye-faithful-4b59a145ca01)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2023

---

### A*nswer the questions below*


Q1) Open the notebook “Workbook” located in the directory “4_Capstone” on the VM. Use what you have learned today to analyze the packet capture.

>

ANS: No Answer Needed


## Get dollarboysushil’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Q2) How many packets were captured (looking at the PacketNumber)?


Here we are using `.count()` method on dataframe `df` which prints the size.

>

ANS: 100


Q3) What IP address sent the most amount of traffic during the packet capture?


Question is asking for the IP address which sent the most amount of traffic.
For which we can use `.groupby()` method with column name `Source` as the argument to group it by the ‘Source’ column. Further we are using `.size()` method to get the count of occurrences in each group.

>

ANS: 10.10.1.4


Q4) What was the most frequent protocol?


To find the most frequent protocol we are using `value_counts()` method on the `'Protocol' `column of a DataFrame which will print a Series containing counts of unique values in the ‘Protocol’ column

---

*Originally published on [Medium](https://infosecwriteups.com/writeup-advent-of-cyber-2023-day-2-log-analysis-o-data-all-ye-faithful-4b59a145ca01). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
