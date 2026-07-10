# :game_die: How I Hijacked a CTF Platform with Four Lines of Burp Suite Rules

---

# How I Hijacked a CTF Platform with Four Lines of Burp Suite Rules

A few weeks ago I was poking around CTF platform. What I found was a pretty embarrassing vulnerability: any registered user could give themselves full admin access without knowing any admin credentials.

## What Was Actually Happening

When you log into the platform, the server sends back your account details including your role. Something like:

```
{
"username": "hamza",
"role": "participant"
}
```

This gets saved in browser’s `sessionStorage`. From that point on, every time you do anything on the platform load a page, submit a form, click a button the browser sends this role back to the server. And the server just... believes it. No verification against the database, no server-side session check, nothing. If your browser says you're an admin, the server treats you like one.

This is a classic case of client-side role enforcement the application is trusting the client to tell it who you are, which is never a good idea.

## Reproduction

To exploit this I used Burp Suite to modify web traffic in real time.

## Setting Up the Match and Replace Rules

Burp Suite has a feature called Match and Replace. Think of it like Find & Replace in Word, but it runs on live web traffic automatically. I set up four rules to cover all the places the role string could appear:

Rule 1 — Response body:

Field Value Type Response body Match `participant` Replace `admin`

Rule 2 — Request body:

Field Value Type Request body Match `participant` Replace `admin`

Rule 3 — Response headers:

Field Value Type Response header Match `participant` Replace `admin`

Rule 4 — Request headers:

Field Value Type Request header Match `participant` Replace `admin`

Then the same for request parameters — name and value both:

## Get ReFang’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

End result — all rules active:

Logging In

With those rules running, I logged in as a normal participant account. The server sends back `"role": "participant"`, Burp silently flips it to `"admin"` before it hits the browser, the browser saves it, and from that point every request going back to the server carries the admin role.

## What Happened Next

I navigated through the dashboard, profile pages, and challenge pages. Within a few requests the application started rendering the full admin panel.
Full challenge management. I could edit or delete any existing room and upload new ones.

## The Impact

This wasn’t just “oops, you can see an extra menu item.” Admin access on this platform means:

- Full user management — view, modify, or delete any account on the platform

- Challenge manipulation — create fake challenges, delete real ones, change scores

- Certificate fraud — the platform issues certificates for completed challenges. An attacker could issue themselves (or anyone else) a certificate for work they never did. Every certificate the platform has issued now has a question mark over it

- VM control — admin can start and stop virtual machines for any user, meaning you could kill someone’s active session mid-challenge

- No detection — because you’re using a legitimate account and only modifying traffic client-side, nothing unusual shows up in server logs

## Root Cause

The application was storing the full user object including the role in `sessionStorage` and then reading that role back on every subsequent request to make authorization decisions. There was no server-side verification that the role being claimed actually matched what was in the database.

The fix is straightforward:

- Never read role from client-supplied data. The server should derive the user’s identity from a secure, signed token (session cookie or JWT), then look up their actual role from the database on every request.

- Enforce access control server-side on every admin endpoint. If the role check doesn’t exist in your backend code, a frontend check is meaningless.

- Store only an opaque token in the browser. The client doesn’t need to know what your role is. Give it a random token that means nothing on its own, and let the server do the lookup.

## Closing Thoughts

Broken access control has sat at #1 on the OWASP Top 10 for years, and this is a textbook example of why. It’s not always some sophisticated exploit chain sometimes it’s just the server being too trusting about data it receives from the client.

The issue was reported responsibly through official VDP.

---
