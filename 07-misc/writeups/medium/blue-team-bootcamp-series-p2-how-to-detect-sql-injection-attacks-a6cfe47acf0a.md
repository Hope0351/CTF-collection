# :game_die: Blue Team Bootcamp Series (P2): How to Detect SQL Injection Attacks

---

# Blue Team Bootcamp Series (P2): How to Detect SQL Injection Attacks

Hello Friend :)

## Get Ali AK’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Welcome again to the second part of the “Blue Team Bootcamp Series”. In this part, we are going to cover the common WEB Attacks such as XSS, IDOR, Command Injection & RFI/LFI Attacks that all Blue Teamers face in their journey.

>

*Note: There’s no sequence in all of the parts of this series so it’s up to you to decide which topic to learn first & so on.*

The most common & old but deadly attack in the WEB World is SQL injection

>

Prerequisite: Basic knowledge about How Attackers Find & Exploit SQLi injection vulnerability is preferred

But first, let’s understand:
Why Blue Teamer Should Know about WEB Attacks?
It is no surprise that attackers choose web applications as a gateway for their attacks because all institutions have web applications that mostly contain critical data and because modern-day applications are highly complicated and have numerous attack vectors.

>

*A study conducted by Acunetix reimburses this idea.
”Recent research shows that 75% of cyber attacks are done at the web application level.“*

Hope my stats convince you to learn about WEB Attacks. Now let’s dive.

## What is SQL Injection (SQLi)?

SQL Injections are critical attacks where a web application directly includes unsanitized data/input provided by the user in SQL queries & executes them.
When a web application communicates with a database using input from a user that hasn’t been properly validated, there runs the potential of an attacker being able to steal, delete or alter private and company data.

## SQL Injection Types

- In-band SQLi: If a SQL query is sent and replied to over the same channel, we call these In-band SQLi.

- Inferential or Blind SQLi: SQL queries that receive a reply that cannot be seen are called Inferential or Blind SQLi.

- Out-of-band SQLi: If the reply to a SQL query is communicated over a different channel then this type of SQLi is called Out-of-band SQLi. For example, if the attacker is receiving replies to his SQL queries over the DNS this is called an out-of-band SQLi.

## Detecting SQL Injection Attacks

- When examining a web request check all areas that come from the user: SQLi attacks are not limited to the form areas, you should also check the HTTP Request Headers like User-Agent.

- Look for SQL keywords: Look for words like INSERT, SELECT, WHERE within the data received from users.

- Check for special characters: Look for ‘, dashes (-), or parentheses which are used in SQL or special characters that are frequently used in SQL attacks within the data received from the user.

- Familiarize yourself with frequently used SQL Injection payloads: Even though SQL payloads change according to the web application (database), attackers still use some common payloads to check for SQL Injection vulnerabilities. If you are familiar with these payloads, you can easily detect SQL Injection payloads. You can see some frequently used SQL Injection payloads [here](https://github.com/payloadbox/sql-injection-payload-list).

## Detecting Automated SQL Injection Tools

Attackers use many automated devices to detect SQL Injection. One of the most well-known is Sqlmap.
You may use the methods listed below to detect SQL Injection Automated tools:

- Look at the User-Agent: Automated browser devices generally have their names and versions recorded. You can look at the User-Agent to detect these automated tools.

- Check the frequency of requests: Automated devices were designed to send an estimated amount of requests per second to be able to test payloads as quickly as possible. A normal user could send 1 request per 3 seconds, so you can tell if the requests are made by an automated device or not by looking at the number of requests per second.

- Look at the contents of the payload: Automated devices usually record their names in their payloads. For example, a SQL Injection payload sent by an automated tool could look like this: sqlmap’ OR 1=1

## SQL Injection (In-Band) Detection Example

We have the web server’s access logs of a web application that was victim to an SQL Injection attack.

- First, we perform URL decoding using Cyberchef to understand properly

>

*Browsers perform a URL encoding of the special characters and replace each special character with a character string that begins with % and has 2 hexadecimal characters in it.*

- We can see on 1 March at 8:35:14 the attacker with IP (192.168.31.167) first sends an SQLi payload to test if SQLi vulnerability exists.

- The attacker found out that it was vulnerable. The id parameter is passing without any sanitization. We can confirm this by looking at the response size 607 returned from the first payload. Look closely the normal size of data returned from the server is usually 4200–4900 here but when the attacker sends the first payload the response size drops to the lowest which means the server returns an error (which can be an SQL syntax error).

- Now we’ve confirmed that the SQLi attack occurred & it was successful as payloads such as ‘OR 1=1 -- -, UNION select null, version() & other return normal response size which means the server’s executing the payload & showing the result such as database version from version() payload & user database from user() payload to the attacker.

## Investigation Report

- What date did the exploitation phase of the SQL Injection Attack start?
01/Mar/2022:08:35:14

- What is the IP address of the attacker who performed the SQL Injection attack?
192.168.31.167

- What method does the attacker use is it automated (tool) or manual?
Manual because the request rate difference between each payload is 1 to 2.5 minutes & also user-agent is legit,

- What was the parameter vulnerable to SQL injection?
id

- Was the SQL Injection attack successful?
Yes, the attacker can execute any malicious SQL payload on the server.

- What is the type of SQL Injection attack?
In-Band or Classic

## How to Prevent/Mitigate SQL Injections (SQLi)

- Check the OWASP [Cheatsheet](https://cheatsheetseries.owasp.org/cheatsheets/SQL_Injection_Prevention_Cheat_Sheet.html)

- Check out this [article](https://logz.io/blog/defend-against-sql-injections/)

---
