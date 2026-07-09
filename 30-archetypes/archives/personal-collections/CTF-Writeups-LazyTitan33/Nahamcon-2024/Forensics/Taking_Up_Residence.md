## Taking Up Residence

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution

For this challenge we just get a file that is only identified as data:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

However, if we look at it with `xxd` we can see a `FILE0` header:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

A quick google search reminds us that this is an [MFT](https://learn.microsoft.com/en-us/windows/win32/fileio/master-file-table) file:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

A very good tool that allows a grafical viewing of the content of such files is the [MFTViewer](https://ericzimmerman.github.io/). It takes a long time for it to load because of its size, but eventually we have it loaded and find a `flag.txt` and `ransom.py` in the Downloads folder:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

In the bottom right, we can see the ASCII data content of the flag.txt file:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

So we'll save this for later:  

```text
gAAAAABmS9s32v5Ju181EaJhh2vYMsR6MJ31SK-9mDwgiCz3_MBWopjqqynjoY_-HNOw3tX1T3RthBZHz9ylmyqckZ0gUZ_6T7UUxprMHoCAaTV3m1q0weznBg98RL7dRVhRn0cX6Xta
```

For the ransom.py we can see 2 data streams:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Base64 decoding the string in the first data stream we see that it is actually getting the second data stream as the key and using it for a Fernet Encryption:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

```python
from cryptography.fernet import Fernet
import subprocess

key = subprocess.run(["powershell", "-EncodedCommand", "RwBlAHQALQBDAG8AbgB0AGUAbgB0ACAALQBQAGEAdABoACAAIgByAGEAbgBzAG8AbQAuAHAAeQAiACAALQBTAHQAcgBlAGEAbQAgACIAawBlAHkAIgA="], capture_output=True, text=True).stdout.strip()

print(key)
with open('flag.txt', 'r') as reader:
    message = reader.read()
f = Fernet(key)

encrypted_message = f.encrypt(message.encode())
print(encrypted_message)
with open('flag.txt', 'w') as writer:
    writer.write(encrypted_message.decode('ascii'))
```
The second data stream is our key to decrypt the flag:  

```text
62QJTO5dH0xaKgmiVfOFKNYCBMfRiNF5L7rxDChc0SU=
```

Armed with this knowledge we can use [CyberChef](https://gchq.github.io/CyberChef/#recipe=Fernet_Decrypt('62QJTO5dH0xaKgmiVfOFKNYCBMfRiNF5L7rxDChc0SU%3D')&input=Z0FBQUFBQm1TOXMzMnY1SnUxODFFYUpoaDJ2WU1zUjZNSjMxU0stOW1Ed2dpQ3ozX01CV29wanFxeW5qb1lfLUhOT3czdFgxVDNSdGhCWkh6OXlsbXlxY2taMGdVWl82VDdVVXhwck1Ib0NBYVRWM20xcTB3ZXpuQmc5OFJMN2RSVmhSbjBjWDZYdGE) to decrypt it and get our flag:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`flag{a4096cd70d8859d38cf8e7487b4cd0fa}`
