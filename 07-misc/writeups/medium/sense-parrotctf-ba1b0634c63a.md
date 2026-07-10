# :game_die: Sense: ParrotCTF. Writeup of a new machine, where we…

---

Hello everyone, hope you are doing well, breaking the systems and figuring out how the system was broken. Any hoops, I have brought you another new write-up on a machine that I recently solved. This machine was shared by the parrotCTF team. So, without wasting much time, let us go.

## Scanning

We have our machine’s IP address, and simply let us do two things quickly. First, set up the nmap and visit the website.

The nmap command I mainly use is;

>

sudo nmap -sC -sV -vvv -A <IP_Address>

```
PORT STATE SERVICE REASON VERSION
80/tcp open http syn-ack ttl 63 nginx
| http-methods:
|_ Supported Methods: GET HEAD POST OPTIONS
|_http-title: Did not follow redirect to https://sense.pt/
443/tcp open ssl/http syn-ack ttl 63 nginx
|_http-title: Error
|_http-favicon: Unknown favicon MD5: 5567E9CE23E5549E0FCD7195F3882816
| tls-nextprotoneg:
| h2
|_ http/1.1
| http-methods:
|_ Supported Methods: GET HEAD POST
| tls-alpn:
| h2
|_ http/1.1
| http-cookie-flags:
| /:
| PHPSESSID:
|_ httponly flag not set
|_ssl-date: TLS randomness does not represent time
| ssl-cert: Subject: commonName=pfSense-6780653c9cdeb/organizationName=pfSense webConfigurator Self-Signed Certificate
| Subject Alternative Name: DNS:pfSense-6780653c9cdeb
| Issuer: commonName=pfSense-6780653c9cdeb/organizationName=pfSense webConfigurator Self-Signed Certificate
| Public Key type: rsa
| Public Key bits: 2048
| Signature Algorithm: sha256WithRSAEncryption
| Not valid before: 2025-01-10T00:09:32
| Not valid after: 2026-02-12T00:09:32
| MD5: c680:346b:e908:350b:8e99:9134:d297:bf65
| SHA-1: f038:0b6b:4209:6b51:6e97:cc5e:cacd:2471:d5a1:bfef
| -----BEGIN CERTIFICATE-----
| MIIElDCCA3ygAwIBAgIIb/Iz9oEOgHEwDQYJKoZIhvcNAQELBQAwWjE4MDYGA1UE
| ChMvcGZTZW5zZSB3ZWJDb25maWd1cmF0b3IgU2VsZi1TaWduZWQgQ2VydGlmaWNh
| dGUxHjAcBgNVBAMTFXBmU2Vuc2UtNjc4MDY1M2M5Y2RlYjAeFw0yNTAxMTAwMDA5
| MzJaFw0yNjAyMTIwMDA5MzJaMFoxODA2BgNVBAoTL3BmU2Vuc2Ugd2ViQ29uZmln
| dXJhdG9yIFNlbGYtU2lnbmVkIENlcnRpZmljYXRlMR4wHAYDVQQDExVwZlNlbnNl
| LTY3ODA2NTNjOWNkZWIwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDJ
| 8d2N6cIHOVuJuoA3ndHnw3qi89W1rXo/a5WDQhzM8ucsc/blP2vYDGRalOx8byjj
| +IhPsPJj1ojL3zx3iD0NrsDdHzwhAypU/e5l47CwKbBnA2Wl+A3e1+FLMsOSXYRu
| HpDwzZn6hsytXUAi4JxHDvMiPHJMRArnvgWM4Iz++sxk9Y66nalrWXgGtiz+9FX+
| uuG1k/A3KOb5ba6rffrFh/Z6qc3WSpfgKhgOesK70V2WYiLkOiBVxR5fAce3ymWC
| udAL1xSn0ntrNvPTrnpt4rXOdBy+goAr+QC6/Bu5559eKidK8HGr2DASCvAqzGJy
| kfV4fYIBocT2hRfs6nz9AgMBAAGjggFcMIIBWDAJBgNVHRMEAjAAMBEGCWCGSAGG
| +EIBAQQEAwIGQDALBgNVHQ8EBAMCBaAwMwYJYIZIAYb4QgENBCYWJE9wZW5TU0wg
| R2VuZXJhdGVkIFNlcnZlciBDZXJ0aWZpY2F0ZTAdBgNVHQ4EFgQUAdrCgsvPYYTp
| ko4u4oLzJIy75WYwgYsGA1UdIwSBgzCBgIAUAdrCgsvPYYTpko4u4oLzJIy75Wah
| XqRcMFoxODA2BgNVBAoTL3BmU2Vuc2Ugd2ViQ29uZmlndXJhdG9yIFNlbGYtU2ln
| bmVkIENlcnRpZmljYXRlMR4wHAYDVQQDExVwZlNlbnNlLTY3ODA2NTNjOWNkZWKC
| CG/yM/aBDoBxMCcGA1UdJQQgMB4GCCsGAQUFBwMBBggrBgEFBQcDAgYIKwYBBQUI
| AgIwIAYDVR0RBBkwF4IVcGZTZW5zZS02NzgwNjUzYzljZGViMA0GCSqGSIb3DQEB
| CwUAA4IBAQBbOkOPu+qhHXmmRs8wIp+ZpzNaJwF1QcSqGnBsCaggRp39mt9lSNG7
| 5qdDniWXTbHi4p1hmRam2uY8lAfw7+ueAEsOSgXUSmfMq/F4zwyITiYyDATIIEld
| hlM6NBTd+GzOTF79CwV8hWP85zFhEi0OCoSFJkc+PL6qgSGTP6VA/zdLaBf4sB42
| 9C3k396smz+jWk4K2w5A95En2aBrF9cGe/N+eTG5RcEe214897J4iV/jwfF8R90w
| un5ZPesvtOca4GPpj/zVCCdJHWIUithnJuArnbM8kr5UuYZPeqYjeJ6TQFP1FgpR
| 1ifAHPg4SVM/sCKi7krKFmKwlDOWdnQb
|_-----END CERTIFICATE-----
```

