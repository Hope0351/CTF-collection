# :globe_with_meridians: Insecure Deserialization: It’s super hard! Or is it?

> **Original Source:** [Insecure Deserialization: It’s super hard! Or is it?](https://infosecwriteups.com/insecure-deserialization-its-super-hard-or-is-it-94d89e2847)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Insecure Deserialization: It’s super hard! Or is it?


## Introduction


Insecure deserialisation is often seen as a very hard vulnerability type but it doesn’t have to be. It does require decent knowledge of the programming languages in question but it can also occur very trivially if you have some knowledge of the programming languages.


In this module we will be looking at PHP and Ruby deserialisation processes by practical examples on the portswigger labs. This will allow us to better understand the concept.


Java serialization and deserialisation use binary formats which are harder to read and out of the scope of this document.

## Serialization


If we want to learn about deserialisation processes we first need to learn about what serialization is. When we talk about serialization, we are talking about the processing complex structures such as objects (For example a person with an age,sex and name) into a much flatter format so that it can be sent and received in a sequential stream of bytes. This allows us to write complex data structures to memory, files or databases and also to send that data over the network to different API’s.


When we serilalise data, we save it’s attributes and their values, this is really important to remember. Such as a female person of 16 years of age with the name “Sophie Kent” will get turned into something like {female|16|Sophie|kent}

---

*Originally published on [Medium](https://infosecwriteups.com/insecure-deserialization-its-super-hard-or-is-it-94d89e2847). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
