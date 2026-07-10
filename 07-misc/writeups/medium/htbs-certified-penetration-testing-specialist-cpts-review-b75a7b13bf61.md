# :game_die: HTB’s Certified Penetration Testing Specialist (CPTS) Review

---

# HTB’s Certified Penetration Testing Specialist (CPTS) Review

## One part review. One part therapy.

*Pictured: Me, just preparing for the CPTS.*

Early this year, I failed TCM Security’s Practical Network Penetration Tester certification exam. I gave it a real shot, but I just wasn’t ready. Initial access is my Kryptonite. I gave it another half-hearted shot a short time later, and ended my exam early when I realized that I couldn’t bring myself to even open Burp Suite.

The burnout was real, and I needed time to recover and refocus. I wasn’t even working in a directly hands-on role anymore, so even my base skillset made me already one of the most hands-on cyber risk analysts you could find. *(Dec 2025 Update: After a brief foray into CTI again in late 2024-early 2025, I’m back to GRC… sorta. I’m more of a security engineer working for a GRC team.)*

I spent the next few months:

- Getting a couple Microsoft Azure certifications, AI-900 and AZ-900.

- Learning how to build, configure, and (legally) hack AI applications.

- Playing on my Playstation 5. Spider-Man 2 was a masterpiece. (I’ll be honest, it was 90% this.)

Thankfully, I was able to recuperate with this regimen.

