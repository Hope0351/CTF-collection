# :globe_with_meridians: From “Meh, It’s Just Reflected XSS” to “Sh*t, I Own the CEO” 🎭

---

## The “Wait a Minute…” Moment 🤔

Here’s what went through my mind:

>

*Me: *“Okay, I have XSS. But RXSS is boring. How do I make this… spicier?”
*Also Me: *“What if this is actually Stored XSS and triggers when employees view it?”
*My Brain: *“Even if it is, you need something valuable to steal…”

Then it hit me like a truck full of security textbooks: Authentication tokens!

## The Investigation Begins

I opened the browser DevTools and started hunting. I know from experience that most modern web apps use:

- Bearer tokens for API authentication

- Session tokens stored somewhere in the browser

- Usually in `localStorage`, `sessionStorage`, or cookies

I checked the Network tab. Sure enough, every request had this beautiful header:

```
Authorization: Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...
```

*“Okay, so they use Bearer tokens. But where do they store them?”*

I opened the DevTools => Application [Chromium]:

```
localStorage
```

And there it was, sitting pretty like a treasure chest with no lock:

```
localStorage.getItem('sb-jlmhsrfinffrgxcfkycl-auth-token')
```

## The “OH SH*T” Realization 😱

My jaw literally dropped. They were storing the session authentication token in `localStorage`?!

For those who don’t know, storing auth tokens in localStorage is like:

- Keeping your house keys in your mailbox

- Writing your PIN on your credit card

- Posting your password on your Instagram story

IT’S A TERRIBLE IDEA.

Why? Because any JavaScript can access it. Including malicious JavaScript. Including *my* JavaScript.

---
