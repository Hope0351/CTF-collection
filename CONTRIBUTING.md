# Contributing to CTF-collection

First off, thanks for taking the time to contribute! This project aims to be the most comprehensive, professionally-curated archive of CTF (Capture The Flag) learning resources on the internet — and community contributions are essential to keeping it current.

## How to Contribute

### Adding a New Resource

1. **Check for duplicates.** Search the relevant category, event, and archetype pages to make sure the resource isn't already listed.
2. **Pick the right entry point.** A resource belongs in exactly one primary category (e.g., `01-pwn/`), but can be cross-referenced from events (`20-events/`), archetypes (`30-archetypes/`), and years (`50-writeups-by-year/`).
3. **Use the standard entry format** (see below).
4. **Open a pull request** with a clear title like `Add: <resource name> to <category>`.

### Standard Entry Format

Each entry in a list should follow this format:

```markdown
| # | Resource | Type | Difficulty | Year | Why It Matters |
|---|----------|------|-----------|------|----------------|
| 1 | [Resource Name](url) | GitHub / Medium / YouTube / Blog | Beginner / Intermediate / Advanced / Elite / Varied | 2024 | 1–2 sentence reason |
```

For featured entries (top 3–5 in a category), add a dedicated subsection with:

- A 100–200 word summary of what the resource covers
- Recommended prerequisite knowledge
- What you'll learn
- A direct link

### Improving Existing Entries

- Fix broken links (open an issue first if the resource has moved)
- Add missing metadata (difficulty, year, prerequisites)
- Improve annotations — make them more specific and useful

### Reporting Issues

Open an issue for:
- Broken links
- Miscategorizations
- Outdated information
- Suggestions for new categories or sections

## Style Guidelines

- **Tone:** Third-person, encyclopedic, portfolio-grade. Avoid first-person.
- **Depth:** Every section should have at least 150 words of substantive content. No stub sections.
- **Links:** Always link to the canonical source. Don't link to mirrors or aggregators.
- **Attribution:** Cite the original author/team by name when known.
- **Language:** English only at this time.

## Pull Request Process

1. Fork the repo and create your branch from `main`.
2. Make your changes following the style guidelines above.
3. Ensure the markdown renders correctly on GitHub.
4. Update the `CHANGELOG.md` with a one-line entry describing your addition.
5. Open a pull request with a clear description.

## Code of Conduct

By participating, you are expected to uphold our [Code of Conduct](CODE_OF_CONDUCT.md).
