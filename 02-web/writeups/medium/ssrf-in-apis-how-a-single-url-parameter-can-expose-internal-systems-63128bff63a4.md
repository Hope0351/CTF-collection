# :globe_with_meridians: SSRF in APIs: How a Single URL Parameter Can Expose Internal Systems

> **Original Source:** [SSRF in APIs: How a Single URL Parameter Can Expose Internal Systems](https://infosecwriteups.com/ssrf-in-apis-how-a-single-url-parameter-can-expose-internal-systems-63128bff63a4)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# SSRF in APIs: How a Single URL Parameter Can Expose Internal Systems


*A single misconfigured URL parameter can allow an attacker to abuse server-side requests and potentially access internal services, cloud metadata endpoints, or hidden resources that were never meant to be exposed.*


### What is SSRF? The Silent Attack Hiding in Plain Sight


SSRF stands for Server-Side Request Forgery.


Imagine asking a waiter to bring food from the kitchen, but instead you trick the waiter into entering the manager’s office and retrieving confidential documents. The waiter is trusted, so security does not stop him. SSRF works in a similar way.


In web applications, servers frequently make requests on behalf of users, such as:


- Fetching URLs

- Generating previews

- Calling external APIs

- Retrieving remote resources


SSRF occurs when an attacker manipulates these requests and causes the server to communicate with destinations it was never intended to access.


Instead of fetching a harmless webpage, the server may begin interacting with:


- Internal services

- Cloud metadata endpoints

- Private APIs

- Administrative interfaces


The dangerous part is that the request originates from the server itself, which is generally considered a trusted source. Firewalls and network controls may treat this traffic as legitimate.


No credentials may be required. In some cases, all it takes is a URL parameter that lacks proper validation.

### What Does an SSRF Attack Actually Look Like?


To demonstrate this vulnerability, I used crAPI, a deliberately vulnerable API application designed for security practice. It provides a safe and legal environment for learning and testing web application security concepts.


I navigated to the Contact Mechanic section, submitted the form, and intercepted the request using Burp Suite.


The application sends requests to an endpoint responsible for processing service reports. The key parameter here is mechanic_api, which uses user-supplied input to make an outbound request on behalf of the user. Since this parameter controls the request destination, it becomes a potential SSRF injection point.


### Step 1: Confirming the SSRF


To determine whether arbitrary URLs were accepted, I replaced the mechanic_api value with an external URL.


The server returned a successful response containing external page content.


This confirms several important observations:


- The application performs outbound HTTP requests using user-controlled input

- URL validation or allowlisting is absent

- The server can access external destinations and potentially internal resources


This confirms SSRF behavior.


The server is processing user-controlled requests without proper validation, allowing attackers to abuse it to access unintended destinations.


## Step 2: Accessing Internal Admin Functionality


Since requests originate from the server itself, internal resources that are inaccessible externally may sometimes become reachable through SSRF. I attempted to access internal administrative paths. The response returned: HTTP 404:Not Found This suggests the resource does not exist at that specific location. I then tested access to the application’s own endpoint through localhost.


I then tested access to the application’s own endpoint through localhost.


This time the response returned:


HTTP 405 :Method Not Allowed


## Get Sana Jalil’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


This is interesting because it suggests the endpoint exists and is reachable, but the request method used was incorrect.


This indicates that additional testing with different HTTP methods may reveal more functionality.


## Potential Post-Exploitation Scenarios


Once SSRF is confirmed, attackers may attempt additional actions depending on the target environment:


- Internal service discovery through port scanning

- Accessing internal-only APIs

- Retrieving cloud metadata information

- Testing filter bypass techniques

- Identifying blind SSRF behavior using out-of-band interactions


The success of these activities depends heavily on application design and network architecture.

---

*Originally published on [Medium](https://infosecwriteups.com/ssrf-in-apis-how-a-single-url-parameter-can-expose-internal-systems-63128bff63a4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
