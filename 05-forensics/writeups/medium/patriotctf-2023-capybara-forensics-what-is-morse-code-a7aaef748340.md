# :mag: Patriotctf 2023 Capybara Forensics What Is Morse Code A7Aaef748340

> **Original Source:** [Patriotctf 2023 Capybara Forensics What Is Morse Code A7Aaef748340](https://infosecwriteups.com/patriotctf-2023-capybara-forensics-what-is-morse-code-a7aaef748340)
> **Platform:** infosecwriteups.com | **Category:** `FORENSICS` | **Year:** 2023

---

## Challenge description


*pctf{ ??? }*


When I first checked out the challenge description, it was pretty straightforward. It simply said,📸


“What a cute picture of a capybara!”

*poipoipoi...*


Now, if you’re not familiar with what a capybara is, allow me to introduce you to this adorable creature! 😉


The capybara holds the prestigious title of being the largest rodent on the planet. Picture a guinea pig 🐷, but super-sized — as big as a dog! 🐶


Capybaras call South America 🇺🇸 home, covering the continent except for Chile. In some regions, they’re so abundant that they’re considered a pest. For instance, back in 1999, scientists stumbled upon a whopping 12.5 capybaras per hectare in the Brazilian 🇧🇷 Pantanal. Yet, in other places, like certain parts of the Amazon, spotting a capybara can be quite rare. 🌎


Alright, alright, I know I’ve gone a bit off-topic here, but hey, that’s just how I roll! 😄 Now, let’s get back to the task at hand. XD

## How to Solve it ?


Now that you’re acquainted with this adorable capybara, let’s dive into how I went about solving this challenge. 🧐


First things first, I downloaded what they provided for us to solve — a simple JPEG image of a capybara. Yep, that’s it! 😄

*🥲 short description and now only one image*


So, when I started pondering the tricks I could use on this image to uncover the flag, I began with some basic steganography techniques. My usual go-to is the “strings” command. This nifty command is designed to extract string characters from files, particularly focusing on figuring out what’s hidden inside binary files (non-text files). 🧐


Unfortunately, “strings” didn’t yield any results for me this time. So, I decided to explore other tools in my steganography toolkit. One of my favorites is ExifTool, a powerful utility for extracting metadata from files. It’s not just for images but also works with various other file formats like PDFs and MP4s. ExifTool allows you to update and remove metadata and provides a wealth of information about files. 🛠️


*exiftool output*


Unfortunately, even ExifTool didn’t provide much information. But you know what i say to me ,


“Never lose hope!” 😉


After a bit more digging, I stumbled upon a tool called “binwalk.” It’s a command-line gem in the world of Linux, perfect for analyzing and extracting the contents of binary files. People commonly use it for tasks like reverse engineering firmware images or dissecting various binary files to unveil hidden or encoded data. Think bootloaders, kernel images, or filesystems — binwalk’s got your back! 🕵️‍♂️


*Binwalk tool output*


And voila, it worked! 😄


When I checked the output of Binwalk, I was in for a pleasant surprise. It managed to extract an audio file from that seemingly innocent capybara .JPEG image. 🎶📸 It's amazing how these challenges can hide things in plain sight!


Haha, I can imagine your excitement to listen to that hidden audio file! 🎧


So, you quickly grabbed your headphones, hit play, and what did you hear? Beep, beep, beep! 😳 You were probably thinking,


“What on earth could these beeps possibly mean??” 🤔

*wow,gg*


In moments like these, Google, your trusty research buddy, comes to the rescue! 🔍🔎


*google search results*


and after some deep searching i know about Morse Code?📜 🌐

## History of Morse Code📡


Morse code communicates text information using dots and dashes (short and long signals) to represent letters, numbers, or symbols. It originated in the early 1830s and has been widely used in various applications throughout history. Its primary use has been in long-distance communication before the advent of modern telecommunications systems. 📻


*Morse Code*


Now that I had a much better understanding of what those beeping sounds meant, one thing was still bothering me: how could I convert that audio into Morse Code? 🤔


## Get Dev_vj1’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


English Content

>

Hello, How are you?


Output: Morse Code


```
.... . .-.. .-.. --- --..-- ....... .... --- .-- ....... .- .-. . ....... -.-- --- ..- ..--..
```


## Let’s tackle that puzzle! 😉


Now that we’ve confirmed that those beeps are, indeed, a Morse-encoded message (the flag) in the form of audio, it was time for my trusty research buddy, Google, to come to the rescue once more! 🔍


I fired up my Firefox browser, started searching for


“how to encode messages in audio Morse code” and after reading some articles and exploring websites, i stumbled upon the


[International Morse Decoders](https://morsecode.world/international/decoder/)


*[https://morsecode.world/international/decoder/](https://morsecode.world/international/decoder/)*


This website takes an audio file from the user, examines the audio beep frequencies 🎵, and magically transforms them into Morse code, which can then be converted into good old ASCII text. 🎩🔠


It sounds like we were on the right track to cracking the code! 😄


So, all i had to do was upload the audio file to this website, and like magic, it automatically gave you the code in ASCII text! ✨


It took just a minute to decode that Morse code message, and boom! You had your ASCII text. 🕒💥


### Q&A:


“Oh, thanks for asking! It’s not always obvious to identify encodings or ciphers just by looking at them, especially for beginners. there are so many different encoding methods and ciphers out there, and it’s practically impossible to remember them all.


*Easy-peasy ;)*


But here’s the good news: you don’t have to worry about memorizing everything. There are handy online tools known as Cipher Identifiers that can do the heavy lifting for you. In my case, I used the Cipher Identifier on the [dcode.fr](https://www.dcode.fr/cipher-identifier) website to quickly determine that the given text was in ASCII format. These tools are a real lifesaver and make solving challenges a lot more accessible, even for newcomers!”


For the final stretch, all you needed to do was copy that ASCII text and paste it into an online ASCII decoder. my preferred choice is Dcode.fr, a fantastic website for encoding and decoding. You really appreciate this website since it’s been a valuable tool in solving many other crypto challenges. 🌐👏


*[https://www.dcode.fr/ascii-code](https://www.dcode.fr/ascii-code)*


And there we have it! When i plugged in that ASCII code into the decoder, it revealed our final output — the flag! 🚩

### PCTF{d0_y0U_kN0W_h0W_t0_R34D_m0r53_C0d3?}


Mission accomplished! we cracked the challenge and unveiled the hidden message. Well done, and thanks for reading my Write-up!


At the end of this write-up, I can imagine your excitement to learn about how our team_Valhalla performed in the PatriotCTF! 🎧


We really gave it our all in this competition, putting in our best effort.And you know what? It paid off! We secured the 19th rank out of a whopping 1,274 teams! 🏆


Personally, me and ‘l1nx1n’ went all in, working tirelessly on solving each challenge. we worked until midnight , staying up until 2:00 AM, and dedicated every waking hour to crack these challenges during the intense 48 hours of PatriotCTF 2023. 💪😅


It was an incredible experience, and I’m proud of what we achieved together! 🏆👏

---

*Originally published on [Medium](https://infosecwriteups.com/patriotctf-2023-capybara-forensics-what-is-morse-code-a7aaef748340). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of forensics CTF writeups.*
