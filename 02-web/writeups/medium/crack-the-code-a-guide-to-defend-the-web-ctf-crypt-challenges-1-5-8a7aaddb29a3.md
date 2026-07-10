# :globe_with_meridians: Crack the Code: Defend the Web CTF Guide

> **Original Source:** [Crack the Code: Defend the Web CTF Guide](https://infosecwriteups.com/crack-the-code-a-guide-to-defend-the-web-ctf-crypt-challenges-1-5-8a7aaddb29a3)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Crack the Code: A Guide to Defend the Web CTF Crypt Challenges 1–5


*Created by lexica.art*

## Crypt 1 / Crypt


The challenge presents a jumbled message that has been encrypted or obfuscated in some way. You can solve the challenge by recognizing that the message has had its letters reversed.


By reversing the letters in each word, you can reveal the original message: “`Hello, welcome to the crypt levels on hackthis. These levels are all about decryption and logic, you will need to employ a lot of brain power. To complete this level enter this pass: woocrypt"`. The password required to complete the challenge is "`woocrypt`".

## Crypt 2 / Crypt


To solve this CTF, you need to decrypt the given message “`Aipgsqi fego, xlmw pizip mw rsx ew iewc ew xli pewx fyx wxmpp rsx xss gleppirkmrk. Ws ks elieh erh irxiv xlmw teww: wlmjxxlexpixxiv`".


The message is encrypted using the ROT cipher, which shifts each letter in the alphabet by a certain number of positions. The hint provided in the message suggests that you need to shift each letter in the message by one position to the left. You can use an online tool or write a simple script to decrypt the message.


The decrypted message is “`Welcome back, this level is not as easy as the last but still not too challenging. So go ahead and enter this pass: shiftthatletter`", which provides you with the password to log in to the next level of the CTF.

## Crypt 3 / Crypt


I recognize that the encrypted text is Morse code. “`…. .. –..– / — …. .- -. -.- … / — — / … .- — ..- . .-.. / — — .-. … . / — …. . / — .-. .- -. … — .. … … .. — -. / — ..-. / — . .-.. . –. .-. .- .–. …. .. -.-. / .. -. ..-. — .-. — .- — .. — -. / .– .- … / … — .- -. -.. .- .-. -.. .. –.. . -.. .-.-.- / …. . / ..- … . -.. / -.. — — … / .- -. -.. / -.. .- … …….. / — — / -.-. .-…- — . / .- / … — .- -. -.. .- .-. -.. / .– .- -.– / — ..-. / -.-. — — — ..- -. .. -.-. .- — .. — -. –..– / …. . / …. .- … / ……-.. .–. . -.. / -.– — ..- / — — -.. .- -.– / — — / –. . — / — …. . / .–. .- … … — … / — …. .- -. -.- -.– — ..- … .. .-.`”


Decrypt the Morse code using a tool like the Cipher Identifier web page.


Interpret the decrypted text, which contains information about standardizing telegraphic communication. ”`HII THANKS T SAUEL RSE THE TRANSISSIN F TELEERAIHIC INFRATIN EAS STANDARDIIED. HE USED DTS AND 5S T C�TE A STANDARD EAN F CUNICATINI HE HAS 5LIED NU TDAN T EET THE IASSS THANKNUSIR`”


## Get Ahmet Talha Şen’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Guess the password based on the message content. In this case, the password is likely “`thankyousir`", which is mentioned at the end of the message.

## Crypt 4 / Crypt


To solve this CTF, you need to decrypt the given message “`Dc, gdcl cl h lcrcshn ckqh gz sqwqs guz. Gdcl gcrq qhyd sqggqn cl hllcomqk h ljqycacqk nqshgczmldcj ucgd hmzgdqn sqggqn. Jhll: cdhwqancqmkl`".


Cipher Identifier web page to help you decrypt the text. This is a useful tool that can automatically identify the encryption method used to encrypt a given piece of text and provide suggestions for how to decrypt it.


Using this tool, you were able to determine that the plaintext message is “`HI, THIS IS A SIMILAR IDEA TO LEVEL TWO. THIS TIME EACH LETTER IS ASSIGNED A SPECIFIED RELATIONSHIP WITH ANOTHER LETTER. PASS: IHAVEFRIENDS`".

## Crypt 5 / Crypt


The challenge presented is to decrypt the following text: “`qoymlNlpY :ccdf lpy yzJ .qoh ln lxigqoh qlxlm eeiw zot ydpy gmipylnoC ,zot gmiyqdncyzo ho ydpy ci lniqk tN .lsie sooe tlpy ydpw yom ,smipy amd tdc tlpy ydpw tj lefolf gmigazb ho ydpy ci lniqk tN .tyicoiqzk ho ydpy ci lniqk tN .edminiqk d nd i clT`"


Firstly I reverse the encypted text. Then using [quipqiup.com](http://quipqiup.com), we can input the encrypted text and select the option for frequency analysis. The tool will then analyze the frequency of each letter in the encrypted text and provide potential decryption options based on common English words and phrases.


In this case, inputting the encrypted text into [quipqiup.com](http://quipqiup.com) produces the following potential decryption option: “`Yes i am a criminal. My crime is that of curiosity. My crime is that of judging people by what they say and think, not what they look like. My crime is that of outsmarting you, Something that you will never forgive me for. But the pass: TheMentor"`.

---

*Originally published on [Medium](https://infosecwriteups.com/crack-the-code-a-guide-to-defend-the-web-ctf-crypt-challenges-1-5-8a7aaddb29a3). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
