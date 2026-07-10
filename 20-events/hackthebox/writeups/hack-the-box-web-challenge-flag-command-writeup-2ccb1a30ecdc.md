# 🌐 Hack The Box — Web Challenge: Flag Command Writeup

> **Original Source:** [Hack The Box — Web Challenge: Flag Command Writeup](https://medium.com/@rahulhoysala07/hack-the-box-web-challenge-flag-command-writeup-2ccb1a30ecdc)
> **Platform:** medium.com | **Category:** `WEB` | **Event:** HackTheBox CTF

---

## 📝 Full Writeup

Hack The Box — Web Challenge: Flag Command Writeup[![Rahul Hoysala](https://web.archive.org/web/20250501053621im_/https://miro.medium.com/v2/resize:fill:64:64/1*oWzoi9vID30bAzAJofB2Xg.jpeg)

](/web/20250501053621/https://medium.com/@rahulhoysala07?source=post_page---byline--2ccb1a30ecdc---------------------------------------)

[Rahul Hoysala](/web/20250501053621/https://medium.com/@rahulhoysala07?source=post_page---byline--2ccb1a30ecdc---------------------------------------)

·
Oct 10, 2024

[

](/web/20250501053621/https://medium.com/m/signin?actionUrl=https%3A%2F%2Fmedium.com%2F_%2Fvote%2Fp%2F2ccb1a30ecdc&operation=register&redirect=https%3A%2F%2Fmedium.com%2F%40rahulhoysala07%2Fhack-the-box-web-challenge-flag-command-writeup-2ccb1a30ecdc&user=Rahul+Hoysala&userId=38edcb39ebc9&source=---header_actions--2ccb1a30ecdc---------------------clap_footer------------------)

--

1



Let’s go ahead and solve one of HTB’s Ctf Try Out web challenges — Flag Command.

Looks like an interesting challenge. Let’s see what we can pwn here!

I’m going ahead and starting the dockup environment. Let’s see how the web application looks like.

Okay, so we’re on 94.237.60.78, port 31547 (these will probably be different for you). This is what I find.

I’m going to start the adventure and see what turns up. Remember, we’re searching for a flag in the format HTB{Ex4mp13_f14g}.

Looks like a terminal environment. I’m gonna try and run a command and see if that helps in enumeration.

Okay, no commands for now. We have to pick from the options provided. Instead of playing along, let’s see what we can find out first.

As a general rule of thumb, I’ll check for a /robots.txt file. It can be especially useful in CTFs to start off by checking this in web based challenges, as it usually reveals directories with useful information.

Okay, no file there. No problem, we can move on.

Let’s hit F12 on Chrome and open up DevTools, and see what we can find. I’m betting there’ll be something useful for this challenge there.

(To be honest, I kind of like this sound LOL.)

Let’s get to the important part now. I see three JavaScript files from which the whole setup likely works. We shall now have a look at these scripts to enumerate how the adventure works.

Our three main file paths are —

/static/terminal/js/commands.js

/static/terminal/js/game.js

/static/terminal/js/main.js

Let’s look into the commands.js file first.

Okay, this is mainly info regarding the success/fail messages and the other introductory messages. Information on how to view command history and submit commands, and commands to toggle audio on and off/start the game/clear the screen/restart the game. Nothing particularly useful here.

Nothing useful in the game.js file either.

Finally, we move on to the main.js file. Here is where we’ll be gathering most of our information as we can see that something’s being imported from it in the game.js file.

And that’s correct! There’s lots of interesting stuff in the main.js file.

Here’s what looks like the most important code segment in this file —

Here, we can see that the variable `currentStep` increments when certain options are chosen in the adventure — namely “Head north”, “Follow a mysterious path” and “Set up camp”. These save us a lot of trial and error while navigating the game.

So, we shall now enter those options in the adventure and see where that takes us.

So, I tried each of these options, but ended up at dead ends with each option. Let’s see where we can go from here.

We’ll go back to the main.js file now, because there is a certain line which will be important. Curious? Here it is:

Essentially, this `if` statement checks if the current command is EITHER in the array of accepted commands (head north, mysterious path, set up camp) OR if your command is in a secret array of accepted commands which also satisfy the condition to proceed inside the loop. We need to find what commands are included in this secret array, as it will likely contain information we need to find the flag.

Scrolling down to the bottom of the file reveals that there’s a request and response being sent to and from `/api/options`, and then being exported as a JSON file.

To see if these options could potentially be part of the secret array we’re searching for, we shall go to the Network tab in DevTools to see the resources being received.

Here’s what it currently is. Let’s refresh the page to load the resources again-

Here’s what it shows now! (The typing_sound.mp3 has not loaded correctly because the breakpoint was paused on the debugger)

Now out of these, the `options`file is the most interesting. Let’s open it up and see what’s lurking inside.

Here we go! This is the JSON file which contains what we’re looking for. Look at the last line inside “secret”.

We’ll go ahead and paste that line as a command in the adventure, as it belongs to the secret array we were looking for.

Success! We’ve found the flag!

Overall, it was a fairly easy challenge. Poking around with DevTools and having working knowledge of JavaScript will get you there.

Until next time. Keep on hacking and defending, cybersecurity enthusiasts! 🖖

---

*📖 Originally published on [Medium](https://medium.com/@rahulhoysala07/hack-the-box-web-challenge-flag-command-writeup-2ccb1a30ecdc). All credit goes to the original author.*
*📂 Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
