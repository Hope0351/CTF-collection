# PackedAway

## Solution 
Running strings on the provided binary, we can tell it is [UPX](https://upx.github.io/) packed:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can use upx to also unpack it:  
```bash
upx -d packed
```
Now that the binary is unpacked we can run strings on it and grep the flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`HTB{unp4ck3d_th3_s3cr3t_0f_th3_p455w0rd}`
