## Deprecated commands

GEF is in itself a large file, but to avoid it to be out of control some commands once part of GEF
were either moved to GEF-Extras or even simply removed. This
page aims to track those changes.

| Command | Status | Since | Link (if Applicable) | Notes |
| -- | -- | -- | -- | -- |
| `cs-disassemble` | Moved | 2022.06 | New location | Depends on `capstone` |
| `assemble` | Moved | 2022.06 | New location | Depends on `keystone` |
| `emulate` | Moved | 2022.06 | New location | Depends on `unicorn` and `capstone` |
| `set-permission` | Moved | 2022.06 | New location | Depends on `keystone` |
| `ropper` | Moved | 2022.06 | New location | Depends on `ropper` |
| `ida-interact` | Moved | 2022.06 | New location | Depends on `rpyc` |
| `exploit-template` | Moved | c402900 | New location | |
| `windbg` | Moved | a933a5a | New location | |
| `is-syscall` | Moved | 3f79fb38 | New location | |
| `syscall-args` | Moved | 3f79fb38 | New location | |
| `shellcode` | Removed | 2026.06 | N/A | Reason: `http://shell-storm.org` not active |

## Removed support for pyenv

Support for pyenv has been removed after `2024.05`, for more
information see [#1078](../../../../../40-tooling/archives/pwn-tools/gef) and [#1062](../../../../../40-tooling/archives/pwn-tools/gef).
