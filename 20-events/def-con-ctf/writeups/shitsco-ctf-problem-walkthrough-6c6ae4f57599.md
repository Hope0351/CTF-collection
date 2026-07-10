# 🔌 Shitsco CTF Problem Walkthrough

> **Original Source:** [Shitsco CTF Problem Walkthrough](https://medium.com/@georgiaweidman/shitsco-ctf-problem-walkthrough-6c6ae4f57599)
> **Platform:** medium.com | **Category:** `HARDWARE` | **Event:** DEF CON CTF | **Year:** 2014

---

## 📝 Full Writeup

Member-only story

Shitsco CTF Problem Walkthrough[![Georgia Weidman](https://web.archive.org/web/20250817150728im_/https://miro.medium.com/v2/resize:fill:64:64/1*beoNCmO1PGRywQo-2ND0pg.jpeg)

](/web/20250817150728/https://medium.com/@georgiaweidman?source=post_page---byline--6c6ae4f57599---------------------------------------)

[Georgia Weidman](/web/20250817150728/https://medium.com/@georgiaweidman?source=post_page---byline--6c6ae4f57599---------------------------------------)

·
Feb 26, 2019

[

](/web/20250817150728/https://medium.com/m/signin?actionUrl=https%3A%2F%2Fmedium.com%2F_%2Fvote%2Fp%2F6c6ae4f57599&operation=register&redirect=https%3A%2F%2Fmedium.com%2F%40georgiaweidman%2Fshitsco-ctf-problem-walkthrough-6c6ae4f57599&user=Georgia+Weidman&userId=4f9607f6cd4c&source=---header_actions--6c6ae4f57599---------------------clap_footer------------------)

--

4



I started my career doing security research. I guess technically I had a government red team job before that, but to really get where I wanted to go in the industry I did some research, gave some talks, and went from there. But for the past couple of years I’ve mainly been focusing on building my consulting practice, commercializing my mobile security research, and build a product startup. So I haven’t had as much time for research as I would have liked. With the release of our first pro product [Dagah ](https://web.archive.org/web/20250817150728/http://www.shevirah.com/dagah/)I’ve made a resolution to change that.

I’ve decided to start this blog to post some of my work. My goal is to make everything understandable to someone who has read the exploit development chapters in my book and/or did the exploit development exercises in the OSCP course and exam. I find that even with years of study I sometimes fall into the gaps of assumed knowledge and skipped steps on vulnerability write-ups. What I’ll try and do different here is make everything I post go step by step and include all the background. That might make it really boring to some of you and I apologize, but that’s the kind of blog I want to have.

I’ve been working on bug hunting and will post some write-ups of my first couple findings as soon as the responsible disclosure window runs out. In the meantime, I’ve also been dusting off my skills by working through some old CTF problems. This particular post will be about a CTF problem from the Defcon CTF Qualifier in 2014. There are already other write-ups on this problem including [here](https://web.archive.org/web/20250817150728/https://github.com/ctfs/write-ups-2014/tree/master/def-con-ctf-qualifier-2014/shitsco) and [here](https://web.archive.org/web/20250817150728/https://www.endgame.com/blog/defcon-capture-flag-qualification-challenge-1).

---

*📖 Originally published on [Medium](https://medium.com/@georgiaweidman/shitsco-ctf-problem-walkthrough-6c6ae4f57599). All credit goes to the original author.*
*📂 Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of hardware CTF writeups.*
