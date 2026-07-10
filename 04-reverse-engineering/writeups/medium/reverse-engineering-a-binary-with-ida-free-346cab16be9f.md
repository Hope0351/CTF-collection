# :arrows_counterclockwise: Reverse Engineering A Binary With Ida Free 346Cab16Be9F

---

## Introduction

Reverse Engineering of a binary is a process of analyzing and understanding the behavior of an executable file in order to obtain information about binary like it’s code, instructions, functionality and some hidden juicy information.

The binary we are going to reverse engineer is made by me. You can download the binary and related source code from below given link.

Here are some tools that I am going to showcase in this blogpost.

- File

- ltrace

- strace

- objdump

- IDA Freeware

### File

The file command is used in Linux and other Unix-like operating systems to determine the type of a file. When you run the file command followed by the name of a file, it will output information about the file’s format, contents, and other attributes.

### ltraceltrace is a command-line utility in Linux that allows you to trace and analyze the dynamic library calls made by a program. It is often used for debugging and troubleshooting purposes.

### strace

strace is a command-line utility in Linux that allows you to trace and analyze the system calls made by a program. It is often used for debugging and troubleshooting purposes.

### objdump

objdump is a command-line utility in Linux and other Unix-like operating systems that allows you to display information about object files, executable files, shared libraries, and core dumps. It is often used for analyzing binary files and debugging programs.

objdump is a powerful tool for analyzing binary files, but it requires some knowledge of computer architecture and assembly language to interpret its output.

### IDA Freeware

IDA Freeware is a disassembler and debugger software for Windows, Linux, and macOS that allows you to analyze binary files, executable files, and firmware. It is often used by reverse engineers, malware analysts, and security researchers.

## Get Jay Vadhaiya’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

IDA Freeware provides a comprehensive set of features for analyzing binary files, including advanced static analysis capabilities like graphing and cross-referencing. It also includes a dynamic analysis feature called the Debugger, which allows you to run a program inside IDA and pause execution at any point to inspect memory, registers, and call stack information.

## Analysis

Now as you know little bit about tools being used, let’s start the analysis. At the first, we will run the program check what is asking for and how it behaves on user input. (See figure 1.1)

*Figure 1.1*

