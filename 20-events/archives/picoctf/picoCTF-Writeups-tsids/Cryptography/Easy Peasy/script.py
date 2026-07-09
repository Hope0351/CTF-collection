# encrypted flag: 551257106e1a52095f654f510a6b4954026c1e0304394100043a1c5654505b6b
# flag: 75302b38697a8717f0faee9c0fd36a57

from pwn import *

io = remote('mercury.picoctf.net', 36449)

encrypted = unhex(io.recvline_startswith('55'))

io.sendlineafter("What data would you like to encrypt?",
                 'p'*(50000-len(encrypted)))
io.sendlineafter(
    "What data would you like to encrypt?", encrypted)
io.recvline()
flag = unhex(io.recvline())
print(f"picoCTF{{{str(flag, 'utf-8')}}}")
io.close()


chars = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
for i in range(26, 66, 2):
    for c in chars:
        io = remote('mercury.picoctf.net', 36449)
        log.success(f"Current character: {c}")
        e = io.recvline_startswith('55')
        io.sendlineafter("What data would you like to encrypt?",
                         'p'*(50000-len(encrypted)))
        io.sendlineafter(
            "What data would you like to encrypt?", (flag + c.encode()))
        io.recvline()
        new = io.recvline()
        if new[:-1] == e[:i]:
            flag += c.encode()
            break
        io.close()
print(f"picoCTF{{{str(flag, 'utf-8')}}}")
