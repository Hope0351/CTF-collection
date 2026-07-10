# :arrows_counterclockwise: Reverse Engineering | CTF Newbies | Part 1

---

# Reverse Engineering | CTF Newbies | Part 1

## Introduction

These challenges are designed in such a way that forces the contestants to understand what a program does.

Reverse Engineering as the name suggests, is reversing something that is already made, to learn its internals and working. It is the process of Analyzing and Understanding, A particular piece of code, software, electronics, etc…….

## Why do you need such challenges in CTF ?

In basic CTF’s Reversing challenges are mostly a piece of compiled software, for you to reverse, understand, and break with your skills.

This skill set translates to real-world security scenarios where attackers might use similar techniques to exploit software flaws. These challenges will train you to be more experienced Reverse Engineers, which will help you a lot when tackling real-world problems.

## Where Reversing-Engineering is used in the real world:-

How do you think there is cracked software for you to use?

How do you think people can break multiple malware attacks?

How do you think Game-mods are made?

Yes, Reversing-Engineering is a very vast topic and sure can’t be explained or understood in a single blog post.

## Pre-requisites:

Reversing-Engineering is a complex topic and it goes deeper as you drive in, but…. here are some basics you need to start reversing

1. C/C++ (Basic Understand)

2. ASM (x86_64) (at least basics are recommended)

3. basic use of Debuggers (GDB, x64dbg, Ollydbg) etc……

4. basic use of Disassemblers (IDA, Ghidra, BinaryNinja) any of these.

## About some tools:

You should have some basic knowledge of these tools before diving deep into rev challenges.

## Disassemblers:-

### 1. Hexrays IDA

IDA is the most used and oldest disassembler currently, IDA is preferred by more seasonal Reverse-Engineers because of its brilliant Pseudo-code generation.

### 2. Ghidra

Ghidra is a free Open-Source reverse-engineering tool which is developed by the NSA (National Security Agency), Its Pseudo-code generator is good enough and it has a lot more potential to grow being an Open-Source tool.

### 3. Binary Ninja

Binary Ninja is the most recent disassembler, It has a good Pseudo-code generator and a really good user interface.

## Debuggers:-

### 1. GDB

Gdb is a powerful debugger for debugging Linux binaries, Although Vanilla-gdb feels a little crampy to use, We recommend applying some plugins like…. Peda, Pwndbg, and Gef, Try all 3 and use what you prefer.

### 2. x64-dbg

This is an Open-Source debugger for debugging Windows software, it is the most used and very powerful debugger for Windows.

There are a lot more tools, to use while doing specific tasks on Rev challenges, You learn about them as you go on, your journey of Reverse-Engineering, the above tools are more than enough to get started with.

## # Trying to solve some challenges:

Solving a “compiled-C” type Reversing challenge involves using a combination of Disassemblers and Debuggers to understand the control flow of the program, As you dive deep into learning how to reverse programs, You’ll encounter and learn how to defeat multiple Anti-Debug techniques, packers etc….., which makes your work harder and harder.

## Wanna See It Happening Live?

Let’s take a look at a simple CTF problem.

Here is the link to the CTF problem. You can go ahead and try it on your own.

[picoCTF — picoGym Challenges](https://play.picoctf.org/practice/challenge/175?category=3&page=1)

This is a very basic rev CTF problem. As you see, the only thing we have here is a [crackme.py](http://crackme.py) file. We will download the file and open it.

Opening the file in VS Code we get a Python script, like this

If you look in the header of the program, it has comments telling about an important number that is encrypted.

## Get HackTheBox SRMIST’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Then, there are 2 functions decode_secret() and choose_greatest().

As you know according to Python’s workflow, the execution will start by calling the choose_greatest() function.

Let’s try and call the other function.

Well, this function needs a parameter. If you look closely, you will find a string declared at the top named bezos_cc_secret.

we will try giving that as an input to the function call.

now, if you run the program, you will get the output

That’s your flag.

The above one is a basic Python-Rev challenge, Now we’ll look at a basic binary reversing……

Getting started, We are given a binary called “chall”, forget about the “.c” file, it’s just my work.

Executing the binary, We were asked to enter some password, Try something random, gave us “Wrong Pass”, So….. we can see that the Binary is performing some kind of Password-Check.

Loading the binary into “Binary Ninja”, you can see that we are shown with some de-compiled code, If you take a quick look, you’ll know what the actual password is, this is a very basic strcmp check with our input and password, let’s not stop here, we’ll explore some formats that Binary Ninja can display in.

Looking there, we can see the disassembly, so let’s look at it.

You see, this is how disassembly looks, If you are a little experienced, you should be able to understand this disassembly pretty easily, now…. let’s see how else we can look at it.

Binary Ninja offers a Graph view too, So…. let’s just look into it.

Looking at the graph view, We can depict the control flow easily without following much.

This may look overwhelming at the start, But…. you’ll get used to it once you start doing it.

Now, going back to the Pseudo-C code, We’ll find that “Secret-Password” is the actual password, let’s go ahead and try it.

You see, It works! , This is how you normally approach a reversing challenge.

Now that you have a basic understanding of what reversing engineering is, here are some blogs/videos to help you get started.

You can also practice your skills at sites like

and many more…

You can always google for more :)

Contribution —

Sai Shashank Reddy

Vitthal Choudhary

Devansh Gupta

---
