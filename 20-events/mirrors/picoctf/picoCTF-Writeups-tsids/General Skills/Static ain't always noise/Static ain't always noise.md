# [Static ain't always noise](https://play.picoctf.org/practice/challenge/163)

## Overview

**Points**: 20

**Category**: [General Skills](../)

## Description

Can you look at the data in this binary: [static](./static)? This [BASH script](./ltdis.sh) might help!

## Hints

None

## Solution

Turn the `ltdis.sh` file into an executable by running `chmod +x ltdis.sh`, then run the file using `./ltdis.sh`.

```sh
>>> ./ltdis.sh
Attempting disassembly of  ...
objdump: 'a.out': No such file
objdump: section '.text' mentioned in a -j option, but not found in any input file
Disassembly failed!
Usage: ltdis.sh <program-file>
Bye!
```

You'll see that the program requires an additional file as an argument. Run it again using `static` as the argument file, (`./ltdis.sh static`). The flag will be in the `static.ltdis.strings.txt` file.

## Flag

`picoCTF{d15a5m_t34s3r_f6c48608}`
