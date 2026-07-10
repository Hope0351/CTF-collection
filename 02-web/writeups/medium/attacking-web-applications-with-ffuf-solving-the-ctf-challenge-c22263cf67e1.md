# :globe_with_meridians: Attacking Web Applications with Ffuf: Solving the CTF Challenge

---

# Attacking Web Applications with Ffuf: Solving the CTF Challenge

In this article, we’ll examine how to use the flexible web application fuzzing tool Ffuf to resolve a Capture the Flag (CTF) challenge. To assist you comprehend the methods and techniques used, we will outline each stage and give you a thorough walkthrough of the CTF challenge.

## Introduction to Ffuf

Ffuf is a powerful and fast web fuzzer written in Go. It allows security researchers and penetration testers to discover hidden files, directories, and other web application vulnerabilities by performing recursive and brute-force searches. Ffuf is known for its speed and flexibility, making it an excellent tool for CTF challenges.

## The CTF Challenge

Let’s dive into the CTF challenge that we will be solving using Ffuf. The challenge involves finding hidden directories and files on a web application hosted at `http://83.136.250.34:53339`. We will be using Ffuf to perform the fuzzing and discover these hidden resources.

## Step 1: Discovering Hidden Directories

To begin the challenge, we execute Ffuf with a wordlist containing common directory names and the target URL `http://83.136.250.34:53339/FUZZ`. The command looks like this:

```
sudo ffuf -w /opt/useful/SecLists/Discovery/Web-Content/directory-list-2.3-small.txt:FUZZ -u http://83.136.250.34:53339/FUZZ

/'___\ /'___\ /'___\
/\ \__/ /\ \__/ __ __ /\ \__/
\ \ ,__\\ \ ,__\/\ \/\ \ \ \ ,__\
\ \ \_/ \ \ \_/\ \ \_\ \ \ \ \_/
\ \_\ \ \_\ \ \____/ \ \_\
\/_/ \/_/ \/___/ \/_/

v1.4.1-dev
________________________________________________

:: Method : GET
:: URL : http://83.136.250.34:53339/FUZZ
:: Wordlist : FUZZ: /opt/useful/SecLists/Discovery/Web-Content/directory-list-2.3-small.txt
:: Follow redirects : false
:: Calibration : false
:: Timeout : 10
:: Threads : 40
:: Matcher : Response status: 200,204,301,302,307,401,403,405,500
________________________________________________

# Suite 300, San Francisco, California, 94105, USA. [Status: 200, Size: 986, Words: 423, Lines: 56, Duration: 0ms]
blog [Status: 301, Size: 322, Words: 20, Lines: 10, Duration: 0ms]
# directory-list-2.3-small.txt [Status: 200, Size: 986, Words: 423, Lines: 56, Duration: 0ms]
# license, visit http://creativecommons.org/licenses/by-sa/3.0/ [Status: 200, Size: 986, Words: 423, Lines: 56, Duration: 0ms]
# [Status: 200, Size: 986, Words: 423, Lines: 56, Duration: 0ms]
# Copyright 2007 James Fisher [Status: 200, Size: 986, Words: 423, Lines: 56, Duration: 0ms]
# or send a letter to Creative Commons, 171 Second Street, [Status: 200, Size: 986, Words: 423, Lines: 56, Duration: 0ms]
# This work is licensed under the Creative Commons [Status: 200, Size: 986, Words: 423, Lines: 56, Duration: 0ms]
# on atleast 3 different hosts [Status: 200, Size: 986, Words: 423, Lines: 56, Duration: 0ms]
# [Status: 200, Size: 986, Words: 423, Lines: 56, Duration: 0ms]
# Priority ordered case sensative list, where entries were found [Status: 200, Size: 986, Words: 423, Lines: 56, Duration: 0ms]
[Status: 200, Size: 986, Words: 423, Lines: 56, Duration: 0ms]
# [Status: 200, Size: 986, Words: 423, Lines: 56, Duration: 0ms]
# [Status: 200, Size: 986, Words: 423, Lines: 56, Duration: 0ms]
# Attribution-Share Alike 3.0 License. To view a copy of this [Status: 200, Size: 986, Words: 423, Lines: 56, Duration: 0ms]
forum [Status: 301, Size: 323, Words: 20, Lines: 10, Duration: 0ms]
[Status: 200, Size: 986, Words: 423, Lines: 56, Duration: 0ms]
:: Progress: [87664/87664] :: Job [1/1] :: 9901 req/sec :: Duration: [0:02:06] :: Errors: 0 ::After running the command, Ffuf starts scanning the target URL with the provided wordlist. It sends multiple requests and analyzes the responses to identify existing directories. The output reveals the discovered directories along with their corresponding HTTP response status codes, sizes, words, lines, and durations.
```

