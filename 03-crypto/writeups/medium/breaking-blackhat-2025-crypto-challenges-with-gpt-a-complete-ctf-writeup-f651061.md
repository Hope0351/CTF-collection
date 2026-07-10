# :locked_with_key: Breaking BlackHat 2025 Qualifiers Crypto Challenges with GPT: A Complete CTF Writeup

> **Original Source:** [Breaking BlackHat 2025 Qualifiers Crypto Challenges with GPT: A Complete CTF Writeup]()
> **Platform:** medium.com | **Category:** `CRYPTO`

---

# Breaking BlackHat 2025 Qualifiers Crypto Challenges with GPT: A Complete CTF Writeup


This blog contains the solutions to all the crypto challenges from BlackHat 2025. I had no prior background in cryptography, and working on these challenges was not part of my original plan. My initial focus was on web challenges, but since our team already had a skilled web specialist, four0four, handling them independently, I turned my attention to crypto.


I began exploring the challenges using GPT and applied prompt engineering to tackle them. Step by step, I was able to solve all three with the help of ChatGPT.

## Table of Contents


- Hatagawa

- Hatagawa II

- Whack A Scratch

## Hatagawa


```
# Let's solve the user's instance from the 4 ciphertexts they pasted.
# We'll implement robust 2-adic bit-by-bit root finding for x^k ≡ A (mod 2^64)
# and enumerate the small ambiguity, then decrypt and pick the plausible flag.

from typing import List, Tuple
import binascii

MASK64 = (1<<64)-1

hexes = [
"e4252f73fda6346a30f365",
"5de035419f7f80102798b",
"7199def8b620c0b4f5d8d",
]

def v2(n: int) -> int:
if n == 0: return 64
return (n & -n).bit_length()-1

def first_block_u64(h: str) -> int:
b = bytes.fromhex(h)[:8]
return int.from_bytes(b, 'big')

def geom_series_mod_2n(a: int, k: int, nbits: int = 64) -> int:
mod = 1<<nbits
def rec(m: int):
if m == 0: return (0, 1)
if m == 1: return (1 % mod, a % mod)
S, ap = rec(m//2)
if m % 2 == 0:
return ((S * (1 + ap)) % mod, (ap * ap) % mod)
else:
S2 = (S * (1 + ap)) % mod
a2 = (ap * ap) % mod
return ((S2 + a2) % mod, (a2 * a) % mod)
return rec(k)[0] % mod

def inv_mod_2n_odd(x: int, nbits: int) -> int:
assert x & 1
inv = 1
m = 2
for _ in range(1, nbits):
m <<= 1
inv = (inv * (2 - (x * inv) % m)) % m
return inv % (1<<nbits)

def kth_roots_mod_2n_via_bitlift(A: int, k: int, nbits: int = 64) -> List[int]:
"""Find all odd solutions a (mod 2^nbits) to a^k ≡ A, constrained to a ≡ 5 (mod 8).
We do bit-by-bit lifting by trying both choices at each new bit and keeping those that satisfy."""
roots = [5] # start with 5 mod 8
for bit in range(3, nbits):
M_next = 1 << (bit+1)
new_roots = []
for r in roots:
r0 = r % M_next
r1 = (r + (1<<bit)) % M_next
# test both
if pow(r0, k, M_next) == (A % M_next):
new_roots.append(r0)
if pow(r1, k, M_next) == (A % M_next):
new_roots.append(r1)
# deduplicate
roots = sorted(set(new_roots))
if not roots:
break
# ensure full width
roots = [r % (1<<nbits) for r in roots]
# filter odd and congruent to 5 mod 8 (should already be)
roots = [r for r in roots if (r & 7) == 5]
return roots

# Parse data
KNOWN8 = int.from_bytes(b'BHFlagY{', 'big')
msg_len = len(bytes.fromhex(hexes[0]))
k_blocks = (msg_len + 7)//8

y = [first_block_u64(h) ^ KNOWN8 for h in hexes]
diffs = [ (y[i+1] - y[i]) & MASK64 for i in range(len(y)-1) ]
v = min(v2(d) for d in diffs)

# A modulo 2^{64-v}
# pick an index with minimal valuation on consecutive diffs
idx = None
for i in range(len(diffs)-1):
if v2(diffs[i]) == v and v2(diffs[i+1]) == v:
idx = i; break
if idx is None: idx = 0
d0 = diffs[idx] >> v
d1 = diffs[idx+1] >> v
A_low = (d1 * inv_mod_2n_odd(d0, 64 - v)) % (1 << (64 - v))
A_candidates = [(A_low + t*(1 << (64 - v))) & MASK64 for t in range(1<<v)]

# Try each A-candidate
solutions = []
for A in A_candidates:
roots = kth_roots_mod_2n_via_bitlift(A, k_blocks, 64)
if not roots:
continue
for a in roots:
S = geom_series_mod_2n(a, k_blocks, 64)
B = (y[1] - (A * y[0])) & MASK64
vk = v2(k_blocks)
if vk == 0:
invS = inv_mod_2n_odd(S, 64)
c = (B * invS) & MASK64
sols = [c]
else:
assert (S & ((1<<vk)-1)) == 0
assert (B & ((1<<vk)-1)) == 0
Sprime = S >> vk
Bprime = B >> vk
invSprime = inv_mod_2n_odd(Sprime, 64 - vk)
base_c = (Bprime * invSprime) % (1 << (64 - vk))
sols = [ (base_c + (t << (64 - vk))) & MASK64 for t in range(1<<vk) ]
sols = [c for c in sols if (c & 1)] # c must be odd
# try decrypt with each c
for c in sols:
x = y[0]
stream = b''
for _ in range(k_blocks):
stream += int(x).to_bytes(8,'big')
x = (a * x + c) & MASK64
pt = bytes(b ^ s for b,s in zip(bytes.fromhex(hexes[0]), stream[:msg_len]))
solutions.append((A,a,c,pt))

# Score candidates
def score(bs: bytes) -> int:
return int(bs.startswith(b'BHFlagY{')) + int(bs.endswith(b'}')) + sum(32 <= b <= 126 for b in bs)

best = None
if solutions:
best = max(solutions, key=lambda t: score(t[3]))

print("k_blocks:", k_blocks, "v2(diffs):", [v2(d) for d in diffs], "min v:", v)
print("A candidates:", [hex(A) for A in A_candidates])

if best:
A,a,c,pt = best
print("Chosen A,a,c:", hex(A), hex(a), hex(c))
print("Plaintext guess:", pt)
print("As ASCII:", pt.decode('ascii', errors='replace'))
else:
print("No candidates found (unexpected).")
```


