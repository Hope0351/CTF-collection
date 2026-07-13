# Shellcode Analysis: Egg Hunters, Encoders, and Polymorphism

> Topic: Advanced shellcode techniques — egg hunters, encoding, and polymorphic generation
> Source basis: Personal study notes on exploit development

---

## Challenge / Topic Overview

This writeup documents my study of three advanced shellcode techniques that show up frequently in real-world exploits and higher-difficulty CTF challenges:

1. **Egg hunters** — a tiny shellcode stub that searches process memory for a larger payload, used when the overflow buffer is too small for full shellcode.
2. **Encoders** — transform shellcode bytes to evade signature detection (and to avoid bad characters like null bytes), then decode at runtime.
3. **Polymorphism** — generate a different shellcode byte sequence on every run, defeating signature-based AV even when the payload's behavior is identical.

These three techniques are often combined: a polymorphic egg hunter that decodes its own search marker, finds the encoded second-stage payload, decodes it, and executes it.

![Egg hunter + encoder + polymorphism pipeline](diagrams/egg-hunter-pipeline.png)

*The egg hunter searches memory for a marker (e.g., `w00tw00t`), finds the encoded payload, decodes it in-place, and jumps to it. The hunter itself is tiny (~30 bytes) — small enough to fit in very small overflow buffers.*

---

## Egg Hunters

### The problem

Sometimes the overflow buffer is too small for full shellcode. A typical `execve("/bin/sh")` shellcode is 24-30 bytes; a reverse shell is 70-100 bytes. If the overflow buffer is only 20 bytes, neither fits. The egg hunter technique solves this by splitting the exploit into two parts:

- **Stage 1 (the egg hunter):** ~30 bytes, fits in the overflow buffer. Its job is to search process memory for a marker (the "egg") and jump to the payload that follows the marker.
- **Stage 2 (the payload):** The full shellcode, placed elsewhere in memory (e.g., in an environment variable, a command-line argument, or a separate input field). It's prefixed with the egg marker so the hunter can find it.

### The marker

The egg is an 8-byte value (typically `w00tw00t`) that's unlikely to appear in memory by chance. The hunter searches memory page by page, reading 8 bytes at each address and comparing to the egg. When it finds a match, it jumps to the address right after the egg.

### The hunter algorithm

```c
// Pseudocode of the hunter
void *addr = 0;
while (1) {
    if (memcmp(addr, "w00tw00t", 8) == 0) {
        ((void(*)())(addr + 8))();  // jump to payload
    }
    addr++;
}
```

The real implementation is trickier because:
- Most memory pages are unmapped, so reading from them triggers SIGSEGV.
- The hunter must catch SIGSEGV (or use `access()` syscall to check page validity without crashing).
- On Linux, the `access()` syscall returns `EFAULT` for unmapped pages without crashing — this is the common technique.

### A Linux x86-64 egg hunter (~30 bytes)

```asm
egg_hunter:
    mov rdi, 0xffffffffffffffff  ; start at low address
next_page:
    or rdi, 0xfff               ; align to page boundary
next_addr:
    inc rdi                      ; next address
    push 0x15                    ; access syscall number (21)
    pop rax
    mov rsi, rdi                 ; address to check
    syscall                      ; access(addr, 0) — returns EFAULT if invalid
    cmp al, 0xf2                 ; EFAULT = -14 = 0xf2 in low byte
    jz next_page                 ; page invalid → skip to next page
    mov rax, 0x74776f30774e7730  ; "0wN0w0t" (reversed egg marker)
    ; (in practice, the marker is chosen to avoid bad bytes)
    mov rsi, rdi
    cmpsq                        ; compare 8 bytes at [rsi] to [rdi]
    jnz next_addr                ; no match → try next address
    cmpsq                        ; match! check second half of marker
    jnz next_addr                ; (egg is 8 bytes, two 4-byte compares)
    jmp rdi                      ; found! jump to payload (after marker)
```

---

## Encoders

### Why encode?

