# :globe_with_meridians: JWTweak v2.1: A Guided, Offline Toolkit for Modern JWT Attacks

---

# JWTweak v2.1: A Guided, Offline Toolkit for Modern JWT Attacks

*Paste a token, get a full attack plan — then execute it, entirely offline.*

JSON Web Tokens sit at the heart of modern authentication. The catch: the token lives in the user’s hands, not the server’s. One weak validation check on the backend, and an attacker can hand themselves an admin session.

That’s the exact gap JWTweak was built to probe.

It started life as a small script for flipping a token’s algorithm and re-signing it — enough to go hunting for classic JWT Algorithm Confusion bugs. Version 2.1 is a full rewrite: a guided, menu-driven toolkit. You paste a token, it decodes and risk-scores it, tells you which attacks are worth trying, and walks you through each one step by step. No flags to memorize, no internet connection required.

In this post, I’ll walk through what’s new in the tool, then break into a deliberately vulnerable app using two live proof-of-concept attacks.

## Requirements

```
# Python 3.8+ (tested on Kali and macOS)
pip3 install pyjwt cryptography rich
```

`pyjwt` and `cryptography` are required. `rich` is optional — it powers the enhanced terminal UI, but the tool degrades gracefully to plain text without it.

## What’s New in v2.1

---