Based on the output, Ffuf discovers the following directories:

- `/blog` (Status: 301, Size: 322)

- `/forum` (Status: 301, Size: 323)

The directory we need to find in this step is `/forum`.

## Step 2: Fuzzing the ‘/blog’ Directory

In the second step, we need to fuzz the `/blog` directory and find all the pages within it. One of these pages is expected to contain a flag. We use Ffuf again to perform the fuzzing operation with the wordlist and target URL `http://83.136.250.34:53339/blog/FUZZ.php`. The command is as follows:

```
ffuf -w /opt/useful/SecLists/Discovery/Web-Content/directory-list-2.3-small.txt:FUZZ -u http://83.136.250.34:53339/blog/FUZZ.php

/'___\ /'___\ /'___\
/\ \__/ /\ \__/ __ __ /\ \__/
\ \ ,__\\ \ ,__\/\ \/\ \ \ \ ,__\
\ \ \_/ \ \ \_/\ \ \_\ \ \ \ \_/
\ \_\ \ \_\ \ \____/ \ \_\
\/_/ \/_/ \/___/ \/_/

v1.4.1-dev
________________________________________________

:: Method : GET
:: URL : http://83.136.250.34:53339/blog/FUZZ.php
:: Wordlist : FUZZ: /opt/useful/SecLists/Discovery/Web-Content/directory-list-2.3-small.txt
:: Follow redirects : false
:: Calibration : false
:: Timeout : 10
:: Threads : 40
:: Matcher : Response status: 200,204,301,302,307,401,403,405,500
________________________________________________

# [Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 0ms]
# This work is licensed under the Creative Commons [Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 0ms]
# directory-list-2.3-small.txt [Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 0ms]
# license, visit http://creativecommons.org/licenses/by-sa/3.0/ [Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 0ms]
# [Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 0ms]
# Attribution-Share Alike 3.0 License. To view a copy of this [Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 1ms]
# Suite 300, San Francisco, California, 94105, USA. [Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 1ms]
home [Status: 200, Size: 1046, Words: 438, Lines: 58, Duration: 1ms]
# or send a letter to Creative Commons, 171 Second Street, [Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 1ms]
# [Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 1ms]
# Copyright 2007 James Fisher [Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 2ms]
# Priority ordered case sensative list, where entries were found [Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 1ms]
# on atleast 3 different hosts [Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 0ms]
# [Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 0ms]
index [Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 0ms]
[Status: 403, Size: 281, Words: 20, Lines: 10, Duration: 0ms]
[Status: 403, Size: 281, Words: 20, Lines: 10, Duration: 0ms]
:: Progress: [87664/87664] :: Job [1/1] :: 18307 req/sec :: Duration: [0:01:56] :: Errors: 0 ::
```

Ffuf executes the fuzzing operation, sending multiple requests to the target URL with different filenames. It analyzes the responses and provides output with details similar to the previous step.

After the fuzzing process, Ffuf discovers the following page:

- `/blog/home.php` (Status: 200, Size: 1046, Words: 438, Lines: 58)

To find the flag, we navigate to the discovered page: `http://83.136.250.34:53339/blog/home.php`. The flag is revealed on this page:

Flag: `HTB{bru73_f0r_c0mm0n_*}`

## Step 3: Finding More Files/Directories

In the third step, we continue the search for additional files and directories. One of these resources should provide us with another flag. We need to apply the knowledge gained so far and repeat the process.

## Get Ahmet Talha Şen’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

After exploring further, we find the following URL containing the second flag:

- `http://94.237.62.6:51052/forum/flag.php`

Flag: `HTB{fuzz1n6_7h3_}`

## Step 4: Discovering the Swag Shop Sub-Domain

In the final step, we perform a sub-domain fuzzing test on `hackthebox.eu` to discover the online Swag Shop of HackTheBox. We use Ffuf with a wordlist of subdomains and the target URL `http://FUZZ.hackthebox.eu/`. The command is as follows:

