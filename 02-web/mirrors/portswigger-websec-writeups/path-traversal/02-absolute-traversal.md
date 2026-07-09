# Lab Writeup: File path traversal, traversal sequences blocked with absolute path bypass

URL: https://portswigger.net/web-security/learning-paths/path-traversal/common-obstacles-to-exploiting-path-traversal-vulnerabilities/file-path-traversal/lab-absolute-path-bypass#

## Description

This lab contains a path traversal vulnerability in the display of product images.

The application blocks traversal sequences but treats the supplied filename as being relative to a default working directory.

To solve the lab, retrieve the contents of the `/etc/passwd` file.

## Solution

1. Right click on one of the images and intercept with burp

   ![absolute-traversal](/assets/absolute-traversal.png)

2. Create the following payload `/etc/passwd` and URL encode it

   ![absolute-traversal-1](/assets/absolute-traversal-1.png)

3. Change the filename param value and send the request, you'll get all the contents of `/etc/passwd` and the lab should be solved.

   ![absolute-traversal-2](/assets/absolute-traversal-2.png)

   ![absolute-traversal-3](/assets/absolute-traversal-3.png)
