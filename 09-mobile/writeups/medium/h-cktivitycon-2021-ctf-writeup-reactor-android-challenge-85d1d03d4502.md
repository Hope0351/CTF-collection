# :mobile_phone: h@cktivitycon 2021 CTF writeup: Reactor Android Challenge

> **Original Source:** [h@cktivitycon 2021 CTF writeup: Reactor Android Challenge](https://infosecwriteups.com/h-cktivitycon-2021-ctf-writeup-reactor-android-challenge-85d1d03d4502)
> **Platform:** infosecwriteups.com | **Category:** `MOBILE` | **Year:** 2021

---

# h@cktivitycon 2021 CTF writeup: Reactor Android Challenge


Hey there, hosted h@activitycon 2021 CTF a few weeks back. I got time to play around with a few challenges. Here is the write-up about the Reactor challenge.

## The challenge


The challenge says “We built this app to protect the reactor codes” & the flag format is flag{xxxxxx}


Let’s download & install the reactor.apk


The application is expecting 4 digits numeric code.


I entered 1111 pin to observe the output. The app responded with some unreadable characters. So, 1111 is not the correct pin.


We’ll have to look at the source code to understand the logic. Our next step is to open the APK using jadx-gui.


Let’s navigate to com > reactor > MainActivity


There is only one method(not usual) which returns the string “Reactor”. If we look at the imported packages we can conclude that the app is built with [React Native](https://reactnative.dev/) technology.


The presence of React Native libraries suggests that the application logic should have been written in the javascript files.


The location of the JS file is at assets/index.android.bundle


index.android.bundle file was both obfuscated and minified. I un-minified the JS file to have a better look at the content.


I decompiled the app using `apktool d reactor.apk` command and opened the index.android.bundle file.


Next, I searched for the “Insert the pin” text and I found the occurrence. The application is creating a text element and the content is “Insert the pin to show the reactor codes.”


The same message we got when we launched the application.


One thing that got my attention was the onSubmitEditing function.


The above method is taking user input t.nativeEvent.text and if the value is matching with the correct pin it will print the flag.


Let’s confirm if this method is being called when we enter the pin. To accomplish this, I added a `console.log("Debugger hit!");` in statement above method c().


We have made changes to the JS file, now we need to rebuild the application using the following command.


`apktool b reactor`


The application needs to be resigned before we can install it. I resigned the app using the command `apksigner sign --ks /home/jaimin/jaimin.keystore reactor.apk`


The app(modified) is now ready to be installed. Using command `adb install reactor.apk`


Before we interact with the application we need to open the logcat of the android device. To do that use the command `adb logcat`


I kept logcat window open and entered 0000 pin to observe if our debugger is hit.


## The logcat window


Yes, I was on the right path.


## Get Jaimin Gohel’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Previously added value(Debugger hit!) in the JS is being printed in the logs.

## back to index.android.bundle


I searched for occurrences of “decrypt” keyword in the JS file and found an interesting method.


I added the following line to print the decrypted values in the console.


console.log(“Decrypted value: “+o(c, t.default.decode(n)));


Let’s rebuild, resign and re-install


I have added all three commands in `build.sh` for a quicker process.


Open the app & enter 0000 pin.


## Navigating back to logcat


In the logcat we have the same value printed as in the application and it states that the 0000 is not the correct pin.


Now there can be a lot of ways to solve this challenge, I decided to brute-force the PIN by adding the following code in the onSubmitEditing method.

## Before


## After


I added a for loop to brute force the pin from 0000 to 9999.


I tweaked the decrypt method as well to print the entered pin and decrypted values.

## Before


## After


Let’s rebuild, resign and re-install the APK.


Entered any random pin and headed straight to the logcat.


## Bruteforcer in action


The logcat has all the values printed, we can simply grep for flag{ keyword now.


The correct pin was 5927 and flag value was flag{cfbb4c6ec59ce316e8d7644ac4c70a12}

## Challenge solved!


I enjoyed writing this article and I hope that you enjoyed reading it too.


Stay safe, Happy hacking :-)


Twitter: [@jaimin_gohel](https://twitter.com/jaimin_gohel)
LinkedIn: [@jaimin-gohel-440a4a52](https://www.linkedin.com/in/jaimin-gohel-440a4a52)

---

*Originally published on [Medium](https://infosecwriteups.com/h-cktivitycon-2021-ctf-writeup-reactor-android-challenge-85d1d03d4502). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of mobile CTF writeups.*
