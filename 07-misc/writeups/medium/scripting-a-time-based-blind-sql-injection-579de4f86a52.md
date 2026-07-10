# :game_die: Scripting a Time based blind SQL Injection

> **Original Source:** [Scripting a Time based blind SQL Injection](https://infosecwriteups.com/scripting-a-time-based-blind-sql-injection-579de4f86a52)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Scripting a Time based blind SQL Injection


*Understanding Time Based Blind Sql Injection*

## Background


In this article I wanted to touch upon a relatively *difficult *topic of Blind SQL Injections, as we soldier along the hacker terrain. I say it is “*difficult*” because it took me some time to get my head around some of the nuances that come with it. However, it is a sort of vulnerability that you are more likely to find in the SQL injection category than any *other *variation of it. So, it is important to understand it.


As always, PortSwigger provides ample resources to understand SQL injection and its various forms. However, one thing that you will not find in their content is *Scripting *the attack by using languages like *Python*. Strictly speaking that is not their intention or objective when they explain the concept. However, I thought it would be useful to showcase one of their amazing labs on blind SQL injection with Information Retrieval by *scripting *it with Python. This way folks can see the concept and also understand the process of scripting it.

## A look into blind SQL Injections

---

*Originally published on [Medium](https://infosecwriteups.com/scripting-a-time-based-blind-sql-injection-579de4f86a52). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
