# :globe_with_meridians: Making A SQLi Lab Is Not Difficult, Build One With Me.

---

# Making A SQLi Lab Is Not Difficult, Build One With Me.

In the previous part we made a lab with vulnerabilities that, at least to me, is one of the coolest. Today we’re building a lab that can be very destructive for a company. SQLi is one of the most intrusive attacks because we don’t need to elevate privileges. In some cases, like this lab, you don’t even need a proxy like Burp.

## SKWEEL What?

A running joke at my company is that we work very hard to make juniors believe that you pronounce SQL as *skweel*. And you would be surprised how many times this works. We don’t say it one time, no no no. When we as seniors are talking in meetings, even with leadership (yes they are also in the joke), we consistently pronounce it *skweel*. After one week, almost every single one of the juniors start using that term and it is probably not so hilarious if you are reading it, but I always have the time of my life.

Anyway… SQL injection is when an attacker is able to insert or manipulate SQL queries through user-controlled input. Instead of the application treating your input as data, it accidentally treats it as code. The database executes whatever you slipped in. That’s it. No CVE needed, no kernel exploit — just a quote character and a lack of input sanitization.

## Lab Tree

As you’re used by now in this series, we start with the folder structure. For this SQLi lab, it is going to look like this.

```
/mediumLabs
└── /SQLi
├── /node_modules
├── server.js
├── guest.html
├── admin.html
├── login.html
├── package-lock.json
└── package.json
```

Three HTML files, one backend. The idea is simple: a login form that lets you in as either a `guest` or an `admin`, backed by a SQLite database. The vulnerability lives in `server.js` and the goal is to reach `admin.html` without knowing the admin password.

## Getting Started

## Dependencies

