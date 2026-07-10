# :globe_with_meridians: I Read The Claude Code Source Analysis So You Dont Have To 0A8Af82956F4

> **Original Source:** [I Read The Claude Code Source Analysis So You Dont Have To 0A8Af82956F4](https://infosecwriteups.com/i-read-the-claude-code-source-analysis-so-you-dont-have-to-0a8af82956f4)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

## The Core Loop Is Embarrassingly Simple


Everyone building agents seems obsessed with planning architectures. State graphs. Tree search. Explicit reasoning scaffolds. Claude Code ignores all of that.


The core agent loop is a ‘while’ loop. That is it. The ‘queryLoop()’ function in ‘query.ts’ repeats a fixed sequence: assemble context, call the model, check if the response contains tool-use blocks, route approved tool requests to implementations, collect results, and loop again. If the response contains only text with no tool calls, the loop exits.


```
// Simplified representation of Claude Code's core loop
async function* queryLoop(params: QueryParams): AsyncGenerator<QueryEvent> {
let state = initializeState(params);
while (true) {
// 1. Assemble what the model sees
const messages = getMessagesAfterCompactBoundary(state);
// 2. Run five context shapers (budget, snip, microcompact,
// collapse, auto-compact)
const shaped = await runContextPipeline(messages, state);
// 3. Call the model
const response = await callModel(shaped, params.tools);
// 4. Check stop condition: no tool use means we are done
if (response.isTextOnly()) {
yield { type: 'complete', content: response.text };
break;
}
// 5. For each tool_use block, check permissions and execute
for (const toolCall of response.toolUseBlocks) {
const permitted = await checkPermission(toolCall, state);
if (!permitted) {
state.messages.push(deniedResult(toolCall));
continue;
}
const result = await executeTool(toolCall);
state.messages.push(toolResult(toolCall, result));
}
}
}
```


No planning phase.


No explicit state machine.


No backtracking or search.


The model decides what to do next; the harness decides whether to let it.


The paper frames this as a deliberate bet: increasingly capable models benefit more from a rich operational environment than from frameworks that constrain their choices. Anthropic’s own documentation describes Claude Code as “a Unix utility rather than a traditional product,” built from the “smallest building blocks that are useful, understandable, and extensible.”


This directly contrasts with LangGraph (explicit state graphs with typed edges), Devin (maintains planning and task tracking structures), and tree-search approaches like LATS that explore multiple action trajectories before committing.

## The Safety Architecture Is Deeper Than You Think


The simple loop is deceptive. Most of the complexity lives in what sits around it, and the permission system is where it gets genuinely interesting.


Claude Code implements seven independent safety layers. A tool request must pass through all applicable layers, and any single one can block execution:


1. Tool pre-filtering : Blanket-denied tools are removed from the model’s view entirely. The model never even knows they exist, so it cannot waste tokens trying to invoke them.


2. Deny-first rule evaluation : Deny rules always override allow rules, even when the allow rule is more specific. A broad “deny all shell commands” cannot be circumvented by a narrow “allow npm test.” This is the opposite of most ACL systems where more specific rules win.


3. Permission mode constraints : 7 modes span a trust gradient from ‘plan’ (approve everything) through ‘default’ and ‘acceptEdits’ to ‘bypassPermissions’ (minimal prompting).


4. Auto-mode ML classifier : An ML model evaluates tool safety in real-time, potentially denying requests the rule system would allow.


5. Shell sandboxing : Approved commands can still execute inside a sandbox restricting filesystem and network access. Authorization and isolation operate on completely separate axes.


6. Permission non-restoration : Session-scoped permissions are explicitly not restored on resume or fork. You start fresh every time.


7. Hook interception : ‘PreToolUse’ hooks can override permission decisions. External code gets a say before anything runs.


The design rationale is rooted in a specific empirical finding: Anthropic discovered that users approve 93% of permission prompts. In other words, interactive approval is behaviorally unreliable as a safety mechanism because humans rubber-stamp everything after the first few prompts.


```
// How deny-first rule evaluation actually works
function evaluatePermission(toolCall: ToolCall, rules: PermissionRule[]): Decision {
// Deny rules ALWAYS win, regardless of specificity
for (const rule of rules.filter(r => r.type === 'deny')) {
if (toolMatchesRule(toolCall, rule)) {
return { decision: 'deny', reason: rule.reason };
}
}
// Then check allow rules
for (const rule of rules.filter(r => r.type === 'allow')) {
if (toolMatchesRule(toolCall, rule)) {
return { decision: 'allow' };
}
}
// Nothing matched: escalate to human
return { decision: 'ask' };
}
```


The critical thing here: when the classifier or a deny rule blocks an action, the system treats the denial as a routing signal, not a hard stop. The model receives the denial reason, revises its approach, and attempts a safer alternative in the next loop iteration. Permission enforcement shapes behavior rather than simply halting it.

## Context Management: Five Layers of Compression


The paper identifies the context window as Claude Code’s binding resource constraint.


Not compute. Not latency.


Context. E


## Get Raviteja Nekkalapu’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


verything else in the system is designed around this bottleneck.


5 sequential shapers run before every single model call:


Budget reduction enforces per-message size limits on tool results. If ‘cat’ dumps a 10,000-line file, only a size-capped portion makes it into context.


Snip removes older history segments through lightweight trimming. It has a subtle interaction with later stages: because the main token counter derives context size from the ‘usage’ field on the most recent assistant message, and that message survives snip with its pre-snip token count still attached, snip’s savings are invisible to the counter unless explicitly passed through.


Microcompact runs fine-grained compression, always executing a time-based path and optionally a cache-aware path. When cache-aware compression is enabled, boundary messages are deferred until after the API response so they can use actual ‘*cache_deleted_input_tokens’* rather than estimates.


Context collapse is the most architecturally interesting one. It does not mutate the stored conversation history. Instead, it replaces the messages array with a projected view. The model sees the collapsed version while the full history remains available for reconstruction. The source comments state: “Nothing is yielded; the collapsed view is a read-time projection over the REPL’s full history. Summary messages live in the collapse store, not the REPL array.”


Auto-compact fires only when context still exceeds the pressure threshold after all four previous shapers have run. It calls the model itself to produce a compressed summary, making it the most expensive option, used only as a last resort.


```
Context Pipeline (runs before EVERY model call):
Raw messages
|
v
[Budget Reduction] — cap individual tool outputs
|
v
[Snip] — trim old history segments
|
v
[Microcompact] — fine-grained compression
|
v
[Context Collapse] — read-time projection (non-destructive)
|
v
[Auto-Compact] — model-generated summary (last resort)
|
v
Messages sent to model
```


The layered design exists because no single compaction strategy covers all types of context pressure. Earlier, cheaper layers run before costlier ones.


This graduated approach is something I have not seen replicated well in open-source agent frameworks, most of which rely on a single summarization strategy.

## The Extensibility Stack: Four Mechanisms, Not One


A design question that comes up in every agent framework discussion: how do you let users extend the system?


Claude Code uses four distinct mechanisms, each operating at a different cost to the context window.


Hooks (zero context cost): 27 event types covering tool authorization, session lifecycle, user interaction, subagent coordination, context management, and workspace events. Hooks can block, rewrite, or annotate tool calls without consuming any context budget.


Skills (low context cost): Defined by ‘SKILL.md’ files with YAML frontmatter. When invoked via the `SkillTool` meta-tool, skills inject their instructions into context. Only the frontmatter description stays in the prompt permanently; the full content loads on demand.


Plugins (medium context cost): A packaging and distribution format supporting ten component types (commands, agents, skills, hooks, MCP servers, LSP servers, output styles, channels, settings, and user config). A single plugin can extend Claude Code across multiple dimensions simultaneously.


MCP servers (high context cost): The Model Context Protocol is the primary external tool integration path, supporting stdio, SSE, HTTP, WebSocket, and SDK transports. Every connected server contributes tool definitions that consume context budget.


The graduated context-cost ordering is the key insight. Cheap extensions (hooks, skills) scale widely without exhausting the context window. Expensive ones (MCP) are reserved for cases requiring genuine new tool surfaces.

## Subagent Delegation: Isolated Contexts, Summary Returns


When the main agent decides a subtask needs focused attention, it spawns a subagent through ‘AgentTool’. The subagent re-enters the same ‘queryLoop()’ with an isolated context window and its own conversation history. When it finishes, only a summary text returns to the parent. The full subagent conversation is stored in a separate sidechain file.


This is the context management strategy’s natural extension. If every subagent’s full conversation inflated the parent context, complex tasks would exhaust the window before meaningful work completed. Summaries preserve the information the parent needs while respecting the binding constraint.

## The OpenClaw Comparison: Same Questions, Different Answers


The paper includes a comparison with OpenClaw, an open-source multi-channel personal assistant gateway, across six design dimensions. This is where the analysis becomes most useful, because it shows that the same recurring design questions produce fundamentally different architectural answers when the deployment context changes:


Design Dimension Claude Code OpenClaw
Safety model Per-action evaluation (deny-first, 7 layers) Perimeter-level access control
Execution Single CLI loop Embedded runtime within gateway control plane
Context strategy 5-layer compaction pipeline Gateway-wide capability registration
Extension 4 mechanisms with graduated context cost Plugin-oriented with channel adapters
Trust Progressive (20% to 40% auto-approve over sessions) Role-based, static
Persistence Append-only JSONL session transcripts Database-backed stateNeither approach is universally better. Claude Code’s layered safety is necessary because it operates in a developer’s local environment with access to the filesystem, shell, and network. OpenClaw can rely on perimeter control because it operates within a gateway that mediates all external access. The architecture follows from the deployment context, not from abstract principles.


## What The Architecture Does Not Do


The paper applies a sixth concern, whether the architecture preserves long-term human capability, as an evaluative lens. And it finds gaps.


Anthropic’s own study of 132 engineers documents a “paradox of supervision” where overreliance on AI risks atrophying the skills needed to supervise it. Independent research finds that developers in AI-assisted conditions score 17% lower on comprehension tests. Claude Code’s architecture does not appear to have explicit mechanisms that support long-term human skill development, deeper understanding, or sustained codebase coherence.


The tool amplifies short-term capability. Whether it erodes long-term capability is an open question that the architecture, as currently designed, does not address.


## Takeaways For Agent Builders


If you are building agentic systems, three patterns from Claude Code’s architecture are worth stealing:


1. Invest in the harness, not the scaffold. The 98.4/1.6 ratio is not an accident. When the underlying model improves, a minimal-scaffold architecture gets the improvement for free. An architecture that bakes reasoning into the framework needs to be re-engineered with every model generation.


2. Treat context as the binding constraint. Build graduated compression pipelines. Enforce per-tool-result budgets. Use summary-only returns from subagents. Every token that enters context should earn its place.


3. Design safety for inattentive users. If 93% of permission prompts get approved, your safety model cannot depend on human vigilance. Build deny-first defaults, independent layers, and reversibility-weighted risk assessment that work when the user is not paying attention.


The era of complex planning architectures for AI agents may be shorter than most people expect. Claude Code’s bet is that a dumb loop with a smart model and robust infrastructure will outperform a smart framework with a dumb model. So far, the bet seems to be paying off.


— -


The full architectural analysis is available at [arxiv.org/abs/2604.14228](*https://arxiv.org/abs/2604.14228*). The Claude Code source discussed in the paper is version 2.1.88.

---

*Originally published on [Medium](https://infosecwriteups.com/i-read-the-claude-code-source-analysis-so-you-dont-have-to-0a8af82956f4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
