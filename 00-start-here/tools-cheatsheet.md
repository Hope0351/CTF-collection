# 🛠 CTF Tools Cheat Sheet

A condensed reference of the tools and one-liners you'll need most often. For full tool pages, see [`40-tooling/`](../40-tooling/README.md).

## Environment setup

### Linux VM
- **Recommended:** Ubuntu 22.04 LTS in VirtualBox or VMware.
- **Alternative:** WSL2 on Windows 10/11 (works for most categories except some kernel pwn).

### Essential Python packages
```bash
pip install pwntools angr requests beautifulsoup4 ropper pyelftools
```

### Essential system tools
```bash
sudo apt install gdb gdb-gef ghidra wireshark tshark burpsuite sqlite3                  radare2 binwalk foremost volatilty exiftool steghide                  jq ripgrep fd-find
```

---

## Pwn

### pwntools basics
```python
from pwn import *
context.arch = 'amd64'  # or 'i386', 'arm', 'aarch64'

# Connect to a remote challenge
r = remote('challenge.host', 1337)

# Or start a local binary
r = process('./challenge_binary')

# Interact
r.sendline(b'payload here')
r.recvuntil(b'> ')
r.interactive()  # for shell access
```

### Find ROP gadgets
```bash
ROPgadget --binary ./challenge --ropchain
ropper --file ./challenge --search "pop rdi"
```

### Find one_gadgets (libc)
```bash
one_gadget ./libc.so.6
```

### gdb-gef essentials
```
gdb ./challenge
gef➤  checksec        # check security mitigations
gef➤  pattern create 200
gef➤  r < input.txt   # run with input
gef➤  pattern offset $rsp
gef➤  vmmap           # memory map
gef➤  heap chunks     # view heap
gef➤  telescope $rsp  # examine stack
```

### Common pwn checks
```bash
checksec --file=./challenge    # PIE, NX, canary, RELRO
file ./challenge                # architecture, dynamically/statically linked
ldd ./challenge                 # libc version
```

---

## Reverse Engineering

### Ghidra quick start
1. Import binary → File > Import Program.
2. Auto-analyze (default options are fine).
3. Find `main` in the Symbol Tree.
4. Use the Decompiler window (Ctrl+E to edit function signature).
5. Right-click → "Rename Function" / "Retype Variable" as you figure out what things do.

### angr basics
```python
import angr
proj = angr.Project('./challenge', auto_load_libs=False)
state = proj.factory.entry_state()
simgr = proj.factory.simulation_manager(state)
simgr.explore(find=lambda s: b'flag' in s.posix.dumps(1))
print(simgr.found[0].posix.dumps(1))
```

### Strings & symbols
```bash
strings ./binary | grep -i flag
nm ./binary | grep ' T '
objdump -d ./binary | head -100
r2 -A ./binary    # radare2
```

---

## Web

### Burp Suite essentials
- Configure browser proxy to `127.0.0.1:8080`.
- Use **Repeater** to modify and resend requests.
- Use **Intruder** for brute-force / fuzzing.
- Install the **Param Miner** extension to find hidden parameters.

### Common one-liners
```bash
# SQLi test
sqlmap -u "https://target.com/page?id=1" --batch --dbs

# Directory fuzzing
ffuf -u https://target.com/FUZZ -w /usr/share/wordlists/dirb/common.txt

# Subdomain enumeration
ffuf -u https://FUZZ.target.com -w subdomains.txt -mc 200,301,302

# XSS test
curl "https://target.com/search?q=<script>alert(1)</script>"

# SSTI test (Jinja2)
curl "https://target.com/page?name={{7*7}}"
```

---

## Crypto

### SageMath essentials
```python
# In SageMath
from sage.all import *
n = 0x...  # RSA modulus
e = 65537
c = 0x...  # ciphertext

# Factor small n
factor(n)

# RSA decrypt (given p, q)
p, q = ...
phi = (p-1)*(q-1)
d = inverse_mod(e, phi)
m = power_mod(c, d, n)
print(bytes.fromhex(hex(m)[2:]))
```

