# :globe_with_meridians: Insecure Deserialization → RCE

> **Original Source:** [Insecure Deserialization → RCE](https://infosecwriteups.com/insecure-deserialization-rce-b457eed0e2f9)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Insecure Deserialization → RCE


## In this blog, we will discuss insecure deserialization and how we can achieve RCE


## First, what is “serialization”?


Serialization = converting an object into a format that can be:


- > Stored

- > Sent over a network

- > Saved in cookies or sessions


```
Python → pickle

Java → Serializable

PHP → serialize()

.NET → BinaryFormatter
```


```
Example of Serialization data

Python (pickle) – Binary → Base64 (very common)

Original object

{"username": "alex", "role": "user"}

Serialized (pickle → Base64)

gASVJAAAAAAAAAB9lCiMBHVzZXKUjAVhZG1pbpSMBHJvbGWUjAR1c2VylHUu
```


This is stored in the cookies, and the reverse process is called deserialization.

## How does insecure deserialization occur?


```
Serialization data
{"username": "alex", "role": "user"}

Modified Serialization data by attacker which is now insecure
{"username": "alex", "role": "admin"}

insecure deserialization data
gASVJwAAAAAAAAB9lCiMBHVzZXKUjANyYWqUjARyb2xllIwEdXNlcpR1Lg==

Which leads to privilage esclation from normaluser -> admin
```

---

*Originally published on [Medium](https://infosecwriteups.com/insecure-deserialization-rce-b457eed0e2f9). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