```
ffuf -w /opt/useful/SecLists/Discovery/DNS/subdomains-top1million-5000.txt:FUZZ -u http://FUZZ.hackthebox.eu/

/'___\ /'___\ /'___\
/\ \__/ /\ \__/ __ __ /\ \__/
\ \ ,__\\ \ ,__\/\ \/\ \ \ \ ,__\
\ \ \_/ \ \ \_/\ \ \_\ \ \ \ \_/
\ \_\ \ \_\ \ \____/ \ \_\
\/_/ \/_/ \/___/ \/_/

v1.4.1-dev
________________________________________________

:: Method : GET
:: URL : http://FUZZ.hackthebox.eu/
:: Wordlist : FUZZ: /opt/useful/SecLists/Discovery/DNS/subdomains-top1million-5000.txt
:: Follow redirects : false
:: Calibration : false
:: Timeout : 10
:: Threads : 40
:: Matcher : Response status: 200,204,301,302,307,401,403,405,500
________________________________________________

dev [Status: 301, Size: 0, Words: 1, Lines: 1, Duration: 22ms]
mail [Status: 301, Size: 236, Words: 9, Lines: 7, Duration: 14ms]
forum [Status: 301, Size: 0, Words: 1, Lines: 1, Duration: 33ms]
www [Status: 301, Size: 0, Words: 1, Lines: 1, Duration: 57ms]
:: Progress: [112/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 69 ::: Progress: [169/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 125 app [Status: 301, Size: 0, Words: 1, Lines: 1, Duration: 35ms]
:: Progress: [171/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 127 forums [Status: 301, Size: 0, Words: 1, Lines: 1, Duration: 42ms]
:: Progress: [177/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 132 store [Status: 301, Size: 0, Words: 1, Lines: 1, Duration: 57ms]
:: Progress: [179/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 133 help [Status: 301, Size: 0, Words: 1, Lines: 1, Duration: 28ms]
:: Progress: [186/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 139 dev2 [Status: 301, Size: 0, Words: 1, Lines: 1, Duration: 18ms]
:: Progress: [211/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 163 api [Status: 301, Size: 162, Words: 5, Lines: 8, Duration: 76ms]
:: Progress: [270/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 221 :: Progress: [313/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 263 calendar [Status: 302, Size: 249, Words: 9, Lines: 7, Duration: 9ms]
:: Progress: [389/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 339 billing [Status: 301, Size: 162, Words: 5, Lines: 8, Duration: 11ms]
:: Progress: [434/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 383 :: Progress: [443/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 391 MAIL [Status: 301, Size: 236, Words: 9, Lines: 7, Duration: 11ms]
:: Progress: [502/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 450 :: Progress: [567/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 514 :: Progress: [605/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 552 :: Progress: [650/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 597 :: Progress: [690/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 637 sites [Status: 302, Size: 259, Words: 10, Lines: 10, Duration: 206ms]
:: Progress: [697/4997] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 644 :: Progress: [735/4997] :: Job [1/1] :: 959 req/sec :: Duration: [0:00:01] :: Errors: 68resources [Status: 403, Size: 16, Words: 3, Lines: 1, Duration: 14ms]
:: Progress: [770/4997] :: Job [1/1] :: 1115 req/sec :: Duration: [0:00:01] :: Errors: 7:: Progress: [781/4997] :: Job [1/1] :: 1292 req/sec :: Duration: [0:00:01] :: Errors: 7:: Progress: [824/4997] :: Job [1/1] :: 1033 req/sec :: Duration: [0:00:01] :: Errors: 7:: Progress: [867/4997] :: Job [1/1] :: 1087 req/sec :: Duration: [0:00:01] :: Errors: 8:: Progress: [908/4997] :: Job [1/1] :: 1116 req/sec :: Duration: [0:00:01] :: Errors: 8:: Progress: [948/4997] :: Job [1/1] :: 1567 req/sec :: Duration: [0:00:01] :: Errors: 8groups [Status: 302, Size: 238, Words: 9, Lines: 7, Duration: 9ms]
:: Progress: [976/4997] :: Job [1/1] :: 1842 req/sec :: Duration: [0:00:01] :: Errors: 9:: Progress: [982/4997] :: Job [1/1] :: 1927 req/sec :: Duration: [0:00:01] :: Errors: 9:: Progress: [1026/4997] :: Job [1/1] :: 1924 req/sec :: Duration: [0:00:01] :: Errors: :: Progress: [1063/4997] :: Job [1/1] :: 1212 req/sec :: Duration: [0:00:02] :: Errors: :: Progress: [1107/4997] :: Job [1/1] :: 1329 req/sec :: Duration: [0:00:02] :: Errors: :: Progress: [1147/4997] :: Job [1/1] :: 1542 req/sec :: Duration: [0:00:02] :: Errors: enterprise [Status: 301, Size: 0, Words: 1, Lines: 1, Duration: 30ms]
:: Progress: [1161/4997] :: Job [1/1] :: 1599 req/sec :: Duration: [0:00:02] :: Errors: WWW [Status: 301, Size: 0, Words: 1, Lines: 1, Duration: 42ms]
:: Progress: [1191/4997] :: Job [1/1] :: 2079 req/sec :: Duration: [0:00:02] :: Errors: :: Progress: [1192/4997] :: Job [1/1] :: 2140 req/sec :: Duration: [0:00:02] :: Errors: :: Progress: [1235/4997] :: Job [1/1] :: 1613 req/sec :: Duration: [0:00:02] :: Errors: :: Progress: [1274/4997] :: Job [1/1] :: 1724 req/sec :: Duration: [0:00:02] :: Errors: :: Progress: [1313/4997] :: Job [1/1] :: 1329 req/sec :: Duration: [0:00:02] :: Errors: sentry [Status: 301, Size: 0, Words: 1, Lines: 1, Duration: 24ms]
:: Progress: [1322/4997] :: Job [1/1] :: 1420 req/sec :: Duration: [0:00:02] :: Errors: :: Progress: [1350/4997] :: Job [1/1] :: 1859 req/sec :: Duration: [0:00:02] :: Errors: :: Progress: [1401/4997] :: Job [1/1] :: 1635 req/sec :: Duration: [0:00:03] :: Errors: :: Progress: [1439/4997] :: Job [1/1] :: 1863 req/sec :: Duration: [0:00:03] :: Errors: :: Progress: [1483/4997] :: Job [1/1] :: 1568 req/sec :: Duration: [0:00:03] :: Errors: :: Progress: [1530/4997] :: Job [1/1] :: 2353 req/sec :: Duration: [0:00:03] :: Errors: :: Progress: [1568/4997] :: Job [1/1] :: 1552 req/sec :: Duration: [0:00:03] :: Errors: :: Progress: [1603/4997] :: Job [1/1] :: 1234 req/sec :: Duration: [0:00:03] :: Errors: :: Progress: [1638/4997] :: Job [1/1] :: 1000 req/sec :: Duration: [0:00:03] :: Errors: :: Progress: [1677/4997] :: Job [1/1] :: 1494 req/sec :: Duration: [0:00:03] :: Errors: :: Progress: [1721/4997] :: Job [1/1] :: 1558 req/sec :: Duration: [0:00:04] :: Errors: :: Progress: [1760/4997] :: Job [1/1] :: 2350 req/sec :: Duration: [0:00:04] :: Errors: :: Progress: [1808/4997] :: Job [1/1] :: 1154 req/sec :: Duration: [0:00:04] :: Errors: :: Progress: [1870/4997] :: Job [1/1] :: 2169 req/sec :: Duration: [0:00:04] :: Errors: :: Progress: [1917/4997] :: Job [1/1] :: 1726 req/sec :: Duration: [0:00:04] :: Errors: :: Progress: [1971/4997] :: Job [1/1] :: 1534 req/sec :: Duration: [0:00:04] :: Errors: academy [Status: 301, Size: 0, Words: 1, Lines: 1, Duration: 30ms]
:: Progress: [2001/4997] :: Job [1/1] :: 1987 req/sec :: Duration: [0:00:04] :: Errors: :: Progress: [2009/4997] :: Job [1/1] :: 1802 req/sec :: Duration: [0:00:04] :: Errors: :: Progress: [2051/4997] :: Job [1/1] :: 1313 req/sec :: Duration: [0:00:04] :: Errors: :: Progress: [2087/4997] :: Job [1/1] :: 2038 req/sec :: Duration: [0:00:05] :: Errors: :: Progress: [2135/4997] :: Job [1/1] :: 1693 req/sec :: Duration: [0:00:05] :: Errors: :: Progress: [2165/4997] :: Job [1/1] :: 2187 req/sec :: Duration: [0:00:05] :: Errors: :: Progress: [2222/4997] :: Job [1/1] :: 2221 req/sec :: Duration: [0:00:05] :: Errors: :: Progress: [2277/4997] :: Job [1/1] :: 2543 req/sec :: Duration: [0:00:05] :: Errors: :: Progress: [2312/4997] :: Job [1/1] :: 2217 req/sec :: Duration: [0:00:05] :: Errors: :: Progress: [2352/4997] :: Job [1/1] :: 2104 req/sec :: Duration: [0:00:05] :: Errors: :: Progress: [2390/4997] :: Job [1/1] :: 2084 req/sec :: Duration: [0:00:05] :: Errors: :: Progress: [2434/4997] :: Job [1/1] :: 2035 req/sec :: Duration: [0:00:06] :: Errors: :: Progress: [2495/4997] :: Job [1/1] :: 2927 req/sec :: Duration: [0:00:06] :: Errors: :: Progress: [2538/4997] :: Job [1/1] :: 2568 req/sec :: Duration: [0:00:06] :: Errors: :: Progress: [2586/4997] :: Job [1/1] :: 2870 req/sec :: Duration: [0:00:06] :: Errors: :: Progress: [2631/4997] :: Job [1/1] :: 3108 req/sec :: Duration: [0:00:06] :: Errors: :: Progress: [2670/4997] :: Job [1/1] :: 1627 req/sec :: Duration: [0:00:06] :: Errors: :: Progress: [2734/4997] :: Job [1/1] :: 3148 req/sec :: Duration: [0:00:06] :: Errors: :: Progress: [2777/4997] :: Job [1/1] :: 2036 req/sec :: Duration: [0:00:06] :: Errors: :: Progress: [2820/4997] :: Job [1/1] :: 1706 req/sec :: Duration: [0:00:07] :: Errors: :: Progress: [2858/4997] :: Job [1/1] :: 1945 req/sec :: Duration: [0:00:07] :: Errors: :: Progress: [2908/4997] :: Job [1/1] :: 1840 req/sec :: Duration: [0:00:07] :: Errors: :: Progress: [2961/4997] :: Job [1/1] :: 2492 req/sec :: Duration: [0:00:07] :: Errors: :: Progress: [3001/4997] :: Job [1/1] :: 1574 req/sec :: Duration: [0:00:07] :: Errors: :: Progress: [3041/4997] :: Job [1/1] :: 1805 req/sec :: Duration: [0:00:07] :: Errors: :: Progress: [3082/4997] :: Job [1/1] :: 1845 req/sec :: Duration: [0:00:07] :: Errors: :: Progress: [3129/4997] :: Job [1/1] :: 1828 req/sec :: Duration: [0:00:07] :: Errors: :: Progress: [3177/4997] :: Job [1/1] :: 1125 req/sec :: Duration: [0:00:08] :: Errors: :: Progress: [3226/4997] :: Job [1/1] :: 1873 req/sec :: Duration: [0:00:08] :: Errors: :: Progress: [3279/4997] :: Job [1/1] :: 1445 req/sec :: Duration: [0:00:08] :: Errors: :: Progress: [3315/4997] :: Job [1/1] :: 1710 req/sec :: Duration: [0:00:08] :: Errors: :: Progress: [3353/4997] :: Job [1/1] :: 1484 req/sec :: Duration: [0:00:08] :: Errors: :: Progress: [3389/4997] :: Job [1/1] :: 1517 req/sec :: Duration: [0:00:08] :: Errors: :: Progress: [3437/4997] :: Job [1/1] :: 1429 req/sec :: Duration: [0:00:08] :: Errors: :: Progress: [3481/4997] :: Job [1/1] :: 2019 req/sec :: Duration: [0:00:08] :: Errors: :: Progress: [3542/4997] :: Job [1/1] :: 2424 req/sec :: Duration: [0:00:09] :: Errors: :: Progress: [3574/4997] :: Job [1/1] :: 2626 req/sec :: Duration: [0:00:09] :: Errors: :: Progress: [3612/4997] :: Job [1/1] :: 1306 req/sec :: Duration: [0:00:09] :: Errors: :: Progress: [3671/4997] :: Job [1/1] :: 2375 req/sec :: Duration: [0:00:09] :: Errors: :: Progress: [3729/4997] :: Job [1/1] :: 1818 req/sec :: Duration: [0:00:09] :: Errors: :: Progress: [3758/4997] :: Job [1/1] :: 1768 req/sec :: Duration: [0:00:09] :: Errors: :: Progress: [3792/4997] :: Job [1/1] :: 1713 req/sec :: Duration: [0:00:09] :: Errors: :: Progress: [3844/4997] :: Job [1/1] :: 2408 req/sec :: Duration: [0:00:09] :: Errors: :: Progress: [3893/4997] :: Job [1/1] :: 1761 req/sec :: Duration: [0:00:10] :: Errors: :: Progress: [3934/4997] :: Job [1/1] :: 1815 req/sec :: Duration: [0:00:10] :: Errors: drive [Status: 302, Size: 237, Words: 9, Lines: 7, Duration: 16ms]
:: Progress: [3977/4997] :: Job [1/1] :: 1670 req/sec :: Duration: [0:00:10] :: Errors: :: Progress: [3982/4997] :: Job [1/1] :: 1514 req/sec :: Duration: [0:00:10] :: Errors: :: Progress: [4022/4997] :: Job [1/1] :: 1567 req/sec :: Duration: [0:00:10] :: Errors: :: Progress: [4070/4997] :: Job [1/1] :: 2264 req/sec :: Duration: [0:00:10] :: Errors: :: Progress: [4115/4997] :: Job [1/1] :: 1640 req/sec :: Duration: [0:00:10] :: Errors: :: Progress: [4157/4997] :: Job [1/1] :: 1586 req/sec :: Duration: [0:00:10] :: Errors: :: Progress: [4200/4997] :: Job [1/1] :: 2338 req/sec :: Duration: [0:00:10] :: Errors: :: Progress: [4252/4997] :: Job [1/1] :: 2406 req/sec :: Duration: [0:00:11] :: Errors: :: Progress: [4287/4997] :: Job [1/1] :: 2499 req/sec :: Duration: [0:00:11] :: Errors: :: Progress: [4321/4997] :: Job [1/1] :: 2051 req/sec :: Duration: [0:00:11] :: Errors: :: Progress: [4358/4997] :: Job [1/1] :: 2245 req/sec :: Duration: [0:00:11] :: Errors: :: Progress: [4396/4997] :: Job [1/1] :: 2348 req/sec :: Duration: [0:00:11] :: Errors: :: Progress: [4427/4997] :: Job [1/1] :: 2136 req/sec :: Duration: [0:00:11] :: Errors: :: Progress: [4447/4997] :: Job [1/1] :: 1852 req/sec :: Duration: [0:00:11] :: Errors: :: Progress: [4483/4997] :: Job [1/1] :: 1443 req/sec :: Duration: [0:00:11] :: Errors: :: Progress: [4524/4997] :: Job [1/1] :: 2202 req/sec :: Duration: [0:00:12] :: Errors: :: Progress: [4572/4997] :: Job [1/1] :: 1786 req/sec :: Duration: [0:00:12] :: Errors: :: Progress: [4623/4997] :: Job [1/1] :: 2484 req/sec :: Duration: [0:00:12] :: Errors: :: Progress: [4684/4997] :: Job [1/1] :: 2423 req/sec :: Duration: [0:00:12] :: Errors: :: Progress: [4740/4997] :: Job [1/1] :: 2885 req/sec :: Duration: [0:00:12] :: Errors: :: Progress: [4804/4997] :: Job [1/1] :: 2433 req/sec :: Duration: [0:00:12] :: Errors: :: Progress: [4836/4997] :: Job [1/1] :: 2319 req/sec :: Duration: [0:00:12] :: Errors: :: Progress: [4876/4997] :: Job [1/1] :: 2326 req/sec :: Duration: [0:00:12] :: Errors: :: Progress: [4918/4997] :: Job [1/1] :: 2619 req/sec :: Duration: [0:00:13] :: Errors: :: Progress: [4972/4997] :: Job [1/1] :: 2797 req/sec :: Duration: [0:00:13] :: Errors: :: Progress: [4997/4997] :: Job [1/1] :: 2343 req/sec :: Duration: [0:00:13] :: Errors: :: Progress: [4997/4997] :: Job [1/1] :: 1751 req/sec :: Duration: [0:00:30] :: Errors: 4976 ::Ffuf executes the fuzzing operation and generates output with details similar to the previous steps. After scanning, Ffuf discovers the following sub-domain:
```

