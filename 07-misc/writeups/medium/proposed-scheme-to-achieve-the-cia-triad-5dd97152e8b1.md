# :game_die: Medium

---

***B. User Authentication:***

User authentication is about ensuring that the data is indeed sent from the user claiming to have sent it, such that no other person can impersonate them.We hashed our message then we encrypted it using the sender’s private key. **This key is top secret; it is only known by the sender.**

*Asymmetric encryption* has many applications but in the proposed model it is used to achieve the user identity by using Digital Signatures.

If I go to the bank pretending to be you, having all credentials of your account. I ask the bank to withdraw some money. Then the teller took the required
documents from me. Now, I think I am done with my steal job. At last, the teller will ask me to sign the paper to be sure that I am the right person. I could have your credentials, your info, **but your signature?** *No, it is not possible.*

In the world of *communication network*, Digital signatures are the same as your handwritten signature in real life. **No one can forge it!**

## Get Mohamed Mostafa’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Every peer on the network has *two *keys;** Public Key** which all pears know it and **Private Key** which his owner only knows it.

*Golden rule*: What is encrypted using the public key is **only **could be decrypted by the corresponding private key and vice versa!

*At the sender side,* I am encrypting the hashed data with the sender’s
private key, ***who knows it?*** *Only his owner (the sender).*

*At the receiver side,* the receiver will try to decrypt this encrypted hashed data which is encrypted with the sender’s private key. **Guess how could this message be decrypted?**

*No key will decrypt it but the corresponding public key!*

If the receiver decrypts it s**uccessfully** using *the known sender’s public key*, so the receiver is now sure that the peer he/she is communicating with is the desired one and **is not **an attacker who is trying to pretend that he/she is the desired sender.

***C. Message Authentication (Data integrity):***

This feature could be achieved using *Cryptographic Hash Function*.

It is an algorithm for which it is *computationally infeasible* (because no attack is significantly more efficient than brute force) to find either
1. A data object that maps to a pre-specified hash result (*the one-way property).*
2. Two data objects that map to the same hash result *(the collision-free property).*
**Because of these characteristics,** hash functions are often used to *determine
whether or not data has changed.*

*Our data is top secret*, so we do not want an intruder to intercept it and read it, **okay?**

But, what if there is an intruder who performs a MITM attack (or Women in the middle attack) for the sake of gender equality :) ?

*Now the attacker is smarter than before*, he/she will intercept the data, read it, modify it, then he/she will send it to the receiver. For example, *using a replay attack,*** so how will the receiver be sure that the data is not manipulated?**
Here, The role of Hashing Algorithms (we use here SHA3) appears.
*It assures that our info has not been modified.*

**So, how this is achieved in the proposed scheme?**

*At the sender side,* I hashed our data then encrypted it using **the sender’s private key ***(for the sake of USER AUTHENTICATION)*, then concatenated the plain text data with the encrypted hashed data, then encrypted the concatenation using the symmetric key. **Please look at the graph to imagine it!**

*At the receiver side*, First, he/she decrypts the whole block using **the symmetric key**. Then, splits the block into *two* parts. The first part is the plain text data and the second part is the encrypted hashed data.

He/She takes *the part of the encrypted hashed data,* decrypt it using the **sender’s public key** (REMEMBER!, USER AUTHENTICATION IS VERIFIED HERE) and *in parallel,* he/she takes *the plain text* data and hashes it using the *same hashing algorithm* used in the sender side (here I use SHA3).

Finally, he/she **compares** the two parts after these two parallel processes.* If they are the same,* then,** BINGO! Our message has not been manipulated.**

Note: This work is a part of a published research paper which I was one of the research team who published it.

Wassim Alexan, Mohamed Moustafa, Ahmed Ashraf, Eyad Mamdouh, and Sarah Mohamed. “IoMT Security: SHA3‑512, AES‑256, RSA and LSB Steganography”. In: 2021 8th NAFOSTED Conference on Information and Computer Science (NICS), and IEEE Xplore.

---
