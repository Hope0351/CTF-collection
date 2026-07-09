# Web Tooling

> Part of **CTF-collection** — see [`40-tooling/README.md`](README.md) for the full tool index.

## Overview

Burp Suite is the dominant web-proxy tool. sqlmap automates SQL injection. ffuf and gobuster handle directory and vhost enumeration. semgrep and nuclei handle code scanning and templated vulnerability detection.

## Tools

| # | Tool | Language | Description |
|---:|---|---|---|
| 1 | [Burp Suite](https://portswigger.net/burp) | Java | The dominant web proxy tool. Community edition is free; Professional adds scanner and intruder features. Repeater is the most-used feature for CTF. |
| 2 | [sqlmap](https://sqlmap.org/) | Python | Automates SQL injection detection and exploitation. Handles UNION, blind, time-based, error-based. Can dump databases, write files, execute OS commands. |
| 3 | [ffuf (local mirror)](../repos/ffuf/ffuf) | Go | Fast web fuzzer. Used for directory, vhost, and parameter enumeration. Filters by response size, status, words. |
| 4 | [gobuster (local mirror)](../repos/OJ/gobuster) | Go | Alternative directory buster. Simpler than ffuf; good for quick enumeration. |
| 5 | [nuclei (local mirror)](../repos/projectdiscovery/nuclei) | Go | Template-based vulnerability scanner. 5000+ community templates for known CVEs and misconfigurations. |
| 6 | [semgrep](https://semgrep.dev/) | OCaml/Python | Static analysis tool with custom rule support. Useful for source-code review challenges. |
| 7 | [WSL2 + Kali](https://www.kali.org/docs/wsl/) | Linux | Kali Linux on WSL2 — the easiest way to get a CTF-ready environment on Windows. |
| 8 | [Postman](https://www.postman.com/) | Electron | API testing tool. Useful for non-HTTP APIs (gRPC, GraphQL, WebSocket). |
| 9 | [CyberChef](https://gchq.github.io/CyberChef/) | JavaScript | Encoding/decoding Swiss Army knife. Useful for JWT, base64 variants, encoding chains. |


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
