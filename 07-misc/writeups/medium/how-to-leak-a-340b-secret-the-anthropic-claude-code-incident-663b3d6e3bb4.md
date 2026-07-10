# :game_die: How to Leak a $340B Secret: The Anthropic “Claude Code” Incident

> **Original Source:** [How to Leak a $340B Secret: The Anthropic “Claude Code” Incident](https://infosecwriteups.com/how-to-leak-a-340b-secret-the-anthropic-claude-code-incident-663b3d6e3bb4)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# How to Leak a $340B Secret: The Anthropic “Claude Code” Incident


I genuinely thought this was an April Fool’s prank. Every year, companies like Google pull some elaborate stunt, so when I saw the “Claude Code leak” trending on April 1st, I kept scrolling.


But out of curiosity, I checked the npm registry for `@anthropic-ai/claude-code`. The version everyone was talking about (v2.1.88)?


Gone. Not deprecated. Not hidden. Just scrubbed from existence.


That’s when it stopped looking like a joke.


*where is v2.1.88?*

## What Actually Happened


This wasn’t a sophisticated zero-day or a database breach. It is just a bad release.


It was a perfect example of how modern software supply chains fail fast and fail publicly:


- The Trigger: Anthropic pushed an update to npm.

- The Cargo: Inside the package was a 59.8 MB debug artifact.

- The Payload: A `.map` file (`cli.js.map`) that didn't just map code—it contained the `sourcesContent` for the entire project.

## The Timeline of Chaos


- T+0 mins: Version 2.1.88 hits npm.

- +23 mins: Security researcher Chaofan Shou notices the unusual file size and downloads the package.

- +45 mins: The source is extracted. It’s not just snippets; it’s 1,900+ TypeScript files and 512,000+ lines of proprietary logic.

- +2 hours: The GitHub mirrors start to appear, before the first DMCA notice can even be drafted.

- +6 hours: The “clean-room” rewrites begin. A Python port and a Rust rewrite (likely AI-assisted) exploded.

## What is a Source Map actually?


A source map is a JSON file that acts as a bridge between your “ Production Code” and your “Development Code.”


Why this exists:


Modern web development is a series of transformations:


- TypeScript → Compiled to JavaScript

- Modern JS → Transpiled for compatibility (Babel)

- Code → Bundled and Minified (Vite, Webpack, or in Anthropic’s case, Bun)


The final code is a single-line mess. If an error happens in production, your stack trace looks like this: `Error at a.js:1:98432`. You are effectively blind.


## Get Yuvarajan’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The Fix:


A source map tells the browser: *“Line 1, column 98432 in bundle.js actually maps to line 42 in *`*AuthService.ts*`*."*

## How to Extract Code from .map Files


If you’re a dev and you see a `.map` file in the wild, here is how you "reverse" it.

### Method 1: The DevTools Way


- Open Chrome DevTools → Sources tab.

- If the site has maps enabled, look for a folder usually named `webpack://` or `file://`.

- You can browse the original source tree, set breakpoints, and read comments exactly as the author wrote them.

### The Billion-Dollar String: Why `sourcesContent` is a Security Nightmare


If you open that `.map` file in a text editor instead of a browser, you’ll see why DevTools is able to show you the original code.


Most people don’t realize there are two ways a source map handles your files:


- Reference Maps: They just point to paths (e.g., `"sources": ["src/main.ts"]`). If a hacker downloads this, they get a list of your filenames, but the files are empty because they don't have access to your local machine's file system.

- Inline Maps (The “Anthropic” Way): These include the `sourcesContent` field. This is a massive array of strings containing the actual raw source code of every single file in your project.


This is what Anthropic did. They didn’t just point to the code; they bundled the entire repository *inside* the map file. When you have `sourcesContent`, DevTools doesn't need to look for your files on a server—it already has the full text sitting right there in the JSON. What We Learned (The “Undercover Mode” and more)


The leak revealed more than just code; it revealed Anthropic’s roadmap:


- “Kairos”: An unreleased daemon mode that allows Claude to run as an always-on background agent.

- “Undercover Mode”: A feature that strips AI attribution from commits so devs can contribute to public repos “silently.”

- “Buddy”: A full-blown pet/Tamagotchi system (likely the intended April Fool’s release) with rarity tiers and “shiny” variants.

## The Security Takeaway


- Your build pipeline is a bigger risk than hackers. A single misconfigured `.npmignore` or a missing `files` field in `package.json` can bypass all your firewalls.

- Deletion is an illusion. Anthropic nuked the package within hours, but by then, it was already mirrored in 40,000 places.

- Check your Bundler. Anthropic uses Bun. Bun (and Vite/Webpack) make it very easy to generate maps; you must be explicit about *where* those maps go.


Pro-tip: Use a tool like `source-map-explorer` As part of your CI/CD, visualize what you're actually shipping before it hits the registry.

## References:


[https://github.com/chatgptprojects/clear-code/tree/642c7f944bbe5f7e57c05d756ab7fa7c9c5035cc?tab=readme-ov-file](https://github.com/chatgptprojects/clear-code/tree/642c7f944bbe5f7e57c05d756ab7fa7c9c5035cc?tab=readme-ov-file)

---

*Originally published on [Medium](https://infosecwriteups.com/how-to-leak-a-340b-secret-the-anthropic-claude-code-incident-663b3d6e3bb4). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
