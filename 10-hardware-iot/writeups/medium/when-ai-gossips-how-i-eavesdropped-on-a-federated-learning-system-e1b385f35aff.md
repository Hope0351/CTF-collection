# :electric_plug: Medium

> **Original Source:** [Medium](https://infosecwriteups.com/when-ai-gossips-how-i-eavesdropped-on-a-federated-learning-system-e1b385f35aff)
> **Platform:** infosecwriteups.com | **Category:** `HARDWARE / IoT`

---

# When AI Gossips: How I Eavesdropped on a Federated Learning System


Free [Link](https://medium.com/@iski/when-ai-gossips-how-i-eavesdropped-on-a-federated-learning-system-e1b385f35aff?sk=eb5b2b261e9580186462fd524eade469)🎈


Hey there!😁


*Image by AI*


You know that feeling when you’re at a party, and you can piece together everyone’s drama just by listening to random conversation fragments? 🍷 That’s basically what I did to a multi-million dollar AI system last month.


I was surviving on cold pizza and lukewarm coffee, scrolling through a new target’s documentation. “Privacy-First AI!” it screamed. “Your data never leaves your device!” 🤔 Yeah, right. I’d heard that one before.


My target was “SynapSafe,” a company using Federated Learning to train medical AI models across hospitals. The sales pitch was beautiful: hospitals keep their patient data, and only tiny “model updates” get sent to the central server. No data leakage! Totally secure!


Spoiler alert: It wasn’t. Here’s how I turned their privacy-preserving AI into a data-sniffing bloodhound. 🐕

## Phase 1: The Recon — Finding the Secret Meeting Room


Most hunters look for `api/v1/login`. I look for the digital equivalent of the executive washroom. For a federated learning system, that means finding where the model updates are gathered and processed.

---

*Originally published on [Medium](https://infosecwriteups.com/when-ai-gossips-how-i-eavesdropped-on-a-federated-learning-system-e1b385f35aff). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of hardware / iot CTF writeups.*
