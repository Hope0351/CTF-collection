# :globe_with_meridians: 10 Common XSS Payloads and How to Use Them for Bug Bounty Hunting

> **Original Source:** [10 Common XSS Payloads and How to Use Them for Bug Bounty Hunting](https://infosecwriteups.com/10-common-xss-payloads-and-how-to-use-them-for-bug-bounty-hunting-9c49cb54297a)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# 10 Common XSS Payloads and How to Use Them for Bug Bounty Hunting


*Photo by [Caspar Camille Rubin](https://unsplash.com/@casparrubin?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText) on [Unsplash](https://unsplash.com/s/photos/hacking?utm_source=unsplash&utm_medium=referral&utm_content=creditCopyText)*


As technology advances, the techniques of exploiting vulnerabilities in web applications also become more sophisticated. One such vulnerability is cross-site scripting (XSS), which can be used to inject malicious code into a website or web application, allowing an attacker to steal sensitive data, manipulate user sessions, or even take full control of the web server. In this blog post, we will analyze several XSS payloads and explain how they work.

### Chrome XSS-Auditor Bypass by @vivekchsm


The Chrome XSS-Auditor is a built-in security feature that prevents reflected XSS attacks in Google Chrome. However, it is not foolproof and can be bypassed using certain techniques. One such technique is the SVG XSS payload created by @vivekchsm.


Payload:


```
<svg><animate xlink:href=#x attributeName=href values=&#106;avascript:alert(1) /><a id=x><rect width=100 height=100 /></a>This payload injects a malicious script into an SVG element. The script sets the href attribute of the animate element to javascript:alert(1), which will execute the alert function when clicked. Since the script is injected into an SVG element, the Chrome XSS-Auditor fails to detect it.
```


### Chrome < v60 beta XSS-Auditor Bypass


Before version 60 of Chrome, the XSS-Auditor could be bypassed using a data URL with a newline character.


Payload:


```
<script src="data:,alert(1)%250A-->
```


This payload uses a data URL to load a script that executes the alert function. The `%250A` character is a URL-encoded newline character, which bypasses the Chrome XSS-Auditor.

### Other Chrome XSS-Auditor Bypasses


Other ways to bypass the Chrome XSS-Auditor include using null bytes and using script tags with alternate character sets.


Payload:


```
<script>alert(1)</script
<script>alert(1)%0d%0a-->%09</script
<x>%00%00%00%00%00%00%00<script>alert(1)</script>
```


These payloads inject a script tag that executes the alert function. The null bytes in the third payload are used to bypass the Chrome XSS-Auditor, while the second payload uses a combination of carriage return, line feed, and tab characters to obfuscate the script.

### Safari XSS Vector by @mramydnei


This XSS payload is specific to the Safari web browser.


Payload:


```
<script>location.href;'javascript:alert%281%29'</script>
```


This payload injects a script that sets the location.href property to `'javascript:alert(1)'`. When executed, the script will navigate to a new page with the `javascript:alert(1)` URL, which will execute the alert function.

### XSS Polyglot by Ahmed Elsobky


An XSS polyglot is a payload that can be interpreted as valid code in multiple programming languages.


## Get Security Lit Limited’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Payload:


```
jaVasCript:/*-/*`/*\`/*'/*"//(//oNcliCk=alert() )//%0D%0A%0d%0a//</stYle/</titLe/</teXtarEa/</scRipt/--!>\x3csVg/<sVg/oNloAd=alert()//>\x3e
```


This payload is an XSS polyglot that can be interpreted as valid JavaScript, HTML, and CSS code. It injects a script that sets the onClick attribute of an HTML element to `alert()`. The CSS code is used to hide the injected script from view.

### Kona WAF (Akamai) Bypass


This payload is designed to bypass the Kona WAF (Web Application Firewall) implemented by Akamai. It takes advantage of the lack of proper sanitization of user input in the WAF. The payload itself consists of a combination of characters that will not trigger any blocking by the WAF. The payload consists of:


```
\');confirm(1);//
```


This payload is meant to be used in an input field vulnerable to XSS. When executed, it will close the current script tag, add a confirm dialog box to prompt the user, and then add a comment to close the script tag. The backslash before the single quote is used to escape the quote so that it does not prematurely end the script tag.

### ModSecurity WAF Bypass


This payload is designed to bypass the ModSecurity WAF. It is a bit more complex than some of the other payloads, as it takes advantage of a feature of ModSecurity where certain input data can be split into separate variables. The payload itself consists of:


```
<img src=x onerror=prompt(document.domain) onerror=prompt(document.domain) onerror=prompt(document.domain)>
```


This payload takes advantage of the fact that ModSecurity will split certain input data into separate variables. In this case, the ‘onerror’ attribute of the img tag is split into three separate variables, each of which executes the same prompt dialog box to display the current document domain. Because the WAF only looks at individual variables, it is able to bypass the filtering and execute the payload.


Wordfence XSS Bypasses


Wordfence is a security plugin for WordPress sites that includes a firewall to protect against XSS attacks. However, it is not perfect and can be bypassed using the following payloads:


```
<meter onmouseover="alert(1)"
```


This payload is designed to bypass the Wordfence firewall by taking advantage of the fact that it does not filter certain HTML tags. In this case, the meter tag is used, along with an onmouseover event that triggers an alert dialog box.


```
'">><div><meter onmouseover="alert(1)"</div>"

```


This payload is similar to the previous one, but it uses a nested div tag to hide the meter tag. This is done to bypass any filters that may be in place that block the use of the meter tag.


```
<marquee loop=1 width=0 onfinish=alert(1)>
```


This payload is designed to bypass Wordfence by using a marquee tag to hide the alert message. The loop attribute is set to 1 so that the message continues to repeat, and the width attribute is set to 0 so that the message is hidden from view. The finish event triggers the alert dialog box when the message finishes repeating itself.

### Conclusion


XSS vulnerabilities can be a serious issue for web applications, allowing attackers to execute malicious code on a victim’s machine. However, with the right tools and knowledge, these vulnerabilities can be discovered and exploited by ethical hackers to help improve the security of web applications. The payloads listed in this article provide a starting point for finding and exploiting XSS vulnerabilities and can be used by bug bounty hunters and security researchers to identify and report such vulnerabilities. It is important to note, however, that these payloads should only be used for ethical hacking purposes and should never be used for malicious purposes.


Please check out our blog for more articles related to cybersecurity — [www.thoughttide.com](http://www.thoughttide.com)


Refe:[https://github.com/EdOverflow/bugbounty-cheatsheet/blob/master/cheatsheets/xss.md](https://github.com/EdOverflow/bugbounty-cheatsheet/blob/master/cheatsheets/xss.md)

---

*Originally published on [Medium](https://infosecwriteups.com/10-common-xss-payloads-and-how-to-use-them-for-bug-bounty-hunting-9c49cb54297a). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
