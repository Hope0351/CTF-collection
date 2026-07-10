# :globe_with_meridians: Intercepting LDAP With InterceptSuite

> **Original Source:** [Intercepting LDAP With InterceptSuite](https://infosecwriteups.com/intercepting-ldap-with-interceptsuite-45d219c14943)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Intercepting LDAP With InterceptSuite


LDAP authentication is everywhere in networks, but intercepting encrypted LDAP traffic can be challenging. LDAP authentication in the web is generally handled by the backend, and from the frontend, we have HTTP, which is easy to intercept.


When we are directly dealing with LDAP traffic, like in an internal network, a desktop application that performs LDAP on a local network, it's challenging to intercept the LDAP in those cases, especially when the LDAP is using STARTTLS instead of TLS on port 636.


For anyone who does not know about STARTTLS, STARTTLS is a command, or you can say a method that a client and server use to verify if the connection should be in plain text or TLS. It was originally developed for the SMTP protocol, but is used in many protocols. But each protocol has its own way to work with this command.


The general idea is that when a service is running on a server and it supports plain text as well as TLS, or in some cases, for backwards compatibility, the client connects to the server via plain text and uses STARTTLS to check with the server if the server supports TLS or not. The connection will either cancel or continue in plaintext, it depends on the protocol, like SMTP, PostgreSQL, etc, but if the server returns TLS availability, then the client initiates the TLS handshake.


The problem with this is that there are very few proxy or MITM tools available to intercept TLS network traffic for non-HTTP protocols. Some available example is MITM Proxy, which also does not support protocols that use STARTTLS, and in some cases, it requires extra configuration to intercept different protocols.


The reason is that in STARTTLS, the connection is created for plain text, then the existing plaintext TCP connection is upgraded to a TLS connection.


In normal cases, as soon as the TCP handshake is complete, the client will send a Client HELLO packet for TLS handshake when the client knows the server is using TLS.


*TCP/TLS handshake*


When the client knows the server is plaintext, after the TCP handshake client will send a plaintext packet. In startTLS, after the TCP handshake, the client sends a plaintext packet and then upgrades the same connection to TLS with a Client Hello packet.


*General STARTTLS*


This makes it difficult to intercept and track, as each protocol has its own method to change a plain-text connection to TLS, some examples are SMTP, LDAP, Postgresql, MSSQL, or even a custom protocol that uses its own methods for this.

## LDAP TLS Session


LDAP, the protocol uses both TLS and StartTLS, it uses port 636 for TLS. In most cases, when a client tries to connect on port 636, it recognises that it's TLS and performs the TLS handshake soon after the TCP handshake. However, port 389 is a plaintext port that also supports TLS.


*LDAP STARTTLS*


In this case, the client confirms with the server whether TLS should be used or not. This confirmation process happens in plain text, and once confirmed, the client will upgrade the plaintext connection to TLS if the server confirms that TLS is available.

## Intercepting STARTLS


To address the challenges with intercepting network traffic beyond just HTTP protocols, I’ve developed a new application called [InterceptSuite](https://github.com/InterceptSuite/InterceptSuite). Its main focus is on intercepting network traffic for non-HTTP protocols. It is currently the only fully functional proxy application with universal STARTTLS support, compatible with any known or custom protocol. It can peek into ongoing connections, utilising the C language, which speeds up processing significantly. This allows it to perform TLS handshake seamlessly, detect the use of STARTTLS or other plaintext-to-TLS upgrades efficiently, all without affecting performance or risking TCP session timeouts.


## Get Sourav Kalal’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


InterceptSuite is available in two different editions:


I have a local LDAP server if we do a quick Nmap scan


```
Nmap scan report for (192.168.1.4)
Host is up.

PORT STATE SERVICE VERSION
389/tcp open ldap
636/tcp open ldapssl
```


It has both 389 and 636 ports open. If we try to connect over port 389 and look at Wireshark, we can see first 3 packets are just TCP handshake, post we have the 4th packet in plaintext.


If we look at the 22nd packet, we can see a STARTTLS request from the client to the server.


And we have the 24th packet as STARTLS, as success means the server confirms TLS is available.


If we now check the 26th packet, it contains TCP payload as 16 03 01 00 fc 01 00 00 f8 03 03, which is for TLS handshake CLIENT HELLO.


After several plaintext packets are sent, the connection is upgraded to TLS. The process varies for each protocol. For instance, SMTP typically requires just two or three packets to initiate the TLS upgrade. In contrast, the LDAP protocol uses an ExtendedRequest with an OID to upgrade to TLS.


Other protocols also employ different messages and methods for this upgrade. For example, PostgreSQL uses an 8-byte SSLRequest message. Each protocol has its own unique way of handling the TLS upgrade.


If we open the InterceptSuite Pro and set the proxy in Windows using [ProxyBridge](https://interceptsuite.com/download/proxybridge), if we run the client again and check into the InterceptSuite Proxy History, we can see the plaintext data for the LDAP connection.


We can use the Python extension API to dissect data as well, allowing you to parse the specific data. If not, you can right-click and select Export PCAP and open the PCAP file in Wireshark.


If you want to try InterceptSuite, you can download the Standard and Pro versions from below:


The pro version will require the license key to work. You can get 50% off on the yearly license with the coupon: FRESHSTART


You can check out the GitHub repository for the source code:

---

*Originally published on [Medium](https://infosecwriteups.com/intercepting-ldap-with-interceptsuite-45d219c14943). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
