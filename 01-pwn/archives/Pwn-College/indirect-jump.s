.intel_syntax noprefix
.global _start
_start:
cmp rdi,3
ja _default
mov rax, [rsi+rdi*8]
jmp rax
_default:
jmp [rsi+4*8]