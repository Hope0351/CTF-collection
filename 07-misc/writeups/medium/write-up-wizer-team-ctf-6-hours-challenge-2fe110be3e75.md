# :game_die: Write-up, Wizer Team CTF 6-hours challenge

> **Original Source:** [Write-up, Wizer Team CTF 6-hours challenge](https://infosecwriteups.com/write-up-wizer-team-ctf-6-hours-challenge-2fe110be3e75)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# Write-up, Wizer Team CTF 6-hours challenge


So this weekend Wizer hosted a CTF 6-hours Blitz challenge!


I managed to crack 2 of the challenges,


- #1 JWT Authentication 🌶

- #2 Nginx Configuration 🌶 🌶


I did manage to take some screenshots so i will add them as well


## #1 JWT Authentication 🌶


*Get the flag!*
We got a block of code and a form to submit our payload!


```
const express = require('express');
const jwt = require('jsonwebtoken');
const bodyParser = require('body-parser');

const app = express();
app.use(bodyParser.json());
const SECRETKEY = process.env.SECRETKEY;

// Middleware to verify JWT token
// This API will be used by various microservices. These all pass in the authorization token.
// However the token may be in various different payloads.
// That's why we've decided to allow all JWT algorithms to be used.
app.use((req, res, next) => {
const token = req.body.token;

if (!token) {
return res.status(401).json({ message: 'Token missing' });
}

try {
// Verify the token using the secret key and support all JWT algorithms
const decoded = jwt.verify(token, SECRETKEY, { algorithms: ['HS256', 'HS384', 'HS512', 'RS256', 'RS384',
'RS512'…
```

---

*Originally published on [Medium](https://infosecwriteups.com/write-up-wizer-team-ctf-6-hours-challenge-2fe110be3e75). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
