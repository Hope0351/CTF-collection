# :globe_with_meridians: Chaining SSRF and LFI to Achieve Root Access on a Major Telecom Server

---

# Chaining SSRF and LFI to Achieve Root Access on a Major Telecom Server

After hitting a wall with standard testing, I returned to recon and discovered a critical SSRF + LFI chain leading to full root access.

So the other day I was working on a target , a large telecommunications company. Everything on the surface seemed fine. I tested every endpoint but found nothing. After spending a week on it, I was completely exhausted and was about to move on. Then something inside me said I was missing something, so I decided to go back to the recon phase.

For recon, I went to censys.io and searched for all servers related to the telecom company using the query below:

```
(target.com) and host.ip: *
```

After scrolling through the results, I found a server with some unusual HTTP ports open, so I started investigating it further.

Port 8003 : SSRF via an Internal Latency Checker

One of the open ports was 8003. When I visited it, I found an internal latency-checking service. A python tool meant to be used by company staff to monitor their network performance by sending ping requests to various sites and measuring response times.

(Note: The bug is now patched so I can’t have screenshots of interface now while writing this write up)

The problem was it was exposed publicly, and there was no whitelisting of which URLs it could ping.

I captured the request in burp suite and changed the target URL to `localhost`. It worked. The service pinged the internal localhost and returned the latency. From here, I could enumerate internal IP addresses and their open ports

But it wasn’t particularly exciting on its own. I also tried command injection, but since this was a python based application using python’s own ping implementation rather than the native bash `ping` command, that option was closed. So, I noted it down in obsidian and moved on.

Port 8090 — XAMPP Default Page and a Hidden LFI

Continuing my enumeration on the same server, I found another open port ,8090, running an XAMPP server. Visiting it revealed the XAMPP default page, which is always a red flag and a signal that something interesting might be waiting underneath.

## Get ReFang’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Without a second thought I started directory brute forcing and found a directory named `php`. There was some SVG related content inside that didn't lead anywhere useful. I tried XSS here, but nothing worked.

So I ran another brute-force scan within the `php` directory, this time using a `.php` extension filter and found a file named `cors.php`.

Visiting it returned an error: *Missing ‘url’ parameter*.

I added the `url` parameter pointing to `localhost`, and the error disappeared. At first, I thought this was the same kind of SSRF I had already found but then I had an idea. Instead of using `http://`, I switched to the `file://` protocol and pointed it at one of XAMPP's default file and voilà it worked.

The full file contents were returned. I had Local File Inclusion (LFI) meaning I could read any file on the server.

My first thought was the classic log poisoning attack: send a request with a PHP reverse shell payload in the body, then trigger it through the LFI by pointing at the log file. However, the log file was too large, and `cors.php` couldn't handle that much content. I tried to locate smaller log files, but none of them worked either, so I abandoned that approach.

Instead, I started mapping out default file paths on the server with a bit of help from gemini. I tried `file:///C:/xampp/passwords.txt` and it returned the XAMPP passwords in plain text. Since the database and phpMyAdmin were only accessible internally, I couldn't use those credentials directly, at least not yet.

Chaining SSRF + LFI to access phpMyAdmin as Root

Now I had two vulnerabilities: SSRF on port 8003 and LFI on port 8090. I decided to chain them. Using the SSRF at port 8090, I attempted to access the internal phpMyAdmin instance. Not only did it work, it showed me that I was already logged in as root.

At that point, I stopped.

In good faith, I chose not to escalate further. What I *could* have done next is write a PHP web shell and uploaded it through phpMyAdmin to gain full server access. But I had enough evidence to make a strong report, so I disclosed everything responsibly to the telecom company.

They fixed the vulnerabilities and appreciated the effort I put into securing their infrastructure.

Key Takeaways:

- Always go back to recon when you feel stuck. The answer is often hiding in plain sight.

- Chaining low-to-medium severity bugs (SSRF + LFI + exposed credentials) can escalate impact dramatically.

---
