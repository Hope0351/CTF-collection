# :game_die: Vulnhub Fristileaks 1 3 Writeup By Dollarboysushil D18010Cff739

---

Lets start

You should get the IP address of the machine, `192.168.21.140` in my case

### Nmap Scanning

`nmap -sC -sV {victim ip}`
-sC for default scripts and -sV for version enumeration.

nmap scan result shows there is only one service running , that is `http `on port `80`

lets run gobuster to do some directory bruteforcing

using go buster reveals two directories `/images` and `/beer`

`/images` contains image directory and` /beer` contains a image.

well this directory are not much of use. Looking at the theme of the lab and the website i tried manually entering `/fristileaks` , `/fristi` and other directory. Among which `/fristi` worked

We have login portal at `/fristi` directory. I tried to do some SQL injection but didnt work.

Viewing page source `CTRL + U` reveals some interesting things.
First thing to note is the username `eezeepz`

and at the bottom we have `base64 `encoded string

Decoding this string reveals it is of type `png`

Using `base64 to png` online tool gives us the png image. Which contains string.

With this info we can guess, this must be password for username `eezeepz`

Lets try to login

Credentials were valid and we are successfully logged in .

After login we are redirected to `upload `page. Here our best step would be to upload a `reverse php script` and get ourself shell.

download `php-reverse-shell` from here [https://github.com/pentestmonkey/php-reverse-shell](https://github.com/pentestmonkey/php-reverse-shell)

Make sure to change the `$ip` to your machine ip. and upload this file .

Sadly we cannot upload `.php` file. website only takes `png, jpg, gif`
No problem here.

rename the script by adding `.png` at last. `revhsell.php` ->` revshell.php.png`

Then upload this file.

This time file is successfully uploaded.

Lets make our netcat listner ready.

`nc -lnvp 5555` make sure the port number is same as in reverse shell file.

## Get dollarboysushil’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

While nc is ready to listen. Go to the website and open the file.

`ip/fristi/uploads/filename` going here make the site stuck on infinite loading.
looking at our netcat listner.

We have got ourself `shell` as user `apache`

---
