# minicomputer

minicomputer was a DEF CON 2025 CTF Finals challenge, consisting of 4 "chips" players could interact with, plus a bus manager, a flag device, and the player input device.

## BUILDING

`make` should build the relevant binaries, but this challenge only builds on linux, not macOS, due to sigqueue usage. A dockerfile and xinetd config are also included, though the challenge can be run without issue outside of docker. It does spawn multiple binaries but makes some attempt to prevent them hanging around if one exits.

`-DDEBUG=1` is set by the makefile and enables debug logging. That option was not used for the challenge binaries, and the line used to compile april (zig) is also included, commented out, in the makefile.

## LICENSES

see `licenses.txt` for some included library licenses.
