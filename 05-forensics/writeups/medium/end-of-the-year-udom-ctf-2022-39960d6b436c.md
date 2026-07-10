# :mag: End Of The Year UDOM CTF 2022. Just a few hours before “cd year-2023”…

---

# End Of The Year UDOM CTF 2022

Just a few hours before “cd year-2023” or “sudo apt install year-2023” if you’d prefer, I participated in an awesome [CTF competition](https://ctf.peterlymo.com/) organized by [UDOM CYBER CLUB](https://twitter.com/UdomCyberClub).

I solved a few challenges ranging from: OSINT, Forensics, Cryptography, Steganography to Web. Let’s take a look.

## 1. Cryptography

### Challenge: R54

We are given a ct.txt file and a challenge.py file that is supposed to help us get the flag. This is what was in the files.

*ct.txtchallenge.py*

As you know RSA algorithm is an asymmetric cryptography algorithm. Asymmetric simply means it works on two different keys i.e. Public Key and Private Key. One key is used for encryption while the other is used for decryption. If one key is used to encrypt data, the other key decrypts, and vice versa. This ensures data confidentiality and integrity(depending with which key you start with). RSA is usually based on exactly two prime numbers.

Okay, So I went ahead to use the python challenge file and landed on some “modulus invertibility error” which I did not want to debug(It’s end of year, Gotta be somewhere making resolutions)

I tried an online rsa deciphering site([here](https://www.dcode.fr/rsa-cipher)). From the ct file we have n, e, and ct. In RSA: n is usually the modulus, e is the encryption exponent: ct was our cypher message.

Feeding this details on the site gave the flag: flag{usa_e_piu_grandi}

## 2. OSINT

### Challenge: Place

We are given an image file “maporomoko.jpg”
Headed over to [https://tineye.com/](https://tineye.com/) and did an image reverse search.

Got the name of the waterfall. Googled first result out “Kasanga_Rukwa Region”

And Google did the rest: UDOM{Rukwa}

## 3. Forensics

### Challenge: file

We have flag.zip file that I extracts to myfile.pdf

While expecting something, opening the file as pdf was not possible.

I decided to confirm the file type which turned to be an audio file.

Opened it with [Audacity](https://www.audacityteam.org/) only to find myself dancing to morse code.
Quickly uploaded the file to an online morse code decoder. [Link here](https://morsecode.world/international/decoder/audio-decoder-adaptive.html)

I replayed a few times just to be sure. UDOM{M0RS3S0UND5B3TT3R1NMIL1TAR13S}

## 4. Steganography

### Challenge 1: Starting point

We are given a pdf file which when opened, we see:

*We say ‘buda’ in Kenya, hehe*

Tried using steghide to extract hidden files but was prompted with a passphrase. Trying a simple brute force with pdfcrack suggested no encryption.
After running around, I found this site([here](https://products.aspose.app/pdf/parser/pdf)), uploaded the file and checked the parsed files.

### Challenge 2: Simple stego

This CTF also featured WindowsXP as a png file.
Viewing the image shows some blurred markings on the top left corner.

Zooming in brings it better.

*UDOM{BR1LL14NT_5T4RT5_H3R3}*

## 5. Web

### Challenge 1: Turaco

We have a site which shows nothing when visited. I checked the “page source” and found this.

Decrypted the decimal values in pass variable only to be told:
“Uo ni uwongo bhanaa uwongo” — That’s not true men!

I just learnt ‘password’ in Swahili is called msimbo or is it sambo?(It’s msimbo; Thanks to [Stuxkyle](https://twitter.com/stuxkyle8))
There are sambo values in hex down here.
Pasting the hex from the function to [Cyberchef](https://gchq.github.io/CyberChef/) we get decimals that when added a decimal recipe give us the flag.

*UDOM{1ts_an_0m3n}*

Came back later on to find the CTF had ended!

### Challenge 2: Two-step-snake

We have a site which when visited shows nothing.

Viewing the source code reveals a url encoded string within a ‘unescape’ function.

Did a double url decode with [cyberchef](https://gchq.github.io/CyberChef/) and decrypted the resulting decimal values to get the password.

The CTF was really awesome though didn’t get enough time for it.

Oh! and honestly, there are many ways of killing a rat!

[Let’s connect here](https://d-captainkenya.github.io/).

Happy Hacking.

---
