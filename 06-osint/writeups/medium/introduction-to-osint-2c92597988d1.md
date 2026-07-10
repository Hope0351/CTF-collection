# :sleuth_or_spy: Introduction to OSINT. OSINT is a piece of information that is…

> **Original Source:** [Introduction to OSINT. OSINT is a piece of information that is…](https://infosecwriteups.com/introduction-to-osint-2c92597988d1)
> **Platform:** infosecwriteups.com | **Category:** `OSINT`

---

*Intro to OSINT*

## Overview


Technological breakthroughs have revolutionized the entire world into what, at present, is called the information age. One of the most important things about this age is that internet technologies are used in all areas of life and business to get the most out of them. Because of this, a lot of digital information is spread out all over the web, and the vast majority of it is open to the public.


Our digital society is growing all the time, and as it does, it makes a lot of data, which is the basis for many kinds of intelligence. The difficulty is that the more data there is, the more time it takes to search through it all. That is where OSINT comes in and becomes an invaluable asset to any organization.


Open-Source Intelligence (OSINT) is a type of threat intelligence in which a company can gather information about its security concerns from a wide range of sources. These sources can include social media websites, e-commerce sites, and even on-the-ground research by security experts.


The first step in a penetration test or a red team activity is to collect as much information as possible about the target. In general, gathering intelligence starts with getting information from sources that anyone can see. This is called open-source intelligence, or OSINT. To give you an example, the prevalence of social media activity has made OSINT more accessible. Therefore, the attacker can easily collect the required data+ for profile evaluation.


In this blog, we will define OSINT and take a look at how different actors can use OSINT to support intelligence needs in various situations.

## What exactly is OSINT?


OSINT, which stands for "open-source intelligence," is information that anyone can legally get from sources that are free or public. This information is obtained without violating intellectual property regulations.


OSINT takes advantage of different resources and is not just confined to online data.For instance, physical publications such as books, or any form of media such as TV or radio broadcasts, are all considered OSINT sources. As a result of digitization, a lot of OSINT information now comes from online sources. However, OSINT resources are not confined to online data. OSINT sources include, for example, physical publications, books, and any kind of media, like TV or radio broadcasts.


Do not restrict your search to typical search engines such as Bing, Yahoo, or Google while conducting OSINT. These search engines only search the surface web, which accounts for only 4% of all available web content; the rest is hidden deep in the bottom layers and requires special access.


The fundamental idea behind OSINT is as follows:


Public information exists → Data is gathered → Information is analyzed

## OSINT Tools and Techniques


There are a ton of OSINT tools out there, both paid and unpaid. The most widely used OSINT tools will be the subject of discussion. The most crucial thing to understand is that the OSINT process entails using information pieces to be processed using a certain technology to learn more about a person or entity.


1) Google Dorking: Googling the queries or using Google Search. The main purpose of this is to search for text on web server pages that are open to the public. The search operators are the first tool for a search, and more advanced operators can be found here: [Search Operators](http://www.googleguide.com/advanced_operators_reference.html)


Google Dorking, also known as "hacking" Google, is the process of using complicated search terms to get the results you want. For more information check out: [Google Hacking Database](https://www.exploit-db.com/google-hacking-database)


Common operators are:


- inurl: Finds a URL that matches one of the keywords.

- intitle: Searches for all or any keyword occurrences in the title.

- filetype: Looks for a certain filetype that is indicated in the query.

- ext: used to distinguish between files with particular extensions, like.log.

- cache: reveals the web page version that Google has stored in its cache.


Example:


Some other search engines:


2)[have I been pwned?](https://haveibeenpwned.com/) This is a website where Internet users can check to see if their personal information has been exposed due to a data breach. Users can look for their own information by entering their username or email address, and the site collects and analyzes hundreds of database dumps and pastes that contain information from billions of compromised accounts. Users have the option to sign up for email alerts if their email address turns up in upcoming dumps. People have said that a website is a useful tool for Internet users who want to protect their own security and privacy.


## Get Redfox Security’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Example: We are taking an example of the email address which was compromised in the data breach


*Here we can see that the account credentials were leaked in the Dubsmash Data breach.*3) [PimEyes](https://pimeyes.com/en): PimEyes is a reverse image search engine for photos using cutting-edge techniques like facial recognition and artificial intelligence. Users can easily begin their search by uploading a picture of the person’s face. When an image is posted to the PimEyes website, it takes the tool less than a second to search the internet for similar pictures of the subject. It’s important to note that PimEyes does not consider social networking sites when performing its search. Instead, the app looks for photos that can be seen by anyone on websites, blogs, and other open platforms.


*Click or tap to view the details of the result.*


Now, access the website on which the photo appears :


*The next step is to click to open the source website*


You get redirected to the website from where the image was uploaded.


4)[Shodan](https://www.shodan.io/): Shodan is a popular OSINT tool that can be used to find exposed assets. With the help of Shodan, one can find out the geographical locations where vulnerable devices are located throughout the world. When it comes to devices, Shodan has a huge footprint because the tool can be used to view live camera feeds.


We could search for a default password as an example.


We have over 31,000 results in the default password and we can try to log in with the default password as shown below:


As a result, we got access to a router and other sensitive information.


5) [Exif Viewer](http://exif-viewer.com/): “Exchangeable Image File Format” is what EXIF stands for. EXIF metadata is extra data that is kept in an image file. Important information like exposure, date and time, aperture, etc. is kept as part of the image file when a photo is captured on a digital camera. Even the GPS coordinates may be kept on devices that have location services enabled. Looking at this information may help you understand how the shot was taken.


Upload an image from the folder. We have taken a sample image from the Internet.


To view the metadata information for the image, click on the “Show Exif” button.


In this blog, we discussed some basic OSINT tools. We will be discussing OSINT Frameworks in the upcoming blog posts.


[Redfox Security](https://redfoxsec.com/) is a diverse network of expert security consultants with a global mindset and a collaborative culture. We proudly deliver robust security solutions with data-driven, research-based, and manual testing methodologies.


“Join us on our journey of growth and development by signing up for our comprehensive [courses](https://training.redfoxsec.com/).”


References: [https://flashpoint.io/blog/what-is-osint-open-source-intelligence](https://flashpoint.io/blog/what-is-osint-open-source-intelligence)

---

*Originally published on [Medium](https://infosecwriteups.com/introduction-to-osint-2c92597988d1). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of osint CTF writeups.*
