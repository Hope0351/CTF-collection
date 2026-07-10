# :mag: Sunshine CTF 2025 Writeups - Web, Misc and Forensics Challenges

---

# Sunshine CTF 2025 Writeups — Web, Misc and Forensics Challenges

Over the weekend, I dived into Sunshine CTF 2025 and worked through multiple challenges. Here’s a step-by-step walkthrough how I approached and solved some of them.

## Lunar Auth (Web)

I visited `https://comet.sunshinectf.games` and saw the landing page saying “no robots are allowed” and the Robot Protocol note warning that “automated agents are forbidden”. This immediately makes me think there might be endpoints that the site is trying to hide it from bots.

So I checked `/robots.txt`. robots.txt is a standard file that websites use to tell search engines and other crawlers which paths they shouldn’t index or visit. The file contained `Disallow: /admin`, so I navigated to `/admin` in the browser.

Viewing the page source revealed the whole problem in plain sight: two Base64 strings decoded with `atob(...)` and assigned to `real_username` and `real_passwd` in client JavaScript.

The login handler compares your input against those decoded values and if they match, it removes the JS check and lets the form submit. In short: the server trusts the client to say “I’m allowed” instead of performing the check server-side.

```
echo -n "YWxpbXVoYW1tYWRzZWN1cmVk" | base64 -d
echo -n "UzNjdXI0X1BAJCR3MFJEIQ==" | base64 -d
```

I decoded the Base64 strings locally and I got the decoded creds: `alimuhammadsecured` / `S3cur4_P@$$w0RD!`. After pasting them into the fields and submitting let the client JS pass the check and the form submit, and the admin page returned the flag:

Flag: `sun{cl1ent_s1d3_auth_1s_N3V3R_a_g00d_1d3A_983765367890393232}`

## Lunar Shop (Web)

I visited the landing page and clicked View Products. The catalog links point to `/product?product_id=<id>`.

When I clicked Product One, it renders a simple HTML table with four columns: *ID*, *Name*, *Description*, and *Price*.

I tried the classic single-quote test to see if the app echoes SQL errors. The application returned an error on the page. The phrasing and error style suggested it used SQLite(`unrecognized token`). It is a useful hint for later queries against `sqlite_master`.

The product table has 4 columns, so I attempted a `UNION SELECT` payload to make sure the injection point accepts stacked results and to locate which columns reflect on the page.

With `UNION SELECT` working, I inspected `sqlite_master` to find interesting tables with this payload `/product?product_id=0 UNION SELECT 1,2,tbl_name,4 FROM sqlite_master WHERE type='table'`. The query returned a row containing `flag` table.

To confirm schema and column names, I pulled the `sql` column for the `flag` table with this payload `/product?product_id=0 UNION SELECT 1,2,sql,4 FROM sqlite_master WHERE type!='meta' AND sql NOT NULL AND name='flag'`.

Now I knew the `flag` table contains a `flag` TEXT column. With the column name in hand, I retrieved the flag.

Flag: `sun{baby_SQL_injection_this_is_known_as_error_based_SQL_injection_8767289082762892}`

## Lunar File Invasion (Web)

I visited `https://asteroid.sunshinectf.games` and the index shows a simple “Health Check” page with an image and a status (`Status: UP`). Nothing interesting on the surface.

I immediately checked `robots.txt` and found sensitive files.

Requesting `/.gitignore_test` returned a plain text file which clearly looked like a dev `.gitignore` helper file. It told static files are stored in `/index/static/` such as `login.html~`. That told me to check `/index/static/login.html~`.

`/index/static/login.html~` returned a HTML page and dev left the admin email and password in it. I tried those creds at `/login`.

Logging in with the found creds redirected me to `/2FA`, which requests a 10-digit pin.

I couldn’t complete the 2FA, so instead I looked back at `robots.txt` which had `/admin/dashboard` disallowed. When I tried `/admin/dashboard`,it was bypassed and got redirected to `/admin/help`.

From `/admin/help` I clicked Manage Files and reached the file manager UI.

`Manage Files` shows three files: `secret1.txt`, `secret2.txt`, `secret3.txt`. The page uses client-side JS to display files by calling:

```
const viewUrl = `/admin/download/${filename}`;
fetch(viewUrl)
.then(response => response.text())
```

That tells us the server serves files with `/admin/download/<filename>`.

I viewed `secret1.txt` and `secret2.txt`. They contain dev notes that a real attacker once got `/etc/passwd` and references to HackTricks.

