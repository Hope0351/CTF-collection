# :game_die: BSQL Injection Shenanigans(Tool&Manual Method)

> **Original Source:** [BSQL Injection Shenanigans(Tool&Manual Method)](https://infosecwriteups.com/bsql-injection-shenanigans-d6bd545d475a)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

## LAB 1


I started with the first lab which provided us a search query to get email by using username.


*Search*


I searched for Jeremy, and it showed me email related to Jeremy.


I added Jeremy’ and searched, but no user was found. Let’s try another payload to verify if it is vulnerable to SQL injection via Burp Suite.


This is how the web app is making its request whenever I search for a user:


```
SELECT * FROM Email WHERE User = jeremy
```


I tried jeremy’ — — and i got jeremy email back only but i think am missing something.


I tired to comment whatsoever comes after it by using this payload:


```
jeremy' OR '1'=1-- -

```


which will comment everything after our query and i got 3 users email as response.


Em voilà


*Payload success*

## LAB2


I spent a lot of time here.


We are provided with a login interface with default credentials:
jeremy:jeremy


*default cred*


I tried jeremy’ OR ‘1’=1 — — so It will ignore the password, but it’s not working, so I log in normally.


When I log in, I receive a welcome message because the web app recognizes me using a cookie.


*Welcome page*


I once watched a Rana Khalil video on using the UNION statement. Since I watched Rana’s video on SQL injection, I decided to check if the cookie is vulnerable to SQLi. People don’t usually test the cookies parameter, so I used ‘ and 1=1 — — to test for blind SQL injection. We need to use booleans to make the web app communicate with us using the true or false method or use time-based techniques to check if it is vulnerable.


```
' AND SLEEP(20)
```


Em Voila:) It is vulnerable.


*Time based*


I couldn’t use Union for this lab2, so I had to go back to lab1 to get the number of columns in the table.


## Get callgh0st’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Rules for using UNION Statement

>

1. Number of columns
2. Must be same data type


Rule 1: order by 1 — — I changed it to 2, then to 3, but when I changed it to 4, I got no users, so I know I have 3 columns.


Rule 2: ‘ UNION select ‘a’,’a’,’a’ — — to confirm if they are of same datatype. They are all same datatype. They are all strings.


I now know that there is a table named Users, columns > username, password, email and username-bob,jeremy,jessamy.


I wanted to try manual method for dumping the table but it was not successful though i tried diff payloads but none was working.


It time to automate. I saved the request file then use sqlmap on it to dump the database.


```
sqlmap -r r --dbms=mysql --dump -p session
```


- -r : flag specifying i am using request file

- r : Name of file

- —-dbms=mysql : Name of Database

- — -dump : To dump all data

- -p session: Name of vulnerable Parameter.


now it dumps all the tables for all the lab so i check our lab and it proved me right.


This would lead to massive account takeovers.

---

*Originally published on [Medium](https://infosecwriteups.com/bsql-injection-shenanigans-d6bd545d475a). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
