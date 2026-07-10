# :globe_with_meridians: Blind Sql Injection In Oracle Database Exfiltrating Data With Burp Collaborator 

> **Original Source:** [Blind Sql Injection In Oracle Database Exfiltrating Data With Burp Collaborator ](https://infosecwriteups.com/blind-sql-injection-in-oracle-database-exfiltrating-data-with-burp-collaborator-sql-injection-2b8062b04d51)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## Steps to Reproduce & Proof of Concept (POC)


1. Open the Lab


2. Visit one of the available product categories. In this example, we will use the Accessories category:


```
https://<your-lab-id>.web-security-academy.net/filter?category=Accessories
```


3. Open Burp Suite and go to the HTTP History tab. Right-click the request and select Send to Repeater for further testing


4. The application stores user credentials in a users table with two key columns:


Since we already know the structure of the database, our goal is to extract the administrator’s password using an out-of-band (OOB) SQL Injection payload.


## Get Bash Overflow’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


5. You can leverage PortSwigger’s SQL Injection Cheat Sheet for payload ideas. The following Oracle SQL Injection payload will attempt to trigger an external request to Burp Collaborator, allowing us to exfiltrate data:


6. First, test the payload by extracting the password for the Wiener user and sending it to Burp Collaborator:


7. Once the Wiener password retrieval is successful, modify the payload to extract the administrator’s password:


8. Use the extracted credentials to log in to the application as the administrator


9. Once logged in, you have successfully completed the lab


10. If you want to further test the exploit, try retrieving the database name using this query:


---

*Originally published on [Medium](https://infosecwriteups.com/blind-sql-injection-in-oracle-database-exfiltrating-data-with-burp-collaborator-sql-injection-2b8062b04d51). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
