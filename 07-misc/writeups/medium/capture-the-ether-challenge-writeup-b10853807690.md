# :game_die: Capture the Ether - Challenge Writeup

> **Original Source:** [Capture the Ether - Challenge Writeup](https://infosecwriteups.com/capture-the-ether-challenge-writeup-b10853807690)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Capture the Ether — Challenge Writeup


I started concentrating in smart contract security and it is really interesting.


[CaptureTheEther](https://capturetheether.com/)is the game of Ethereum smart contract security. It has interesting challenges. I solved some and made writeup. I will update this writeup as I solve more challenges in it.


I started with warmup challenges, those are straight forward and easy. I will explain the Lotteries section challenges.


- Guess the number:


They gave us a smart contract and the contract address for it. We have to guess the number.


Going through the smart contract I understand the number is 42 which we have to guess to pass the challenge.


```
pragma solidity ^0.4.21;

contract GuessTheNumberChallenge {
uint8 answer = 42;

function GuessTheNumberChallenge() public payable {
require(msg.value == 1 ether);
}

function isComplete() public view returns (bool) {
return address(this).balance == 0;
}

function guess(uint8 n) public payable {
require(msg.value == 1 ether);

if (n == answer) {
msg.sender.transfer(2 ether);
}
}
}
```


Guess function takes a number as a input and it requires 1 ether to make the transaction.

---

*Originally published on [Medium](https://infosecwriteups.com/capture-the-ether-challenge-writeup-b10853807690). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
