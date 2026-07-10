# :globe_with_meridians: 🧠 JWT, Meet Me Outside: How I Decoded, Re-Signed, and Owned the App 🔐💥

---

# 🧠 JWT, Meet Me Outside: How I Decoded, Re-Signed, and Owned the App 🔐💥

Free Link🎈

Hey there!😁

*Gif*

Ever try sneaking back into your own house after forgetting your keys… but instead of picking the lock, you just tell the lock you’re the owner?
Yeah. That’s basically JWT hacking — in hacker terms, not drunk-in-the-middle-of-the-night terms. 😂

Life pro tip: If life gives you locked doors, give life a forged ID and walk in like you own the place.
That’s what happened to me one caffeine-fueled evening. ☕💀

This is the story of how one insecure JWT almost paid for my next two vacations. 🏖️

## 🔍 Phase 1: Recon — Finding the Hidden Treasure Chest 🧭

Mass recon is not just a hobby — it’s a full-on relationship.
Here’s what I started with:

```
subfinder -d target.com -silent > subs.txt
httpx -l subs.txt -mc 200,302 -title -tech-detect -vhost -web-server > live.txt
```

After hours of scrolling through boring stuff (because recon is 90% pain), I spotted a curious endpoint:

```
https://api.target.com/auth/validate_token
```

---
