# :globe_with_meridians: Hacking *BugPoc’s* 18 Game (XSS challenge) hosted by The XXS Rat

> **Original Source:** [Hacking *BugPoc’s* 18 Game (XSS challenge) hosted by The XXS Rat](https://infosecwriteups.com/hacking-bugpocs-18-game-xss-challenge-hosted-by-the-xxs-rat-f3f1adc04c8)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Hacking *BugPoc’s* 18 Game (XSS challenge) hosted by The XXS Rat


Why does my title say “Hacking” when it’s just an XSS challenge? Because I didn’t solve the challenge, I hacked the game.


When you open [the challenge page](https://cards.buggywebsite.com/), the first thing you see is this:


*Challenge page*


This is a game called “18 Game” and its goal is to have three cards of which the sum adds up to 18. This is done by selecting one card from each pile, and after your three cards are selected, you will know if you’ve won or not.


So is there a strategy of some sort to win this game? No. The cards that you select are randomly selected in a [popup window](https://cards.buggywebsite.com/popup.html#indexes=1|1|0&name=Player%201) that opens once you clicked a card.

*Popup to randomly pick a card*


The popup sends a post message to it’s opener, with the randomly chosen card. When inspecting this post message, we see that de data contains the values `guess`, `indexes`and `str`.


- `guess` contains the actual card number

- `indexes` contains the position of the card

- `str` contains a string to be displayed at the homepage of the game.

>

At this point I feel really stupid because if I took an actual look at the entire message, and not only the data, I would have seen that the nonce is also being sent, which is what was needed to solve the challenge. If you want to know the solution of the challenge itself, check out [this awesome writeup](https://holme-sec.medium.com/xss-challenge-the-xss-rat-bugpoc-fd551eb7c0eb) by [Holme](https://twitter.com/holme_sec)!


*Data in post message*


So this `guess` looks really interesting, the number of the card is being sent to the opener. Does this mean we can send our own post message to the opener? Yes, we can! In this case, the home page didn’t verify the domain where the post message was coming from, so we can just open this page from our own site and send it a message with our own choice of card. Also, the `str` variable was vulnerable to html injection, but it turns out this was not needed for the challenge.


## Get GrumpinouT’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Three messages later I finally won the game!


*Winning screen*


I decided to create a tool to make you win the game every time without needing to spend time looking at post requests, because what is even more beautiful than popping an alert? Popping a winning screen of course!


The first thing I did was copy paste a lot of [BugPoc’s](https://bugpoc.com/)code and replace the back of the cards with fronts of cards. Then I added a home screen to explain how the tool works and to open the game when the start button is clicked.


*Start screen of my tool*


*My tool*


So when you clicked the start button, a new tab will be opened with the 18 Game. Then you have to go back to my page and you will see all possible cards per pile. Here you can select 1 card per pile. (in theory multiple cards per pile is possible, but I didn’t allow it because BugPoc also blocked this.)


*Cards selected*


When you select a card, you see a red border to know which card you selected. If you now have a look at the 18 Game’s tab, you will see the cards you selected are also here visible.


*Cards in the 18 Game*


If you select your last card in my tool, and the sum adds up to 18, you will get the following message.


*Winning message in my tool*


If you now go to the game’s tab, you will see the victory screen!


If the sum of your cards does not add up to 18, you will see the following message.


*Losing message in my tool*


If you want to test the tool out yourself, you can find it at [https://grumpinout.be/RAT](https://grumpinout.be/RAT)


Thanks [TheXSSRat](https://twitter.com/theXSSrat) and [BugPoc](https://twitter.com/bugpoc_official) for the fun challenge and nice CSP bypass!

---

*Originally published on [Medium](https://infosecwriteups.com/hacking-bugpocs-18-game-xss-challenge-hosted-by-the-xxs-rat-f3f1adc04c8). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
