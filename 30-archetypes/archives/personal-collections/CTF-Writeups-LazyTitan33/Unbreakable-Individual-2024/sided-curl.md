# sided-curl

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

# Solution
We start the challenge with a hint stating that there's an admin panel on localhost:8000 and we can fetch content by entering a URL in the box:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Trying a test link with google, we see that it is accessing google but then adds a `.png` to our endpoint:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Trying localhost directly obviously doesn't work and in fact, anything we have at the beginning that isn't `http://google.com` would present with the same `Invalid URL` error message:  

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Inspired by [this](https://bugs.xdavidhu.me/google/2021/12/31/fixing-the-unfixable-story-of-a-google-cloud-ssrf/) blog as well as other `SSRF` related cheatsheets, we eventually reach this sort of payload. Notice the `#` at the end that we use to break the URL and stop it from adding the `.png`:

`http://google.com@127.0.0.1:8000/admin#`

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can see that it requires a GET request with username and password as parameters however, we quickly hit another filter regarding length restriction.

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

However, luckily for us, there are numerous ways to say `localhost` and we can shorten the payload to get the flag:  

`http://google.com@0:8000/admin.php?username=admin&password=admin#`

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

`CTF{36555d5ff86de7b5a572f4c01cbfc8c677b1c1287d9c043618442d248d940b65}`
