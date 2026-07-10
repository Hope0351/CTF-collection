# Cloud Security

> Part of **CTF-collection** — see [master README](../README.md) for context.

## 📖 Overview

Misconfiguration exploitation, IAM privilege escalation, container escapes, Kubernetes attacks, and S3-bucket enumeration across AWS, Azure, and GCP. An emerging category that has grown rapidly since 2022.

This category contains **11 curated sources** from across the CTF ecosystem: 10 internal archives, 1 Medium article, 0 YouTube video walkthroughs, 0 CTFtime event entries, and 0 blog posts.

## ✍️ Curated Articles & Walkthroughs

Beyond internal archives, the following articles, videos, and blog posts from Medium, YouTube, and personal blogs provide additional depth on this category.

| # | Title | Source | Year | Summary |
|---:|---|---|---|---|
| 1 | [DEF CON 29 Cloud Village CTF Writeups | by Muhammad Yuga N.](https://myugan.medium.com/def-con-29-cloud-village-ctf-writeups-4ebd2e2cd9c) | ✍️ Medium | n/a | The CTF begins at 02.15 AM (Indonesia Time), we've started our first day by exploring some challenges by understanding … |

## 🔬 Sub-Topic Deep Dive

The Cloud Security category decomposes into the following sub-topics. For each, we list the foundational concepts you should master and the kinds of challenges you'll encounter.

### AWS misconfiguration

S3 bucket enumeration, IAM privilege escalation, Lambda abuse.

*No directly-matching resources in this collection — consult the broader category list above.*

### Azure misconfiguration

Entra ID abuses, Managed Identity escalation.

*No directly-matching resources in this collection — consult the broader category list above.*

### GCP misconfiguration

IAM, GCS, Compute Engine metadata.

*No directly-matching resources in this collection — consult the broader category list above.*

### Kubernetes attacks

RBAC abuses, container escapes, etcd access.

*No directly-matching resources in this collection — consult the broader category list above.*

### Container escapes

privileged containers, capabilities, cgroup escapes.

*No directly-matching resources in this collection — consult the broader category list above.*

### Suggested Learning Order

Cloud security CTFs are a growing category. The resources in this collection are limited, so supplement with these external starting points:

1. **Start with cloud provider documentation** — AWS Security Best Practices, GCP Security Command Center, and Azure Security Center guides provide the foundational knowledge.
2. **Practice on CloudGoat** (AWS) and **Thimble** (GCP) — both are deliberately vulnerable cloud environments designed for learning.
3. **Study IAM misconfiguration patterns** — these are the most common cloud CTF challenge type.
4. **Review the awesome-cloud-sec and awesome-aws-security** GitHub lists for additional resources beyond this collection.

## 🔗 See Also

- [`00-start-here/`](../00-start-here/README.md) — onboarding track if you're new.
- [`20-events/`](../20-events/README.md) — find writeups by specific CTF event.
- [`30-archetypes/`](../30-archetypes/README.md) — browse by repository type.
- [`40-tooling/`](../40-tooling/README.md) — curated tool references.
- [`99-appendix/full-repo-index.md`](../99-appendix/full-repo-index.md) — the complete corpus.
