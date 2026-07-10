# :sleuth_or_spy: OSINT4Fun: Advent of OSINT 2025 (Day 1 - Day 4)

> **Original Source:** [OSINT4Fun: Advent of OSINT 2025 (Day 1 - Day 4)](https://infosecwriteups.com/osint4fun-advent-of-osint-2025-day-1-day-4-0ef1675cee8a)
> **Platform:** infosecwriteups.com | **Category:** `OSINT` | **Year:** 2025

---

## Day 2


[Advent of OSINT 2025 — Day 2 | OSINT4Fun](https://www.osint4fun.eu/advent2025/20251202143000)


Christmas is approaching, and you’re feeling nostalgic for your summer holidays. You come across this photo of one of the iconic places from your trip. One of the members of your group, who particularly enjoyed the visit, shared her thoughts in August 2025 as well as other photos online, including one picture showing the chandelier under the entrance porch.

Location with Ceiling with FlagsQ) What is this person’s first name and what is the green and red object hanging from the chandelier?


For me this challenge was quite difficult. It took me a long time and a few hints before I was finally able to solve it.


The description provided along with the image is pretty important. We learn that the trip in question took place during Summer 2025. We also learn that the person who posted the image is a woman. We also are told that the person enjoyed the location.


Since we have an image, let’s use Google Lens to find images with similar features.

Image Reverse Search Results


Since this image was taken during a trip, results that list flags for purchase can be ignored. I used the TripAdvisor links as a starting point, as they provide reviews for locations that are popular with tourists. I believed this was the site where the person in question had posted their review/images.


However, this is where I ran into a major hurdle. I looked at all the relevant results from the image search; however, none of them had images that matched the picture provided in the question.


This challenge can only be solved when the image search is performed from France (might work for some other countries as well). This issue can, however, be easily mitigated by using a VPN.


After changing my location to France, I once again performed the image search. This time I found a cafe that had a ceiling that looked similar to the image in the question. I decided to investigate the images related to this cafe to identify if this was the correct location.

Image Reverse Search Results


[BAGDAD CAFE, Newberry Springs — Restaurant Review — TripAdvisor](https://www.tripadvisor.in/Restaurant_Review-g32775-d1988674-Reviews-Bagdad_Cafe-Newberry_Springs_California.html)


## Get David Varghese’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


I opened the reviews section and filtered them to only display the ones that match the criteria that were given in the question, which narrowed it down to a single comment.

TripAdvisor Rating Filter


This review did not have an image with a chandelier.

TripAdvisor Review


However, this review had an image that showed the same globe that was present in the image from the question.

TripAdvisor Review


Next, I decided to browse through the images that were posted for this location, and sure enough, I found other images that contained posters and flags, which are also visible in the original image.

TripAdvisor ReviewTripAdvisor Review Image Zoom


I was now confident that I had the correct place. The location visited during the summer trip was Baghdad Cafe in Newberry Springs, California.

Original Image with Highlighted Items of Interest


I looked up Baghdad Cafe on Google. Google also has an option to review places. Clicking the Opinion/Review button will open a new page.

Baghdad Cafe Google Listing


On this page clicking on “more” beside any of the review will open a new page. On this page the full review, along with images, can be viewed.

Baghdad Cafe Google Review


The third review (at the time of writing this walkthrough) was by a Denise Deneuville from 3 months ago (Sept 2025), which falls in the Summer 2025 time range. The review had 5 stars and seems to be posted by a lady. All the attributes of this review match the conditions specified in the description. This review also had an image of a chandelier from the cafe entrance.

Baghdad Cafe Google Review


The chandelier has a green and red hat stuck on it.

Baghdad Cafe Google Review Image

>

Denise Hat

---

*Originally published on [Medium](https://infosecwriteups.com/osint4fun-advent-of-osint-2025-day-1-day-4-0ef1675cee8a). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of osint CTF writeups.*
