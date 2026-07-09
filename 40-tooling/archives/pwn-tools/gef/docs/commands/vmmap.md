## Command `vmmap`

`vmmap` displays the target process's entire memory space mapping.

![vmmap](https://raw.githubusercontent.com/hugsy/gef/refs/heads/main/docs/assets/images/vmmap.png)

Interestingly, it helps finding secret gems: as an aware reader might have seen, memory mapping
differs from one architecture to another (this is one of the main reasons I started `GEF` in a first
place). For example, you can learn that ELF running on SPARC architectures always have their `.data`
and `heap` sections set as Read/Write/Execute.

`vmmap` can accept multiple arguments, either patterns to match again mapping names, or addresses
to determine which section it belongs to:

1.  `-a` / `--addr`:
    -  filter by address -> parses the next argument as an integer or asks gdb to interpret the value
2.  `-n` / `--name`:
    -  filter based on section name
3.  If nothing is specified, it prints a warning and guesses the type

![vmmap-grep](../../../../../../40-tooling/archives/pwn-tools/gef)

![vmmap-address](../../../../../../40-tooling/archives/pwn-tools/gef)

The address can be also be given in the form of a register or variable.

![vmmap-register](../../../../../../40-tooling/archives/pwn-tools/gef)

And you can do all of them in one command 🙂

![vmmap-all-in-one](../../../../../../40-tooling/archives/pwn-tools/gef)