## Hatagawa-II


This exploit will give four possible flags in the output, and only one of them will be correct.


```
# Compute all candidate flags for Hatagawa II instance using 5 ciphertext lines.
from typing import List, Tuple, Set

hex_lines = [
"a25f483211ad62d0",
"02682304c61cfe41",
"903dbbc1bd9661f2",
"06f5ea558511deeb",
"b9017794e283b7a4",
]

def split_pairs(hexes: List[str]) -> List[Tuple[int,int]]:
pairs = []
for h in hexes:
b = bytes.fromhex(h)
u = int.from_bytes(b[:8], 'big')
v = int.from_bytes(b[8:], 'big')
pairs.append((u, v))
return pairs

pairs = split_pairs(hex_lines)

def lift_solve_with_all_constraints(pairs: List[Tuple[int,int]]):
# Lift unknowns a,c,P0,P1 modulo 2^{i+1} from i=0..63
states: Set[Tuple[int,int,int,int]] = set()
# init for i=0 (mod 2): a0=1, c0=1; try p0_0,p1_0 in {0,1}
for p0b in (0,1):
for p1b in (0,1):
a_low=1; c_low=1; p0_low=p0b; p1_low=p1b
ok=True
for idx,(u,v) in enumerate(pairs):
if ((v ^ p1_low) - (a_low*(u ^ p0_low) + c_low)) & 1: ok=False;break
if idx+1 < len(pairs):
u2,v2 = pairs[idx+1]
if ((u2 ^ p0_low) - ( (a_low*a_low) * (v ^ p1_low) + c_low*(a_low + 1) )) & 1: ok=False;break
if ((v2 ^ p1_low) - ( (a_low*a_low*a_low) * (v ^ p1_low) + c_low*((a_low*a_low) + a_low + 1) )) & 1: ok=False;break
if ok: states.add((a_low,c_low,p0_low,p1_low))
# lift
for i in range(1,64):
mod = 1 << (i+1)
new_states: Set[Tuple[int,int,int,int]] = set()
for (a_low,c_low,p0_low,p1_low) in states:
a_bits = [0,1]
if i==1: a_bits=[0] # a1=0
if i==2: a_bits=[1] # a2=1
for ai in a_bits:
a_new = a_low | (ai<<i)
for ci in (0,1):
c_new = c_low | (ci<<i)
for p0i in (0,1):
p0_new = p0_low | (p0i<<i)
for p1i in (0,1):
p1_new = p1_low | (p1i<<i)
ok=True
for idx,(u,v) in enumerate(pairs):
# per-press
if (( (v ^ p1_new) - ( (a_new * ((u ^ p0_new) % mod)) + c_new ) ) % mod):
ok=False;break
if idx+1 < len(pairs):
u2,v2 = pairs[idx+1]
# cross u
if (( (u2 ^ p0_new) - ( ((a_new*a_new) % mod) * ((v ^ p1_new) % mod) + (c_new * ((a_new + 1) % mod)) ) ) % mod):
ok=False;break
# cross v
if (( (v2 ^ p1_new) - ( (pow(a_new,3,mod) * ((v ^ p1_new) % mod) + ( c_new * (((a_new*a_new + a_new + 1) % mod)) ) ) % mod ) ) % mod):
ok=False;break
if ok:
new_states.add((a_new % mod, c_new % mod, p0_new % mod, p1_new % mod))
states = new_states
if not states:
return None
# Small cap to avoid explosion (shouldn't trigger with 5 samples)
if len(states) > 20000 and i < 40:
states = set(list(states)[:20000])
return states

sol = lift_solve_with_all_constraints(pairs)
if not sol:
print("No solutions — add 1–2 more lines and retry.")
else:
candidates = []
for (a,c,p0,p1) in sol:
pt = p0.to_bytes(8,'big') + p1.to_bytes(8,'big')
candidates.append("BHFlagY{" + pt.hex() + "}")
# de-dup same plaintext
uniq = sorted(set(candidates))
print("Possible flags ({}):".format(len(uniq)))
for f in uniq:
print(f)
```


