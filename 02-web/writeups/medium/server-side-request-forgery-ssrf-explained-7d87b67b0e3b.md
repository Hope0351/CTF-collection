# :globe_with_meridians: Server-Side Request Forgery (SSRF) Explained

---

## What is SSRF?

In a Server-Side Request Forgery attack, a malicious actor will exploit a web application by sending a request containing a forged URL. This URL will generally be pointing to a resource located in a restricted back-end location. This will induce the web application to communicate with this unintended destination and send back the result to the user.

The destination can either be on the backend network where the target web application server is located, or it can be on the same server itself. Another type is when the destination is on an external server, generally controlled by the attacker.

### Targeting the Internal Infrastructure

In this type of SSRF, an attacker will try to send a request to a back-end service that is not reachable from the Internet.

Generally, this server is in a secure area behind a Firewall, and an exception may be granted to the web application to allow it to communicate with the server.

The attacker will take advantage of the trust relationship that the back-end service places in the vulnerable application. They will induce the application to send a request to the back-end system, allowing them to gain unauthorized access to data.

*SSRF Process*

Let’s see an example of how an attacker can exploit a vulnerable web application.

Insecure Application Example

For the sake of demonstrating how the attack works, we’ll consider a very basic example of an insecure PHP code.

```
<?php
if (isset($_GET['url']))
{
// The url is provided in a GET parameter
$url = $_GET['url'];
// The destination url is accessed and the content is opened
$handle = fopen($url,"rb");
// The content of the file is dumped
fpassthru($handle);
}
?>
```

In this example, the application opens a file that is provided in a GET parameter named `url`.

Now when the user sends a request to the application, here is what it would look like:

```
GET /?url=http://destination.com/resource
Host: vulnerablesite.com
```

As you can see, the user can manipulate this parameter and change it to any other URL they want. Since the application does not have any protection mechanism to prevent that, the user can provide a private IP address to induce the application to retrieve a resource on the backend network.

```
GET /?url=http://192.168.1.45/resource
Host: vulnerablesite.com
```

The above IP address exists within the range 192.168.0.0–192.168.255.255, which is reserved for private IP addresses.

## Get A. Boukar’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Upon reaching this line of code : `$handle = fopen($url,"rb");`, the web application will send a request to the host who has this IP `192.168.1.45` on the local network.

Of course, in this case, the chances that a backend service will have this IP address are very low.

However, the attacker can build a script that will perform host discovery. The script will scan all possible ranges for private IPs and detect which backend services respond.

The attacker can also go one step further and perform port scans on discovered hosts.

### Targeting the Same Server

The other type of SSRF consists of targeting the same server that hosts the web application.

*SSRF targeting the same server*

The attacker can provide the loopback address (127.0.0.1 or localhost) followed by the path to the file to expose.

They can also use absolute paths to files on the server using URLs starting with `file:///` .

Following on the same example given earlier, an HTTP request targeting the same server will look something like this:

```
GET /?url=http://127.0.0.1/resource
Host: vulnerablesite.com
```

or

```
GET /?url=file:///path/to/local/resource
Host: vulnerablesite.com
```

Here again, the attacker can exploit this vulnerability to perform port scans on the machine hosting the web application. This may disclose information about possible services that are running on the target machine.

## Preventing SSRF Attacks

To protect your web application against Server-Side Request Forgery, there is a set of good practices that you can follow. They should help you mitigate the risk of an SSRF targeting your application.

Whitelisting: Do not rely on Blacklisting URLs. Malicious users can always find a way to bypass these filters, either by using different encodings; using alternative domains that point to the same location; or taking advantage of an open redirection vulnerability. Instead, you can use a whitelist to allow only authorized destinations.

Network Segmentation: Not all backend services need to be on the same network. You can try to segment your network into multiple segments separated by Firewalls. This should reduce the impact of SSRF attacks if they ever occur.

Only allow https schemas: Generally, the application will only need to communicate using https schema. Other schemas like `file:///`, `ftp://` which can be used to exploit an SSRF vulnerability can be disabled.

Authentication: Your application should require authentication even for the communication between back-end services that are on the same internal network.

Additionally, and this goes without saying, you should always follow common good practices for a secure web application. These include user input validation, proper error handling, secure API practices, secure HTTP headers, and so on.

---
