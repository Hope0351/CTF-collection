# Lab Writeup: Unprotected admin functionality

URL: https://portswigger.net/web-security/learning-paths/server-side-vulnerabilities-apprentice/access-control-apprentice/access-control/lab-unprotected-admin-functionality#

## Description

This lab has an unprotected admin panel.

Solve the lab by deleting the user `carlos`.

## Solution

1. Go to `/robots.txt`, here's the response body:

   ```
   User-agent: *
   Disallow: /administrator-panel
   ```

2. Go to `/administrator-panel` and delete `carlos`. The lab should be solved.

   ![Unprotected Admin Functionality](/assets/unprotected-admin.png)
