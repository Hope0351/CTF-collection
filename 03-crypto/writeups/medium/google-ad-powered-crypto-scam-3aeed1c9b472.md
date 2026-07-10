# :locked_with_key: Google Ad powered Crypto Scam. I am Harish SG, a security researcher…

> **Original Source:** [Google Ad powered Crypto Scam. I am Harish SG, a security researcher…](https://infosecwriteups.com/google-ad-powered-crypto-scam-3aeed1c9b472)
> **Platform:** infosecwriteups.com | **Category:** `CRYPTO`

---

# Google Ad powered Crypto Scam


I am Harish SG, a security researcher who studies Masters in Cybersecurity at UT Dallas and AI security intern at Cisco,previously hunted on the Microsoft Bug Bounty Program and Google VRP


I am sharing this article for security awareness and educational purposes only and I am sharing only personal opinions and none of these are related to my work at Cisco. I am not responsible if someone abuses information in this post


In this article I am gonna deep dive into Crypto Scam which abuses deep fake and legitimate services such as google ads to trick people to fall for it


Lets deep dive into!


Once I got above advertisment in youtube , I pressed to 3 dots to check whether it is verified or not


So by looking at above image I got confirmed advertiser is not verfied yet so I was skeptical about that video so I clicked the video and I also I am almost sure this is a scam. So I decided to investigate and figure out modus operandi of attacker


from above image we can see video is unlisted. Also more than 90k people have watched this video and channel has 2.19k subscribers.


What is mean by MeV bot?


MeV bots, which stand for Maximal Extractable Value bots, are a type of software tool used primarily in the cryptocurrency and decentralized finance (DeFi) sectors, particularly on the Ethereum blockchain. These bots are designed to monitor transaction pools (or mempools) for pending transactions and identify profitable opportunities, which they then act upon.


The concept of MEV arises from the ability of miners or validators on a blockchain network to extract additional profits by strategically ordering or managing transactions within a block. This is possible because transactions first appear in a public mempool before being selected and ordered by miners or validators for block inclusion. Transactions with higher gas fees are usually prioritized, and this gives miners and validators a unique opportunity to extract additional profits through strategic transaction ordering.


Solidity Code Analysis


So lets deep dive solidity code provided by attacker. Also I think code is an output of the exploit kit. Since I found more three different instances where attacker used same kind of code.


I asked chatgpt about its opinion on this smart contract code. It also says code lacks trading logic also it uses external call to transfer to funds to address determined by mempool on withdraw actually it should transfer funds to owner wallet address on withdrawal if its legitimate. Also Attacker used some of string ofuscation using string catenation as well as replace string on condition mechanism to hide his hard coded address


Analysis on core function which generate attacker ethereum address based on hardcoded numbers


`callMempool`Function: This function constructs a string by concatenating various values through multiple calls to the `mempool` function.


- It takes several hardcoded numerical values, converts them to strings with some kind of liquidity check (`checkLiquidity` function), and then concatenates these strings in a specific order.

- The final string is a combination of all these concatenated values, prefixed with “0”.


`mempool`Function:


- This is a helper function used to concatenate two string values.

- It takes two strings, converts them into bytes, and then merges them into a single string


`checkLiquidity`Function:


## Get Harish SG’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Although not provided in your snippet, this function seems to convert a uint into a string. It’s likely used to process the hardcoded uint values (`_memPoolSol`, `_memPoolLength`, etc.) into strings that can be concatenated.


`parseMemoryPool`Function:


This function appears to convert a hexadecimal string into an Ethereum address.It processes each character pair of the string, converting it from hexadecimal to a uint, and then combines these to form a 160-bit Ethereum address.


Code Samples.


Code Samples 1 : [https://pastebin.com/raw/RcXWmfh4](https://pastebin.com/raw/RcXWmfh4) ( I found this exploit initially on Jan 7)


Code Sample 2 : [https://pastebin.com/raw/QEWCeWyt](https://pastebin.com/raw/QEWCeWyt) ( I found this exploit initially on Jan 26)


Code diff analysis


So we can confirm that both script belongs to same attacker!


Transcation analysis


Lets analyse the crypto transcations on this address using a tool called breadcrumbs.app


attacker address: 0xD0652E3e871CFb261cC0eA4A4F4bfC3CeBD39a95


From the above image! we can see that attacker withdrew the proceed using well known exchange called coinbase and they used exchange called simpleswap where they converted ETH into some other altcoin.


Recent Transcations on the address and analysis using arkam intelligence


After this analysis! I tried to figure whether photo of person in video is real or not then I used a website called facecheck.id. Then I figured out attackers are impersonating an journalist called Thodoris Chondrogiannos


reference : [https://ipi.media/greece-journalists-targeted-in-several-slapp-lawsuits/](https://ipi.media/greece-journalists-targeted-in-several-slapp-lawsuits/)


Attackers are now a days using Youtube Videos for scamming people who wanted to make money desperately using crypto currency


Purpose of the research :


Purpose of this Analysis is bring awareness on kind of crypto scam


*Try hacking LLM : *[https://github.com/harishsg993010/DamnVulnerableLLMProject](https://github.com/harishsg993010/DamnVulnerableLLMProject)


*Hacking into Bard* : https://infosecwriteups.com/hacking-google-bard-24f9dfa7b455


*Hacking into Facial Recognition system *: [https://medium.com/bugbountywriteup/hacking-into-facial-recognition-system-using-generative-ai-69a741077f0e](https://medium.com/bugbountywriteup/hacking-into-facial-recognition-system-using-generative-ai-69a741077f0e)


*Follow me on twitter: *[https://twitter.com/CoderHarish](https://twitter.com/CoderHarish)


*Follow me on linkedin* :[https://www.linkedin.com/in/harish-santhanalakshmi-ganesan-31ba96171/](https://www.linkedin.com/in/harish-santhanalakshmi-ganesan-31ba96171/)

---

*Originally published on [Medium](https://infosecwriteups.com/google-ad-powered-crypto-scam-3aeed1c9b472). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
