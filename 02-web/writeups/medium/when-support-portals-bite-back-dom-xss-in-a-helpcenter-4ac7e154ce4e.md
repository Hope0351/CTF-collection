# :globe_with_meridians: When Support Portals Bite Back: DOM-XSS in a Helpcenter

> **Original Source:** [When Support Portals Bite Back: DOM-XSS in a Helpcenter](https://infosecwriteups.com/when-support-portals-bite-back-dom-xss-in-a-helpcenter-4ac7e154ce4e)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# When Support Portals Bite Back: DOM-XSS in a Helpcenter


[FREE LINK](https://medium.com/bugbountywriteup/when-support-portals-bite-back-dom-xss-in-a-helpcenter-4ac7e154ce4e?sk=9f3bae9bcfb903c89f8ad5e35f51aba5)


You know what’s fun? Browsing boring helpcenter pages that look like they’d never hurt a fly, until you pop open DevTools and realize they’re basically handing you a free DOM-XSS sink.


That’s exactly what I stumbled upon at support.example.com, a Freshdesk-powered portal. Spoiler: no, I didn’t pwn ExampleCorp. Yes, I did get an `alert(document.domain)` out of it.


## Step 1: Boredom + View Source


The page in question is a public knowledgebase article that proudly lists “secure servers.” Hidden inside the HTML was this neat little script block:


```
xmlHttp.open("GET","https://api.example.com/tunnels",true);
xmlHttp.responseType = "json";
xmlHttp.onload = function() {
if (xmlHttp.status === 200) {
var tunnels = xmlHttp.response;
for (var tunnel of tunnels) {
jQuery(".tunnel-list").append(
"<li><span>"+tunnel.host+"</span><span><i>"+tunnel.ip+"</i></span></li>"
);
}
}
};
```


Yes, you read that right. They take `tunnel.host` and `tunnel.ip` from the API and just string-concat them straight into the DOM. What could possibly go wrong?

## Step 2: Console Shenanigans

---

*Originally published on [Medium](https://infosecwriteups.com/when-support-portals-bite-back-dom-xss-in-a-helpcenter-4ac7e154ce4e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
