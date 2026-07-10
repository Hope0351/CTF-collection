# :locked_with_key: Unlocking with Cryptography | CTF Newbies

---

# Unlocking with Cryptography | CTF Newbies

In the realm of cybersecurity, cryptography stands as the fortress guarding the secrets of digital communication. As technology advances and our world becomes increasingly interconnected, the need to protect sensitive information has never been more critical. Cryptography serves as the cornerstone of this defense, employing mathematical algorithms and encryption techniques to secure data transmission and storage.

- Encryption: Cryptography uses encryption techniques to convert plaintext data into ciphertext, rendering it unreadable to unauthorized users.

- Confidentiality: It ensures that only authorized parties can access and decipher encrypted data, maintaining confidentiality in digital communications and transactions.

- Integrity: Cryptography verifies the integrity of data by detecting any unauthorized alterations or tampering attempts during transmission or storage.

- Authentication: It provides methods for verifying the identity of parties involved in communication, ensuring that they are who they claim to be.

- Digital Signatures: Cryptography facilitates the creation and verification of digital signatures, which ensure the authenticity and integrity of digital documents or messages.

- Secure Communication: It forms the foundation of secure communication protocols such as SSL/TLS, SSH, and VPNs, protecting data transmitted over networks from eavesdropping and interception.

## PREREQUISITES:

To effectively solve cryptography-based challenges in Capture The Flag (CTF) competitions, you’ll need a combination of knowledge and skills in various areas. Here’s a list of prerequisites:

- Basic Cryptography Concepts: Understanding fundamental cryptographic concepts such as encryption, decryption, hashing, symmetric and asymmetric encryption, key exchange protocols, digital signatures, etc., is essential.

- Mathematics: A basic understanding of mathematics, including modular arithmetic, number theory, probability theory, and algebra, is crucial for understanding many cryptographic algorithms.

- Programming Skills: Proficiency in at least one programming language (preferably Python, C, or C++) is necessary for implementing and analyzing cryptographic algorithms, as well as for scripting solutions to automate certain tasks.

- Knowledge of Cryptographic Algorithms: Familiarity with common cryptographic algorithms like AES, RSA, Diffie-Hellman, ECC (Elliptic Curve Cryptography), SHA, MD5, etc., is important. You should know how these algorithms work, their strengths, weaknesses, and common attack vectors.

- Understanding of Cryptanalysis Techniques: Knowledge of various cryptanalysis techniques such as frequency analysis, brute-force attacks, chosen-plaintext attacks, known-plaintext attacks, etc., is necessary to break cryptographic systems.

- Understanding of Encoding and Hashing: Familiarity with different encoding schemes like Base64, Base32, hexadecimal, etc., as well as hashing algorithms like MD5, SHA-1, SHA-256, etc., is important since these are frequently used in CTF challenges.

- Experience with Cryptographic Tools: Familiarity with cryptographic tools and libraries such as OpenSSL, Cryptool, CrypTool 2, PyCrypto, Cryptography library in Python, etc., can be beneficial for analyzing and implementing cryptographic solutions.

- Continuous Learning: Cryptography is a rapidly evolving field, so being open to learning new concepts, staying updated with the latest developments, and practicing regularly are crucial for success in CTF competitions.

### RSA —

RSA (Rivest-Shamir-Adleman) is a widely used encryption algorithm for secure data transmission. Rotating RSA could involve key rotation practices.

Key rotation is a security best practice that involves regularly replacing cryptographic keys with new ones. it will only expose a limited amount of data.

In the context of RSA, rotating keys could involve generating new key pairs periodically and replacing the old ones.

### AES —

The Advanced Encryption Standard (AES) is a widely used symmetric encryption algorithm. It operates on fixed-size blocks of data (128 bits in AES), employing keys of varying lengths (128, 192, or 256 bits). AES replaces the older Data Encryption Standard (DES) and provides stronger security.

AES serves as a critical tool in ensuring data security and confidentiality across various applications and industries.

### Hashing —

In cybersecurity, hashing is a process that converts plaintext passwords or any data into a fixed-length string of characters using a cryptographic hashing algorithm. Common hashing algorithms include MD5, SHA-1, SHA-256, and bcrypt.

