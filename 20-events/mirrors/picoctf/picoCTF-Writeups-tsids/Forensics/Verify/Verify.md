# [Verify](https://play.picoctf.org/practice/challenge/450)

## Overview

**Points**: 50

**Category**: [Forensics](../)

## Description

People keep trying to trick my players with imitation flags. I want to make sure they get the real thing! I'm going to provide the SHA-256 hash and a decrypt script to help you know that my flags are legitimate.
You can download the challenge files here:
- [challenge.zip](https://artifacts.picoctf.net/c_rhea/22/challenge.zip)


The same files are accessible via SSH here:
`ssh -p <port> ctf-player@rhea.picoctf.net`
Using the password `1db87a14`. Accept the fingerprint with `yes`, and `ls` once connected to begin. Remember, in a shell, passwords are hidden!
- Checksum: 55b983afdd9d10718f1db3983459efc5cc3f5a66841e2651041e25dec3efd46a
- To decrypt the file once you've verified the hash, run `./decrypt.sh files/<file>`.


## Hints

1. Checksums let you tell if a file is complete and from the original distributor. If the hash doesn't match, it's a different file.
2. You can create a SHA checksum of a file with `sha256sum <file>` or all files in a directory with `sha256sum <directory>/*`.
3. Remember you can pipe the output of one command to another with `|`. Try practicing with the 'First Grep' challenge if you're stuck!

## Solution

The correct checksum is stored in `checksum.txt`. You can verify files by running `sha256sum <file>` or all files in a directory by running `sha256sum <directory>/*`. 

Run `sha256sum files/*` to get the SHA checksum for each file, then use grep to find the one that matches the original checksum. 

Finally, run `./decrypt.sh files/<file>` to get the flag. 

```bash
ctf-player@pico-chall$ cat checksum.txt 
55b983afdd9d10718f1db3983459efc5cc3f5a66841e2651041e25dec3efd46a
ctf-player@pico-chall$ sha256sum files/* | grep 55b983afdd9d10718f1db3983459efc5cc3f5a66841e2651041e25dec3efd46a
55b983afdd9d10718f1db3983459efc5cc3f5a66841e2651041e25dec3efd46a  files/2cdcb2de
ctf-player@pico-chall$ ./decrypt.sh files/2cdcb2de 
picoCTF{trust_but_verify_2cdcb2de}
```

## Flag

`picoCTF{trust_but_verify_2cdcb2de}`