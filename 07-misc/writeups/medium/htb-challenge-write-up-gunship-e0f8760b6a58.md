# :game_die: HTB Challenge Write-Up: Gunship. Code Review

---

## Code Review

Gunship is a Node.js application with a single API endpoint. A quick inspection of the `package.json` file revealed that it uses the [Pug](https://pugjs.org/)template engine leading me to believe it’s a *Server-Side Template Injection (SSTI) *challenge. However, there’s no parameter that we can pass to the template to test for an SSTI vulnerability. Let’s investigate further.

```
router.post('/api/submit', (req, res) => {
const { artist } = unflatten(req.body);

if (artist.name.includes('Haigh') || artist.name.includes('Westaway') || artist.name.includes('Gingell')) {
return res.json({
'response': pug.compile('span Hello #{user}, thank you for letting us know!')({ user: 'guest' })
});
}

// Code omitted for brevity
});
```

Running `npm install` and `npm audit` not only revealed that the Pug version *(3.0.0)* used by the application is vulnerable to *Remote Code Execution (RCE)*, but also showed that the application uses a version of the `flat` package *(5.0.0)* that is vulnerable to *Prototype Pollution*.

Now that we have identified vulnerabilities that we can chain together, let’s test the application and trace the code execution.

## Local Testing

Let’s install `nodemon` and use the VS Code Debugger to run the application in debug mode.

Going back to the code, the artist names Haigh, Westaway, and Gingell must be used to reach the Pug code. While stepping into the `pug.compile` function, I noticed that Pug defaults its `options` variable to an empty object if not provided—a potential point for prototype pollution.

Now, let’s test the payload mentioned in this GitHub [issue](https://github.com/pugjs/pug/issues/3312). Using Burp Suite Repeater, I resent the request to `/api/submit` with this payload:

Well, that didn’t work. While trying to trace the code execution within the packages, I came across the variable `ast`. It must be referring to the *Abstract Syntax Tree*, right? I just learned about this concept recently while searching for open-source forks of a specific archived library on GitHub.

## Get Pat Bautista’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

After searching for *"pug AST RCE"*, I discovered a Medium article discussing *AST injection*. It details how Pug is vulnerable to RCE through AST injection. Now let’s test this payload:

That worked! Now that we have a functioning payload, it’s time to exploit the vulnerability.

## Exploitation

First, let's launch the Hack The Box Challenge instance. While that is in progress, let’s check the potential file path for the flag by examining the `Dockerfile `and `entrypoint.sh`. It should be formatted like this: `/app/flagCCCCC`, where each 'C' represents a random alphanumeric character.

Since the file path of the flag contains random characters, let’s use the `cp` command with a wildcard to copy the flag to a location we can access — the static folder.

Now let’s view the flag using the `curl` command.

We have successfully captured the flag!

## References

---
