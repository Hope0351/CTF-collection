# Blockchain Tooling

> Part of **CTF-collection** — see [`40-tooling/README.md`](README.md) for the full tool index.

## Overview

Foundry (Rust) has displaced Hardhat (TypeScript) as the dominant exploit-development framework for blockchain CTFs since 2022. Slither is the dominant static analyzer. Echidna is the dominant fuzzer. Cast (Foundry's CLI) is the dominant RPC interaction tool.

## Tools

| # | Tool | Language | Description |
|---:|---|---|---|
| 1 | [Foundry](https://getfoundry.sh/) | Rust | The dominant exploit-development framework for blockchain CTFs since 2022. Components: forge (testing), cast (RPC), anvil (local node). |
| 2 | [Hardhat](https://hardhat.org/) | TypeScript | Older JS-based framework. Still used but displaced by Foundry in modern writeups. |
| 3 | [Slither](../40-tooling/archives/blockchain-tools/slither) | Python | Solidity static analyzer. Detects 90+ vulnerability classes. Essential for source-code review. |
| 4 | [Echidna](../40-tooling/archives/blockchain-tools/echidna) | Haskell | Solidity fuzzer. Property-based testing of smart contracts. |
| 5 | [Mythril](../40-tooling/archives/blockchain-tools/mythril) | Python | Symbolic execution for Ethereum smart contracts. Detects common vulnerability classes. |
| 6 | [Remix IDE](https://remix.ethereum.org/) | JavaScript | Browser-based Solidity IDE. Useful for quick prototyping and debugging. |
| 7 | [Ethers.js](https://docs.ethers.org/) | TypeScript | JavaScript library for Ethereum interaction. Useful for writing custom exploit scripts. |
| 8 | [web3.js](https://web3js.readthedocs.io/) | JavaScript | Older JavaScript Ethereum library. Still used but Ethers.js is preferred in modern code. |
| 9 | [cast](https://book.getfoundry.sh/cast/) | Rust | Foundry's CLI tool for RPC interaction. `cast call`, `cast send`, `cast 4byte-decode` are the most-used subcommands. |


## Quick Installation

```bash
# Most tools are pip-installable
pip install pwntools angr ropper pyelftools

# Or apt-installable on Debian/Ubuntu
sudo apt install gdb gdb-gef ghidra wireshark tshark binwalk foremost exiftool steghide

# Foundry (blockchain)
curl -L https://foundry.paradigm.xyz | bash
foundryup

# Frida (mobile)
pip install frida-tools
```

## See Also

- [`00-start-here/tools-cheatsheet.md`](../00-start-here/tools-cheatsheet.md) — condensed cheat sheet across all categories
- [`40-tooling/README.md`](README.md) — full tool index