Two reasons:
1. **Avoid bad characters.** Many input functions (e.g., `strcpy`, `gets`) terminate on null bytes (`\x00`), newlines (`\x0a`), or carriage returns (`\x0d`). If the shellcode contains these, the overflow truncates. Encoding transforms the shellcode into "safe" bytes, then decodes at runtime.
2. **Evade signature detection.** AV engines have signatures for known shellcode (e.g., Metasploit's `windows/shell_reverse_tcp`). Encoding changes the byte sequence, defeating static signatures.

### XOR encoding (most common)

XOR encoding is simple and self-inverse: `enc = plain ^ key; dec = enc ^ key = plain`. A decoder stub is prepended:

```asm
decoder:
    lea rdi, [rip + encoded_payload]  ; address of encoded bytes
    push 0x80                          ; payload length
    pop rcx
decode_loop:
    xor byte [rdi], 0x5A              ; XOR each byte with key
    inc rdi
    loop decode_loop
    jmp encoded_payload                ; jump to decoded shellcode
encoded_payload:
    db 0x5A ^ <shellcode byte 0>, 0x5A ^ <shellcode byte 1>, ...
```

The decoder stub itself must not contain bad bytes — this is a constraint on the encoder design. Tools like `msfvenom -b '\x00\x0a\x0d' -e x86/shikata_ga_nai` handle this automatically.

### Shikata Ga Nai

The most famous encoder. Instead of a fixed XOR key, it uses a rolling key derived from the previous byte's value, and the decoder stub itself is polymorphic (see below). This makes it much harder to signature than a simple XOR encoder.

---

## Polymorphism

### The problem with encoders

Encoders change the payload bytes, but the decoder stub is always the same. AV can signature the decoder stub. Once they recognize "this is a Shikata Ga Nai decoder," they can flag the file even without knowing the payload.

### The polymorphic solution

A polymorphic engine generates a different decoder stub on every run, even though the decoded payload is identical. The stubs are functionally equivalent but byte-wise different:

- **Register allocation:** The decoder can use `rdi`, `rsi`, `rcx`, or any other register as the loop counter. Each choice produces different bytes.
- **Instruction substitution:** `xor byte [rdi], 0x5A` can be replaced with `sub byte [rdi], -0x5A` (two's complement), or `add byte [rdi], 0xA6` (0x100 - 0x5A). All three have the same effect.
- **Instruction reordering:** The `inc rdi` and `loop` can be swapped if the loop counter is adjusted accordingly.
- **Junk instructions:** Insert `nop`-equivalent instructions (`xchg rax, rax`, `lea rcx, [rcx+0]`) at random points.

### Metasploit's Shikata Ga Nai

Shikata Ga Nai is both an encoder and a polymorphic engine. Every time you run `msfvenom -e x86/shikata_ga_nai`, it produces a different byte sequence — different register allocation, different instruction order, different XOR key derivation. This is why it was (and to some extent still is) hard to signature.

---

## Putting It All Together: Polymorphic Egg Hunter with Encoded Payload

For a real-world engagement, I'd combine all three techniques:

1. **Generate the payload** — a reverse shell shellcode, ~100 bytes.
2. **Encode the payload** — XOR with a random key, prepend the egg marker.
3. **Place the payload** — in an environment variable or separate input.
4. **Generate a polymorphic egg hunter** — ~30 bytes, fits in the small overflow buffer, searches for the egg, jumps to the payload.
5. **Overflow with the egg hunter** — the hunter runs, finds the egg, the (still-encoded) payload is decoded in-place by a small decoder stub in the payload itself, then executed.

This combination defeats both size constraints (egg hunter is tiny) and signature detection (polymorphic stub + encoded payload).

---

## Takeaways

- **Egg hunters are the size-constraint bypass.** When the buffer is too small for full shellcode, use a two-stage approach: a tiny hunter in the buffer, and the payload elsewhere.
- **Encoding is not encryption.** XOR encoding with a known key is trivial to reverse. The purpose is to avoid bad bytes and evade simple signatures, not to protect the payload from analysis.
- **Polymorphism defeats static signatures but not dynamic analysis.** No matter how many times you re-encode, the *behavior* is the same. Modern EDR detects on behavior (API patterns, memory allocation patterns), not byte signatures. The defense evolution from signature-based AV to behavior-based EDR is precisely what made polymorphism less effective in recent years.
- **`msfvenom` is the starting point, not the ending point.** For real engagements, I always customize the encoder/hunter. Off-the-shelf `msfvenom` output is well-signatured; a hand-tweaked variant often isn't.
