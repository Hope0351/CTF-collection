# Babel

### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

### Solution
The file provided seems to contain some obfuscated C# code:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I started adjusting the lines to make it more readable for me:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

At a first glance we can see that the first function is applied to the base64blob with the random characters (key) then the blob is Base64 decoded:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I asked ChatGPT to rewrite that function in python3 and then I applied it to the blob and Base64 decoded it. After that, we write the resulted bytes into a file we call "decoded_assembly.dll":

```python3
import base64

def custom_function(t, k):
    bnugMUJGJayaT = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    WgUWdaUGBFwgN = ""
    ornBLfjI = dict(zip(k, bnugMUJGJayaT))

    for char in t:
        if 'A' <= char <= 'Z' or 'a' <= char <= 'z':
            WgUWdaUGBFwgN += ornBLfjI.get(char, char)
        else:
            WgUWdaUGBFwgN += char

    return WgUWdaUGBFwgN


base64_blob = "base64blob";
key = "lQwSYRxgfBHqNucMsVonkpaTiteDhbXzLPyEWImKAdjZFCOvJGrU";

file = base64.b64decode(custom_function(base64_blob, key))

with open("decoded_assembly.dll", "wb") as fp:
        fp.write(file)
```

After we run the script, indeed a .dll file was created and we have a valid file which seems to be a .Net assembly.  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I wanted to check it in dnSpy but first, as always with any CTF challenge, we run strings on it and actually get the flag, no need for further reversing:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{b6cfb6656ea0ac92849a06ead582456c}
