# :game_die: Bugcrowd CTF 2025. I jumped into Bugcrowd’s CTF and ended…

---

I jumped into Bugcrowd’s CTF and ended up solving multiple challenges in one go. Each one had a different twist, from easy to medium level. Here’s a quick walk through of how I approached them and what I learned along the way.

## 1. Bank

this challenge is related to the range of integer data type, actually here the challenge criteria is like only deposit money with positive amounts, withdrawal we cannot perform, and from this we have to find flag.

and the idea clicked in my mind, that what if i put the maximum amount that I can deposit so i tried for 999999999 but it fails then i searched about the range of INT data type and it is -2,147,483,548 to 2,147,483,547.

now time to deposit 2,147,483,548 amount and BOOM, Flag is there.

## 2. Exif metadata secrets

this is forensics based challenge, we have a angry cartoon character profile pic and they said a twitter account use this for profile picture.

time to check for reverse image search using google and Yandex and at the same time i checked for exif data about image geolocation coordinates that we can get something. but the flag is directly stored over there.

## 3. Nested Maze

this one makes you multiple times the tab switch, I also did the same. so they have given a zip file contained with multiple zip files inside it but twist is each zip files contains a text file with password for next zip file. so first one they already provided and using that we have to find for next one.

and the thing i noticed, the passwords they used for each folder is the sequence of the next file. so i directly i go for the last zip files i used password accordingly and Flag is here.

## 4. dependency dilemma

this one i liked most, they just provided a simple web page with only one error message.

so i checked it source code and found an github username with repository.

so every time in CTF, when i go for GitHub repositories, first i check the commits they have made in the past. sometimes it helps for more about the challenge.

and the first commit is location of FLAG and it was stored in commented api_key form.

## 5. Excel-sior

so this one of reversing category challenge and the description they given as

so i started with use of Linux in-build utility “STRINGS”, so I can get something interesting. And here i found there are multiple worksheets hidden.

they mentioned formula capabilities in description, so i used to unhide sheets option in excel which lists the worksheets hidden in the parent sheet.

and in that i got a flag name sheet where i got FLAG.

## 6. Unicode war

they give in very simple task that provided a server.py file in which we have a /auth endpoint and credentials to login as admin and get the flag. simple right? twist is credentials provided are not is regular ascii form. as you can see below.

At first i also got tricked and directly used the same credentials in burp suite, but after pasting the password, something weird text was printed over there,

so also tried to directly type the password but after making request it says access denied. so another method help me to get FLAG is the “CURL”. I directly copied the values in CURL using the -d module and this time text format is as same as in the server.py file and after making request FLAG is there.

## 7. privilege escalation

this is something i loved most, because the challenge itself helps to learn about LLMs. but this one force me to use hint, so hint says ‘Have you heard about recent advancement for LLM crawlers?’. i started to search learn about techniques which are used to for LLM crawling and i found this article medium, and it works.

## Get VirajMathpati’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

so i tried llm.txt instead robots.txt which help for AI bots instead search engines. And i got one endpoint to change_role of user.

here i have to make a POST request with containing the session key and body part with a ‘role’: ‘admin’ and successfully role is changed to admin from a normal user.

after this when i refresh the home page i got FLAG.

---
