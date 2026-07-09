# Lab Writeup: File path traversal, simple case

URL: https://portswigger.net/web-security/learning-paths/path-traversal/reading-arbitrary-files-via-path-traversal/file-path-traversal/lab-simple#

## Description

This lab contains a path traversal vulnerability in the display of product images.

To solve the lab, retrieve the contents of the `/etc/passwd` file.

## Solution

1. Right click on one of the images and intercept with burp

   ![simple-traversal](/assets/simple-traversal.png)

2. Create the following payload `../../../etc/passwd` and URL encode it

   ![simple-traversal-1](/assets/simple-traversal-1.png)

3. Change the filename param value and send the request, you'll get all the contents of `/etc/passwd` and the lab should be solved.

   ![simple-traversal-2](/assets/simple-traversal-2.png)

   ![simple-traversal-3](/assets/simple-traversal-3.png)
