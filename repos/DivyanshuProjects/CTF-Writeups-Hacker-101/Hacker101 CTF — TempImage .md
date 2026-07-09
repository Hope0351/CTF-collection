Hacker101 CTF — TempImage (Web, Moderate)

🏆 Challenge Overview
- Platform: Hacker101
- Challenge Name: TempImage
- Category: Web
- Flags: 2/2

---

 🔥 Introduction

Hey everyone! I’m Divyanshu Kumar, a cybersecurity adventurer, always on the lookout for hidden exploits and secret backdoors. Today, I’m diving into an exciting CTF challenge—TempImage. This is part of my series where I explore cybersecurity concepts through CTF (Capture The Flag) walkthroughs.

⚠️ Disclaimer: I’m still learning, and these posts are meant to document and share my knowledge as I grow in the cybersecurity field. Now, let’s dive into the challenge!

---

 🛠 Understanding Burp Suite

Before jumping into the challenge, let’s talk about Burp Suite, one of the most powerful tools for web penetration testing. Burp Suite acts as a proxy between the browser and the server, allowing us to intercept, modify, and analyze requests. It’s widely used for testing web application security, manipulating HTTP requests, and automating attacks.

💡 Key Features Used in This Challenge:
✅ Intercept Requests: Capturing and modifying HTTP requests before they reach the server.
✅ Repeater Tool: Resending modified requests to test for vulnerabilities.
✅ Intruder: Automating payloads for brute-force and fuzzing attacks.
✅ Decoder & Encoder: Manipulating and encoding payloads for exploitation.

With Burp Suite ready, let’s tackle TempImage step by step!

---

 🚀 FLAG 0: Path Traversal Exploit

The challenge started with a file upload feature, but only PNG images were allowed. After attempting to upload various files, I noticed that the images were stored in the `/files` directory with an auto-generated prefix.

🔹 Observations:
- Only PNG files were accepted.
- Files were uploaded to `/files/` with a random prefix.
- This hinted at a potential path traversal vulnerability.

🔹 Exploitation:
1️⃣ Uploaded a PNG file and analyzed the response.
2️⃣ Opened Burp Suite and intercepted the file upload request.
3️⃣ Modified the upload path by injecting `../../`, which attempts to traverse directories.

🔹 Payload Used:
```
../../cd/image/png/download.png
```

📌 Outcome: The modified request successfully uploaded the file outside the `/files` directory, and boom! The first flag was captured! 🎉


![image](https://github.com/user-attachments/assets/3b7723e2-e96f-4f6e-80dd-5e0a90d85de7)


---

 🔥 FLAG 1: PHP Code Injection via Metadata

After confirming path traversal, the next goal was to execute arbitrary PHP code by manipulating image metadata.

🔹 Observations:
- Burp Suite displayed metadata details of uploaded images.
- Instead of uploading a normal image, I tried modifying its metadata to inject PHP code.
- If successful, the server would execute my PHP payload when accessing the file.

🔹 Exploitation:
1️⃣ Uploaded an image and captured the request in Burp Suite.
2️⃣ Modified the metadata at the end of the image file to contain malicious PHP code:

```php
<?php echo htmlspecialchars(file_get_contents('index.php')); ?>
```

3️⃣ Renamed the uploaded file from `download.png` to `download.php`.
4️⃣ Used path traversal again to access the uploaded PHP file:
```
../../download.php
```
5️⃣ Sent the request and followed the redirection in Burp Suite.

📌 Outcome: The server executed my PHP script, exposing `index.php`. A quick search for "flag", and boom! The second flag was captured! 🎉

![image](https://github.com/user-attachments/assets/51717996-f8ea-4ee4-8a34-994c54a16ed6)


---

 🔑 Key Takeaways
✅ Path Traversal vulnerabilities can expose sensitive files if upload paths are not properly restricted.

✅ Metadata Manipulation is a sneaky way to bypass file format restrictions and execute arbitrary code.

✅ Burp Suite is a must-have tool for web security testing, allowing interception, manipulation, and automation.

