# :game_die: Ignite CTF 2023 | Machine walkthrough

> **Original Source:** [Ignite CTF 2023 | Machine walkthrough](https://infosecwriteups.com/ignite-2023-ctf-machine-walkthrough-28436cadf7d2)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2023

---

# Ignite CTF 2023 | Machine walkthrough


*Ignite_CTF*


This machine CTF will tell you how do LFI and misconfiguration in ngnix default config file can lead to machine takeover or sometime account takeover.


Challenge Name : Nghinx


Challenge Type : machine


Challenge Difficulty: medium


Points : 100


Description:


We never been hacked, we probably have the most secure app so far.


Firstly when we click on the url of machine the below image will come.


*blog-page*


Now we will click on My first blog button it will redirect us to some .txt file which is giving us error.


*error-page*


So now remove all the path of redirection and enter /etc/passwd file, As we can see in below image that we can read passwd file.


*/etc/passwd*


When I try to read /etc/shadow file it is giving me permission error.


*permission_error*


From the challenge name we knew that this page is using ngnix server, Now we try to read ngnix config file, But don’t find anything.


*config_file*


Then we will read /etc/nginx/sites-available/default to know how requests to specific paths should be handled.


*default_nginx*


Below is default ngnix configuration page in readable form:-


```
server {
listen 80;

location ~ ^/ttydremote(.*)$ {
proxy_http_version 1.1;
proxy_set_header Host $host;
proxy_set_header X-Forwarded-Proto $scheme;
proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
proxy_set_header Upgrade $http_upgrade;
proxy_set_header Connection "upgrade";
proxy_pass http://127.0.0.1:7681/$1;

auth_basic "Restricted Access";
auth_basic_user_file /etc/nginx/.htpasswd;
}

location ~ ^/$ {
proxy_http_version 1.1;
proxy_set_header Host $host;
proxy_set_header X-Forwarded-Proto $scheme;
proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
proxy_set_header Upgrade $http_upgrade;
proxy_set_header Connection "upgrade";
proxy_pass http://127.0.0.1:5000/$1;
}

location /view {
proxy_http_version 1.1;
proxy_set_header Host $host;
proxy_set_header X-Forwarded-Proto $scheme;
proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
proxy_set_header Upgrade $http_upgrade;
proxy_set_header Connection "upgrade";
proxy_pass http://127.0.0.1:5000/view$is_args$args;
}
}
```


From the above config file we knew that /ttydremote is authenticating from /etc/nginx/.htpasswd, So now we will navigate to .htpasswd and get the username and hash password.


*.htpasswd*


Now we try to cracked the hash through hashcat and we will get the cracked password.


## Get Hanzala Ghayas Abbasi’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Command that I used to crack the password is below:-


```
sudo hashcat -m 1600 hash.txt /home/Ignite/Desktop/Tool/rockyou.txt
```


Cracked password is password.


*cracked_password*


Now we will navigate to /ttydremote and it asks us for username and password we enter it that we we have find:


Username : username.


Password : password.


*Authentication_/ttydremote*


If we enter the correct username and password, we will gain access to the machine on port 80. Knowing that I was a low-privileged user, I attempted to escalate my privileges. Upon running sudo -l, I discovered that ansible-playbook can be executed with sudo privileges.


Now we will search ansible-playbook on [gtfobin](https://gtfobins.github.io/#) and get the privilige escalation technique.


*gtfobin*


Finally, I just run above three command one by one I get the root 😍 .Then I change my directory to root and find flag, Now come to my favorite part of solving the machine CTRL+C and Ctrl+V the flag and solve the challange.


*flag*What is the flag? Flag{QCFAb2I1MlNaY1lld2dyUElDMVNIeU5sZz09ZjU0MjhiMmZlN2MwZmViOA==}

---

*Originally published on [Medium](https://infosecwriteups.com/ignite-2023-ctf-machine-walkthrough-28436cadf7d2). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
