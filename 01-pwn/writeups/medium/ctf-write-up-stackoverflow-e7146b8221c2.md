# :skull: CTF Write-Up: StackOverflow

---

# CTF Write-Up: StackOverflow

- CTF challenge available at ctf-mystiko.com.

- Challenge name: StackOverflow

- Category: Web

— — —

I created this challenge from what I learned from this post (all due credit to him!):

```
https://www.wizer-training.com/blog/copy-paste
```

When we access the page indicated in the challenge description:

>

[http://173.212.221.197:34024/overflow.html](http://173.212.221.197:34024/overflow.html)

We see a typical stack overflow page, full of info.

## Get Antonio Lara’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

The point of this challenge is to stress how a website can use javascript to place on your clipboard something different from what you think you copied. I will not go into details here because I just modified what the author of the post mentioned above shows.

Doing the usual thing that we do on stackoverflow, which is of course to copy and paste the code from the most voted answer:

we see that something else is pasted (we can copy as many or as few characters as we want from the code box):

>

Use the source, Luke. What you are looking for is here: Th3F74g1$H3rE.fL4G

And, unsurprisingly, the flag is here:

[http://173.212.221.197:34024/Th3F74g1$H3rE.fL4G](http://173.212.221.197:34024/Th3F74g1$H3rE.fL4G)

---