## Whack A Scratch


This was one of the harder challenges, and solving it was tough even with GPT. It required careful prompt engineering and well-structured commands. After about five hours of intense prompting, the solution finally worked on the third code attempt.


Run scripts with these arguments:


```
python3 <filename> <ip> <port> - start-batch 256 - max-batch 16192 - timeout 120
```


```
#!/usr/bin/env python3
# Whack-A-Scratch solver (stream-safe burst pipelining + checkpoint/resume + progress + cashbox retry)

import argparse, json, os, queue, re, signal, socket, sys, threading, time

# -------------------- CLI --------------------
def parse_args():
p = argparse.ArgumentParser(description="Whack-A-Scratch solver (stream-safe burst/parallel/resumable)")
p.add_argument("host")
p.add_argument("port", type=int)
p.add_argument("--start-batch", type=int, default=256, help="initial burst per write")
p.add_argument("--max-batch", type=int, default=4096, help="max burst per write")
p.add_argument("--timeout", type=float, default=20.0, help="socket read timeout seconds")
p.add_argument("--status-interval", type=float, default=2.0, help="progress update interval seconds")
p.add_argument("--retry", type=int, default=20, help="cashbox open retries")
p.add_argument("--retry-delay", type=float, default=1.0, help="delay between cashbox retries (s)")
p.add_argument("--redo", action="store_true", help="ignore checkpoint-done flags and recompute all diagonals")
return p.parse_args()

args = parse_args()
HOST, PORT = args.host, args.port
START_BATCH, MAX_BATCH, TIMEOUT = args.start_batch, args.max_batch, args.timeout
STATUS_INTERVAL = args.status_interval
RETRY_N, RETRY_D = args.retry, args.retry_delay
REDO = args.redo

# -------------------- constants --------------------
INT_MOD = (1 << 21) - 9 # 2,097,143
DIM = 6 # 6 diagonals per matrix, 2 matrices => 12 targets

# -------------------- regex prompts --------------------
PROMPT_MENU = re.compile(r"\|\s+Menu\s*\(", re.S | re.I)
ASK_OPEN = re.compile(r"The cash box requires a key", re.I)
RETRIEVE = re.compile(r"You retrieve (\d+) credits\.", re.I)

# per-line tokens (we parse line-by-line to avoid split-line misses)
SUB_OK = "you whacked the ticket machine"
SUB_BROKE = "YOU BROKE MY TICKET MACHINE?!"

# -------------------- checkpoint --------------------
CKPT = f"whack_ckpt_{HOST}_{PORT}.json"
ckpt_lock = threading.Lock()

def default_state():
return {
"work0": [0]*DIM, "work1": [0]*DIM, # whack counts per diagonal (kept even after done)
"val0": [0]*DIM, "val1": [0]*DIM, # recovered diagonal values
"done0": [False]*DIM, "done1": [False]*DIM,
}

def load_ckpt():
if not os.path.exists(CKPT):
return default_state()
try:
with open(CKPT, "r") as f:
st = json.load(f)
base = default_state()
for k in base:
if k in st and isinstance(st[k], list) and len(st[k]) == len(base[k]):
base[k] = st[k]
return base
except Exception:
return default_state()

def save_ckpt(state):
tmp = CKPT + ".tmp"
with open(tmp, "w") as f:
json.dump(state, f)
os.replace(tmp, CKPT)

STATE = load_ckpt()

# allow redo: recompute all diagonals fresh
if REDO:
with ckpt_lock:
STATE["done0"] = [False]*DIM
STATE["done1"] = [False]*DIM
STATE["val0"] = [0]*DIM
STATE["val1"] = [0]*DIM
save_ckpt(STATE)

# current burst sizes (for status)
BATCH0 = [0]*DIM
BATCH1 = [0]*DIM

# -------------------- socket helpers --------------------
def recv_until(sock, patterns, timeout=TIMEOUT):
"""Read until ANY regex pattern matches; return accumulated text (may include extra)."""
sock.settimeout(timeout)
buf = b""
while True:
txt = buf.decode(errors="ignore")
if any(p.search(txt) for p in patterns):
return txt
try:
chunk = sock.recv(65536)
if not chunk:
return txt # EOF
buf += chunk
except (TimeoutError, socket.timeout):
return txt

def resync_to_menu(sock):
"""Nudge and read until Menu appears."""
try:
sock.sendall(b"\n")
except Exception:
pass
txt = recv_until(sock, [PROMPT_MENU], timeout=TIMEOUT)
return PROMPT_MENU.search(txt) is not None

def connect():
s = socket.create_connection((HOST, PORT), timeout=20.0)
try:
s.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
except Exception:
pass
resync_to_menu(s)
return s

# -------------------- burst whacking (stream-safe) --------------------
def send_burst(sock, i, j, k, n):
"""Send 'w' + '(i,j,k)' exactly n times without waiting."""
payload = ("w\n" + f"({i},{j},{k})\n") * n
sock.sendall(payload.encode())

def whack_diag_worker(mat_idx, diag_idx, out_q):
# skip if already done
with ckpt_lock:
if STATE[f"done{mat_idx}"][diag_idx]:
out_q.put((mat_idx, diag_idx, STATE[f"val{mat_idx}"][diag_idx]))
return
count = int(STATE[f"work{mat_idx}"][diag_idx])

def ensure_conn():
while True:
try:
s_ = connect()
return s_
except Exception:
time.sleep(0.2)

s = ensure_conn()
batch = START_BATCH
carry = "" # line-buffer carry across recv() calls
last_save = time.time()

while True:
try:
with ckpt_lock:
(BATCH0 if mat_idx==0 else BATCH1)[diag_idx] = batch

if not resync_to_menu(s):
s.close(); s = ensure_conn()

send_burst(s, mat_idx, diag_idx, diag_idx, batch)

ok_seen = 0
broke_seen = False
s.settimeout(TIMEOUT)

# stream-safe line parsing
while ok_seen < batch and not broke_seen:
chunk = s.recv(65536).decode(errors="ignore")
if not chunk:
s.close(); s = ensure_conn(); break

carry += chunk
while True:
nl = carry.find("\n")
if nl == -1:
break
line = carry[:nl]
carry = carry[nl+1:]

if SUB_BROKE in line:
broke_seen = True
# add the final increment (no OK printed for it)
count += ok_seen + 1
val = (INT_MOD - count) % INT_MOD
with ckpt_lock:
STATE[f"work{mat_idx}"][diag_idx] = count
STATE[f"val{mat_idx}"][diag_idx] = val
STATE[f"done{mat_idx}"][diag_idx] = True
save_ckpt(STATE)
try:
s.close()
except Exception:
pass
print(f"[+] static[{mat_idx}][{diag_idx},{diag_idx}] = {val}")
out_q.put((mat_idx, diag_idx, val))
return

if SUB_OK in line.lower():
ok_seen += 1

if not broke_seen:
count += ok_seen
if batch < MAX_BATCH:
batch = min(MAX_BATCH, max(START_BATCH, batch * 2))

except (TimeoutError, socket.timeout):
try:
if not resync_to_menu(s):
s.close(); s = ensure_conn()
except Exception:
try:
s.close()
except Exception:
pass
s = ensure_conn()
except Exception:
try:
s.close()
except Exception:
pass
s = ensure_conn()

# periodic checkpoint & progress
now = time.time()
if now - last_save > 2.0:
with ckpt_lock:
STATE[f"work{mat_idx}"][diag_idx] = count
save_ckpt(STATE)
done_total = sum(STATE["done0"]) + sum(STATE["done1"])
print(f"[.] diag({mat_idx},{diag_idx}) progress: {count} whacks; overall done {done_total}/12; batch={batch}")
last_save = now

# -------------------- status printer --------------------
stop_status = threading.Event()

def status_printer():
last_total = 0
last_t = time.time()
while not stop_status.wait(STATUS_INTERVAL):
with ckpt_lock:
done0, done1 = STATE["done0"][:], STATE["done1"][:]
work0, work1 = STATE["work0"][:], STATE["work1"][:]
b0, b1 = BATCH0[:], BATCH1[:]
total_whacks = sum(work0) + sum(work1)
dt = max(1e-6, time.time() - last_t)
rate = (total_whacks - last_total) / dt
last_total = total_whacks
last_t = time.time()
done = sum(done0) + sum(done1)

def row(tag, work, done_flags, batches):
counts = " ".join(f"{w:>7d}{'*' if d else ' '}" for w,d in zip(work, done_flags))
bsz = " ".join(f"{b:>5d}" for b in batches)
return f"{tag} work:[{counts}] batch:[{bsz}]"

print(f"[STATUS] done {done}/12 | total whacks {total_whacks} | rate ~ {rate:.1f}/s")
print(" " + row("M0", work0, done0, b0))
print(" " + row("M1", work1, done1, b1))

# -------------------- key assembly & cashbox --------------------
def assemble_key_bytes(val0, val1):
"""
Pack 12x21-bit diagonals into the low 252 bits, LSB-first:
pieces = [static[0] diag0..5, static[1] diag0..5]
"""
pieces = list(val0) + list(val1)
key_int = 0
for i, piece in enumerate(pieces):
key_int |= (piece & ((1 << 21) - 1)) << (21 * i)
return key_int.to_bytes(32, "big")

def open_cashbox(hexkey):
s = connect()
try:
s.sendall(b"o\n")
recv_until(s, [ASK_OPEN], timeout=TIMEOUT)
s.sendall((hexkey + "\n").encode())
txt = recv_until(s, [RETRIEVE, PROMPT_MENU], timeout=TIMEOUT)
m = RETRIEVE.search(txt)
if not m:
return None
return int(m.group(1))
finally:
try:
s.close()
except Exception:
pass

def open_cashbox_with_retry(hexkey, retries=RETRY_N, delay=RETRY_D):
for attempt in range(1, retries + 1):
cash = open_cashbox(hexkey)
if cash is not None and cash >= 0:
print(f"[+] Cashbox success on attempt {attempt}")
return cash
print(f"[-] Attempt {attempt} failed, retrying in {delay:.1f}s...")
time.sleep(delay)
return None

def int_to_flag(n):
b = n.to_bytes((n.bit_length() + 7)//8 or 1, "big")
try:
return b.decode()
except Exception:
return "BHFlagY{" + b.hex() + "}"

# -------------------- main --------------------
def main():
print(f"[*] Target: {HOST}:{PORT} | start_batch={START_BATCH} max_batch={MAX_BATCH} timeout={TIMEOUT}")
print("[*] Spawning 12 stream-safe burst workers (one per diagonal)…")

def on_sigint(_a, _b):
save_ckpt(STATE)
print("\n[!] Interrupted — checkpoint saved. Re-run to resume.")
os._exit(1)
signal.signal(signal.SIGINT, on_sigint)

q = queue.Queue()
threads = []
for (m, d) in [(0, i) for i in range(DIM)] + [(1, i) for i in range(DIM)]:
t = threading.Thread(target=whack_diag_worker, args=(m, d, q), daemon=True)
threads.append(t); t.start()

stat = threading.Thread(target=status_printer, daemon=True)
stat.start()

for t in threads:
t.join()
stop_status.set()
stat.join(timeout=1.0)

with ckpt_lock:
done_all = all(STATE["done0"]) and all(STATE["done1"])
val0 = STATE["val0"][:]
val1 = STATE["val1"][:]

if not done_all:
print("[!] Not all diagonals finished. Re-run this script to resume or add --redo to recompute.")
return

key_bytes = assemble_key_bytes(val0, val1)
hexkey = key_bytes.hex()
print("[*] Reconstructed key:", hexkey)

cash = open_cashbox_with_retry(hexkey)
if cash is None:
print("[!] Key rejected repeatedly. If you computed earlier with a non stream-safe parser, re-run with --redo.")
return

print(f"[*] Cashbox integer: {cash}")
print("[*] FLAG:", int_to_flag(cash))

if __name__ == "__main__":
main()
```

---

*Originally published on [Medium](https://theeomega.medium.com/breaking-blackhat-2025-crypto-challenges-with-gpt-a-complete-ctf-writeup-f65106193fd2). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
