# :game_die: LetsDefend ==> Phishing Email Challenge

> **Original Source:** [LetsDefend ==> Phishing Email Challenge](https://infosecwriteups.com/letsdefend-phishing-email-challenge-e470c06e6d2b)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# LetsDefend ==> Phishing Email Challenge


Welcome to this new post in which we will be solving a beginner level challenge of the LetsDefend platform.

## Scenario


Your email address has been leaked and you receive an email from Paypal in German. Try to analyze the suspicious email.

## Goal


This challenge requires you to determine if the email received is a phishing attack or not.

>

Before starting the process of analyzing the eml file, let’s define some important concepts to be considered


## What´s an EML file?


An EML file is an email message saved by an email application, such as Microsoft Outlook or Apple Mail. It contains the content of the message, along with the subject, sender, recipient(s), and date of the message. EML files may also store one or more email attachments, which are files sent with the message.

## What´s a VirusTotal?


Is a free to use web application with which you can analyze any suspicious file, application, URL, IP address or hash function. This way, before installing, opening or running any application, you can perform a quick and easy scan over the Internet.


## Get Cyb3r-Kr4k3s’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


VirusTotal works by integrating more than 50 antivirus and more than 60 detection engines. Among many others, you can find:

>

Kaspersky.
CyRadar.
Emsisoft.
Antiy-AVL.
Opera.
Tencent.
Sophos.
PhishLabs


## Tools


>

VirusTotal & Kaspersky Threat Intelligence Portal


Visual Studio Code


emlAnalyzer


Well, having in mind the concepts mentioned above, now let’s analyze the .eml file.

## Question 1.- What is the return path of the email?


To find the return path of an emal, it is necessary to run a Python script called emlAnalyzer, usually the return path is the one to which the reply will be sent to the attacker who sent the email.

### Running emlAnalyzer tool


To find the path you need to execute the following command in a linux terminal


*emlAnalyzer Command*


After executing the command we look for the return path header


*Return Path Header*

### Running vscode tool


*Return Path*

>

*A: {{ bounce@rjttznyzjjzydnillquh.designclub.uk.com }}*


## Q2.-What is the domain name of the url in this mail?


Same situation as in the previous question we will use the emlAnalyzer script and VS Code.

### Running emlAnalyzer tool


To find the path you need to execute the following command in a linux terminal


this command will show us the URLs contained in the eml file


### Running vscode tool


When opening the eml file in VS Code you only need to look for the URL found in the <a href> tags as shown in the screenshot below


*Domain Name*

>

*A: {{ *storage.googleapis.com* }}*


## Q 3.- Is the domain mentioned in the previous question suspicious?


This point of the analysis we are performing is important because of two situations that I am going to show below

### Running VirusTotal


- - If only the domain found is analyzed based on VirusTotal results it is not a malicious URL.


*Analyze VirusTotal*


2.- Well, taking into account the previous result, it is recommended to analyze the complete URL found in the eml file.


### Running Kaspersky Threat Intelligence Portal


- - If only the domain found is analyzed based on Kaspersky Threat Intelligenceresults it is not a malicious URL.


*Analyze Kaspersky Threat Intelligence Portal*


2.-Well, taking into account the previous result, it is recommended to analyze the complete URL found in the eml file.


>

*A: {{ yes}}*


## Q 4.- What is the body SHA-256 of the domain?


To identify the SHA-256 of the domain, we are going to repeat the analysis performed with VirusTotal, within the results there is a section of details, once inside this section we look for the BODY SHA-256


>

A: ==> Body SHA-256{{ 13945ecc33afee74ac7f72e1d5bb73050894356c4bf63d02a1a53e76830567f5}}


## Q 5.- Is this email a phishing email?


With all the analysis previously done, we can conclude that the email is a Phishing Attack.


A: {{ yes }}


Thank you for reading my post feel free to share it on your social networks and friends to spread the knowledge to the right people.


Greetings and success

---

*Originally published on [Medium](https://infosecwriteups.com/letsdefend-phishing-email-challenge-e470c06e6d2b). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