- `store.hackthebox.eu` (Status: 200, Size: ..., Words: ..., Lines: ...)

The full domain of the HackTheBox Swag Shop is `store.hackthebox.eu`.

## Step 5: VHost Fuzzing

The first challenge requires us to perform a VHost fuzzing scan on the domain ‘academy.htb’ and identify any additional VHosts. To accomplish this, we use the `ffuf` tool with the following command:

```
ffuf -w /usr/share/seclists/Discovery/DNS/subdomains-top1million-5000.txt:FUZZ -u http://94.237.59.206:42671/ -H 'Host: FUZZ.academy.htb' -ms 0

/'___\ /'___\ /'___\
/\ \__/ /\ \__/ __ __ /\ \__/
\ \ ,__\\ \ ,__\/\ \/\ \ \ \ ,__\
\ \ \_/ \ \ \_/\ \ \_\ \ \ \ \_/
\ \_\ \ \_\ \ \____/ \ \_\
\/_/ \/_/ \/___/ \/_/

v2.0.0-dev
________________________________________________

:: Method : GET
:: URL : http://94.237.59.206:42671/
:: Wordlist : FUZZ: /usr/share/seclists/Discovery/DNS/subdomains-top1million-5000.txt
:: Header : Host: FUZZ.academy.htb
:: Follow redirects : false
:: Calibration : false
:: Timeout : 10
:: Threads : 40
:: Matcher : Response size: 0
________________________________________________

[Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 59ms]
* FUZZ: test

[Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 4155ms]
* FUZZ: admin

:: Progress: [4989/4989] :: Job [1/1] :: 578 req/sec :: Duration: [0:00:11] :: Errors: 0 ::
```

