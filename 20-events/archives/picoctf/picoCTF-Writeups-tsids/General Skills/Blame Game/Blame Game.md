# [Blame Game](https://play.picoctf.org/practice/challenge/405)

## Overview

**Category**: [General Skills](../)

**Difficulty**: Easy

**Event**: picoCTF 2024

## Description

Someone's commits seems to be preventing the program from working. Who is it?
You can download the challenge files here:
- [challenge.zip](https://artifacts.picoctf.net/c_titan/72/challenge.zip)

## Hints

1. In collaborative projects, many users can make many changes. How can you see the changes within one file?
2. Read the chapter on Git from the picoPrimer [here](https://primer.picoctf.org/#_git_version_control).
3. You can use `python3 <file>.py` to try running the code, though you won't need to for this challenge.

## Solution

We can find the name of the authors who made changes to `message.py` using the `git blame <file>` command.

```sh
git blame message.py
```

Alternatively, to list all the authors, use 

```sh
git log --pretty="%an" -- message.py | sort | uniq
```

- `--pretty="%an"` formats the output to print only the author name (`%an` stands for "author name")
- `sort` sorts the names
- `uniq` removes duplicates

## Flag

`picoCTF{@sk_th3_1nt3rn_b64c4705}`
