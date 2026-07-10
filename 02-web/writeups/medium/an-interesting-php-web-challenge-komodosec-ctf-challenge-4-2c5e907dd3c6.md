# :globe_with_meridians: An interesting PHP web challenge(Komodosec CTF-Challenge 4)

---

# An interesting PHP web challenge(Komodosec CTF-Challenge 4)

I’m a fan of web-sec and i just begin to learn and find some interesting challenges for myself. once time, walk through some ctf site, i see [http://ctf.komodosec.com](http://ctf.komodosec.com). I walk through and find that about web-sec challenge. I start solving. The first and second and third challenge is not as interesting as this one because of it’s kind. Just about SQLi and the third is quite strange with me(about XXE attack, I will write about it someday :3)

Let’s start with the challenge 4 ( [http://ctf.komodosec.com/challenge-4.php](http://ctf.komodosec.com/challenge-4.php) )

*Challenge 4*

It just displays some weird text

‘ICcnLmpvaW4oW2NocihvcmQoaSleODIpIGZvciBpIGluICdcJyE3ciQ7NyUhPVwnIDE3ciIzIDM/J10p’

As usual, first i try to base64 decode it, and it’s easy to decode at the first(so lucky !!)

*Base64 decode*

Something like Python :3(my favorite language), let’s see what it tells us!!

*some basic python codes*

let’s check viewsource param !!

*[http://ctf.komodosec.com/challenge-4.php?viewsource](http://ctf.komodosec.com/challenge-4.php?viewsource=)*

Ohhhh!! we get something interesting. I start walk through and focus some important codes

What does this code means??

imaging something like this:

Continue analyzing codes

As you can see. The code above following this:

- connect to the database to get the flag of challenge 4

Wait!! Get flag and do what ??? :3

*And this is the answer*

Send mail ;__;

And I image that the we have to set the param sendTo=*our email* to get the flag ✌️

But it’s not easy like that. i try :

ctf.komodosec.com/challenge-4.php?sendTo=*mail*(but not get any mail even i check the spam folder). I keep analyzing and found this

if we set the param error=*something* it will output *something* on the screen. Try:

[http://ctf.komodosec.com/challenge-4.php?error=PeterJson](http://ctf.komodosec.com/challenge-4.php?error=PeterJson)

But nothing show on the screen :(

I start again and see the code. I forgot that something weird which I told you. So sad that I fotgot it. It’s the most important

*THIS IS THE MOST IMPORTANT :(*

The extract function together with the If Statement!!! Damnn

It means we have to set extract=*something* that makes the if statement come true.When the if statement is true we can set the new value for $sendTo(cuz extract function will import our variable to the current tabale!!!)

I make some php code the reveal the vaule of extract parameter

And i get the value of extract param (p)

*Now we can get the message on the screen!!!*

Finally, Let’s get the flag!!!!

[http://ctf.komodosec.com/challenge-4.php?sendTo=*mail*&extract=p](http://ctf.komodosec.com/challenge-4.php?error=PeterJson&extract=p)
Ps: Remember to check the spam folder!! I have experienced this one :( which makes me a lot times to work :(

Hope you fell good with this challenge.. It’s not difficult but i think it is necessary for noobs. I am just a noob and always learn and share something interesting. Have a nice day all!!

---
