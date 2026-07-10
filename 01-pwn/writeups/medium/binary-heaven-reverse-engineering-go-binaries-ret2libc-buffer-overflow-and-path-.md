# :skull: Binary Heaven - Reverse Engineering Go Binaries, ret2libc Buffer Overflow, and PATH Hijack to Root | TryHackMe

---

## 2.2 Reversing angel_A with radare2

Loading `angel_A` In radare2, running a full analysis reveals the main function. The binary calls `ptrace(PTRACE_TRACEME)` on itself as an anti-debug trick — if a debugger is attached, the call fails and the binary exits early.

```
$ r2 angel_A
[0x00001090]> aaa
[0x00001090]> afl
0x00001175 8 225 main
```

```
[0x00001090]> pdf @ main
; ptrace anti-debug check
0x000011a2 cmp rax, 0xffffffffffffffff
0x000011a8 lea rdi, str.Using_debuggers...
; Username input via fgets() size=9
0x000011df mov esi, 9
0x000011e7 call sym.imp.fgets
; XOR comparison loop against stored value
0x00001211 movzx eax, byte [rbp + rax - 0xd]
0x00001215 xor eax, 4 ; key = 4
```

Dumping the strings section shows the obfuscated username stored at the address `0x4060`:

```
[0x00001090]> iz
4 0x00004060 8 32 .data utf32le kym~humr
```

The stored value `kym~humr` is XOR-encoded with the key `4`. A simple Python script decodes it:

```
# de.py
stored = "kym~humr"
decoded = "".join([chr((ord(c)-8) ^ 4) for c in stored])
print(decoded)
```

```
$ python de.py
[REDACTED]
```

>

*🔑 Username: *`*[REDACTED]*`

Confirming with the binary:

```
$ ./angel_A
Say my username >> [REDACTED]
Correct! That is my name!
```

---
