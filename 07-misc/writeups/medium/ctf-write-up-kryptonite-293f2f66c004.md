# :game_die: Ctf Write Up Kryptonite 293F2F66C004

---

— — — — -

### Intro and setup

This challenge intends to show how to enumerate android apps in search for hidden information.

Disclaimer: this write-up shows tools specific for testing Android apps, which need to be installed separately. The installation steps vary depending on the host OS. It’s clearly explained on the Internet, google it if you don’t have these tools installed.
The apk is installed by dragging it to Genymotion or other emulators, or by installing it to a physical device with the command:

A new icon appears on the device:

We proceed to run the app. Text is written in 1337 for extra haX0r feel. The title has the word 435 = AES in 1337. This gives a hint about the crypto being used in the app.

*Main Activity of the app*

We can enter a message and a key, and encrypt the message with AES. The function used in the Java code of the app is:

Stronger ciphers exist, for example CBC mode. Also, entering a ciphered text with this same algorithm allows to decrypt it. In both cases the result is shown in the lower textbox. AES requires a key length of 16, 24 or 32 bytes. Otherwise we are warned by a toast message:

*The key used has wrong length*

After supplying a valid length for the key we see the encrypted message:

*Valid key length results in an encrypted message*

### Enumeration

When pentesting mobile apps, it’s always a good idea to use them as a normal user would before start testing for errors. Very often apps start storing data locally and errors can occur with the way data is stored. If we don’t produce this data first by using the application features, we could miss this data.

We need to inspect the internal memory of the application. For that we need to access the phone via USB using the android debug bridge (ADB). We get a shell inside the phone with:

Android apps are installed in /data/data. We need to find our target app, for that we can simply combine ls with grep, looking for the app name.
The folder databases has been created by the app, and it contains a sqlite database. With the:

sqlite3 default.db

command we can access it.
.tables shows the tables available in the database.
We see all records of table test with

Three records (marked in blue in the next picture) existed prior to the newly created record, containing the ciphered message we entered (marked in red in the next picture). Notice that the default.db doesn’t exist right after the app is installed. This shows how important it is to use the app a little before analyzing it in search for bugs:

*Interaction with the SQLite database*

From the table we have the three following suspicious strings, to the right of the name of the user who created it:

## Get Antonio Lara’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

*XAc860TQ62HaVTjOGV5egywXXWS0hUc6yOR/0eu5aQM=
bq3G0iIKEKfb4bJcqvpsziaHZLEsEZfzxRY21d9yV3g=
vEpr9q0DVMSbe7pDyqz7TtjWEhxZZ03uDcksStPArvo=*

They seem encrypted, presumably with the same algorithm that the app uses. It represents some leftovers that a lazy admin could have left there for testing. Or they could be there because a test version of the app was obtained before it was fixed for production.

If the strings are really AES encrypted, we need the key to decrypt it. To find it, some more enumeration is necessary. The app can be decompiled, and the manifest examined, with tools like apktool (apktool d kryptonite.apk) or jadx-gui.
The manifest.xml file contains information about the structure and configuration of the app. If the .apk file is simply extracted, this file is encoded and not visible, but the aforementioned tools decode it. The manifest file in jadx-gui shows this:

Marked in red are the activities (that is, the different “windows” contained in the app). MainActivity is the starting point of any app. There is the H1dD3n activity. The app has been created so that this activity can’t be accessed by any means from the MainActivity window. Again, this could represent some leftover activity forgotten by a lazy admin in a complex app. We can open any activity if we know its name, regardless of how it can be accessed in a legitimate way. To do this, we again access the phone shell with “adb shell”

and from there, we run this command:

Notice that a new activity has opened on the emulator. The am command is the activity manager, and with am start we can open activities by providing the app name (as shown in the /data/data directory) and the activity name (pay attention to the “ . ” preceding the activity name, it’s not part of the name, and must be there.

Although it may not look like it, the image at the top of the activity is actually a button. Don’t forget to click/tap everywhere so you don’t miss anything. Tapping on it shows a toast message:

This message gives a hint to check the logs. It’s also a good idea to check the logs in real world applications, important debugging info can be found there among the huge amount of messages.
In this case this is shown when tapping the button (check the logs, and keep them open to see the real time updates with the command adb logcat from outside the phone shell):

To continue with the kryptonite thematic of the challenge, when the krypton element is displayed in a list of gases, an error occurs (everything is hardcoded, no real error is happening). A suspicious string is displayed:

*KrYp70N1t3_k1LLz_$uPerM4N&H4ck3R*

With this string and a bit of imagination we can imagine that it’s the decryption key for the three strings found on the database previously:

Decryption gives:

Ciphertext: XAc860TQ62HaVTjOGV5egywXXWS0hUc6yOR/0eu5aQM=

Plaintext: Pl4N37_kRYp70N_X-P70d3d

……….

Ciphertext: bq3G0iIKEKfb4bJcqvpsziaHZLEsEZfzxRY21d9yV3g=

Plaintext: (%)KrYpT0NyT3_4_L1F3~

………

Ciphertext: vEpr9q0DVMSbe7pDyqz7TtjWEhxZZ03uDcksStPArvo=

Plaintext: #36kRyPtoN_GaZ_4_LuNCH?@

Finally, the text in the H1dD3n activity is the encrypted flag. It’s been split in chunks and presented as images to discourage the use of commands like strings and grep, and to force to dig deeper and understand the structure of android apps. However, careful examination of the resources and the source code could still allow to retrieve the images, but this is the intended path, spawning the hidden activity with the activity manager. After typing the message in the hidden activity (being careful to try lowercase “L” or uppercase “i” in the one occurrence that there is):

OUSRuRRH
NCtyyvHM
Qq3G+9QC
E0z+tuHB
/bWq8EZG
3YGg/4H1
uflzq1Nz
T2faKtMy

Rewriting it in one line and decrypting it with the third plain text
password found in the previous step retrieves the flag:

*Final flag*

---
