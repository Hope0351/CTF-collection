# :sleuth_or_spy: Approaching CTF OSINT Challenges - Learn by Example

> **Original Source:** [Approaching CTF OSINT Challenges - Learn by Example](https://infosecwriteups.com/approaching-ctf-osint-challenges-learn-by-example-b92be1dddc8d)
> **Platform:** infosecwriteups.com | **Category:** `OSINT`

---

## Keeber 1


>

“You have been applying to entry-level cybersecurity jobs focused on reconnaissance and open-source intelligence (OSINT). Great news! You got an interview with a small cybersecurity company; the Keeber Security Group. Before interviewing, they want to test your skills through a series of challenges oriented around investigating the Keeber Security Group.


The first step in your investigation is to find more information about the company itself. All we know is that the company is named Keeber Security Group and they are a cybersecurity startup. To start, help us find the person who registered their domain.”


### Solution:


A simple google search for: *Keeber Security Group *gets us to the company’s website: *keebersecuritygroup.com*


*Photo by Author*


To identify who registered the site, I used the *whois *Linux command which retrieves various metadata about a given domain.


By running: `*whois keebersecuritygroup.com*`, we get the flag:


*Photo by Author*


`*flag{ef67b2243b195eba43c7dc797b75d75b}*`

## Keeber 2


>

“The Keeber Security Group is a new startup in its infant stages. The team is always changing and some people have left the company. The Keeber Security Group has been quick with changing their website to reflect these changes, but there must be some way to find ex-employees. Find an ex-employee through the group’s website.”


### Solution:


For this challenge, the sentence I have marked in bold in the challenge description is the key to finding the flag.


Browsing to the *Team* section on the *Keeber Security Group* company website reveals 6 employees:


*Photo by Author*


That is to be expected as the description clearly says that the group has been quick with updating their website.


So how can we get access to a previous version of the website which will hopefully still contain information regarding the ex-employee in question?


For that purpose, we can use the [Wayback Machine](https://web.archive.org/). The Wayback Machine is a digital archive of the World Wide Web that stores archived copies of obsolete web pages.


When looking for the team page we see that the oldest copy present is from April 19th:


*Photo by Author*


Clicking on the archived version of the page and scrolling down will get us the ex-employee *Tiffany Douglas* as well as the desired flag:


*Photo by Author*


`flag{cddb59d78a6d50905340a62852e315c9}`

## Keeber 3


>

“The ex-employee you found was fired for “committing a secret to public GitHub repositories”. Find the committed secret, and use that to find confidential company information.”


The Keeber Security Groupwebsite contained a link to their Github account. By examining the commit history for the *security-evaluation-workflow* repository, we can see a suspicious commit message stating *“Removed Secret from repository”*:


*Photo by Author*


By clicking on the above-mentioned commit and looking at the diff we can see the actual secret in a file called *asana_secret.txt*.


*Photo by Author*


At first glance it doesn’t say much, so I thought I’ll do some Googling to find out what Asana is and how this string can be used. After a bit of digging around the [Asana documentation](https://developers.asana.com/docs/using-terminal), I came across this handy text box which describes how Curl can be used in order to query the Asana API:


*Photo by Author*


As can be seen ☝️, the last parameter in the curl command resembles the secret we have identified in Git. This must be the API token.


All we need to do now is to run the following curl command:


```
curl https://app.asana.com/api/1.0/users/me -H “Authorization: Bearer REDACTED_ASANA_TOKEN”
```


We get the following response:


```
{“data”:{“gid”:”1202152286661684",”email”:”keebersecuritygroup@protonmail.com”,”name”:”flag{49305a2a9dcc503cb2b1fdeef8a7ac04}”,”photo”:null,”resource_type”:”user”,”workspaces”:[{“gid”:”1202152372710256",”name”:”IT”,”resource_type”:”workspace”},{“gid”:”1146735861536945",”name”:”My Company”,”resource_type”:”workspace”},{“gid”:”1202202099837958",”name”:”Marketing”,”resource_type”:”workspace”},{“gid”:”1202201989074836",”name”:”Informatique”,”resource_type”:”workspace”},{“gid”:”1202203933473664",”name”:”Engineering”,”resource_type”:”workspace”},{“gid”:”1202205585474112",”name”:”Design”,”resource_type”:”workspace”},{“gid”:”1202206423101119",”name”:”IT”,”resource_type”:”workspace”},{“gid”:”1202166412558403",”name”:”richdn.com”,”resource_type”:”workspace”},{“gid”:”1202206546743807",”name”:”IT”,”resource_type”:”workspace”}]}}
```


Which contains our flag: `flag{49305a2a9dcc503cb2b1fdeef8a7ac04}`

## Keeber 4


>

“The ex-employee also left the company password database exposed to the public through GitHub. Since the password is shared throughout the company, it must be easy for employees to remember. The password used to encrypt the database is a single lowercase word somehow relating to the company. Make a custom word list using the Keeber Security Groups public-facing information, and use it to open the password database.”


(Hint: John the Ripper may have support for cracking .kdbx password hashes!)


As you can probably guess, the hint plays an important role in solving this challenge.


But first, we need to find the password database. We return to the company Github page and specifically examine the [password-manager](https://github.com/keebersecuritygroup/password-manager) repository to find the desired database file:


*Photo by Author*


What’s a `.kdbx` file you ask?


I asked Google the same question and learned that this extension is usually related to data files created by the KeePass Password Safe application.


The next question that comes to mind is how do we crack such a `.kdbx` file?


Since I have never encountered this format, let alone cracked such a file, once again I turned to Google looking for answers. The first link in the search results was to [this great guide](https://www.thedutchhacker.com/how-to-crack-a-keepass-database-file/) offering a detailed walkthrough on how to crack `.kdbx` files using [John the Ripper](https://www.openwall.com/john/) or [Hashcat](https://hashcat.net/hashcat/).


*Photo by Author*


According to the guide (and the challenge description), there are 3 stages we need to go through to crack the database file:


- Extract the password hash from the database file

- Generate a custom wordlist

- Use john-the-ripper to crack the password hash using the generated wordlist


To extract the hash, we run the following command:


`keepass2john ksg_passwd_db.kdbx > Keepasshash.txt`


*Photo by Author*


Now that we have the password hash, in order to generate the wordlist, we will use[Custom Word List generator](https://digi.ninja/projects/cewl.php) (CeWL) and provide it with the company’s Github page:


```
cewl [https://github.com/keebersecuritygroup/security-evaluation-workflow](https://github.com/keebersecuritygroup/security-evaluation-workflow) -w word_list.txt — lowercase -d 1
```


Lastly, we will run john-the-ripper using the generated wordlist in order to crack the password hash:


`זדאגjohn --wordlist=word_list.txt Keepasshash.txt`


## Get Yotam Perkal’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


All that is left is to wait patiently for the results and we get our password:


*Photo by Author*


```
craccurrelss
```


In order to get the flag, I have used an online service called [app.keeweb.info](https://app.keeweb.info/):


*Photo by Author*


Alternatively, as I later found, there is also a utility called [keepassx](https://www.keepassx.org/)​​ which can be used to open the database file and get the flag.


`flag{9a59bc85ebf02d5694d4b517143efba6}`

## Keeber 5


>

“The ex-employee in focus made other mistakes while using the company’s GitHub. All employees were supposed to commit code using the keeber-@protonmail.com email assigned to them. They made some commits without following this practice. Find the personal email of this employee through GitHub.”


This challenge was actually pretty straightforward. Since the description says that the ex-employee has committed code using a personal email, I simply downloaded the repository and ran the following git command in order to get all of the users and email addresses which committed code to the repo: `git shortlog -sne --all` and found the flag:


*Photo by Author*


`flag{2c90416c24a91a9e1eb18168697e8ff5}`


Note: As can be seen in the `git shortlog` command [documentation](https://git-scm.com/docs/git-shortlog), the `-s` flag suppresses the commit descriptions while the `-e` flag adds the author’s email address.

## Keeber 6


>

“After all of the damage the ex-employee’s mistakes caused to the company, the Keeber Security Group is suing them for negligence! In order to file a proper lawsuit, we need to know where they are so someone can go and serve them. Can you find the ex-employee’s new workplace? The flag is in regular format, and can be found in a recent Yelp review of their new workplace.


(Hint: You will need to pivot off of the email found in the past challenge!)”


For me, this was the most challenging and enjoyable challenge in the entire CTF. Since I was lacking any meaningful OSINT experience, I didn’t go about solving it in a very methodological way, yet I have learned a lot in the process.


I started by trying to google the *tif.hearts.science@gmail.com* email address without much success.


Then, I found on her Github page that while she was working for Keeber Security Group, she lived in Maine:


*Photo by Author*


This led me to assume that her new place of work will also be around the same area.


Unfortunately, trying to search for the email address on Yelp was also a dead end, and there are far too many businesses in the Maine area, let alone reviews, for it to be realistic to go over them one by one. We need to find additional information that will help us narrow down the search.


After a few hours without much progress, I realized that this challenge probably requires a more methodological approach.


After a bit of exploration, I learned that there are designated tools for such tasks. One of these tools is [sherlock](https://github.com/sherlock-project/sherlock), which allows finding social-media accounts by username:


*Photo by Author*


There are some false positives, but the relevant account for this challenge turns out to be [Tiffany’s Instagram account](https://www.instagram.com/tif.hearts.science/).


Her Instagram account only contains 6 posts, yet a ton of useful information.


For example:


*Photo by Author*


​​These two images make it pretty clear that Tiffany has abandoned her software engineering ambitions and has found a new job is in a hotel.


We are getting closer…


Now all that is left is to find the exact hotel. Another hint we get is in the following image which tells us the hotel in question has an indoor pool:


*Photo by Author*


At this point, I felt I had enough information to try and identify the exact hotel.


I went over to TripAdvisor and started going over hotels in the Maine Area that have an indoor pool, until I came across Residence Inn or more specifically, these images:


*Photo by Author*


*Photo by Author*


The fire pit immediately caught my eye as it resembles the fire pit I saw in one of Tiffany’s Instagram posts:


*Photo by Author*


Yelping the Residence Inn indeed gets us Tiffany’s review and the desired flag:


*Photo by Author*


`flag{0d70179f4c993c5eb3ba9becfb046034}`

### 🌐 A Few Words Regarding Geolocation 🌐


This challenge was meant to be mainly a geolocation challenge. Geolocation based OSINT probably deserves a post of its own. If you wish to get a glimpse of the level of complexity and ingenuity that can be reached during geolocation based investigations, I recommend taking a look at this [article](https://exposingtheinvisible.org/en/guides/geolocating-images-suncalc/). For some hands-on experience practicing geolocation challenges, take a look at:


- [GeoGuessr](https://www.geoguessr.com/), a geography game, in which you are dropped somewhere in the world in a street view panorama and your mission is to find clues and guess your location on the world map.

- [Verif!cation Quiz Bot](https://twitter.com/quiztime), a Twitter account which post regular short geolocation challenges.


You can find nice geolocation approaches for solving this challenge that utilized this 👇 additional image as clue [here](https://bytebreach.com/nahamcon-2022-ctf-writeup/#20-keeber-osint), and [here](https://github.com/piyagehi/CTF-Writeups/blob/main/2022-NahamCon-CTF/Keeber.md#description-5).


Note: *Challenges 7 and 8 were solved after the competition had ended. I’m providing their solutions here for completeness.*

## Keeber 7


>

“Multiple employees have gotten strange phishing emails from the same phishing scheme. Use the email corresponding to the phishing email to find the true identity of the scammer. The flag is in regular format.


(Note: This challenge can be solved without paying for anything!)”


When looking at the phishing email content we see that the fraudster has provided *cheerios.fanatic1941@gmail.com* as a contact email address:


*Photo by Author*


In this case, trying to track the user name via sherlock did not help.


After the competition has concluded I have learned that there is a powerful tool called [Maltego](https://www.maltego.com/) which its community addition can be used in order to identify a Myspace account associated with the above-mentioned email address under the user *cereal_lover1990*:


*Photo by Author*


And in the [Myspace page](https://myspace.com/cereal_lover1990) we find the f​​lag: `*flag{4a7e2fcd7f85a315a3914197c8a20f0d}*`


Note: Maltego isn’t very intuitive to use and probably deserves a blog post of its own, but in this case all that was needed was to:


- Create a new graph

- Drag the email palette onto it and edit it to reflect the *cheerios.fanatic1941@gmail.com* email address

*Photo by Author*


3. Right-click on the email icon and run some of the available transformers. In this case, the relevant transformer was: *Transform To Myspace Account*.

*Photo by Author*

## Keeber 8


>

“Despite all of the time we spend teaching people about phishing, someone at Keeber fell for one! Maria responded to the email and sent some of her personal information. Pivot off of what you found in the previous challenge to find where Maria’s personal information was posted.”


Now that we have the alternative username *cereal_lover1990*, we can resort back to sherlock and see what comes up:


*Photo by Author*


This time, the relevant link is the link to [Pastebin](https://pastebin.com/u/cereal_lover1990), in which we find Maria’s personal information along with our flag:


*Photo by Author*


`flag{70b5a5d461d8a9c5529a66fa018ba0d0}`

## Final Thoughts


This concludes the NahamCon CTF series of OSINT challenges.


I learned a lot while solving these challenges and I can’t help but appreciate the enormous effort that was probably put into building them (kudos to @matlac#2291 and @Gary#4657).


I hope I was able to convey my thought process and learnings.


Feel free leave your thoughts in the comments or reach out directly via [Twitter](https://twitter.com/pyotam2) if you have any questions.

---

*Originally published on [Medium](https://infosecwriteups.com/approaching-ctf-osint-challenges-learn-by-example-b92be1dddc8d). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of osint CTF writeups.*