Then, in the summer, I felt that familiar itch again, so I started working on abusing my own personal AD lab, and after realizing it was largely like riding a bike, I randomly decided to try [Hack the Box’](https://hacktheboxltd.sjv.io/19ZM06)s Pro Labs. By midsummer, I was knee deep in hobbyist hacking again. Since I was already fully engrossed in the entire HTB ecosystem, I decided to pursue their Certified Penetration Testing Specialist (CPTS) certification, lauded by many as the most difficult of the intermediate-level pentesting certifications (compared to OSCP, GPEN, PNPT, etc.), and supposedly much harder (by multiple accounts) than the PNPT I failed earlier that year.

I took it as a personal challenge to pass it, just to be able to say that I could.

## The Preparation

Firstly, there has been a lot of lamenting about [Hack the Box Academy](https://hacktheboxltd.sjv.io/19ZM06) forcing you to 100% the CPTS pathway to even be able to sit through the exam, but now I see why. Unless someone started hacking from preschool, writing custom scripts in between nap times, I can’t imagine anyone just blindly taking this exam. Most everyone will need to 100% all modules in the CPTS path. There is just simply too much content.

Luckily, [Hack the Box](https://hacktheboxltd.sjv.io/19ZM06) Academy is excellent. It is, in my opinion, the best hands-on platform for learning both offensive and defensive security. It goes in depth for what to do, how to do it, and *why you’re doing it*. It really goes into the risks of various configurations and how threat actors can exploit them. I’ve gone through the CPTS path start to finish, and it’s a truly great resource.

(Edit: More on HTB Academy in my followup article [here](https://grepstrength.dev/you-need-to-get-on-hack-the-box-academy-025ab0b0fd1e).)

There is often a lot of discussion about how well a company’s training materials prepares students to actually pass their certification exams. Some are better than others. To be 100% clear, everything you need to pass the test can be found within the [Hack the Box](https://hacktheboxltd.sjv.io/19ZM06) Academy CPTS path. The exam isn’t entirely note for note from the Academy, but it will show you the methodology to help come to the finish line.

Probably the biggest knock against it is the lack of videos. For more visual or auditory learners, this can make it especially difficult to get through HTBA. You can try to supplement this by going to [ippsec.rocks](https://ippsec.rocks/?#) and searching for different terms to point you to Ippsec’s training videos on YouTube:

*Enter the term…*

Which will take you to:

*All for free!*Update: I found the below resource randomly on the HTB Discord channel, and while I haven’t used it myself, it was made by IppSec:

It’s a YouTube playlist called the “Unofficial CPTS Prep” filled with some of IppSec’s HTB machine video walkthroughs. I wish I had seen this before I took CPTS…

My one gripe with HTB Academy is that (*Edit: Nevermind, it’s *[several](https://grepstrength.dev/you-need-to-get-on-hack-the-box-academy-025ab0b0fd1e)*…*), depending on your prior knowledge and skill level, going through each and every single module can be a bit of a slog. For me, this most recent push was essentially a speedrun starting in late August and ending in mid/late September. I previously worked as a junior cloud admin, so basically any module related to Nmap or DNS had me skipping through as fast as possible. Also, as I’ve said before, I’ve been studying both HTBA and TCM Security since last year, making a lot of what I was doing essentially review. I personally didn’t actually *complete *it until this September, but I was reading the different modules, taking the methodology and commands, and applying them to machines on [Hack the Box](https://hacktheboxltd.sjv.io/19ZM06) since Summer 2023.

(Update 2025: But even with all that being said, I don’t recommend doing a speedrun like me. I burned out big time. I’ve since struggled to muster up the energy to do even do a normal machine on their Labs platform.)

All in all, the majority of my time doing the modules were in anything related to web apps (my weakest area), Active Directory Enumeration and Attacks, Linux Priv Esc (my second weakest area) and Windows Priv Esc. To be honest, just getting through these was dangerously close to burning me out.

(Update 11–2–2024: I wrote the next paragraph and modified the following one to elaborate more about what’s required to prep.)

Earlier I said that everything you need to learn to pass the CPTS can be found right in the Academy’s CPTS path. Apologies, but this isn’t telling the whole story. While true, you would be hard pressed to actually pass the exam with that alone. You need to tie it all together in a way that only the final skill assessment (Attacking Enterprise Network, aka AEN) forces you, or just reinforce concepts from outside the Academy entirely.

I was told a while back that one of the best things you can do to prepare is doing the Zephyr Pro Lab, and I can definitely concur with that. It’s the closest thing to the overall exam experience that I found. You have to chain attacks, think outside the box, and overall come up with creative solutions to apply the various techniques you’ve learned. I heard that Dante can help a bit with web apps, so I went through roughly 50% of it. I’m not the biggest fan of exploiting web apps, aside from the AI/LLM variety, so it felt torturous to continue.

With that being said, I also feel like nearly any box can help you in some capacity for this exam. See below for some notable ones.

Pro Labs:

- Zephyr

- Dante (for the web app and Linux priv esc portions of the exam)

Active Directory:

- Forest

- Active

- Cerberus

- Sauna

- Escape

Where individual boxes come into play is that they can help cement some individual concepts from a module that might assist during the exam. For example, if you want more practice abusing ADCS, then I recommend working on Escape. If you want to work on network pivoting, then I recommend Cerberus.

## Get grepStrength’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Also, those seemingly random AD attack guides I recently wrote were done in preparation for this exam. [DCSync](https://systemweakness.com/pervasive-and-persistent-dcsync-attacks-25e66e65aa08) and AS-REP roasting are far from new attacks, but going through the process of researching both and practicing them taught me a lot about Active Directory and it’s weak points. Sure, I *wrote *about AS-REP roasting, but I had to learn a lot about Kerberos and how users authenticate in Active Directory, for example. This in turn helped me know the difference between AS-REP roasting and Kerberoasting and also recognizing when I would do one over the other.

Lastly, I vaguely recall being unable to see anything forbidding the use of generative AI or LLM tools in the exam rules, so I ended up using a custom agenic AI app I built specifically to help me get through this. In it, I included literally every note I’ve ever taken when going through multiple security training vendors in it’s knowledgebase. For (hopefully) obvious reasons, this isn’t a publicly accessible app, so please don’t ask. I included my own pivoting, AS-REP roasting, and DCSync guides in the knowledgebase, as well.

I finally just simply asked in their support *(*cough* after I submitted my report, but I’m glad it confirmed what I had thought I saw when I signed the TOS…)* but it similarly stated that we can use literally any tool to pass. One way to look at it is if APTs are using generative AI to infiltrate corporate networks, why can’t we?

As a side note, I wish there was a way to see those exam rules again aside from when you first agree to begin it. I assumed I could reference it again later on somewhere on the exam page, but I was definitely wrong.

## The Exam

I’m very much a #YOLO test taker.

If I feel a surge in energy and motivation, it doesn’t matter if I think I’m ready, this is typically the time for me to take an exam. For CPTS, it was no different.

I had originally intended to take it after completing Dante or going through Zephyr once or twice again. I had also intended to go through the modules one more time, but after hitting 100%… something in me just said “Screw it,” so next thing I knew I was in the exam, mid-week and in the middle of the night.

I’ve taken multiple certification exams, across several job roles, using different exam formats, but nothing came close to this. This was easily the most difficult exam I’ve ever taken.

It’s points based, and you need a minimum of 85 points to pass. It is at its core a large CTF mimicking a small corporate network. As you capture flags, you submit them into the exam portal and you watch your point total rise. Please note the flags don’t make it feel “CTFish” but serve as progress markers to show that you’ve reached a new milestone in the exam.

It’s also recommended to show a screenshot of the flag within your exam report as well. There are a total of 14 flags, but you really only need 12 to pass as long as you have a good report. To that end, I highly highly recommend that you just simply populate the report template they provide you when you first begin. It’s clean and guides you into providing what they’re looking for from a passing report.

Unlike most who typically pass, I’m not a pentester or red teamer, so I’m probably not as quick on the draw nor work completely from muscle memory. This led to me relying more heavily on my aforementioned custom agenic AI app than I personally would have preferred. When I got stuck, which I did multiple times, as long as I gave the necessary context with my prompts, it helped me navigate and take next steps. It was honestly a huge help and I’m not entirely convinced that I would have passed without it.

One might ask:

>

“Did you just tell your AI ‘What exploit should I run?’”

Not quite. Garbage in. Garbage out. It was more like:

>

“My attacker machine is X.X.X.X, and I’ve compromised A user using B exploit on my target machine at the address of X.X.X.X, and I see that this has a web service running on port ####. When I visit the portal, I see that it is running C software. I found X exploit on GitHub, but I’m unable to get it to work, despite doing Y. I keep getting Z output. What am I doing wrong and what else can I try?”

If you’re used to doing machines on HTB’s main lab platform, you have an idea of what the initial access for CPTS will be like. Assume that the entire initial access portion is the equivalent of a Hard or Insane-level box, where just as you think you’re in, you’re definitely not. To say that you have to put in the work to even gain a foothold in this exam is an understatement. Just when I thought I could get a breather, I realized that the only thing separating me from starting from scratch was a single tenuously connected shell. This led me to continuing on despite desperately wanting to rest until I finally had a real foothold.

Don’t ask me how I managed to do my actual job and squeeze in some family time, but I did. Luckily, when the weekend hit, I was able to really give it true focus.

Taking a page from previous test takers, I was doing my report all throughout the practical part of the exam. I believe it was day 5 when I got the 12th flag…

*…and I called it.*

I simply did not have it in me to go any further, so I focused on cleaning up my report and finally submitted it a couple days later.

What felt like forever waiting on results was in reality only 8 days. They warn you that it can take up to 20 days to get your results, and that was torture in of itself. I felt some anxiety waiting for mine because I realized from talking with some CPTS holders that they had *way *more pages and screenshots than I did. I felt true dread hit me when a buddy of mine told me that his report had 144 pages to my 64.

When I finally got the email saying that I was a certified hacker, I felt relief more than anything. The feedback even told me that for the future, include more screenshots from output, but overall my report was clean, organized, and well done.

## Employment & Final Thoughts

This is the biggest reason anyone would go through the trouble, right?

Well, I’m not a penetration tester. I just want the skills of one. I’ve found that studying ethical hacking has overall made me both a better cyber risk and CTI analyst. It makes it far easier to speak to various vulnerabilities, configurations, network architecture, software deployments, etc.

>

“That software config that you want to enable? I found 5 exploits for it on GitHub with one Google search.”

But for those who do want to use this to get a job?

Update Dec 2025:

HTB’s CPTS is now recognized as a FedRAMP authorized provider with DoD 8140 alignment!

This is *huge *for anyone in the US that’s interested in going with HTB to learn pentesting, and will push CPTS and HTB as a whole on the map even further.

From what I’ve seen, if the DoD wants it, the US private sector wants it… eventually.

---
