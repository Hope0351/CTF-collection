# :locked_with_key: Fake Crypto Game Job Offer Phishing

> **Original Source:** [Fake Crypto Game Job Offer Phishing](https://infosecwriteups.com/fake-crypto-game-job-offer-phishing-27642662fe13)
> **Platform:** infosecwriteups.com | **Category:** `CRYPTO`

---

# Fake Crypto Game Job Offer Phishing


Hi!


I am morimolymoly.


I accidentally got a DM from suspicous ppl.


I feeled like it is a fake job offer to me.


So I pretend to having an interest to this project and told my discord account and looked at it deeply.


Fake website is below.


It looks pretty nice!


It has also GitBook whitepaper.


Discord account is here.


He created Discord account at 21th March 2023.


It is also suspicous because seeing Roadmap, it says in Q4 2021 — Q2 2022, discord server has been launched.


I did HUMINT and got a beta key to download malware.


It is a obfuscated with SmartAssembly.


This binary is so big, 1GB or some.


## Get morimolymoly’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Because this binary is 0x00 filled.


Flare Royal NFT’s Malware fetches encrypted payload from resource and decrypts like this. It is so cheap.


Decryption code is below.


```
p0 = "kgggdlbmgIpdl"

f = open("kgggdlbmgIpdl", "rb")
p1 = bytearray(f.read())
f.close()

num = 0
bytes1 = bytearray(p0.encode('utf-8'))
num2 = 0

while num2 <= (len(p1) - 1) * (num + 1):
p1[num2 % len(p1)] = ((p1[num2 % len(p1)] ^ bytes1[num2 % len(bytes1)]) - (p1[(num2 + 9 - 10 + 2) % len(p1)] + 255 + 1)) % 256
num2 += 1

p1 = p1[:-1]

f2 = open("test", "wb")
f2.write(p1)
f2.close()
```


Decrypted payload is below.


It seems RedLine.


C2 is below.


## IoCs


deobfus one: 3f56b955edc65b0d5148120ebc2ea0c6528cbee648ed2c2af4ea75102f69e908


original binary: 7e4f4e82aa3986d6627676bdf5927de0564b2c1a878f66d7d68d7667a9285bb4


Payload: f08322b5c4567749aa03a20f37ffe664c7d19aef39199cad4d4ccfe2bb88ad1d


hxxps://flareroyalenft.com/


hxxps://flareroyale.gitbook.io/untitled/


DiscordID: HandsomE.nft#4006


Twitter: https://twitter.com/intent/user?user_id497945521

---

*Originally published on [Medium](https://infosecwriteups.com/fake-crypto-game-job-offer-phishing-27642662fe13). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
