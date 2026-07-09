# [Binary Search](https://play.picoctf.org/practice/challenge/442)

## Overview

**Category**: [General Skills](../)

**Difficulty**: Easy

**Event**: picoCTF 2024

## Description

Want to play a game? As you use more of the shell, you might be interested in how they work! Binary search is a classic algorithm used to quickly find an item in a sorted list. Can you find the flag? You'll have 1000 possibilities and only 10 guesses.
Cyber security often has a huge amount of data to look through - from logs, vulnerability reports, and forensics. Practicing the fundamentals manually might help you in the future when you have to write your own tools!
You can download the challenge files here:
- [challenge.zip](https://artifacts.picoctf.net/c_atlas/19/challenge.zip)


## Hints

1. Have you ever played hot or cold? Binary search is a bit like that.
2. You have a very limited number of guesses. Try larger jumps between numbers!
3. The program will randomly choose a new number each time you connect. You can always try again, but you should start your binary search over from the beginning - try around 500. Can you think of why?

## Solution

Binary search works by repeatedly dividing in half the portion of the list that could contain the item, until you've narrowed down the possible locations to just one.

Here's a tool you can use to visualize binary search: https://binary-search-visualization.netlify.app/


For example, to guess a number between 0 and 1000, you would start by guessing $\frac{(0 + 1000)}{2} = 500$. 

If the number is higher than 500, you would guess $\frac{(500 + 1000)}{2} = 750$. 

If the number is lower than 500, you would guess $\frac{(0 + 500)}{2} = 250$.

Continue with this process until you find the number.

## Flag

`picoCTF{g00d_gu355_1597707f}`
