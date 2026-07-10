# :locked_with_key: The Family Laptop Trap Unmasking A Go Based Crypto Heist 604Deb35776C

---

## Phase 1: Static Analysis — The Illusion of Product

To understand why this campaign is successful, we must look at the archive’s internal structure. This isn’t a single, suspicious file; it’s a carefully crafted “product” designed to build trust through visual and structural authenticity.

## Visual Authenticity: Assets and UI

Upon extraction, the user sees a directory filled with subfolders that mimic a real modding environment:

- `Assets/`: Contains `.png` and `.ico` files—actual UI elements like button designs and icons for the "cheat menu."

- `Config/`: Contains `.ini` and `.json` files that look like legitimate settings for a game injector.

By providing these “cosmetic” files, the attacker makes the user feel they have downloaded a complex, finished piece of software.

## Technical Masquerading: The Imposter Launcher

The launcher, `Boostrtrappper.exe`, is a textbook case of T1036: Masquerading.

- The Discrepancy: While named `Boostrtrappper.exe`, its internal metadata reveals an Original Filename of `identify_helper.exe`.

- The Origin: `identify_helper.exe` is a legitimate, signed Microsoft C++ component. The attacker has renamed it to hide in plain sight.

- Entropy Analysis: A standard “helper” utility usually has moderate entropy. This file, however, hits an Entropy of 6.5 (81%). This discrepancy confirms that while the wrapper is C-based, it carries a packed malicious overlay.

PeStudio analysis showing the ‘identify_helper.exe’ original name and the high entropy indicating hidden, packed resources.

## The Brain: `msedge_elf.dll` and the Obfuscation Wall

The payload is a massive Go-lang binary. The use of Go-lang is a deliberate choice to complicate reverse engineering due to static linking and the massive size of the binary.

## The “Go” Factor: Why Modern Malware Loves it

The choice of Go-lang for the payload is not accidental. Unlike C++ or C#, Go-lang binaries are statically linked by default. This means that the entire Go runtime and all necessary libraries are bundled into a single, massive executable (usually 5MB+).

For an analyst, this creates a “needle in a haystack” problem. A simple “Hello World” in Go contains thousands of functions. Threat actors exploit this by stripping symbol tables, making it incredibly difficult to distinguish between legitimate Go runtime functions and the malicious logic buried within. Furthermore, the way Go handles memory and string offsets differs significantly from traditional Windows PE files, often breaking older automated deobfuscators.

During static analysis, this file presented a significant challenge:

- High Entropy: Near maximum, indicating heavy packing.

- Luraph Obfuscation: The code encrypts the string table and mangles the control flow.

- The Result: Standard static string extraction failed. The binary refused to “talk.”

However, when the code refuses to speak statically, we force it to act dynamically. Where PeStudio saw encrypted gibberish, our behavioral logs captured the malware resolving these hidden strings in real-time. By capturing the access to `\\\\Local Extension Settings\\\\`, we confirmed the malware's intent to harvest LevelDB databases and Login Data.

Procmon captures the process resolving encrypted paths to ‘Local Extension Settings’. Access to these folders confirms the target is the wallet’s LevelDB database.

---
