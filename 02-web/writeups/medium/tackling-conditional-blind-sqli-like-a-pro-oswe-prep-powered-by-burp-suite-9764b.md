# :globe_with_meridians: Tackling Conditional Blind SQLi Like a Pro: OSWE Prep Powered by Burp Suite

---

# Tackling Conditional Blind SQLi Like a Pro: OSWE Prep Powered by Burp Suite

On the path to OSWE or chasing PortSwigger’s Web Security Academy certification? Imagine wielding your Burp Suite like Luke Skywalker wielded his lightsaber:

Precision, finesse, and just a hint of the Force guiding every move. This post is your hyperspace jump into Blind SQL Injection mastery: I’ll walk you through my personal write-up for conquering the Blind SQL lab, share the exact thought process that turned subtle “Welcome back!” echoes into a full database dump, and — spoiler alert — drop the link to my Python automation script at the end so you can automate the extraction and feel the Force in every request. May your payloads be swift and your hashes revealed.

### What Is Blind SQL Injection?

Blind SQL Injection is a stealthy variant of SQL injection where the application is vulnerable, but its HTTP responses reveal no direct query results or error messages. Instead of printing database data back to you, the server only lets you infer true or false conditions — like a silent oracle that nods or shakes its head. It’s like using a Jedi Mind Trick on your database: you never see the raw data, but with careful coaxing, you can still extract every secret, one subtle hint at a time.

## Exploiting blind SQL injection by triggering conditional responses:

In this write-up, we’ll focus on a specific flavor of Blind SQL Injection: boolean-based, or “conditional” Blind SQLi. The target application only ever changes one thing in its HTTP response — when our injected cookie matches a valid database entry, it displays “Welcome back.” No data dumps, no error messages — just a yes-or-no oracle. Think of it as using a Jedi mind trick on the database: with each payload, you ask a simple true/false question and watch for that single phrase to confirm your guess. By iterating these queries and observing the “Welcome back” cue, you can systematically extract every secret stored in the tables. Let’s break it down, step by step.

Fellow Padawans, your next trial awaits — simply sign up for a free PortSwigger Academy account and dive into the SQL Injection module. Join me there, and together we’ll harness the Force of Blind SQL Injection.

