# :globe_with_meridians: Day 3 Dom Xss In Innerhtml Sink Using Source Location Search Zero To Hero Series

> **Original Source:** [Day 3 Dom Xss In Innerhtml Sink Using Source Location Search Zero To Hero Series](https://infosecwriteups.com/day-3-dom-xss-in-innerhtml-sink-using-source-location-search-zero-to-hero-series-portswigger-3795cf43eab7)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

What is DOM?


*DOM stands for Document Object Model; it’s a model that browsers use to render a web page. The DOM represents a web page’s structure; it defines the basic properties and behaviour of each HTML element and helps scripts dynamically access and modify the page’s content, structure, and style.*


What is DOM XSS?


*A DOM-based XSS attack is possible if the web application writes data to the Document Object Model without proper sanitisation. The attacker can manipulate this data to include XSS content on the web page, for example, malicious JavaScript code.*


Note: -

## Source:


*It is one of JavaScript's properties that accepts data, which is controlled by the attacker is known as the source. For instance, location.search property as this property reads input from the query string, which is easy to control by the attacker. *This means that any property that the attacker can control is a potential source. ( Some of the sources example listed below)
document.URL
document.documentURI
document.URLUnencoded
document.baseURI
location
document.cookie
document.referrer
window.name
history.pushState
history.replaceState
localStorage
sessionStorage

## Sink:


*Every DOM-based XSS vulnerability has two elements: the source of user input and the target where this user input is written, called a sink.
*Some examples of common sinks.
document.write()
window.location
document.cookie
eval()
document.domain
WebSocket()
element.src
postMessage()
setRequestHeader()
FileReader.readAsText()
ExecuteSql()
sessionStorage.setItem()
document.evaluate()
JSON.parse()
element.setAttribute()


## Get RayofHope’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


*Now that we understand what the DOM is and how it works, let’s go back to the lab and practice it.*

---

*Originally published on [Medium](https://infosecwriteups.com/day-3-dom-xss-in-innerhtml-sink-using-source-location-search-zero-to-hero-series-portswigger-3795cf43eab7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
