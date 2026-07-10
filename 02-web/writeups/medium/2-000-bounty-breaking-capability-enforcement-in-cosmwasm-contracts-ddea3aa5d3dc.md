# :globe_with_meridians: 2 000 Bounty Breaking Capability Enforcement In Cosmwasm Contracts Ddea3Aa5D3Dc

> **Original Source:** [2 000 Bounty Breaking Capability Enforcement In Cosmwasm Contracts Ddea3Aa5D3Dc](https://infosecwriteups.com/2-000-bounty-breaking-capability-enforcement-in-cosmwasm-contracts-ddea3aa5d3dc)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## Step-by-Step: How to Exploit the Bug


## Step 1: Find a Chain With Restricted Capabilities


Pick a Cosmos chain that disallows certain contract actions — e.g., staking or bank module access.


## Get Monika sharma’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Some chains expose these capabilities to users via native messages (non-Wasm), but block Wasm contracts from doing the same.

## Step 2: Modify the CosmWasm Compiler


In the CosmWasm build system, capabilities are embedded during compilation as metadata strings like:


```
json
CopyEdit
"requires_staking": true,
"requires_ibc": false
```


The attacker simply removes the logic that inserts these strings during compilation.

>

*Think of it like removing the “I need access” tag before walking into a restricted room.*


## Step 3: Deploy the Contract


With no `requires_*` string present, the chain checks nothing and allows upload.

## Step 4: Execute Restricted Actions


Now, even if the chain disallowed certain capabilities, the attacker can invoke them directly via CosmWasm messages:


```
json
CopyEdit
{
"stake_tokens": {
"amount": "1000"
}
}
```


As there’s no runtime guard in place, the action executes successfully, violating the expected security model.

---

*Originally published on [Medium](https://infosecwriteups.com/2-000-bounty-breaking-capability-enforcement-in-cosmwasm-contracts-ddea3aa5d3dc). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
