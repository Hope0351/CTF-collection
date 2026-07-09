# Lab Writeup: Web shell upload via Content-Type restriction bypass

URL: https://portswigger.net/web-security/learning-paths/server-side-vulnerabilities-apprentice/file-upload-apprentice/file-upload/lab-file-upload-web-shell-upload-via-content-type-restriction-bypass#

## Description

This lab contains a vulnerable image upload function. It attempts to prevent users from uploading unexpected file types, but relies on checking user-controllable input to verify this.

To solve the lab, upload a basic PHP web shell and use it to exfiltrate the contents of the file `/home/carlos/secret`. Submit this secret using the button provided in the lab banner.

You can log in to your own account using the following credentials: `wiener:peter`

## Solution

1. Login with `wiener:peter`
2. Create the following PHP script:
   ```php
    <?php echo file_get_contents('/home/carlos/secret'); ?>
   ```
3. Upload as avatar and intercept with burp. We'll see the following error after upload:
   ![shell-c-type](/assets/shell-c-type.png)

   That means we have to change the `Content-Type` in the HTTP request to either `image/jpeg` or `image/png`

   ![shell-c-type-1](/assets/shell-c-type-1.png)

4. Send the new HTTP request and open the image. The content of `/home/carlos/secret` should be seen

   ![shell-c-type-2](/assets/shell-c-type-2.png)

   Copy and paste in the secret submit form. The challenge should be solved.

   ![shell-c-type-3](/assets/shell-c-type-3.png)
