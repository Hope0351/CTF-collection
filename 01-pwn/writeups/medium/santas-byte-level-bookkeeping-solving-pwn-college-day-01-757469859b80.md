# :skull: Santa’s Byte-Level Bookkeeping: Solving pwn.college Day 01

> **Original Source:** [Santa’s Byte-Level Bookkeeping: Solving pwn.college Day 01](https://infosecwriteups.com/santas-byte-level-bookkeeping-solving-pwn-college-day-01-757469859b80)
> **Platform:** infosecwriteups.com | **Category:** `PWN`

---

# Santa’s Byte-Level Bookkeeping: Solving pwn.college Day 01


The Synopsis of the Challenge


Begin by establishing the context. Indicate that the challenge (from pwn.college) features a binary that verifies an input of 1024 bytes. The account states:


“it’s merely static analysis: even a basic objdump | grep naughty is quite effective.”


Preliminary Assessment (The “Reason”)


Describe what occurs when you observe the assembly. You may utilize a portion of the objdump output you shared previously.


The program employs a syscall to read 0x400 (1024) bytes.


The Obfuscation: Rather than merely verifying a password, the program executes countless addb (add byte) and subb (subtract byte) operations on separate bytes of your input.


The Objective: Following these actions, it checks every byte against a predetermined hardcoded value using cmpb

## 1. The Investigation: Peeking Under the Hood


When you run the binary, it expects an input of exactly 1024 bytes ($0x400$). To understand how it processes this input, I dumped the assembly code using `objdump`:


Bash


```
objdump -S /challenge/check-list > checklist.S
```


Looking at the output, the program’s logic becomes clear. It reads your input and then subjects it to thousands of tiny mathematical transformations.

## The Assembly Pattern


The code follows a very specific pattern:


- The Math Phase: Thousands of `addb` (add byte) and `subb` (subtract byte) instructions applied to specific offsets in the input buffer.

- The Comparison Phase: A long series of `cmpb` (compare byte) instructions that check if the result of the math matches a hardcoded "target" value.

## 2. The Strategy: Reversing the Math


The binary is essentially a massive system of simple equations. For any given byte in our input ($x$), the program does something like this:


$$x + \text{change}_1 — \text{change}_2 + \text{change}_3 = \text{Target}$$


## Get Eeshan Agrawal’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


To find our original input ($x$), we just need to work backward:


$$x = \text{Target} — (\text{Total Changes})$$


Because we are dealing with `byte` operations, all calculations are performed modulo 256. Doing this by hand for 1024 bytes is impossible, so I wrote a Python script to automate the "un-obfuscation."

## 3. The Solution Script


The following script parses the `checklist.S` file we generated. It extracts the addition/subtraction values and the final comparison values for every single byte offset.


Python


```
# flag.py
values = [0] * 0x400 # Tracks total changes (add/sub)
cmp_targets = [0] * 0x400 # Tracks the final expected values
```


```
for line in open("checklist.S"):
parts = line.split()
if len(parts) == 0 or "rbp" not in line:
continue

# Extract the instruction address
addr = int(parts[0][:-1], 16)

# Logic for the "Math Phase" (add/sub instructions)
if 0x401022 <= addr <= 0xAA0DA5:
value = int(parts[-1].split(",")[0].removeprefix("$"), 16)
offset = 0x400 + int(parts[-1].split(",")[1].removesuffix("(%rbp)"), 16)

if parts[-2] == "addb":
values[offset] += value
elif parts[-2] == "subb":
values[offset] -= value

# Logic for the "Comparison Phase" (cmpb instructions)
elif 0xAA0DAC <= addr <= 0xAA4022 and "cmpb" in line:
value = int(parts[-1].split(",")[0].removeprefix("$"), 16)
offset = 0x400 + int(parts[-1].split(",")[1].removesuffix("(%rbp)"), 16)
cmp_targets[offset] = value# Final calculation: Original Input = (Target - TotalChanges) % 256
final_payload = [0] * 0x400
for i in range(0x400):
final_payload[i] = (cmp_targets[i] - values[i]) % 256# Save the bytes to a file
with open("data.bin", "wb") as f:
f.write(bytes(final_payload))print("Payload generated successfully!")
```


## 4. Capturing the Flag


Once the script generated `data.bin`, all that was left was to pipe that data into the challenge binary.


Bash


```
python3 flag.py
/challenge/check-list < data.bin
```


The result:

>

*✨ Correct: you checked it twice, and it shows! *`*pwn.college{Redacted}*`


## Conclusion


This challenge is a perfect example of how automated static analysis can bypass obfuscation. While the program tried to hide its logic behind thousands of lines of assembly, the underlying math was simple. By writing a parser, we turned a daunting manual task into a 5-second script execution.


Happy Hacking!


Github: [https://github.com/Die-Another-Day](https://github.com/Die-Another-Day)
Linkedin: [https://www.linkedin.com/in/eeshangarg888](https://www.linkedin.com/in/eeshangarg888)

---

*Originally published on [Medium](https://infosecwriteups.com/santas-byte-level-bookkeeping-solving-pwn-college-day-01-757469859b80). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of pwn CTF writeups.*
