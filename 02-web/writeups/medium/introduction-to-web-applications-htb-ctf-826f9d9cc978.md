# :globe_with_meridians: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/introduction-to-web-applications-htb-ctf-826f9d9cc978)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Introduction to Web Applications HTB LAB


*Created by Lexica.art*


In this article, we will walk through the solutions to the challenges in the “Introduction to Web Applications” Capture The Flag (CTF) on Hack The Box (HTB). We will provide detailed explanations and answers to each challenge, covering topics such as HTML tags, CSS properties, website vulnerabilities, and more.

## Challenge 1: HTML Image Tag


The first challenge asks for the HTML tag used to display an image. The correct answer is `**<img>**`.

## Challenge 2: CSS Text Alignment


The second challenge requires identifying the CSS property and value used to align text to the left. The correct answer is `**text-align: left;**`.

## Challenge 3: Exposed Password


In this challenge, we are instructed to check the login form for exposed passwords. By examining the provided HTML code, we can see that the test credentials are `**admin:HiddenInPlainSight**`. Thus, the password to be submitted as the answer is `**HiddenInPlainSight**`.


```
curl 167.99.207.3:31969 -v
* Trying 167.99.207.3:31969...
* Connected to 167.99.207.3 (167.99.207.3) port 31969 (#0)
> GET / HTTP/1.1
> Host: 167.99.207.3:31969
> User-Agent: curl/7.88.1
> Accept: */*
>
< HTTP/1.1 200 OK
< Date: Fri, 07 Jul 2023 14:08:16 GMT
< Server: Apache/2.4.41 (Ubuntu)
< Last-Modified: Fri, 11 Dec 2020 13:01:53 GMT
< ETag: "51b-5b62fe5763240"
< Accept-Ranges: bytes
< Content-Length: 1307
< Vary: Accept-Encoding
< Content-Type: text/html
<
<!DOCTYPE html>
<html>
<style>
body {
background-color: #151D2B;
}

form {
background-color: #1A2332;
width: 25%;
margin: auto;
border-radius: 10px;
color: white;
font-family: Arial, Helvetica, sans-serif;
}

input[type=text],
input[type=password] {
background-color: #101927;
width: 100%;
padding: 12px 20px;
margin: 8px 0;
display: inline-block;
border: 1px solid #101927;
box-sizing: border-box;
border-radius: 10px;
color: white;
}

button {
background-color: #2A86FF;
color: white;
padding: 14px 20px;
margin: 8px 0;
border: none;
cursor: pointer;
width: 100%;
border-radius: 10px;
}

button:hover {
opacity: 0.8;
}

.container {
padding: 16px;
}
</style>
<form action="#" method="post">

<div class="container">
<label for="uname"><b>Username</b></label>
<input type="text" required>

<label for="psw"><b>Password</b></label>
<input type="password" required>

<!-- TODO: remove test credentials admin:HiddenInPlainSight -->

<button type="submit">Login</button>
</div>
</form>

* Connection #0 to host 167.99.207.3 left intact
</html>
```


## Challenge 4: Displayed Text from Payload


The fourth challenge asks what text would be displayed on a page when using a specific payload. The provided payload is `**<a href="<http://www.hackthebox.com>">Click Me</a>**`. By executing a GET request to the given URL, we receive the following response: "Your name is Click Me".


