# :game_die: Hack The Box Cyber Santa CTF 2021 — Common Mistake

---

# Hack The Box Cyber Santa CTF 2021 — Common Mistake

*Cyber Santa Capture The Flag*

From the Crypto Category of Cyber Santa Is Coming To Town CTF which was going on from December 1st to December 5th 2021, there was a challenge called “Common Mistake”. let’s solve this challenge

## Get Aydin Naserifard’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Take a look at the challenge description:

*challenge description*

let’s cat encrypted.txt file, as you can see, we have the same modulus and two different encryption values and ciphertexts Which leads to the Common Modulus attack.

*encrypted file content*

Generate the first public key using (‘n’ and the 1st ‘e’ value):

*key1.pub*

Generate the second public key using (the same ‘n’ and the 2nd ‘e’ value):

*generate first public key using (n and 1st e):key2.pub*

Generate Base64 encoded form of the first cipher text using [rsa-cm.py](https://github.com/HexPandaa/RSA-Common-Modulus-Attack)

*c1.b64*

Generate Base64 encoded form of the second cipher text using [rsa-cm.py](https://github.com/HexPandaa/RSA-Common-Modulus-Attack)

*c2.b64*

Run the script to perform common modulus attacks on RSA to recover the plaintext of the message:

*flag*

and we get the flag: HTB{c0mm0n_m0d_4774ck_15_4n07h3r_cl4ss1c}

hope you enjoyed this write-up…

---
