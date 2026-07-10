# :mag: The Coolest Digital Forensics Challenge I Ever Solved

> **Original Source:** [The Coolest Digital Forensics Challenge I Ever Solved](https://infosecwriteups.com/the-coolest-digital-forensics-challenge-i-ever-solved-e0f03e0d196d)
> **Platform:** infosecwriteups.com | **Category:** `FORENSICS`

---

# The Coolest Digital Forensics Challenge I Ever Solved


*Photo by [Artem Bryzgalov](https://unsplash.com/es/@abrizgalov?utm_source=medium&utm_medium=referral) on [Unsplash](https://unsplash.com/?utm_source=medium&utm_medium=referral)*


As a man obsessed with both cybersecurity and puzzles, Capture The Flag (CTF) challenges are a dream come true. What’s a CTF challenge? It’s a fun, gamified cybersecurity-related challenge that requires some sort of creative problem-solving, technical skill, and/or tool to solve. I have seen a lot of great CTF challenges during my revolutions around the sun, but none have come close to the one I am about to show you. Think of it as an easter egg hunt for nerdy hackers. What makes this challenge so great? Well- rather than just being another cryptography challenge, it engages multiple senses. The instructions for this challenge were mysterious and curt. With the only hint being “decode this”. Keep in mind that this is my recreation of the challenge and not the original challenge itself. WARNING: You will want to lower your volume since this audio recording is very high-pitched.

*This is the sound with the hidden message. The only instructions given were to decode it with no additional context*

## My First Attempt


Upon an initial listen, my mind quickly hypothesized that it could be Morse code. The high-pitched variance in the sounds reminded me of the dots and dashes of the typical Morse code format. Certainly not a sound that would help me sleep. It also wasn’t the typical “beep-boop” noises that we would expect from Morse code, but it was worth a shot to double-check. After toiling away at this for an hour or so, I realized this was probably just a red herring. Damn!


Eager to solve the challenge, I quickly relied on a skill I have been honing since I was a young child, my ability to Google. Clocking in at a blazing 77 wpm (words per minute) I cleverly typed “how information can be hidden in an audio file” and after a little bit of digging, I stumbled upon a unique method of hiding information. This method completely changed how I perceived the challenge. What if I tried to *see *the audio file, rather than *hear*it.


Confused? I was too.


## Get Cyber Golden Retriever’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Here is the explanation: There is a way to view a graphical depiction of the sound amplitude plotted against the time. This is called Waveform. It looks like when a reality TV show is showing a phone call and displays the waves of the audio.

## Using Our Eyes To Hear The Answer


Now that I had a path forward for solving our problem, I researched tools I could use. I came across a program called Audacity, and it worked like a charm.


*We will be using a program called Audacity to analyze the sound file*


After opening Audacity, I selected File -> Open -> and chose the file named “NotAHiddenMessage.wav”

*Here is the filename*


Now that we have loaded the audio file into Audacity, we can use this program to convert the format that the audio file is displayed in. Seeing as this file is uploaded in Waveform by default, we will try switching it to the spectrogram format. Even though we have not yet converted it to the correct format, we can vaguely see that some of the patterns resemble the letter “H”.


*This is the audio file visually shown in waveform.*


Now, to convert to a spectrogram format we will click on the arrow symbol next to the filename and make the switch.


*The option menu*


After selecting spectrogram, we now see the decoded message


*The decrypted message displayed in the spectrogram format*


And there you have it! Another creative and cool challenge completed.


If you found this interesting, like and follow for more!

---

*Originally published on [Medium](https://infosecwriteups.com/the-coolest-digital-forensics-challenge-i-ever-solved-e0f03e0d196d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of forensics CTF writeups.*
