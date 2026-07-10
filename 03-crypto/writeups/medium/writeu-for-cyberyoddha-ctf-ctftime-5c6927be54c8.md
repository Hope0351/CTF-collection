# :locked_with_key: Writeup for CyberYoddha CTF — CTFtime

> **Original Source:** [Writeup for CyberYoddha CTF — CTFtime]()
> **Platform:** medium.com | **Category:** `CRYPTO`

---

# Writeup for CyberYoddha CTF — CTFtime


This blog post contains the writeups for the following challenges :-


- Misc (Lorem Ipsum)

- Forensics (Image Viewer, The row beneath, What’s the password, Steg 2 and Steg Ultimate)

- Cryptography (Beware the Ides of March and Sus)

- Reverse Engineering (Password 1)

- Trivia (Trivia 1, Trivia 3, Trivia 4, Trivia 5, Trivia 7 and Trivia 8)

## LOREM IPSUM


The given text when googled will give you the original text and you’ll realise that the given text has some additional characters attached to some words.


Lorem ipsum dolor/c/ sit amet, consectetur/y/ adipiscing /c/elit, sed do/t/ eiusmod tempor inci/f/didunt ut labore et dolore magna aliqua/l/. Ut enim ad minim/a/ veniam, quis/t/ nostrud exercitation ullamco/i/ laboris nisi/n/ ut aliquip ex ea/i/ commodo/s/ consequat. Duis /c/aute irure dolor in reprehenderit in voluptate velit /o/esse cillum dolore eu fugiat nulla pariatur. Excepteur /o/sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim /l/id est laborum.


Extracting all these characters will give the flag.


So the flag for this challenge is CYCTF{latiniscool}

## IMAGE VIEWER


Taking a strings of the given image will provide the flag.


CYCTF{h3h3h3_1m@g3_M3t@d@t@_v13w3r_ICU}

## THE ROW BENEATH


Similar to the previous challenge the flag can be retrieved with the help of strings.


So the flag is CYCTF{L00k_1n_th3_h3x_13h54d56}

## WHATS THE PASSWORD?


I used steghide to extract the image. Firstly I tried with an empty password. When that didn’t worked I took a look at the image and the password was clear. It was sudo


So the flag was written in the extracted text file.


And the flag is CYCTF{U$3_sud0_t0_achi3v3_y0ur_dr3@m$!}

## STEG 2


I used stegsolve and found the flag in red plane 1


The flag is CYCTF{l$b_st3g@n0gr@phy_f0r_th3_w1n}

## STEG ULTIMATE


First I used an empty password to extract steg3.jpg out of the original image using steghide. Then I used steghide again with an empty password on steg3.jpg and got a text file which directed me to pastebin.


The pastebin URL was [https://pastebin.com/YnKqT9s3](https://pastebin.com/YnKqT9s3)


When I went to this URL I received the following message:


Hmmmm. What cipher is this? Sometimes, it’s not the type we think.


iVBORw0KGgoAAAANSUhEUgAAAowAAABYCAYA……….


The cipher was base64 encoded and decoding it gave me the ascii code of a PNG image


I used Cyberchef to decode and save the file as a PNG and got the flag


CYCTF{2_f0r_th3_pr1c3_0f_1_b64}

## BEWARE THE IDES OF MARCH


The given ciphertext is JFJAM{j@3$@y_j!wo3y}. Now one thing is very clear that JFJAM will convert to CYCTF. Notice the positions of J’s and C’s. This was a clear indication of Caesar Cipher. So I used [dcode](https://www.dcode.fr/en) to convert the ciphertext to plain and found that the key was +7.


So the flag was CYCTF{c@3$@r_c!ph3r}

## SUS


For this one I guessed that it could be a Vignere Cipher. So I used [Guballa](https://www.guballa.de/vigenere-solver) to decode it and found the plaintext to be wouldyoulikesomevinegarwiththat and key to be salad.


So the flag is CYCTF{wouldyoulikesomevinegarwiththat}

## PASSWORD 1


The contents of the file are:


import random


def checkPassword(password):


if(len(password) != 43):


return False


if(password[26] == ‘r’ and


password[33] == ‘t’ and


password[32] == ‘3’ and


password[16] == ‘3’ and


password[4] == ‘F’ and


password[21] == ‘r’ and


password[38] == ‘1’ and


password[18] == ‘c’ and


password[22] == ‘@’ and


password[31] == ‘g’ and


password[7] == ‘u’ and


password[0] == ‘C’ and


password[6] == ‘p’ and


password[39] == ‘3’ and


password[3] == ‘T’ and


password[25] == ‘3’ and


password[29] == ‘t’ and


password[42] == ‘}’ and


password[12] == ‘g’ and


password[23] == ‘c’ and


password[30] == ‘0’ and


password[40] == ‘3’ and


password[28] == ‘_’ and


password[20] == ‘@’ and


password[27] == ‘$’ and


password[17] == ‘_’ and


password[35] == ‘3’ and


password[8] == ‘7’ and


password[24] == ‘t’ and


password[41] == ‘7’ and


password[13] == ‘_’ and


password[5] == ‘{‘ and


password[2] == ‘C’ and


password[11] == ’n’ and


password[9] == ‘7’ and


password[15] == ‘h’ and


password[34] == ‘h’ and


password[1] == ‘Y’ and


password[10] == ‘1’ and


password[37] == ‘_’ and


password[14] == ‘t’ and


password[36] == ‘r’ and


password[19] == ‘h’):


return True


return False


password = input(“Enter password: “)


if(checkPassword(password)):


print(“PASSWORD ACCEPTEDn”)


else:


print(“PASSWORD DENIEDn”)


So I just rearranged the code which was a useless effort as I could have used python to manage this somehow.


The flag is CYCTF{pu771ng_th3_ch@r@ct3r$_t0g3th3r_1337}

## TRIVIA 1


The flag is Linus Torvalds

## TRIVIA 3


Found the answer on [Wikipedia](https://en.wikipedia.org/wiki/Apache_Hadoop)


The flag is Yahoo

## TRIVIA 4


The flag is honeypot

## TRIVIA 5


The flag is shoulder surfing

## TRIVIA 7


The flag is sfc

## TRIVIA 8


I just reverse searched the image on Google


The flag is haskell

---

*Originally published on [Medium](https://architvats96.medium.com/writeu-for-cyberyoddha-ctf-ctftime-5c6927be54c8). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
