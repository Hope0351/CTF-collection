# :globe_with_meridians: Register Mapping: From Blind Scan to Process Understanding in GRFICSv3

---

# Register Mapping: From Blind Scan to Process Understanding in GRFICSv3

## Raw numbers, no labels and the question of what happens to the physical world if you change them

In IT security, you compromise a server and you get files with names. Documents. Emails. Credentials. The data tells you what it is.

In OT security, you compromise a PLC and you get three raw values from a live industrial controller no units, no names, no context. Just `5195`. `65535`. `28856`. Change the wrong one and a valve slams shut. Change the right one and a reactor runs at unsafe pressure for days before anyone notices.

That’s the hardest part of OT exploitation. Not getting in. Understanding what you’re looking at once you’re there.

In Part 13a, we built the GRFICSv3 lab, a virtualized chemical plant running a real Tennessee Eastman process simulation, with a live PLC, HMI, and engineering workstation on an isolated OT network. We confirmed everything was reachable. We knew *where* data lived. We did not know *what any of it meant*.

This post answers that question. We’ll enumerate every live register on the GRFICSv3 PLC, classify them by behavior, correlate raw values with the HMI’s engineering units, and test hands-on which registers are actually writable and which attack paths are viable. By the end you’ll have a complete, labeled register map and the technical foundation to plan a process-aware attack.

