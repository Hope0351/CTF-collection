# :skull: Pwn Challenges CTF 2025 [binary Exploiation]

---

# Pwn Challenges CTF 2025 [binary Exploiation]

I love to play ctf. I started learning pwn (binary exploiation). There are some cool challenges that also help you to solve some easy pwn challenges. Lets Start…

## 1: Bof1

So this challenge was the first challenge. Easy one.

We just have to bufferoverflow. And to overflow anything we just have to cross the limits of the thing. Like water, or code.

And there we go our first FLAG…

## 2: stack0

This was our 2nd pwn challenge. Same simple but thinking different. That,s why i couldn,t solve easy challenges fast.

Same challenge bufferoverflow, but twist was you the limit was high compair to first challenge. So we just have to put more letters.

## 3: heap0

This challenge was little bit complex. Because to solve this challenge you have to write code. So the challenge was

So in this challenge we have to get shell and see the flag.txt by using cat command. I started pwn so i spend alot of time to run my code and get shell. I made but my commands was not running after getting shell. The problem was in my this script.

And I was getting this result from my script.

So atlast after spending alot of time because of being a self-learner and not having any friend or teacher. I solved it and took a long breath of happiness.

The problem was in padding. `padding = b"A" * (0x40 - 0x08)` if you know the buffer size and offset. This is the better approach because it dynamically calculates the padding and is more maintainable. And this solved my problem. And the movement of truth…..

Hurrah….!!! Solved …

I love ctf. And I know you also. I love to have you my friend.

In Github , Facebook , Instagram

---
