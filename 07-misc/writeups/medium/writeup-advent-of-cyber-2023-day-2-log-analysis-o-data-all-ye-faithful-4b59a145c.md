# :game_die: Writeup Advent Of Cyber 2023 Day 2 Log Analysis O Data All Ye Faithful 4B59A145C

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
