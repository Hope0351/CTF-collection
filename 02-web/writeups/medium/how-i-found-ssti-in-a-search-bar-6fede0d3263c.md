# :globe_with_meridians: How I Found SSTI in a Search Bar. While casually poking around a website…

> **Original Source:** [How I Found SSTI in a Search Bar. While casually poking around a website…](https://infosecwriteups.com/how-i-found-ssti-in-a-search-bar-6fede0d3263c)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## 🧪 Testing for SSTI


I began with some common SSTI payloads:


`{{7*7}}`


`${7*7}`


`<%= 7*7 %>`


`{{config}}`


Most of them either returned nothing or gave back the input as-is.


But then I tried:


```
{{7*7}}
```


Boom. The result came back as:

>

***Results found for: 49***


This was the first solid indicator that the input was being parsed by a server-side template engine.


## Get Umanhonlen Gabriel’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


To be sure, I tried another:


```
{{8*8}}
```


Encoded as:


```
/search/%7B%7B8%2A8%7D%7D
```


The result?

>

***Results found for: 64***


Confirmed — the server is evaluating these expressions. That’s a classic **SSTI vulnerability**.

---

*Originally published on [Medium](https://infosecwriteups.com/how-i-found-ssti-in-a-search-bar-6fede0d3263c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
