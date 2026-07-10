# :globe_with_meridians: How Recon → SQLi Made €€€€ Bounty

> **Original Source:** [How Recon → SQLi Made €€€€ Bounty](https://infosecwriteups.com/how-recon-sqli-made-bounty-425fc0fa2e92)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# How Recon → SQLi Made €€€€ Bounty


Hi there…!


Free [Link](https://medium.com/@iski/how-recon-sqli-made-bounty-425fc0fa2e92?sk=652b2102340fe05aa3502595714aba94)🎈


With a boooooooooring evening and zero plans, I sat there contemplating life choices — should I fix my sleep schedule or start another anime marathon?


Then my evil brain whispered: “Why not hack something instead of reorganizing your room for the 100th time?”


So, like every bug hunter avoiding reality, I fired up my tools.

## 🕵️‍♀️ The Recon Phase


I started manual recon using tools like waybackurls, katana, and gauplus.


Result? Tons of juicy URLs — but most of them gave me the classic 403 Forbidden.


I bypassed the 403 using 403 bypasser tools.


Since it was a Java app running on Apache Tomcat, the backslash had to be encoded as: `%5c`.


Even the 500 Internal Server Error could be bypassed using a double backslash.

## 🥸 The Hidden Gems


Pro tip: Don’t forget to dig through JS files — sometimes, they hide treasure.


I got lucky and found some juicy parameters:


- SelectedSources

- SelectedNames

- SelectedTemplate


My bug hunter instincts kicked in. Time to test for SQLi!

## ⚡ The SQLi Attack

---

*Originally published on [Medium](https://infosecwriteups.com/how-recon-sqli-made-bounty-425fc0fa2e92). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