The HTTP history shows the request to `/admin/download/secret2.txt`. Then I tried a basic traversal payload to read `/etc/passwd`.

Server returned `400 Bad Request` for that route (probably server-side blacklist + request validation).

When requesting a non-existent file like `/admin/download/notexist` the app redirects back to `/admin/lunar_files?err_msg=[ Resource Does not Exist! ]`. That gave me a baseline response size `305` for “Resource Does not Exist!” behavior so I could filter fuzzing results. Since the challenge explicitly says “Fuzzing NOT allowed” (IP rate-limited) and this was an authenticated endpoint, I used `ffuf` in single-threaded mode with a delay and included my valid `session` cookie header.

```
ffuf -w /usr/share/seclists/Fuzzing/LFI/LFI-Jhaddix.txt \
-u '<https://asteroid.sunshinectf.games/admin/download/FUZZ>' \
-H 'Cookie: session=<my-session-cookie>' \
-t 1 -fs 305 -p 2.0
```

ffuf returned hits for double-encoded traversal payloads.

When I manually requested the double-URL-encoded path the server returned `err_msg=[ Succession of '../../' detected, forbidden ]`. So there was a blacklist detection for `../` patterns.

I experimented with a slightly different payload where I replaced `../` sequences with `..//` and then URL-encoded those slashes twice (double URL encoding). When I requested this form, the response returned the actual contents of `/etc/passwd`.

Then I tried a few filesystem targets that can leak app source. Because the app was Flask (according to default 404 page), I tried `/proc/self/cwd/app.py`. That returned the Flask app source. In `app.py` I found the flag path is `./FLAG/flag.txt` relative to the app working directory. I requested that file via the same `/admin/download/<payload>` mechanism and retrieved the flag.

Flag: `sun{lfi_blacklists_ar3_sOo0o_2O16_8373uhdjehdugyedy89eudioje}`

## Web Forge (Web)

Visiting the root of the site shows a small webapp called Space Forge with a link to an SSRF tool at `/fetch`.

Accessing `/fetch` directly returned a 403 with the message: `403 Forbidden: missing or incorrect SSRF access header`. Then I checked `robots.txt` and it leaks useful hints.

That comment suggested the `/fetch` endpoint expects a specific header with a `true` value. I created a header wordlist using ChatGPT and used `ffuf` to fuzz possible header names.

```
ffuf -w headers.txt -u '<https://wormhole.sunshinectf.games/fetch>' -H 'FUZZ: true' -fc 403
```

`ffuf` returned two hits for `Allow` (uppercase) and `allow` (lowercase). That means the application accepted `Allow: true` (or `allow: true`) as the required SSRF auth header.

With the header set, `/fetch` returned the SSRF testing UI (a simple form that accepts a URL and performs a server-side request).

Given the SSRF tool, a natural idea is to request internal-only endpoints like `/admin`. I issued a request via the SSRF tool to `http://127.0.0.1/admin` the server’s response was helpful.

So `/admin` expects a `?template=` parameter. I tried `http://127.0.0.1/admin?template=hi`, but it failed with a connection error when it tried local port `80`.

That suggested the internal service might be listening on a different port. I tried other common internal ports (e.g. 8080, 5000, 8000).

The SSRF to `http://127.0.0.1:8000/admin?template=hi` returned the provided `hi` string, indicating a web service was running on port 8000 and it reflected the `template` parameter.

I tested for SSTI by submitting `{{7*7}}` as the `template` value and it rendered `49`. SSTI confirmed. The app had some filters, so I used a technique by @SecGus that bypass most common filters ('.','_','|join','[',']','mro' and 'base'). The payload I used is:

```
{{request|attr('application')|attr('\\x5f\\x5fglobals\\x5f\\x5f')|attr('\\x5f\\x5fgetitem\\x5f\\x5f')('\\x5f\\x5fbuiltins\\x5f\\x5f')|attr('\\x5f\\x5fgetitem\\x5f\\x5f')('\\x5f\\x5fimport\\x5f\\x5f')('os')|attr('popen')('id')|attr('read')()}}
```

This returned command output (e.g. output of `id`) proving command execution. I then enumerated the remote filesystem.

This showed `flag.txt` in the working directory.

Attempting a direct `cat flag.txt` via the same `popen` chain returned `Nope` (the app likely filters or blocks direct file read attempts with specific command names like `cat` or file names like `flag.txt`). To bypass this, I used base64 encoded command and execute:

