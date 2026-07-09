# Sekiro




## My Solution

Going through the service and experimenting with our inputs, we soon find that it's basically Rock Paper Scissors:  

We can script it to automate it and get the flag:  

```python
#!/usr/bin/python3

from pwn import *
context.log_level = "warn"

p = remote('challenge.ctf.games', 32523)

# retreat < strike
# strike < block
# block < advance
# advance < retreat

while True:
	try:
		p.recvuntil(b'Opponent move: ')
		action = p.recvline()
		if b'block' in action:
			p.recvuntil(b'Your move: ')
			p.sendline(b'advance')
			
		elif b'retreat' in action:
			p.recvuntil(b'Your move: ')
			p.sendline(b'strike')
			
		elif b'strike' in action:
			p.recvuntil(b'Your move: ')
			p.sendline(b'block')
			
		elif b'advance' in action:
			p.recvuntil(b'Your move: ')
			p.sendline(b'retreat')
	except:
		p.interactive()
```



`flag{a1ae4e5604576818132ce3bfebe95de5}`
