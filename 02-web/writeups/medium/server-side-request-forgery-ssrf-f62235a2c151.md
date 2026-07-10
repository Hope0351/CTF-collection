# :globe_with_meridians: Server Side Request Forgery — SSRF

> **Original Source:** [Server Side Request Forgery — SSRF](https://infosecwriteups.com/server-side-request-forgery-ssrf-f62235a2c151)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Server Side Request Forgery — SSRF


Server side request forgery is one of the web vulnerabilities which allows an attacker to use the backend server to make unintended requests to the internal systems. This way an attacker can gain access to the internal systems which are blocked by firewalls, if the application uses a cloud platform like AWS then a vulnerable application can result in the attacker accessing the metadata instances which has a lot of juicy information such as security keys of IAM roles etc.


*Working of SSRF*


The above image is an example of how SSRF works. This scenario shown in the image contains two servers


- Web Server

- Victim Server (Internal Server protected by a firewall )


Let us assign Ip address for each of the servers


- Web Server — 192.168.0.3

- Victim Server — 192.168.0.4

- Attacker — 222.234.123.1


This system is designed in such a way that a web server can be accessed by any IP address inside or outside the network. Whereas the victim server has a firewall and only allows connection from the mail server, so if the attacker tries to access the victim server directly he/she would be blocked by the firewall.


Now the attacker has to find a way to bypass the restriction and access the victim server. Let's say the web-server mentioned above acts as an online image gallery, where a user can upload their pictures and save it in a cloud.


The image can be uploaded in 2 ways


- Upload from their device.

- An URL, where the image is hosted.

>

*Uploading an image through a URL means the webserver has to make a GET request to the user given URL and fetch the image and later store it in the cloud. So the GET request made to get the image is on behalf of the backend webserver(192.168.0.3).*


This little feature offered by the webserver can be exploited if the user input URL is not sanitized properly. So what if instead of giving an actual image URL the attackers inputs an URL pointing to an internal domain of the network (in this case the victim server)?


## Get Shaik Ajmal’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Now the attacker can input the IP address of the Victim server -http://192.168.0.4 in the image URL field and in turn the webserver would make a GET request to the victim server, the victim server’s firewall allows this request as the request is made from 192.168.0.3 and not 222.234.123.1( Attackers address). This results in the attackers accessing the internal server and bypassing the firewall.

>

In short, the attacker uses the mail server as a proxy to make the victim server believe the request arrises from an authorized user.

---

*Originally published on [Medium](https://infosecwriteups.com/server-side-request-forgery-ssrf-f62235a2c151). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
