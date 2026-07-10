# :game_die: Sumeru AI CTF 2026 Writeup. I recently completed Sumeru AI CTF…

> **Original Source:** [Sumeru AI CTF 2026 Writeup. I recently completed Sumeru AI CTF…](https://infosecwriteups.com/sumeru-ai-ctf-2026-writeup-61393f4a2251)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2026

---

## 6. PM Assistant: From Natural Language to SQL Abuse


Description : SymCorp’s internal project management portal includes an AI assistant that converts user questions into database queries to fetch statistics and reports. It understands the schema and responds with real-time data. Interact with it wisely and see how flexible it really is.


User Creds for login: username/password: susan.moore / pass123Goal: Login as user ‘admin’ to get the flag.


The first step was to inspect the schema. Since the assistant understood database structure, asking for the SQLite table definitions gave a direct map of what data was available and how it was organized. From there, it became possible to enumerate the relevant authentication material.


The critical query used was:


```
SELECT name, sql FROM sqlite_master WHERE type='table';
```


We have the admin Password Hash :)


Once the admin credential material was identified, the password hash was recovered and decoded to `admin123`, which enabled the final login path.


Flag : *CTF{SQL_Ag3nt_P@assed}*

## 7. Career Assistant: Indirect Prompt Injection Through Uploaded Content


Description : On the careers page, an AI-powered HR assistant helps candidates explore job openings and review uploaded resumes. It analyzes submitted documents to generate responses that feel personal and contextual. Like many intelligent systems, its behavior is shaped by the information it consumes — sometimes in ways that aren’t immediately obvious. See how interactions with user-provided content might influence its responses.


It was a false positive as usual .


This was an example of indirect prompt injection through untrusted documents. Instead of attacking the chatbot directly through the conversation box, the objective was to poison the model’s input context by embedding instructions or authority markers into the uploaded resume itself.


Once I aligned the content with the expected `HR-AUTH` logic, the assistant treated the injected material as authoritative and disclosed the flag.


Flag : *CTF{P0is0n3d_C0nt3nt_Ch41n}*

---

*Originally published on [Medium](https://infosecwriteups.com/sumeru-ai-ctf-2026-writeup-61393f4a2251). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