Anything we will give to it except it will say Better luck next time. :(

Let’s first determine file type and see what kind of information we can get out of it.

As you can see, it’s a ELF 64-bit binary and not stripped. Not stripped indicates that their may be some debug information can be found.

Now let’s test the binary with ltrace and strace command and see we can found any value able information or not.

*ltrace information*

*strace information*

As you can see there is no information related to password that can give us any hint. In short we got nothing from here. Now we have to go through the assembly representation to get the password. Here we can use both objdump and IDA Freeware but reading a large amount of assembly in terminal is very hard. Let’s take a glace at objdump and then move towards IDA Freeware.

```
┌──(kali㉿kali)-[~/Desktop/C]
└─$ objdump -d level1

level1: file format elf64-x86-64

Disassembly of section .init:

0000000000001000 <_init>:
1000: 48 83 ec 08 sub $0x8,%rsp
1004: 48 8b 05 c5 2f 00 00 mov 0x2fc5(%rip),%rax # 3fd0 <__gmon_start__@Base>
100b: 48 85 c0 test %rax,%rax
100e: 74 02 je 1012 <_init+0x12>
1010: ff d0 call *%rax
1012: 48 83 c4 08 add $0x8,%rsp
1016: c3 ret

Disassembly of section .plt:

0000000000001020 <printf@plt-0x10>:
1020: ff 35 ca 2f 00 00 push 0x2fca(%rip) # 3ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
1026: ff 25 cc 2f 00 00 jmp *0x2fcc(%rip) # 3ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
102c: 0f 1f 40 00 nopl 0x0(%rax)

0000000000001030 <printf@plt>:
1030: ff 25 ca 2f 00 00 jmp *0x2fca(%rip) # 4000 <printf@GLIBC_2.2.5>
1036: 68 00 00 00 00 push $0x0
103b: e9 e0 ff ff ff jmp 1020 <_init+0x20>

0000000000001040 <__isoc99_scanf@plt>:
1040: ff 25 c2 2f 00 00 jmp *0x2fc2(%rip) # 4008 <__isoc99_scanf@GLIBC_2.7>
1046: 68 01 00 00 00 push $0x1
104b: e9 d0 ff ff ff jmp 1020 <_init+0x20>

Disassembly of section .plt.got:

0000000000001050 <__cxa_finalize@plt>:
1050: ff 25 8a 2f 00 00 jmp *0x2f8a(%rip) # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
1056: 66 90 xchg %ax,%ax

Disassembly of section .text:

0000000000001060 <_start>:
1060: 31 ed xor %ebp,%ebp
1062: 49 89 d1 mov %rdx,%r9
1065: 5e pop %rsi
1066: 48 89 e2 mov %rsp,%rdx
1069: 48 83 e4 f0 and $0xfffffffffffffff0,%rsp
106d: 50 push %rax
106e: 54 push %rsp
106f: 45 31 c0 xor %r8d,%r8d
1072: 31 c9 xor %ecx,%ecx
1074: 48 8d 3d 5a 01 00 00 lea 0x15a(%rip),%rdi # 11d5 <main>
107b: ff 15 3f 2f 00 00 call *0x2f3f(%rip) # 3fc0 <__libc_start_main@GLIBC_2.34>
1081: f4 hlt
1082: 66 2e 0f 1f 84 00 00 cs nopw 0x0(%rax,%rax,1)
1089: 00 00 00
108c: 0f 1f 40 00 nopl 0x0(%rax)

0000000000001090 <deregister_tm_clones>:
1090: 48 8d 3d 89 2f 00 00 lea 0x2f89(%rip),%rdi # 4020 <__TMC_END__>
1097: 48 8d 05 82 2f 00 00 lea 0x2f82(%rip),%rax # 4020 <__TMC_END__>
109e: 48 39 f8 cmp %rdi,%rax
10a1: 74 15 je 10b8 <deregister_tm_clones+0x28>
10a3: 48 8b 05 1e 2f 00 00 mov 0x2f1e(%rip),%rax # 3fc8 <_ITM_deregisterTMCloneTable@Base>
10aa: 48 85 c0 test %rax,%rax
10ad: 74 09 je 10b8 <deregister_tm_clones+0x28>
10af: ff e0 jmp *%rax
10b1: 0f 1f 80 00 00 00 00 nopl 0x0(%rax)
10b8: c3 ret
10b9: 0f 1f 80 00 00 00 00 nopl 0x0(%rax)

00000000000010c0 <register_tm_clones>:
10c0: 48 8d 3d 59 2f 00 00 lea 0x2f59(%rip),%rdi # 4020 <__TMC_END__>
10c7: 48 8d 35 52 2f 00 00 lea 0x2f52(%rip),%rsi # 4020 <__TMC_END__>
10ce: 48 29 fe sub %rdi,%rsi
10d1: 48 89 f0 mov %rsi,%rax
10d4: 48 c1 ee 3f shr $0x3f,%rsi
10d8: 48 c1 f8 03 sar $0x3,%rax
10dc: 48 01 c6 add %rax,%rsi
10df: 48 d1 fe sar %rsi
10e2: 74 14 je 10f8 <register_tm_clones+0x38>
10e4: 48 8b 05 ed 2e 00 00 mov 0x2eed(%rip),%rax # 3fd8 <_ITM_registerTMCloneTable@Base>
10eb: 48 85 c0 test %rax,%rax
10ee: 74 08 je 10f8 <register_tm_clones+0x38>
10f0: ff e0 jmp *%rax
10f2: 66 0f 1f 44 00 00 nopw 0x0(%rax,%rax,1)
10f8: c3 ret
10f9: 0f 1f 80 00 00 00 00 nopl 0x0(%rax)

0000000000001100 <__do_global_dtors_aux>:
1100: f3 0f 1e fa endbr64
1104: 80 3d 15 2f 00 00 00 cmpb $0x0,0x2f15(%rip) # 4020 <__TMC_END__>
110b: 75 2b jne 1138 <__do_global_dtors_aux+0x38>
110d: 55 push %rbp
110e: 48 83 3d ca 2e 00 00 cmpq $0x0,0x2eca(%rip) # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
1115: 00
1116: 48 89 e5 mov %rsp,%rbp
1119: 74 0c je 1127 <__do_global_dtors_aux+0x27>
111b: 48 8b 3d f6 2e 00 00 mov 0x2ef6(%rip),%rdi # 4018 <__dso_handle>
1122: e8 29 ff ff ff call 1050 <__cxa_finalize@plt>
1127: e8 64 ff ff ff call 1090 <deregister_tm_clones>
112c: c6 05 ed 2e 00 00 01 movb $0x1,0x2eed(%rip) # 4020 <__TMC_END__>
1133: 5d pop %rbp
1134: c3 ret
1135: 0f 1f 00 nopl (%rax)
1138: c3 ret
1139: 0f 1f 80 00 00 00 00 nopl 0x0(%rax)

0000000000001140 <frame_dummy>:
1140: f3 0f 1e fa endbr64
1144: e9 77 ff ff ff jmp 10c0 <register_tm_clones>

0000000000001149 <checkPass>:
1149: 55 push %rbp
114a: 48 89 e5 mov %rsp,%rbp
114d: 48 89 7d f8 mov %rdi,-0x8(%rbp)
1151: 48 8b 45 f8 mov -0x8(%rbp),%rax
1155: 0f b6 00 movzbl (%rax),%eax
1158: 3c 73 cmp $0x73,%al
115a: 75 70 jne 11cc <checkPass+0x83>
115c: 48 8b 45 f8 mov -0x8(%rbp),%rax
1160: 48 83 c0 01 add $0x1,%rax
1164: 0f b6 00 movzbl (%rax),%eax
1167: 3c 75 cmp $0x75,%al
1169: 75 68 jne 11d3 <checkPass+0x8a>
116b: 48 8b 45 f8 mov -0x8(%rbp),%rax
116f: 48 83 c0 02 add $0x2,%rax
1173: 0f b6 00 movzbl (%rax),%eax
1176: 3c 64 cmp $0x64,%al
1178: 75 59 jne 11d3 <checkPass+0x8a>
117a: 48 8b 45 f8 mov -0x8(%rbp),%rax
117e: 48 83 c0 03 add $0x3,%rax
1182: 0f b6 00 movzbl (%rax),%eax
1185: 3c 6f cmp $0x6f,%al
1187: 75 4a jne 11d3 <checkPass+0x8a>
1189: 48 8b 45 f8 mov -0x8(%rbp),%rax
118d: 48 83 c0 04 add $0x4,%rax
1191: 0f b6 00 movzbl (%rax),%eax
1194: 3c 30 cmp $0x30,%al
1196: 75 3b jne 11d3 <checkPass+0x8a>
1198: 48 8b 45 f8 mov -0x8(%rbp),%rax
119c: 48 83 c0 05 add $0x5,%rax
11a0: 0f b6 00 movzbl (%rax),%eax
11a3: 3c 78 cmp $0x78,%al
11a5: 75 2c jne 11d3 <checkPass+0x8a>
11a7: 48 8b 45 f8 mov -0x8(%rbp),%rax
11ab: 48 83 c0 06 add $0x6,%rax
11af: 0f b6 00 movzbl (%rax),%eax
11b2: 3c 31 cmp $0x31,%al
11b4: 75 1d jne 11d3 <checkPass+0x8a>
11b6: 48 8b 45 f8 mov -0x8(%rbp),%rax
11ba: 48 83 c0 07 add $0x7,%rax
11be: 0f b6 00 movzbl (%rax),%eax
11c1: 3c 38 cmp $0x38,%al
11c3: 75 0e jne 11d3 <checkPass+0x8a>
11c5: b8 01 00 00 00 mov $0x1,%eax
11ca: eb 07 jmp 11d3 <checkPass+0x8a>
11cc: b8 00 00 00 00 mov $0x0,%eax
11d1: eb 00 jmp 11d3 <checkPass+0x8a>
11d3: 5d pop %rbp
11d4: c3 ret

00000000000011d5 <main>:
11d5: 55 push %rbp
11d6: 48 89 e5 mov %rsp,%rbp
11d9: 48 83 ec 50 sub $0x50,%rsp
11dd: 89 7d bc mov %edi,-0x44(%rbp)
11e0: 48 89 75 b0 mov %rsi,-0x50(%rbp)
11e4: 48 8d 05 19 0e 00 00 lea 0xe19(%rip),%rax # 2004 <_IO_stdin_used+0x4>
11eb: 48 89 c7 mov %rax,%rdi
11ee: b8 00 00 00 00 mov $0x0,%eax
11f3: e8 38 fe ff ff call 1030 <printf@plt>
11f8: 48 8d 05 1f 0e 00 00 lea 0xe1f(%rip),%rax # 201e <_IO_stdin_used+0x1e>
11ff: 48 89 c7 mov %rax,%rdi
1202: b8 00 00 00 00 mov $0x0,%eax
1207: e8 24 fe ff ff call 1030 <printf@plt>
120c: 48 8d 45 c0 lea -0x40(%rbp),%rax
1210: 48 89 c6 mov %rax,%rsi
1213: 48 8d 05 1b 0e 00 00 lea 0xe1b(%rip),%rax # 2035 <_IO_stdin_used+0x35>
121a: 48 89 c7 mov %rax,%rdi
121d: b8 00 00 00 00 mov $0x0,%eax
1222: e8 19 fe ff ff call 1040 <__isoc99_scanf@plt>
1227: 48 8d 45 c0 lea -0x40(%rbp),%rax
122b: 48 89 c7 mov %rax,%rdi
122e: e8 16 ff ff ff call 1149 <checkPass>
1233: 85 c0 test %eax,%eax
1235: 74 16 je 124d <main+0x78>
1237: 48 8d 05 fc 0d 00 00 lea 0xdfc(%rip),%rax # 203a <_IO_stdin_used+0x3a>
123e: 48 89 c7 mov %rax,%rdi
1241: b8 00 00 00 00 mov $0x0,%eax
1246: e8 e5 fd ff ff call 1030 <printf@plt>
124b: eb 14 jmp 1261 <main+0x8c>
124d: 48 8d 05 fa 0d 00 00 lea 0xdfa(%rip),%rax # 204e <_IO_stdin_used+0x4e>
1254: 48 89 c7 mov %rax,%rdi
1257: b8 00 00 00 00 mov $0x0,%eax
125c: e8 cf fd ff ff call 1030 <printf@plt>
1261: b8 00 00 00 00 mov $0x0,%eax
1266: c9 leave
1267: c3 ret

Disassembly of section .fini:

0000000000001268 <_fini>:
1268: 48 83 ec 08 sub $0x8,%rsp
126c: 48 83 c4 08 add $0x8,%rsp
1270: c3 ret
```

And this is what we got from objdump but it is very hard to analyze the binary this way. Let’s how load the binary in IDA Freeware and take a look at binary. IDA Freeware provides a very popular and easy graphical representation of binary which makes analysis more easy.

*IDA Freeware*

Now let’s understand what it is doing and how can we get a password.

*Main Function*

As you can see it prints welcome message and asking for a secret to user. After that it scans the user input and stores it to [rbp+var_40] variable. If you see, it calls a function called checkPass and passes the user input to the function. Double click on checkPass function to see what this function is doing.

*checkPass Function*

As you can see, It seems like it is checking multiple conditions with user provided input to actual password. It’s understand it and get the actual password.

*Condition Statement*

As you can see, It is tacking one one byte from user input and compares it to certain character. If condition satisfies then moves to another block of code and compares another character. You can see IDA Freeware shows us the char representation in comment besides the hex value. This what we looking for.

Now collect every character from each block and it will reveal the actual password. Woh, we got the password. Now let’s check if this password is right or not by entering in command line.

*Final Password*

Boom and we cracked our first binary. I haven’t revealed the password because I want you to repeat the process to try your own.

---
