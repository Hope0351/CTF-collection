## Indicium

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Enumeration

We can easily recognize the string above as being Decimal encoding so we can use [cyberchef](https://gchq.github.io/CyberChef/) to decode it:  

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Interestingly enough, we get another string that is not recognized by cyberchef: `gmbh|cc265ceg113b731ec768c9eg95b98175~`

However, we know the flag format needs to start with `flag` but this one starts with `gmbh`. A keen eye would observe that `g` is the next letter after `f`, `m` is one letter after `l`, `b` is `a` + 1 and `h` is `g` + 1.

## Solution

If we apply the same logic to the entire string, we need to decrease 1 from all the letters and we can easily do so with python.

```python
input_string = "gmbh|cc265ceg113b731ec768c9eg95b98175~"
transformed_string = ""

for char in input_string:
    transformed_string += chr(ord(char) - 1)

print(transformed_string)
```
We run it and get the flag.

`flag{bb154bdf002a620db657b8df84a87064}`
