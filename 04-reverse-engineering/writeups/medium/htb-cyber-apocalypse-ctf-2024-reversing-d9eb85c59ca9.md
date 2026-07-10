# :arrows_counterclockwise: Htb Cyber Apocalypse Ctf 2024 Reversing D9Eb85C59Ca9

> **Original Source:** [Htb Cyber Apocalypse Ctf 2024 Reversing D9Eb85C59Ca9](https://infosecwriteups.com/htb-cyber-apocalypse-ctf-2024-reversing-d9eb85c59ca9)
> **Platform:** infosecwriteups.com | **Category:** `REVERSE ENGINEERING` | **Year:** 2024

---

## BoxCutter


>

You’ve received a supply of valuable food and medicine from a generous sponsor. There’s just one problem — the box is made of solid steel! Luckily, there’s a dumb automated defense robot which you may be able to trick into opening the box for you — it’s programmed to only attack things with the correct label.


### 💡Solution


Again, we kick off by extracting the ZIP archive provided by the challenge, which contains a file that resembles a binary. Let’s double-check its file type:


```
$ file cutter

cutter: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=f76eb244685ad0c3b817caa99093531754fc84c8, for GNU/Linux 3.2.0, not stripped
```


We have indeed a 64-bit Unix binary. We proceed with running the basic checks such as `strings` and `hexdump`.


```
$ strings cutter | grep -i htb

$ hexdump cutter| grep -i htb
```


This yielded nothing. Right, before we roll up our sleeves and run a debugger, let’s re-read the challenge description for more clues.


In the given challenge, words like “*automated defense robo*t” and “*correct label*” may hint at the need to analyze the program’s behavior, making `strace`a valuable tool for understanding its actions.

>

“strace” is a debugging tool used to monitor system calls and signals. In CTF challenges, it can help uncover hidden functionality or reveal clues by tracing the execution of a program.


```
$ strace ./cutter

execve("./cutter", ["./cutter"], 0x7ffec8610920 /* 55 vars */) = 0
brk(NULL) = 0x55dd45444000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f3cf4a37000
access("/etc/ld.so.preload", R_OK) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=90375, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 90375, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f3cf4a20000
close(3) = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\220x\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=1926256, ...}, AT_EMPTY_PATH) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 1974096, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f3cf483e000
mmap(0x7f3cf4864000, 1396736, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x26000) = 0x7f3cf4864000
mmap(0x7f3cf49b9000, 344064, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x17b000) = 0x7f3cf49b9000
mmap(0x7f3cf4a0d000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1cf000) = 0x7f3cf4a0d000
mmap(0x7f3cf4a13000, 53072, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f3cf4a13000
close(3) = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f3cf483b000
arch_prctl(ARCH_SET_FS, 0x7f3cf483b740) = 0
set_tid_address(0x7f3cf483ba10) = 194052
set_robust_list(0x7f3cf483ba20, 24) = 0
rseq(0x7f3cf483c060, 0x20, 0, 0x53053053) = 0
mprotect(0x7f3cf4a0d000, 16384, PROT_READ) = 0
mprotect(0x55dd44aeb000, 4096, PROT_READ) = 0
mprotect(0x7f3cf4a69000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x7f3cf4a20000, 90375) = 0
openat(AT_FDCWD, "HTB{tr4c1ng_th3_c4ll5}", O_RDONLY) = -1 ENOENT (No such file or directory)
newfstatat(1, "", {st_mode=S_IFCHR|0600, st_rdev=makedev(0x88, 0x3), ...}, AT_EMPTY_PATH) = 0
getrandom("\x80\x44\x83\x84\xa3\x91\xb5\xc7", 8, GRND_NONBLOCK) = 8
brk(NULL) = 0x55dd45444000
brk(0x55dd45465000) = 0x55dd45465000
write(1, "[X] Error: Box Not Found\n", 25[X] Error: Box Not Found
) = 25
exit_group(0) = ?
+++ exited with 0 +++
```


We have found the flag in the line starting with “openat(AT_FDCWD”.
`openat()`is a system call used to open files, similar to open(). In this case, the file was the flag string, which does not exist, hence the error “*No such file or directory*”.


## Get Abdul Issa’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


We’ve tried the system call monitoring route, what about any dynamic library calls? Another way of checking for the flag is by using `ltrace` tool to execute the binary and monitor library calls.

>

“ltrace” is a debugging tool used to intercept and record dynamic library calls made by a program during its execution. It helps in understanding how a program interacts with shared libraries, which can be useful in analyzing its behavior or identifying specific functions or system calls it makes.


```
$ ltrace ./cutter

open("HTB{tr4c1ng_th3_c4ll5}", 0, 00) = -1
puts("[X] Error: Box Not Found"[X] Error: Box Not Found
) = 25
+++ exited (status 0) +++
```


Bingo! The ltrace tool successfully intercepted a dynamic library call to `open()`a file named “HTB{tr4c1ng_th3_c4ll5},” which, as expected, does not exist. However, this interception revealed the location where the flag value was hidden within the application.

>

Flag: HTB{tr4c1ng_th3_c4ll5}

---

*Originally published on [Medium](https://infosecwriteups.com/htb-cyber-apocalypse-ctf-2024-reversing-d9eb85c59ca9). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of reverse engineering CTF writeups.*
