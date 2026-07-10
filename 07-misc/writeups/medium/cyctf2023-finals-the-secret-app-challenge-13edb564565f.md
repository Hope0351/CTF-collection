# :game_die: Cyctf2023 Finals The Secret App Challenge 13Edb564565F

---

*Forgetpassword.html*

It asks for Account number so let’s give it our account number 1337

*resetpassword.html response*

It says token generated and asks for a pin code to be able to Reset your password.

OfCourse as it’s a CTF so there is no mail will be sent to your account, and there is no other way to find the secret pin.

Let’s try to send random and empty pin

*response for random / non pin*

nothing returns.

Okay… what will happen if we tried to reset our password again ?

*Response for the same account id 1337*

It says “ Error Creating Token ” interesting!

i tried to do the same process for account 1,2,500 and the same flow was happening.

i assumed that the server is checking whether there is a token is being generated only 1 time then server returns error after that.

I didn’t know the actual reason at that moment , but now I’m sure about something: the token is a fixed value for each account.

Great let’s take a note by this information as well.

For my last test i tried to reset password for unknown account (“SAY 1500 ”)

What happened was the server responded with “ token generated successfully ” and the same flow was happening if i tried to reset it again.

HMM…. Okay we can conclude the following:

1. The Token Field in the Database isn’t at the same table as users
2. There Is A Separate Table for the tokens let’s say it’s called “ A ” for now
3. This A table has no foreign key with the users table

OKAY i think that’s enough for The application on the Browser Let’s dig into The Source Code so we can address all the questions in our minds (“ i think the source code wasn’t attached from the beginning and they attached it at the end ”)

---
