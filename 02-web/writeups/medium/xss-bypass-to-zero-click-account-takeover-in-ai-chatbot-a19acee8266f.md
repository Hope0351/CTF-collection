# :globe_with_meridians: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/xss-bypass-to-zero-click-account-takeover-in-ai-chatbot-a19acee8266f)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# XSS Bypass to Zero Click Account Takeover in AI Chatbot


*Photo by [Emiliano Vittoriosi](https://unsplash.com/@emilianovittoriosi?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*


Hi everyone, in this article, I’ll walk through a recent penetration test I conducted against a custom-built AI chatbot. As usual, we’ll cover:


- The application overview

- The high-level architecture

- The vulnerability

- The exploit


This assessment was conducted as a black-box test, meaning no source code access, no architectural documentation, and no internal visibility — only what an external attacker would see.

## Application Overview


Let’s call the company **A.Corp**.


Instead of integrating a third-party chatbot, A.Corp built their own AI assistant from scratch:


- The model was trained in-house.

- The user interface was custom-built.

- The guardrails and safety controls were implemented internally.

## **Overview**


Riding on the AI wave, this company, had come up with an AI chatbot. Unlike the ones in the market, the had created one for themselves, which means —


- It was an in-house trained model.

- They had created the UI themselves

- The guardrails were also created by their team

---

*Originally published on [Medium](https://infosecwriteups.com/xss-bypass-to-zero-click-account-takeover-in-ai-chatbot-a19acee8266f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