### Hash Cracking Techniques:-

- Password Hashing: Websites and applications often store user passwords in hashed form rather than plaintext to enhance security.

- Brute Force Attack: This involves trying every possible combination until the correct one is found. While it’s not efficient for longer passwords or complex hash functions, it’s a fundamental technique.

- Dictionary Attack: Uses a predefined list of common passwords or dictionary words to attempt to crack hashes. It’s faster than brute force and targets common passwords first.

- Rainbow Table Attack: Precomputed tables containing hash values for a large number of possible plaintext passwords.

- Hybrid Attack: Combines elements of brute force, dictionary, and rule-based attacks to optimize the cracking process.

- Tools: There are various tools available for hash cracking, such as Hashcat, John the Ripper, and Cain & Abel.

## CRYPTOGRAPHY TOOLS FOR CTF:

### 1. OpenSSL:

- Description: OpenSSL is a robust, open-source implementation of the SSL and TLS protocols, along with a full-strength cryptography library.

- Features: It provides various cryptographic functions, including symmetric encryption (e.g., AES), asymmetric encryption (e.g., RSA), hashing algorithms (e.g., MD5, SHA), digital signatures, key generation, SSL/TLS protocols, and more.

- Usage: OpenSSL is often used for secure communication, cryptographic operations, certificate management, and cryptographic analysis.

- Here are some common commands and functionalities that might be used in CTF challenges involving OpenSSL:

- Generating RSA Keys:

- Extracting Public Key from Private Key:

- Encrypting/Decrypting Base64:

- Creating and Verifying Message Authentication Codes(MAC):

### 2. Cryptool:

- Description: Cryptool is an open-source cryptography and cryptanalysis software that provides a graphical user interface (GUI) for analyzing and understanding cryptographic algorithms.

- Features: It offers tools for experimenting with cryptographic algorithms, visualizing encryption/decryption processes, analyzing ciphers, performing cryptanalysis, and educational purposes.

- Usage: Cryptool is widely used in educational settings, cryptographic research, and by security professionals for understanding and analyzing cryptographic algorithms.

### 3. CrypTool 2:

- Description: CrypTool 2 is an open-source cryptography and cryptanalysis software, which is an improved and extended version of Cryptool.

- Features: Similar to Cryptool, CrypTool 2 provides a GUI for experimenting with cryptographic algorithms, analyzing ciphers, performing cryptanalysis, and educational purposes. It includes additional features and improvements over Cryptool.

- Usage: CrypTool 2 is used for educational purposes, cryptographic research, and by security professionals for understanding and analyzing cryptographic algorithms.

### 4. PyCrypto:

- Description: PyCrypto is a collection of cryptographic algorithms and protocols implemented in Python.

- Features: It provides various cryptographic functions, including symmetric encryption (e.g., AES), asymmetric encryption (e.g., RSA), hashing algorithms (e.g., MD5, SHA), digital signatures, and more, all implemented in Python.

- Usage: PyCrypto is often used for implementing cryptographic solutions, writing cryptographic scripts, performing cryptographic operations in Python-based applications, and cryptographic experimentation.

- Here are some common commands and functionalities that might be used in PyCrypto during CTF challenges:

- Symmetric Encryption/Decryption:

- Asymmetric Encryption/Decryption:

These tools offer a wide range of capabilities for cryptographic analysis, experimentation, implementation, and education, catering to different user needs and preferences.

### 5. Dcode —

It is an online tool that can be used to identify/recognize the type of encryption/encoding applied to a message (more 200 ciphers/codes are detectable). Cipher identifier to quickly decrypt/decode any text.

## Get HackTheBox SRMIST’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

