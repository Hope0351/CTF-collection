# :globe_with_meridians: Increasing XSS impact using XSScope

---

# Increasing XSS impact using XSScope

During Bug Hunting, everyone aims for triggering the “1” alert. However, if you want to escalate your impact of XSS, now you can do this easily by using XSScope.

## *What is XSScope?*

What is XSScope? XSScope is an advanced XSS payload generator platform for Client-Side attacks and also with an aim of increaing the impact of an XSS during Bug Hunting. Using all modules that XSScope offers, advanced XSS can be simply use with 1–2 click(s).

Github page of XSScope: [https://github.com/kleiton0x00/XSScope](https://github.com/kleiton0x00/XSScope)

## Demo usage

I have found a website which is vulnerable to XSS and doesn’t filter any kind of malicious JS code.

First, let’s try injection HTML code.

We can see that after clicking “search” button, our payload got reflected into HTML code. Now let’s see if we can inject Javascript code. This time, I will enter a Javascript payload.

```
<script>alert(1)</script>
```

Our payload got successfully executed without being filtered and we got our lovely alert trigger.

## *Go beyond the alert! — with XSScope*

Go to [https://github.com/kleiton0x00/XSScope](https://github.com/kleiton0x00/XSScope) and clone the project.

```
git clone [https://github.com/kleiton0x00/XSScope](https://github.com/kleiton0x00/XSScope)
python3 xsscope.py
```

A GUI software will open, so go to Main -> Add HTML code
A new tab will popup, like in the image below.

Now click on “Choose Pre-generated HTML code” and click on which website you like to generate a Phishing Clone. In this case, I will choose “Amazon Login Form”. The whole code will be added into the text box automatically, so click Apply Code.

Now click on Main -> XSS Payloads and a new window will popup.

There will be 10 payloads ready to be deployed, but I’m copying the first payload since *<script>alert(1)</script>* worked before.

## Get kleiton0x7e’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Paste the payload into the website and the Phishing Website will be displayed.

*Generating Amazon Phishing Website using XSS*

Now the victim will simply add his credentials into the phishing website.

The credentials will be stored in /XSScope/login_phishing/credentials/

*Credentials captured*

## Other features of XSScope

### ~~ Spying Features ~~

- Camera Hijacking

- Get every Entry form value that victim enters in the website

- Grab victim’s cookies

- Keylogger

### ~~ HTML code injection ~~

- Generate Phishing Websites with 2 using pregenerated HTML codes such as:
Amazon, Google, Line, LinkedIn, Steam, Twitch, Verizon, WiFi and so on…

- Generate Website Deface

- Import HTML file from external file

- Add your own HTML code

### ~~ Funny modules ~~

- Change every link in the website

- Change every image in the website

- Clickjacker (redirect to another URI once user click somewhere on the website)

For any question, please contact me on: kurtikleiton@gmail.com
Happy hacking!

---
