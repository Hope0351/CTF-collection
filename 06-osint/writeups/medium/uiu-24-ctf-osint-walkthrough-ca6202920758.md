# :sleuth_or_spy: Uiu 24 Ctf Osint Walkthrough Ca6202920758

---

Assalam o Alikum and hello! I’m Rehan Mumtaz, a seasoned CTF Player and full time Penetration Tester.

If you’re looking to improve your OSINT skills, there’s no better way than by participating in CTF challenges. In this post, I’ll be sharing my experience and walkthrough of a recent CTF challenge that I participated in with my team, m4lware. Due to time constraints, I was only able to solve some of the OSINT challenges, but I’m excited to share my approach and techniques with you. Lets dive in!

Its all about 3 part OSINT challenge suite. These challenges needs to be solved in order to finish smoothly.

## Hip With The Youth

The bold hint is Instagram, lets hunt it out at insta and search possible account for `LongIslandSubwayAuthority` . We were presented with the this new account.

Checking out the post comments & descriptions did not give us such something juicy,

We revisited the profile again, checked the description and found [thread](https://www.threads.net/) link for that account is attached `longislandsubwayauthority` .

And found the flag in one of replies.

## An Unlikely Partnership

Now moving forward in the sequel of the challenge, next task is to find partner, LISA had partnership with! Starting from the thread application

With the newest technology of Android 14 in the wild that provides googling of anything on the screen by just tap and search. I utilized that feature and do a wholesome screen scanning, it showed me the results. Of one which is the LinkedIn account for `LISA Transit` .

This is the whole [linkedin](https://www.linkedin.com/in/long-island-subway-authority/) profile which had some posts but overall did not make any sense at all. I revisited the challenge description and the keyword `partnership` made me think of something else like of giving recommendation of someone or maybe endorsement for skillset. I then checked out skills section and found one endorsement there and that was the lucky partner I was looking for!

And here is the flag.

## The Weakest Link

This is the final one, there has to be something to do with the Spotify collaboration project between these LISA and its partner.

We got the Spotify account for `UIUC-chan` and this looked like this with no private Collab on his profile

We went through all public playlist and songs for possible hint but it was just the song, I scratched my head what to do now. I just now poking at every feature on this screen.
In his followers list, I found LISA account and I was like it was a rabbit hole.

One of the followers here, CS, took my attention and I checked out his profile and was provided with

I felt its a dead end, one of my solving trick always I utilized is to try out every feature possible on the dashboard. Then there is download option for desktop application of spotify. I downloaded it by thinking it maybe some extra feature it may provide that the web app did not.

Here I found out extra feature that provides friend activity column that fetches your friend’s current song being played (current activity).

I looked out for that song and got the flag!

The last challenge made me do some extra effort to reach for the final flag.
But, this thing took some time and I submitted the flag after the competition ended. Anyway, what matters more is the learning.
I really hope you guys liked my whole journey of problem solving. Thank you for sticking till the end. We will soon meet again in next blog!

Follow me :
LinkedIn: [linkedin.com/in/rehan-mumtaz](http://linkedin.com/in/rehan-mumtaz)

---
