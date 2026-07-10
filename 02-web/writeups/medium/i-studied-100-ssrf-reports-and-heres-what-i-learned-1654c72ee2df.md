# :globe_with_meridians: I Studied 100+ SSRF Reports, and Here’s What I Learned

> **Original Source:** [I Studied 100+ SSRF Reports, and Here’s What I Learned](https://infosecwriteups.com/i-studied-100-ssrf-reports-and-heres-what-i-learned-1654c72ee2df)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# I Studied 100+ SSRF Reports, and Here’s What I Learned


After diving into over 100 write-ups and reports on Server-Side Request Forgery (SSRF), I’ve compiled the key insights and knowledge I’ve gained into this blog. Here, I aim to share a comprehensive overview of SSRF vulnerability

## Server-Side Request Forgery (SSRF)


Server-Side Request Forgery (SSRF) is a vulnerability that allows an attacker to send crafted requests from a vulnerable server to other internal or external resources. SSRF occurs when a web application accepts a URL or IP address input from a user and uses that input to make requests without properly validating or sanitizing it.

## Identifying SSRF Vulnerabilities


Identifying SSRF in a target application is about understanding how that application interacts with external resources, processes URLs, and handles user input. The first thing you want to do is take a step back and review all the functions in the target application that fetch external resources. This could be anything from loading images to fetching data from other servers. These spots are the most likely entry points for SSRF vulnerabilities.


URL Import Features: A common one. Think about functions where the application fetches something based on a URL — maybe an image importer or data fetcher. If the app is grabbing content from an external URL, you can bet it might be susceptible to SSRF, especially if there’s no proper validation. The idea here is to try feeding internal URLs like `http://localhost` or `http://127.0.0.1`


File Upload Mechanisms: Oh yes, file uploads. These can be sneaky. Imagine an application that lets users upload files — things like PDFs, SVGs, or even Office documents. If the backend processes these files, SSRF might be hiding here. You can try uploading files with embedded URLs pointing to internal services (Reference: [The PDF Trojan Horse: Leveraging HTML Injection for SSRF and Internal Resource Access](https://uchihamrx.medium.com/the-pdf-trojan-horse-leveraging-html-injection-for-ssrf-and-internal-resource-access-fbf69efcb33d)).


Headless Browsers / HTML Rendering: These are usually found in features that generate PDFs or images on the backend. When you find a target using a headless browser, try injecting URLs into areas that process HTML content. If you manage to make the backend fetch something unintended, you might have hit an SSRF goldmine! (Reference: [SSRF on a Headless Browser Becomes Critical](https://medium.com/@Nightbloodz/ssrf-on-a-headless-browser-becomes-critical-c08daaa1017e)).


Server Status and Monitoring Features: Now, look for those features that allow you to check server status or application health. These functionalities often query internal services for status information — perfect spots for SSRF. If you find one, try manipulating the requests to hit internal endpoints or sensitive services (Reference: [31k SSRF in Google Cloud Monitoring](https://nechudav.blogspot.com/2020/11/31k-ssrf-in-google-cloud-monitoring.html)).


Proxy Implementations: Proxies are interesting because they route requests through the server. If the application lets you send requests through a proxy and doesn’t validate the URLs strictly, you’ve got a shot at SSRF. This is especially true if it doesn’t sanitize user-supplied URLs. Try sending requests to internal services or other unauthorized endpoints and see what happens (Reference: [Server-Side Request Forgery on Havoc C2](https://blog.chebuya.com/posts/server-side-request-forgery-on-havoc-c2/)).


Vulnerabilities in Security Mechanisms: It’s not just the app itself — sometimes, SSRF is hiding in the libraries and security mechanisms that the application uses. Authentication libraries, request-handling components, or other backend tools could have SSRF flaws. You’ll want to audit those, too, because these third-party systems often expose vulnerabilities you wouldn’t expect (Reference: [Digging for SSRF in Next.js Apps](https://www.assetnote.io/resources/research/digging-for-ssrf-in-nextjs-apps)).


File Storage Integrations: If your target integrates with third-party services like Google Drive, Amazon S3, or Dropbox, check if the app makes server-side requests to fetch or store files. These are excellent candidates for SSRF, as you can try manipulating the requests to fetch internal files or data from unauthorized services. By injecting a crafted URL into these integrations, you might access internal systems that were never meant to be exposed (Reference: [SSRF: Server-Side Request Forgery Worth $4,913](https://medium.com/techfenix/ssrf-server-side-request-forgery-worth-4913-my-highest-bounty-ever-7d733bb368cb)).


Path Parameters and Host Headers: Pay close attention to how path parameters and host headers are handled. If an application uses path parameters to construct server-side requests, that’s another spot to test for SSRF. Try manipulating the parameters to redirect requests to internal resources. Similarly, the host header might be leveraged to control where requests are sent. Test for any weaknesses here — you might be able to influence the destination of requests using the host header (Reference: [Host Header Injection to Complete Organization Takeover](https://medium.com/@_yldrm/host-header-injection-to-complete-organization-takeover-67a8a2ddb188)).

## Blind SSRF


Blind SSRF is a vulnerability where you can send requests to internal hosts but only receive a status code in response, rather than the full HTTP response.


The most reliable way to detect Blind SSRF vulnerabilities is by using out-of-band (OAST) techniques. This involves triggering an HTTP request to an external system that you control and monitoring any network interactions with that system.


One of the most common mistakes bug bounty hunters make is reporting DNS pingbacks alone. Simply receiving DNS pingbacks via Burp Collaborator isn’t enough to confirm an SSRF vulnerability. In fact, DNS pingbacks are often considered out of scope for bounties on most bug bounty platforms.

## SSRF Using DNS Rebinding


When SSRF (Server-Side Request Forgery) and DNS Rebinding are used in tandem, they can create a formidable attack vector. Although this combination is not commonly exploited, it can lead to significant risks by effectively bypassing the Same-Origin Policy. This is primarily because, from the browser’s perspective, the targeted server and the loopback address are seen as part of the same domain.


Consider the following scenario: a victim is browsing the internet on their work laptop, which is connected to the organization’s network. Within this network lies an internal web application located at [http://192.168.1.3/](http://192.168.1.3/), accessible only within the organization.


To exfiltrate data from this internal web application, an attacker could utilize DNS rebinding as follows:


- Domain Acquisition: The attacker obtains the domain name example.com and configures a DNS server with a low Time-To-Live (TTL) setting. This DNS server is set to resolve example.com to the IP address of the web application that hosts a malicious JavaScript payload.

- Victim Interaction: The victim accesses the attacker’s web application at [http://example.com](http://example.com). At this point, the browser resolves example.com to the attacker’s server, loading the malicious JavaScript payload.

- DNS Rebinding: The attacker then updates or “rebinds” the DNS settings of example.com to resolve to 192.168.1.3, the internal web application.

- Malicious Request: The JavaScript payload initiates an HTTP GET request to [http://example.com/sensitive-endpoint](http://example.com/sensitive-endpoint). Due to the DNS rebinding, example.com now resolves to 192.168.1.3. Consequently, the victim’s browser sends the request to the internal web application. Since the origin (i.e., scheme, host, and port) remains unchanged, this request is not regarded as cross-origin. Thus, the JavaScript code can access the response without breaching the Same-Origin Policy.

- Data Exfiltration: Finally, the JavaScript payload exfiltrates the response data to another domain controlled by the attacker, for instance, [http://harmfull.example.com](http://harmfull.example.com).


Reference:

## SSRF Filter Bypasses


When bypassing SSRF (Server-Side Request Forgery) filters, it’s essential to understand the various techniques available for evading protections. Here are several effective methods that you can use to get around SSRF defenses:


## Get Aditya Sawant’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Open Redirects: These can redirect requests to otherwise blocked endpoints. An open redirect vulnerability within the target application can be leveraged to bypass SSRF filters by redirecting requests to internal services.


IP Address Tricks: Some SSRF protections block specific hosts (e.g., localhost or 127.0.0.1), but there are ways to disguise these IPs:


- *Localhost Range:* `127.0.0.0` to `127.255.255.255`

- *Shortened Form:* `127.1`

- *Padded Form:* `127.000000000000000.1`

- *All Zeroes:* `0.0.0.0` (which often resolves to the local machine)

- *Shortened Zeroes:* Simply `0`

- *Decimal Form:* `2130706433`

- *Octal Form:* `0177.0000.0000.0001`

- *Hexadecimal Form:* `0x7f000001`

- *IPv6 Loopback:* `0:0:0:0:0:0:0:1` or `::1`

- *IPv4-mapped IPv6 Loopback:* `::ffff:127.0.0.1`


Protocol-Based Bypass: Some SSRF filters focus on blocking HTTP(S) URLs, but many web applications support other protocols like FTP or SMTP. By switching protocols, you may reach restricted resources not monitored by the filter.


IP Obfuscation Techniques: Encoding or manipulating IP addresses in unusual ways can help bypass filters. This includes hexadecimal, octal, or decimal representations of IP addresses, which may not be recognized by simplistic filtering rules.


URL Encoding and Parsing Tricks: Many SSRF filters struggle with unusual or encoded URL formats. Experimenting with URL encoding, double encoding, or adding null bytes can help in cases where the filter doesn’t normalize or validate URLs thoroughly.


Using Different Parsers: By testing how different parsers in the target application interpret URLs, you may identify inconsistencies that allow access to blocked endpoints.


For an extensive reference on SSRF payloads, check the [PayloadsAllTheThings GitHub repository](https://github.com/swisskyrepo/PayloadsAllTheThings/blob/master/Server%20Side%20Request%20Forgery/README.md).

## Useful Tools for SSRF


I hope this blog provides valuable insights and a deeper understanding to help you better understand and address SSRF vulnerabilities. Happy hunting!

>

Your support helps me continue publishing in-depth, implementation-focused guides.


[https://buymeacoffee.com/aditya_sawant](https://buymeacoffee.com/aditya_sawant)

---

*Originally published on [Medium](https://infosecwriteups.com/i-studied-100-ssrf-reports-and-heres-what-i-learned-1654c72ee2df). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
