# :locked_with_key: Cryptography essential for H4CK3Rs and CTF players 0x1(encoding).

> **Original Source:** [Cryptography essential for H4CK3Rs and CTF players 0x1(encoding).](https://infosecwriteups.com/cryptography-essential-for-h4ck3r-and-ctf-player-0x1-encoding-b638ab5821a9)
> **Platform:** infosecwriteups.com | **Category:** `CRYPTO`

---

# Cryptography essential for H4CK3Rs and CTF players 0x1(encoding).


*Photo by [sippakorn yamkasikorn](https://unsplash.com/@sippakorn?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*


Hello dear hackers in this series we will teach you basic concept of cryptography which is very helpful during CTF competition and hacking challenge and also cybersecurity exam and interview.

### What is Cryptography?


Cryptography is the practice and study of techniques for secure communication in the presence of third parties, simply It is a process of converting data into unreadable format to protect data from unauthorized people.

### Why it is important?


Just because data is everything of any person, so if we want to protect it from malicious user or unintended person. then it is compulsory to protect our data, And also to maintain confidentiality of CIA trade.

### Basic term:


- Cipher: an algorithm for performing encryption or decryption.

- Plaintext: The unencrypted or “original” message.

- Ciphertext: The encrypted message.

- Key: a piece of information that specifies the transformation of plaintext into ciphertext, and vice versa for decryption algorithms.


*Photo by [Jake Johnson](https://unsplash.com/@iakeiohnson?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

## Encoding:


Encoding is the process of storing data. It is just like translation of data.Different computer systems operate with different forms of encoding like different people use different languages. Just like languages have specific alphabets, encodings have alphabets of their own.


>> Same data can be encoded into various forms. <<


Base: The total number of unique elements we can use to represent data in an encoding format.

## Some common encoding format:


### ASCII : American Standard Code for information interchange


- Every character,digit,number and a symbol has a unique ascii code.

- “a-z” => 97–122

- “A-Z” => 65–90

- “0–9” => 48–57

### Base 2 (Binary) : 0 ,1


It is most basic and widely used encoding, all computers and approx all digital microprocessor devices use this encoding to process data and many things.


## Get Vicky Aryan’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


It has only two unique base or numbers which one is 0 and second one is 1 that’s why we call it base 2 encoding or binary. Very easy to decode it.

>

`ASCII: This is some ASCII text, and I like it very much.`


`Binary:01010100 01101000 01101001 01110011 00100000 01101001 01110011 00100000 01110011 01101111 01101101 01100101 00100000 01000001 01010011 01000011 01001001 01001001 00100000 01110100 01100101 01111000 01110100 00101100 00100000 01100001 01101110 01100100 00100000 01001001 00100000 01101100 01101001 01101011 01100101 00100000 01101001 01110100 00100000 01110110 01100101 01110010 01111001 00100000 01101101 01110101 01100011 01101000 00101110`


Tool for decode: [https://www.binaryhexconverter.com/binary-to-ascii-text-converter](https://www.binaryhexconverter.com/binary-to-ascii-text-converter)

### Base 16 (Hex): [0–9,a-f]


Base 16 encoding uses the hexadecimal number system (0123456789ABCDEF) to encode text.

>

`ASCII: Hey! This is an example of base16 encoding.
HEX:48657921205468697320697320616E206578616D706C65206F662062617365313620656E636F64696E672E`


Tool for decode: [https://www.rapidtables.com/convert/number/hex-to-ascii.html](https://www.rapidtables.com/convert/number/hex-to-ascii.html)

### Base 32 : [A-Z,2–7]


Base 32 is very similar to base16 encoding but it has a larger alphabet, and uses padding characters (equals signs).

>

`ASCII: Hey! This is an example of base32 encoding.
Base 32: JBSXSIJAKRUGS4ZANFZSAYLOEBSXQYLNOBWGKIDPMYQGEYLTMUZTEIDFNZRW6ZDJNZTS4===`


Hint: Some identifying characteristics of base32 encoding are the padding characters (equal signs) and the upper-case and numeric alphabet.


This is a tool you can use to encode and decode base32: [https://simplycalc.com/base32-encode.php](https://simplycalc.com/base32-encode.php)

## Base 64:[A-Z,a-z,0–9,+,/]


Base 64 is similar to base32, but it has an even larger alphabet! It also uses padding characters.

>

`ASCII: Hey! This is an example of base64 encoding.
Base 64: SGV5ISBUaGlzIGlzIGFuIGV4YW1wbGUgb2YgYmFzZTY0IGVuY29kaW5nLg==`


Hint: The identifying features of base64 encoding are the upper and lower case alphabet, use of numbers, and message padding (equals signs at the end of the string).


This is a tool you can use to encode and decode base64: [https://simplycalc.com/base64-encode.php](https://simplycalc.com/base64-encode.php)


*Photo by [Chang Duong](https://unsplash.com/@iamchang?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*

## URL Encoding (Percent-Encoding)


URL encoding is a standard used to encode specific data or characters in URLs.

>

`ASCII: Hey! This is an example of URL or Percent Encoding.
URL encoded: Hey!%20This%20is%20an%20example%20of%20URL%20or%20Percent%20Encoding.%0A`


Hint:The identifying feature of URL encoding is the usage of percentage signs and some plaintext (although there is base64 and base32 URL encoding).


Tool for encoding and decoding URL or Percent Encoding: [https://meyerweb.com/eric/tools/dencoder/](https://meyerweb.com/eric/tools/dencoder/)

### H4ck3r Tip:


You can use father of tools in cryptography: [https://gchq.github.io/CyberChef/](https://gchq.github.io/CyberChef/)


Happy Hacking Hackers.

---

*Originally published on [Medium](https://infosecwriteups.com/cryptography-essential-for-h4ck3r-and-ctf-player-0x1-encoding-b638ab5821a9). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
