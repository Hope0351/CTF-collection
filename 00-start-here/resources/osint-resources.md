# OSINT Resources Reference

This file consolidates the OSINT (Open-Source Intelligence) tools and
services referenced in my tools cheat sheet. Instead of linking out to
each service every time, I keep descriptions and usage notes here so the
collection stays self-contained.

---

## whatsmyname.app

**What it is.** A web-based username enumeration tool that checks
hundreds of social-media and web platforms for the existence of a given
username. The project is open-source and the source data is maintained
on GitHub by the "WebBreacher" project.

**How to use it.** Enter a username; the tool returns a list of sites
where that username exists (and where it doesn't). For CTF OSINT
challenges, this is usually the first step — find the target's accounts
on other platforms.

**Local alternative.** The same data is available via the
`sherlock-project/sherlock` command-line tool (see below), which is
useful when the web version is rate-limited or when I want to script
the search.

---

## Sherlock (command-line)

**What it is.** A Python command-line tool that enumerates usernames
across 300+ websites. Given a username, it produces a list of URLs where
that username is registered.

**Installation.**
```bash
pip install sherlock-project
```
If the pip package is out of date, I clone the source locally instead and
run it from the checkout:
```bash
# Fallback if pip version is behind:
# git clone the sherlock repo, cd into it, pip install -r requirements.txt
# Then run: python3 sherlock username1
```

**Usage.**
```bash
# Search for a username across all sites
python3 sherlock username1

# Search multiple usernames
python3 sherlock username1 username2

# Output to a text file
python3 sherlock username1 --output results.txt
```

**Tips for myself.**
- The output can have false positives (sites that always return 200).
  Manually verify any URL before treating it as a hit.
- Combine with `whatsmyname.app` — the two projects use overlapping but
  not identical site lists.

---

## Have I Been Pwned

**What it is.** A free breach-notification service run by Troy Hunt. It
indexes data from major data breaches and lets you check whether an
email address or username has appeared in any known breach.

**How to use it.** Enter an email address on the site; the tool reports
which breaches (and pastes) the email has appeared in. For CTF OSINT
challenges, this often reveals a target's secondary accounts or password
patterns.

**Notes.**
- The free tier shows the breach names but not the actual passwords.
  Don't pay for the paid tier for CTF purposes — the breach name is
  usually enough of a lead.
- HIBP also offers a domain search (for finding all breached emails at
  a given domain) and a Pwned Passwords API (for checking if a password
  is in any known breach).

---

## Shodan

**What it is.** A search engine for internet-connected devices. Where
Google indexes web pages, Shodan indexes the banner responses of every
service it can reach — HTTP, SSH, FTP, RDP, MQTT, industrial control
systems, and more.

**How to use it.**
- `apache country:DE` — Apache HTTP servers in Germany.
- `port:22` — all SSH services.
- `product:nginx version:1.18` — Nginx 1.18 specifically.
- `org:"Target Org"` — all services owned by an organisation.
- `http.title:"dashboard"` — pages with "dashboard" in the title.

**Notes.**
- A free account is enough for most CTF OSINT challenges.
- Shodan also publishes exploits and CVEs that map to its indexed
  services — useful for finding vulnerable targets (within the rules of
  the challenge).

---

## Censys

**What it is.** A search engine similar to Shodan, but with a stronger
focus on TLS/SSL certificates and a slightly different data-collection
approach. For some CTF OSINT challenges, Censys finds things Shodan
doesn't, and vice versa.

**How to use it.**
- `services.tls.certificates.leaf_data.subject.common_name: "target.com"`
  — find certificates issued for a domain.
- `services.port: 443 AND location.country: "Kenya"`
  — HTTPS services in Kenya.
- `services.software.product: "nginx"` — Nginx services globally.

**Notes.**
- The free tier has a daily query limit; use it sparingly.
- Censys's certificate search is particularly strong — use it when the
  challenge is about finding sub-domains or related infrastructure.

---

## TinEye

**What it is.** A reverse image search engine. Given an image, TinEye
finds other instances of the same image (or modified versions) across
the web. Useful for identifying where an image came from, finding
higher-resolution versions, or tracking a target's photo across
platforms.

**How to use it.** Upload an image or paste an image URL; TinEye returns
a list of pages hosting that image.

**Notes.**
- TinEye finds the *same* image. For *similar* images (e.g., other
  photos of the same person or place), use Google Images or Yandex.
- Yandex's reverse image search is notably strong for faces — often
  better than Google for identifying people in photos.

---

## SunCalc

**What it is.** A web app that visualises the sun's position at any
location on Earth, at any time and date. For OSINT geolocation
challenges, SunCalc is the tool for figuring out where a photo was
taken based on the length and direction of shadows.

**How to use it.** Navigate to the date and time the photo was taken
(if known), then drag the marker on the map until the simulated shadow
direction and length match the photo. The marker's location is your
estimate of where the photo was taken.

**Notes.**
- The technique requires knowing the date and approximate time the
  photo was taken. Without that, shadow analysis is ambiguous.
- SunCalc also shows moonrise/moonset and twilight phases, which can
  help narrow down the time window.

---

## Wayback Machine (web.archive.org)

**What it is.** The Internet Archive's historical web cache. It has
been archiving web pages since 1996 and has snapshots of billions of
URLs over decades. For OSINT challenges, the Wayback Machine is the
canonical tool for finding deleted pages, old versions of sites, and
content that has been edited since publication.

**How to use it.** Paste a URL into the search bar; the Wayback Machine
shows a calendar of every snapshot it has for that URL. Click a
snapshot to view the page as it was on that date.

**Notes.**
- The "Save Page Now" feature lets me archive a live page for future
  reference — useful when a CTF challenge page might disappear after
  the event.
- The Wayback Machine also has an API for programmatic access:
  `https://web.archive.org/web/*/example.com/*` returns all snapshots
  of any page under `example.com`.

---

## Source attribution

The descriptions above were written in my own words based on the
official landing pages of each service, downloaded on 2026-07-11 for
reference. The services themselves are not reproduced here — only my
notes about them. Service names are trademarks of their respective
owners.
