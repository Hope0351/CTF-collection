# :game_die: UIUCTF 2024 - Summarize. Summarize

> **Original Source:** [UIUCTF 2024 - Summarize. Summarize](https://infosecwriteups.com/uiuctf-2024-summarize-c9b3e100c736)
> **Platform:** infosecwriteups.com | **Category:** `MISC` | **Year:** 2024

---

# UIUCTF 2024 — **Summarize**


Category: Reverse Engineering
Tags: reversing, ghidra, z3-solver

## Description


>

All you have to do is find six numbers. How hard can that be?


Author: Nikhil


*It will be EZ.*

## Disassembly (BinaryNinja/ghidra)


[https://dogbolt.org/?id=8d09d83e-8514-464b-8722-515ca0f11d91](https://dogbolt.org/?id=8d09d83e-8514-464b-8722-515ca0f11d91)


## Get Szigecsán Dávid’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Based on the `entry()`, we know the program starts with the `FUN_004011d6()/sub_4011d6()`, which asks for six numbers, each is 9-digit long.
After that, there is a check method called `FUN_0040137b()/sub_40137b()`, which gets the numbers and does a bunch of examinations on them.
First, it checks if they are in the correct range.


```
if (
(param_1 < 0x5f5e101) || (param_2 < 0x5f5e101) ||
(param_3 < 0x5f5e101) || (param_4 < 0x5f5e101) ||
(param_5 < 0x5f5e101) || (param_6 < 0x5f5e101)
) {
uVar1 = 0;
}
```


*Note: 0x5f5e101 = 100000001*


```
if (
(param_1 < 1000000000) && (param_2 < 1000000000) &&
(param_3 < 1000000000) && (param_4 < 1000000000) &&
(param_5 < 1000000000) && (param_6 < 1000000000)
) {
uVar1 = FUN_004016d8(param_1,param_2);
uVar2 = FUN_0040163d(uVar1,param_3);
uVar3 = FUN_0040163d(param_1,param_2);
uVar1 = FUN_004016fe(2,param_2);
uVar4 = FUN_004016fe(3,param_1);
uVar5 = FUN_004016d8(uVar4,uVar1);
uVar6 = FUN_0040174a(param_1,param_4);
uVar1 = FUN_0040163d(param_3,param_1);
uVar7 = FUN_004017a9(param_2,uVar1);
uVar11 = FUN_0040163d(param_2,param_4);
uVar1 = FUN_0040163d(param_4,param_6);
uVar8 = FUN_0040174a(param_3,uVar1);
uVar9 = FUN_004016d8(param_5,param_6);
uVar10 = FUN_0040163d(param_5,param_6);
if (
(uVar2 % 0x10ae961 == 0x3f29b9) &&
(uVar3 % 0x1093a1d == 0x8bdcd2) &&
(uVar5 % uVar6 == 0x212c944d) &&
(uVar7 % 0x6e22 == 0x31be) &&
(uVar11 % param_1 == 0x2038c43c) &&
(uVar8 % 0x1ce628 == 0x1386e2) &&
(uVar9 % 0x1172502 == 0x103cf4f) &&
(uVar10 % 0x2e16f83 == 0x16ab0d7)
) {
uVar1 = 1;
}
}
```


After that, there are lots of (5*) functions we have to analyze, what they do.
Let's see them one by one.
The second one is called `FUN_0040163d()/sub_40163d()`, where BinaryNinja works a bit better, so I changed to that.


```
int64_t sub_40163d(uint32_t arg1, uint32_t arg2) __pure
{
uint32_t var_2c = arg1;
uint32_t var_30 = arg2;
int64_t var_10 = 0;
int32_t var_20 = 0;
int32_t var_1c = 0;
while (!((var_2c == 0 && var_30 == 0)))
{
int32_t rax_2 = (var_2c & 1);
int32_t rax_4 = (var_30 & 1);
var_2c = (var_2c >> 1);
var_30 = (var_30 >> 1);
var_10 = (var_10 + (((rax_2 ^ rax_4) ^ var_20) << var_1c));
var_20 = ((rax_4 & var_20) | ((rax_2 & rax_4) | (rax_2 & var_20)));
var_1c = (var_1c + 1);
}
return (var_10 + (var_20 << var_1c));
}
```


My first thought was “Holly Cow, what am I looking at?“. I admit, I couldn’t figure it out, so I rewrote it in a small python script and tested it with different inputs.


```
def sub_40163d(arg1, arg2):
var_2c = arg1
var_30 = arg2
var_10 = 0
var_20 = 0
var_1c = 0
while not (var_2c == 0 and var_30 == 0):
print("var_2c != 0 || var_30 != 0")
rax_2 = (var_2c & 1)
print("rax_2 = ", rax_2)
rax_4 = (var_30 & 1)
print("rax_4 = ", rax_4)
var_2c = (var_2c >> 1)
print("var_2c = ", rax_4)
var_30 = (var_30 >> 1)
var_10 = (var_10 + (((rax_2 ^ rax_4) ^ var_20) << var_1c))
var_20 = ((rax_4 & var_20) | ((rax_2 & rax_4) | (rax_2 & var_20)))
var_1c = (var_1c + 1)

return var_10 + (var_20 << var_1c)

for i in range(0, 10):
for j in range(0, 10):
print("sub_40163d(", i, ", ", j, ") => ", sub_40163d(i, j))
```


It turned out it is just an overcomplicated add method, so I continued with the first method called `FUN_004016d8()/sub_4016d8()`, where basically just calling the second one with a negative second parameter. So it is a negative add alias subtraction.
I checked the other methods and rewrote them if needed. The methods are `addition()`, `subtraction()`, `multiplication()`, `xor()` and `and()`.
For better performance, I rewrite them in a simple way in python.


```
def add(param_1, param_2):
return param_1 + param_2


def sub(param_1, param_2):
return param_1 - param_2


def mul(param_1, param_2):
return param_1 * param_2


def xor(param_1, param_2):
return param_1 ^ param_2


def and_(param_1, param_2):
return param_1 & param_2
```


Finally, I needed to solve the system of equations with 6 unknowns. Fortunately, there is a python tool called [z3](https://pypi.org/project/z3-solver/), which can solve difficult problems based on simple statements.
Luckily, we have simple statements, so put them into a python script.

## Solution


```
from z3 import *


def add(param_1, param_2):
return param_1 + param_2


def sub(param_1, param_2):
return param_1 - param_2


def mul(param_1, param_2):
return param_1 * param_2


def xor(param_1, param_2):
return param_1 ^ param_2


def and_(param_1, param_2):
return param_1 & param_2


a, b, c, d, e, f = BitVecs('a b c d e f', 32)

s = Solver()

s.add(a > 100000001)
s.add(b > 100000001)
s.add(c > 100000001)
s.add(d > 100000001)
s.add(e > 100000001)
s.add(f > 100000001)

s.add(a < 1000000000)
s.add(b < 1000000000)
s.add(c < 1000000000)
s.add(d < 1000000000)
s.add(e < 1000000000)
s.add(f < 1000000000)

uVar1 = sub(a, b)
uVar2 = add(uVar1, c)
uVar3 = add(a, b)
uVar1 = mul(2, b)
uVar4 = mul(3, a)
uVar5 = sub(uVar4, uVar1)
uVar6 = xor(a, d)
uVar1 = add(c, a)
uVar7 = and_(b, uVar1)
uVar11 = add(b, d)
uVar1 = add(d, f)
uVar8 = xor(c, uVar1)
uVar9 = sub(e, f)
uVar10 = add(e, f)

s.add(uVar2 % 0x10ae961 == 0x3f29b9)
s.add(uVar3 % 0x1093a1d == 0x8bdcd2)
s.add(uVar5 % uVar6 == 0x212c944d)
s.add(uVar7 % 0x6e22 == 0x31be)
s.add(uVar11 % a == 0x2038c43c)
s.add(uVar8 % 0x1ce628 == 0x1386e2)
s.add(uVar9 % 0x1172502 == 0x103cf4f)
s.add(uVar10 % 0x2e16f83 == 0x16ab0d7)

if s.check() == sat:
m = s.model()
print(f'a = {m[a]}\nb = {m[b]}\nc = {m[c]}\nd = {m[d]}\ne = {m[e]}\nf = {m[f]}')
else:
print("No solution found")
```


This script solves our problem and prints the following result.


```
a = 705965527
b = 780663452
c = 341222189
d = 465893239
e = 966221407
f = 217433792
```


We just need to run the application and put the values there.


*Solution*

## Skills Learned


- reversing and rewriting overcomplicated algorithms

- z3-solver

---

*Originally published on [Medium](https://infosecwriteups.com/uiuctf-2024-summarize-c9b3e100c736). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
