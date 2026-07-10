# :game_die: How to Organize a CTF on CTFd for free?

> **Original Source:** [How to Organize a CTF on CTFd for free?](https://infosecwriteups.com/how-to-organize-a-ctf-on-ctfd-for-free-6077d34b0c9b)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# How to Organize a CTF on CTFd for free?


Hey, welcome to my first blog. We are going to know, how to organize a ctf for free.

>

Digital Ocean provide free 100$ Credit to every new user for one time.


[Digital Ocean](https://www.digitalocean.com/)


We are going to use this credits to host our ctf.

>

Note: You will get credits, only if you have Credit Card, International Debit Card or PayPal account.


*Photo by [Arget](https://unsplash.com/@arget?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText) on Unsplash*


After creating the account, go to homepage and click on Get started with a Droplet.


After this, you will get an option to choose OS. I will go for Ubuntu 18.4 (LTS) x64. Will config it to:


- 8 GB/ 4 CPUs

- 5 TB Transfer

- 160 GB SSD


After choosing the plan, choose a data center region. Now, create a password for root.


Then, click on Create Droplet option. You will get your IP address once all done.


## Get Nihal Umar’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Now login into the machine with ssh.

>

Username: root Password: <You choosed>


`apt update && apt upgrade`


Once update & upgrade is done. We have to install docker & docker-compose.


`apt install docker docker-compose`


All done? Visit ctfd deployment (docs) page to proceed.


[CTFd Docs](https://docs.ctfd.io/docs/deployment/)


Now open tmux session by typing `tmux`. Clone the ctfd repo first & then move forward.


```
git clone [https://github.com/CTFd/CTFd.gi](https://github.com/CTFd/CTFd.git)t
```


Move to CTFd dir and open docker-compose.yml file. Here, we have to update the secret key & workers (so that it can handle the load.)


After making changes, save & exit docker-compose.yml file. And type `docker-compose up`. It will start your ctfd. This may take few minutes. All done 👍


Now, visit [cloudflare](https://www.cloudflare.com/) website, add your website with a free plan [Basic]. Once the website is added successfully, add a record in DNS Management as follows:

>

Type: A Name: <subdomain> IPv4 Address: <IP Address>


Just save it. Now visit your subdomain site and setup your admin account with other configurations.


Now sit back and enjoy 😉

---

*Originally published on [Medium](https://infosecwriteups.com/how-to-organize-a-ctf-on-ctfd-for-free-6077d34b0c9b). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
