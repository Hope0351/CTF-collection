# :game_die: 4. Prototype Pollution: One JSON Key That Turns You into Admin

> **Original Source:** [4. Prototype Pollution: One JSON Key That Turns You into Admin](https://infosecwriteups.com/4-prototype-pollution-one-json-key-that-turns-you-into-admin-1a4d6ec4128c)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# 4. Prototype Pollution: One JSON Key That Turns You into Admin


If you’ve ever seen a payload like this and ignored it:-


```
{"__proto__":{"isAdmin":true}}
```


### You probably missed a real P1.


>

Prototype Pollution isn’t about breaking authentication directly.
It’s about poisoning the logic the application trusts.


And when modern JavaScript apps trust polluted objects — things fall apart fast.


*Created by Gemini*

## 🧠 What Is Prototype Pollution (No Theory, Just Reality)


Prototype Pollution happens when:


- A JavaScript application merges user-controlled objects

- Without filtering dangerous keys

- Allowing attackers to modify the prototype of objects


In simple terms:

>

*You don’t change *your* object
You change the default behavior of all objects*


## 🎯 Why This Bug Is High Impact

---

*Originally published on [Medium](https://infosecwriteups.com/4-prototype-pollution-one-json-key-that-turns-you-into-admin-1a4d6ec4128c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
