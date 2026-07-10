# 🔄 I solved EIGHT challenges — CTF Writeup 001 (Part 2)

---

## 📝 Full Writeup

I solved EIGHT challenges — CTF Writeup 001 (Part 2)![Harry Zhu

](/web/20251008203809/)

[Harry Zhu](/web/20251008203809/)

·
May 22, 2024

[

](/web/20251008203809/)

--

IDA Pro and Ghildra
Where were we? Let’s check back on the [first part](/web/20251008203809/) before we move on.

Right… the Packer’s Paradox. **thinkingprocessing thought**

Alright, let’s do it!

Quick reminder: Be sure to have [Kali](https://kali.org/) installed for this challenge!

### Challenge #4: Packer’s Paradox
We were first provided a Microsoft Executable (EXE) file. I first did some elementary Linux commands to explore the file’s metadata and content.

```
➜ Packer strings PackerParadox.exe | grep C1
C1jF
```

A flag starts with “C1”, remember? I just quickly checked that here.

```
➜ Packer file PackerParadox.exe
PackerParadox.exe: PE32 executable (GUI) Intel 80386, for MS Windows, UPX compressed
```

Perfect! This confirms my initial suspicion. It’s packed with UPX compression. Let’s put it through an Unpacker tool before we look through the assembly, or do we even need to?

Let’s use this unpacker UPX tool: [https://www.kali.org/tools/upx-ucl/](https://www.kali.org/tools/upx-ucl/)

I was then able to move the file to Kali using another command. Remember, for CTF competitions, you should be very comfortable with Linux and its commands.

```
scp ~/Downloads/Packer.exe kali@<ip_addr>:/home/kali/.
```

You should then look for the manpage for `upx-ucl` to find the proper command to decompress the executable file, which is:

```
upx-ucl --help # get help or the manpage for this tool

upx-ucl -d Packer.exe # used to decompress the file
```

Perfect! Now that it’s decompressed. I can copy the file back over from Kali to my host because I don’t like working in Kali if I don’t need to.

Time to pull out the big guns! `IDA Free` Because, duh, you think I got `IDA PRO` money for a CTF competition?

Graph view of x86 assembly code / [IDA Free](https://hex-rays.com/ida-free/)
Not a big fan of this view, so let’s explore the `Hex View` right next to the graph view that we’re currently looking at.

OK.. found it!

But I was frustrated... do you know why? This meant I could have done this after I decompressed the file… which I should have done first to avoid using another tool like IDA.

I’ll show ya!

```
➜ DOD strings PackerParadox.exe | grep C1
C1{N0t_$uch_a_Parad0x_Aft3rall}
```

Now it shows! Great, we solved another one!

On to the next one…

### Challenge #5: Printer
This was a web challenge and an easy one. Always check `robots.txt` for any web challenge claiming to be easy. It always is.

For this problem, you’ll see something like this:

```
Disallow: /notes.txt
```

LOL — perfect! Inside it says:

```
... dev password is <password>
```

Forgot the password, and the challenge website just went down, but that was it! Now, the infrastructure hosting this web server was on Google Cloud instances that didn’t share the right connection pooling.

So, participants, including myself, had to spam the login box to get the flag. It was a tad unfair, but that was it. LOL. Took me about 15 tries before I go the `C1{w3bsite_fl4g}` flag.

OK.. next one!

### Challenge #6: Header Hinterlands
I was given a TAR file, which was a saved Docker instance. Initially, I went through all the blobs honestly by brute forcing to check every file, to which I found an Nginx configuration file where it has Base64 encoded data.

```
 listen 80;

 # Define the location of your root directory
 root /usr/share/nginx/html;

 # Define the custom 404 page
 error_page 404 /custom_404.html;

 # Location block for your main content
 location / {
 try_files $uri $uri/ =404;
 add_header X-Syndicate-Command "QzF7YW1AejFuZ193aEB0X3VfY0BuX2gxZDNfMW5faDNAZDNyc30=" always;
 }
```

OK.. wow, too easy!

Decoding this with [Cyberchef](https://cyberchef.io/) gives us this

```
C1{am@z1ng_wh@t_u_c@n_h1d3_1n_h3@d3rs}
```

### Challenge #7: Important Document
This is all about code obfuscation! But we’ve gone way too long with this one. Feel free to [follow me](/web/20251008203809/) for Part 3 this week!

Follow me for more content about tech, post-grad life, and security writeups. If you’re also in the world of helping others, connect with me on [LinkedIn](https://www.linkedin.com/in/harryjzhu/)!

I am a software developer with a passion for engineering secure, performant, and creative software and a heart for telling my stories and digital manifestations as I go through life and beyond.

---
