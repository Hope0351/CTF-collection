# :mobile_phone: Trend Micro CTF 2020 - Keybox writeup | tatocaster

> **Original Source:** [Trend Micro CTF 2020 - Keybox writeup | tatocaster](https://tatocaster.medium.com/trend-micro-ctf-2020-keybox-writeup-cf5a69d2d091)
> **Platform:** tatocaster.medium.com | **Category:** `MOBILE` | **Year:** 2020

---

### Static Analysis


Almost all activities look the same, they wait for string data from the intent with the pattern “hintkey{0–4}”, if exists it will be set as singleton object’s property and executes javascript.


*Key1HintActivity decompiled*


We can continue reading the code but all the clues are in the AndroidManifest.xml — “Unlocking the hints requires sending the appropriate intent ….”


### Key 1


Above hint means that if we want to grab the key 1 we need the hint first for which we found the hint(LOL, hint for the hint) in the AndroidManifest.


Ok, but what is the password? Let's step back and think again, check the Singleton class. It is used in every activity `Singleton.getInstance()` Singleton class as the name suggests uses a singleton design pattern and has a private constructor hidden behind the static method “getInstance()”, constructor itself is very interesting.


*Singleton class*


It creates `ContextFactoryFactory` (yeah, Java developers love factories) and sets `hintkey0` and `hintkeymain` .


*ContextFactoryFactory class*


There is a `CreateKey` method which takes an integer argument but always returns the same value “TrendMicro”. Clearly calling CreateKey(0) and CreateKey(1) is a decoy. Looks like we have a password — “TrendMicro” because it is a hint for Key0HintActivity so it will work for other activities as well as the AndroidManifest states.


Let’s run a `adb` command to send the intent to unlock the first hint and it will start KEY1HintActivity.


```
adb shell am start -a com.trendmicro.keybox.UNLOCK_HINT -n com.trendmicro.keybox/.KEY1HintActivity -e hintkey1 TrendMicro
```


As the result, we read


```
Good job figuring out the password to the Key One hints!As you are aware, the password you used was 'TrendMicro'.Here is a hint about decrypting flagkey1.enc:
To unlock Key 1, you must call Trend Micro
```


Hmm, we need to call Trend Micro. Trend Micro — the company, owner of the CTF. From here it is manual work and pure guessing or we can automate this part. But too lazy to write decrypt script and try to call Trend Micro headquarters first. Turns out the Japanese HQ’s number is the right one — 81353343618. And we have a key 1.


```
adb shell am start -a android.intent.action.CALL -d tel:81353343618
```


### Key 2


After repeating the same intent with different extras to unlock the hint we get the message: To unlock KEY2, send the secret code. Secret code? sending? Back to the AndroidManifest. There is a BroadcastReceiver registered which gets filtered intent for telephony secret code, SMS receive/send and calls. Clearly, this broadcast was involved in the previous key because it catches CALL action, SMS and SECRET_CODES.


more about secret codes: [https://developer.android.com/reference/android/telephony/TelephonyManager#ACTION_SECRET_CODE](https://developer.android.com/reference/android/telephony/TelephonyManager#ACTION_SECRET_CODE)


AndroidManifest clearly states two codes but only one is working. If we take a close look on Unlocker broadcast receiver, in case of “8736364276” it creates gets Singleton instance and starts an activity again but if “8736364275” is received it will set a flag to singleton object and then will start the activity.


*Unlocker snippet*


Here is a tricky part: do you remember Singleton class with two public getInstance() methods? The second one is a decoy, creates a new instance, that's why entering “8736364276” will not work, singleton object is created again in the broadcast receiver and all of our previous progress will be lost. That’s a little bit of info what is under the hood and why the application may reset our progress. I should admit I really liked this application because there are several pitfalls where you can break a leg and in a real-life scenario, this will be more frustrating.


*Singleton class snippet*


Anyways here is an ADB command or another way of doing this via dialer is:


*#*#<code>#*#*


```
adb shell am broadcast -a android.provider.Telephony.SECRET_CODE "android_secret_code://8736364275/TrendMicro" -n com.trendmicro.keybox/.Unlocker
```


### Key 3


“Unlock KEY3 with the right text message”


AndroidManifest and broadcast receiver does not contain any code snippet for SMS handling. But if we search “sms” or “[content://sms](https://stackoverflow.com/questions/15352103/android-documentation-for-content-sms-type-values)” in Jadx we will find snippet in ContextFactoryFactory and then we can trace the variable from here. We will end up in Observer class which is a subclass of Android [ContentObserver](https://developer.android.com/reference/android/database/ContentObserver). This will be called for changes to content in this case SMS.


The most important part of the logic is that: SMS is stored in SQLite database in Android, it means it has standard columns like any other RDBMSs. This code iterates through the columns and matches the content of the SMS to the column name and type should be equal 1. type 1 is Inbox obviously from the official documentation [https://developer.android.com/reference/android/provider/Telephony.TextBasedSmsColumns#MESSAGE_TYPE_INBOX](https://developer.android.com/reference/android/provider/Telephony.TextBasedSmsColumns#MESSAGE_TYPE_INBOX).


We can send SMS from the emulator.


The column name that decrypted KEY3 turned out to be [“body”](https://developer.android.com/reference/android/provider/Telephony.TextBasedSmsColumns#BODY).

### Key 4


“Visit the headquarters to unlock Key 4”


I searched through the official website and Trend Micro has 3 headquarters: 1 in the USA, 1 in Canada and 1 in Japan.


Key 4 requires to not equal the longitude and latitude from the previous location we tried. Each new location change triggers new KEY4HintActivity and adds it to back stack. We need the correct sequence of visited locations to decrypt the key.


The fastest way is to search via a map which is built into Android emulator and save them as points.


Turns out correct sequence is: Japan -> Canada -> USA and the key is ours.

### Keys:


key 0 = KEY0–7135446200
key 1 = KEY1–1047645455
key 2 = KEY2–9517232028
key 3 = KEY3–2510789910
key 4 = KEY4–4721296569


So for the final flag, we need to combine all of them and send an intent action “UNLOCK_FLAG” as AndroidManifest states:


```
adb shell am start -a com.trendmicro.keybox.UNLOCK_FLAG -n com.trendmicro.keybox/.FlagActivity -e key0 "KEY0-7135446200" -e key1 "KEY1-1047645455" -e key2 "KEY2-9517232028" -e key3 "KEY3-2510789910" -e key4 "KEY4-4721296569"
```


*final flag*


The flag was: TMCTF{pzDbkfWGcE}


Happy hacking.

---

*Originally published on [Medium](https://tatocaster.medium.com/trend-micro-ctf-2020-keybox-writeup-cf5a69d2d091). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of mobile CTF writeups.*
