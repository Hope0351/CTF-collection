# :sleuth_or_spy: OSINT Industries CTF 2025 Write Ups

> **Original Source:** [OSINT Industries CTF 2025 Write Ups](https://0xmanikmaya.medium.com/osint-industries-ctf-2025-write-ups-fb7ffc1079d7)
> **Platform:** 0xmanikmaya.medium.com | **Category:** `OSINT` | **Year:** 2025

---

# OSINT Industries CTF 2025 Write Ups


## Table of Contents


## Preface


I would like to express my sincere appreciation to Nathaniel Fried ([https://www.linkedin.com/in/nathanielfried/](https://www.linkedin.com/in/nathanielfried/) ) for organizing and making this OSINT CTF available, providing an excellent platform for everyone to sharpen their OSINT skills. This challenge has been an incredible opportunity to engage with and learn from some truly remarkable talents, including:


A special shout-out is also due to Megadose Palenath ([https://www.linkedin.com/in/megadose/](https://www.linkedin.com/in/megadose/) ), Tom Church ([https://www.linkedin.com/in/tschurch/](https://www.linkedin.com/in/tschurch/) ), Brett Redman ([https://www.linkedin.com/in/brettredman/](https://www.linkedin.com/in/brettredman/) ) and everyone involved in the OSINT Industries CTF for their contributions. The challenge has proven to be an outstanding exercise in OSINT methodologies, GEOINT, and a clear demonstration that OSINT is far more than just Google searching. It requires a systematic approach to connect the countless pieces of data scattered across the vast ocean of publicly available information. I sincerely hope that OSINT Industries will consider making this CTF a regular event. it’s been an incredibly valuable learning experience, and I’m looking forward to the next one! Also… haven’t had the opportunity to obtain the first blood, so would like to have more opportunities in the future for some free credits hahaha

## Write Ups


### Challenge #1 [GEOINT] Find the Masked Man


```
Description: A photograph was taken in Paris on December 3rd, 2023, around 18:00.
Your mission is to identify the nearest metro station to the location where the masked man was photographed.
This challenge focuses on applying GEOINT and OSINT techniques to analyze urban structure, lighting conditions, environmental clues, and the layout of Parisian transportation infrastructure.

Context
Investigators received an image showing a masked individual standing in a central and upscale district of Paris.
The metadata and environmental observations indicate:
• The image was taken on December 3rd, 2023
• The approximate time was 18:00 (early evening)
• The location is in Paris, within a central and upscale area
• The scene is located near the intersection of a Rue and an Avenue
Your objective is to determine the closest metro station to the photographed location, using only the contextual and visual clues provided.

Mission
Analyze the given information and identify the nearest Paris metro station.
The final answer must follow a strict flag format.

Flag Format
The flag is simply the name of the nearest metro station to the scene.
Participants must submit the flag exactly like this:
OSINT{STATION_NAME}

Rules:
• All uppercase
• No accents
• Use underscores between words
```


For me, the very first step whenever I am tasked with an OSINT investigation involving images — especially when I know that metadata will not be part of the analysis — is to conduct a reverse image search. This approach helps quickly determine whether the image has appeared elsewhere online, identify its original source, uncover related contexts, and detect potential reuse or manipulation. As an initial screening technique, reverse image searching provides a fast and effective way to establish baseline context before proceeding with deeper analytical steps.


From the reverse image search results, the only information obtained was that the possible location is Paris, France. However, this detail was already provided in the challenge description and did not add any new value to the analysis. Consequently, the investigation progressed to a closer examination of the visual details within the image itself in order to extract additional, actionable information.


As I am not personally familiar with Paris beyond general knowledge — such as the existence of the Eiffel Tower — I used AI assistance to help narrow down the possible location. To do this, I employed the following prompt to guide the analysis:

>

“Can you help me identify a central, upscale location in Paris with paved streets (rather than asphalt), buildings at least 7 stories tall, and commercial businesses on the first floor? The location should feature digital advertisement panels along the road, be situated at the intersection of a rue and an avenue, and have trees lining the road. Additionally, it should be located near a metro station”


Therefore, we used this information as a guide to conduct further exploration through Google Maps and Street View.

>

Disclaimer: This approach may appear inefficient due to its indirect nature. However, it was undertaken given my limited familiarity with Paris and its metro system, and it served as a practical method to progressively narrow down the potential location based on visual and contextual cues.


With the assistance of AI, we identified an initial potential location around Avenue des Champs-Élysées, which functions as a central hub connecting several major avenues. One location that stood out in particular was the intersection of Rue La Boétie and Avenue Franklin D. Roosevelt, where a metro station is conveniently located nearby. Based on this assessment, I proceeded to place Google Street View at this intersection to examine the area in greater detail.


The Street View image closely matches the photo provided in the challenge. Given the striking similarities, we can confidently confirm that this location has the highest likelihood of being where the masked man took the selfie.


Therefore, the closest Metro station is Saint-Philippe du Roule.

*Challenge #1 Flag*

### Challenge #2 [OSINT] Holehe & The Secret Email


```
Description
You are investigating the origins of a popular OSINT tool used to pivot from email addresses to online accounts: Holehe.
Behind every tool, there is a creator — and behind that creator, there is an email address.
Your mission is to trace back the very first appearance of the creator’s email address online and determine the exact date it was created.

Objective
Using open-source intelligence only, find:
1. The creator of Holehe
2. The public email address used for Holehe
3. The exact creation date of this email address
The final flag must be based only on this date.

Flag Format
OSINT{DD-MM-YYYY}
Example (not the real answer):
OSINT{01-01-2020}

Rules
• Use only legal, open-source information
• Do not contact the developer
• No exploitation, intrusion, OSINT only
• Everything can be found through:
o Code repositories
o Public profiles
o Archives
o Lawful OSINT sources
```


This challenge requires us to use GitHub as a platform to gather more information. Having a GitHub account would be advantageous, as it provides access to additional features and more extensive search results.


Our first task is to determine the creator’s email address and the date of their first online appearance. The creator of HOLEHE is PALENATH, and his GitHub page is


According to the information in his profile, he has listed megadose@protonmail.com as his email address. However, there may be another email address associated with his earlier contributions that could potentially be traced through his commits. Therefore, we need to search for the term “email” across his commits and contributions.


The earliest contribution associated with him is the Fl0wj0b repository.


However, this repository does not contain any email addresses. Consequently, we moved on to another project.


The second oldest repository that he contributed to is toutatis.


On December 29, 2023, he updated the README.md file to include the email megadose@protonmail.com. This update leads us to use this email address as a reference to check for any earlier changes or potential email addresses that may have been replaced.


The earliest mention of the email address in this repository appears in the CODE_OF_CONDUCT.md file, where megadose@protonmail.com is listed. This suggests that this email address has been in use since the beginning.


Since the email address is associated with the protonmail.com domain, we can check the timestamp of this email, which can then be converted into an account creation date. This approach was inspired by a post on X


[https://x.com/GONZOs_int/status/1336721581561815042](https://x.com/GONZOs_int/status/1336721581561815042)


Therefore, we have the following result:


Using the provided timestamp 1610617266, we employed AI to convert it into a readable date.


The resulting account creation date is January 14, 2021.

*Challenge #2 Flag*

### Challenge #3 [INTERPOL] The Hadjej File


```
Important
This is a real Interpol Red Notice.
Participants may verify the information on the official Interpol website:
https://www.interpol.int/How-we-work/Notices/Red-Notices/View-Red-Notices#2025-86873
________________________________________

Target Information
Name: Olivier HADJEJ
Date of birth: 17/07/1967
Countries linked: France, Israel
Wanted by France for:
• Fraud committed by an organised group
• Money laundering connected to organised fraud
• Participation in a criminal conspiracy punishable by up to 10 years of imprisonment
This data originates from the official Red Notice.
________________________________________

Objective
Using legal open-source intelligence methods, identify one email address that can be reasonably linked to the individual named above.
Your final answer must follow this exact format: OSINT{email} Example format (not the solution): OSINT{john.doe@example.com}
Rules
• Use only legal OSINT methods
• No direct contact
• No intrusion or bypassing access controls
```


My approach to this challenge is based primarily on guesstimation, acknowledging that a degree of luck plays a role, which, while not methodical, can still yield useful insights. This challenge also illustrates how a potential data breach can be ethically leveraged for analysis.


I particularly enjoy the term “guesstimating,” coined by one of my colleagues, as it provides a more accurate description for situations where we lack a complete data set. Through analysis of likelihood, augmented by AI, we can make educated guesses or estimates. However, in a more formal investigative context, guesstimation cannot be relied upon as a legal basis for proof, as it is prone to biases and lacks the rigorous standards required for conclusive evidence.


Based on available documents, Olivier Hadjej is associated with two companies engaged in engineering and computer-related activities. As a result, it can be inferred that Olivier Hadjej is likely well-versed in technological advancements. Additionally, we found a Facebook page under the name “Olivier Hadjej,” which provides an opportunity to cross-check his identity by comparing the photos uploaded on the page with the image published in the Interpol Red Notice.


He also uploaded his driver’s license, which displays the exact same date of birth as provided in the Interpol Red Notice. Therefore, we are confident that this is most likely Olivier Hadjej’s Facebook account.


Using AI, I employed the following prompt to guide my search:

>

“If I was born in Israel in 1967 and later moved to France at some point in my life, and I am someone who keeps up with technological advancements, what are some possible email domain addresses I might have used?”


From the results, we have identified several domains associated with Olivier Hadjej: @hotmail.com, @walla.co.il, @netvision.net.il, and @012.net.il. Additionally, there are two potential usernames under consideration:


- Olivierhadjej, which is a straightforward use of his full name,

- Olivier.hadjej, which is derived from the ID of his alleged Facebook page.


To investigate whether these email addresses or usernames have been involved in any data breaches, we will use the site Have I Been Pwned. This platform is a legitimate and ethical tool that allows individuals and organizations to check if their personal information has been compromised in known data breaches.


Why "Have I Been Pwned" is Legal and Ethical:
"Have I Been Pwned" operates within legal and ethical boundaries for several reasons:


- Data Privacy Compliance: The service does not store or retain any personal data entered into its system. When a user checks an email or username, the site only checks the provided data against publicly available information from breaches that have been made public by other sources, ensuring no personal data is stored or misused.

- Transparency: The platform is fully transparent about its data sources and how it works. It compiles information only from known and verified data breaches that have been publicly disclosed. It does not collect any new data beyond what is already available to the public.

- User Consent: Users voluntarily choose to check their email addresses or usernames on the platform, which means they are fully aware of and consenting to the search. No third-party can use the platform to check someone else's data without permission.

- Security Benefits: By using the service, individuals can be notified of any data breaches involving their information, allowing them to take proactive steps, such as changing passwords or monitoring accounts, to safeguard their personal security. This aligns with the principles of responsible data use and cybersecurity.

- Public Good: The website’s purpose is to raise awareness about the risks of data breaches and to encourage individuals to take steps to protect their personal information. It is a tool designed to protect people and prevent harm, which is the essence of ethical cybersecurity practice.


Therefore, using "Have I Been Pwned" is a legally sound and ethical approach to verifying if someone’s information has been exposed in any known data breaches.


Our first email candidate has been flagged as having a breach history, which significantly increases the likelihood that this email is indeed exist. Given this finding, I am more confident in proceeding with the first of five potential attempts to use this email as a flag for further investigation. The breach history suggests that this email may be tied to past incidents of data compromise, making it a stronger lead to pursue in our inquiry.

*Challenge #3 Flag*

### Challenge #4 [INTERPOL] The Benarroch File


```
Important
This is a real Interpol Red Notice.
Participants may verify the information on the official Interpol website:
https://www.interpol.int/How-we-work/Notices/Red-Notices/View-Red-Notices#2025-86779
This challenge is intended exclusively for OSINT training purposes.
________________________________________

Target Information
Name: BENARROCH, INONE
Date of birth: 19/05/1978
Age: 47
Country link: Israel, France
Wanted by France for:
• Fraud committed by an organised group
• Money laundering related to organised fraud
• Participation in a criminal conspiracy punishable by up to 10 years of imprisonment
This information comes from the official Interpol Red Notice.

Objective
Using only legal open-source intelligence methods, identify the last known address of the individual in the year 2015.
Your final answer must follow this exact format, in this exact order: OSINT{[street number], [street name], [postal code] [city]}
Example format (not the solution): OSINT{10, Downing Street, SW1A 2AA London}

Rules
• Use only legal, open-source methods
• No contact with the target
• No intrusion or bypassing access controls
```


Based on the INTERPOL Charges statement, BENARROCH was charged for Organized fraud; Money laundering; Complicity in the placement, concealment, or conversion of the proceeds of organized fraud; Participation in a criminal conspiracy to commit a crime punishable by 10 years’ imprisonment.


That kind of charges can’t be done by an individual alone. A seemingly-legal business need to be established. Think of it like doing a laundry, no matter what, you need a tool to wash it. A legit, tangible tool. Doesn’t have to be a washing machine, can be as simple as rock on the river, yet it is tangible.


Therefore, our first step is to look for the namer INONE BENARROCH.


Some the top results include a site from Pappers. I don’t know what Papper is, however, we have Copilot AI to answer our question.


Based on the explanation that Pappers is a French platform that offers free access to legal, financial, and institutional information about French companies, including official data from [Open Data sources](https://www.google.com/search?q=Open+Data+sources&sca_esv=1a5899b9da7a2cf9&sxsrf=AE3TifNScbYQyie1MG9UhKu_rSLdnEFxZg%3A1766554061755&ei=zXlLadztLcS6seMPwpPCkQI&ved=2ahUKEwjEl5HxvtWRAxU2XmwGHTlfGKkQgK4QegQIARAE&uact=5&oq=what+is+pappers+site+in+frech&gs_lp=Egxnd3Mtd2l6LXNlcnAiHXdoYXQgaXMgcGFwcGVycyBzaXRlIGluIGZyZWNoMgcQIRigARgKMgcQIRigARgKSKcuUIMDWJQtcAV4AJABAJgBmAGgAYAdqgEEOC4yNbgBA8gBAPgBAZgCJaAC2R7CAgoQIxiABBgnGIoFwgILEAAYgAQYsQMYgwHCAgoQABiABBhDGIoFwgIREC4YgAQYsQMY0QMYgwEYxwHCAgQQABgDwgIIEAAYgAQYsQPCAgUQABiABMICCBAuGIAEGLEDwgIOEC4YgAQYxwEYjgUYrwHCAhcQLhiABBixAxiXBRjcBBjeBBjfBNgBAcICBxAjGLECGCfCAhUQLhiABBixAxjRAxiDARjHARgKGAvCAgcQABiABBgKwgIPEAAYgAQYsQMYgwEYChgLwgIMEAAYgAQYsQMYChgLwgIJEAAYgAQYChgLwgIKEAAYgAQYChjLAcICCRAuGIAEGAoYC8ICDBAuGIAEGLEDGAoYC8ICBBAjGCfCAgUQLhiABMICCBAAGIAEGMsBwgIHEAAYgAQYDcICBhAAGA0YHsICBhAAGBYYHsICCBAAGAoYDRgewgIIEAAYCBgNGB7CAgUQABjvBcICCBAAGIAEGKIEwgIFECEYkgPCAgUQIRifBZgDAIgGAboGBggBEAEYFJIHBDUuMzKgB6v8AbIHBDEuMzK4B8YewgcLMC4xNi4xNy4zLjHIB6EBgAgA&sclient=gws-wiz-serp&mstk=AUtExfCHNbkY4SPlVqYBIJfiaaKRgaBt_1idK6QnFVjhguzAPKg7cQSGsEaiv_AuYljkoA8eBfvOifDEPI0UqIhyyJmOD9a3PxsGMO_6ur7DNRnx44afLEp3BhRVGwtZs9tZebUU7_EGp0u6Xfbp2qrDPOYalJHkufAqTfZNwLxaH4AzniVcE8nSTNx3O_BPXmrlrgQaJlJx4Wjw7VGh1OtM2O52_mCIWi_eXZ1wNKzZBpD6XaSrLA9NG8VSSAmMIt9NQHZ5SvukzMO3OkmRqxy2B6Mp&csui=3) like SIREN/SIRET numbers, financial statements, and legal texts, functioning as a comprehensive search engine for business and public data in France and beyond.


Benarroch is wanted by the France, therefore, it is make sense that his ‘business’ may be based on France.


There are two companies associated with INONE BENARROCH, however, the challenge asked for his last known address in 2015. Therefore, the PRESTIGE CONSEIL HABITAT seems like the most logical option for us since it was established in 2014.


They also have a document dated back to 09/12/2015


Within the document, Monsieur INONE BENARROCH is known to have address in 95 Rue Sedaine 75011 Paris

*Challenge #4 Flag*

### Challenge #5 [OSINT] Depix


```
Target Information
A passenger posted a photo of their flight ticket online.
The ticket is heavily pixelated, but key details remain partially recoverable.
Your task is to identify:
• The passenger’s first and last name
• The seat number
• The arrival airport IATA code
All information can be deduced through lawful open-source intelligence techniques.

Objective
Using only legal OSINT methods, extract the required information from the depixelated ticket.
Your final answer must follow this exact format, in this exact order: OSINT{NAME_SURNAME_SEATNUMBER_AIRPORTIATA}
Example format (not the solution):
OSINT{JOHN_DOE_14A_JFK}

Rules
• Use only legal, open-source methods
• No contact with any individuals
• No intrusion or unauthorized access


```


In standard OSINT (Open Source Intelligence) practices, when analyzing a picture, it is generally understood that metadata is less likely to provide valuable insights. Therefore, the next logical step is to proceed with reverse image searching. I utilized several reverse image search tools, including Google Image Search, Yandex Image Search, and TinEye.


Among these, TinEye provided the most direct and clear results, which led us to an identical boarding pass.


The depixelated boarding pass revealed key information, including the first name and surname as Michael Chen and the seat number as 3D.


To verify the IATA code, I referred to the official IATA website:following website


After performing a search, I confirmed that the 3-letter IATA code for Shanghai Pudong Airport is PVG.

*Challenge #5 Flag*

### Challenge #6 [OSINT] On The Traces of the Silk Road Black Market


```
Important
This challenge is based on publicly documented information related to Ross Ulbricht,
creator of Silk Road.
All elements are used exclusively for OSINT training purposes.
No private, leaked, intrusive, or unethical methods are allowed.
________________________________________

Background
In 2010, before his arrest, Ross Ulbricht celebrated his girlfriend’s birthday at a specific location.
Through careful open-source analysis of information publicly available from that period,
it is possible to determine:
1. The exact name of the location linked to the birthday celebration
2. The girlfriend’s day and month of birth, which can be inferred from contextual clues found within legal, publicly accessible sources
The solution does not require guessing or access to restricted data.
It can be identified through advanced OSINT methodology.
________________________________________

Objective
Using only lawful and open-source intelligence techniques, identify:
1. The name of the location associated with the 2010 birthday event
2. The girlfriend’s day and month of birth
Your final answer must follow this exact format, in this exact order:
OSINT{LOCATION_NAME_DD-MM}
Example format (not the solution):
OSINT{PLACE_23-09}
________________________________________

Rules
• Use only legal, open-source information
• No contact with any individuals
• No intrusion, access bypassing, or password attempts
• No use of private or leaked data
```


The first step I did was find out every publication about ROSS ULBRICHT. It wasn’t hard to find who his girlfriend was because she appeared on a few documentaries and publications:


[https://www.imdb.com/name/nm8682963/](https://www.imdb.com/name/nm8682963/)


Ross Ulbricht created Silk Road in 2010, prior to its official launch in 2011. According to multiple open sources, during this period he was in a relationship with an individual named Julia Vie. A basic name-based search on Facebook returned several profiles using the name *Julia Vie*; however, one account appeared particularly relevant based on contextual consistency and content alignment:


To further assess this attribution, a photograph published by CBS was compared with an image uploaded to the identified Facebook account:


An AI-assisted facial comparison indicates that the two images are likely to depict the same individual. While AI-based face comparison alone is not sufficient for definitive identification, this finding serves as corroborative evidence when considered alongside additional contextual indicators.


However, simply relying on AI face comparison is not enough to conclusively confirm the identity. On April 27, 2017, Julia reposted Nick Bilton’s post about Ross Ulbricht, further indicating her connection to him. This additional context strengthens the likelihood that the individual in question is indeed Julia Vie.


*[https://www.facebook.com/share/p/1DRiaptL9G/](https://www.facebook.com/share/p/1DRiaptL9G/)*


Based on facebook username on the url, I was able to navigate to her business/personal Facebook page:[https://www.facebok.com/Viviansmuse](https://www.facebok.com/Viviansmuse) . On this page, she also posted about Ross Ulbricht, further confirming her connection to him.


*[https://www.facebook.com/share/p/1CyJYNsMog/](https://www.facebook.com/share/p/1CyJYNsMog/)*


Based on the following documentary


At minute 8:22 of the referenced documentary, she states that she was studying photography when she met Ulbricht. This detail is consistent with information obtained from other open sources and further strengthens the attribution between her and Ross Ulbricht.


Based on the cumulative evidence, it is reasonable to assess that Julia Vie, operating under the photography business name Vivian’s Muse, is the individual in question — specifically, Ross Ulbricht’s girlfriend around 2010.


This confirmation is analytically useful, as it provides a reliable anchor for further biographical research, particularly with respect to determining her date of birth. Additionally, this attribution enabled further OSINT pivoting: her Instagram account was identified at Instagram.com/viviansmuse, which in turn links to her current husband’s Instagram account at [https://www.instagram.com/lerustique_shackleford/](https://www.instagram.com/lerustique_shackleford/). These publicly available profiles offer additional contextual insights that may assist in corroborating personal details through passive analysis.


A review of publicly available posts reveals a recurring pattern relevant to estimating her date of birth. While she has not explicitly published her birthday, posts made by her partner consistently reference September 26 across multiple years. Based on this recurring temporal signal, it is reasonable to assess that her birthday falls within a narrow window between September 24 and September 26. Furthermore, references indicating that she was 34 years old in 2024 suggest a likely year of birth of 1990.


The next analytical step involved identifying potential birthday-related locations that could help further narrow the date. Attempts to retrieve historical Facebook content using the Wayback Machine did not yield useful results. Additionally, none of Julia Vie’s known social media accounts contain posts that directly reference Ross Ulbricht, limiting the usefulness of those platforms for temporal correlation and prompting exploration of alternative data sources.


At this stage, an understanding of U.S. digital culture circa 2010 became relevant. During that period, Yelp was a widely used platform for publishing and discovering business reviews and often functioned as a form of social signaling for both individuals and businesses. Importantly, Yelp restricts certain features to authenticated users only. One such feature, “Find Friends,” enables users to discover connections based on shared email contacts or platform interactions. Leveraging this functionality provided a plausible OSINT pivot to uncover additional contextual information related to her personal timeline through passive analysis.


There are several results for Ross Ulbricht on Yelp, but one stands out as being linked to Vivian’s Muse. This connection could provide additional insights into her relationship with Ross Ulbricht and may offer more clues regarding her personal details and history.


This account also posted a review about a place where they had a birthday party on September 28, 2010. This aligns with the previously mentioned pattern, further suggesting that her birthday is likely around this date. The review could provide more context about the location and potentially validate the birthday details.


Therefore, our flag is AQUARELLE, with the most likely birthday being September 26. However, after several attempts with dates ranging from September 24 to 26, none were successful. Ultimately, I used the date from the Yelp post, September 28, which was accepted.it.

*Challenge #6 Flag*

>

OBJECTION: The challenge specifically states that “The girlfriend’s day and month of birth, which can be inferred from contextual clues found within legal, publicly accessible sources,” which is reasonable given that the girlfriend never explicitly posted her exact date of birth. However, by analyzing the history of her posts and connections, we were able to narrow down her date of birth to somewhere between September 24 and 26, 1990. The accepted date, however, is September 28, which aligns with the date Ross posted a review on YELP. This discrepancy contradicts the challenge’s description and may have contributed to some users’ inability to provide the correct answer, leading to the loss of all available attempts. However, official write up that can explain about this will help.


### Challenge #7 [EUROPOL] Operation LOCKERGOGA


```
Important
This challenge has been made by EVO7
This is a real Europol Most Wanted listing.
Participants may verify the information on the official Europol website:
https://eumostwanted.eu/de#/tymoshchuk-timoschuk-volodymyr-viktorovych-volodimir-viktorovich
________________________________________

Target Information
• Name: TYMOSHCHUK (ТИМОЩУК), Volodymyr Viktorovych (Володимир Вікторович)
• Date of birth: October 2, 1996 (29 years old)
• Countries linked: France, Ukraine
________________________________________

Wanted by France for
• Computer-related crime
• Participation in a criminal organisation
• Racketeering and extortion
This data originates from the official Europol Most Wanted listing.
________________________________________

Case Summary (From official listing)
From 2018 to 2020, Volodymyr TYMOSHCHUK and accomplices participated in deploying the LOCKERGOGA ransomware on hundreds of victim companies.
These attacks severely disrupted operations and forced multiple organisations to pay ransom demands.
Total global damages exceeded $18 billion.
________________________________________

Objective
Using legal open-source intelligence methods, identify:
• the licence plate of the vehicle linked to the individual
• its brand
• model
• year of manufacture
• last known mileage
________________________________________

Final Answer Format
Your final answer must follow this exact format, in this exact order:
OSINT{[licence plate number], [brand], [model], [year], [mileage]}
Example format (not the solution)
OSINT{OS 1111 NT, MCLAREN, 750S, 2023, 123KM}
________________________________________

Rules
• Use only legal, open-source methods
• No contact with the target
• No intrusion or bypassing access controls
```


My approach to this challenge was relatively straightforward, though not entirely methodical. It relied heavily on guesstimation and a degree of luck. I began by referencing the aliases and pseudonyms listed in the official Europol announcement, using these as potential usernames to search on popular social media platforms. Given that the individual in question was born in 1996, it was reasonable to assume that he would have an active presence on several widely-used social media platforms such as Twitter/X, Instagram, TikTok, VK, and Facebook.


I initially focused on Instagram as my primary platform for this search. By using the username Deadforz, I was able to locate a photography account associated with this name. However, it seems like it doesn’t hold any valuable association with our possible target.


The searches for Boba and farnetwork yielded no relevant results. However, the search for Volotmsk returned a promising lead — an account with the username @volotmsk___. The profile picture shows a man sitting on a couch. The bio includes UA, which is the two-letter country code for Ukraine (UKRAINA), and Вова, which corresponds to a name listed on the EUROPOL wanted list. These two details strongly correlate with the information provided by Europol.


The account contains only four posts and several highlights. The most recent post features a black Porsche with the registration plate AB 6637 IE. Further investigation using external sources, such as


and


revealed that the vehicle is a 2019 Porsche Cayenne, further linking the profile to the individual in question.


These findings provide a promising connection, and further verification of the account could potentially yield additional relevant information.


One of the highlights on the Instagram account is a video taken from the driver’s seat of a Porsche car. This visual reinforces the connection to the 2019 Porsche Cayenne featured in the recent post, suggesting that the individual behind the account may indeed have access to this vehicle. This detail adds another layer of credibility to the possibility that the account is associated with the person listed on the Europol wanted list. Further investigation into the account and its content could potentially provide more evidence to confirm the mileage.


Through the dashboard of the Porsche, we can observe that the mileage is displayed as 36,921 KM. This specific detail, along with the previous findings, strongly suggests that the vehicle in question is indeed a 2019 Porsche Cayenne with the registration plate AB6637IE. Therefore, our possible flag is the 2019 Porsche Cayenne, with the registration plate AB6637IE and the mileage recorded at 36,921 KM. This information, when cross-referenced with other data, could help strengthen the connection to the individual of interest.


*Challenge #7 Flag*

### Challenge #8 [GRU] GRU Foreign Operations


```
Important
This challenge is intended exclusively for OSINT training purposes.
It simulates an intelligence-related investigation scenario.
No unlawful access, harassment, or real-world interference is permitted.
________________________________________
Challenge
3GRU FOREIGN OPERATIONS
A fragment of an old poem has surfaced in an online dead-drop allegedly used by a former Russian intelligence agent.
It is connected to a high-profile defection case, but nothing in the text is explicit.
Despite the ambiguity, the fragment contains enough indirect indicators — linguistic patterns, temporal references, and operational clues — to reconstruct the event.
________________________________________
Objectives
Using only legal open-source intelligence (OSINT) methods, identify:
1. The NAME and SURNAME of the FSB agent who defected
2. The exact date the covert operation took place (DD/MM/YYYY)
3. The exact place of the operation (2 words)
4. Shortly after the operation, a suspicious dark blue vehicle was reportedly seen parked near the entrance.
o Identify the registration plate of the vehicle
________________________________________
Flag Format (STRICT)
Your final answer must follow exactly this format: Flag format:
OSINT{NAME_SURNAME_DD/MM/YYYY_LOCATION_LOCATION_PLATE}
Formatting rules
• CAPITAL LETTERS ONLY
• Use UNDERSCORES (_)
• Location must contain exactly 2 words → WORD_WORD
• Date format: DD/MM/YYYY
________________________________________
Rules
• Use only legal, open-source methods
• No contact with real individuals
• No intrusion, exploitation, or bypassing of access controls
• No doxxing or harassment
• This challenge is for educational purposes only
```


This challenge is particularly noteworthy because it combines steganographic elements embedded within a fragment of an alleged dead drop, effectively elevating the task beyond basic OSINT into a more advanced methodology. The approach required not only the use of publicly available information but also a structured investigative mindset and analytical reasoning.


Several key indicators can be extracted from the challenge description and used as analytical anchors:


- High-profile defection
The challenge explicitly references a high-profile defection. Such cases are, by nature, likely to be extensively documented across open sources, including academic publications, investigative journalism, and government or institutional analyses.

- Russian (Eastern Bloc) origin
Given that the defection originated from the Russian intelligence ecosystem (formerly part of the Eastern Bloc), it is reasonable to assess that the defector most likely sought asylum in Western Bloc countries. Historically, countries such as the United Kingdom, Germany, and the United States have been primary destinations for intelligence defectors.

- Reference to an “online dead drop”
The mention of an online dead drop strongly suggests a modern-era defection, occurring after the widespread adoption of the Internet. This allows us to confidently exclude Soviet-era and pre-2000 defection cases from consideration, as the operational context would not align with the use of online infrastructure.


Based on these parameters, the logical starting point is to review publicly available information concerning high-profile defections involving Russian intelligence officers after 2000.


An academic article published by MIT provides useful context in narrowing the field:


[https://direct.mit.edu/jcws/article/26/3/37/125441/The-KGB-Wanted-List-and-the-Evolving-Soviet](https://direct.mit.edu/jcws/article/26/3/37/125441/The-KGB-Wanted-List-and-the-Evolving-Soviet)


From this and corroborating open sources, it becomes evident that post-2000 defection cases involving former Russian intelligence officers who defected to the West are relatively limited. The most prominent cases include:


- Alexander Litvinenko — A former FSB officer who defected to the United Kingdom and was later assassinated in 2006 using polonium-210.

- Sergei Skripal — A former GRU officer who defected to the United Kingdom and survived a Novichok nerve agent poisoning in 2018.


This process of elimination significantly narrows the potential entities of interest and provides a focused analytical framework for further investigation within the context of the challenge.


With the Named Entity of Interest (NEI) now identified, it is appropriate to derive corresponding Named Areas of Interest (NAIs) based on locations associated with alleged Russian-backed extrajudicial killing operations. Identifying NAIs allows the analysis to move from a person-centric focus to a spatial and operational framework, which is essential in intelligence and OSINT methodologies.


Based on open-source reporting, two primary NAIs can be established:


- Millennium Hotel, Grosvenor Square, London, United Kingdom (Pine Bar)
This location is directly associated with the Alexander Litvinenko case. The poisoning occurred at the Pine Bar within the Millennium Hotel. The hotel’s proximity to the former United States Embassy at Grosvenor Square suggests an environment characterized by heightened surveillance, diplomatic presence, and security infrastructure. The selection of such a location is consistent with intelligence tradecraft, where operational boldness and signaling may be deliberate components of the act.

- Christie Miller Road, Salisbury, Wiltshire, England
In the Sergei Skripal case, Skripal and his daughter Yulia were found incapacitated on a public bench near The Maltings shopping area in Salisbury city center on 4 March 2018. However, subsequent investigation determined that the Novichok nerve agent was applied to the door handle of Skripal’s residence on Christie Miller Road. As this location represents the point of initial exposure, Christie Miller Road is assessed as the primary operational NAI for this incident.


Although the challenge presents the poem in an intentionally ambiguous manner, it explicitly suggests that indirect indicators — such as linguistic patterns, temporal references, and operational clues — can be extracted to infer the geographical and contextual aspects of the operation. This aligns with advanced OSINT practices, where meaning is often derived not from explicit statements but from structured interpretation of subtle cues.


Accordingly, the next analytical step is to examine the poem stanza by stanza, assessing each segment for spatial references, symbolic language, timing indicators, and tradecraft-consistent elements that may correlate with the identified NAIs or further refine the operational context.


The poem can be translated into:

>

IN THE CAPITAL, FAR FROM MOSCOW, WHERE THE EVENING SEEMS TOO LONG, EVERY STEP OF THE AGENT IS ACCOMPANIED BY THE QUIET ECHO OF LONG-BURIED THINGS.


HE WALKS BECAUSE HE MUST, FOLLOWING A PATH THAT ONLY HE CAN SEE


ALONG THE WAY, HE MUTTERS A WORD HE ONCE HEARD BEHIND A CLOSED OFFICE DOOR, THE WORD THAT IN ENGLISH IS CALLED ‘MORAL’ (MORAL), WHICH TENDS TO LOSE ITS CLARITY DURING DIFFICULT FOREIGN ASSIGNMENTS, BUT FOR SOME REASON, NEVER DISAPPEARS COMPLETELY.


THE WIND, RUSHING THROUGH THE ALLEY, CARRIES WITH IT THE DAMP BREATH OF NEARBY WATER, THE FAINT SMELL OF THE RIVER, AND ALONG WITH IT, THE UNEXPECTED SCENT OF TROUT… LIKE AN ANCIENT CODE, WHISPERED INTO HIS EAR.


THE PATH FINALLY LEADS TO A SOLITARY DOOR, A PLACE WHERE THE FUTURE OF MORE THAN ONE PERSON COULD CHANGE


AND WHEN HE STANDS BEFORE IT, ALL THAT HE HAS LEFT IS A SMALL, FLICKERING EMBER INSIDE AND BARELY NOTICEABLE HOPES… BUT STILL STRONG ENOUGH TO PREVENT HIM FROM TURNING AWAY”


The morse code after the poem


.- — . . -. — / — -… / ..- … . / -. — — — ..- .-. / …. . .- -.. / .- -. -.. / -. — — — ..- .-. / — .-. .- .. -. .. -. — . .-.-.- / ..-. ..- .-.. ..-. .. .-.. / — …. .. … / — .. … … .. — — -. / .- -. -.. / — .- -.- . / …. .. — / . — . .- -.-


Is decrypted as AGENT : USE YOUR HEAD AND YOUR TRAINING. FULFIL THIS MISSION AND MAKE HIM PAY


.


From the Morse code, it can be inferred that the operation represents a form of retaliation. The phrase “Make Him Pay” should not be interpreted in a light-hearted, *GTA–style* sense of repossessing belongings like CJ would do in Los Santos. Rather, it implies a far more severe consequence — payment with one’s life as retribution for treason. In this context, both Named Entities of Interest (NEI) — Alexander Litvinenko and Sergei Skripal — are victims of alleged extrajudicial killing operations, placing them squarely within the scope of the challenge.


A closer reading of the poem reveals several phrases that stand out and serve as indirect indicators:


- “In the capital, far from Moscow”
This strongly suggests that the operation took place in a foreign capital city. Given Moscow as the reference point, the comparison implies another capital of comparable geopolitical weight. This favors London (NAI 1) over Salisbury, which is not a capital.

- “Quiet echo of long-buried things”
This phrase evokes the presence of historical remnants — institutions, architecture, and legacies that no longer serve their original purpose but continue to exist. London, with its deep historical and imperial layers, aligns more naturally with this imagery than Salisbury. Again, this favors NAI 1.

- “He walks because he must, following a path that only he can see”
This can be interpreted as the perpetrator acting alone, guided by intent known only to them. Both NEIs were poisoned without immediate awareness, meaning this indicator plausibly applies to both Litvinenko and Skripal.

- The emphasized use of *MORAL* in Latin
The deliberate stylistic choice suggests an ethical or philosophical justification. Both NEIs defected on moral grounds, believing their actions were justified. This clue does not decisively separate the two, but it reinforces their shared profile.

- “Difficult foreign assignments”
Both Litvinenko and Skripal served in intelligence roles involving high-risk and complex assignments abroad. This criterion applies equally to both.

- “Never disappears”
Interpreted operationally, this likely refers to the traceability of the method. Both polonium-210 and Novichok are substances that leave forensic signatures. While designed for silent killing, neither truly disappears.

- “The wind rushing through the alley”
If taken geographically, this favors a large, dense urban environment. London, by sheer scale, contains far more alleys and narrow passages than Salisbury.

- “Damp breath of nearby water, the faint smell of the river”
Both locations are near water — London with the Thames and multiple canals; Salisbury with the Avon and Nadder. This indicator alone does not conclusively favor either.

- “Unexpected scent of trout”
Salisbury is well known for trout fishing, making such a scent *expected*. In London, however, trout are present but culturally unexpected. This inversion makes the imagery more compelling for London, once again favoring NAI 1.

- Final stanza — fading but persistent hope
This stanza is particularly revealing:
*“All that he has left is a small, flickering ember… barely noticeable hopes… but still strong enough to prevent him from turning away.”*
Skripal survived the Novichok attack and retains visible hope and continuity of life. Litvinenko, by contrast, deteriorated rapidly. Despite this, he continued giving interviews and making statements up until his death — his “barely noticeable hopes” were just strong enough to keep him speaking, warning, and exposing his assassination. This imagery aligns more closely with Litvinenko’s final days.


When all elements of the poem, Morse-derived message, and contextual indicators are assessed holistically, the analysis converges most strongly on Alexander Litvinenko as the primary Named Entity of Interest (NEI) and London as the corresponding Named Area of Interest (NAI). While both Litvinenko and Skripal meet the baseline criteria of being victims of alleged Russian-backed extrajudicial killings, the cumulative weight of the clues consistently favors Litvinenko. The explicit reference to *“the capital, far from Moscow”* serves as a firm geographic anchor pointing to London, a city with unmatched symbolic, historical, and intelligence significance. Phrases such as *“quiet echo of long-buried things”* align with London’s layered legacy of espionage and Cold War-era rivalries, within which Litvinenko’s case is deeply embedded. Operational cues — including retaliation implied by *“Make Him Pay,”* the notion of something that *“never disappears,”* and the use of traceable polonium-210 — further reinforce this assessment. Most decisively, the final stanza’s imagery of fading yet persistent hope closely mirrors Litvinenko’s final days: despite rapid physical decline, he continued to speak, testify, and expose his own assassination, driven by a diminishing but unextinguished resolve. Taken together, these linguistic, symbolic, environmental, and psychological indicators strongly suggest that the challenge centers on London and Alexander Litvinenko, with Skripal functioning as a plausible but ultimately secondary comparator rather than the primary focus.


With the analytical focus now shifted toward Alexander Litvinenko, we can proceed to a more in-depth examination of his case. Fortunately, due to the significant international attention it received, information related to this incident is extensively documented, well preserved, and readily accessible through open sources. Using basic Google dorking techniques, we were able to identify a number of relevant materials, leading us to the following website:


[https://webarchive.nationalarchives.gov.uk/ukgwa/20160613090333/https://www.litvinenkoinquiry.org/evidence](https://webarchive.nationalarchives.gov.uk/ukgwa/20160613090333/https:/www.litvinenkoinquiry.org/evidence)


Based on an interview with Alexander Litvinenko himself, which can be reviewed in the following document, valuable firsthand insights can be extracted regarding his experiences, state of mind, and the circumstances surrounding the events leading up to his poisoning. This primary-source material is particularly significant, as it provides direct testimony from Litvinenko prior to his death and serves as a critical reference point for understanding both the personal and operational dimensions of the case.


[https://webarchive.nationalarchives.gov.uk/ukgwa/20160613094451mp_/https://www.litvinenkoinquiry.org/files/2015/04/INQ016582wb.pdf](https://webarchive.nationalarchives.gov.uk/ukgwa/20160613094451mp_/https:/www.litvinenkoinquiry.org/files/2015/04/INQ016582wb.pdf)


This portion of the interview states that Alexander Litvinenko met Andrei Lugovoy and Dmitry Kovtun at the Millennium Hotel. This detail is operationally significant, as it places all three individuals at a confirmed location directly linked to the poisoning event and further reinforces the Millennium Hotel as a critical node within the broader investigative timeline.


They subsequently sat together in a bar. Within the Millennium Hotel Mayfair, there is a bar known as the Pine Bar, which aligns with this account. This detail is further corroborated by a receipt from the Pine Bar bearing Lugovoy’s name, dated 1 November 2006. The receipt provides tangible documentary evidence placing Lugovoy at the Pine Bar on the relevant date, thereby strengthening the linkage between the individuals, the location, and the timeline of events.


[https://webarchive.nationalarchives.gov.uk/ukgwa/20160613094138mp_/https://www.litvinenkoinquiry.org/files/2015/04/INQ015344wb.pdf](https://webarchive.nationalarchives.gov.uk/ukgwa/20160613094138mp_/https:/www.litvinenkoinquiry.org/files/2015/04/INQ015344wb.pdf)


To establish the exact date with greater precision, we can refer to the official statements made by Andrei Lugovoy and Dmitry Kovtun. These statements provide authoritative confirmation of the timeline and allow the meeting at the Millennium Hotel — and specifically the Pine Bar — to be accurately anchored within the sequence of events.


*[https://webarchive.nationalarchives.gov.uk/ukgwa/20160613093658mp_/https://www.litvinenkoinquiry.org/files/2015/04/INQ002696wb.pdf](https://webarchive.nationalarchives.gov.uk/ukgwa/20160613093658mp_/https:/www.litvinenkoinquiry.org/files/2015/04/INQ002696wb.pdf)*


*[https://webarchive.nationalarchives.gov.uk/ukgwa/20160613092611mp_/https://www.litvinenkoinquiry.org/files/2015/04/INQ002058wb.pdf](https://webarchive.nationalarchives.gov.uk/ukgwa/20160613092611mp_/https:/www.litvinenkoinquiry.org/files/2015/04/INQ002058wb.pdf)*


We can further corroborate this timeline by cross-checking it against Litvinenko’s clinical statements, which indicate that he began experiencing a rapid deterioration in his health starting on 1 November 2006. This medical evidence aligns closely with the date referenced in Lugovoy and Kovtun’s statements, reinforcing the conclusion that the meeting at the Millennium Hotel — and specifically at the Pine Bar — occurred on that date and was directly linked to the onset of Litvinenko’s poisoning.


*[https://webarchive.nationalarchives.gov.uk/ukgwa/20160613093941mp_/https://www.litvinenkoinquiry.org/files/2015/04/INQ007753wb.pdf](https://webarchive.nationalarchives.gov.uk/ukgwa/20160613093941mp_/https:/www.litvinenkoinquiry.org/files/2015/04/INQ007753wb.pdf)*


Based on the cumulative evidence, we can state with high confidence that the operation to eliminate Alexander Litvinenko took place on 1 November 2006 and was executed at the Pine Bar, located inside the Millennium Hotel Mayfair, London, Grosvenor Square. With this operational baseline established, the next analytical step is to address the reference to a “suspicious dark blue vehicle” reportedly parked near the entrance shortly after the operation.


Given the timeline and individuals involved, it is reasonable to assess that such a vehicle — if relevant — would most likely be associated with Andrei Lugovoy or Dmitry Kovtun, either directly or indirectly. In examining the physical layout of the Millennium Hotel, there are two plausible access points: first, Adams Row, which provides access to basement parking; and second, Grosvenor Square, where valet parking is available. If a vehicle were genuinely considered “suspicious” and subsequently noticed or reported, it would most likely be positioned in a high-visibility, space-limited area — namely the Grosvenor Square entrance — rather than concealed in basement parking. As such, analytical weighting favors the valet parking area on Grosvenor Square as the most plausible location.


However, despite extensive searches across contemporaneous reporting, archival news sources, and open records within a reasonable temporal window following the operation, no verified reports were found documenting a suspicious vehicle parked near the Millennium Hotel in direct connection to the Litvinenko incident. This absence is notable, particularly given the broader security context of London in 2006, a period marked by heightened alert levels due to ongoing terrorism concerns. One initial hypothesis was that, if unrelated to Litvinenko, any report of a suspicious vehicle in that area might instead have been linked to counterterrorism activity — especially considering the hotel’s proximity to the former U.S. Embassy, a known high-risk target at the time. Yet, even under this expanded framing, no corroborating reports surfaced.


Complicating the assessment further, available evidence indicates that Lugovoy and Litvinenko traveled through London in chauffeur-driven vehicles, none of which are described as dark blue. This weakens the likelihood that a dark blue vehicle — if observed — was directly tied to their movements. Nonetheless, CCTV footage does appear to show a possible dark blue vehicle parked near the entrance of the Millennium Hotel. At present, this remains an unattributed visual element: observable, but not conclusively linked to any known individual, report, or operational record. As such, the vehicle remains an unresolved data point — suggestive, but not evidentiary — within the broader analytical framework.


*[https://webarchive.nationalarchives.gov.uk/ukgwa/20160613090333/https:/www.litvinenkoinquiry.org/evidence](https://webarchive.nationalarchives.gov.uk/ukgwa/20160613090333/https:/www.litvinenkoinquiry.org/evidence)*


However, the poor quality of the available CCTV footage makes it impossible to identify or read the vehicle’s registration plate. Compounding this issue, there are no contemporaneous or reasonably associated reports that reference a suspicious vehicle matching this description in connection with the incident.


After several days of exhaustive searching — and, admittedly, a few sleepless nights — the effort to identify a plausible “suspicious dark blue vehicle” reached a point of diminishing returns. At that stage, professional detachment gave way to a moment of analytical desperation (which, in hindsight, is not best practice — though perhaps a familiar experience to anyone who has chased an OSINT lead too far).


In a final attempt to resolve this anomaly, I pivoted to Google Maps and examined historical Street View imagery of The Biltmore Mayfair (the current name of the former Millennium Hotel). By reviewing the earliest available Street View capture from 2008, I identified a dark-colored vehicle parked near the hotel entrance that matched the general description referenced in the challenge. While this discovery does not provide definitive attribution or evidentiary linkage, it represents the closest observable approximation to the “suspicious dark blue vehicle” described, given the constraints of available open-source material.


From this Street View image, we can observe a dark blue Range Rover parked near the entrance of the Millennium Hotel on Grosvenor Square, with the registration plate LD54XPL clearly visible. Somewhat unexpectedly, this vehicle turned out to be the accepted flag.


Admittedly, this outcome was not what I initially anticipated, especially given the lack of contemporaneous reporting or direct evidentiary linkage to the Litvinenko operation. Nevertheless, within the constraints of the challenge, this finding satisfies the requirement to identify a dark blue vehicle positioned near the hotel entrance shortly after the operation. Sometimes, despite rigorous analysis and structured reasoning, OSINT challenges still hinge on pragmatic pattern matching rather than perfectly documented causality — and this appears to be one of those cases.

*Challenge #8 Flag*

>

OBJECTIONS. This challenge is extremely hard not only because it is require some degree of analysis, but also because the specific flag about the car is somewhat irrelevant with the case’s description. The description provided for the challenge regarding the suspicious dark blue vehicle states: “Shortly after the operation, a suspicious dark blue vehicle was reportedly seen parked near the entrance. Identify the registration plate of the vehicle.” However, this description is somewhat misleading for the following reasons:


Timing Issue: The car was parked two years after the operation occurred, making it unclear why it would be considered “shortly after”. Unless we are speaking something cosmical, then 2 years is just a a quarter blink of an eye.


Lack of Suspicion: There is no official report stating that the vehicle was suspicious. The only factor making it “suspicious” is the fact that we are actively searching for it, which introduces a degree of bias into the investigation.


No Association with the Case: There appears to be no direct connection between the vehicle and the core aspects of the case, making its relevance questionable.


OSINT (Open Source Intelligence) relies on publicly available information, but it does not justify disregarding or misinterpreting objects or data that have no clear connection to the case. While my analysis is based on my current understanding and the information at hand, a more official write-up or clarification on this matter would certainly provide further enlightenment and potentially correct any misconceptions.


### Challenge #9 [FSB] FSB Part 1.


```
Important
The following challenges are provided strictly for OSINT training purposes.
They are based on real-world leaked material and must be handled responsibly.
Participants must remain strictly passive:
• No contact with individuals
• No interaction with real accounts
• No harassment or operational use
• Analysis and reasoning only
________________________________________
CHALLENGE 1 — DATE OF BIRTH IDENTIFICATIONContext
A historical dataset linked to an FSB-related leak contains partial civil information.
Only the individual’s identity is visible. The date of birth is missing.
Known Information
• Full name: КОВЖАРОВА ЕЛЕНА АЛЕКСАНДРОВНА
• Gender: Female
Objective
Using open-source intelligence methods, determine the date of birth of the individual.
No direct access to private databases or accounts is permitted.
Flag format
OSINT{DD/MM/YYYY}
```


Given that the subject bears a Russian personal name, the initial step in this investigation was to use Yandex, a search engine widely recognized for its superior indexing of Russian-language sources and regional content. This choice is consistent with standard OSINT practices, where search tools are selected based on linguistic and geographic relevance.


A direct name query for КОВЖАРОВА ЕЛЕНА АЛЕКСАНДРОВНА returned multiple results referencing individuals with the same or similar name. Among these, one source stood out due to its official and authoritative nature: an open publication hosted on an official Ukrainian government website operated by the Main Directorate of Intelligence of Ukraine (GUR).


The relevant source is publicly accessible at:


This page documents individuals identified as employees of the Federal Security Service of the Russian Federation (FSB) allegedly involved in criminal activities abroad. The inclusion of the subject’s full name within this dataset provides a strong contextual anchor for further analysis.


Based on the information presented in this publicly available government publication, the most reasonable and corroborated date of birth associated with Elena Aleksandrovna Kovzharova is 11 December 1968. Additionally, the dataset indicates a service-related date of 21 October 2002, which plausibly corresponds to the beginning of her professional affiliation with the FSB.


It is important to explicitly note that this investigation does not involve accessing private databases, restricted systems, or personal accounts. The analysis relies solely on previously leaked material that has been curated, published, and contextualized by an official government body, thereby placing it firmly within the bounds of ethical and passive OSINT methodology. No interaction with individuals, no operational use, and no attempts at data exploitation were conducted, in full compliance with the challenge rules.


Based on open-source verification and authoritative public disclosure, the most credible date of birth for the subject is: 11/12/1968

*Challenge #9 Flag*

### Challenge #10 [FSB] FSB Part 2.


```
Important
The following challenges are provided strictly for OSINT training purposes.
They are based on real-world leaked material and must be handled responsibly.
Participants must remain strictly passive:
• No contact with individuals
• No interaction with real accounts
• No harassment or operational use
• Analysis and reasoning only
CHALLENGE 2 — SECURITY IDENTIFIER CORRELATIONContext
A separate dataset references the same individual but contains only a digital contact identifier.
Other personal identifiers were removed.
Known Information
• Email address: polinaak@rambler.ru
This email address appears across multiple historical data sources.
Objective
Using passive OSINT correlation, identify the national social security identifier (SNILS) associated with the individual.
Flag format
OSINT{SNILS_NUMBER}
```


Building on the findings from Challenge 1, we established that the email address polinaak@rambler.ru is associated with Elena Aleksandrovna Kovzharova. This correlation provides a valid starting point for further passive OSINT analysis, as email addresses are commonly used as cross-dataset identifiers in historical leak material.


As an initial validation step, the email address was checked using Have I Been Pwned (HIBP) to identify whether it appeared in known commercial or service-related data breaches. This step serves two purposes: first, to confirm the historical exposure of the identifier across datasets; and second, to assess whether any breach directly contained Russian national identifiers. While the email appeared across six separate breaches, none of these datasets contained SNILS or other Russian civil identifiers, which is consistent with the fact that such identifiers are generally not stored by foreign commercial platforms.


To progress further, it was necessary to contextualize how Russian citizen data is structured and administered. In the Russian Federation, many core personal identifiers — including SNILS (Страховой номер индивидуального лицевого счёта) — are centrally managed by state institutions and are often accessible through the national e-government portal Gosuslugi (Госуслуги). Gosuslugi functions as a unified digital gateway that aggregates services from multiple government agencies, including the Social Fund of Russia.


Open-source reporting in late 2024 and early 2025 indicated that datasets allegedly originating from Gosuslugi-related systems were being offered for sale on underground forums. One such report is documented publicly by BrinzTech:


These reports describe the circulation of previously leaked or aggregated data, including email addresses and state-issued identifiers, within secondary datasets. Importantly, the analysis in this challenge does not involve accessing Gosuslugi directly, bypassing authentication, or interacting with compromised systems. Instead, it relies exclusively on already-published breach reporting and leaked material that has entered the public OSINT ecosystem.


This approach remains compliant with established OSINT ethics and best practices for several key reasons. First, the investigation was conducted using strictly passive collection methods. At no point was there any interaction with live systems, real accounts, or individuals, nor any attempt to bypass authentication or access restricted databases. All analysis relied solely on previously leaked material that has already entered the public domain and is widely indexed, archived, and discussed by third-party cybersecurity researchers and journalists.


This methodology aligns closely with the ethical framework articulated by Bellingcat, which emphasizes that OSINT practitioners may analyze leaked or sensitive material *provided it is already publicly accessible* and the analyst does not contribute to harm, harassment, or further exploitation. Bellingcat’s published guidance highlights that the ethical boundary in OSINT is crossed by active intrusion or engagement, not by responsible analysis of open data:


Bellingcat — *Ethics and Safety*


[https://www.bellingcat.com/about/ethics-and-safety/](https://www.bellingcat.com/about/ethics-and-safety/)


Similarly, Michael Bazzell, a widely cited authority in open-source intelligence and digital investigations, explicitly states that OSINT is defined by how information is collected, not by how it originally became public. In *Open Source Intelligence Techniques*, Bazzell explains that once data is publicly accessible — whether through lawful publication, leaks, or secondary reporting — it can be ethically analyzed as long as the investigator remains passive and avoids misuse:


Michael Bazzell — *Open Source Intelligence Techniques* (official site)


At an institutional level, NATO OSINT doctrine and military intelligence literature recognize that leaked datasets, when openly circulating and accessible without technical intrusion, may be treated as open-source material. NATO doctrine consistently defines OSINT as intelligence derived from information that is *publicly available or commercially accessible*, provided collection is non-intrusive and legally compliant:


NATO — *Open Source Intelligence Handbook* (public reference)


[https://www.nato.int/docu/stanag/OSINT_Handbook.pdf](https://www.nato.int/docu/stanag/OSINT_Handbook.pdf)


NATO Strategic Communications Centre of Excellence — OSINT publications


With this contextual and ethical foundation established, the next step was to examine whether the email address polinaak@rambler.ru appears within publicly reported Gosuslugi-related leak datasets or derivative compilations, and whether a corresponding SNILS number can be passively correlated from those sources — without direct system access or interaction.


This forms the analytical basis for identifying the national social security identifier required by Challenge 10.

*Challenge #10 Flag*

### Challenge #11 [FSB] FSB Part 3.


```
CHALLENGE 3 — SOCIAL NETWORK ASSOCIATIONContext
Archived online records indicate that personal identifiers were reused across social platforms.
The profile itself is not directly named.
Known Information
• Email address: polinaak@rambler.ru
• Phone number: +7 910 438 8202
Objective
Identify the VK social network profile historically associated with these identifiers.
________________________________________
Rules (Apply to All Challenges)
• Passive OSINT techniques only
• No interaction with accounts or individuals
• No authentication or recovery attempts
• Educational and analytical use exclusively
Flag format
OSINT{VK_ID}
```


This final challenge builds directly upon the analytical and ethical foundation established in Challenges 1 and 2, particularly the principle that publicly exposed identifiers may be passively correlated across historical datasets without engaging in active interaction or intrusion. The objective here is to identify a historically associated VK (VKontakte) social network profile using two known identifiers: an email address and a phone number. Both identifiers have already been established as part of previously leaked, publicly indexed material and therefore fall within the scope of permissible OSINT analysis.


As a first step, the email address polinaak@rambler.ru was once again assessed using Have I Been Pwned (HIBP) to determine its presence in known historical breaches. This step serves as a validation mechanism rather than a discovery tool, confirming whether the identifier has previously appeared in datasets relevant to social media platforms. The results indicate that the email address was included in the 2012 VKontakte data breach, a well-documented incident that exposed approximately 100 million VK user accounts. This breach is widely referenced in cybersecurity literature and is firmly established within the public OSINT ecosystem.


Analytical Rationale for VK Correlation


The presence of the email address in the 2012 VK breach provides a strong analytical pivot. At the time, VK commonly allowed account registration using an email address and, in many cases, a phone number as an additional identifier. As a result, breached datasets from this period frequently contain direct mappings between email addresses, phone numbers, and VK user IDs. Given that both the email address and phone number are known identifiers associated with the same individual from previous challenges, it is reasonable — within OSINT methodology — to treat them as correlated inputs when examining historical VK breach data.


Importantly, this approach does not involve interacting with VK itself, attempting account recovery, logging in, or querying live systems. Instead, it relies exclusively on static, historical breach material that has been archived, mirrored, and indexed by third-party researchers and data breach aggregators over time. This ensures that the investigation remains strictly passive and analytical, in full compliance with the challenge rules.


Ethical Justification and Continuation


As emphasized in the previous challenge, analyzing historical breach datasets that are already public does not constitute unethical behavior under recognized OSINT standards. This methodology aligns with the principles articulated by Bellingcat, Michael Bazzell, and NATO OSINT doctrine, all of which recognize that once data is publicly accessible and widely disseminated, it may be analyzed responsibly provided the investigator avoids operational use, harassment, or intrusion. In this challenge, the reuse of identifiers across platforms is treated as an analytical phenomenon rather than an opportunity for exploitation.


Accordingly, by using the email address polinaak@rambler.ru as a search parameter within the historical VK breach dataset — and corroborating results where available with the associated phone number — it is possible to passively identify the VK profile historically linked to these identifiers. This process represents a logical and ethical continuation of the previous challenges and satisfies the objective of identifying the VK social network association using OSINT techniques alone.

*Challenge #11 Flag*

### Challenge #12 [OSINT] Found the HACKER


```
OSINT Challenge – Forum Post InvestigationContext
Several years ago, a cybercriminal published a message on a well-known underground forum.
The individual was the author of the thread referenced below.
Thread Information
• Thread URL:
https://[REDACTED]/Thread-New-User-pass-40k-gmail-prmuim-netflix-hulu-steam-uplay-spotify
• Date:
May 11, 2018 – 03:38 PM
• Content:
Just Do it : http://[REDACTED]
The original link pointed to a monetized website used to distribute compromised account credentials.
Both the domain of the monetized link and the forum domain have been intentionally redacted.
________________________________________
Objective
Your mission is to identify the cybercriminal behind this forum post using open-source intelligence only.
You must determine:
1. The email address used by the individual
This email appears on multiple cybercrime-related forums, allowing strong attribution. 2. The individual’s Twitter account 3. The country where the individual lives
(Country name must be provided in English.) 4. The individual’s first name
________________________________________
Flag Format
The flag must be submitted in the following format:
OSINT{email_username-twitter_country_in_english-firstname}
Example (fictional):
OSINT{johndoe@gmail.com-johndoe123-canada-john}
________________________________________
Notes
• The subject was the original author of the thread
• Username reuse and cross-platform correlation are expected
• No direct interaction or active exploitation is required
Good luck.
```


This final challenge serves as a strong exercise in historical OSINT reconstruction, particularly the investigation of openly accessible web content that is no longer live. The challenge provides a partially redacted forum thread posted by a cybercriminal in May 2018, alongside a monetized link used to distribute compromised account credentials. Although both the forum domain and the monetization domain are redacted, the remaining contextual clues are sufficient to initiate a structured investigation.


Before proceeding, all observable details from the challenge were extracted:


- The URL structure (despite redaction) retains a visible path, strongly suggesting a forum-based thread rather than a standalone webpage.

- The thread title (“New user pass 40K gmail premium netflix hulu steam uplay spotify”) follows a well-known naming convention used in cybercrime forums to advertise credential combo lists (commonly referred to as *combolists*).

- The timestamp is precise: *May 11, 2018–03:38 PM*, which enables temporal filtering during archival research.

- The challenge explicitly states that the author reused identifiers across platforms, implying weak operational security (OPSEC) and making cross-platform correlation feasible.


These indicators strongly suggested that the post originated from a well-known clear-net cybercrime forum active in 2018.


To identify the likely forum, known cybercrime marketplaces active in 2018 were reviewed. According to reporting by *eucrim* (a reputable European criminal law publication), several major cybercrime forums were seized by law enforcement in subsequent years, including:


From these publications, three prominent candidates emerged:


- RaidForums

- Nulled

- Cracked


All three platforms operated on the clear net and were therefore candidates for archival recovery via the Internet Archive (Wayback Machine). Each forum was examined to compare historical URL path syntax against the partially visible structure provided in the challenge.


Cracked presented navigational issues due to historical DDoS protection layers.


Nulled exhibited URL structures inconsistent with the challenge’s thread path.


RaidForums, however, displayed a highly consistent URL pattern matching the visible elements of the challenge link.


Although the earliest fully accessible RaidForums snapshot dated to August 23, 2018, the Wayback Machine provides a secondary capability: enumeration of archived URLs, including removed content


Using this feature, keyword-based discovery was performed — specifically targeting the term “combolist”, which is commonly used within RaidForums for credential dumps. This led to the discovery of archived pages under the “Removed Content” section of the forum.


Notably, RaidForums organized removed threads in chronological order, allowing efficient navigation based on date. By iterating backward through archived entries, a removed thread was identified that:


- Matched the exact timestamp (May 11, 2018–03:38 PM)

- Matched the thread naming convention

- Matched the URL structure referenced in the challenge


This conclusively identified the thread and confirmed that the original author’s RaidForums username was “RoNey.”


Attribution could not stop at a forum username. Fortunately, RaidForums itself was breached in 2023, exposing credentials and metadata for over 400,000 users, a fact documented by multiple breach-monitoring platforms, including Have I Been Pwned.


Using this publicly documented breach as a secondary OSINT source, correlation between the username RoNey and associated identifiers was performed. While sensitive handling is required, the investigation relied solely on previously leaked and widely circulated datasets, without interacting with any systems or individuals.


Through passive correlation, the email address associated with the username “RoNey” was identified as:


roneyads1@gmail.com


With the email address identified, standard OSINT pivoting techniques were applied.


Google dorking revealed that the same email address was associated with a YouTube channel, primarily focused on Minecraft-related content, with video descriptions and metadata largely written in Arabic.


The YouTube channel’s “About” section provided two additional data points:


- A declared first name: Saad

- An indicated country of origin: Morocco


The channel also referenced an Instagram handle, which no longer existed, and no immediate Twitter handle was visible.


To locate the required Twitter account, the email address was again checked using Have I Been Pwned, which showed a total of 14 historical breaches, including a Twitter breach in 2021.


Using this breach as a correlation source, the associated Twitter username was identified as: ii_Ney


Further review of this account confirmed behavioral and thematic consistency with the previously identified YouTube channel (gaming-related content, naming patterns, and temporal alignment), strongly indicating common ownership.


Based on consistent cross-platform correlation — forum username reuse, breached credentials, content alignment, and self-declared information — the cybercriminal behind the original forum post was attributed with high confidence.


Final Identifiers:


- Email: roneyads1@gmail.com

- Twitter: ii_ney

- Country: Morocco

- First name: Saad

*Challenge #12 Flag*

---

*Originally published on [Medium](https://0xmanikmaya.medium.com/osint-industries-ctf-2025-write-ups-fb7ffc1079d7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of osint CTF writeups.*
