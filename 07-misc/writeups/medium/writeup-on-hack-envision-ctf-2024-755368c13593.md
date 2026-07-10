# :game_die: OUTPUT

---

The characters appear to be in decimal format. Converting them to ASCII could provide us with a valuable string.

Indeed, that is accurate; we obtained a message after applying the conversion using the following code.

```
characters = [65, 83, 67, 73, 73, 0, 0, 0, 84, 104, 101, 32, 108, 105, 116, 116, 108, 101, 32, 98, 111, 121, 32, 102, 114, 111, 109, 32, 82, 111, 115, 97, 114, 105, 111, 44, 32, 83, 97, 110, 116, 97, 32, 70, 101, 44, 32, 104, 97, 115, 32, 106, 117, 115, 116, 32, 112, 105, 116, 99, 104, 101, 100, 32, 117, 112, 32, 105, 110, 32, 104, 101, 97, 118, 101, 110, 46, 32, 72, 101, 32, 99, 108, 105, 109, 98, 115, 32, 105, 110, 116, 111, 32, 97, 32, 103, 97, 108, 97, 120, 121, 32, 111, 102, 32, 104, 105, 115, 32, 111, 119, 110, 46, 32, 72, 101, 32, 104, 97, 115, 32, 104, 105, 115, 32, 99, 114, 111, 119, 110, 105, 110, 103, 32, 109, 111, 109, 101, 110, 116, 32, 97, 110, 100, 32, 111, 102, 32, 99, 111, 117, 114, 115, 101, 32, 104, 101, 32, 105, 115, 32, 110, 111, 116, 32, 97, 108, 111, 110, 101, 46, 32, 32]
print("".join([chr(c) for c in characters]))
# OUTPUT
# ASCIIThe little boy from Rosario, Santa Fe, has just pitched up in heaven. He climbs into a galaxy of his own. He has his crowning moment and of course he is not alone.
```

Upon google search, based on the above phrase, we discovered that it was spoken by Peter Drury. Therefore, our flag can be derived as quarkCTF{peter_drury}.

FLAG: quarkCTF{peter_drury}

---