The scan result reveals the existence of two VHosts: ‘`test.academy.htb`’ and ‘`admin.academy.htb`’.

## Step 6: Parameter Fuzzing

In the second challenge, we need to run a parameter fuzzing scan on a specific webpage and determine the accepted parameter. Using the `ffuf` tool, we execute the following command:

```
ffuf -w /usr/share/seclists/Discovery/Web-Content/web-extensions.txt:FUZZ -u http://admin.academy.htb:34138/admin/admin.php?FUZZ=key -fs 798
user
```

The scan output indicates that the parameter ‘`key`’ is accepted by the webpage.

## Step 7: Wordlist Creation and POST Request

For the third challenge, we have to create a wordlist called ‘`ids.txt`,’ identify the accepted value through a fuzzing scan, and use it in a ‘`POST`’ request with ‘curl’ to retrieve the flag. Let’s follow these steps:

- Create the wordlist ‘ids.txt’ with the desired values.

- Perform a fuzzing scan using `ffuf` to identify the accepted value for the '`id`' parameter:

```
ffuf -w ids.txt:FUZZ -u http://admin.academy.htb:34138/admin/admin.php -X POST -d 'id=73' -H 'Content-Type: application/x-www-form-urlencoded'
```

The response contains the flag: `HTB{p4r4m373r_fuzz1n6_15_}`.

