# :game_die: How to make our own CTF Challenge with ease.

---

## Ubuntu Server Installation

Now, we will proceed with installation of Ubuntu Server. So when server starts up, we will first see this window where a language is need to be selected. Let’s proceed with English.

- Pressing enter and we will see the installer update available. But let’s continue without updating it,

- Press enter and next will come Keyboard Configuration. Leave it as it is,

- Press enter and we will see the Network connections window. So let the server use DHCP to self assign IP address to the machine,

- Press enter and now we will be presented to configure proxy but we’ll skip it by pressing enter,

- Now, we will be presented with Storage configs. We will use the entire disk for our box,

- After selecting the storage layout, press enter,

- we don’t have to make changes here so pressing enter again,

- It will prompt a confirmation box and start the installation. Go for Continue. It’ll then ask to enter the device name and a username and it’s corresponding password, so let’s make one,

*I’ve entered the hostname (name of the server) as test and username & password as hellfire.*

- Press enter after providing name, username and password. Then it’ll ask us if we want to install OpenSSH Server, and since we want to, so we’ll select it by taking cursor to the area and pressing *spacebar*,

- Press enter and it’ll ask us to install snap features, let’s skip these,

- Pressing enter for the last time to finish with this configurations and ubuntu will start the installation process,

After getting to this point, you will get an option to Reboot Now. Go ahead and reboot this machine and now our machine is ready.

## Box Creation

Now that we’re done with our installation of the ubuntu server, let’s quickly start the process of box creation (I know some of you are already excited, so I am). We can now log in to the server using credentials we have (hellfire:hellfire, in my case). Let’s see the information,

```
id
whoami
hostname
```

The `id` the command will show us the ID of hellfire user, `whoami` command will show us that who we currently are and `hostname` command will show us the name of the system. Issuing `ls -la` command and we can see the directory contents (nothing useful at this moment).

Now, to perform some major tasks, we need to have root user access and for that, let’s first enable root user login,

```
sudo -i passwd root
su root
id
```

The first command `sudo -i passwd root` enables the root user login by asking us to set the root user password. The second command `su root` helps us to switch to root user and `id` command checks the ID of root user.

Now that we’re in root user directory, let’s create root user flag,

```
echo 'root_flag' | md5sum > root.txt
ls -la
chmod 600 root.txt
ls -la
```

