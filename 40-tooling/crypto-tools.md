# Crypto Tooling

> Part of **CTF-collection** — see [`40-tooling/README.md`](README.md) for the full tool index.

## Overview

SageMath is the dominant computational algebra system for crypto CTFs — it provides Python syntax with full symbolic algebra, number theory, and cryptography primitives. For specific attacks, RsaCtfTool (RSA attacks), yafu (factorization), and PARI/GP are common.

## Tools

| # | Tool | Language | Description |
|---:|---|---|---|
| 1 | [SageMath](https://www.sagemath.org/) | Python/Cython | The dominant computational algebra system for crypto CTFs. Provides Python syntax with full symbolic algebra, number theory, and cryptography primitives. Install via `sage` package or Docker. |
| 2 | [RsaCtfTool (local mirror)](../repos/RsaCtfTool/RsaCtfTool) | Python | Automates common RSA attacks: Wiener, Hastad, common modulus, Fermat, etc. Good for quick wins. |
| 3 | [yafu](https://sourceforge.net/projects/yafu/) | C | Advanced factorization tool. Uses SIQS and GNFS. Faster than SageMath's `factor()` for hard semiprimes. |
| 4 | [PARI/GP](https://pari.math.u-bordeaux.fr/) | C | Number theory computation system. Older than SageMath but faster for some operations. |
| 5 | [pycryptodome](https://www.pycryptodome.org/) | Python | Python crypto library. Standard for implementing AES, RSA, ECC, hashes in exploit scripts. |
| 6 | [Hashcat](https://hashcat.net/hashcat/) | C | GPU-accelerated hash cracker. Supports 300+ hash types. |
| 7 | [John the Ripper](https://www.openwall.com/john/) | C | CPU hash cracker. More flexible than Hashcat for unusual hash formats. |
| 8 | [CyberChef](https://gchq.github.io/CyberChef/) | JavaScript | Web-based 'Swiss Army knife' for encoding/decoding operations. Indispensable for rapid prototyping. |


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
