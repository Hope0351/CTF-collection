# :game_die: SQL Injection

---

# SQL Injection

## How to detect and exploit SQL Injection vulnerabilities.

Structured Query Language (SQL) Injection, or SQLi, is a web security vulnerability that allows an attacker to interfere with queries an application performs to its database.

*This method will allow attackers to view data that is typically not accessible. This data may belong to other users or any other data that the application can access.*

An attacker can often delete or modify this data, which may permanently alter the application’s behavior.

### How to detect SQL injection vulnerabilities

SQL injection can detected manually by using a systematic set of tests against every entry point in the application.

For example, you can submit a quote” ‘ “ character and look for errors or misbehavior.

You may also use boolean conditions such as “OR 1=1” and “OR 1=2” to check how the application responds.

Suppose you prefer using tools to find most SQL injection vulnerabilities. In that case, you can use [Burp Scanner](https://portswigger.net/burp/documentation/scanner) or [sqlmap](https://sqlmap.org/), which are designed to replicate the actions and methodologies of a skilled manual tester.

*It is better to do it manually for a better understanding. Tools are handy and automate processes, but they come and go.*

### SQL injection in different parts of the query

---
