# :globe_with_meridians: [Research] Authenticated RCE found in HorizontCMS — Part 1 (Malicious Plugins)

> **Original Source:** [[Research] Authenticated RCE found in HorizontCMS — Part 1 (Malicious Plugins)](https://infosecwriteups.com/bughunt-authenticated-rce-found-in-horizontcms-part-1-malicious-plugins-72846f4ab6fe)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# [Research] Authenticated RCE found in HorizontCMS — Part 1 (Malicious Plugins)


## Intro


A couple of weeks ago, I teamed up with my buddy, [Chi Tran](https://ctrsec.io/), to do some bug hunting on an open-source CMS application, [HorizontCMS](https://github.com/ttimot24/HorizontCMS). This application was created by [@ttimot24](https://github.com/ttimot24). Thank you [@ttimot24](https://github.com/ttimot24) for a quick response to our bug reports and allowing us to writing a blog post about them!


Firstly, we installed the HorizontCMS on our testing environment and made it listen on the localhost (127.0.0.1). Then, we configured the Firefox to allow the localhost proxying. (If you didn’t know it already, do the following configuration on your Firefox so that it can proxy the localhost web applications.)

## Initial Digging


Next, we knew that one of the recently found CVEs for the HorizontCMS was about an arbitrary PHP file upload vulnerability: [CVE-2020–27387](https://packetstormsecurity.com/files/160046/HorizontCMS-1.0.0-beta-Shell-Upload.html). So, our initial approach was to see if we could bypass any filetype restrictions that the author had already fixed. This time, the issue was properly mitigated by restricting file extensions like `.php`, `.php5`, `.php7`, `.phtml`, `.inc`, etc.

### Bypassing the Patch…?


However, we found a filetype bypass by using “`/`” (e.g., `test.php/`) to upload a PHP file.


- Upload the `test.php` file to the “File manager”

---

*Originally published on [Medium](https://infosecwriteups.com/bughunt-authenticated-rce-found-in-horizontcms-part-1-malicious-plugins-72846f4ab6fe). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