## Skills Assessment — Web Fuzzing

## Step 1: Sub-Domain/VHost and Extension Fuzzing

In the fourth challenge, we are tasked with running a sub-domain/VHost fuzzing scan on ‘`.academy.htb`’ and identifying all the sub-domains. We employ `ffuf` once again:

```
ffuf -w /usr/share/seclists/Discovery/DNS/subdomains-top1million-5000.txt:FUZZ -u http://94.237.55.114:47287/ -H 'Host: FUZZ.academy.htb' -ms 0

/'___\ /'___\ /'___\
/\ \__/ /\ \__/ __ __ /\ \__/
\ \ ,__\\ \ ,__\/\ \/\ \ \ \ ,__\
\ \ \_/ \ \ \_/\ \ \_\ \ \ \ \_/
\ \_\ \ \_\ \ \____/ \ \_\
\/_/ \/_/ \/___/ \/_/

v2.0.0-dev
________________________________________________

:: Method : GET
:: URL : http://94.237.55.114:47287/
:: Wordlist : FUZZ: /usr/share/seclists/Discovery/DNS/subdomains-top1million-5000.txt
:: Header : Host: FUZZ.academy.htb
:: Follow redirects : false
:: Calibration : false
:: Timeout : 10
:: Threads : 40
:: Matcher : Response size: 0
________________________________________________

[Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 63ms]
* FUZZ: test

[Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 61ms]
* FUZZ: archive

[Status: 200, Size: 0, Words: 1, Lines: 1, Duration: 67ms]
* FUZZ: faculty

:: Progress: [4989/4989] :: Job [1/1] :: 578 req/sec :: Duration: [0:00:09] :: Errors: 0 ::
```

