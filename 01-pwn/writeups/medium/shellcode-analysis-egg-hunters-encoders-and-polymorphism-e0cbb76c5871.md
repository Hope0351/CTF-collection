# :skull: Shellcode Analysis: Egg Hunters, Encoders, and Polymorphism

---

# Shellcode Analysis: Egg Hunters, Encoders, and Polymorphism

## *Or, how to read malware’s secret love letters to your CPU.*

*Photo by [Patrick Martin](https://unsplash.com/@patrickmmartin?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

### Why Shellcode Even Exists

Think of shellcode as the hacker’s version of a portable camping stove — small, lightweight, and able to cook up something dangerous anywhere you drop it.

Originally, shellcode literally spawned a shell (like `/bin/sh`), but nowadays it can:

- Download payloads

- Steal passwords

- Disable antivirus

- Manipulate memory structures

It’s designed to run directly in memory, no fancy file needed.
And because defenders like us keep getting better, attackers have gotten creative with egg hunters, encoders, and polymorphic tricks.

### Step 1: The Usual Shellcode Workflow

Here’s the recipe:

- Get the shellcode into memory — exploit a vulnerability, spray it somewhere.

- Find it if you don’t know exactly where — that’s where egg hunters come in.

- Hide it from scanners — that’s where encoders and polymorphism shine.

- Run it — and then… bad things happen.

---
