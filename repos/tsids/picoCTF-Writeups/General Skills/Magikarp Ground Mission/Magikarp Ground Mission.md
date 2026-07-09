# [Magikarp Ground Mission](https://play.picoctf.org/practice/challenge/189)

## Overview

**Points**: 30

**Category**: [General Skills](../)

## Description

Do you know how to move between directories and read files in the shell? Start the container, `ssh` to it, and then `ls` once connected to begin. Login via `ssh` as `ctf-player` with the password, `b60940ca`

## Hints

1. Finding a cheatsheet for bash would be really helpful!

## Solution

1. Open the WebShell on the right side of the window and login using your username and password.
![webshell](webshell.png)
2. Launch the challenge instance and `ssh` into the challenge using `ssh ctf-player@venus.picoctf.net -p 57170`, then enter the password `b60940ca`.
3. Run `ls` to see the files in the current directory.
```sh
ctf-player@pico-chall$ ls
1of3.flag.txt  instructions-to-2of3.txt
```
4. Run `cat 1of3.flag.txt` to print out the first part of the flag, then run `cat instructions-to-2of3.txt` to figure out how to get to the second part of the flag.
```sh
ctf-player@pico-chall$ cat 1of3.flag.txt 
picoCTF{xxsh_
ctf-player@pico-chall$ cat instructions-to-2of3.txt 
Next, go to the root of all things, more succinctly `/`
```
5. To go to the root, use the `cd ..` command to go back one directory. Do this until you get to the root. Use the `ls` command to list the files at each directory.
```sh
ctf-player@pico-chall$ cd ..
ctf-player@pico-chall$ ls
3of3.flag.txt  drop-in
ctf-player@pico-chall$ cd ..
ctf-player@pico-chall$ ls 
ctf-player
ctf-player@pico-chall$ cd ..
ctf-player@pico-chall$ ls
2of3.flag.txt  dev   instructions-to-3of3.txt  media  proc  sbin  tmp
bin            etc   lib                       mnt    root  srv   usr
boot           home  lib64                     opt    run   sys   var
```
6. Run the `cat` command to print the second part of the flag, and the instructions to get to the third flag.
```sh
ctf-player@pico-chall$ cat 2of3.flag.txt 
0ut_0f_\/\/4t3r_
ctf-player@pico-chall$ cat instructions-to-3of3.txt 
Lastly, ctf-player, go home... more succinctly `~`
```
7. `cd` into the home directory by running `cd ~`. Then use the `cat` command to print out the last part of the flag.
```sh
ctf-player@pico-chall$ ls
3of3.flag.txt  drop-in
ctf-player@pico-chall$ cat 3of3.flag.txt 
c1754242}
```

## Flag

`picoCTF{xxsh_0ut_0f_\/\/4t3r_c1754242}`