```
curl 167.99.207.3:30092 -v
* Trying 167.99.207.3:30092...
* Connected to 167.99.207.3 (167.99.207.3) port 30092 (#0)
> GET / HTTP/1.1
> Host: 167.99.207.3:30092
> User-Agent: curl/7.88.1
> Accept: */*
>
< HTTP/1.1 200 OK
< Date: Fri, 07 Jul 2023 14:15:40 GMT
< Server: Apache/2.4.41 (Ubuntu)
< Set-Cookie: cookie=XSSisFun; expires=Sun, 06-Aug-2023 14:15:40 GMT; Max-Age=2592000; path=/
< Vary: Accept-Encoding
< Content-Length: 414
< Content-Type: text/html; charset=UTF-8
<
<!DOCTYPE html>
<html>


<body>
<button onclick="inputFunction()">Click to enter your name</button>
<p id="output"></p>

<script>
function inputFunction() {
var input = prompt("Please enter your name", "");

if (input != null) {
document.getElementById("output").innerHTML = "Your name is " + input;
}
}
</script>
</body>

* Connection #0 to host 167.99.207.3 left intact
</html>
```


## Challenge 5: Exploiting XSS Vulnerability


For this task, retrieving the cookie value from a web page involves using an XSS vulnerability, or cross-site scripting. To do this, two approaches are shown.


## Get Ahmet Talha Şen’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Method 1: By injecting the following payload, we can trigger an alert with the cookie value:


```
#"><img src=/ onerror=alert(document.cookie)>
```


Method 2: By using cURL to fetch the page and inspect the response headers, we can obtain the cookie value. The provided command is:


```
curl 167.99.207.3:30092 -v
* Trying 167.99.207.3:30092...
* Connected to 167.99.207.3 (167.99.207.3) port 30092 (#0)
> GET / HTTP/1.1
> Host: 167.99.207.3:30092
> User-Agent: curl/7.88.1
> Accept: */*
>
< HTTP/1.1 200 OK
< Date: Fri, 07 Jul 2023 14:42:55 GMT
< Server: Apache/2.4.41 (Ubuntu)
< Set-Cookie: cookie=XSSisFun; expires=Sun, 06-Aug-2023 14:42:55 GMT; Max-Age=2592000; path=/
< Vary: Accept-Encoding
< Content-Length: 414
< Content-Type: text/html; charset=UTF-8
<
<!DOCTYPE html>
<html>


<body>
<button onclick="inputFunction()">Click to enter your name</button>
<p id="output"></p>

<script>
function inputFunction() {
var input = prompt("Please enter your name", "");

if (input != null) {
document.getElementById("output").innerHTML = "Your name is " + input;
}
}
</script>
</body>

* Connection #0 to host 167.99.207.3 left intact
</html>
```


## Challenge 6: Web Server Operating System


The next challenge asks for the operating system associated with the acronym “WAMP.” The correct answer is Windows.

## Challenge 7: HTTP Code 201


In this challenge, we need to determine the meaning of an HTTP code 201. The correct answer is “Created.”

## Challenge 8: Google Firebase Database


The challenge requires identifying the type of database used by Google’s Firebase Database. The correct answer is NoSQL.

## Challenge 9: User Search with GET Request


In this challenge, we are asked to perform a GET request to `**/index.php?id=0**` to search for the name of the user with ID number 1. By executing the provided cURL command, we obtain the answer: `**superadmin**`.


```
curl -X GET "http://161.35.37.13:30839/index.php?id=1"

superadmin
```


## Challenge 10: Public Vulnerability Category


The challenge involves categorizing the public vulnerability with the identifier `**CVE-2014-6271**`. This vulnerability belongs to the category of "Command Injection."

## Challenge 11: CVSS Score of Public Vulnerability


The final challenge requires determining the Common Vulnerability Scoring System (CVSS) score for the public vulnerability with the identifier `**CVE-2017-0144**`. The correct score is `**9.3**`.

## Conclusion


In this article, we provided detailed solutions to the challenges presented in the “Introduction to Web Applications” HTB CTF. By understanding HTML, CSS, web vulnerabilities, and other related concepts, you can successfully solve these challenges. CTFs are an excellent way to enhance your web application security knowledge and improve your skills. Keep practicing and exploring different CTF challenges to further develop your expertise.

---

*Originally published on [Medium](https://infosecwriteups.com/introduction-to-web-applications-htb-ctf-826f9d9cc978). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
