# :globe_with_meridians: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/learning-more-about-yaml-deserialization-9c08093b4a3d)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Learning More About YAML Deserialization


**Introduction**


Deserialization attacks are quite popular when it comes to programming languages such as Java, Python, and Ruby. These flaws manifest themselves when a stream of data is directly deserialized without any checks being performed first, and they might result in the execution of remote code.


In this blog post, we’ll be learning about yet another deserialization technique but in the context of YAML.


Before we dive into the basics of YAML Deserialization, let’s throw some light into serialization and de-serialization.


**Serialization:**


*[Source](https://portswigger.net/web-security/deserialization)*


Let’s consider that you are playing an online game. The character that you own will have a number of attributes. For example, username, avatar, clothes, rank, weapons, etc. How do you think these attributes are transferred/communicated and even stored on the server?


The answer is serialization.


What is Serialization? Conversion of the object into a byte stream or a flat structure is called serialization.


This “byte stream” is also referred to as a flatter version of the object. This can now be…

---

*Originally published on [Medium](https://infosecwriteups.com/learning-more-about-yaml-deserialization-9c08093b4a3d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
