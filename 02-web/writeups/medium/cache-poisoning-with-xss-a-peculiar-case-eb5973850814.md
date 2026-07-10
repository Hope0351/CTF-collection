# :globe_with_meridians: Bug Hunting with Param Miner: Cache poisoning with XSS, a peculiar case

---

# Bug Hunting with Param Miner: Cache poisoning with XSS, a peculiar case

You have heard of the cache poisoning, a bug that had existed for far longer than most of people have been aware, as in many other cases of this nature, in my opinion. But, this article isn’t about a history lesson; however, there are a couple of lessons, maybe more, that you might find useful.

Param Miner with an Edge:

See what I did there? Never mind, it will make itself known soon enough.

Here’s the real world example. Of course I can’t disclose the bbp in question, but the details of the attack won’t make it necessary to do so.

I use Param Miner, an extension for burp pro (technically, it also works in burp community edition, but with a lot of limitations). And, aside from testing for hidden parameters, it also tests for cache poisoning, and then there’s burp pro with its scanner which tests for xss. Add them together and you can get yourself some nice bounties. But, it still requires some legwork.

Doesn’t your heart simply swell up by an increase in adrenaline production upon seeing this, or maybe it flutters, or it starts beating stronger. Either way, it means a good news. It did for me. Upon the initial (with hands shaking) review, it turned out that it wasn’t a false positive. Param miner had discovered a hidden…

---
