# :globe_with_meridians: Claude Code Leak Explained: How Claude Code Works, Why It Matters, and What Developers Can Learn

> **Original Source:** [Claude Code Leak Explained: How Claude Code Works, Why It Matters, and What Developers Can Learn](https://infosecwriteups.com/the-accidental-open-source-what-claude-codes-leaked-source-code-tells-us-about-the-future-of-ai-c5706b0b41d0)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

# The Accidental Open Source: What Claude Code’s Leaked Source Code Tells Us About the Future of AI Agents


A 59.8 MB debugging artifact accidentally shipped to npm just handed the AI developer community the most detailed blueprint of a production-grade agentic coding system ever made public.


On March 31, 2026, security researcher Chaofan Shou noticed something unusual inside version 2.1.88 of the `@anthropic-ai/claude-code` npm package. Tucked inside was a JavaScript source map, a developer debugging file that maps minified production code back to its original, readable source. Shipping one publicly is roughly like publishing your internal blueprints on the cover of your product box. The map pointed to a ZIP archive sitting on Anthropic's own Cloudflare R2 storage bucket. Nobody had to hack anything. The front door was open.


The ZIP contained 2,300 source files and nearly half a million lines of TypeScript. Within 24 hours, the leak had 22 million views on X. By the end of the day, someone had already converted the entire codebase to Python, making it effectively impossible to enforce copyright through DMCA takedowns. The community had what it came for.


Now, as someone who has spent years building event-driven, AI-first enterprise platforms, my reaction was not “how embarrassing for Anthropic.” It was: “finally, let’s see how this thing actually works.”

## The Gap Between “AI Tool” and “AI Agent”


Before getting into what the code reveals, it helps to understand what makes Claude Code different from a typical AI coding assistant.


Most tools work like a very smart autocomplete. You type, they suggest. Claude Code operates differently. It is an agentic harness: a system that wraps a large language model with tools, memory management, permissions, and orchestration logic, then lets it act autonomously across your entire codebase.

>

Claude Code serves as the agentic harness around Claude: it provides the tools, context management, and execution environment that turn a language model into a capable coding agent. — Anthropic, Claude Code Documentation (docs.claude.com)


Think of it this way. A regular AI coding tool is like a very smart consultant who answers your questions. Claude Code is like giving that consultant a laptop, access to your whole codebase, a terminal, the ability to run tests, and asking them to fix the bug while you sleep. The difference is not just convenience; it is a fundamentally different class of software.


This is why the leak matters. We now have a detailed, unobscured look at the engineering decisions behind one of the best examples of production agentic AI in the world.

## The Engine Room: What Half a Million Lines Actually Contain


The biggest single module is `QueryEngine.ts` at approximately 46,000 lines. This handles everything that touches the Anthropic API: prompt construction, streaming response handling, token counting, cost tracking, and the retry logic that keeps long-running agent sessions stable.

>

The feature flag list embedded in this module is itself a product roadmap, including prompt-caching-scope-2026–01–05, token-efficient-tools-2026–03–28, and task-budgets-2026–03–13. — Verdent AI, “Claude Code Source Code Leaked: What the Architecture Reveals” (verdent.ai)


The permission and tool architecture is equally revealing. Every tool carries explicit permission requirements baked into the tool layer itself, separate from the LLM. The model decides what to attempt; the tool system decides what is permitted.

>

That separation matters: the model decides what to attempt, but the tool system decides what is permitted. — Verdent AI, “Claude Code Source Code Leaked: What the Architecture Reveals” (verdent.ai)


This is not an afterthought. It is deliberate security architecture. And it is exactly the kind of design decision that separates a production system from a demo.

## Five Lessons Every AI Builder Should Take Away


### 1. Your CLAUDE.md File is Doing Almost No Work (And It Should Be)


Claude Code loads a file called `CLAUDE.md` into every single conversation turn, every one, without exception. This file is your 40,000-character instruction set: the coding standards your team follows, the architectural patterns you care about, the files Claude should prioritize.


Most people barely touch it. That is leaving enormous capability on the table. Think of it as the onboarding document you would give a senior engineer on day one. Every team convention, every naming pattern, every “we do not do X here” decision belongs in that file.

### 2. Single-Agent Thinking is the Wrong Mental Model


The leaked code documents three distinct execution models for sub-agents: “fork” (inherits parent context, cache-optimized), “teammate” (separate pane in Tmux or iTerm, communicates via file-based mailbox), and “worktree” (its own isolated git branch per agent).


## Get Faisal Feroz’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Running a single agent sequentially is not how Claude Code is designed to be used. It is designed for parallelism, where multiple agents share prompt caches, meaning you get near-parallel execution without paying for independent context windows on each sub-agent.

>

A multi-agent system with Claude Opus 4 as the lead agent and Claude Sonnet 4 subagents outperformed single-agent Claude Opus 4 by 90.2% on our internal research eval. — Anthropic Engineering, “How we built our multi-agent research system” (anthropic.com/engineering)


The math is hard to ignore. The orchestration model that emerges from the source is a lead-agent-plus-subagents pattern, where a primary Claude instance coordinates the session and spawns isolated sub-agents for parallel or context-isolated work.

### 3. Context Management is Architecture, Not a Settings Knob


The code reveals five mechanisms for managing what the model remembers and, crucially, what it forgets. There is micro-compact (time-based clearing of old tool results), context collapse (summarizing spans of conversation), session memory (extracting key context to a file), full compact (summarizing entire history), and PTL truncation (dropping the oldest message groups).


There is a useful principle buried in here. Knowing what to forget matters as much as knowing what to remember. An agent carrying stale, irrelevant context in a 200,000-token window will underperform an agent with a tight, well-managed 50,000-token context. Use `/compact` proactively instead of letting the system autocompact and discard context you actually care about.


Large tool results get stored to disk, with only an 8-kilobyte preview sent to the model. If you paste a massive file expecting Claude to reason over all of it, the model may only see a fraction. Keep your inputs focused.

### 4. Permission Prompts are a Configuration Failure


Every time Claude Code asks “do you want to allow this?”, that is not Claude being cautious. According to the source code, it is a signal that you have not properly configured your permissions. The system is designed to have everything pre-approved.


The code documents three modes: bypass (no permission checks at all, fast but dangerous), allow-edits (auto-allows file edits in your working directory), and auto (runs an LLM classifier on each action to predict whether you would approve it). The auto mode is the intended default for experienced users, and the old “dangerously skip permissions” flag is effectively deprecated.

>

Newer users employed full auto-approve roughly 20% of the time; by 750 sessions, this increases to over 40% of sessions. — Anthropic Research, “Measuring AI Agent Autonomy in Practice” (anthropic.com/research)


Trust is earned through experience, and the system is designed to grow with you.

### 5. Sessions Are Stateful, So Stop Starting Fresh


Every Claude Code conversation is saved as a JSONL file. You can resume, fork, and continue sessions. A resumed session carries accumulated session memory: structured summaries of task specs, file lists, workflow state, errors, and learnings from prior work.


Starting a fresh session every time discards that institutional memory. If there is any continuity with previous work, resuming the existing session is almost always the better choice.

## What This Means for Competitors and the Open Source Ecosystem


The honest answer is: quite a lot.


Competitors now have direct access to the exact prompts, the agent setup patterns, the permission architecture, and the compaction strategies that make Claude Code work. For teams building their own coding agents or improving open-source alternatives, this is a significant acceleration.


What competitors cannot easily replicate is the co-evolution between the harness and the Claude model family. Claude Code was built for Claude. The prompting strategies, the context management, the tool definitions, all of it was designed in tandem with the model’s specific behaviors and strengths. Plugging a different model into the same harness will produce different, likely weaker, results.


What the open source community can extract are the engineering patterns: how to structure tool permissions, how to design context compaction, how to orchestrate parallel sub-agents, how to build hooks for pre- and post-tool-use automation. These ideas will disseminate quickly, and the broader agentic AI ecosystem will be stronger for it.

## A Sloppy Mistake, Not a Crisis


For Anthropic, the actual damage is limited. No customer data was exposed. No API keys were included. No model weights were leaked. What was exposed is the engineering sophistication of their agentic harness, which, if anything, demonstrates how seriously they take this problem.


It does look careless. A source map file should never reach a public npm package in a production release. That is a CI/CD gate that should exist and did not trigger. As someone who has navigated production incidents in complex distributed systems, I know how these things happen: a configuration change in a build step, an automated pipeline that nobody audited that week, and suddenly your debugging artifacts are public.


The more meaningful outcome is that the community now has a detailed, honest look at what a well-engineered agentic coding system actually requires. Not a blog post describing it. Not a conference talk gesturing at the architecture. The actual code.


That transparency, even if accidental, advances the field.

---

*Originally published on [Medium](https://infosecwriteups.com/the-accidental-open-source-what-claude-codes-leaked-source-code-tells-us-about-the-future-of-ai-c5706b0b41d0). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
