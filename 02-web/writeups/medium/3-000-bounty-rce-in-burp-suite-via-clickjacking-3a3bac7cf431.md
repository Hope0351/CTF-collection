# :globe_with_meridians: $3,000 Bounty: RCE in Burp Suite via Clickjacking

> **Original Source:** [$3,000 Bounty: RCE in Burp Suite via Clickjacking](https://infosecwriteups.com/3-000-bounty-rce-in-burp-suite-via-clickjacking-3a3bac7cf431)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# $3,000 Bounty: RCE in Burp Suite via Clickjacking


## From Click to Command: $3,000 RCE in Burp Suite via Chrome Debug Port


### Summary


In a brilliant attack chain combining Chrome internals Java behavior and UI tricks researcher mattaustin discovered a remote code execution (RCE) vulnerability in Burp Suite. The vulnerability exploits the way Burp Suite’s embedded headless Chrome scanner enables remote debugging allowing attackers to clickjack their way into executing arbitrary OS commands on the host machine. Yes including launching the Calculator app on a Mac.


Let’s dive into how this was achieved and why it matters.

### Root Cause


When Burp launches a Chrome instance for its scanner or crawler it does so in headless mode with the remote debugging port flag enabled. This allows automation and introspection of the browser via a WebSocket interface.


However, Chrome’s remote debugging port is:


- Randomized per instance

- Publicly accessible on localhost

- Not protected by authentication


The researcher combined this with:


- A known JavaScript port scanning trick to discover which port Chrome is listening on

- A clickjacking UI overlay to trick a user into clicking a poisoned frame

- An outdated Chrome XSS vector to execute JavaScript that interacts with the debug WebSocket

- And finally: A way to overwrite JVM options in Burp to achieve RCE on restart.

### Exploit Flow


- Host an HTML payload (burp.html) on a local server.

- Start Burp Suite and run a scan against that server.

- Visit the page in a regular browser (e.g., Chrome): [http://127.0.0.1:8000/burp.html](http://127.0.0.1:8000/burp.html)

- The exploit page uses JavaScript to port scan localhost to find Chrome’s debug port.

- Once found it performs clickjacking to trigger file write via DevTools protocol.

- It writes a malicious user.vmoptions file in: /Applications/Burp Suite Professional.app/Contents/

- On the next Burp restart the JVM loads that file and executes arbitrary code.

### POC Enhancement


In a follow up mattaustin made the exploit quieter by replacing the memory exhaustion trick with a Java Agent.


## Get Monika sharma’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Instead of crashing the JVM to trigger a command they created a small agent.jar:


```
public class Hax {
public static void premain(String args, Instrumentation inst) {
Runtime.getRuntime().exec("open -a Calculator");
}
}
```


By adding this to the user.vmoptions file using:


```
-javaagent:agent.jar
```


The agent runs immediately at JVM startup no crash required.

### Mitigation & Recommendations


PortSwigger could have avoided this attack by:


- Switching to remote-debugging-pipe which avoids exposing a network port.

- Isolating the headless Chrome environment further.

- Preventing UI interactions with the scanning browser.


For developers:


- Avoid exposing debug interfaces without proper isolation.

- If you must expose them restrict access to specific IPs or interfaces.

- Be cautious with file write access in applications like DevTools.

### Impact


An attacker can gain control over the victim’s machine with the same permissions as the user running Burp.


While this required the victim to:


- Run Burp with scan/crawl enabled

- Visit a malicious local page

- Restart the app


…it’s a devastating local privilege escalation vector for shared workstations internal red team setups or even co-working environments.

### Credit


- Hunter: mattaustin

- Bounty: $3,000

- Report id : #1274695

### Final Thoughts


While this issue may seem niche it underscores how attack surfaces aren’t limited to the web app they include the tools we use to test them. The report also reminds us that sometimes the weakest link is not the app but the automation or debug tools surrounding it.


Bug bounty hunters should keep an eye on:


- Debug ports

- Misused dev flags ( — headless, — inspect, etc.)

- Unprotected localhost interfaces


Every overlooked interface is a potential exploit.

>

Happy Hunting ✨Monika ☕✨

---

*Originally published on [Medium](https://infosecwriteups.com/3-000-bounty-rce-in-burp-suite-via-clickjacking-3a3bac7cf431). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
