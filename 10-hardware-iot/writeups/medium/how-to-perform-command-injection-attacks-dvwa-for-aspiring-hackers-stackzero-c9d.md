# :electric_plug: How To Perform Command Injection Attacks (DVWA) For Aspiring Hackers! - StackZero

---

# How To Perform Command Injection Attacks (DVWA) For Aspiring Hackers! — StackZero

## Introduction

Hi reader! In this write-up, I want to show you how to attack [DVWA](https://github.com/digininja/DVWA) by using command injection attack.

Command injection is one of the easiest attacks to understand, however, there are not so many online tutorials covering that subject from a practical point of view.
As usual, I want to do my best to explain that in order to make you able to hunt this type of bug without any problem.

So let’s make our hands dirty by running our Kali VM and the [DVWA](https://github.com/digininja/DVWA) machine on [TryHackMe](https://tryhackme.com/room/dvwa).

If you don’t know how to run [DVWA](https://github.com/digininja/DVWA), you can take a look at the dedicated paragraph in this article.

I have already shown how to turn the vulnerability into an arbitrary file upload and then a reverse shell, so in this article, I will just focus on how to bypass the filters.
The goal here will be to show the content of the */etc/passwd* file.

## Cheat Sheet for Command Injection

Usually, an application that is vulnerable to OS Command Injection attack, takes an input either without sanitization or with badly designed filters. What we want to do in order to run our exploit in [DVWA](https://github.com/digininja/DVWA) is to understand how we…

---
