# [Time Machine](https://play.picoctf.org/practice/challenge/425)

## Overview

**Points**: 50

**Category**: [General Skills](../)

## Description

What was I last working on? I remember writing a note to help me remember...
You can download the challenge files here:
- [challenge.zip](https://artifacts.picoctf.net/c_titan/67/challenge.zip)

## Hints

1. The `cat` command will let you read a file, but that won't help you here!
2. Read the chapter on Git from the picoPrimer [here](https://primer.picoctf.org/#_git_version_control).
3. When committing a file with git, a message can (and should) be included.

## Solution

Unzip the challenge and navigate to the the `drop-in` directory. There you will find a `.git` directory. This means that the directory is a git repository. You can use the `git log` command to see the commit history.

```bash
$ git log
commit b92bdd8ec87a21ba45e77bd9bed3e4893faafd0f (HEAD -> master)
Author: picoCTF <ops@picoctf.com>
Date:   Sat Mar 9 21:10:29 2024 +0000

    picoCTF{t1m3m@ch1n3_5cde9075}
```

## Flag

`picoCTF{t1m3m@ch1n3_5cde9075}`