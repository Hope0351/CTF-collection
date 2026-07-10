# :game_die: NPST CTF 2020 - WRITE-UP

---

## Day 3 — Image Stegano

*Day 3 — Cracking the cupcake retrieved from [npst.no](http://npst.no) — by Author*

During the night one of the employees to Santa Claus managed to guess the password for the zip file we got yesterday. And they, in addition, offer us a clue informing us that there is with high probability something hidden that you can’t watch we your own eyes.

*Password for file in day 3 guessed retrieved from [npst.no](http://npst.no) — by Author*

Opening the privat.7z file represent a small challenge. Because the message informed us: Ultimately, I guessed the password for the zip-file,, and it works! Send from my PDA.

In this case the password was: til zip-fila, (for the zip-file,). Unlocking it, we find two items one txt document, and an image. The text file is as you might expect an easter egg, but at this moment we did not have the tools to figure it out. You can skip to easter egg #2 if you want to grasp the secret.

*Imange and file directory retrieved from [npst.no](http://npst.no) — by Author*

Cupcake.png display to us a penguin relaxing in the sun with a muffin. This challenge was the one I believe was the hardest. I tried literally everything before I got it! And when I obtained the answer, I have never been more frustrated. So, lets walkthrough this challenge.

I opened the text file, reflecting on what the heck? This generates no sense, and it does not look like anything that is familiar. I will focus on this later and then go for the image.

I start with running zteg on the image to see if there are something hidden.

Lucky us the image contains a URL link: [youtu.be/I_8ZH1Ggjk0](http://youtu.be/I_8ZH1Ggjk0). It is a video link from CIA, demonstrating them zooming in and enhancing the image to perceive a small thing in the background. Naturally, this was a huge hint! Therefore, I started to zoom in, check color layers you name it. Investing a couple of hours squandering my time.

At that time suddenly when I go to the check the mail inbox at dass.npst.no, I identify that solution. And I cannot believe it is so easy. You have an option called Forbedre (enhance) in the menu. I have previously uploaded some image there to test it, but it has always replied wrong image. Hence, what if this time it is the right image?

*Menu retrieved from [npst.no](http://npst.no) — by Author*

I uploaded the image and hit Forbedre (enhance). And as soon as I do, the image start to zoom inn more and more getting a little bit better for each time I punch the button. All the way back so I can in the end read the post it on the palm tree.

*Zooming to get the flag retrieved from [npst.no](http://npst.no) — by Author*

Day 3: PST{HuskMeteren} — A reminder to keep social distance with one meter.

## Easter egg #3 — Stegano

This was the first egg to be discovered. We had not found egg #1, and egg #2 where we unable to decode at this time. Wondering if there maybe was hidden something in the images, we got from the enhancer I run all the images once more with zsteg. The last image gives me this result.

>

EGG 3: EGG{MeasureOnceCutTwice}
- Check it twice?

---
