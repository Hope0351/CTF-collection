# :link: Easiest Bug: Improper Token invalidation.

---

# Easiest Bug: Improper Token invalidation.

I wasn’t hunting for anything fancy that day. Just poking around, checking how the password reset flow works on the target web app.
The usual: fire up the site, enter an email, click “Forgot Password?”, and see what the response looks like. But there was a problem.
No matter how many times I tried, there was no password reset email in my mailbox. Is there be a bug? nahh, maybe it’s just some QA issue.. I left my desk to have some coffee.
When I came back, my mail box was full of password reset mails I requested earlier.

The rest link contains a token and looks something like this:

```
https://redacted.com/api/us/2/c/password_reset/1337/T0kEnyDZ
```

Thinking of IDOR? already tested, no result. So let’s continue further.

I was going through the mails one by one, looking for something interesting. I used all of the reset links to reset my password, nothing seems interesting. Hmmm, but something here doesn’t looks right..
Wait, I was able to use all the password reset links to reset my password is pretty weird by itself..
When I am done resetting my password, all the other reset tokens should get expired, right? is it a bug? I started searching on Google to find more info, to find similar cases, to find disclosed reports featuring this scenario and found this HackerOne report.

The scenario the hunter described there, exactly resembles my finding. I did some more digging and came up with this attack scenario.

Now let’s imagine this in the wild.
An attacker manages to get brief access to the victim’s email , maybe through phishing, maybe from a previously leaked breach.
The attacker, let’s call him Retro form now on, didn’t try to log in immediately.

Instead, he uses “Forgot Password” and receives a reset token through the email.

## Get Gr3yG05T’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

He quietly saves it.

Let’s name our victim Bob.
Later, Bob notices something suspicious. He resets his password by generating another token then also secures his email account by resetting it’s password.
Now what? Retro lost his access? NAHH

Remember the reset token he saved? That token is still active and he can use that to get back into Bob’s account.

This bug doesn’t pose that much of a serious threat as compared to other bugs but its really easy to exploit. This types of bugs comes handy in the post exploitation scenarios, where attackers have already got some level of access and they wanna dig further. This can be used in post exploitation account takeover and backdoor.

Most programs accepts it, some don’t, it really depends on how you explain the impact and the attack scenario.

### Hunting Cheat Sheet

Step 1: Visit the login page of the target application

Step 2: Request for password recent multiple times

Step 3: Reset your password with the latest password token

Step 4: Now test out the previous password reset tokens, If any of these works then the vulnerability is preset in the application.

This finding was pretty rare at the time I found it, There not much info were present in the internet (found some more reports later on). I was doubting myself whether its gonna get accepted or not. But just 2 days after submitting the bug, I received a reply, The bug was traiged.

You can reach out to me anytime at[@gr3yg05t](https://x.com/gr3yg05t)

Until the next hack, *Goodbye*

---
