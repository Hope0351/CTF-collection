# :game_die: Medium

---

# 💰 Anatomy of a Cloud Native Attack: How We Pwned Kubernetes for $100k

>

**TL;DR: The Ultimate Cloud Hack Chain**

🕵️ We found a simple Server-Side Request Forgery (SSRF) vulnerability in an unassuming microservice.

🔑 We used the SSRF to pivot and steal cloud metadata credentials from the underlying EC2 instance.

🤖 With node credentials, we abused the Kubelet API to deploy a rogue, privileged pod onto the cluster.

👑 From our privileged pod, we stole a high-powered Service Account token, giving us full `cluster-admin` rights.

💰 We responsibly disclosed the full chain for a $100,000 bug bounty payout. This is how it all went down. 👇

Ever wondered how a tiny, seemingly harmless bug can unravel an entire cloud infrastructure? You’re in the right place. This isn’t just theory; this is a real-world story of how we turned a single vulnerability into complete control over a massive Kubernetes cluster.

Strap in, because we’re about to dive deep into a kill chain that netted us a six-figure payout. It’s a story of misconfigurations, chained exploits, and the beautiful, terrifying complexity of modern cloud native environments.

This is the stuff they don’t teach you in certifications. This is real-world hacking. Let’s begin. 🚀

## 🔥 The Spark: A Tiny Flaw with a HUGE Blast Radius

---
