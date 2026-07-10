# :sleuth_or_spy: FINDING GEOLOCATION from only OSINT Powers.

---

## TryHackMe

# FINDING GEOLOCATION from only OSINT Powers.

Level: Easy

The domain of Room: osint geolocation

Tools used here: Yandex Bing Google (Reverse image search)

>

Image 1

so we’ve given an image & have to find where in the world this image is from or taken.

So we don’t have any name to search or any hint to search in any web browser so we can use the reverse image search tools in this situation.

“Reverse image search isa service provided by many browsers like google, Yandex etc that allows a user to search for images using an image as the starting point, rather than a written or spoken search query. & Yandex is the most accurate one on the list”

So after a reverse search, we get to know that it’s a famous place known as cloud gate in china.

It’s just a duplicate copy of the original one which is located in Chicago.

>

Where in the world is image 1? The answer is the country name.

China

>

Image 2

Here we’ve to find the name of the place that set up this webcam. We find this webcam from shodan.io.

Here we do have a lot of information from just looking at the image like:

N Sheffield Street | N Addison Street | Sports corner around between both the streets.

## Get Ali AK’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

A simple google search of street names gives us a lot of info.

A famous bar on that street & has a banner design the same as what we see on our first image so with that clue I think we’re quite close to our target name.

*Yandex find from the name of the bar*

Now let’s hit the google map with our famous bar location (Actually there’s also another more famous place known as Wrigley field).

There’s our bar & in front of it, we’ve our target name who set up the webcam.

>

Where was image 2 taken?

Wrigleyville Sports

>

Image 3

In this image, we’ve to find the name where our webcam is focused.

You’ll notice that there’s a tower & it's looking kind of interesting & unique also its shape resembles a lot of Eiffel tower in Paris (France).

So another simple google map confirms that query also there’s a river on the map (seine river) and in this image you can see it’s also there so it’s a clue that we’re going in the correct direction to our target.

So after that just follow the river between south & west & it’ll go straight into the forest where our target is located.

In that forest area, it’s known as Meudon according to Yandex reverse search.

In the Paris observatory, we’ve our target near the museum.

>

Where was image 3 taken?

Meudon Observatory

>

Image 4

We’ve to find a location here we do have a lot of information such as car license numbers, some writing on the walls and a lot of posters but a simple Yandex reverses search gives us the location of this location/webcam. (Look like it’s a famous road :/ a lot of live open webcams there).

>

Where is image 4 taken?

Abbey Road

That’s it for this challenge if you want to solve more cases related to the OSINT domain then do check the following websites:

---
