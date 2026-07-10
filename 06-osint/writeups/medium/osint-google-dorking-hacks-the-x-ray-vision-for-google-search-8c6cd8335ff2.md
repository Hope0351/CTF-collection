# :sleuth_or_spy: OSINT: Google Dorking Hacks: The X-Ray Vision for Google Search

---

# OSINT: Google Dorking Hacks: The X-Ray Vision for Google Search

You type in some keywords, scroll past 10 pages of useless results, and wonder why the internet’s hiding the good stuff. Sound familiar?

Then, you must know about Google dorking.

### What is Google Dorking ?

It refers to using special search commands that help you find exactly what you’re looking for.

With it, you can uncover hidden info,documents, or data that doesn’t show up in normal searches. Think of it like having X-ray vision for the internet!

But here’s the thing: while it can be super useful for research or finding public info, it can also be misused to sneak into sensitive stuff.

These are the search operators that make Google bend to your will:

- `site:example.com`: Limits results to a specific domain. Want only stuff from NASA? site:nasa.gov

- `filetype:pdf` (or `ext:pdf`): search file types (PDF, pptx, xlsx, epub).

- `intitle:keyword`: keyword appears in the page title.

- `inurl:keyword`: keyword appears in the URL.

- `intext:keyword`: keyword appears in the page body (at least one).

- `allintext:kw1 kw2` : all words after operator must appear in the body text.

- `inanchor:keyword` : keyword appears in anchor text of links to the page.

- `cache:URL`: view Google’s cached version of a page.

- `link:example.com` : pages that link to a URL (limited usefulness).

- `related:example.com`: sites similar to a domain.

- `"exact phrase"` : force exact phrase match.

- `-keyword`: exclude results containing keyword.

- `OR`: logical OR (must be uppercase).

- `*`: wildcard (fills in unknown words in a phrase).

- `before:YYYY-MM-DD` and `after:YYYY-MM-DD`: date filters for indexed content.

>

Pro tip: Combine these like a scientist. Try filetype:pdf site:*.edu “financial report” to find academic PDFs. I once found a 200-page report on AI ethics this way.

For example:

```
filetype:pdf site:example.com "financial report"
```

This query looks for PDF files on `example.com` containing the phrase “financial report.”

### Few Google Dork Queries You Can Try Legally

- Find publicly available PDFs on a website

```
"Deep Learning with Python" filetype:pdf
```

This will list PDF files mentioning the book. Often, you may find slides, tutorials rather than full pirated books.

## Get S.Ali’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

2. Find video tutorials with slides or code

```
"Deep Learning with Python" site:youtube.com
```

YouTube videos specifically about the topic

3. Locate specific keywords in URLs

```
inurl:blog "AI trends"
```

This will return blog pages with “AI trends” in their URL. Perfect for finding niche blogs and industry insights.

4. Track Down Tech Handbooks

```
"Web Application Hacker's Handbook" filetype:pdf OR site:github.com
```

Free, public PDFs or GitHub repos mentioning the book.

```
"The DevOps Handbook" filetype:pdf OR site:github.com
```

Checks your site for exposed config files or credentials.

Find pages where *all* words appear in text

```
allintext: neural networks backpropagation tutorial
```

Exclude common noise

```
"Deep Learning with Python" filetype:pdf -site:scribd.com -site:amazon.com
```

5. Secure Your Own Site (Defenders Only)

```
site:example.com filetype:env OR filetype:config OR intext:"API_KEY" OR intext:"password"
```

## How site owners can use dorks to defend themselves

Run these searches on your own domain (or ask your security team) to find public leakage:

- `site:yourdomain.com filetype:env OR filetype:sql OR filetype:bak`

- `site:yourdomain.com intext:"password" OR intext:"api_key" OR intext:"secret"`

- `site:yourdomain.com inurl:admin OR inurl:login OR inurl:dashboard`
Found something: Remove them from public directories, add `robots.txt` rules, use `X-Robots-Tag: noindex`, and request removal from Google Search Console or use the URL removal tool.

## Ethical & legal rules (non-negotiable)

- Only access publicly indexed content. Never use dorks to find and then exploit vulnerabilities or download pirated content.

- Do not attempt unauthorised access. Querying is allowed; breaching, scanning, or exploiting is illegal.

- When in doubt, act as a defender : report exposures to the site owner or use responsible disclosure channels.

---
