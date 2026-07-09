# [Commitment Issues](https://play.picoctf.org/practice/challenge/411)

## Overview

**Points**: 50

**Category**: [General Skills](../)

## Description

I accidentally wrote the flag down. Good thing I deleted it!
You download the challenge files here:
- [challenge.zip](https://artifacts.picoctf.net/c_titan/137/challenge.zip)

## Hints

1. Version control can help you recover files if you change or lose them!
2. Read the chapter on Git from the picoPrimer [here](https://primer.picoctf.org/#_git_version_control)
3. You can 'checkout' commits to see the files inside them

## Solution

After downloading the zip file, extract it and navigate to the `drop-in` directory. You will find a `.git` directory. This means that the directory is a git repository. Use the `git` command to interact with the repository.

Run `git log` to see the commit history. Notice that there are two commits. Run `git checkout <commit-hash>` to checkout to the commit when the flag was created. Then, `cat` the contents of `message.txt` to see the flag.

```bash
$ git log
commit ef0b7cc6b98367fa168573c931e0f7098ef59182 (HEAD -> master)
Author: picoCTF <ops@picoctf.com>
Date:   Tue Mar 12 00:06:20 2024 +0000

    remove sensitive info

commit ea859bf3b5d94ee74ce5ee1afa3edd7d4d6b35f0
Author: picoCTF <ops@picoctf.com>
Date:   Tue Mar 12 00:06:20 2024 +0000

    create flag


$ git checkout ea859bf3b5d94ee74ce5ee1afa3edd7d4d6b35f0
$ cat message.txt
picoCTF{s@n1t1z3_cf09a485}
```

To return back to the original commit, run `git switch -`.

## Flag

`picoCTF{s@n1t1z3_cf09a485}`
