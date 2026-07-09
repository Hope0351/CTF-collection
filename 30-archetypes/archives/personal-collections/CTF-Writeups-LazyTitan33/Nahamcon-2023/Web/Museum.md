# Museum

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

When we access the webpage, we have the option to view some images:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The link is interesting. What else can we browse other than artifacts?

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

I fuzzed it with my favorite wordlist for LFI, `LFI-Jhaddix.txt` from seclists.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can read files which is great because it turns a blackbox approach into a whitebox one:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can't read the flag though.. so sad:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Abusing the `/proc/self/cmdline` path, we can see where the app is running from:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And we can grab the source code to better understand the application and experiment locally.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We find two interesting endpoints. A `/private_submission_fetch` and a `/private_submission`. The latter seems to only be accessible from `127.0.0.1`. This will become important later.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

From the source code we can see that from the /browse endpoint we won't be able to read the flag.txt because it is filtered:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Several hours of experimentation later, we reach a syntax that allows us to actually write abritrary files locally, even overwrite them. The URL encoding was crucial as well. Even when putting the link in the browser. Letting the browser do its own encoding for some reason didn't work for me and the payload wasn't triggering. Same with using localhost instead of 127.0.0.1 (see above).

http://challenge.nahamcon.com:31631/private_submission_fetch?url=http%3a//127.0.0.1%3a5000/private_submission%3furl%3dhttp://127.0.0.1:1337/test.txt%26filename%3dfile.txt

I had saved the source code locally so the link above reflects me accessing another endpoint where I'm downloading test.txt from and writing it to file.txt.. into the /public folder according to the source code, however path traversal is possible there so it could be written anywhere the user running the app has access to.

The problem I was facing for the longest time is what to do with it because this Flask application was running with Debug set to `False`. This means that the application will run in the state it was when it was started. Any changes to its code won't apply unless the app is restarted. 

I even experimented with the `file:///` protocol on the /private_submission_fetch endpoint and I wasn't able to get anything out of it.

Then in the last leg of the race, literally 15 minutes before the CTF ended, I was nudged towards a different angle. I was made to realise that I failed to try the file protocol in the /private_submission endpoint. It clicked into place in my mind and then I ended up with the URL below:

http://challenge.nahamcon.com:31631/private_submission_fetch?url=http%3a//127.0.0.1%3a5000/private_submission%3furl%3dfile:///flag.txt%26filename%3dfile.txt

This copies the flag in the /public directory with the name file.txt and I can read it.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

flag{c3d727275bee25a40fae2d2d2fba9d70}






