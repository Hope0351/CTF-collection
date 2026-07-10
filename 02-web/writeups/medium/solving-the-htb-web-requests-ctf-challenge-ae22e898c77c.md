# :globe_with_meridians: Solving the HTB Web Requests CTF Challenge

> **Original Source:** [Solving the HTB Web Requests CTF Challenge](https://infosecwriteups.com/solving-the-htb-web-requests-ctf-challenge-ae22e898c77c)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Solving the HTB Web Requests CTF Challenge


*Created by Lexia.art*


The stages to completing the HTB Web Requests Capture The Flag (CTF) challenge will be discussed in this article. To make sure you comprehend the answer, we’ll dissect every facet of the problem in great depth.

## Challenge Overview


The HTB Web Requests CTF challenge consists of several tasks that involve interacting with a web server using cURL and browser devtools. Let’s dive into each task and explore how to solve them.

## Task 1: Downloading a File


The first task requires us to download a file returned by the `/download.php` endpoint on the server. We can achieve this using the cURL command:


```
curl 165.22.127.181:30029/download.php
```


The command will retrieve the file, and the flag can be found within the downloaded content: `HTB{64$!c_cURL_u$3r}`.

## Task 2: Identifying the HTTP Method


The second task involves intercepting a request and determining the HTTP method used. By executing the following cURL command, we can inspect the request and its response headers:


```
curl 165.22.127.181:30029 -v
* Trying 165.22.127.181:30029...
* Connected to 165.22.127.181 (165.22.127.181) port 30029 (#0)
> GET / HTTP/1.1
> Host: 165.22.127.181:30029
> User-Agent: curl/7.88.1
> Accept: */*
>
< HTTP/1.1 200 OK
< Date: Fri, 07 Jul 2023 11:46:11 GMT
< Server: Apache/2.4.41 (Ubuntu)
< Vary: Accept-Encoding
< Content-Length: 348
< Content-Type: text/html; charset=UTF-8
<
<!DOCTYPE html>
<html lang="en">

<head>
<meta charset="UTF-8">
<meta http-equiv="X-UA-Compatible" content="IE=edge">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Blank Page</title>
</head>

<body>
This page is intentionally left blank.
<br>
Using cURL should be enough.
</body>

* Connection #0 to host 165.22.127.181 left intact
</html>
```


From the response headers, we can observe that the HTTP method used for the request is `GET`.

## Task 3: Extracting Server Information


In order to complete the third assignment, we must determine the server’s Apache version by looking at the response headers. By making a GET call to the server and looking at the return headers, we can do this. The cURL command below retrieves the headers:


```
curl 144.126.206.249:31621 -I
HTTP/1.1 200 OK
Date: Fri, 07 Jul 2023 11:55:06 GMT
Server: Apache/2.4.41 (Ubuntu)
Last-Modified: Mon, 16 Jan 2023 14:12:19 GMT
ETag: "c83-5f2622bcb16c0"
Accept-Ranges: bytes
Content-Length: 3203
Vary: Accept-Encoding
Content-Type: text/html
```


Among the response headers, we find the server information: `Server: Apache/2.4.41 (Ubuntu)`. The Apache version is `2.4.41`.

## Task 4: Analyzing Network Requests


The fourth task involves analyzing network requests made by a web page to find the request that retrieves the flag. By inspecting the network tab in the browser’s developer tools, we can identify the request we are interested in. The cURL command below retrieves the relevant information:


```


## Get Ahmet Talha Şen’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in
curl 144.126.206.249:31621 -v
* Trying 144.126.206.249:31621...
* Connected to 144.126.206.249 (144.126.206.249) port 31621 (#0)
> GET / HTTP/1.1
> Host: 144.126.206.249:31621
> User-Agent: curl/7.88.1
> Accept: */*
>
< HTTP/1.1 200 OK
< Date: Fri, 07 Jul 2023 11:51:46 GMT
< Server: Apache/2.4.41 (Ubuntu)
< Last-Modified: Mon, 16 Jan 2023 14:12:19 GMT
< ETag: "c83-5f2622bcb16c0"
< Accept-Ranges: bytes
< Content-Length: 3203
< Vary: Accept-Encoding
< Content-Type: text/html
<
<!DOCTYPE html>
<html lang="en" class="theme_switchable">

<head>
<meta charset="UTF-8">
<title>Recommended Modules</title>
<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/normalize/8.0.0/normalize.min.css'>
<link rel='stylesheet' href='https://static.fontawesome.com/css/fontawesome-app.css'>
<link rel='stylesheet' href='https://pro.fontawesome.com/releases/v5.2.0/css/all.css'>
<link rel='stylesheet' href='https://fonts.googleapis.com/css?family=Roboto:400,700'>
<link rel="stylesheet" href="./style.css">

</head>

<body>
<!-- partial:index.partial.html -->
<div style="padding: 10% 10%;">
<div>
<h1>Recommended Modules</h1>
</div>
<div class="options">
<div class="option active" style="--optionBackground:url(./img/0.png);">
<div class="shadow"></div>
<div class="label">
<div class="icon">
<i class="fas fa-network-wired"></i>
</div>
<div class="info">
<div class="main">Current Module</div>
<div class="sub">Web Requests</div>
</div>
</div>
</div>
<div class="option" style="--optionBackground:url(./img/1.png);">
<div class="shadow"></div>
<div class="label">
<div class="icon">
<i class="far fa-window-restore"></i>
</div>
<div class="info">
<div class="main">Next Module</div>
<div class="sub">Introduction to Web Applications</div>
</div>
</div>
</div>
<div class="option" style="--optionBackground:url(./img/2.png);">
<div class="shadow"></div>
<div class="label">
<div class="icon">
<i class="fab fa-connectdevelop"></i>
</div>
<div class="info">
<div class="main">Module 3</div>
<div class="sub">Using Web Proxies</div>
</div>
</div>
</div>
<div class="option" style="--optionBackground:url(./img/3.png);">
<div class="shadow"></div>
<div class="label">
<div class="icon">
<i class="fas fa-ethernet"></i>
</div>
<div class="info">
<div class="main">Module 4</div>
<div class="sub">Information Gathering - Web Edition</div>
</div>
</div>
</div>
<div class="option" style="--optionBackground:url(./img/4.png);">
<div class="shadow"></div>
<div class="label">
<div class="icon">
<i class="fab fa-js"></i>
</div>
<div class="info">
<div class="main">Module 5</div>
<div class="sub">JavaScript Deobfuscation</div>
</div>
</div>
</div>
</div>
</div>

<!-- partial -->
<script src='./jquery.min.js'></script>
<script src="./script.js"></script>

</body>

* Connection #0 to host 144.126.206.249 left intact
</html>
```


Among the response headers, we find the URL of the flag request: `http://144.126.206.249:31621/flag_327a6c4304ad5938eaf0efb6cc3e53dc.txt`. The flag can be found within the file: `HTB{p493_r3qu3$t$_m0n!t0r}`.

## Task 5: Troubleshooting Broken Functionality


The fifth task involves troubleshooting broken functionality to obtain the flag. By observing the search request made by the broken feature, we can mimic the request using cURL to search for the flag. The following cURL command performs the search:


```
curl 'http://134.209.179.69:30190/search.php?search=flag' -H 'Authorization: Basic YWRtaW46YWRtaW4=' -v
* Trying 134.209.179.69:30190...
* Connected to 134.209.179.69 (134.209.179.69) port 30190 (#0)
> GET /search.php?search=flag HTTP/1.1
> Host: 134.209.179.69:30190
> User-Agent: curl/7.88.1
> Accept: */*
> Authorization: Basic YWRtaW46YWRtaW4=
>
< HTTP/1.1 200 OK
< Date: Fri, 07 Jul 2023 12:36:28 GMT
< Server: Apache/2.4.41 (Ubuntu)
< Cache-Control: no-cache, must-revalidate, max-age=0
< Content-Length: 23
< Content-Type: text/html; charset=UTF-8
<
flag: HTB{curl_g3773r}
* Connection #0 to host 134.209.179.69 left intactThe response contains the flag: flag: HTB{curl_g3773r}.
```


## Task 6: Leveraging Session Cookies


The sixth task requires obtaining a session cookie through a valid login and then using that cookie to search for the flag through a JSON POST request to `/search.php`. First, we need to retrieve the session cookie by visiting the login page. The following cURL command retrieves the cookie:


```
curl http://138.68.155.223:32576/ -v
* Trying 138.68.155.223:32576...
* Connected to 138.68.155.223 (138.68.155.223) port 32576 (#0)
> GET / HTTP/1.1
> Host: 138.68.155.223:32576
> User-Agent: curl/7.88.1
> Accept: */*
>
< HTTP/1.1 200 OK
< Date: Fri, 07 Jul 2023 12:43:35 GMT
< Server: Apache/2.4.41 (Ubuntu)
< Set-Cookie: PHPSESSID=g2rfiv1ru3um1idqd4jb59g8si; path=/
< Expires: Thu, 19 Nov 1981 08:52:00 GMT
< Cache-Control: no-store, no-cache, must-revalidate
< Pragma: no-cache
< Vary: Accept-Encoding
< Content-Length: 1167
< Content-Type: text/html; charset=UTF-8
<

<!DOCTYPE html>
<html lang="en">

<head>
<meta charset="UTF-8">
<title>City Search</title>
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/meyer-reset/2.0/reset.min.css">
<link rel='stylesheet' href='https://fonts.googleapis.com/css?family=Roboto:400,500,700'>
<link rel='stylesheet' href='https://static.fontawesome.com/css/fontawesome-app.css'>
<link rel='stylesheet' href='https://pro.fontawesome.com/releases/v5.2.0/css/all.css'>
<link rel="stylesheet" href="./style.css">
<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/normalize/5.0.0/normalize.min.css">
<script src="https://cdnjs.cloudflare.com/ajax/libs/prefixfree/1.0.7/prefixfree.min.js"></script>
</head>

<body>
<div class="login">
<h1>Login</h1>
<form method="post">
<input type="text" name="username" placeholder="Username" required="required" />
<input type="password" name="password" placeholder="Password" required="required" />
<button type="submit" class="btn btn-primary btn-block btn-large">Login</button>
</form>
</div>

</body>

* Connection #0 to host 138.68.155.223 left intact
</html>
```


Once we have the cookie, we can use it in the subsequent request to search for the flag. The following cURL command performs the search using the session cookie:


```
curl -X POST -d '{"search":"flag"}' -b 'PHPSESSID=euvqgluu4mtasdeiachd0dufui' -H 'Content-Type: application/json' <http://138.68.155.223:32576/search.php>
```


The response returns the flag: `["flag: HTB{p0$t_r3p34t3r}"]`.

## Task 7: Manipulating Data through API Requests


The final task involves manipulating data through API requests to retrieve the flag. We need to update a city’s name to “flag,” delete another city, and then search for the city named “flag” to obtain the flag. The following cURL commands perform the required operations:


```
curl -X PUT <http://165.22.127.181:31910/api.php/city/Boston> -d '{"city_name":"flag"}' -H 'Content-Type: application/json'
curl -X DELETE '<http://165.22.127.181:31910/api.php/city/london>'
curl -X GET <http://165.22.127.181:31910/api.php/city/flag>
```


The response of the last request provides the flag: `HTB{crud_4p!_m4n!pul4t0r}`.

## Conclusion


In this article, we explored the HTB Web Requests CTF challenge and provided a comprehensive solution for each task. You should to be able to complete this challenge successfully by according to the guidelines mentioned above. Keep practicing and having fun as CTFs are an excellent method to improve your online security and penetration testing abilities.

---

*Originally published on [Medium](https://infosecwriteups.com/solving-the-htb-web-requests-ctf-challenge-ae22e898c77c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
