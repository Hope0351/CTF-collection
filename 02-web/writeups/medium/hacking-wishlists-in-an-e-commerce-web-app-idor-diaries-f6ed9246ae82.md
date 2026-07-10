# :globe_with_meridians: Hacking Wishlists in an E-commerce Web App (IDOR Diaries)

---

# Hacking Wishlists in an E-commerce Web App (IDOR Diaries)

If you haven’t checked other writes on the IDOR Diaries series you check below write-ups

## Vulnerability

We was testing a Shopping website where we came across a wired wishlist. We were able to view private and public wishlists fo any user in the website. So the wishlist URL looked like below sample URL

```
https://www.xyz.com/find/wishlist.jsp#/1122A36R456/supun-default-wish-list
```

First we tried removing the /*supun-default-wish-list *which gave us a 404 error . The URl looked like below

```
https://www.xyz.com/find/wishlist.jsp#/1122A36R456
```

Then we added “/” to the url which looked like

```
https://www.xyz.com/find/wishlist.jsp#/1122A36R456/
```

It provided the results of the private wishlist of another user.

---
