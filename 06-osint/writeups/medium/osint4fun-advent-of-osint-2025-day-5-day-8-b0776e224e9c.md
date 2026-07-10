# :sleuth_or_spy: OSINT4Fun: Advent of OSINT 2025 (Day 5 - Day 8)

---

## Day 6

[Advent of OSINT 2025 — Day 6 | OSINT4Fun](https://www.osint4fun.eu/advent2025/20251206183000)

You come across this [inspiring video](https://www.linkedin.com/posts/macha-b-626b78_en-ces-temps-incertains-ou-nous-nous-faisons-activity-6921350945398288385-rvhy/) on LinkedIn.

Q) Which influencer was the first to make this video go viral?

This question was a little weird for me, as I just stumbled into the correct answer. I am not sure if this was the intended way to solve the challenge.

First, I used a LinkedIn post date extractor to find out when the video was posted.

LinkedIn Post Date

The post on LinkedIn was made on April 17, 2022. Since we know this is a reshare, the original post will have been made on a date before April 17, 2022.

A video is nothing but a collection of images. Which means we can use the same technique we have used with images to find videos. Using screenshots taken at different points in the video, we can find videos with similar content.

This works because most of the time frames from the video are used as the thumbnail. Luckily for us, social media sites only use frames from the first few seconds to decide the thumbnail. So using screenshots from the start of the video, we should be able to find all sites on which this video was posted.

Frame 1 from Video

I took the 1st frame from the video and performed an image search. There were multiple results from LinkedIn, but none of these accounts had sufficient followers to be called an influencer.

LinkedIn page with postLinkedIn page with post

There was also a post by an account on Facebook that had thousands of followers; however, this video was posted after April 17, 2022, which disqualifies it.

Facebook GroupFacebook Group Post

The result also had a news article. This caught my attention because the title mentioned Anand Mahindra, who I know is the chairman of the Mahindra Group. Mahindra Group is a large multinational conglomerate from India.

Google Image Search resultNews article with video

The article has a direct link to Mahindra’s post on Twitter/X. The video was uploaded to Twitter on April 1, 2022, which is before the April 17, 2022 date. Clicking on Mahindra’s name will take us to his Twitter page.

Link from news article

He has over 11M followers and can definitely be called an influencer. Anand Mahindra turned out to be the correct answer.

Original posters Twitter page

>

Anand Mahindra

I also performed an image search using a frame that is a few seconds into the video. With this frame I was able to get Mahindra’s post on Twitter/X as the first result.

Another frame from the videoGoogle Image Search results

---
