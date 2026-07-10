# :locked_with_key: My mobile challenge and BSides SF CTF

> **Original Source:** [My mobile challenge and BSides SF CTF]()
> **Platform:** medium.com | **Category:** `CRYPTO`

---

# My mobile challenge and BSides SF CTF


(Originally published on Mar 1st, 2017)


A couple of weeks ago I had a blast organizing the BSides SF CTF alongside — [@bmenrigh](https://twitter.com/bmenrigh), [@CornflakeSavage](https://twitter.com/CornflakeSavage), [@iagox86](https://twitter.com/iagox86) and [@matir](https://twitter.com/matir). The CTF had challenges that were primarily in the easy to intermediate range, with a few curve balls thrown in for the seasoned players. We had a few on-site challenges, including a lock picking challenge by @bmenrigh and @matir. This was by far my favorite challenge, which had a lock mounted on a wooden post that was hooked to a receipt printer. When a player successfully picked the lock they would get a one time flag.


I started playing CTFs about a year ago after joining @matir’s group — Shadow Cats. So, the entire CTF landscape is very new to me. It was great to work with the rest of the organizers, who were seasoned CTF players, their energy and enthusiasm was contagious! One of my favorite sessions was when each of us spoke about the challenges we had designed, it convinced me that @iagox86 was a mad man for creating nibbler. In terms of my role with the BSides CTF, I was mostly in the periphery, helping out with — css changes, scoreboard updates, challenge release and general slack support.


I enjoyed most of my interactions with people on slack, watching folks work on challenges I wrote and going from frustrated to elated as they unravelled the puzzle was very rewarding. After talking to them and the folks on-site I realized that they enjoyed listening to the inspiration behind the challenges and how they were meant to be solved, so here it goes!


Pinlock


I don’t see a lot of mobile challenges or people attempting them during CTFs, so I decided to make a simple reversing challenge to show people that android applications are just fancy jars.


The application is fairly simple, it takes a numeric pin, if correct it displays text read from a database. To get things started, a player could change the extension of the apk to zip and unzip it, or decompile it with apktool. This should give them access to the SQLite database (pinlock.db) and a README in the assets folder.


The database had three tables — pinDB, secretsDBv1 and secretsDBv2, each had only one entry. Pindb as the name suggests has the hashed pin, given that the pin is numeric I was hoping the first thing someone did was google the hash (d8531a519b3d4dfebece0259f90b466a23efc57b). That should give them the 4 digit pin — 7498. The other two had a base64 string, I observed that a lot of players stopped at this step and started trying to plug in the the base64 decoded strings. These were encrypted blobs, so they are readable strings and certainly do not have the prefix “flag:” which was the flag format.


If the player took to the time to look at the README, it would have helped tie things together by outlining the contents of the database. Here is what it said -

>

*v1.0:- Pin database with hashed pinsv1.1:- Added AES support for secretv1.2:- Derive key from pin[To-do: switch to the new database]*


At this stage, the player should have realized that the content of the secrets tables are encrypted and will probably require inspecting the code for more details. They can dex2jar and then use a java decompiler like jd-gui to look over the source code, which should be fairly readable.


The code should reveal that the data shown on the second activity is the data in the first version and doesn’t need further inspection, this leaves them with the string in secretsv2. The README talks about a key derived from the pin, and a closer inspection of the code should show that it uses PBKDF2. Here is the snippet for v2 key creation -

>

*int iterations = 1000;byte[] salt = “SampleSalt”.getBytes();char[] pinArray = pin.toCharArray();SecretKeyFactory secretKeyFactory = SecretKeyFactory.getInstance(“PBKDF2WithHmacSHA1”);KeySpec ks = new PBEKeySpec(pinArray, salt, iterations, 128);SecretKey secretKey = secretKeyFactory.generateSecret(ks);keySpec = new SecretKeySpec(secretKey.getEncoded(),”AES”);*


A player could copy the above snippet and the decryption function and get the flag, or just reimplement the key derivation + decryption in their language of choice.


Flag Receiver


This challenge was aimed at people who knew more about Android / wanted to learn more. The core part of the challenge was intents and custom permissions. It was


a slightly simplified version of an android challenge I made for Google CTF last year called “Ill Intentions”. I decided that the name gave too much away and instead went with Flag Receiver, in retrospect not many people solved it so, I could have stuck to another “intent” related name as a hint.


The android application had a blank landing activity, this should have made the player realize that they had to reverse the app to proceed. Following the same steps as the previous challenge, they would have seen that application receives and sends intents. It listens for an intent with action — com.flagstore.ctf.INCOMING_INTENT and permission — ctf.permissions._MSG. Once it receives such an intent it will check to see if the intent had an extra named “msg” with the value “OpenSesame”.


This would display a button that would allow the player to broadcast an intent. The outgoing intent will have the flag :)


To make reversing harder, I had the flag computation split between java and JNI. The player could use adb to call the second activity and then broadcast the intent, reverse the JNI bits with IDA or write a small app with the custom permission ([with uses-permission](https://developer.android.com/guide/topics/manifest/uses-permission-element.html)).


Most players went with the [reversing approach](https://ctf.rip/bsides-sf-ctf-2017-flag-receiver-mobile-reverse-engineering/), because it was their forte or preferred approach. The [second approach](http://blog.squareroots.de/en/2016/05/google-ctf-2016-ill-intentions-mobile/) was to use frameworks like Xposed or Android’s adb to broadcast the intents. I did see a [writeup](https://blog.lse.epita.fr/articles/78-google-capture-the-flag-2016-mobile-category.html) for “Ill Intentions” that had folks write an app, but this seemed like an outlier.


Overall, the challenges were fun to write and it was great to listen to how people solved the challenges. If you want read @iagox86’s take on his challenges, check out his write-up [here](https://blog.skullsecurity.org/2017/bsidessf-ctf-wrap-up). If you want to try the BSides SF 2017 challenges, check out our Git repo [here](https://github.com/BSidesSF/ctf-2017-release).

---

*Originally published on [Medium](https://itsc0rg1.medium.com/my-mobile-challenge-and-bsides-sf-ctf-f9fc4dfca60). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of crypto CTF writeups.*
