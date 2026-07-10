# :arrows_counterclockwise: Solving the JavaScript Deobfuscation HTB Challenge

> **Original Source:** [Solving the JavaScript Deobfuscation HTB Challenge](https://infosecwriteups.com/solving-the-javascript-deobfuscation-htb-ctf-challenge-b7054e9d6ce9)
> **Platform:** infosecwriteups.com | **Category:** `REVERSE ENGINEERING`

---

# Solving the JavaScript Deobfuscation HTB CTF Challenge


*Created by Lexica.art*


In this article, we’ll explain how to finish the JavaScript Deobfuscation challenge from Hack The Box (HTB). We need to analyse and deobfuscate JavaScript code in order to get a secret flag in order to finish this challenge. The steps used to overcome the challenge will be discussed in detail for each phase.

### Step 1: Initial Analysis


First, we visit the provided URL (`http://94.237.54.69:48876/`) and inspect the page source. We find an HTML file with embedded JavaScript code. Our goal is to deobfuscate the ‘secret.js’ file to obtain the flag.


```
</html>
<!DOCTYPE html>

<head>
<title>Secret Serial Generator</title>
<style>
*,
html {
margin: 0;
padding: 0;
border: 0;
}

html {
width: 100%;
height: 100%;
}

body {
width: 100%;
height: 100%;
position: relative;
background-color: #6fb3eb;
}

.center {
width: 100%;
height: 50%;
margin: 0;
position: absolute;
top: 50%;
left: 50%;
transform: translate(-50%, -50%);
color: white;
font-family: "Helvetica", Helvetica, sans-serif;
text-align: center;
}

h1 {
font-size: 144px;
}

p {
font-size: 64px;
}
</style>
<script src="secret.js"></script>
<!-- HTB{4lw4y5_r34d_7h3_50urc3} -->
</head>

<body>
<div class="center">
<h1>Secret Serial Generator</h1>
<p>This page generates secret serials!</p>
</div>
</body>

</html>
```


### Step 2: Deobfuscating ‘secret.js’


We encounter an obfuscated JavaScript code block within the HTML file. The deobfuscated code reveals a function named ``generateSerial()``, which generates a secret serial and makes a POST request to ‘`/serial.php`’.


```
eval(function (p, a, c, k, e, d) { e = function (c) { return c.toString(36) }; if (!''.replace(/^/, String)) { while (c--) { d[c.toString(a)] = k[c] || c.toString(a) } k = [function (e) { return d[e] }]; e = function () { return '\\w+' }; c = 1 }; while (c--) { if (k[c]) { p = p.replace(new RegExp('\\b' + e(c) + '\\b', 'g'), k[c]) } } return p }('g 4(){0 5="6{7!}";0 1=8 a();0 2="/9.c";1.d("e",2,f);1.b(3)}', 17, 17, 'var|xhr|url|null|generateSerial|flag|HTB|1_4m_7h3_53r14l_g3n3r470r|new|serial|XMLHttpRequest|send|php|open|POST|true|function'.split('|'), 0, {}))
```


### Step 3: Making a POST Request


We follow the instructions and send a ‘POST’ request to ‘`http://94.237.54.69:48876/serial.php`'. The response we receive contains an encoded string.


```
'use strict';
function generateSerial() {
var flag = "HTB{1_4m_7h3_53r14l_g3n3r470r!}";
var xhr = new XMLHttpRequest;
var url = "/serial.php";
xhr.open("POST", url, true);
xhr.send(null);
}
;
```


### Step 4: Decoding the Response


We need to determine the encoding used in the string received from the previous step. By analyzing the format of the encoded string, we identify it as Base64 encoding. We decode the string to obtain the flag.


```
HTTP/1.1 200 OK
Date: Wed, 12 Jul 2023 16:21:42 GMT
Server: Apache/2.4.41 (Ubuntu)
Content-Length: 32
Connection: close
Content-Type: text/html; charset=UTF-8

N2gxNV8xNV9hX3MzY3IzN19tMzU1NGcz
```


### Step 5: Obtaining the Flag


Using the decoded output from the previous step, we send another ‘POST’ request to ‘`http://94.237.54.69:48876/serial.php`'. We set the data parameter as “`serial=YOUR_DECODED_OUTPUT`”. The response we receive contains the flag.


```
curl http://94.237.54.69:48876/serial.php -X POST -d "serial=7h15_15_a_s3cr37_m3554g3"
HTB{ju57_4n07h3r_r4nd0m_53r14l}
```


## Skills Assessment:


The article also includes a skills assessment section, where we encounter a similar challenge. We analyze the HTML code of a different webpage, identify the JavaScript code being used, and run it to observe the output.

### Step 6: Analyzing and Deobfuscating JavaScript Code


We find the JavaScript code in the HTML source and notice that it is obfuscated. Using the techniques we learned, we deobfuscate the code to retrieve the flag variable.


```
</html>
<!DOCTYPE html>

<head>
<title>Secret Serial Generator</title>
<style>
*,
html {
margin: 0;
padding: 0;
border: 0;
}

html {
width: 100%;
height: 100%;
}

body {
width: 100%;
height: 100%;
position: relative;
background-color: #6fb3eb;
}

.center {
width: 100%;
height: 50%;
margin: 0;
position: absolute;
top: 50%;
left: 50%;
transform: translate(-50%, -50%);
color: white;
font-family: "Helvetica", Helvetica, sans-serif;
text-align: center;
}

h1 {
font-size: 144px;
}

p {
font-size: 64px;
}
</style>
<script src="api.min.js"></script>
</head>

<body>
<div class="center">
<h1>API Keys</h1>
<p>API Keys control panel</p>
</div>
</body>

</html>
```


Open `src="api.min.js"` and get this:


```
eval(function (p, a, c, k, e, d) { e = function (c) { return c.toString(36) }; if (!''.replace(/^/, String)) { while (c--) { d[c.toString(a)] = k[c] || c.toString(a) } k = [function (e) { return d[e] }]; e = function () { return '\\\\w+' }; c = 1 }; while (c--) { if (k[c]) { p = p.replace(new RegExp('\\\\b' + e(c) + '\\\\b', 'g'), k[c]) } } return p }('t 5(){6 7=\\'1{n\\'+\\'8\\'+\\'9\\'+\\'a\\'+\\'b\\'+\\'c!\\'+\\'}\\',0=d e(),2=\\'/4\\'+\\'.g\\';0[\\'f\\'](\\'i\\',2,!![]),0[\\'k\\'](l)}m[\\'o\\'](\\'1{j\\'+\\'p\\'+\\'q\\'+\\'r\\'+\\'s\\'+\\'h\\'+\\'3}\\');', 30, 30, 'xhr|HTB|_0x437f8b|k3y|keys|apiKeys|var|flag|3v3r_|run_0|bfu5c|473d_|c0d3|new|XMLHttpRequest|open|php|n_15_|POST||send|null|console||log|4v45c|r1p7_|3num3|r4710|function'.split('|'), 0, {}))
```


Go `http://www.jsnice.org/` and past it and get this:


```
'use strict';
function apiKeys() {
var flag = "HTB{n" + "3v3r_" + "run_0" + "bfu5c" + "473d_" + "c0d3!" + "}";
var xhr = new XMLHttpRequest;
var url = "/keys" + ".php";
xhr["open"]("POST", url, !![]);
xhr["send"](null);
}
console["log"]("HTB{j" + "4v45c" + "r1p7_" + "3num3" + "r4710" + "n_15_" + "k3y}");
```


`HTB{j4v45cr1p7_3num3r4710n_15_k3y}`

---

*Originally published on [Medium](https://infosecwriteups.com/solving-the-javascript-deobfuscation-htb-ctf-challenge-b7054e9d6ce9). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of reverse engineering CTF writeups.*
