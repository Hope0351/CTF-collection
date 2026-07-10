# :globe_with_meridians: The Unexpected $500 Reward: How I Found an Surprise XSS

---

# The Unexpected $500 Reward: How I Found an Surprise XSS

Buckle up, dear readers, for a tale that defies the mundane and embraces the hilariously unexpected! It all started with an online snooze-fest, commonly known as a webinar. Little did we know, an unsuspecting webinar on a certain platform would become the backdrop for a bug-hunting adventure that led to a surprising $500 bounty. Grab your popcorn, this one’s a wild ride!

### The Beginnings

Ah, webinars — the virtual lullabies of the digital age. There I was, trapped in a riveting webinar on a certain platform. As minutes dragged on slower than molasses, my inner mischievous imp got restless. What to do? Why, inject some flair, of course!

>

The Payload Plot Twist

>

Fueled by equal parts boredom and technical wizardry, I sneakily slipped a crafty payload into the attendee name field.Armed with XSSHunter’s powerful payload, I injected the h”<img src=x onerror=alert(document.cookie)>payload into a seemingly innocent input field. The goal was simple: let’s inject some fun where it’s least expected!

>

Boredom Triggered an Avalanche

What followed was beyond my wildest imagination. Hours after the webinar’s end, my inbox became a bustling hub of activity. The XSS payload’s magic was at play, triggering repeated alerts and notifications. This unexpected wave of activity was like an alarm clock jolting me awake from my digital slumber.

>

The Investigation

Realizing that this wasn’t your average “oopsie,” I donned my virtual detective hat. Private chats on the platform were the unsuspecting playground for this exploit. The rabbit hole led me to a fascinating discovery — not just about the exploit itself, but also about the vulnerability’s source and scope.

## Get Abhi Sharma’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Steps to Reproduce the Issue:

- Join the target webinar on the specified platform.

- Inject the payload: h”<img src=x onerror=alert(document.cookie)> into the name field.

- Submit the input containing the payload.

- Attend the webinar and then drop the msg in private chat with host or other users.

- Observe your inbox for any unexpected notifications or alerts, indicating the payload’s activation.

With my findings meticulously documented, I knew it was time to take the next step. Armed with determination and a healthy dose of curiosity, I reached out to the platform’s security team through Twitter DMs. The result? An invitation to their private program for submitting bug reports. This was the moment — the channel through which I could share my findings officially.

>

The Bounty: A Reward for the Unexpected

With my invitation secured, I submitted a comprehensive report to the private program. The result? A prompt confirmation of the vulnerability’s existence and its severity. And to my astonishment, a bounty of $500 was awarded as a token of appreciation for my efforts.

>

Conclusion

And there you have it, folks — the thrilling escapade of how a sleepy webinar turned into a tech treasure hunt, all thanks to a mischievous payload and some good old boredom. Who knew that injecting a dose of tech wizardry could turn a snooze-fest into a showstopper?

>

So, the next time you’re stuck in a digital daze, just remember that behind every yawn could be a virtual pot of gold — or in my case, a cool $500 bounty! Stay curious, keep your code creative, and may your boredom always lead to delightful discoveries. 🎉🕵️‍♂️💰

Thanks for joining me on this exploit expedition! Let’s keep supporting, sharing, and caring as we navigate the ever-enthralling landscape of technology together. Connect with me on Twitter [@a13h1_](https://twitter.com/a13h1_) or find me on LinkedIn [https://www.linkedin.com/in/a13h1/](https://www.linkedin.com/in/a13h1/). Until next time, happy hacking and keep those virtual adventures alive! 🚀🕶️👾

---
