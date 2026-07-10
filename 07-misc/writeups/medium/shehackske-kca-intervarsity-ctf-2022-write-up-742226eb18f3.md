# :game_die: SheHacksKE KCA Intervarsity CTF - 2022 Write up

---

# SheHacksKE KCA Intervarsity CTF — 2022 Write up

A short write up for some ctf challenges held at [KCA University](https://www.kca.ac.ke/) during the intervarsity bootcamp by [SheHacksKE](https://www.shehackske.com/), [fr334aks](https://fr334aks.github.io/), [Safaricom](https://www.safaricom.co.ke/), [AfricaHackOn](https://africahackon.com/), [Ekraal Innovation Hub](https://ekraal.org/), [Trend Micro](https://www.trendmicro.com/en_za/business.html) & [Microsoft](https://www.microsoft.com/en-us/).

Challenge link [https://kca.ciphercode.dev/](https://kca.ciphercode.dev/)

## OSINT
Challenge: Hunter1

Given a SHA256 hash of a malicious office document,
What’s the name of the ransomware behind the Malicious Office Document?

This was pretty easy.

### Solution

Searching the SHA256 hash on Google brings up a link highlighting “Gandcrab ransomware” and that’s it, you have hunted down the name of the ransomware. flag{gandcrab}

## Challenge: Last Hunt

This hunt was about the payment methods used by gandcrab.
Other than BTC the Ransomware group also uses?

### Solution

I did some googling on “gandcrab ransomware” and went through articles.

A story featured on [malwarebytes](https://www.malwarebytes.com/gandcrab) [(here)](https://www.malwarebytes.com/gandcrab) stated the payment method.

flag{dash}

## Forensics
Challenge: Chatty Chatty — 2

“See ye and you shall find me”. Dig deeper to earn the second flag.
I didn’t get the first flag but here, I could “see and find”

Download the given file.
Well, turns out there are many ways of killing a rat(including burning the whole house)

### Solution

I ran strings on the file and found a base64 string.

I decoded the base64 string to get the flag.

Flag{I_Kn3w_Y0u_w0ulD_f1nd_me}

Similarly:
Uploading the file at [cyberchef](https://gchq.github.io/CyberChef/) also revealed the base64 without any recipe.

*Go ahead and decode the string.*

Similarly:
The exiftool should reveal the base64 string as explained by oste [here](https://05t3.github.io/posts/SheHacksInterUniCTF/).

There are many ways of killing a rat!

Connect with me: [Here](https://d-captainkenya.github.io/)

Happy Hacking.

---