### Common crypto checks
- RSA: small `e` with small message? → cube root attack.
- RSA: common modulus between two ciphertexts? → common modulus attack.
- RSA: `n` close to a perfect square? → Fermat factorization.
- AES ECB: repeating patterns in ciphertext? → ECB mode, block-wise analysis possible.

---

## Forensics

### File identification
```bash
file image_or_disk
binwalk image_or_disk        # find embedded files
foremost -i image -o output/ # carve files
exiftool photo.jpg           # metadata
```

### Steganography
```bash
steghide extract -sf image.jpg      # password-protected stego
zsteg image.png                      # PNG stego
stegsolve image.png                  # visual analysis (Java tool)
aperisolve.fr                        # online, multi-algorithm
```

### Memory forensics (Volatility)
```bash
volatility -f memory.dmp imageinfo          # identify OS/profile
volatility -f memory.dmp --profile=Win7SP1x64 pslist
volatility -f memory.dmp --profile=Win7SP1x64 hashdump
volatility -f memory.dmp --profile=Win7SP1x64 cmdscan
```

### Network forensics (Wireshark/tshark)
```bash
tshark -r capture.pcap -Y "http" -T fields -e http.request.uri
tshark -r capture.pcap -Y "tcp.stream eq 0" -z "follow,tcp,ascii,0"
tshark -r capture.pcap -Y "ftp" -T fields -e ftp.request.command -e ftp.request.arg
```

---

## Blockchain

### Foundry setup
```bash
forge init my-exploit
cd my-exploit
forge install openzeppelin/openzeppelin-contracts
```

### Foundry exploit test
```solidity
// test/Exploit.t.sol
pragma solidity ^0.8.0;
import "forge-std/Test.sol";
import "../src/Challenge.sol";

contract ExploitTest is Test {
    Challenge challenge;
    function setUp() public {
        challenge = new Challenge();
    }
    function testExploit() public {
        // Your exploit here
        assertTrue(challenge.isSolved());
    }
}
```

### Run
```bash
forge test -vvv
```

---

## Mobile

### APK reverse engineering
```bash
apktool d target.apk -o output_dir/
jadx-gui target.apk    # GUI decompiler
```

### Frida basics
```bash
# Hook a Java method
frida -U -l hook.js -f com.target.app --no-pause
```

```javascript
// hook.js
Java.perform(function() {
    var Target = Java.use('com.target.Class');
    Target.method.implementation = function(arg) {
        console.log('called with:', arg);
        return this.method(arg);
    };
});
```

---

## Network / Pcap

### Wireshark display filters (most-used)
```
http                     # all HTTP traffic
http.request.method==POST   # POST requests
http.host contains "target"
tcp.port==443
dns.qry.name contains "evil"
ftp.request.command==PASS
```

### Export objects from pcap
```
Wireshark → File → Export Objects → HTTP
```

---

## OSINT

### Quick-reference tools
- **Username search:** [whatsmyname.app](https://whatsmyname.app/)
- **Email breach check:** [haveibeenpwned.com](https://haveibeenpwned.com/)
- **Domain/IP:** [shodan.io](https://www.shodan.io/), [censys.io](https://search.censys.io/)
- **Reverse image search:** [tineye.com](https://tineye.com/), Google Images, Yandex
- **Geolocation:** [suncalc.org](https://www.suncalc.org/) (shadow analysis), Google Earth
- **Archived web:** [web.archive.org](https://web.archive.org/)

---

## Keeping current

- **Subreddits:** r/securityCTF, r/netsec, r/HowToHack
- **Discord:** LiveOverflow, John Hammond, IppSec
- **Twitter:** Follow `@ctftime`, `@Hacker0x01`, `@portswigger`
- **Newsletters:** PortSwigger weekly, HackerOne weekly

For full tool pages with deeper examples, see [`40-tooling/`](../40-tooling/README.md).
