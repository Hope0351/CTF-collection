# :globe_with_meridians: Ssrf Steals Ec2 Tokens D6F46835286E

> **Original Source:** [Ssrf Steals Ec2 Tokens D6F46835286E](https://infosecwriteups.com/ssrf-steals-ec2-tokens-d6f46835286e)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

What is SSRF (Server-Side Request Forgery)? Server-Side Request Forgery (SSRF) is a critical vulnerability that allows an attacker to manipulate a server into making unintended requests. This can lead to leakage of sensitive data, access to internal systems, or even remote code execution. Let’s go deeper into how SSRF can be used to steal source code, access internal services, and exfiltrate sensitive data.


- Many applications run internal services that shouldn’t be exposed to the public `(e.g., http://localhost, http://127.0.0.1, [http://internal-service.local).](http://internal-service.local).)`

- If an attacker can manipulate the URL, they can scan internal services.

## Example payload:


>

`http://example.com/get-image?url=http://localhost:6379/` If the response is different for an open port, the attacker knows which services are running.


AWS SSRF Payload:

>

[http://example.com/get-image?url=http://169.254.169.254/latest/meta-data/](http://example.com/get-image?url=http%3A%2F%2F169.254.169.254%2Flatest%2Fmeta-data%2F)


If successful, the attacker can read IAM role credentials, allowing them to take over cloud resources.


Now let’s we reproduce the vulnerability . I found the target by [https://www.youtube.com/@lostsecc](https://www.youtube.com/@lostsecc) this youtube channel you can support him and learn from him . His is bug hunter also and some of vulnerability i learn from him i’m very grateful . So let’s we talking about how to reproduce this vulnerability . I’ve tried to reproduce the vulnerability to more critical and i see something it’s using AWS server . So based on my research i can steal the IAM credentials and takeover S3 cloud bucket from the server and also i’ve identify the website is using a php languages so i can use a symlink to get the current path to arbitary read file on the server .


I will not be responsible if you use this lesson incorrectly. I am only conveying knowledge.


TBH this vulnerability has been patched by a few weeks and i think i want to disclosure this vulnerablity


1. [https://www.somaiya.edu/download.php?pdf_path=https://XXX.com/blabla.pdf](https://www.somaiya.edu/download.php?pdf_path=https%3A%2F%2FXXX.com%2Fblabla.pdf)


It’s will downloading a pdf file so i tried to manipulation the url and it’s work , so that’s mean the `download.php` allows downloads from external url and not internal only , So the conclusion is i can get any source from the server like arbitary file read , I can get IAM credentials by change `pdf_path` value into AWS internal and also can do `file:///etc/passwd`


## Get Muhammad Nizar’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


So after i try to manipulation the external url with `file:///etc/passwd` it's valid now let's we leak the mysql credentials using a symlink


## What is Symlink?


First of all we need to knows how symlink was work. A symbolic link (symlink) is a special type of file in a filesystem that points to another file or directory. It acts as a shortcut, allowing users to access the target file or directory from a different location without duplicating the actual data


Now let’s find the current path of server using symlink . After i research i’ve found this `/proc/self/cwd/index.php` so this is symlink to read current path on server


Then after i put this `file:///proc/self/cwd/index.php` it’s work i’ve leaked the index.php. In `index.php` after i analyze the code i got the location of database on `arigel/config/database.php`


Here the credentials of mysql . As you can see here the host mysql is using amazon cloud so i think it’s possibility i can access the cloud AWS from the server and steal the credentials


1.Change the `pdf_path` value with internal aws `[http://169.254.169.254/latest/user-data](http://169.254.169.254/latest/user-data)`


As you can see there is list of directory for internal aws so to steal the credentials just do this


`[http://169.254.169.254/latest/meta-data/identity-credentials/ec2/security-credentials/ec2-instance](http://169.254.169.254/latest/meta-data/identity-credentials/ec2/security-credentials/ec2-instance)`


So for full video you can watch in my youtube channel here


## Impact Of SSRF


- Attacker can takeover s3 bucket or any sensitive credentials on cloud server

- Possibility leakage source code


Best Regards,


Muhammad Nizar

---

*Originally published on [Medium](https://infosecwriteups.com/ssrf-steals-ec2-tokens-d6f46835286e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
