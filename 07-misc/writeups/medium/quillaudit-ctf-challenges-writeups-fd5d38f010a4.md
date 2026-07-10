# :game_die: QuillAudit CTF challenges - Writeup

---

# QuillAudit CTF challenges — Writeup

My solutions to all retired challenges can be found here.

## 1. Confidential Hash

### Challenge Description:

This contract checks whether the keccak256 hash of aliceHash and bobHash is same to inputted hash. The given task is to find the keccak256 hash of aliceHash and bobHash, which is to get true from `checkthehash `function. `hash` function can calculate the keccak256 hash from two inputted `bytes32` variables.

### Vulnerability Description:

Confidential contract is initialising the private keys and hashes as private varibles in contract itself which is the vulnerability here because these variables are placed in storage with slot numbers. Anyone can just count the slot in which the private key is located and call it. In this case the slots are 4(aliceHash) and 9(bobHash).

### Attack steps:

1. Setup the contract and attacker
2. Load the hashes of alice and bob from the respective slots in storage using `load` function.
3. Calculate the keccak256 hash of aliceHash and bobHash now using `hash` function of the contract.
4. Verify the calculated hash using `checkthehash` function of the contract which will return `true`.

---
