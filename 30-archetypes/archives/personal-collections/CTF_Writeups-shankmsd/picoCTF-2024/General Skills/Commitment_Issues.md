## Challenge 🧩

I accidentally wrote the flag down. Good thing I deleted it!

Author: JEFFERY JOHN</br>
Points: 50

Hints:

1. Version control can help you recover files if you change or lose them!
2. Read the chapter on Git from the picoPrimer [here](https://primer.picoctf.org/#_git_version_control)
3. You can 'checkout' commits to see the files inside them

## Solution 🕵️‍♂️

The .git folder has all the commit history and thus can be used to reconstruct the commits.

I used GitTools Extractor to reconstruct the commits.

```bash
┌──(user㉿shell)-[~]
└─$ ./extractor.sh drop-in commitIssues
```

the flag is in `message.txt`

```text
-picoCTF{s@n1t1z3_xxxxxxxx}
+TOP SECRET
```

Tool Used: </br>
GitTools Extractor

## Flag 🚩

`picoCTF{s@n1t1z3_xxxxxxxx}`
