# :game_die: BEARCAT CTF 2026 WRITEUPS

---

# BEARCAT CTF 2026 WRITEUPS

## Flag Format: BCCTF{}

## #1.RIVER RAIDER (OSINT)

For this challenge, we were given a picture of a rogue pirate ship sailing through a river, and we needed to find the name of the bridge right behind it.

I didn’t recognize the bridge off the top of my head, so my first step was to just crop the image a bit and run it through Microsoft Bing’s reverse image search to see if it could identify the landmark.

Bing quickly matched the distinct stone towers and cables of the bridge to a location in Cincinnati, Ohio.

Just to be absolutely sure and to get the proper name of the area, I went over to Google Maps. I looked at the river running through Cincinnati and checked the bridges to match the exact shape and location.

Google Maps confirmed the bridge was the John A. Roebling Suspension Bridge.

When submitting the flag, it took a couple of tries to get the exact phrasing the challenge creator wanted (they ended up leaving out the word “Suspension”), but we finally got the points!

## Flag: `BCCTF{John A. Roebling Bridge}`

## #2.Operation Buccaneer (OSINT)

### Step 1: Researching the Operation

I started by searching for “Operation Buccaneer” and “DrinkOrDie.” These searches led to several Department of Justice (DOJ) archives. The challenge mentioned a specific member who was indicted after most of the other convictions and who ran a “high-traffic server.”

Most of the initial DrinkOrDie members were caught in 2001. However, looking through later news reports from 2003, I found a man named Kirk Patrick St. John (online alias “thesaint”).

### Step 2: Finding the Server Name

According to the official DOJ press release, St. John didn’t just participate; he provided a massive storage hub for the group. In the world of “Warez” (pirated software), these were often called “candy stores.”

The press release explicitly named his server: Godcomplex.

### Step 3: Flag Formation

The challenge asked for the server name in a specific format. By taking the unique name found in the legal documents and placing it inside the flag bracket, I got the final answer.

## Flag: `BCCTF{GodComplex}`

## #3.Poem About Pirates (Forensics)

### Challenge Overview

We were provided a `.zip` archive containing several text files, all featuring poems about pirates. The objective was to extract a hidden flag from the archive.

### Initial Analysis & The Rabbit Hole

Running basic string analysis on the extracted text files revealed an intentional acrostic in `acrostic.txt` that spelled out the word `JOLLYROGER`. While this initially looked like a promising passphrase for whitespace steganography tools, the high solve rate of the challenge suggested a simpler intended path. The poetry was a distractor.

### Finding the Attack Surface

Taking a step back from analyzing the text contents, a standard directory enumeration revealed the true nature of the challenge.

The presence of a hidden `.git` folder immediately pivoted the challenge from text steganography to version control forensics. The flag was hidden somewhere within the repository's history.

### Git Forensics & The Solution

Reviewing the active commit history via `git log -p` showed a completely clean main branch. The author had simply added the poem files one by one, with no suspicious deletions or base64 strings in the diffs. Furthermore, checking `git branch -a` confirmed there were no hidden branches.

## Get Fr1cTioN’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Since the active timeline was clean, the flag had to be hiding in an orphaned (dangling) commit or a stash — likely added and then scrubbed using `git reset --hard`.

git log — all — reflog -p | grep -i “ctf{“

By searching the hidden, unreferenced Git history, the flag was successfully carved out of the dangling commit.

## *FINAL FLAG : BCCTF{1gN0r3_4ll_PreV1OU5_1n57Ruc7iOns}*

## #4. Prolly the Parrot (Misc)/Steg

- Initial Inspection: The provided file was `prolly_the_parrot.wav`. Listening to the audio revealed distorted, screeching bird sounds that didn't form coherent speech.

- Visualizing the Sound: Since the audio sounded like “noise,” I suspected the flag was hidden visually. I opened the file in Audacity to inspect the Spectrogram.Action: Clicked the track dropdown menu and selected Spectrogram.

- Finding the Flag: Immediately, the flag appeared drawn into the frequency waves of the audio.

---
