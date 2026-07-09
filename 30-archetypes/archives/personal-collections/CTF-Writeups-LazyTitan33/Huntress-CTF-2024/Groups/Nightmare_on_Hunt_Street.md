# Nightmare on Hunt Street



Download: [logs-parts1-5.zip](https://raw.githubusercontent.com/LazyTitan33/CTF-Writeups/refs/heads/main/Huntress-CTF-2024/challenge-files/logs-parts1-5.zip)

## My Solution

This is a group of questions where we need to figure out the answers from the provided Windows Event Viewer logs.  



I'm sure that there are better ways to do this challenge however, what I usually do is I convert the `.evtx` files to something that is human readable. For this purpose I used the EvtxECmd.exe tool to convert the files to `.csv`.  

```bash
EvtxECmd.exe -f "C:\Temp\Application.evtx" --csv "c:\temp\out" --csvf MyOutputFile.csv
```

The data, or Payload, is all now in one column:  



### Question 1: What is the IP address of the host that the attacker used?

Answer: `10.1.1.42`



### Question 2: How many times was the compromised account brute-forced? Answer just the integer value.

Answer: `32`

A quick google or just general knowledge tells us that brute force attacks can be identified by looking for the Event log failure Ids of `4625`:  



We filter those and can see the number of times this shows up in the logs.

### Question 3: What is the name of the offensive security tool that was used to gain initial access? Answer in all lowercase.

Answer: `psexec`

In the logs we can see a .exe binary with a random name which is a strong indicator of psexec. This tools creates these kinds of files when getting a foothold:  



### Question 4: How many unique enumeration commands were run with net.exe? Answer just the integer value.

Answer: `3`

I noticed the `net` command being used so I opened the .csv file in sublime and looked for unique instances of it being used.

First time it is used to enumerate the users on the machine:  



Second time it is used to enumerate the groups on the machine:  



Third time it is used to enumerate the shares on the machine:  



### Question 5: What password was successfully given to the user created?

Answer: `Susan123!`

We know that the EventID for a password reset is 4724 so when looking for it, we can only see one instance at 11:53.9:  



A quick look in the logs for activity around that time, we can see the password:  



