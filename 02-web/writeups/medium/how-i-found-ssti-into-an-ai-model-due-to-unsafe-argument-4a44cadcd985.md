# :globe_with_meridians: How I found SSTI into an AI model due to unsafe argument

---

# How I found SSTI into an AI model due to unsafe argument

Hello

Today I will show you how I found SSTI into an AI model due to unsafe argument.

**Overview of AI model**

The AI is made in India. and only work over WhatsApp. I am unable to disclose the report since the report is not yet patched by team (they don’t respond).

## Get JEETPAL’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

So, the hunt starts with some news. I saw on X. That some AI company launch against a known AI brand and the AI work only on WhatsApp, so I tried there AI just see how they work. I started chatting with the AI and I notice something strange with

He knows my name even I didn’t tell him. so, I asked him on whic data he was trained or how do he get my name.

He told me that he got my name using my WhatsApp description and I checked and found yes it was set to `Jeet` No surprise at all.

I noticed the AI replies using the user’s WhatsApp profile name. WhatsApp allows custom names up to 25 characters. I replaced my name with a known SSTI payload: `{{7*7}}`. After resetting the chat session, the AI responded using the evaluated result, showing “49” instead of the payload. This confirms server-side template rendering of user-supplied data without sanitization.

Then I tried this on many more AI like Llama to see if he also does that if yes it might be a bug into WhatsApp of just glitch token respond again and I found Llama able to respond without Evaluated the syntax so I tried to report this to that AI company but the team didn’t respond at all.

Then I tried again if I can do anything else to make it more impactable, but I was unable to properly test due to limit into WhatsApp name field

Thank you for reading

New articles Dropping soon

**Connect with meLinkedIn**: [https://www.linkedin.com/in/jeet-pal-22601a290/](https://www.linkedin.com/in/jeet-pal-22601a290/)
**Instagram:** [https://www.instagram.com/jeetpal.2007/](https://www.instagram.com/jeetpal.2007/)
**X/Twitter:** [https://x.com/Mr_mars_hacker](https://x.com/Mr_mars_hacker)

## Here’s something special for you! 🚨

Join a community of 30**00+ security researchers** on our **Discord server**, where we discuss **Web3 vulnerabilities, audits, and much more!** 🚀
👉 **Join the server here: **[https://discord.gg/Y467qAFM4X](https://discord.gg/Y467qAFM4X)

---
