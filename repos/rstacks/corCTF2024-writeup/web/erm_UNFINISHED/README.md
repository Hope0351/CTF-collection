# erm

## Description

erm guys? why does goroo have the flag?

[erm.be.ax](https://erm.be.ax)

## Attachments

[erm.tar.gz](attachments/erm.tar.gz)

## Solution (Unfinished)

- The challenge website is very similar to the [real Crusaders of Rust website](https://cor.team/).
By examining the attachment, we can see that this website uses a SQL database to manage the list
of members and writeups that are displayed on the site.

- In <code>db.js</code>, one of the files in the attachment, this code segment is of note:

```
// the forbidden member
// banned for leaking our solve scripts
const goroo = await Member.create({ username: "goroo", secret: process.env.FLAG || "corctf{test_flag}", kicked: true });
const web = await Category.findOne({ where: { name: "web" } });
await goroo.addCategory(web);
await web.addMember(goroo);
```

- We can see that the member "goroo" is added to the database. If we can access their entry, we can check their value
of "secret" to determine the flag. However, note that goroo's "kicked" parameter is set to
<code>true</code>.

- In <code>app.js</code>, another file in the attachment above, we can find a list of endpoints
for GET requests. Of particular note is the following:

```
app.get("/api/members", wrap(async (req, res) => {
    res.json({ members: (await db.Member.findAll({ include: db.Category, where: { kicked: false } })).map(m => m.toJSON()) });
}));
```

- Accessing <code>/api/members</code> will list all members whose "kicked" parameter is <code>false</code>. The
member we need to see is goroo, but his "kicked" status is <code>true</code>. This is where I got
stuck. I tried to find a way to modify the GET request to include all members with [Burp Suite](https://portswigger.net/burp/communitydownload), but
I wasn't able to figure anything out.