All scripts used in this post are in the [ot-security-lab-scripts](https://github.com/urjasec/ot-security-lab-scripts) repo under `part13d-register-mapping/`

## The 99% Before the Write

When people see a Modbus attack demo, the dramatic part is always the write. `client.write_register(40100, 9999)` and suddenly a pump stops or a valve opens. But that one line is the last 1% of the work.

The other 99% is answering a deceptively simple question: “What is register 40100?”

A holding register is sixteen bits. In the field, those bits could be any of the following:

- An integer temperature in tenths of a degree (`2453` = 245.3°C)

- A boolean packed into a word (`0x0001` = pump running)

- One half of a 32-bit float split across two registers (IEEE 754)

- A bitfield where each bit is an alarm flag

- An unused memory slot the engineer never cleared

In GRFICSv3 specifically, you’ll encounter only one encoding pattern: linear UINT16 scaling across the full 0–65535 range, with a known full-scale maximum per variable type. No floats, no bitfields. The challenge here isn’t data type ambiguity, it’s knowing what the full-scale range is for each variable, which Section 3 covers.

The PLC knows what each register means because the engineer who wrote the ladder logic knows. The HMI knows because someone typed the mapping into a tag database. An attacker on the network knows *none of this*. Figuring it out without the HMI project files, without the PLC source, without documentation is the real exploitation work.

Three techniques, in order of stealth:

- Read-only enumeration — poll every register, watch values over time. Values that change are process variables. Values that never change are setpoints or constants.

- HMI correlation — screenshot the HMI at time T, snapshot registers at time T, match numbers to labels. The HMI is a decoder ring the engineers installed for you.

- Active probing — change a value and watch what happens. This is no longer passive. This is the write.

We’ll do all three, but in that order.

## Enumerating the Register Space

If you need a refresher on FC1–FC4 and how Modbus address tables work, Part 4 covers it. The GRFICSv3-specific detail worth knowing here: OpenPLC’s Modbus address mapping is *not* a flat offset. Three different IEC 61131–3 variable types map to different Modbus address ranges:

- `%QW` (output words) → Holding Registers at the declared address (`%QW100` → HR 100)

- `%MW` (memory words) → Holding Registers at 1024 + offset (`%MW0` → HR 1024)

- `%IW` (input words) → Input Registers at the declared address (`%IW108` → IR 108)

The difference matters for attackers: `%QW` are outputs the PLC recomputes every scan cycle, you can't hold them. `%MW` are internal memory the PLC trusts but doesn't recalculate, external writes stick. `%IW` are read-only sensor inputs.

### Step 1: Blind sweep with `wide_scan.py`

`wide_scan.py` opens a single raw TCP socket, sweeps all four function codes across 0–2000 addresses in blocks of 50, stops at the first illegal-address error, and prints only non-zero values, the whole sweep runs in under 5 seconds.

From the Kali container:

```
python3 wide_scan.py
```

Output from our lab (process running):

*Fig 1: Full address sweep across all four Modbus function codes with wide_scan.py script*

One scan. Thirteen non-zero registers across thousands of possible addresses. No labels, no context, just numbers. You can’t know what any of these mean yet, but you can form hypotheses worth testing:

- Coil 40 is ON — something is active. Possibly a run/stop bit, possibly an enable flag. Worth monitoring.

- Two clusters of holding registers — HR 100–103 and HR 1024–1028, separated by a 900-address gap. Why two clusters? Different variable types? Different modules? The gap is suspicious.

- HR 100 maxed at 65535 — something pegged at 100% of scale. HR 102 is missing (zero). HR 101 is near-zero (211) and HR 103 is mid-range (11522).

- HR 1024–1028 look like configuration — five tightly packed registers with stable-looking values (30000, 30801, 55295, 31675, 28835). Possibly setpoints or constants.

- Nine input registers (FC4, read-only) — sensor data. IR 100/101 and IR 104/105 are missing (zero-valued valves, as we’ll confirm later).

- Consecutive pairs — IR 102/103 and IR 106/107 might be valve-position + flow-rate pairs. Common distributed I/O pattern. IR 102 = 209 and IR 103 = 17 — one near-zero, one negligible. That pair’s valve is barely cracked open.

- IR 108 is high (54914) — 83.8% of full scale. If this is pressure, the reactor is running hot. Worth watching whether it’s climbing or stable.

- IR 110 + 111 + 112 — expressed as fractions of 65535, they sum to ~100% (47.0% + 14.4% + 38.6%). Possibly three components of a gas composition measurement.

These are starting hypotheses, not conclusions. Every one of them could be wrong and as we’ll see in the next section, some of them are.

### Step 2: Behavioral classification with `focused_poll.py`

A single snapshot tells you what exists. Polling over time tells you what *moves*. `focused_poll.py` reads the known ranges 10 times at 3-second intervals and classifies each register:

```
python3 focused_poll.py
```

Output from our lab (10 polls × 3 seconds):

*Fig: Behavioral classification over 10 polls using focused_poll.py script*

Two categories emerge:

- Static — COIL 40, HR 100, HR 1024–1028. Never change. Static holding registers in a running process usually mean setpoints or constants.

- Actively computed — HR 101 (1330→242) and HR 103 (17005→9373). The PLC recomputes these each scan cycle.

- Dynamic process variables — IR 102–111. Live sensor data. Pairs move together (IR 102/103, IR 106/107), likely valve + flow combinations. IR 108 drifts slowly (pressure). IR 109 is nearly stable (level). IR 110/111 drift (composition).

- Watch the traps — HR 103 and IR 106 fall at similar rates. You’d conclude one controls the other. Without the PLC source, you can’t tell whether that’s a command-response relationship or two independent loops responding to the same drift.

## Correlating Registers with the HMI

The register maps tells you which *values* are interesting. It doesn’t tell you which one is reactor pressure and which is feed flow. This section covers what works, what doesn’t and how real attackers bridge the gap.

### The scaling problem

GRFICSv3 uses the full UINT16 range (0–65535) for every process variable:

```
engineering_value = (raw_register / 65535) × full_scale_max
```

In GRFICSv3, these ranges are documented in the Tennessee Eastman process benchmark, publicly available. In a real engagement, you’d need to pull them from HMI tag databases, historian metadata, or P&ID documentation.

## Get urjasec’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Full-scale ranges for the Tennessee Eastman simulation:

Without knowing the full-scale range, the same raw value decodes to five different engineering values. You need external context.

### Method 1: Side-by-side snapshot

Open ScadaLTS in your browser and run `wide_scan.py` from Kali at the same moment with variation in few second. Screenshot both. Work backwards from the displayed engineering values:

---
