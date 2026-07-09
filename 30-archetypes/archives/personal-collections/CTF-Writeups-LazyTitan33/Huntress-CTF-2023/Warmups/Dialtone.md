# Dialtone

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
Listening to the audio file, we can tell it is a recording of DTMF. There are tools that can decode such files. An example we used can be found here:  
tmf-decoder
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We get this data:
```
13040004482820197714705083053746380382743933853520408575731743622366387462228661894777288573
```
It was a struggle figuring out what to do with it. A quick glance my indicate it's hex data but it's not since it's unlikely for such large data to not have a letter in it. It is more likely for it to be a `BigInt`, just a big number so we can google for decoders online:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We tested this online tool:  
https://www.mobilefish.com/services/big_number/big_number.php

After some experiments on what to convert it to, we find we get a valid value for `decimal` to `hexadecimal`:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can hex decode this to get the flag:

```bash
echo 666C61677B36633733336566303962633466326134333133666636333038376532356436377D|xxd -r -p
```

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{6c733ef09bc4f2a4313ff63087e25d67}

