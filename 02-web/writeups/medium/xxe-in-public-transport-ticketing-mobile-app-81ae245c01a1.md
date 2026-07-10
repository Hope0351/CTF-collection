# :globe_with_meridians: XXE in Public Transport Ticketing Mobile APP

---

Finally, I replaced the payload in the original request and forwarded the request to the server. And, bang! I got the content of `/etc/passwd`

Since the application was using java, you can even list the directories by using the following payload

```
<?xml version="1.0" encoding="UTF-8"?><!DOCTYPE aa[<!ELEMENT bb ANY><!ENTITY xxe SYSTEM "file://">]>
```

I was mainly looking for SSH private keys but out of curiosity, I tried to fetch `/etc/shadow` (feeling lucky :D). And, to my surprise, I got it (this is a rare case). The response makes it clear that it’s running as root.

---
