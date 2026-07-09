# Lab Writeup: File path traversal, traversal sequences stripped non-recursively

URL: https://portswigger.net/web-security/learning-paths/path-traversal/common-obstacles-to-exploiting-path-traversal-vulnerabilities/file-path-traversal/lab-sequences-stripped-non-recursively#

## Description

This lab contains a path traversal vulnerability in the display of product images.

The application strips path traversal sequences from the user-supplied filename before using it.

To solve the lab, retrieve the contents of the `/etc/passwd` file.

## Solution

1. Right click on one of the images and intercept with burp

   ![stripped-traversal](/assets/stripped-traversal.png)

2. Create the following payload `....//....//....//etc//passwd` and URL encode it

   ![stripped-traversal-1](/assets/stripped-traversal-1.png)

3. Change the filename param value and send the request, you'll get all the contents of `/etc/passwd` and the lab should be solved.

   ![stripped-traversal-2](/assets/stripped-traversal-2.png)

   ![stripped-traversal-3](/assets/stripped-traversal-3.png)
