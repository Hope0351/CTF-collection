# :globe_with_meridians: [CVE-2021-28428] Authenticated RCE found in HorizontCMS - Part 2 (PHP Filetype Bypass)

---

# [CVE-2021–28428] Authenticated RCE found in HorizontCMS — Part 2 (PHP Filetype Bypass)

## Intro

As I talked about in the Part 1, [[BugHunt] Authenticated RCE found in HorizontCMS — Part 1 (Malicious Plugins)](), blog, we found a way to bypass the patched PHP filetype restrictions to upload a `.php` file. However, the executing the uploaded PHP file was not accomplished.

So, we wanted to go with different route of choosing files to upload and gain PHP code execution on the application.

## Media Files Upload RCE

As mentioned in the Part 1, the original file upload vulnerability ([CVE-2020–27387](https://packetstormsecurity.com/files/160046/HorizontCMS-1.0.0-beta-Shell-Upload.html)) was remediated by restricting the PHP extensions; however, we discovered that the filter could be bypassed via uploading an arbitrary `.htaccess` and `*.hello` files in order to execute PHP code to gain RCE.

### Reproduction of the Issue

- Login to the admin panel (`http://<HorizontCMS IP>/admin/login`)

- Go to “Media” → “Files”

3. Upload the following `test2.htaccess` → Rename the file name as `.htaccess`

---
