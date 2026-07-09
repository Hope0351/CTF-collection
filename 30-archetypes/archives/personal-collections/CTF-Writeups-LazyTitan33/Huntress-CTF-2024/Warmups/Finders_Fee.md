# Finders Fee



## My Solution

We are dropped in a shell where the `find` command has SUID permissions and the flag is in the `finder` user home directory. Looking through the help section of the find command, we can see that using the `-files0-from` argument, it allows us to give it a file as an argument from which to read files.  



However, similar to other binaries, when it is not finding the file you provide, it tells you with a verbose error message and as such you can leak information. 

```bash
find -files0-from /home/finder/flag.txt
```



`flag{5da1de289823cfc200adf91d6536d914}`
