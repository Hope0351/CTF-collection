# :globe_with_meridians: “Day 26: The WebSocket Hijack — How I Eavesdropped on Every Customer Support Chat”

> **Original Source:** [“Day 26: The WebSocket Hijack — How I Eavesdropped on Every Customer Support Chat”](https://infosecwriteups.com/day-26-the-websocket-hijack-how-i-eavesdropped-on-every-customer-support-chat-de5ddc819ad2)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# “Day 26: The WebSocket Hijack — How I Eavesdropped on Every Customer Support Chat”


## Exploiting the Trusting Handshake of Real-Time Communication


The target was a major bank’s customer support portal. They had a sleek, modern live chat feature powered by WebSockets. It felt responsive and secure. But during testing, I noticed the initial WebSocket connection didn’t use a typical Authorization header. My curiosity turned to shock when I realized the authentication mechanism was a simple, predictable token passed in the URL. By manipulating this token, I didn’t just hijack one chat — I gained the ability to connect to *any* active support session in real-time, listening in and even injecting messages. This breach of confidentiality led to a $6000 bounty.


[free link](https://amannsharmaa.medium.com/day-26-the-websocket-hijack-how-i-eavesdropped-on-every-customer-support-chat-de5ddc819ad2?sk=54034a8721ebc56fb0d123d4725ef88c)


## Why WebSockets Are a Unique Attack Surface


WebSockets provide full-duplex, persistent communication channels over a single TCP connection. This is great for real-time apps like chat, notifications, and trading platforms. But this persistence creates new risks:


- Custom Protocols: They often implement bespoke authentication and authorization logic, bypassing standard HTTP security controls.

- Statefulness: The connection is stateful. If you can…

---

*Originally published on [Medium](https://infosecwriteups.com/day-26-the-websocket-hijack-how-i-eavesdropped-on-every-customer-support-chat-de5ddc819ad2). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
