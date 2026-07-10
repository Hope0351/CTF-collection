# :game_die: SecLeaf Q2 CTF 2026 Writeups. From recon to flag capture: a…

---

### Challenge-5: double-trouble (300 points)

Again given a file named “encrypted.txt”. I conformed that, it would one of the *cyberchef solvable* challenge.

>

We intercepted a suspicious encoded transmission during routine monitoring.

Analysts believe the message was processed through multiple transformation layers before being transmitted. Can you recover the original message?

```
526e4a7757584a756333737759544e66655452734d325666616a526d5957
64664d3245776148523166513d3d0a
```

It looks like Hex format. So i decoded it.

```
RnJwWXJuc3swYTNfeTRsM2VfajRmYWdfM2EwaHR1fQ==
```

Now it looks like base64 format. Again decoded it.

```
FrpYrns{0a3_y4l3e_j4fag_3a0htu}
```

Now it seems to be in order like ABC{xyz}. It might be rotation of characters, where there is popular method called ROT13, ROT47. I used ROT13 to decode it.

```
SecLeaf{0n3_l4y3r_w4snt_3n0ugh}
```

---