```
echo Y2F0IGZsYWcudHh0 | base64 -d | bash
```

Flag: `sun{h34der_fuzz1ng_4nd_ssti_1s_3asy_bc10bf85cabe7078}`

## Tribble with my Skin (Misc)

The challenge said that a Minecraft account got hacked and now the skin looks “a little off.” The username they gave us was `oatzs`. They also noted that no Minecraft account or instance is required for this challenge, so that’s the hint that everything can be done through Mojang’s APIs and public skin data.

Minecraft accounts are internally identified by a ID, not just the username. Mojang provides an official API to resolve a username into its ID. When I visited this link `https://api.mojang.com/users/profiles/minecraft/oatzs`, I got JSON response containing ID `b81a3caab69b47f18aad440a3eb38aa5`.

Next, to see the current skin data of a user, Mojang has another API `https://sessionserver.mojang.com/session/minecraft/profile/<ID>`. This returned another JSON. Inside it, there’s a `properties` array, and the interesting part is a field called `value`. That `value` is base64 encoded JSON, which contains the actual skin texture information. After decoding the base64 data, I got this url.

Opening the URL `http://textures.minecraft.net/texture/868f45a675a029042087c319d67128a28a5f3eb105375fa1d571a18f2c5efb15` in the browser gave me the hacked skin image. Looking carefully at the skin, you can see the flag written in it.

Flag: `sun{tribble_craft}`

## OK BOOMER (Misc)

Opened the challenge and immediately noticed the weird looking flag format with a bunch of numbers. At first glance it reminded me of the old-school phone keypad texting system.

The challenge gave me this `77778866{8444447777_7446666633_4447777_26622244433668}`. So basically, pressing a number multiple times cycles through the letters. For example, `7` = p, `77` = q, `777` = r, `7777` = s. After putting them together, I got the flag.

Flag: `sun{this_phone_is_ancient}`

## BigMak (Misc)

The two hints “Cole” and “mak” immediately made me think of Colemak keyboard layout, which is a popular alternative to QWERTY. So the idea is: the flag was typed on a Colemak keyboard, but shown as if it was typed on QWERTY.

After applying this inverted mapping, the gibberish text `rlk{blpdfp_iajylg_iyi}` turned into something meaningful `sun{burger_layout_lol}`.

Flag: `sun{burger_layout_lol}`

## Pretty Delicious Food (Forensics)

After downloading `prettydeliciouscakes.pdf` I ran a quick metadata/feature scan with `pdfid` to see if the file contained anything interesting (JavaScript, embedded files, streams, etc.). `pdfid` is great for a fast surface-level look:

Here it flagged `/EmbeddedFile 1` that tells “there is an embedded file inside the PDF” and that’s exactly where flags like to hide in forensics challenges. So I used `pdf-parser` to inspect embedded files and their objects. I searched for the `/EmbeddedFile` type with this command `pdf-parser prettydeliciouscakes.pdf -s '/EmbeddedFile'`.

Object `11 0` is an embedded file. It has a `Filter /FlateDecode` which means the data is compressed with zlib/deflate inside the PDF stream. `Size 49` is the uncompressed size, `Length 57` is the stored length (compressed). The `CheckSum` is just a checksum, not needed for extraction. Then I extracted the stream from object 11 to a file called `embedded.bin`.

I checked what type of file I extracted. So it’s text, not a binary blob. I printed it to see the contents.

That string looks like Base64. So I decoded that string and got the flag.

Flag: `sun{p33p_d1s_fl@g_y0!}`

## t0le t0le (Forensics)

The given file was named `Team_5_-_Inject_72725.docx`. The first thing I did was check its type.

Since DOCX is basically just a zip archive, I unzipped it to see the structure.

Among the usual XMLs, I spotted something suspicious `word/embeddings/oleObject1.bin`. This is interesting because `embeddings/` holds OLE objects (embedded files inside the document). Next, I checked the embedded file.

So, it’s an OLE compound file. I used `oleobj` (part of `oletools`) to parse the OLE package.

And it found an `Ole10Native` stream and extracted it as a file named `Team_5_-_Inject_72725.docx_vro`. I looked at what was inside and found base64 string.

When I decoded it, I got something flag-like, but it is not. The prefix `fha{` stood out because that’s probably just `sun{` with ROT13.

I ran ROT13 over the string and got the actual flag.

Flag: `sun{t0le_t0le_my_b3l0v3d!}`

---
