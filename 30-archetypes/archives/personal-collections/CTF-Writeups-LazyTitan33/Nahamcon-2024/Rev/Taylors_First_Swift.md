## Taylors_First_Swift

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Solution

The provided file is not one that I can run however, being an easy one, I don't expect that we need to.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I opened it in Ghidra and noticed some hex strings in the "flagchecky" function:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I copied them into a temporary file called test:  

```text
  *puVar7 = 0x73;
  puVar7[1] = 0x77;
  puVar7[2] = 0x69;
  puVar7[3] = 0x66;
  puVar7[4] = 0x74;
  puVar7[5] = 0x69;
  puVar7[6] = 0x65;
  puVar7[7] = 0x73;
  puVar7[8] = 0x21;
```
And then converted them to ASCII with this one liner:  

```bash
cat test|awk '{print $3}'|tr -d ';' |xxd -r -p
```
It turns out it is the word `swifties!`:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Below that there is a longer one which gets converted similarly to a base64 encoded string:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I noticed a mention of some `XOR` in some other functions:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

So I made an educated guess that the longer string is XORed with the smaller one and tried it in [CyberChef](https://gchq.github.io/CyberChef/#recipe=From_Base64('A-Za-z0-9%2B/%3D',true,false)XOR(%7B'option':'UTF8','string':'swifties!'%7D,'Standard',false)&input=RlJzSUFROFBWQlVWRVJFSVZFUmJCa1VSRmtVSUJ4VlFWa0FZRnhKZlYwRllWa0lWUWdvPQ&ieol=CRLF):  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And we got the flag:  

`flag{f1f4bfa202c60e2aaa9339de61513141}`
