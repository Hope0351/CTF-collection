# :game_die: Introduction To Sql Injection F4F0911F3461

---

## What is SQL Injection?

SQL injection (SQLi) is a web security vulnerability that allows an attacker to interfere with the queries that an application makes to its database.

A parameter passing through HTTP Request is placed in a SQL query to fetch the user data. If the parameter is not properly sanitized then an attacker can modify that parameter in such a way, so that an attacker can get some sensitive or private information from the database.

## Impact of Successful SQL Injection Attack

- Unauthorized access to sensitive data, such as passwords, credit card details, or personal Identifiable information (PII), etc.

- Reputational damage and regulatory fines.

- persistent backdoors and permanent changes to application’s content or behavior.

## How to detect SQL Injection vulnerabilities?

Test the web-application by submitting special characters such as single quote ( ‘ ) or double quote ( “ ) to the URL Parameters or HTTP request parameters and look for any changes in the web-application.

If you see any changes between the original parameter response and response with special character parameter, that means the application endpoint can be vulnerable to SQL Injection.

## Types of SQL Injection

- In-band SQL Injection

- Blind SQL Injection

- Out-of-Band SQL Injection

- Second-order SQL Injection

### In-Band SQL Injection:

In-Band SQL Injection, also known as Classic SQL Injection, is the most common and easy to exploit of SQL Injection Attack.

It occurs when the attacker can able to use the same communication channel to both launch the attack and gather results.

There are two types of In-Band SQLi:

1. Error-Based SQLi

It relies on Error messages thrown by the database server when attacker inject malicious payload in the parameter to obtain information about the structure of the database.

2. Union-Based SQLi

It leverages the UNION SQL operator to combine the results of two or more SELECT statements into single result.

Using UNION-Based SQLi, Attacker can fetch data from different table in the database.

### Blind SQL Injection:

In this attack, application does not return the results of the SQL query or any errors within its response.

## Get PriOFF’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

There are some techniques that can be used to exploit blind SQL Injection vulnerabilities, but thay are generally more complicated and difficult to perform.

- Change the logic of the query to trigger a detectable difference in the application’s response.

- You can conditionally trigger a time delay in the processing of the query, this technique is known as Time-Based SQLi.

- You can inject a new condition into some Boolean logic, or conditionally triggering an error such as a divide-by-zero, this technique is known as Boolean-Based SQLi.

- Also, You can directly exfiltrate data via the out-of-band channel. For example, you can place the data into a DNS lookup for a domain that you own.

### Out-of-Band SQL Injection:

It is not very common, because it depends on the features being enabled on the database server being used by the web application.

Out-of-Band SQL Injection techniques relies on the database server’s ability to make DNS or HTTP requests to deliver data to an attacker.

Example:

- Microsoft SQL Server’s xp_dirtree command, which is used to make DNS requests to a server.

- Oracle Database’s UTL_HTTP package, which can be used to send HTTP requests from SQL and PL/SQL to a server an attacker controls.

### Second-order SQL Injection

First-order SQLi occurs when the application processes user input from an HTTP request and incorporates the input into a SQL query in unsafe way.

Second-order SQLi occurs when the application takes user input from an HTTP request and stores it for future use. This is usually done by placing the input into a database, but no vulnerability occurs at the point where the data is stored.

And Later on, when handling a different HTTP request, the application retrieves the stored data and incorporates it into a SQL query in unsafe way.

## How to prevent SQL Injection

Most instances of SQL injection can be prevent using parameterized queries instead of using string concatenation withing the query. These are known as “Prepared Statements”.

Example:

>

String concatenation

String query = “SELECT * FROM products WHERE category = ‘ ” + input + “ ‘ “;

Statement statement = connection.createStatement();

ResultSet resultSet = statement.executeQuery(query);

Prepared Statements

String query = “SELECT * FROM products WHERE category = ?”;

PreparedStatement statement = connection.prepareStatement(query);

statement.setString(1, input);

ResultSet resultSet = statement.executeQuery();

### References:

---
