# [Super SSH](https://play.picoctf.org/practice/challenge/424)

## Overview

**Points**: 25

**Category**: [General Skills](../)

## Description

Using a Secure Shell (SSH) is going to be pretty important.
Can you `ssh` as `ctf-player` to `titan.picoctf.net` at port `<port>` to get the flag? You'll also need the password `84b12bae`. If asked, accept the fingerprint with `yes`.

If your device doesn't have a shell, you can use: https://webshell.picoctf.org

If you're not sure what a shell is, check out our Primer: https://primer.picoctf.com/#_the_shell

## Hints

1. <https://linux.die.net/man/1/ssh>
2. You can try logging in 'as' someone with `<user>`@titan.picoctf.net
3. How could you specify the port?
4. Remember, passwords are hidden when typed into the shell

## Solution

The formula for ssh is `ssh <user>@<host> -p <port>`. We can use this to connect to the server.

Then, enter `yes` to accept the fingerprint. Finally, enter the password so that we can get the flag. Remember that the password is hidden when typed into the shell.

```bash
ssh ctf-player@titan.picoctf.net -p <port>
```

## Flag

`picoCTF{s3cur3_c0nn3ct10n_07a987ac}`