And by visiting the website, we have;

Pfsense, sounds fishy. After observing the nmap result, it is clear that we need to focus on the website now. Pfsense was looking like a login panel for a framework, decided to search for pfsense.

Upon googling it, I saw that pfSense is an open-source firewall. Well technically,

>

*“PfSense is a firewall/router computer software distribution based on FreeBSD. The open source pfSense Community Edition and pfSense Plus are installed on a physical computer or a virtual machine to make a dedicated firewall/router for a network.”*

So, being a framework, it might have a default login password that we can try. Searching for it on Google, we got.

Great, everything is going easily. The credentials are admin:pfsense. Let us try to log in to the framework.

And we are successful. This is the point where we should note down the insights we have gained till now.

>

Insights till now

We have the framework of pfSense, which is an open-source firewall.
We have its default `ID:pass, and it is working.
The version of the platform is 2.5.2-RELEASE.

## Enemueration

We have the version of the platform, so let us check if it has any previous CVEs present. For searching for 5 mins on the internet, we got that CVE-2024-46538 is present for 2.5.2, and there is a PoC for that.

Now the real fun begins.

Now, when I was solving this machine, I was very happy that a machine would be solved in an hour; however, it wasn’t the case. The room is built such that it would depict the real world, so the creator of the machine set it for manual exploit, thus we have to push our limits and not be a script kiddie.

I tried for at least an hour with the repo, but it wasn’t working as it had been shown in the repo. So, I had to read more about this vulnerability. At this point, I read the entire article and got to know about the XSS present in the interface_group_edit.php

### Vulnerability

The vulnerability is: In this framework, we have an option to edit the group’s name, description, and members. So, if we capture the request before sending the changes to the server and manipulate the member’s parameter, we will be able to execute the script/HTML payload.

To exploit, we need to be here, and our Burp Suite should be started, and our Foxy Proxy should be on. We need to select the group members, WAN and hit save. The packet will be intercepted in the burp.

In this request, we have to modify the member’s parameter. I have used a simple XSS script.

## Get Sidharth Panda’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

<script>alert(“hacked”)</script>

And simply hit forward and check the website. We will see a beautiful XSS message saying hacked.

Hence, the vulnerability is approved. But the question now arises is how do we get the RCE?

## XSS to RCE

To be very honest, this is one of the most difficult tasks for me. Because I haven’t found a good article on it and I have to like bounce or understand the system thoroughly to figure out how I can get a RCE.

Upon studying the GitHub repo (the same repo), I figured that he is using a mal.js to get the RCE. So, let us study that file.

```
(function() {
const csrfMagicToken = 'csrfMagicToken'; // Replace this with the actual token
const formData = new FormData();
formData.append("__csrf_magic", csrfMagicToken);
formData.append("txtCommand", "id");
formData.append("txtRecallBuffer", "id");
formData.append("submit", "EXEC");
formData.append("dlPath", "");
formData.append("ulfile", new Blob(), "");
formData.append("txtPHPCommand", "");

fetch("https://192.168.102.61/diag_command.php", {
method: "POST",
body: formData
})
.then(response => response.text())
.then(data => {
const parser = new DOMParser();
const doc = parser.parseFromString(data, "text/html");
const contentDiv = doc.querySelector("div.content");

if (contentDiv) {
alert(contentDiv.textContent);
} else {
alert("No content found");
}
})
.catch(error => {
console.error("Error:", error);
alert("Request failed");
});
})();
```

### Understanding the Code

Let us understand the code line by line.

- The first 10 lines indicate that we are just giving the commands that need to be sent to the server. For example, csrf token, text command, text recall buffer, execution command.

- Next, we are fetching the data from the diag_command.php endpoint. The IP used in this, maybe this IP belongs to the machine he’s working on. So, we need to change the IP.

- And then we are sending a post request to that endpoint.

- Further, we are gathering the response of the endpoint, parsing it into a text-type string, and passing it into the div component.

- Finally, we have a conditional statement that will work as a printer of the result that came from the endpoint.

Now I worked with this JS file for almost two hours, tweaking every single line and writing my own. But none of them worked. Being frustrated, I thought to visit that endpoint by myself.

And here I had the Ohhhh! moment. We have the execute shell command. So, does that mean we will be able to execute the commands from here?

Let us test.

Damn! It works. Here we can try to get the RCE, but it becomes highly unstable and crashes after a few moments. After solving it, I asked the creator of this machine about the shell, and he mentioned that he would check about the stability. I think it is stable now.

However, I had solved it completely in a manual way, so I will share that way.

I tried a bunch of options, such as checking the /home directory, main file system directory, and even the /opt directory, but didn’t get any leads. Then I thought, why don’t we try the root directory?

Amazing, we got r00t.txt and user.txt in the same place. Now, we just have to use the cat command to get them.

## Conclusion

My final thoughts on this machine. It is an amazing machine, like it played with me on different levels. It gave me a bit of real-world experience as most of I face these kinds of issues (CVE will be correct, but it won’t be able to penetrate into the system). I had a major learning from playing this, and that is to learn the vulnerability and the CVE, up to the core level, on how they are working.

With that said, I will stop my write-up here. I hope you learned something, will meet you in the new write-up/blog. Till then, keep learning and keep hacking.

---
