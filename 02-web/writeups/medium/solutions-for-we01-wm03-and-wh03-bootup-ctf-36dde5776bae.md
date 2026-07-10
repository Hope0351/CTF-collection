# :globe_with_meridians: BootUp CTF — Web challenges Walk through

> **Original Source:** [BootUp CTF — Web challenges Walk through](https://medium.com/p/6ab8cbb4eebe/edit)
> **Platform:** medium.com | **Category:** `WEB`

---

# BootUp CTF — Web challenges Walk through


Solutions for WE01, WM03 and WH03

## WE01:


*Basic Directory traversal*


Upon opening the webpage I see a nearly empty page, HTML, JS.


*Only pointing out that nothing is present here*


The challenge describes the key to get the flag is finding a common directory


It will painstaking to try out all the common directories in a webpages/ web application.


[URL Fuzzer](https://pentest-tools.com/website-vulnerability-scanning/discover-hidden-directories-and-files) is an online tool which does the job for us.


What does it do, you ask?*
Well it fuzzes around with the URL in order to find common directories.*Result: URL fuzzer found a directory called “/sample”


Opening the directory in the website [https://ggcs-we01.allyourbases.co/sample/](https://ggcs-we01.allyourbases.co/sample/) I facing a webpage asking me to download the Flag text file.


And, that’s it I found the flag and submitted it to claim my points.

## WM03:


The website is a page with only a static content and there way to start any API calls. I went though the HTML code, JS code in the header element was interesting.


*JS code in HTML header for ajax requests*


The AJAX requests use HTTP POST to get data with request body containing “getuser” key with a value.


I made a similar request using the RESTClient extension of Firefox.


*Response is similar to what is rendered on the website*


*Changed the key to something random*


The response from the API shown which commands it can process.


I went for the head (“getFlag” command)


*API response for getFlag*


API throws an error as getFlag command should come with a api_token.


*API response for Config*


From the config response, I got the the
“api_token”: “supersecret31337apitoken”
I used it and send a new getFlag request.


This exposes the Flag from the API.

## WH03:


I had no idea what was coming at me. Then opening the website in challenge to took me to a blank page.


*Just like this*


I started inspecting the elements, JS, HTML. There I found something interesting.


*JavaScript of the website*


This means that the key is in the JavaScript but the code is unreadable so I used [JavaScript Beautifier](https://beautifier.io/).


This will make the code readable.

*The JS code after passing through the beautifier*


I when through a lot of code to understand what this JS code is doing but I met with so many blocks on the way then I somehow found that the absurd and random b function calls are to get a meaningful string. This tested it through the console — developers tools of the page.


*“b” is function used with the JS code to obfuscate the obvious strings*


The JS code captures the Arrow keystrokes as input and renders different outputs by comparing the input to random keystroke in the sequence of inputs.


In case if wrong sequence is entered, the page will redirect to other pages sometimes to a Meme or a google search of JS.


I had initially tried to break the sequence and get the flag but after more careful examination and de-obfuscation of the JS code. I found out where the Flag is hard-coded in the JS code and used it directly to submit.


Other articles: [Google CTF — Walkthough](https://medium.com/p/6ab8cbb4eebe/edit)


*I would really appreciate your feedback and support on the content, please let me know it by sharing or commenting or clapping.*

---

*Originally published on [Medium](https://pranavakumar.medium.com/solutions-for-we01-wm03-and-wh03-bootup-ctf-36dde5776bae). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
