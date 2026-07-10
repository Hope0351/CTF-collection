# :locked_with_key: How these Crypto Hackers earned a $5000 Bug Bounty

---

# How these Crypto Hackers earned a $5000 Bug Bounty

## Moral of the story — test concurrent requests

## What is a Race Condition?

A [race condition](https://en.wikipedia.org/wiki/Race_condition) occurs when two threads or processes are trying to access the same resource at the same time. Exactly what happens can depend on the the machine, the CPU, the compiler, etc., and the behavior is not always deterministic. Essentially, it all depends on the timing of [context switches](https://en.wikipedia.org/wiki/Context_switch) as the order of operations changes. For example, if a user starts with a balance of $500, and then thread `A` handles a deposit of $1000 and thread `B` handles a withdraw $500, we should expect a total of $1000. However, if the order of operations is such that `A` and `B` both read that there is $500, `A` updates `500 + 1000` , then B updates `500 — 500` , the user is left with $0! Conversely, you could expect the user to be left with $1500 if `A` went second!

Now, here is a real-life example of a race condition two hackers, users @cyberboy and @z0mb13, found that led them to a $5000 bounty.

*AI-generated image “bitcoin thief illustration” by craiyon.com*

## The Exploit

The original, full disclosed report can be found [here at HackerOne](https://hackerone.com/reports/1438052). The bug was found on a platform called [Starpor](https://blog.cosmos.network/learn-to-build-your-own-blockchain-with-the-starport-community-call-50fc32df92e7)t. *Note: the *[Github repo can be found here](https://github.com/ignite/cli/tree/7812125a7e96f4b0cb1da62766c6e96e56fc4f5b). Starport is the “easiest way to build a blockchain*,”* and is built on the [Cosmos SDK](https://cosmos.network/)…

---
