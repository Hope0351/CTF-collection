# :game_die: Natas1 - Wargames solutions writeup

---

# Natas1 — Wargames solutions writeup

Hello and welcome back. Today, we shall solve the next challenge in this series which is natas1

Link to natas1 challenge: [http://natas1.natas.labs.overthewire.org/](http://natas1.natas.labs.overthewire.org/)

Let’s get into it. So, in this challenge website, we get the page as shown below

### Solution 1: Using the browser tools itself

*Homepage of natas1 challenge*

It says that the password is on this page itself but rightclicking has been blocked.

But I find that in my Brave browser I am currently using, rightclicking is still possible. That itself indicates a first loophole in this challenge. The way to block these rightclick events involves writing some JavaScript that blocks these mouse (or even keyboard events that we want to). But browsers like Brave are intelligent enough to avoid executing unwanted JavaScript to give users a better experience (that is how it blocks ads from being shown). The working of certain JavaScript programs depend from browser to browser as different browsers implement APIs differently and these implementations have their own bugs and quirks.

But assuming that I rightclick does’nt work I’ll still show you how this challenge is solved.

Press Ctrl+Shift+I on your keyboard

Go to the Elements tab in your browser’s Dev Tools and click the down arrow present on <div id=”content”> element. You can clearly see an HTML comment with the password for the next level.

*Viewing natas1 homepage source code with browser dev tools*

Please ignore the lines containing “sqrx” as they are injected by an extension called sqrx that I use in my browser.

Next, we shall see a much more robust way to solve this challenge without relying on browser controls to see source code and other resources.

### Solution 2: Using a proxy tool

We shall use a web proxy. BurpSuite is the most popular one and there are many alternatives out there too.

## Get Adithya M S’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

If you are using a Chrome based browser, this is how you should enable BurpSuite to intercept requests coming from your browser.

- Load the CA certificate of BurpSuite or any other proxy tool you are using into your browser. You can read the official blog by portswigger on how to do this.

- Then go to browser settings and search for proxy

- You would see an option to change computer proxy settings, click on it and then you would see the below menu

*Proxy settings menu on my Windows machine*

- Click on the setup button below the Manual proxy setup heading

*Proxy settings to use BurpSuite*

- Now open BurpSuite on your system

- Configure your proxy to intercept ONLY requests to [http://natas1.natas.labs.overthewire.org](http://natas1.natas.labs.overthewire.org/) . There are various BurpSuite Tutorials that teach you how to do this

- Go to proxy tab and set “Intercept On”

After all this, load the Url, [http://natas1.natas.labs.overthewire.org/](http://natas1.natas.labs.overthewire.org/) on your browser and have the proxy intercept this request. Send the request to the Repeater module, and send it again through repeater to see the request and response come side by side.

*Response to request for natas1 homepage*

You can clearly see the password in this response!!

You may again think what is the significance of this challenge in terms of real world web applications. The answer is very similar to what I have explained in the previous blog. Developers may write JavaScript to block certain browser controls on the client side of the website but still leave confidential data such as passwords to theit admin portals, or API keys in the comments.

Browsers blocking certain actions does not mean that the frontend code cannot be viewed. We can always use a proxy like BurpSuite to view the responses directly.

Thanks for reading guys!! Give me claps 👏 if you enjoyed it and want to learn more of web security concepts from my blog series.

---
