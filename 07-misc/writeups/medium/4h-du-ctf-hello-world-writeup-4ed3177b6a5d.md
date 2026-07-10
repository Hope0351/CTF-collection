# :game_die: 4H Du Ctf Hello World Writeup 4Ed3177B6A5D

---

Let’s download ourselves some password recovery tool and get to work.

prt.go

```
package prtimport (
"crypto/sha256"
"encoding/hex"
"net/http"
"strconv"
"html/template"
)type PasswordRecoveryTool struct {
Password []byte
Minimum uint64
templates *template.Template
}func NewPasswordRecoveryTool(s string, minimum uint64, tmpl *template.Template) *PasswordRecoveryTool {
return &PasswordRecoveryTool{[]byte(s), minimum, tmpl}
}func (prt PasswordRecoveryTool) hashPassword(extraTimes uint64) string {
tmp := prt.Password
var hash [32]byte
for x := prt.Minimum; x <= prt.Minimum + extraTimes && x <= 30; x++ {
hash = sha256.Sum256(tmp)
tmp = hash[:]
}	return hex.EncodeToString(tmp)
}func (prt PasswordRecoveryTool) ServeHTTP(w http.ResponseWriter, r *http.Request) {
err := r.ParseForm()
if err 	!= nil {
http.Error(w, err.Error(), http.StatusBadRequest)
return
}
extra, err := strconv.ParseUint(r.FormValue("x"), 10, 64)
if err != nil {
extra = 0
}	h := prt.hashPassword(extra)	prt.templates.ExecuteTemplate(w,"recover.html", h)
return
}
```

Now, why the hell is there a form value involved with hashing a password? that’s where I should focus my efforts.

I tried using negative numbers at first because I didn’t realize it was an unsigned int due to the fact I get too excited when I make progress and want to get it done as fast as possible. Also, I’m dumb :)

In addition to the negative number, I tried words, special characters, etc, etc to maybe trigger some kind of error. But alas it would always return the same hashed password.

At this point, I decided since I have all the code I will just run it on my computer that way I can debug it with GoLand to step through and see what’s what.

I took a small break at this point to get some lunch and brainstorm how I can convince the server to give me an unhashed password. I thought about what data types (uint64) were used for user inputs and how they are used in the code.

Side note, did you know the largest uint64 that’s possible is 18,446,744,073,709,551,615? This is interesting because our values are uint64s and in our use case 2 uint64s get added together :) so if I pass in a value it can’t calculate correctly it will just return the password in hex form and just skip the for loop in the hashpassword function

I send it off with this curl

```
curl --request POST \\
--url <http://challenges.ctfd.io:30537/recover> \\
--header 'Content-Type: application/x-www-form-urlencoded' \\
--data x=18446744073709551615 \\
--data =
```

Response to the hex-encoded password :D

Converting the hex to ascii gives us this as a result: `WowDidYouReallyCrackThisPassword` yep that looks like a standard CTF password! Let's through it in the admin panel and see if we get a flag.

Look at that! Perfect!

*Success!*

## Retrospective

This was a fairly easy challenge but it was fun since it was the first CTF I’ve done in quite a few months. I love challenges where you get to read the code and extract a vuln from it. It makes it easier but it’s great to see the thought process behind blocking security vulns.

If you have any questions or comments on how I went about this, feel free to reach out to me!

---
