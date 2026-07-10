# :globe_with_meridians: When Open Source Isn’t: How OpenRewrite Lost Its Way

---

# When Open Source Isn’t: How OpenRewrite Lost Its Way

## Moderne quietly relicensed community-contributed OpenRewrite code from Apache 2.0 to a proprietary license, abandoning its open source commitments. This decision risks legal exposure, undermines community trust, and sets a dangerous precedent for OSS stewardship.

On December 26th 2024, I opened GitHub and discovered that openrewrite/rewrite-java-security — a repository I had spent the better part of two years building recipes for — had been moved, made closed source, relicensed, and made proprietary by [Moderne, Inc](https://www.moderne.ai/). The code I authored, the recipes I wrote, and the security work that had been funded by open source security initiatives was now locked behind the [Moderne Proprietary License (MPL)](https://docs.moderne.io/licensing/overview/). No heads-up. No contributor outreach. No blog post.

Just a new license.

## A Quick Recap

OpenRewrite is a code refactoring framework that enables large-scale, automated changes to Java (and other JVM) codebases. At its best, it offers a vision of what developer tooling could be: scalable, modular, and language-aware. It was originally developed by Moderne CEO Jonathan Schneider while at Netflix as an almost entirely Apache 2.0 licensed codebase, until recently.

I was one of the earliest and most active contributors to the rewrite-java-security project. My work on it began in 2022 under the [Dan Kaminsky Fellowship](https://www.darkreading.com/cyber-risk/spotlight-on-first-dan-kaminsky-fellow-jonathan-leitschuh) at HUMAN Security, and continued in 2023 through a position with the [Linux Foundation’s OpenSSF Project Alpha-Omega](https://alpha-omega.dev/), funded by Microsoft, Google, and Amazon. I led a small team of interns to author OpenRewrite recipes that automatically fixed common security issues in vulnerable codebases. I used these recipes to generate hundreds of OSS pull requests to fix security vulnerabilities at-scale; then subsequently spoke publicly about this work on [stages like Black Hat and DEFCON](https://github.com/JLLeitschuh#user-content-scaling-the-security-researcher-to-eliminate-oss-vulnerabilities-once-and-for-all).

*I’m the primary author of the “Zip Slip Vulnerability” Recipe featured predominantly on the Moderne site*

Combined, these efforts represented many thousands of hours of community investment into a resource intended to benefit the entire open source ecosystem.

Then Moderne changed the license.

## The License Lockdown

In December 2024, Moderne moved rewrite-java-security under the Moderne Proprietary License (MPL). This license is not open source, not OSI-approved, and requires a signed commercial contract with Moderne to use or access the code going forward.

This means:

- Any improvements or changes Moderne makes to the code I originally wrote are no longer publicly available.

- I am no longer able to make changes, improvements, or even contribute bug fixes to that code.

Despite being one of the primary maintainers of the project, my ability to contribute to it has been fully revoked.

This licensing shift didn’t just impact rewrite-java-security. It affected a wide swath of the OpenRewrite ecosystem. Moderne applied its new licensing approach across many repositories and modules, including some with longstanding community involvement.

Here’s how the license breakdown now looks across various OpenRewrite modules: [Full list available here](https://docs.openrewrite.org/reference/latest-versions-of-every-openrewrite-module).

This happened without a blog post, and without an announcement to the community. It was done silently during, for most projects, a minor version bump.

When I raised these concerns in the OpenRewrite community Slack channel, I was hoping for a good-faith discussion about community impact. Instead, I was privately criticized and dismissed as being self-centered for speaking up. That kind of response made it clear that this was not a collaborative decision — it was a unilateral one.

## “Committed to the Principles of Pure Open Source”

In April 2024, Moderne announced that OpenRewrite was joining the [Commonhaus Foundation](https://www.commonhaus.org/), a nonprofit supporting open-source sustainability:

“Moderne is committed to the principles of pure open source… Commonhaus supports our commitment to keep OpenRewrite community-driven and accessible, ensuring its utility and relevance for years to come.”

*LinkedIn post announcing OpenRewrite is joining the Commonhaus Foundation*

This press release has since been deleted.

On December 9th, Moderne [formally withdrew OpenRewrite from the foundation](https://github.com/commonhaus/foundation/pull/218). The reasoning included concerns over:

- Trademark policy constraints that would limit Moderne’s creative use of the OpenRewrite brand

- A majoritarian voting structure that could, they felt, pose future risks to Moderne’s commercial interests

Despite expressing support for Commonhaus’s goals, Moderne concluded that its vision for OpenRewrite couldn’t coexist with the foundation’s governance model.

The irony here is hard to ignore. A company that professed commitment to community-led governance and “pure open source” walked back that commitment in both practice and policy — first by withdrawing from a nonprofit governance body, then by relicensing community-contributed code as proprietary.

## “Protecting Ourselves From AWS”

When asked why they made this change, Moderne leadership cited concerns about companies like Amazon and VMware using OpenRewrite recipes without contributing back.

That might be a fair frustration. But here’s the hypocrisy:

- Amazon didn’t strip your name from your code.

- VMware didn’t relicense your work without your consent.

At Moderne’s CodeRemix Summit 2025, several employees explained that this fear crystallized in late 2024 when several prospective customers reportedly said they didn’t see value in paying for Moderne. Why? Because they believed that solutions like Amazon Q Code Transformer, Sourcegraph Batch Changes, or Broadcom Application Advisor would suffice.

## Get Jonathan Leitschuh’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

In other words, Moderne had built a powerful open source tool — OpenRewrite — and now found itself competing with its own creation. Worse, they felt they were competing against tech giants using their own tooling without contributing anything back.

Originally, Moderne leadership viewed the company’s core value in its SaaS infrastructure, not the recipes. The OpenRewrite project — and its growing recipe library — was meant to be the open source foundation, while Moderne’s differentiator would be in the serialization and storage of large-scale abstract syntax trees (LSTs). But when third-party platforms demonstrated they could run OpenRewrite recipes at scale without Moderne, that became an existential threat to the company.

The fear was real. But the response — locking down code contributed by others — was deeply flawed and has left myself and other members of the community feeling hurt.

## This Isn’t Just About Me

Moderne CEO Jonathan Schneider stated:

>

“We looked through every repo, and those repos that either Moderne only contributed to or for which there were only ‘contributions like this’, we felt comfortable making the change… rewrite-java-security was the only really oddball one that needed to have some of its stuff archived and some of its stuff moved.”

However, this statement does not align with observed contributions. There are [multiple examples](https://github.com/openrewrite/rewrite-testing-frameworks/pull/520) of non-trivial community contributions that have been swept into Moderne’s proprietary or source available license, including from major enterprise contributors:

These are clear counterexamples that demonstrate community-written recipes — contributed under Apache 2.0 — have now been relicensed without consent.

Other contributors have raised similar concerns. Some have seen their Apache-licensed recipes swept under restrictive terms. Others have flagged that attribution and SPDX headers were removed. All of this breaks the unspoken contract that powers open source: *contribute in good faith, and your contributions will be respected and remain open.*

All of this left many of us asking if this license change was even legal.

That’s not just a rhetorical question. Under the Apache 2.0 license, relicensing code without permission from each contributor — unless governed by a Contributor License Agreement (CLA) — is a legally murky move. While companies like MongoDB and Elastic have made similar license transitions, those shifts sparked community forks and ongoing debate about their legality. Moderne’s decision follows this controversial pattern, but does so without the scale, communication, or governance that often accompany such major transitions. That raises real questions for downstream adopters and contributors alike.

Worse still, this sets a dangerous precedent:

>

Any company investing in the OpenRewrite ecosystem today risks having their employee-contributed recipes pulled into a proprietary licensing regime tomorrow.

This mirrors broader industry trends — like the relicensing decisions made by MongoDB and HashiCorp — where companies facing commercial pressure restrict the freedoms of the very communities that helped them grow.

We can acknowledge that “open source is free, as in free puppy.” Maintaining large-scale projects like OpenRewrite is not free, and Moderne — like any steward of OSS infrastructure — needs a viable business model. But that doesn’t make what they did right.

After crunching some data, I found that across OpenRewrite non-composite recipes, there are 2,635 unique recipe contributor pairs. Of those, ~350 are from email addresses that do not end in @moderne.io nor are identifiable personal emails of Moderne employees. At least some of these are [real, non-trivial community contributions](https://docs.google.com/spreadsheets/d/10KI2EfV4T4bdEvjMcBM1Ns1w_fgC4ydSBVEASlRZegA/edit?gid=1613606561#gid=1613606561).

We can disagree about business models. We can even disagree about licenses. But we shouldn’t just retroactively rewrite history to consolidate ownership over public, community-authored code.

## Moderne’s Corrections and Course Adjustments

In the weeks following community pushback, Moderne took steps to correct some of the most immediate concerns:

- Apache-licensed repositories were restored and archived, preserving prior community contributions in a public, accessible form, including [rewrite-java-security](https://github.com/openrewrite/rewrite-java-security).

- Major version bumps were introduced to properly signal the license changes in affected projects.

- Split namespaces (e.g., org.openrewrite vs. io.moderne) were introduced to distinguish between fully open and source-available/proprietary modules.

These changes demonstrate that some of the feedback was heard and acted upon. However, the fact remains: these were not proactive measures discussed openly with the community — they were reactive corrections to a course that was set in motion without our input.

## A Path Forward

What Moderne should do:

- Revert the license changes on all community-authored recipes. Let what was given freely by the community remain free and open for the community.

- Commit to community discourse: Changes like this should not be a surprise, and if they need to be, then they should be communicated publicly instead of silently.

- Respect versioning: Moving forward, license changes should be major semver bumps, not slipped into a v2.17.0 update.

What I’m doing:

Despite all of this, I’m still passionate about automated security remediation at scale, especially for OSS projects. I plan to continue leveraging OpenRewrite as a powerful tool to perform security research and fix vulnerabilities at-scale across OSS. If you want to explore how your organization can use OpenRewrite effectively, feel free to get in touch or[book some time with me](https://calendly.com/jonathan-leitschuh).

## Final Thoughts

Open source doesn’t work without trust. And trust is easy to lose. It only takes a quiet relicense, a removed attribution, and a private dismissal when you raise concerns in good faith. I came to the community expecting collaboration, only to be told I was being self-centered for asking questions about code I helped write.

This wasn’t just a licensing update. It was a violation of the norms, values, and expectations that hold open source communities together.

But it doesn’t have to be this way. We can build ecosystems that value contribution, respect consent, and center community over control.

OpenRewrite showed what’s possible when open source and security come together to empower developers at scale. The ideas behind it still matter. The need still exists. And I still want to help build that future — one that’s grounded in shared ownership, transparency, and trust.

*Correction: An earlier version of this article incorrectly stated ~600 contributions were from non-moderne employees, this has been updated to be ~350 after some feedback from Moderne.*

---