The first command `echo ‘root_flag’ | md5sum > root.txt` echoes the root_flag string and [pipes](https://www.geeksforgeeks.org/piping-in-unix-or-linux/) it into [md5sum](https://www.geeksforgeeks.org/md5sum-linux-command/) command to generate a alphanumeric value which is directed straight into root.txt file. Issuing `ls -la` , we can see that our root.txt file is created but having reading permissions for others and groups as well (and we need to take these permissions away as you don’t want the low level user to read information of root user files). So to take the reading permissions of others and groups away, the third command `chmod 600 root.txt` helps us (files have r-w-x permissions with value of 4–2–1 respectively), and making sure that no one else but root user can read this flag. Again issuing `ls -la` and we can clearly see that file permission is changed.

To verify if low level user can read this flag or not, simply type `exit` command and try to read the root.txt file as low level user (hellfire, in my case) and we can see the Permission denied message which verifies that no one but root user can read the root.txt file.

We are good here. (:

Now, let’s switch back to root user again with `su root` command and create the flag for low level user,

```
echo 'user_flag' | md5sum > /home/hellfire/user.txt
ls -la
chown hellfire:hellfire user.txt && chmod 660 user.txt
ls -la
```

The first command `echo ‘user_flag’ | md5sum > /home/user/user.txt` helped us to create the user flag. Issuing `ls -la` command to view the permissions of the user.txt file and we can see that groups and others can read the user.txt file. So here, what we can do is that we can make this file owned by hellfire user and changing its permissions so that only owner and group members can read this user.txt file. We can achieve both tasks by combining two commands `chown hellfire:hellfire user.txt && chmod 600 user.txt` as this command will only work if 1st command is correct (that’s because of && operator). Again issuing `ls -la` , we can see that our file is now owned by hellfire and has suitable permissions.

## Get Akshat Gupta’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Moving forward towards interesting things like configuring FTP server, apache2 webserver, openssh server, etc etc. Now that we are done with creating flags, let’s actually start the work. To enable traffic via any port on this server, we need ufw ([Uncomplicated Firewall](https://www.linux.com/training-tutorials/introduction-uncomplicated-firewall-ufw/)) tool. Let’s install it on our server,

```
apt install ufw
ufw status
ufw enable
ufw status
```

The first `apt install ufw` command installs the uncomplicated firewall on our server. The second `ufw status` command checks the status of firewall to see if it’s active or inactive. The third `ufw enable` command enables/starts the firewall and the fourth command again checks the status of firewall (which is now active).

After downloading and setting up the uncomplicated firewall, let’s install the FTP server,

```
apt install vsftpd
cp /etc/vsftpd.conf /etc/vsftpd.conf.orig
nano /etc/vsftpd.conf
```

The first `apt install vsftpd` command installs the vsftpd server on our machine. The second `cp /etc/vsftpd.conf /etc/vsftpd.conf.orig` command makes backup of the configuration of vsftpd.conf file. The third `nano /etc/vsftpd.conf` command opens up the text editor to edit the vsftpd.conf file.

Now, we all like anonymous user login enable while solving CTFs because it makes our work easier, right? We are going to configure the same anonymous user access to our FTP server (YAY!). Since our configuration file is already running, we have to make changes into this file. To enable anonymous user to login into ftp,

We changed the Anonymous Login enabled from NO to YES as this will allow anonymous user to login to FTP. Next, we defined a directory for the ftp in `/var/ftp`. And lastly, we have disabled the login password for anonymous user; what this will do is that when an anonymous user tries to login, ftp won’t ask for password while authentication.

So now that we’re done with vsftpd.conf configuration, let’s bake some things on terminal as well,

```
cd /var
mkdir ftp
chown nobody:nogroup ftp/
cd ftp && echo 'Hello Hellfire' > file.txt && chown nobody:nogroup file.txt
```

Okay so, we’ll navigate to `/var` directory using the first command and then using second command, we’ll create a directory of name ftp. After creating a directory, let’s do some magic, shall we? First, let’s change the onwership of this ftp directory to `nobody:nogroup` using `chown nobody:nogroup ftp` command. Read more about [Nobody](https://askubuntu.com/questions/329714/what-is-the-purpose-of-the-nobody-user) group. Alas, we first navigate to the directory we made, created a file named file.txt having content “Hello Hellfire” and then changing the ownership of the file file.txt. After issuing `ls -la` command, we can see that file permissions are set as the way we want.

We are done with this and now, all there left is to enable traffic for ftp,

```
ufw allow 20/tcp
ufw allow 21/tcp
ufw status
```

The above 2 commands `ufw allow 20/tcp` and `ufw allow 21/tcp` will allow traffic to be flown from these 2 ports. Read more about [why FTP uses 2 ports](https://stackoverflow.com/questions/626823/in-protocol-design-why-would-you-ever-use-2-ports). Checking the firewall status again to verify if these ports are allowed by firewall or not.

Here, we will now use kali machine to access the ftp service,

```
ftp 10.0.2.27
get file.txt
```

Okay so with first `ftp 10.0.2.27` command, we connect to ftp service using ftp client installed on the kali machine, providing it the IP address of the ubuntu server. Then it will prompt us for login, so provide Anonymous username and press enter but it won’t prompt us for password (remember we disable for password prompt in vsftpd.conf file?) and we’ll get logged in straight. We can list the directory content and see that there is a file named file.txt (which we create before). Then, we’ll download this file on our local system using `get file.txt` command and then `exit` from this server. Reading the content of the file.txt will show that our FTP service is working fine!!

Now, coming to Webserver part, apache2 is not installed in ubuntu server 20.04 so I had to manually installed, but it’s really easy. We just need to type out the following command,

```
sudo apt update
sudo apt install apache2
```

First command updates the installed packages in the system and second command will actually install the apache2 server on our ubuntu.

Now, if we visit [http://10.0.2.27](http://10.0.2.27) in our browser, we will see the default webpage for Ubuntu (this means that our webserver is up and running),

Now that we know that our webserver is up and running, let’s install PHP language on our system to make it more fun! To install PHP on our system, we first need to add repository on our ubuntu system,

```
apt install software-properties-common
add-apt-repository ppa:ondrej/php
```

The first command allows to easily manage the distribution. You can read more information on [software-common-properties](https://askubuntu.com/questions/1000118/what-is-software-properties-common). The second command actually adds the ondrej PHP repository on ubuntu system. Well in case if you’re wondering now what is ondrej? Here’s the look at the screenshot,

*screenshot from google*

Now, we need to issue 2 more commands to install php on our system,

```
apt update
apt install -y php7.4
```

First command as usual, will update packages in our system and second command will install PHP7.4 on our system.

Well, I hope you’re still following me till now. As you can think by now, how much I have to type, document all of this stuff because before organizing them, they were just scattered and making my mindset to write an article on this topic (I knew it will be going to be a lengthy one), is not easy, but I am really enjoying it so that what matters to me!! Also, if you need a break, you can drink water, relax your shoulders by rolling them backwards, relax your neck and spine, and start the creation process, again! ((:

Okay, now that we have installed PHP7.4 on our system, we will first create a test php file to see if it’s working or not. I’ll follow up with the most basic code of php,

```
echo '<?php phpinfo(); ?>' > test.php
ls -la
chown -R www-data:www-data /var/www/html
ls -la
```

With the first command, we will redirect the basic php code (contains a phpinfo() function which is used to output a large amount of information about PHP installation and can be used to identify installation and configuration problems) into test.php file. Then viewing the content of the directory and we saw that both of the files are having root user ownership, and since we know that files in webserver should have ownership of [www-data user](https://askubuntu.com/questions/873839/what-is-the-www-data-user) (think about a scenario where webserver gets compromised and files having root user ownership will lead to full system compromised). So we will change the ownership of all files to www-data user in `/var/www/html` directory (root directory for webserver!). Again viewing the content of directory and now we can see that files have www-data user ownership!

We’re all set! Let’s navigate to [http://10.0.2.27/test.php,](http://10.0.2.27/test.php,) and we can see the PHP info page,

We can see this page because this test.php file exist in `/var/www/html` directory and we can’t see any file outside of this directory from browsing action. So we’re all set!! I won’t be implementing [Command Injection](https://www.imperva.com/learn/application-security/command-injection/) vulnerability or [LFI](https://www.acunetix.com/blog/articles/local-file-inclusion-lfi/) vulnerability on this box. As I already mentioned, this blog is just a base for everyone who’s thinking to developing/creating a box but don’t really know how to get started, you got my point. However, I highly encourage you to stop here, at least try to do some research on those mentioned vulnerabilities (these 2 are few of many!!) and try to implement it on your own. Play with it, until it start working and *you shall see the wonder*.

Okay, so we’re done with setting up FTP server and Web server, now all that left is to set up SSH server. Start by checking the version of ssh installed on the system,

```
sshd --version
```

This command checks the version of the ssh installed on the system or if it’s even installed or not on the system. Read more about [SSHD](http://www.nsc.ru/cgi-bin/www/unix_help/unix-man?sshd+8=).

Since it is installed, let’s move forward by enabling traffic from port 22 (default port for SSH service),

```
ufw allow ssh
ufw status
```

The first command will allow traffic from port 22 and second command will check the status of the firewall and we can see that our rules are correctly added. Our job with this configuring SSH server is done.

Let’s try to access hellfire user with ssh client on kali box,

```
ssh kali@10.0.2.27
```

SSH client will prompt us for user password, provide that and we’ll get logged in! So this means our user can login via ssh as well (HURRAYYY). Now, I encourage you to try to create 2–3 users and try to login on your own to get the feel of the developer (even if it’s a little bit!) or you can even configure SSH Key-Based Authentication for your user (try it! It is really fun, believe me on this!).

## Exporting Appliance

Now, this will gonna be an easy process as you only have to export your system to a .ova file and you can send it over internet across or maybe your hacker friend to pwn it. Shutdown your ubuntu system now as we need to export it. Now, follow the steps below to export the system,

- File → Export Appliance → Virtual Machines to export (select your ubuntu machine you just configured) → Appliance Settings (Format should be Open Virtualization Format 1.0 and then save the file with desired name and location. Leave the check boxes as they’re) → DONE!!!!

## Notes

P.S. So here are the notes which I forgot to attach at the end of the blog,

```
## Change root user password
- sudo -i passwd root## Switch to root user
- su root## add root user flag
- echo 'root_flag' | md5sum > /root/root.txt
- chmod 600 /root/root.txt## add user flag
- echo 'user_flag' | md5sum > /home/user/user.txt
- chmod 660 /home/user/user.txt### You can create other users like testuser1, testuser2
- adduser testuser1
- adduser testuser2## Install uncomplicated firewall (ufw)
- apt install ufw
- ufw enable
- ufw status## Install FTP server
- apt install vsftpd
- cp /etc/vsftpd.conf /etc/vsftpd.conf.orig #(use sudo before the command if not root)### add these lines in the /etc/vsftpd.conf file:
- anonymous_enable=YES #Allow anonymous login FTP (Disabled by Default)
- anon_root=/var/ftp #Directory for FTP
- no_anon_password=YES #Stop prompting password-> save file and exit.- mkdir /var/ftp #Now make a ftp directory in /var
- chown nobody:nogroup ftp/ #changing owner of ftp dirctory to nobody:nogroup
- cd ftp; touch file.txt; chown nobody:nogroup file.txt #change directory; create a new file; assign new permissions
- ufw allow 20/tcp; ufw allow 21/tcp #allow ftp traffic for tcp port 20,21### enable vsftpd service
- sudo service vsftp start #enable vsftp service
- service vsftpd start #if running as root-> Now login as anonymous user on ftp user and see that there will be a file named file.txt present.## Configure Apache HTTP server
- ufw allow http (or)
- ufw allow 80/tcp #allow ftp traffic for tcp port 80
- ufw status #check status of firewall
- apt update #update packages before installing apache2
- apt install apache2 #install apache2 on server### install PHP
- apt install software-properties-common #configure repository on system
- add-apt-repository ppa:ondrej/php #adding ondrej php repo on ubuntu system
- apt update #update packages before installing
- apt install -y php7.4 #install php7.4 on ubuntu system-> Navigate to [http://$IP](http://$IP) and you will be presented with Apache2 Ubuntu Default Page. Now to create a test.php page, do:- echo '<?php phpinfo(); ?>' > test.php #simple php page to run on web pages
- chown -R www-data:www-data /var/www/html #webserver files must belong to user and group www-data:www-data not the root:root user-> Now visit [http://$IP/test.php](http://$IP/test.php) and you'll presented with PHP info page. From there you can set RCE if you want.## Configure SSH
- sshd --version #check if openssh is installed by checking it's version
- ufw allow ssh (or)
- ufw allow 22/tcp #allow ftp traffic for tcp port 22-> Now test if you can login as testuser1/testuser2/root user via ssh service.## Export the VM to an OVA format- Now after machine is tested and working as intented we can export it into OVA format in Virtual Box.
- Go into:
---- File > Export Appliance
---- Then select your vulnerable machine in this case mine is Ubuntu 20.04 Server
---- Choose Open Virtualization Format 1.0
---- Name the file you want to save
---- Click 'Export'=> You just made your first CTF box.
```

---
