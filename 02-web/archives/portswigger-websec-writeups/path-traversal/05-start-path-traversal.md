# Lab Writeup: File path traversal, validation of start of path

URL: https://portswigger.net/web-security/learning-paths/path-traversal/common-obstacles-to-exploiting-path-traversal-vulnerabilities/file-path-traversal/lab-validate-start-of-path#

## Description

This lab contains a path traversal vulnerability in the display of product images.

The application transmits the full file path via a request parameter, and validates that the supplied path starts with the expected folder.

To solve the lab, retrieve the contents of the `/etc/passwd` file.

## Solution

1. Right click on one of the images and intercept with burp

   ![start-path-traversal](/assets/start-path-traversal.png)

2. Create the following payload `/var/www/images/../../../etc/passwd` and URL encode it twice

   ![start-path-traversal-1](/assets/start-path-traversal-1.png)

3. Change the filename param value and send the request, you'll get all the contents of `/etc/passwd` and the lab should be solved.

   ![start-path-traversal-2](/assets/start-path-traversal-2.png)

   ![start-path-traversal-4](/assets/start-path-traversal-3.png)
