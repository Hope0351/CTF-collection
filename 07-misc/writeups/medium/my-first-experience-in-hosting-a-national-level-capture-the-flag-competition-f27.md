# :game_die: My first experience in hosting a National Level Capture The Flag Competition

> **Original Source:** [My first experience in hosting a National Level Capture The Flag Competition](https://infosecwriteups.com/my-first-experience-in-hosting-a-national-level-capture-the-flag-competition-f274eb9db0f7)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# My first experience in hosting a National Level Capture The Flag Competition


Hey hackers!!!


My name is Krishnadev P Melevila, Welcome to my writeups, I usually post bug bounty writeups here, But today I am sharing my experience in hosting a National level CTF.

>

Summary


I Krishnadev P Melevila and my friend Jerin Manoj and our 6 volunteers, In association with Computer society of India students branch, Viswajyothi college of engineering and technology, organised a National level capture the flag competition known as BUFF3R CTF, The complete event was sponsored by Redteam academy and co-sponsored by Etlab Softwares.


Around 100+ Teams participated in online preliminary round and the top 10 competed in the offline finals.


The prize money was: Rs.20000/-


>

Where am I inspired from?


It all started from DomeCTF, Yes! DomeCTF is a CTF competition organised by Beagle security as a flagship event of C0C0N (International cybersec conf, Organised by Kerala Police cyberdome)


In 2021, I heard about the CTF for the first time, It was during the covid pandemic, So the domectf was online that year. And due to curiosity, I also joined and participated in DomeCTF 2021. And from 80+ teams, I got 17th rank.


In 2022, The same DomeCTF was held offline at Grand Hyatt Kochi, Kerala,India. I went to DomeCTF 2022 with my friend Jerin as my teammate. We secured 6th rank out of 60+ teams.


These two CTF inspired me a lot, Mainly the second one. So we decided to start a CTF competition on our college too…


So during our Technical fest of our college, Bodhi’22, We conducted a mini CTF, Which include very basic encryption and web challenges. And it was a grand success and was a great learning experience to many students in my college.


And all after that, During the starting week of November, we decided to host a CTF in college level once again, and make the new students (New batch 2022–2023 academic year) aware about cybersec.


But later we decided to shift it to National level, At that time, I am not sure that will it work or not. But we took the risk and continue with the National level plan.

>

What was the starting?


First we decided to host as one of our class (S3 CSE 2021–2025 batch) program, But later when we thought about the constrains of a National level competition, We pointed out that, It will not be viable to host it as a class organised competition.


So we searched for one of our college clubs of any organisation and we selected Computer society of India as our CTF banner.


Roshan Shaji, Our senior was the chair of CSI SB VJCET. So we contacted him and informed him about our matter.


He was very supportive but usually our college clubs will provide only limited funds for organising competitions, So what we asked was Rs.20000 as the first prize, But Rs. 20000 was not easy to get sanctioned from the club as we have no prior experience in organising an event.


So what next, Yes it’s time for external sponsors!!!!!!

>

How we contacted sponsors?


Finding sponsors was a hectic challenge for us, What we have is only a intermediate level LinkedIn profile, Some bug bounty writeups, and a single experience of hosting a college level CTF.


We cold mailed many companies, even Google, HTB, Devfolio, TryHackME, Amazon etc…Received many rejection reply mails… Every reply mails state a common point -> that we didn’t have prior experience.


*HTB Rejection mail*


*Google Rejection Mail*


*Vector35 Rejection mail*


So we shifted from MNC’s to startup companies, So we thought about the well reputed cybersec companies, a Google search revealed that Redteam Academy is a well reputed hacking academy in Kerala.


We just pinged Redteam on whatsapp about our requirement through an unoffical procedure and they told us that they will have a meeting with us and decide it.


The meeting was scheduled online and we discussed our overall requirements.


Ms.Anagha was our event coordinator from the Redteam. She was convinced with our plans and told us that they will proceed with our requirements if we can reduce the prize amount to Rs.20000/-


We agreed with it and the sponsorship was ready!!!!!!


After two days, I received another mail from Etlab softwares, stating that they were also ready to sponsor us and gave a sum of Rs.5000/-

>

College approval and finalising the dates


Then we contacted Roshan, chair of CSI VJCET again and made him know about this.


And we moved to the next process — The college approval!


The college approval was not smooth as we thought, Yes, The academic calendar is very tight, But still we convinced our Faculties and staffs. Our HOD was very supportive, He came with us to visit principal for taking his approval.


Finally we got the permission, And now we are ready to fire it up!!!!!


But wait…. We have only 10 days in total. Approval process completed on 14–11–2022 and we need to push up the first round of the competition by 26–11–2022 and second round by 02–12–2022.


Plans taken:


Inauguration(online): 26–11–2022 19:00 IST


First round(online): 26–11–2022 19:30 IST to 27–11–2022 19:30 IST


Finals(Offline at VJCET campus): 02–12–2022 09:30 IST to 02–12–2022 15:30 IST


Now the sleepless night begins!!!

>

Branding


As it is a National level event, We need a branding for our event, As I mentioned earlier, We have a single experience in hosting a college level CTF during Bodhi’22, technical fest of our college. At that time, our CTF was branded like BodhiCTF. So we decided to make it as our branding and we made logos and first look poster for our event.

*Our first logo*


But our tutor recommended us to change the name, As it may reflect some name conflicts with Bodhi Tech fest in future, So taking advice from her, We changed the name from BODHI to BUFF3R.

*BUFF3R-CTF Logo*

>

Setting up the platform


Our first CTF on college level was hosted on FBCTF platform which was an opensource project by Facebook, But currently it is deprecated and archived by Facebook. So taking experience from our last CTF we decided to host on FBCTF itself. But at that time it was offline, So we hosted it locally. but this time, We are expecting around 50+ teams and need to host it online.


So, Deploying FBCTF on wan was the most difficult task for us as part of this event.


We spend almost 3 entire day and night in setting up the platform. We tried standalone installations, Vagrant installations, Quick installations. But failing at each and every step. After many days of research we got a docker image from github and the funny thing was that I am completely new to docker, I have no prior experience in docker, I feel like giving up in many stages. But due to commitments to our sponsors and college, It’s our responsibility to successfully conduct this event.


After Googling, Reading tutorials, Finding walkthroughs, Watching youtube videos etc…I learned about docker platform and started setting up it.


At last we managed to host the FBCTF on our Azzure server (From Github students sponsorship)

>

Making challenges


Making challenges for the prilims was very easy for us. Because it contains only simple decryption,crypto, web, and miscellaneous challenges as we need to include maximum students from many colleges and everyone need to participate and earn knowledge.


We prepared 40+ challenges.

>

Promotions


I was bad at graphic designing, But after this event, I earned an intermediate experience in using Canva. We already have Canva pro ( From Github student sponsorship)


So we made all our promotion posters and videos through Canva pro.


## Get Krishnadev P Melevila’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


For the sponsor promotion, a 2 day college level exhibition was going on our college, We contacted our HOD and asked him to give a space in the exhibition for Red Team to put a promotion booth during the exhibition. He supported it and approved our request and Redteam visited our college and promoted their contents.


For our co-sponsor, We displayed banner ads and branded Etlab logo on all our promotion videos and posters.

>

Registration Phase


We started registrations on 19–11–2022, We expected very little or low participants. We expected around 50 teams, But our promotions and hype worked very well, Also students of our college supported very well in circulating poster national wide. We got registrations from Rajasthan, Hyderabad etc…


We crosses 25+ registration in the first day itself, Second day 50+ and by 24th of november, We reached 116 teams and a participant count of 232


That was a great news…

>

Preprations


We know that there are 116 teams national wide totaly, But now I am bit afraid that will the server handle these much requests at a time. This was my first hosting experience. So we tested the load, But while testing we came to know that server can handle across 200+ requests concurrently at a sec.


So we proceeded.

>

Day 1: Online Prelims — 26–11–2022 (24 hours )


The day came!!!!! We all are excited!! This day we planned an online meeting for inauguration of the event and for contestants to introduce the platform and to inform about the rules and regulations.


The meeting was scheduled at 26–11–2022 18:30 IST. We planned it as a highlight session of the event. But from here everything went wrong!!!!


As soon as we revealed our platform URL on the meet to introduce the platfom, Due to the hype we given before the event, Everyone started to ping the URL, and server flooded with requests, And the server responded with a 503 error, and we were forced to end the meeting in an unexpected manner. I was totally lost at that point. 100’s of whatsapp messages, calls from unknown numbers, time is running.


I was very sad,upset and tensed. I know nothing about load balancing, I contacted all of my technical friends, They are telling many complicated steps…I can’t apply it in a hurry manner,


Call came from our sponsors, They enquired the matter…I informed them that we are facing a large amount of ping, and we have not taken necessary steps to overcome it. But as soon as they know it, Their way of speech made me more confident. They were very supportive, And recommended a new platform and some other alternative measures.


By taking advice from them and my friends, we decided to shift the platform to CTFd, But….needs time……


We then soon contacted our senior Roshan for asking a provision to postpone the event to at-least 12 hours. Now the time is around 21:30 IST.


It’s already late to start as we planned, We then decided to postpone the event to 27–11–2022 07:00 IST to 28–11–2022 07:00 IST.


We got approved and that whole night gave me a lot of new experience… me and Jerin not slept during that night,


We purchased a CTFd subscription worth $50 and also we decided to regain our lost reputation, So we purchased a domain name of bufferctf.in worth $15, Now we established a brand!!!


Then we done the initial setups of the CTFd and after the initial setups, The time as around 01:20 IST.


By around 03:30 IST, We shifted all challenges from FBCTF to CTFd, and now its all right.


On morning 06:30 IST , We informed all participants to register on the event and we started by sharp 7:00 IST


From here all went very well.. We didn’t expect such a involvement from participants, I thought everyone get tired after few hours. But each and every participant involved very well and competed the whole 24 hours.


The leader-boards are unpredictable and shuffling each and every second.That made me very happy.


After the prelims the Top 10 teams are as follows


These were the selected team for Round 2 happening at VJCET campus


We released a Google form for the feedback of the first round, and we came to know that this CTF had helped most of the students to know about cyber attacks scenarios, and most of them learned lot of new stuffs.


>

Challenge development for round 2


After the first round some teams told that the challenges were quite easy, So it was our prestige issue to build more challenges, We started building soon after the prelims, I am experienced more in web development so I started building more difficult web challenges. We paved many rabbit holes along with the challenges,


First of all I have no idea from where to start, Later I researched many ctf organisers experiences and found that we need to install some vulnerable webapps using containers and expose it to contestants and they will find vulnerability, exploit it and take the flags.


So all challenges were set and now time to know who is the king!!!!!

>

Day 2: Offline Finals— 02–12–2022 (5 hours )


The day 2 was very thrilling, Teams from various engineering colleges throughout Kerala were there to compete, Many teams are coming even from 200+ KMs apart.


We organisers and volunteers came early at the venue and started the preparations and arrangements for the finalists.


We started sharp at 09:30 and end at sharp 15:30


We had arranged a lunch break during 12:30 to 13:30 IST. During this time we freeze the score board also challenges were hidden.


For the first 2 hours the scoreboard was unpredictable and shuffling was rigorous, But for the last 3 hours, It was almost clear that one among Cypher404,Kaapi,Pwneverything,G0S7 or phi will be the winner.


Finally Cypher404 grabbed the throne and become the winner!!!!


Our sponsor was not able to attend the closing ceremony function as one of their staff had a medical emergency.


Our Vice principal and HOD joined the ceremony and distributed the price to the winners.


*Team Cypher 404 — Winner*

>

How was the overall experience?


It was one of the milestone in my life, I can proudly showcase each and every step and procedure of this event to my portfolio. We know that we made many mistakes during the entire event, But apart from that, from the feedback of contestants, we understood that, the contestants were able to a learn a lot of new stuffs. And the contestants also mentioned that the organising and coordination of the event was great, That made me very happy.


For me as a cybersec enthusiast, It was a nice experience in hosting such an event, Really learned a lot… Actually those mistakes made me to learn it, The first server issue during the prelims round teached me stress management, Audience management, Situation handling etc…


and also technical skills like Domain mapping, Load balancing idea, Dockersing containers, Nginx configrations etc…


I actually loved hosting this event.


Here is the event after movie:


>

Will we host BUFF3R CTF again?


BUFF3R CTF 2.0 will be coming soon……


*Don’t forget to follow me on medium and other social media. Also please give your 50 claps for this write-up and that’s my inspiration to write more!!My Instagram handle: *[https://instagram.com/krishnadev_p_melevila](https://instagram.com/krishnadev_p_melevila)


*My LinkedIn handle: *[https://www.linkedin.com/in/krishnadevpmelevila/](https://www.linkedin.com/in/krishnadevpmelevila/)


*My Twitter handle: *[https://twitter.com/Krishnadev_P_M](https://twitter.com/Krishnadev_P_M)

---

*Originally published on [Medium](https://infosecwriteups.com/my-first-experience-in-hosting-a-national-level-capture-the-flag-competition-f274eb9db0f7). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
