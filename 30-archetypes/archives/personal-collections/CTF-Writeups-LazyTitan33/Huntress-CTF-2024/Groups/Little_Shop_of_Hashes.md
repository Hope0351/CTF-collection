# Little Shop of Hashes




Download: [little_shop_of_hashes_logs.zip](https://raw.githubusercontent.com/LazyTitan33/CTF-Writeups/refs/heads/main/Huntress-CTF-2024/challenge-files/little_shop_of_hashes_logs.zip)


## My Solution

This is a group of questions where we need to figure out the answers from the provided Windows Event Viewer logs.  

I'm sure that there are better ways to do this challenge however, what I usually do is I convert the `.evtx` files to something that is human readable. For this purpose I used the EvtxECmd.exe tool to convert the files to `.csv`.  

```bash
EvtxECmd.exe -f "C:\Temp\Application.evtx" --csv "c:\temp\out" --csvf MyOutputFile.csv
```

### Question 1: What is the name of the service that the attacker ran and stopped, which dumped hashes on the first compromised host?

Answer: `Remote Registry`

In the System logs of HostB we can see the Remote Registry service having been run and stopped. This is a service that `secretsdump.py` starts and stops when dumping hashes.



### Question 2: What lateral movement technique did the threat actor use to move to the other machine?

Answer: `Pass the Hash`

Since the attacker dumped hashes, it's logical to deduce that the attacker then used said hashes.

### Question 3: What is the full path of the binary that the threat actor used to access the privileges of a different user with explicit credentials?

Answer: `C:\\Users\\DeeDee\\Documents\\runasc.exe`

This can be seen in the Application logs of HostA.  



### Question 4: How many accounts were compromised by the threat actor?

Answer: `3`

In the Security logs from HOSTB and HOSTA, we filter based on EventID 4776 which is for NTLM authentication.



### Question 5: What is the full path of the binary that was used to attempt a callback to the threat actor's machine?

Answer: `C:\Users\DeeDee\Documents\nc.exe`

This can be seen in the Application logs of HostA:  


