# Lab Writeup: File path traversal, traversal sequences stripped with superfluous URL-decode

URL: https://portswigger.net/web-security/learning-paths/path-traversal/common-obstacles-to-exploiting-path-traversal-vulnerabilities/file-path-traversal/lab-superfluous-url-decode#

## Description

This lab contains a path traversal vulnerability in the display of product images.

The application blocks input containing path traversal sequences. It then performs a URL-decode of the input before using it.

To solve the lab, retrieve the contents of the `/etc/passwd` file.

## Solution

1. Right click on one of the images and intercept with burp

   ![double-decode-traversal](/assets/double-decode-traversal.png)

2. Create the following payload `../../../etc/passwd` and URL encode it twice

   ![double-decode-traversal-1](/assets/double-decode-traversal-1.png)

   ![double-decode-traversal-2](/assets/double-decode-traversal-2.png)

3. Change the filename param value and send the request, you'll get all the contents of `/etc/passwd` and the lab should be solved.

   ![double-decode-traversal-3](/assets/double-decode-traversal-3.png)

   ![double-decode-traversal-4](/assets/double-decode-traversal-4.png)
