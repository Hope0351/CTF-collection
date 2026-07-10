# :link: Playground TCP1P CTF : Blockchain Challenge Writeup

> **Original Source:** [Playground TCP1P CTF : Blockchain Challenge Writeup](https://infosecwriteups.com/tcp1p-ctf-blockchain-callenge-writeup-94b7ebe1464c)
> **Platform:** infosecwriteups.com | **Category:** `BLOCKCHAIN`

---

# Playground TCP1P CTF : Blockchain Challenge Writeup


[TCP1P](https://tcp1p.team/) is an Indonesian CTF team actively engaging in competitive cybersecurity events on ctftime.


In the rapidly evolving world of cybersecurity, Capture The Flag (CTF) challenges have become an invaluable tool for both learning and demonstrating skills. These competitions simulate real-world scenarios, testing participants’ abilities to solve complex problems and think critically under pressure. Among the myriad of challenges, those focused on blockchain technology stand out for their intricacy and relevance in today’s digital landscape.


Blockchain, the backbone of cryptocurrencies and a promising technology for secure, decentralized transactions, presents unique challenges and opportunities for cybersecurity enthusiasts. In this write-up, I will take you through my journey of tackling a blockchain-focused CTF challenge, highlighting the key steps, strategies, and tools I used to navigate this intricate puzzle.


Whether you’re a seasoned cybersecurity professional or an aspiring enthusiast, this write-up aims to provide valuable insights into blockchain security, demystify the challenge-solving process, and hopefully inspire you to dive deeper into the fascinating world of blockchain technology.


Let’s dive in and unravel the mysteries of this CTF blockchain challenge together!


*Blockchain Challenges List*

## Transact


```
// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.0;

contract Setup {
bool private solved;

constructor() payable {
}
function solve() public {
solved = true;
}

function isSolved() external view returns (bool) {
return solved;
}
}
```


based on this contract, we can easily spot that we just neet to call the function solve() to get the flag.


```
cast call "0x5b2bE141fa1B152B6C8C5fa314fC00B767aeF9A7" "solve()" --rpc-url "http://172.188.90.64:5301/c1b80be9-cc94-4d18-8478-66b36b78e599" --private-key "0xb7429735d868d4c670de349846920972d9177078c181b0dac31f1db1c776f5d8"
```

---

*Originally published on [Medium](https://infosecwriteups.com/tcp1p-ctf-blockchain-callenge-writeup-94b7ebe1464c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of blockchain CTF writeups.*
