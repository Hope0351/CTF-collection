# :globe_with_meridians: Beginner’s Guide: Defend the Web SQLi 1–2 CTF Challenges

> **Original Source:** [Beginner’s Guide: Defend the Web SQLi 1–2 CTF Challenges](https://infosecwriteups.com/beginners-guide-defending-web-sqli-1-2-ctf-challenges-7dfe4dd2acab)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Beginner’s Guide: Defend the Web SQLi 1–2 CTF Challenges


*Created by lexica.art*

## SQLi 1 / SQLi


To solve the “`Gain access to any user's account`" CTF challenge, we need to exploit a SQL Injection vulnerability in the login system. The challenge provides us with the username "`user`" and suggests that the vulnerability is related to SQL Injection.


To get around the password check and access the account, we may insert SQL code into the password box of the login form. We may disregard the rest of the query and insert our own code by using a popular approach that combines the “`OR`" operator with the comment sign (`--`).


To do this, we can enter the following code into the password field:


`' OR 1 -- -`


Without a working password, this code will go past the password verification and provide us access to the user account. In the real world, SQL Injection may be quite hazardous, thus it’s crucial to take precautions to safeguard your systems from this and other widespread vulnerabilities.

## SQLi 2 / SQLi


Finding the weakness is the first step in solving the issue. SQL Injection is the flaw in this case, allowing you to bypass authentication and access the website by inserting malicious SQL code into the login form.


The usernames are then enumerated using a URL with a SQL Injection payload. Enter the following payload into the URL to do this:


“`<https://defendtheweb.net/playground/sqli2?q=A>' OR 1 -- -`”


The ‘OR’ operator is used in this payload to return all usernames from the database. The remainder of the SQL query is commented out and any mistakes are avoided using the double hyphen at the end of the payload.


Finding the administrator’s username comes after listing all the usernames. Enter the following payload into the URL to do this:


## Get Ahmet Talha Şen’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


“`<https://defendtheweb.net/playground/sqli2?q=A>' OR admin = 1 -- -`”


The ‘OR’ operator is used in this payload to determine whether the database’s ‘admin’ field is set to 1, indicating that the user is an administrator. The administrator’s username should be the only one visible after running the payload.


`‘bellamond`' is the username of the administrator in this instance.


The next step is to extract the administrator’s password hash now that you are aware of their username. Enter the following payload into the URL to do this:


“`<https://defendtheweb.net/playground/sqli2?q=>' UNION ALL SELECT password,2 FROM members WHERE admin='1';--`”


This payload combines two choose statements, one to choose the password field and another to select a random field, in this case ‘`2`', using the '`UNION`' operator. Only the password for the administrator's account is returned when the results are filtered using the `WHERE` clause.


You should see a hash code, which is the administrator’s password’s SHA1 hash, after running the payload. ‘`1b774bc166f3f8918e900fcef8752817bae76a37`' is the hash code in this instance.


The administrator’s account must be accessed by decrypting the password hash. You may accomplish this by using an online SHA1 decrypter tool, which will try to decipher the hash and provide the password’s plaintext.


You should be able to view the plaintext password — in this case,’`sup3r`'—after passing the hash code through the decryptor. With this password, you may now access the website as an administrator and finish the task.

---

*Originally published on [Medium](https://infosecwriteups.com/beginners-guide-defending-web-sqli-1-2-ctf-challenges-7dfe4dd2acab). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
