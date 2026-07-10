# :game_die: Flare-On 12 Challenge 1: “Drill Baby Drill” — Detailed Writeup

> **Original Source:** [Flare-On 12 Challenge 1: “Drill Baby Drill” — Detailed Writeup](https://infosecwriteups.com/flare-on-12-challenge-1-drill-baby-drill-detailed-writeup-e49a50295f1e)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Flare-On 12 Challenge 1: “Drill Baby Drill” — Detailed Writeup


## Introduction


“Drill Baby Drill” is a Python-based pygame challenge from Flare-On 12 that initially appears to be a simple drilling game but contains a clever cryptographic puzzle beneath its surface. This writeup details the manual approach to solving this challenge through game analysis and strategic gameplay.

## Initial Analysis


Upon launching the game, we’re presented with a retro-style drilling game where we control “Drill Baby” — a character that can move horizontally and extend a drill vertically to search for lost bears while avoiding boulders. The game provides simple instructions:


- Use arrow keys to move left/right

- Use up/down to raise or lower the drill

- Don’t drill into rocks

- Win the game


Let’s examine the provided source code to understand the game mechanics.


---

*Originally published on [Medium](https://infosecwriteups.com/flare-on-12-challenge-1-drill-baby-drill-detailed-writeup-e49a50295f1e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
