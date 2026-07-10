# :globe_with_meridians: Portswigger Lab: JWT authentication bypass via algorithm confusion with no exposed key, a slightly different walkthrough

---

# Portswigger Lab: JWT authentication bypass via algorithm confusion with no exposed key, a slightly different walkthrough

## , or how I learned the importance of RTFM yet again

I mean, to be perfectly honest, this article started as a huge complaint in my head while I was working on solving [the lab in question](https://portswigger.net/web-security/jwt/algorithm-confusion/lab-jwt-authentication-bypass-via-algorithm-confusion-with-no-exposed-key), but in the end it turned out I was in the wrong. So, here’s a different walkthrough compared to the community walkthroughs under the solutions of this lab. And, if you consider yourself not as smart at times when it seems that you ought to be which then leads into frustration/anger, just keep in mind to take some deep breaths to calm down and think things through. You’ll be surprised at how far you can get when taking things slowly, even when you’re sure that you have done it all correctly and you think that the solution is just this one little thing that you missed so you try and speed through looking for it. But, of course you can’t find it because it’s not just one little thing. What you do find is that you are even more angry because you’ve been mentally running through this maze, and you can’t find the cheese, but you can smell it, and that drives you crazy. Instead, just start slowly from the get go, and the smell of cheese won’t be spread evenly all over the maze confusing you in which direction to go. Which means, you’ll actually get to the cheese sooner while not losing your cool. I don't know why the maze and cheese metaphor, but there you go :)

---
