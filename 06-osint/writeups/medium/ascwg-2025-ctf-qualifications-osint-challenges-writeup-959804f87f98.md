# :sleuth_or_spy: ASCWG 2025 CTF Qualifications - OSINT Challenges Writeup

---

## 3rd Challenge

## Challenge Name: “Operation Spare Clue”

>

Description:
Agent,
Your mission — should you choose to accept it — involves tracking a target moving between the cracks of the visible and the invisible. Intelligence has provided a single, seemingly innocent street photograph. But as always, the truth hides in the details.

OBJECTIVESPhase 1: Ground Recon

Examine the provided street image. Determine the exact location of the scene.

Across the street lies your first lead — a supermarket. Secure its contact number this will be the first part of the flag.

Also in the street you will find a PGP key. Your task: Unmask the true identity behind the key.

Phase 2: Social Deep Dive (When you find the name/username of the PGP key owner)

The subject has left a trace on social media — a selfie taken in front of a mirror.

Within this reflection lies the name of a shop.

Phase 3: Final Lock

Locate the physical location of this shop.

Secure the Facebook Page ID of the associated restaurant and this will be the second part of the flag.

Remember:
Time is not on your side. The enemy covers their tracks quickly. This message will self-destruct in five seconds.

Good luck, Agent.
The Agency is counting on you.

for Example:
- if the phone number of supermarket is 098765432 and the restaurant’s facebook page ID is: 12345667789
so the flag will be: ASCWG{098765432_12345667789} remember the underscore.

Challenge Photo:

Not every OSINT investigation starts with leaked data or exposed credentials. Sometimes it starts with something far more mundane, a single street photograph.

But in the world of open‑source intelligence, no image is just an image. Every reflection, every signboard, every QR code is a potential thread in a larger story.

That’s exactly the premise of *Operation Spare Clue*, a multi‑phase geolocation and identity investigation that moves from the streets of Georgia to the digital traces of a person, and finally to a Facebook page buried behind a restaurant’s branding.

## Phase 1 : Ground Recon

The provided image showed a spare parts shop not a global chain, but one with multiple branches. A quick search of its branding/logo across Google Images showed several potential matches across Eastern Europe and the Caucasus region.

Filtering results, the shopfront style and sign fonts aligned closely with those in Tbilisi, Georgia.

## Phase 2: Verifying with Google Earth

Dropping into Google Street View / Earth, I virtually navigated the identified Tbilisi street, moving up and down until the exact perspective from the photo matched perfectly.

Once aligned, I scanned the opposite side of the street just as the mission briefing hinted and there it was: a supermarket.

The supermarket’s signboard was clearly visible, allowing me to Google its name, find its official business listing, and extract the contact phone number. This number would later become the first part of the flag.

first part of the flag: 597574957

## Phase 3: The Hidden PGP Key

Looking back at the original image, something else stood out a white van parked on the street, with a QR code printed on the door.

Scanning the QR code redirected to a Carbon paste link a minimal pastebin‑style site containing a PGP public key block.

With the key in hand, I needed the fingerprint.
Using any OpenPGP tool (either `gpg` locally or online parsers), I extracted the key fingerprint.

Searching the fingerprint in:

- Google Search Pages

- Keyserver databases

- GitHub commits

- PGP directory lookups

will lead you to a username repeatedly associated with the key the PGP key owner’s online handle.

Searching that username across multiple platforms revealed a social media account. On one of their profiles was a mirror selfie.

Among all Google Lens results you will find another selfie at the same place with the same mirror reflection exposes the specific place address which is: Rome.

So, according to the challenge description, we need the Facebook Page ID and now we have Place name and location. all what need now is just a simple google search to get our page.

From “About > Page Transparency” tab you will find the Facebook Page ID:

So, the final flag is: ASCWG{597574957_132037800183249}

---
