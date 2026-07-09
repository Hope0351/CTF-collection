# Crabshell


Attachment: [crabshell](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Writeup

When running the binary, I can see it is expecting a 16 bytes key:  



Giving it 16 bytes, we get a different error:  



This is a rust binary so I started with the Main function:  



Going deeper into it, I can see it is making multiple checks on the user input:  



After it checks to ensure it gets 16 bytes, it makes multiple comparisons to see if the input is its valid key.



The first byte it is expecting is `1`. That's `31` in hex. The following 2-8th bytes are `261f2d233117221f` after reversing it to account for the endianness. From the 9th byte we need these values `32136864`. Again reversed because of endianness. The last 3 bytes are `d` = `64` and `h` twice = `68`.

After making these comparisons, there are other MD5 calculations it does however I should have all I need. Putting the entire thing together, I get a 32 bytes MD5 hash which I hex decode and pass to the binary.

```bash
echo -n '31261f2d233117221f32136864646868'|xxd -r -p|./crabshell
```



flag{cc811d4486decc3379dd13688a46603f}
