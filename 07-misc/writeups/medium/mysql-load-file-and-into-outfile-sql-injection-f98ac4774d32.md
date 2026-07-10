# :game_die: MySQL LOAD_FILE() and INTO OUTFILE() Sql Injection

> **Original Source:** [MySQL LOAD_FILE() and INTO OUTFILE() Sql Injection](https://infosecwriteups.com/mysql-load-file-and-into-outfile-sql-injection-f98ac4774d32)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# MySQL LOAD_FILE() and INTO OUTFILE() Sql Injection


*Photo by [Sara Bakhshi](https://unsplash.com/@sarabakhshi?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*


In this article, we will discuss the MySQL LOAD_FILE() function and the INTO OUTFILE() function and Sql Injection. MySQL provides the LOAD_FILE() and INTO OUTFILE() functions that can be used to read or write files on the file system of the server where the MySQL database is running. These functions can be vulnerable to SQL injection attacks if user input is not properly sanitized.


An attacker could use SQL injection to modify the file path passed to the LOAD_FILE() or INTO OUTFILE() function to access or write to unauthorized files on the server. For example, an attacker could use SQL injection to read sensitive files on the server or to write malicious code to the server, potentially leading to further compromise of the system.


To prevent SQL injection attacks when using these functions, it’s important to properly validate and sanitize any user input used as a parameter in the function. Additionally, it’s also a good practice to use the least privileged MySQL user account when connecting to the database, as this will limit the potential damage that an attacker can do if they are able to successfully inject malicious SQL.


```
<?php
$file_path = $_GET['file'];
$sql = "SELECT * FROM users WHERE profile_picture = LOAD_FILE('" . $file_path . "')";
$result = mysqli_query($connection, $sql);
?>
```

---

*Originally published on [Medium](https://infosecwriteups.com/mysql-load-file-and-into-outfile-sql-injection-f98ac4774d32). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
