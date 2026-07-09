# Lab Writeup: SQL injection vulnerability allowing login bypass

URL: https://portswigger.net/web-security/learning-paths/server-side-vulnerabilities-apprentice/sql-injection-apprentice/sql-injection/lab-login-bypass#

## Description

This lab contains a SQL injection vulnerability in the login function.

To solve the lab, perform a SQL injection attack that logs in to the application as the `administrator` user.

## Solution

1. Go to login page `/login` and try logging in with whatever username and password, intercept it with burp

   ![sqli-login-bypass](/assets/sqli-login-bypass.png)

2. Send to repeater and create the payload `test' OR 1=1 --` to username param and URL encode it

   ![sqli-login-bypass-1](/assets/sqli-login-bypass-1.png)

3. Apply the encoded payload to username, send the request and the lab should be solved.

   ![sqli-login-bypass-2](/assets/sqli-login-bypass-2.png)

   ![sqli-login-bypass-3](/assets/sqli-login-bypass-3.png)
