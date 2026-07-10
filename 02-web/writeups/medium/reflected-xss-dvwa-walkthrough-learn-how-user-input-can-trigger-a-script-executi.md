# :globe_with_meridians: Reflected XSS → DVWA Walkthrough: Learn How User Input Can Trigger a Script Execution

> **Original Source:** [Reflected XSS → DVWA Walkthrough: Learn How User Input Can Trigger a Script Execution](https://infosecwriteups.com/reflected-xss-dvwa-walkthrough-learn-how-user-input-can-trigger-a-script-execution-3c9f9f26962b)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

[ Security-Level : MEDIUM ]


Let’s put the payload again:


*[ Input field ]*


Now you can see that our payload isn’t working here. When you look at the response, it’s being treated as plain text. But why isn’t the <script> tag printed? We can assume it’s being ignored or filtered. We actually increased the security level a bit. So does this mean XSS doesn’t work here? Nope. What would you do in this situation?


There are different ways to bypass filters, so listen carefully, if our payload doesn’t work, they might be filtering it. We need to craft suitable payloads and keep testing different variants until one succeeds. So how do we craft the payload?


First, I’ll show you how it’s done:


*[ Input field ]*


Just submit this payload!


*[ xss ]*Boom! We triggered the XSS again…


Why did it work? Just observe the payload:


First Payload:


```
<script>alert('xss')</script>
```


Second Payload:


```
<Script>alert('xss')</Script>
```


Take a look at both payloads and see the difference. Notice the tag we used I changed <script> to <script>. The filter was misconfigured, so it only blocked lowercase <script> and didn’t block <script>. If you didn’t understand that, don’t worry. Just look here—let’s see what’s happening behind the scenes.


```
<?php

header ("X-XSS-Protection: 0");

// Is there any input?
if( array_key_exists( "name", $_GET ) && $_GET[ 'name' ] != NULL ) {
// Get input
$name = str_replace( '<script>', '', $_GET[ 'name' ] );

// Feedback for end user
echo "<pre>Hello ${name}</pre>";
}

?>
```


Look here at this specific area:


```
$name = str_replace('<script>', '', $_GET['name']);
echo "<pre>Hello ${name}</pre>";
```


look the conditon in here it only removes the exact string “<script>”(lowercase, no spaces, no attributes), so that means what ever we input the payload expect <script> , so what will happen next?


the PHP’s str_replace is case‑sensitive, so it will not remove:


```
<Script>
<SCRIPT>
<script >
```


So we can craft payloads using different tag variations and still trigger XSS. Pretty cool, right? But how do we find the right payload? In real scenarios, you don’t have access to the source code to see the misconfiguration. So how do you figure it out? It’s up to you by understanding how the input field works and how the response is reflected back. Like I said earlier, just start by putting the normal payload:


```
<script>alert('xss')</script>
```


You’ve understood how the response looks, but you can also inspect the source of webpages by pressing F12 or opening the Developer Tools. This way, you can understand how it works too.”


*[ Dev tools ]*


You’ve learned two things: you can understand how the application behaves by looking at the echoed response or inspecting the page with Developer Tools, and you can craft different payloads depending on the situation.


here is the useful resource, save it somewhere it may very helpful:


You can easily craft different types of XSS payloads from here.


[ Security-Level : HIGH]


Let’s test some payloads:


*[ Input field ]*


Not working. Okay, let’s try the next payload.


*[ Input field ]*


It’s not working! But what’s happening here? The security has been increased, and earlier the filtering was misconfigured but now they’ve fixed that too. First, look at the response: it echoes as ‘Hello >’ and doesn’t show the full payload. This means we can understand that the input is being filtered.


```
<script>
<Script>
```


But the > character was still echoed, so we can assume that the <script> tag is being filtered. I tried different variations of the <script> tag, but none of them worked. But as I said earlier, whenever we see an input field, we should always test this payload.


```
<script>alert('xss')</script>
```


But in your mind, you might think about changing <script> to <Script> or SCRIPT, but it’s not working here. So the question is: can we trigger XSS without using the <script> tag? Is it possible to use a different tag?

>

Yes, absolutely. I already told you before that we can craft XSS payloads in different ways based on different situations. So I hope you checked the XSS cheat sheet I shared earlier in the Medium level.


When you look at the cheat sheet, you’ll notice I crafted a suitable payload that can trigger XSS and it doesn’t even use the <script> tag.


*[ Cheat sheet ]*


Let’s test it:


*[ Input field ]*


Just submit the payload:


*[ xss ]*Boom! We triggered the XSS again…


Let’s examine our payload:


```
<img src/onerror=alert('xss')>
```


This creates an image element. The browser tries to load the image from src and when it fails, the onerrorevent runs and that event can contain JavaScript. So the alert(‘xss’) runs when the image load fails. A more common, clearer form is:


```
<img src=x onerror=alert('xss')>
```


Here src = ‘x’ is an invalid image URL so the image fails to load and onerror fires.


If you don’t know how the <img> tag works or how to use it, here’s a reference:


Here is the demo:


What is onerror?


onerror is an HTML event attribute. It tells the browser what to do when something goes wrong, like when an image or script fails to load.


```
<img src=x onerror=alert('xss')>
```


If the browser can’t find ‘x’ it triggers the onerror event and runs the JavaScript there we palced the alert function alert(‘xss’) .


Let’s look at what’s happening behind the scenes:


```
<?php

header ("X-XSS-Protection: 0");

// Is there any input?
if( array_key_exists( "name", $_GET ) && $_GET[ 'name' ] != NULL ) {
// Get input
$name = preg_replace( '/<(.*)s(.*)c(.*)r(.*)i(.*)p(.*)t/i', '', $_GET[ 'name' ] );

// Feedback for end user
echo "<pre>Hello ${name}</pre>";
}

?>
```


The app only looks for the word script and removes that.The attacker used img + onerror, which is a different way to run JavaScript.Result: the filter misses it, the browser executes the onerror code, and XSS happens.


[ Security-Level : IMPOSSIBLE]


*[ xss ]*


They’ve added more security to prevent XSS attacks:


```
<?php

// Is there any input?
if( array_key_exists( "name", $_GET ) && $_GET[ 'name' ] != NULL ) {
// Check Anti-CSRF token
checkToken( $_REQUEST[ 'user_token' ], $_SESSION[ 'session_token' ], 'index.php' );

// Get input
$name = htmlspecialchars( $_GET[ 'name' ] );

// Feedback for end user
echo "<pre>Hello ${name}</pre>";
}

// Generate Anti-CSRF token
generateSessionToken();

?>
```


It’s impossible to perform XSS here, they’ve effectively prevented reflected XSS.


What this code does:


1, It checks if the page received a name value in the URL (like ?name=adw..)


2, It calls checkToken(…) to validate a CSRF token (that’s for preventing cross-site request forgery a different security problem).

>

A CSRF token is like a secret handshake between your browser and the website only real forms from the site know it, so attackers can’t fake your actions.


3, It runs the input through htmlspecialchars() this turns < into &lt; and > into &gt; , so any <script> a user sends becomes plain text instead of code.


4, Then it prints Hello {user} inside the page. Because the input was escaped, the browser shows the raw characters and won’t run any JavaScript, so this prevents reflected XSS in this place.

*[ GIF sourced from tenor. Rights belong to the creator. ]*

>

If you suspect an XSS‑vulnerable field, try every possible payload. Check the response, inspect the page, craft payloads from cheat sheets, and keep testing even if it fails, try again and again until it succeeds. You can discover different tags, events, and bypass tricks for different situations. In real‑world applications, you’ll face WAFs (Web Application Firewalls), rate‑limiting, and many stronger protections than these basic filters. That’s why you must research, explore bypass techniques, and stay updated.


Here are some useful references on filter‑bypass methods hope they help:

---

*Originally published on [Medium](https://infosecwriteups.com/reflected-xss-dvwa-walkthrough-learn-how-user-input-can-trigger-a-script-execution-3c9f9f26962b). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
