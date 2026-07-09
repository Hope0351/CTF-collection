# Lab Writeup: File path traversal, validation of file extension with null byte bypass

URL: https://portswigger.net/web-security/learning-paths/path-traversal/common-obstacles-to-exploiting-path-traversal-vulnerabilities/file-path-traversal/lab-validate-file-extension-null-byte-bypass#

## Description

This lab contains a path traversal vulnerability in the display of product images.

The application validates that the supplied filename ends with the expected file extension.

To solve the lab, retrieve the contents of the `/etc/passwd` file.

## Solution

1. Right click on one of the images and intercept with burp

   ![null-bytes-traversal](/assets/null-bytes-traversal.png)

2. Change the filename param value and send the request, you'll get all the contents of `../../../etc/passwd%00.jpg` and the lab should be solved.

   ![null-bytes-traversal-1](/assets/null-bytes-traversal-1.png)

   ![null-bytes-traversal-2](/assets/null-bytes-traversal-2.png)
