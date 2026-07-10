# :mobile_phone: Millions Of Records Exposed Via Sql Injection In A Tamil Nadu Government Portal 

---

## How I Found the Vulnerable Endpoint

After spending hours manually testing and coming up short, I decided to run dirsearch to uncover hidden endpoints.

```
dirserach -u https://example.com -w word.txt -o output.txt
```

Eventually, I stumbled upon an admin login panel.

I began fuzzing it with typical SQLi payloads in the input fields of the admin login pannel(`'`, `"`, `--`, etc.), and received an Internal Server Error (500) — a classic sign that something was breaking server-side. At this point, I knew I was onto something.

## Get Hack-Bat’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

I fired up SQLMap to automate the testing and dump the data:

```
sqlmap -r request.txt --batch --threads=10 --level=3 --dump
```

And boom 💥 — it started dumping entire database.

---
