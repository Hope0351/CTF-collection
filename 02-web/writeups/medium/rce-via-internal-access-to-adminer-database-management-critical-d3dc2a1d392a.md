# :globe_with_meridians: RCE via Internal Access to Adminer Database Management (Critical)

---

## Get Ahmad Halabi’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Getting Internal Access ::

First of all, I searched for CVEs and known exploits belonging to the version number identified by this Adminer Login panel but I had no luck.

Second thing I did, I checked the target program’s Github repository for any exposed credentials pointing to the Adminer Login Panel but I also didn’t find anything interesting.

Last thing I did, I searched Google for Default Adminer Login credentials AND for commonly credentials used for Adminer Login. I got quite cool results. Trying them all out after 2 hours I got successful access to the internal Database of the company leading to Remote Code Execution where I can manipulate their Database.

The username was: `homestead`

The password was: `secret`

---
