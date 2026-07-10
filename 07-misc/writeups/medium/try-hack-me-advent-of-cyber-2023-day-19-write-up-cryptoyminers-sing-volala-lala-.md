# :game_die: Try Hack me - Advent Of Cyber 2023 Day 19 Write Up - CrypTOYminers Sing Volala-lala-latility

---

Room: [Advent of Cyber 2023 Day](https://tryhackme.com/room/adventofcyber2023)19

*Try Hack me — Advent Of Cyber 2023 Day 19 Write Up — CrypTOYminers Sing Volala-lala-latility*

Yesterday we killed the process of a cryptocurrency miner on one of the Linux database servers. Today we’ll investigate this process and how it got onto the server in the first place.

A memory dump is a snapshot of memory that has been captured to perform memory analysis. It will contain data relating to running processes, captured when the memory dump was created.

The advantage of memory forensics is that volatile data is usually not on disk, but in memory. It’s size is also a lot smaller than disk size, increasing the speed of the analysis.

After the analysis we uncover some troublesome evidence, the next question that arises from this incident is: “Are the pipelines safe?”

### Task 1: What is the exposed password that we find from the bash history output?

After creating a custom Linux profile, which we need because there are so many Linux Distro that it’s impossible to make one off the shelve, we take a look at the command history using Volatility.

*Using Volatility to see command history*

Here we find the answer to Task 1, which is the password to the mysql server.

We also notice that someone entered a command to download and run a cryptocurrency miner?!

### Task 2: What is the PID of the miner process that we find?

Using the plugin linux_plslist we can see the miner is running.

*Using Volatility to see running processes*

This provides the answer to Task 2.

## Get Leendert Coenen’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Also there is mysqld and mysqlserver running, that last one being something someone named themselves.

### Task 3: What is the MD5 hash of the miner process?

To further understand the suspicious processes, we’ll extract their binaries in a new folder.

```
mkdir extracted
```

*Extracting binaries with Volatility*

What is an MD5 hash?

Md5sum is used to verify the integrity of files, as virtually any change to a file will cause its MD5 hash to change. Most commonly, md5sum is used to verify that a file has not changed as a result of a faulty file transfer, a disk error or non-malicious meddling.

Transforming to md5 is built into linux, we can transform the 2 suspicious processes from which we just extracted the binaries, so we can send them to McSkiddy in md5 hash format and be sure nothing went wrong a long the way.

*md5 hash miner*

### Task 4: What is the MD5 hash of the mysqlserver process?

*md5 hash mysqlserver*

### Task 5: Use the command `strings extracted/miner.<PID from question 2>.0x400000 | grep http://`. What is the suspicious URL? (Fully defang the URL using CyberChef)

Using the string command on the extracted binary, we find a suspicous URL. Because it’s suspicious, we defang the URL before copy/paste or sharing it to anyone.

*Using cyberchef to defang the url*

### Task 6: After reading the elfie file, what location is the mysqlserver process dropped in on the file system?

First we’ll use the linux_enumerate_files plugin from Volatility, and take everything that contains “cron”, to find where possible cronjobs are located.

*Finding the cron directory*

Next we’ll use the linux_find_file plugin from Volatility, so we can extract that file. and print out it’s contents, which gives us the answer to Task 6.

*Readin the Elfie file*

Happy Hacking!

*💡 If you want to stay updated with what I’m working on. Follow me and Subscribe! 🔔*

Medium— [LinkedIn](https://www.linkedin.com/in/coenenleendert/) — [Twitter](https://twitter.com/LeendertCoenen)— [Substack](https://leendert.substack.com/)

---
