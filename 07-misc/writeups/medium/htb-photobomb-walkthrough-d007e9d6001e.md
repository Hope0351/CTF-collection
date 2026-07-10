# :game_die: HTB | Photobomb | Walkthrough. The HTB - Photobomb Machine is rated as…

---

### Reconnaissance

As usual I started with active reconnaissance against the given target.

```
nmap -sC -sV 10.10.11.192
```

This gives us some interesting feedback.
In total nmap finds only two open TCP ports:
- SSH (22)
- HTTP (80)

Web Enumeration — TCP — Port 80
We will start with the inspection of Port 80, while doing some web enumeration.

Opening 10.10.11.192:80 in the webbrowser gives us back an error.
Therefore we are adding the domain-name in our /etc/hosts file.

```
sudo nano /etc/hosts
```

*General Impression*
A website about photoshop. Not much to see on the main page, except a Login page. But basic standard credentials do not work.

*Basic Enumeration*
Robots.txt File — Gives us back a strange site:

sitemap.xml — Gives us back a similar site as the robots.txt file.
curl website — Gives us nothing very interesting back.
Inspecting Website — Here we found something interesting in the Debugger Register. A JavaScript Code that gives credentials for tech supporters who forget their login-data.

We then copy the “href” URL Cookie: [http://photobomb.htb/printer](http://photobomb.htb/printer) into the Browser and receive the following message:

Once pressing the Button “OK” we are seeing a new page. The found Cookie is now stored in the Cookies Section. We are logged in with the tech-supporters pre-built Cookie-Credential. Now we can see the below new page, called /printer:

This page lets us Download Pictures with either file type JPG or PNG in different sizes.

I inspected the /printer page in more detail but found nothing interesting. While looking at the page sourcecode, I received again a pop-up message to confirm my credentials:

But again, nothing interesting is found in the source code itself.

## Get ceelineek’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

So we go back to have a look at the printer side and try to capture the Download Traffic using Burp Suite.
*(If you are using BurpSuite for the fist time, follow this guideline to set it up in Firefox: *[Configuring Firefox to work with Burp Suite — PortSwigger](https://portswigger.net/burp/documentation/desktop/external-browser-config/browser-config-firefox)*).*

- Open up BurpSuite, navigate to register “Proxy” and turn on the Intercept.

- Navigate back to the photobomb.htb/printer page and press the Download-Button.

- Go back to the BurpSuite and see if the Download-Request has been captured:

---