[https://www.dcode.fr/cipher-identifier](https://www.dcode.fr/cipher-identifier)

### 6. CyberChef —

CyberChef is a simple, intuitive web app for carrying out all manner of “cyber” operations within a web browser. These operations include simple encoding like XOR or Base64, more complex encryption like AES, DES and Blowfish, creating binary and hexdumps, compression and decompression of data, calculating hashes and checksums, IPv6 and X.509 parsing, changing character encodings, and much more.

## Practical, real-life usage:

How to Encrypt / Decrypt files using OpenSSL

```
openssl aes-256-cbc -base64 -salt -pbkdf2 -in secrets.txt -out secrets.txt.enc
```

CBC standard for Cipher Block Chaining

256 States the bit key length

AES stands for Advanced encryption standard

This flag commands openssl to output data in base64 encryption

This option instructs OpenSSL to use a salt when generating the encryption key.

This option specifies the use of the PBKDF2 (Password-Based Key Derivation Function 2) algorithm for key derivation

This specifies the input file to be encrypted, in this case, secrets.txt.

This specifies the output file where the encrypted data will be written, in this case, secret.txt.enc

```
openssl aes-256-cbc -d -base64 -pbkdf2 -in secret.txt.enc -out secrets.txt.new
```

CBC standard for Cipher Block Chaining

256 States the bit key length

AES stands for Advanced encryption standard

-d: This option indicates that OpenSSL should decrypt the input data

This flag commands openssl to output data in base64 encryption

This option specifies the use of the PBKDF2 (Password-Based Key Derivation Function 2) algorithm for key derivation

This specifies the output file where the decrypted data will be written, in this case, secret.txt.new

This specifies the input file to be decrypted, in this case, secrets.txt.enc

## Solving a Crypto category CTF problem —

Question Description:

*In the realm of communication, RSA is one of the techniques (in cryptography) to secure communication via the Internet. so to solve the given Cipher text “C” which is in RSA I have provided you with the two keys one is the private key and another is the public key. in RSA you can encrypt a message using any of the keys but to decrypt you need to use the other one(the one that is not used for the encryption).THE TEXT FILE CONTAINS THE CIPHER TEXT(FLAG) WITH RSA MATHEMATICSflag_format = HTBSRMIST{flag_here}.*

## Given instructions in the text file :-

step 1: assume two prime numbers P and Q .

step 2: calculate N which is P X Q (multiplication of P and Q).

step 3: calculate ƛ(n) which LCM(P-1, Q-1) .

step 4: choose any random value between 2 to ƛ(n) which is e. e also should be coprime with ƛ(n).

step 5: now let’s calculate d which is the modular multiplicative inverse of e modulo ƛ(n) or d = (e)^-1(modƛ(n)).

public key is the pair of (N,e)

private key is the pair of(N,d)

Cipher text = message^e(mod n)

Message text = cipher^d(mod n)

we start writing a Python script to solve this.

```
public_key = (3233, 2753)
```

we define a *public_key* tuple where 3233 is the large integer used in RSA encryption (N)

```
message = [3000, 2159, 524, 2680, 1859, 3123, 1486, 2680, 2159, 855, 99, 624, 2160, 119, 641, 2412, 529, 281, 597, 368, 1759, 119, 2653, 2170, 368, 119, 1859, 1802, 529, 1516]
```

with this line, we initialize a list having ASCII values of characters of the message

```
N, e = public_key
```

We now unpack the *public_key* tuple into two variables N and e,

now N = 3233 ; e= 2753

```
cipher_text = [(m  e) % N for m in message]
```

we now iterate over each integer m in the message list, which then computes its encryption using the RSA algorithm.

```
ascii_text = ''.join(chr(c) for c in cipher_text)
```

Here we convert the list of integers into a string by iterating over each integer c in *cipher_text* and converts to a character using *the chr()* function.

```
print(ascii_text)
```

finally, we print the string.

The complete code is as follows:

```
public_key = (3233, 2753)
message = [3000, 2159, 524, 2680, 1859, 3123, 1486, 2680, 2159, 855, 99, 624, 2160, 119, 641, 2412, 529, 281, 597, 368, 1759, 119, 2653, 2170, 368, 119, 1859, 1802, 529, 1516]
N, e = public_key
cipher_text = [(m  e) % N for m in message]
ascii_text = ''.join(chr(c) for c in cipher_text)
print(ascii_text)
```

Output:

```
FLAG : HTBSRMIST{Y0u_Cr4cK3D_7h3_R54}
```

### Contribution —

Suyash Jain

Bhavya Agarwal

Nishchay Manhas

Devansh Gupta

---