The scan output reveals three sub-domains: ‘`test.academy.htb`,’ ‘`archive.academy.htb`,’ and ‘`faculty.academy.htb`.’

Before running the page fuzzing scan, it’s recommended to perform an extension fuzzing scan. The goal is to identify the different extensions accepted by the domains. We can accomplish this with the following command:

```
ffuf -w /usr/share/seclists/Discovery/Web-Content/web-extensions.txt:FUZZ -u http://94.237.55.114:47287/indexFUZZ

/'___\ /'___\ /'___\
/\ \__/ /\ \__/ __ __ /\ \__/
\ \ ,__\\ \ ,__\/\ \/\ \ \ \ ,__\
\ \ \_/ \ \ \_/\ \ \_\ \ \ \ \_/
\ \_\ \ \_\ \ \____/ \ \_\
\/_/ \/_/ \/___/ \/_/

v2.0.0-dev
________________________________________________

:: Method : GET
:: URL : http://94.237.55.114:47287/indexFUZZ
:: Wordlist : FUZZ: /usr/share/seclists/Discovery/Web-Content/web-extensions.txt
:: Follow redirects : false
:: Calibration : false
:: Timeout : 10
:: Threads : 40
:: Matcher : Response status: 200,204,301,302,307,401,403,405,500
________________________________________________

[Status: 200, Size: 985, Words: 423, Lines: 55, Duration: 63ms]
* FUZZ: .php

[Status: 403, Size: 281, Words: 20, Lines: 10, Duration: 61ms]
* FUZZ: .phps

:: Progress: [40/40] :: Job [1/1] :: 0 req/sec :: Duration: [0:00:00] :: Errors: 0 ::The scan output indicates that the extensions ‘.php’ and ‘.phps’ are accepted.
```

