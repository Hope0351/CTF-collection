# :game_die: HACK-ERA CTF - Phase 1 Walkthrough

---

## Challenge 1: The Ghost Protocol

>

Elliot’s mission was never meant to fade.

>

Mission Brief:

E Corp is back stronger, smarter, more dangerous. But so are we. @revenantRoot, once a ghost in the system, now leads a new digital resistance. As the head of this reborn crew, they’ve launched RabbitCatCTF, a covert campaign to finish what Elliot started. With Elliot back in the network, the fight reignites. Each flag you uncover exposes cracks in E Corp’s armor. “We don’t forget. We don’t forgive. Elliot’s mission lives on through us.” Join revenantRoot. Dig deep. Break their system. This is RabbitCatCTF. This is the new fsociety. Try OSINT to reveal the answers.

This is an OSINT CTF….which means we need to search for the flags in different open-source platform and by carefully observing the Mission Brief or Problem Statement we got a usernameLet’s start searching about this username @revenantRoot.

First, we will use normal google search.

But we didn’t got lucky…there is no entry related to revenantRoot in the Search Engine. Let’s use some advance tool like [sherlock](https://github.com/sherlock-project/sherlock)*.*

>

Sherlock is the tool which Hunt down social media accounts by username across [400+ social networks](https://sherlockproject.xyz/sites)

let’s search for revenantRoot using sherlock tool.

And as you can see we got many links for the user revenantRoot but most of them are irrelevant……Only the medium link has something of our interest.

After clicking on Medium link it redirect us to a blogging page where there is only one blog written titled Legacy of Rebellion: Why We Hacked E-Corp Again…which is kind of related to our Mission Brief or Problem Statement.

Let’s see what’s inside.

So, there are many hints in the blog.

*HINT 1*

Hint 1: Same Name of CTF (The RabitCat CTF) as in the Problem Statement…which confirms that we are on the right track.

*HINT 2*

Hint 2: Name of the repository legacy-zeroday which contains a file called exploit.py

*HINT 3*

HINT 3: Clue for the image inside the same repository and also about the metadata of the image.

let’s search for the repository in github.com

And we got one repository which contains a exploit.py as mentioned in the blog.

exploit.py is a dummy code which doesn’t hold any value let’s check for the images directory.

Image directory contains a image of a building which is related to our first flag.

>

1. What was the name of the café where deals, leaks, and whispers were exchanged just to the right of the building with too many windows?

To search the cafe we need to first find the location where this image was taken. We can use different methods like [Metadata](https://en.wikipedia.org/wiki/Exif), [Reverse Image Search.](https://en.wikipedia.org/wiki/Reverse_image_search)

We will go with Reverse Image Search because it’s easy with Google Lens.

Now we will got many results related to the image we got from github.com

And…we got the address in one of the result. See the screenshot below:

Let’s search for this address in Google Maps…because as per the first flag question we need to name the cafe just right to this building.

And we successfully got the cafe just right to this building.

If it’s not clear…let me show you the closer view of the cafe.

Yeaah… we got our first flag which is:-

>

1. What was the name of the café where deals, leaks, and whispers were exchanged just to the right of the building with too many windows?

Ans: my_place_soho

Now…we already have a hint from the blog about the metadata, let’s see the metadata of this image using [exiftool.](https://exiftool.org/)

And it looks like we got another username *xLangford01 *and it is having that /u/<username> format which indicates it may be a reddit user.

let’s search reddit.com/u/xLangford01

Again we got different hints in this reddit post.

HINT 1: The same name of CTF (RabbitCat CTF) which indicates we are on the right track.

HINT 2: We got another username *ciscoMadx.*

Let’s search for *ciscoMadx *using sherlock tool.

We got different profile related to *ciscoMadx *but we got a relevant link of Twitter account.

By going through the Twitter account we got a post which reveal our last flag of this Challenge.

>

2. WHat is the real email of revenantRoot? its not ctrlxrevenant@gmail.com?

Ans: FLAG{revenantroot.6889@hackera.com}

---
