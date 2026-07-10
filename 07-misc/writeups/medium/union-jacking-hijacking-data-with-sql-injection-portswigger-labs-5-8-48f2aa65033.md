# :game_die: UNION Jacking: Hijacking Data with SQL Injection (PortSwigger Labs 5-8)

> **Original Source:** [UNION Jacking: Hijacking Data with SQL Injection (PortSwigger Labs 5-8)](https://infosecwriteups.com/union-jacking-hijacking-data-with-sql-injection-portswigger-labs-5-8-48f2aa650330)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# UNION Jacking: Hijacking Data with SQL Injection (PortSwigger Labs 5–8)


## In the Name of Allah, the Most Beneficent, the Most Merciful.
All the praises and thanks be to Allah, the Lord of the ‘Alamin (mankind, jinns and all that exists).


Here we are again with the continuation of [PortSwigger SQLi Labs](https://portswigger.net/web-security/all-labs#sql-injection).


I will attach the links to the previous labs’ write-ups at the end of this write-up.


## Lab5: [SQL injection UNION](https://portswigger.net/web-security/sql-injection/union-attacks) attack, determining the number of columns returned by the query


This lab contains a SQL injection vulnerability in the product category filter. The results from the query are returned in the application’s response, so you can use a UNION attack to retrieve data from other tables. The first step of such an attack is to determine the number of columns that are being returned by the query. You will then use this technique in subsequent labs to construct the full attack.


To solve the lab, determine the number of columns returned by the query by performing a SQL injection UNION attack that returns an additional row containing null values.

### Solution


Select any category and inject your payload.


In the first step, we need to determine the number of columns returned by the query. I used ‘ORDER BY’ to obtain the number of columns and their respective data types.


```
' ORDER BY 3-- -
```


*ORDER BY 3 — -*


I was able to get 3 columns, but upon checking the data types, they are not all strings.

>

NOTE: We already got the number or columns using ORDER BY but you have to use the following payload to solve the lab.


```
' UNION SELECT NULL,NULL,NULL-- -
```


NULL matches all data type.


## Lab6: [SQL injection UNION](https://portswigger.net/web-security/sql-injection/union-attacks) attack, finding a column containing text


This lab contains a SQL injection vulnerability in the product category filter. The results from the query are returned in the application’s response, so you can use a UNION attack to retrieve data from other tables. To construct such an attack, you first need to determine the number of columns returned by the query. You can do this using a technique you learned in a [previous lab](https://portswigger.net/web-security/sql-injection/union-attacks/lab-determine-number-of-columns). The next step is to identify a column that is compatible with string data.


The lab will provide a random value that you need to make appear within the query results. To solve the lab, perform a SQL injection UNION attack that returns an additional row containing the value provided. This technique helps you determine which columns are compatible with string data.

### Solution


I smiled when I saw this and am already constructing payloads in my head. I planned on using “NULL” then switching other “NULL” to text until I found where it is compatible with text using the following, one after the other.


```
' UNION SELECT NULL,NULL,'zEPbgC'-- -
' UNION SELECT 'zEPbgC',NULL,NULL-- -
' UNION SELECT NULL,'zEPbgC',NULL-- -
```


The final payload works.


## Lab7: [SQL injection UNION](https://portswigger.net/web-security/sql-injection/union-attacks) attack, retrieving data from other tables


This lab contains a SQL injection vulnerability in the product category filter. The results from the query are returned in the application’s response, so you can use a UNION attack to retrieve data from other tables. To construct such an attack, you need to combine some of the techniques you learned in previous labs.


## Get callgh0st’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The database contains a different table called `users`, with columns called `username` and `password`.


To solve the lab, perform a SQL injection UNION attack that retrieves all usernames and passwords, and use the information to log in as the `administrator` user.

### Solution


Simple. We need to get the number of columns and check their data type.


Select any category and our possible payload:


```
' UNION SELECT username,password FROM users-- -
```


## Lab8: [SQL injection UNION](https://portswigger.net/web-security/sql-injection/union-attacks) attack, retrieving multiple values in a single column


This lab contains a SQL injection vulnerability in the product category filter. The results from the query are returned in the application’s response so you can use a UNION attack to retrieve data from other tables.


The database contains a different table called `users`, with columns called `username` and `password`.


To solve the lab, perform a SQL injection UNION attack that retrieves all usernames and passwords, and use the information to log in as the `administrator` user.

### Solution


We are basically doing the same thing as the previous lab but with a few differences. We need to retrieve multiple values together within a single column by concatenating the values. I checked the [SQL injection cheatsheet](https://portswigger.net/web-security/sql-injection/cheat-sheet) for how to concatenate in MySQL.


I spent a lot of time trying to get it right. I tried to concatenate in MySQL the right way, but it wasn’t working. I started to think if something was wrong with the lab until I checked the solution, and it dawned on me that the database is Oracle, not MySQL.

*OH NOOO*


I checked the number of columns to be two, with one string using:


```
' UNION SELECT NULL,NULL--
```


```
' UNION SELECT NULL,'abc'--
```


using this payload to retrieve username and password:


```
' UNION SELECT NULL,username || '¬' || password FROM users--
```


You might be wondering why we don’t remove NULL and insert a username or password in it? So, where we had our string ‘abc’ is the injection point, from my understanding. You can correct me if I am wrong.


That’s all for now. Thank you for reviewing the write-up.


Flood me with 50 likes if you enjoy the write-up. :)

>

*For any suggestions or Correction, Kindly reach out to me:*


*Twitter — ***[callgh0st](https://twitter.com/callgh0st)

---

*Originally published on [Medium](https://infosecwriteups.com/union-jacking-hijacking-data-with-sql-injection-portswigger-labs-5-8-48f2aa650330). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