```
ffuf -w /usr/share/seclists/Discovery/Web-Content/web-extensions.txt:FUZZ -u http://faculty:47287/indexFUZZ
.php7
```

One of the pages you will identify should say ‘You don’t have access!’. What is the full page URL?

```
ffuf -w /usr/share/seclists/Discovery/Web-Content/directory-list-2.3-small.txt:FUZZ -u <http://faculty.academy.htb:47287/FUZZ> -recursion -recursion-depth 1 -e .php -v -t 80
index.hph7
courses
linux-security.php7
```

`http://faculty.academy.htb:47287/courses/linux-security.php7`

## Challenge 5: Parameter Identification and Fuzzing

In the fifth challenge, we need to identify the parameters accepted by a specific page obtained in the previous step. We run the following command to achieve this:

```
ffuf -w /opt/useful/SecLists/Discovery/Web-Content/burp-parameter-names.txt:FUZZ -u http://faculty.academy.htb:PORT/courses/linux-security.php7 -X POST -d 'FUZZ=key' -H 'Content-Type: application/x-www-form-urlencoded'
ffuf -w /opt/useful/SecLists/Discovery/Web-Content/burp-parameter-names.txt:FUZZ -u http://faculty.academy.htb:30796/courses/linux-security.php7 -X POST -d 'FUZZ=key' -H 'Content-Type: application/x-www-form-urlencoded' -fs 774
```

The scan output reveals two parameters: ‘`user`’ and ‘`username`.’

Next, we are required to fuzz the identified parameters with working values to retrieve the flag. We can accomplish this using the following command:

```
ffuf -w /opt/useful/SecLists/Usernames/xato-net-10-million-usernames.txt:FUZZ -u http://faculty.academy.htb:30401/courses/linux-security.php7 -X POST -d 'username=FUZZ' -H 'Content-Type: application/x-www-form-urlencoded'
ffuf -w /opt/useful/SecLists/Usernames/xato-net-10-million-usernames.txt:FUZZ -u http://faculty.academy.htb:30401/courses/linux-security.php7 -X POST -d 'username=FUZZ' -H 'Content-Type: application/x-www-form-urlencoded' -fs 781
```

The response contains the flag: `HTB{w3b_fuzz1n6_}`.

## Conclusion

In this article, we explored the process of solving various web fuzzing challenges encountered in a CTF competition. We learned how to perform VHost fuzzing, parameter fuzzing, wordlist creation, and fuzzing scans for sub-domains, extensions, and parameters. By following these steps and leveraging the `ffuf` tool, we successfully obtained the desired flags. Web fuzzing is a crucial skill in the field of cybersecurity, allowing us to discover vulnerabilities and potential attack vectors.

More Walkthrough:

---
