# :sleuth_or_spy: How I Hacked 1000 + Tesla Cars using OSINT

> **Original Source:** [How I Hacked 1000 + Tesla Cars using OSINT](https://infosecwriteups.com/how-i-hacked-1000-tesla-cars-using-osint-4cd837b8c530)
> **Platform:** infosecwriteups.com | **Category:** `OSINT`

---

# How I Hacked 1000 + Tesla Cars using OSINT


I am Harish SG, a security researcher who studies Masters in Cybersecurity at UT Dallas and AI security intern at Cisco,previously hunted on the Microsoft Bug Bounty Program and Google VRP


I am sharing this article for security awareness and educational purposes only and I am sharing only personal opinions and none of these are related to my work at Cisco. I am not responsible if someone abuse this methods against tesla car owner and I wrote this article to bring awareness among tesla owner and Note this is not a vulnerability in Tesla vehicle or Tesla’s infrastructure


In this article I am gonna share How I used OSINT techniques to hack tesla cars and what was the reply from tesla when I reported about this to them and How can impacted tesla owners protect themselves


What is teslamate?


TeslaMate is an open-source, self-hosted data logger for your Tesla vehicle. It’s designed for Tesla owners who want detailed insights into their driving habits, charging behavior, efficiency, and other metrics related to their Tesla vehicle.


Here are some features and aspects of TeslaMate:


Detailed Dashboards: TeslaMate provides visual dashboards that display data on drives, charges, efficiency, and more. It makes use of Grafana for creating visually appealing and detailed data visualizations.


Charging Stats: It provides insights into your charging habits, how much you’ve spent on electricity, efficiency, and more.


Drive Tracking: You can get detailed statistics about each drive, including the path taken, efficiency, and other relevant metrics.


Geofencing: This allows you to define specific areas (like “Home” or “Work”) and get statistics based on those areas. It can help in understanding how much you drive within specific regions.


Privacy: Since TeslaMate is self-hosted, all your data remains with you. Unlike some third-party services that might store your data on their servers, with TeslaMate, you have full control.


Updates & Community: Being open-source means there’s a community around it that can contribute to its development. This can lead to frequent updates, new features, and community support.


Integration with Home Automation Systems: Some advanced users have integrated TeslaMate with their home automation systems to make intelligent decisions based on vehicle state, like adjusting thermostats when the car is nearing home.


I used censys to find teslamate instances using this query “teslamate” i found that most of them secured with authentication


I started to read documentation of the teslamate available here [https://docs.teslamate.org/docs/installation/docker/](https://docs.teslamate.org/docs/installation/docker/) and while read the documentation I found that teslamate can installed and integrated with tesla cars without authentication


## Get Harish SG’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Then I used the following query to find all teslamate dashboard without authentication


Out of curiosity I opened one of results and I found this below response cached by censys. (This is not realtime) this means that instance is misconfigured and it does not have authentication.


I did not opened dashboard since it might be illegal even though it got exposed publicly or it might be legal gray area so I tried to contact owner to get permission but unfortunately I failed in that attempt of finding the owner then out of curiosity to know what can an attacker do if they can access this misconfigured teslamate I started to read their documentation and project’s github repository. I attacker can do following in misconfigured teslamate without authentication.


- Track live location

- check if driver present in that car or not

- check if car is locked or not

- make online car to sleep

- check if trunk of car is open or not

- check if car is in sentry mode or not


*Screenshot from the projects github repo*


*screenshot from Teslamates’repo*


*screenshot from Teslamates’repo*


*screenshot from Teslamates’repo*


above screenshot shows what are the car data attacker can see in the misconfigured teslamate dashboard


How can does this data can be used against tesla owners who have misconfigured teslamate dashboard?


Attacker can do physical damage to the tesla owner who have their cars connect to a misconfigured teslamate dashboard


How can tesla owner who has misconfigured teslamate protect themselves?


- Enable authentication in their teslamate’s instance by following this [https://docs.teslamate.org/docs/guides/traefik](https://docs.teslamate.org/docs/guides/traefik)

- If you are running this instance locally in home server then disable portforwarding of that specific port this dashboard running generally its 4000

- Try to contact services such as Shodan and censys to remove the results of your instance


Response from Tesla when I reported about this issue to them and asked them to send push notification to users to remove this from internet via bugcrowd


Thanks for reading my article!


*Try hacking LLM : *[https://github.com/harishsg993010/DamnVulnerableLLMProject](https://github.com/harishsg993010/DamnVulnerableLLMProject)


*Hacking into Bard* : https://infosecwriteups.com/hacking-google-bard-24f9dfa7b455


*Hacking into Facial Recognition system *: [https://medium.com/bugbountywriteup/hacking-into-facial-recognition-system-using-generative-ai-69a741077f0e](https://medium.com/bugbountywriteup/hacking-into-facial-recognition-system-using-generative-ai-69a741077f0e)


*Follow me on twitter: *[https://twitter.com/CoderHarish](https://twitter.com/CoderHarish)


*Follow me on linkedin* :[https://www.linkedin.com/in/harish-santhanalakshmi-ganesan-31ba96171/](https://www.linkedin.com/in/harish-santhanalakshmi-ganesan-31ba96171/)

---

*Originally published on [Medium](https://infosecwriteups.com/how-i-hacked-1000-tesla-cars-using-osint-4cd837b8c530). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of osint CTF writeups.*
