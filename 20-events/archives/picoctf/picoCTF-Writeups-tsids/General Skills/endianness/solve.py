from Crypto.Util.number import *
from pwn import *

r = remote('titan.picoctf.net', 54462)
word = r.recvline_contains(b"Word: ").split(b": ")[1]
hex_array = [word.hex()[i:i+2] for i in range(0, len(word.hex()), 2)]
r.recvuntil(b"Enter the Little Endian representation: ")
r.sendline(''.join(hex_array[::-1]).encode())
r.recvuntil(b"Enter the Big Endian representation: ")
r.sendline(''.join(hex_array).encode())
print(r.recvline_contains(b'picoCTF{').decode())