The boilerplate for the code is simple enough. But first we need to install some dependencies. So when you’re in `mediumLabs` (in the terminal, you're a hacker!), create a directory SQLi with `mkdir SQLi`. After you `cd` into it, start with `npm init` to create `package.json`. After that we're going to install our dependencies with `npm i nodemon express better-sqlite3 jsonwebtoken`, this will also make `package-lock.json` and your folder `node_modules`.

## Code

In this part, I’m just gonna give you the boilerplate code. Try and use `vim` inside the terminal. Alternatively I do accept if you do it in your favorite IDE. However, Word isn't an IDE 😄

server.js

```
const express = require('express');
const Database = require('better-sqlite3');
const jwt = require('jsonwebtoken');
const path = require('path');
const app = express();
const db = new Database(':memory:');
const JWT_SECRET = 'sqli-lab-secret';
db.exec(`
CREATE TABLE users (
id INTEGER PRIMARY KEY,
username TEXT,
password TEXT,
role TEXT
)
`);
db.prepare("INSERT INTO users (username, password, role) VALUES ('guest', 'guest123', 'guest')").run();
db.prepare("INSERT INTO users (username, password, role) VALUES ('admin', 'sup3rs3cr3t', 'admin')").run();
app.use(express.urlencoded({ extended: false }));
function getToken(req) {
const auth = req.headers.authorization;
if (auth && auth.startsWith('Bearer ')) return auth.slice(7);
const match = (req.headers.cookie || '').match(/token=([^;]+)/);
return match ? match[1] : null;
}
function requireAuth(req, res, next) {
try {
req.user = jwt.verify(getToken(req), JWT_SECRET);
next();
} catch {
res.redirect('/');
}
}
function requireAdmin(req, res, next) {
try {
req.user = jwt.verify(getToken(req), JWT_SECRET);
if (req.user.role !== 'admin') return res.status(403).send('403 Forbidden');
next();
} catch {
res.redirect('/');
}
}
app.get('/', (req, res) => res.sendFile(path.join(__dirname, 'login.html')));
app.post('/login', (req, res) => {
// TODO Implement login logic
});
app.get('/guest', requireAuth, (req, res) => res.sendFile(path.join(__dirname, 'guest.html')));
app.get('/admin', requireAdmin, (req, res) => res.sendFile(path.join(__dirname, 'admin.html')));
app.get('/logout', (req, res) => {
res.setHeader('Set-Cookie', 'token=; Max-Age=0; Path=/');
res.redirect('/');
});
app.listen(3000, () => console.log('Listening on http://localhost:3000'));
```

guest.html

```
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Guest</title>
</head>
<body>
<h1>Welcome, Guest!</h1>
<p>You are logged in with the <strong>guest</strong> role.</p>
<a href="/logout">Logout</a>
</body>
</html>
```

admin.html

```
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Admin</title>
</head>
<body>
<h1>Welcome, Admin!</h1>
<p>You are logged in with the <strong>admin</strong> role.</p>
<a href="/logout">Logout</a>
</body>
</html>
```

login.html

```
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Login</title>
</head>
<body>
<h1>Login</h1>
<form method="POST" action="/login">
<div>
<label>Username: <input type="text" name="username" required></label>
</div>
<div>
<label>Password: <input type="password" name="password" required></label>
</div>
<button type="submit">Login</button>
</form>
</body>
</html>
```

package.json

```
{
"name": "sqli",
"version": "1.0.0",
"description": "",
"license": "ISC",
"author": "",
"type": "commonjs",
"main": "server.js",
"scripts": {
"start": "node server.js",
"dev": "nodemon server.js"
},
"dependencies": {
"better-sqlite3": "^12.10.0",
"express": "^5.2.1",
"jsonwebtoken": "^9.0.3",
"nodemon": "^3.1.14"
}
}
```

## Adding Some Vulnerable Code

Now for the fun part, writing some mistakes. The big mistake developers make when creating a query, is allowing raw userinput. In code it looks like this:

```
let query = `select * from secrets where
clearance = '${userClearance}'
and clearancePassword = '${clearancePassword}';`
```

In this scenario we imagine a system where you can access documents with a certain security clearance threshold by providing the password that you receive when you get your security clearance. We use backticks so we can easily import the variables that are filled in when the user enters the credentials.

## Get ShadowForge’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

If a user would enter TOP SECRET, but didn’t know the password, the query would return 0 results. But what happens if we comment out the `and` part? If we'd enter `TOP SECRET' -- -` the query that would be executed would look like this:

```
SELECT * FROM secrets where clearance = 'TOP SECRET' -- -' AND clearancePassword = wrong_password;
```

As you see, the security control (the password), is just commented out, and will not be evaluated. This results in the user being able to see top secret documents without having the right password (and credentials). Exactly what we want for our lab!

In our lab, we are going to make it possible to log in as `admin` without providing the correct password. In our code, we're gonna add this to the `POST` request to `/login`

```
app.post('/login', (req, res) => {
const { username, password } = req.body;
const query = `SELECT * FROM users WHERE username = '${username}' AND password = '${password}'`;
let user;
try {
user = db.prepare(query).get();
} catch (e) {
return res.status(400).send(`SQL Error: ${e.message}`);
}
if (!user) return res.redirect('/?error=Invalid+credentials');
const token = jwt.sign({ username: user.username, role: user.role }, JWT_SECRET, { expiresIn: '1h' });
res.setHeader('Set-Cookie', `token=${token}; HttpOnly; Path=/`);
res.redirect(user.role === 'admin' ? '/admin' : '/guest');
});
```

In this code we made the exact same mistake as I explained in the example of our secret documents. You’ll also notice the `catch` block sends the raw SQL error message back to the browser — that's a second intentional vulnerability. In a real app, leaking database errors is a serious info disclosure: it tells an attacker exactly what their payload broke and makes tuning an injection much easier. In our lab, it's a deliberate feature that gives you feedback while you experiment. Never do this in production. In the `try` block, we assign the variable `user` with the result of the query. But, we are going to make sure that our code never checks if we even know the password of the user "admin".

Once you added this to the code, hit save and run `npm start` or `npm run dev` if you want to use `nodemon`.

>

*If you don’t know, using nodemon prevents you from having to turn off and bring back on your server each time you change something to your code. If you hit *`*CMD-S*`* or *`*CTRL-S*`*, nodemon will automatically restart your server.*

## Exploit Our Vulnerability

I promised you in the beginning of this post that you wouldn’t need any special tools to exploit this app, and I tend to keep my promises. Now if you read through this blog, you will probably already know what payload you need to use in the inputfield for `username`.

If you entered the payload `admin' -- -`, and a random password, you are now looking at the admin page. Congratulations!

## Challenge

Before I drop the challenge, a quick heads-up: to solve this one you’ll need a different technique called UNION-based injection. While comment-based injection (`-- -`) lets you skip parts of a query, UNION injection lets you *append* a second query and pull data from a completely different table. The basic idea is that if the original query returns one row with N columns, you can tack on `UNION SELECT col1, col2, ... FROM other_table -- -` and the database will return both rows together. The trick is getting the column count right. If your UNION doesn't match the number of columns in the original query, you'll get an error. That error message in your browser? That's your feedback loop.

So now the challenge! I want you to open `server.js`, and add this to the database seed on line 20.

```
db.exec(`
CREATE TABLE secrets (
id INTEGER PRIMARY KEY,
level TEXT,
prio TEXT,
secret TEXT
)
`);
db.prepare("INSERT INTO secrets (level, prio, secret) VALUES ('confidential', 'low', 'flag{sql_union_is_powerful}')").run();
```

After you saved it and your server is up and running, your job is to get the flag reflected in your `JWT`.

## My Proof

>

*Should you not be able to figure it out, do reach out to me! I’ll be more than happy to help you out.*

## How To Avoid This Vulnerability

Avoiding SQLi isn’t about complex coding structures. It’s not about implementing packages that mitigate it. It’s all about `prepared statements`. Instead of using backticks with the `${}` syntax (or `let query = baseString + userInput` if you're old school), you'll be using this syntax instead:

```
app.post('/login', (req, res) => {
const { username, password } = req.body;
const user = db.prepare('SELECT * FROM users WHERE username = ? AND password = ?').get(username, password);
// rest of the code
});
```

The question marks will make sure that no malicious payload can creep up in the query itself.

Services like Cloudflare can be a addition in trying to avoid SQLi attempts to be send to the server, but having `prepared statements` in your backend should be default use by developers and your number 1 defence against SQLi. Luckily AI tools like Claude will do this by default, so even though AI slop will still be there, at least SQLi will hopefully become something from the past in a few years.

The real takeaway here is simple: never trust user input, and never let it touch a raw query. One quote character is all it takes to go from a login form to a full database dump. That’s the power and the danger of SQL injection.

Next up we’re looking at IDOR (Insecure Direct Object Reference), a vulnerability so simple it almost feels like cheating. No injections, no clever payloads. Just changing a number in a URL and seeing what you’re not supposed to see. Stay tuned.

---