[https://portswigger.net/](https://portswigger.net/)

Here’s our vulnerable application:

*Vulnerable Application*

Next, I flipped on FoxyProxy in my browser and funneled every request straight into Burp Suite:

*FoxyProxy*

I activated the Burp Suite proxy to capture and inspect every HTTP request sent to our SQLi-vulnerable site. By examining the raw traffic — cookies, headers, and payload parameters — in real time, I could see exactly how the application handles each injection and fine-tune my queries on the fly.

*Proxy configuration*

I refreshed the application page, caught the request in Burp, and sent it straight to Repeater.

*Send to Repeater*

Right-click the captured request in Burp and select Send to Repeater. Now that it’s in Repeater, we can study its structure, tweak the parameters, and start testing our SQL payloads.

We can observe the fields that make up the Cookie:

>

TrackingId=nFLuJRJSquaLj2PK; session=imAl1sckJ1PxWnGiX6YRYIx8b9PhxrPE

Note: The session cookies will change throughout this write-up, as I had to restart the lab several times due to connection issues and the time needed to properly organize everything.

When we send the request, we receive the following server response:

*Response*

*Response*

We can see the server’s response includes the message “Welcome back”Now, to test the application’s behavior, let’s send a request with an incorrect TrackingId.

*Incorrect TrackingId*

When we send the modified cookie, we see the application returns the same page but without the “Welcome back” message. Now let’s test if it’s vulnerable to SQLi by sending the following payload in the `TrackingId` cookie:

```
' AND '1'='1' -
```

```
Cookie: TrackingId=6RzbYikNkLFaaP1E' AND '1'='1' - ; session=LMYnMADmQWcUuTHCpSuphO42r6fI4ckh
```

Using `AND 1=1` we saw “Welcome back” because the condition was true. Now let’s try a false test with `AND 1=2`. If the “Welcome back” message disappears, we’ve proven the app evaluates our SQL and is vulnerable to Blind SQL Injection.

```
' AND '1'='2' -
```

```
Cookie: TrackingId=6RzbYikNkLFaaP1E' AND '1'='2' - ; session=LMYnMADmQWcUuTHCpSuphO42r6fI4ckh
```

*1=2*

As you can see, the missing “Welcome back” message confirms the application is processing our injected command. Now that we know it’s vulnerable, our next step is to check whether the `users` table exists.

```
' AND (SELECT 'x' FROM users LIMIT 1) = 'x' -
```

At this stage, we’re essentially asking the database: “If I ask you to return the letter ‘x’ from the users table — fetching just one record — will you hand back ‘x’?” The `--` at the end comments out the rest of the original query so only our check runs. If the users table exists and contains at least one entry, the condition is true and we see “Welcome back.” If it’s missing or empty, the message disappears. We could test other letters if ‘x’ hadn’t worked, but since we received a positive response, we’ve confirmed the users table is there.

Agora precisamos saber se existe o usuário administador na tabela users :

```
' and (select username from users where username='administrator') = 'administrator' -
```

Next, let’s verify that the administrator account actually exists in the `users` table

Now that we’ve confirmed the administrator account exists, we could craft a similar payload to pull its password — but that really just turns into a brute-force attack. For pure password guessing, it’s far more efficient to test credentials directly on the login page rather than exploit the database.

Now we need to find out how many characters the administrator’s password contains, which will streamline our extraction. We’ll inject a boolean payload like:

```
' and (select username from users where username='administrator' and LENGTH(password)>1)='administrator' -
```

This injection essentially asks the database, “Is there a user named administrator whose password is longer than one character?” Since we still saw “Welcome back,” we know the password has at least two characters — and we didn’t need any Jedi tricks to uncover that. By repeating this boolean length check with different values, we can pinpoint the exact length of the administrator’s password one step at a time.

## Get Anezaneo’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Stay aligned with the Light Side — follow me on LinkedIn [Douglas Costa | LinkedIn](https://www.linkedin.com/in/douglas-costa-b968091a8/) or ☕[Buy me a coffee!](https://ko-fi.com/douglasanezaneo) FREE eBook → [Zero to Pentester: A Resource Guide for Aspiring Ethical Hackers](https://douglasanezaneo.gumroad.com/l/gqqcul)

Alright, young Padawans: now that our boolean payload returns “Welcome back” in Repeater, it’s time to automate the length checks with Burp Intruder. Right-click the request, choose Send to Intruder, mark the `TrackingId` value as your payload position, select the Sniper attack type, and load a list of length guesses. Intruder will then fire off each test in rapid succession, revealing the exact size of the administrator’s password in no time.

I’m running the free Burp Suite Community Edition, so our Intruder-style tests will fire one request at a time and move more slowly.

I selected the Sniper attack type, clicked on the `TrackingId` cookie value to mark our payload position, and hit Add. In the Payloads tab, I chose a numeric payload, set the range from 1 to 30 to guess common password lengths, and clicked Start attack. Burp will now cycle through each length one by one—watching for the “Welcome back!” response to pinpoint the exact size of the administrator’s password.

Our Intruder run showed “Welcome back” for lengths 1–19 and a different response at 20, so we know the administrator’s password is exactly 20 characters long.

Now we return to Repeater to craft our next boolean payload:

```
' and (select substring(passsword,1,1) from users where username='administrator')='b'--
```

This new payload pulls the very first character of the administrator’s password using `SUBSTRING` and checks if it equals `'b'`

If you still see “Welcome back,” you’ve confirmed the first character is b.

Now switch back to Intruder, replace the payload with this query, and start the attack so you can iterate through every possible character position.

Next, I switched Burp’s attack mode to Cluster Bomb so we can test two variables at once: the position in the password and the character guess. For Payload Set 1, I loaded the numbers 1–20 to cover each character slot. For Payload Set 2, I supplied our full character list — letters, digits, and symbols — to brute-force each byte. When the correct pair aligns, Burp will return “Welcome back,” revealing that specific character.

>

⚠️ If you’re using Burp Suite’s free Community Edition like me, this process can be painfully slow — sometimes taking hours to complete, as the screenshot below shows.

After the attack finishes, filter the responses that returned “Welcome back” and match each successful request to its character position. Then piece those letters together in order to reconstruct the full administrator password.

But don’t worry, young Padawans:

You don’t have to spend hours sifting through Intruder results. I’ve built a Python script that automates every boolean check — sending payloads, detecting the “Welcome back” responses, and assembling each character — so you can recover the full 20-character admin password in minutes instead of days:
👉 Check out the full script and detailed Python walkthrough on my GitHub:

[Exploit_Web/Blind_SQL_Conditional_Responses at main · DouglasANCosta/Exploit_Web](https://github.com/DouglasANCosta/Exploit_Web/tree/main/Blind_SQL_Conditional_Responses)

We got it !!!!

Young padawans, you’ve made it this far — may the Force of offensive security guide you. Share if this helped you hack your way forward, spread the word — and fuel my next exploit with a ☕[Buy me a coffee!](https://ko-fi.com/douglasanezaneo)Follow me [Douglas Costa](https://www.linkedin.com/in/douglas-costa-b968091a8/) and Infosec-Writeup for more red-team wizardry. May your shells be stealthy and your pivots silent.

Below is a video from a Grand Master [Rana Khalil](https://www.youtube.com/@RanaKhalil101) who walks through every step covered in this post:

Armed with these boolean-based tactics, you’ve now got a repeatable playbook for tackling any Blind SQL Injection scenario — whether you’re refining payloads in Repeater, speeding up tests with Intruder, or automating the process with Python. Let’s connect on LinkedIn to keep the conversation going — and here’s your challenge: what was the toughest obstacle you faced when extracting data from a Blind SQLi lab? Share your story in the comments below!

Kick-start your hacking career → FREE eBook → [Zero to Pentester: A Resource Guide for Aspiring Ethical Hackers](https://douglasanezaneo.gumroad.com/l/gqqcul)

## Let’s Connect on LinkedIn

[Douglas Costa | LinkedIn](https://www.linkedin.com/in/douglas-costa-b968091a8/)

---
