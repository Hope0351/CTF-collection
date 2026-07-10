# :globe_with_meridians: When Support Portals Bite Back: DOM-XSS in a Helpcenter

---

# When Support Portals Bite Back: DOM-XSS in a Helpcenter

FREE LINK

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
