# :sleuth_or_spy: OSINT Dojo: Sakura. In this article, I learn how to use…

> **Original Source:** [OSINT Dojo: Sakura. In this article, I learn how to use…](https://infosecwriteups.com/osint-dojo-sakura-37c0fded88b)
> **Platform:** infosecwriteups.com | **Category:** `OSINT`

---

## Task 5: Homebound


### Challenge Description


>

Based on their tweets, it appears our cybercriminal is indeed heading home as they claimed. Their Twitter account seems to have plenty of photos which should allow us to piece together their route back home. If we follow the trail of breadcrumbs they left behind, we should be able to track their movements from one location to the next back all the way to their final destination. Once we can identify their final stops, we can identify which law enforcement organization we should forward our findings to.


### Challenge Questions & Answers


>

1. What airport is closest to the location the attacker shared a photo from prior to getting on their flight?


Looking through the attacker’s Tweet history, I saw a picture they posted of some cherry blossom trees before they boarded their flight home. In the photo, I can see a large white obelisk in the distance that appears to be the Washington monument.

*Twitter Post with Washington Monument.*


The closest airport to the Washington monument is the Ronald Reagan Washington National Airport, also known as DCA.

>

2. What airport did the attacker have their last layover in?


The next tweet from the attacker shows the name of a first class lounge they visited for their final layover.


I can see that the lounge belongs to Japan Airlines (JAL) and a quick search on google for the [Sakura lounge](https://www.jal.co.jp/en/inter/service/lounge/hnd/sakura/#top), shows that it is located in Tokyo International Airport, Haneda (HND).

>

3. What lake can be seen in the map shared by the attacker as they were on their final flight home?


The attacker tweeted a satellite image of their home country, which includes a lake.


*Satellite Image.*


Based on previous tweets, I know the attacker was in Tokyo International Airport, Haneda, before boarding their final flight. Pulling up Google maps for Japan, I searched for similar landmarks and found the same island and lake as seen above in the tweet.


*Japan Google Maps.*


Zooming in on the lake, I can see it’s name.

*Lake Name.*

>

4. What city does the attacker likely consider “home”?


Using the information I have collected so far throughout the investigation, I know that the attacker’s nationality is Japanese and lives somewhere in northern Japan. Looking at the list of WiFi SSID’s from earlier, I can see that there is an SSID called “*HIROSAKI_Free_Wi-Fi*”.


*List of SSID’s.*


[Hirosaki](https://en.wikipedia.org/wiki/Hirosaki) is the name of a city in northern Japan and is the answer for this challenge.

*Hirosaki, Japan.*

---

*Originally published on [Medium](https://infosecwriteups.com/osint-dojo-sakura-37c0fded88b). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of osint CTF writeups.*
