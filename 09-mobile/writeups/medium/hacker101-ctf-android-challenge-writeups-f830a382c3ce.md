# :mobile_phone: Hacker101 CTF: Android Challenge Writeups

---

## Intentional Exercise (Moderate, 1 Flag)

Following a similar approach as seen in the previous challenge, I installed the application using ADB and generated a static analysis report of the APK file using MobSF. Opening the application showed an activity with a welcome message and a link called “Flag”*.*

Clicking on the link leads to a “Invalid request” error. Guess it won’t be that easy 😏.

As seen with the previous challenge, I started by looking at the manifest file for the application. There is only one activity declared in the manifest file. What standouts about the activity, is that it has been declared with three intent filters. The two intent filters surrounded by green in the image below shows how you create a deep links for your app’s content (see references).

>

N.B. Deep Links are a concept that help users navigate between the web and applications. They are basically URLs which navigate users directly to the specific content in applications.

To test the first deep link (i.e. http), I can use ADB with the activity manager (am) tool to test that the intent filter URI’s specified for deep linking resolve to the correct app activity. The command seen below successfully starts the main activity for the application.

```
adb shell am start -W -a "android.intent.action.VIEW" -d "http://level13.hacker101.com" com.hacker101.level13
```

I decided to look at the source code for the *MainActivity. *Looking through the java code, I can see that the application creates a WebView. Two string variables are also declared, with the variable *str* containing a hardcoded URL.

>

N.B. The URL for your application will be different.

Entering this URL into a browser brings up the same page seen earlier in the application’s main activity.

Clicking the Flag link still returns an invalid request.

Looking at the source code again, I saw that the application retrieved the data stored in the intent used to launch the main activity. Examining the manifest file from earlier, I know that this data is the http://level13.hacker101.comURL. The application then proceeds to use the java subString(28) method to ignore the first 28 characters (i.e. *http://level13.hacker101.com* URL) in the data string retrieved from the intent and appends the remaining string value in the str2 variable with the hardcoded URL link string in the str variable. The application then checks if the string contains a “?*”* and adds it to the end of the string if it does not.

I do not know what the value of str2is yet based on my static analysis thus far. The final value of str so far is a combination of the hardcoded URL link, the the str2value (Which at this point is just an empty string) and the “?” at the end of the string.

```
http://34.74.105.127/398abac4c8/appRoot'empty str2 value'?
```

The final block of code consists of creating a message digest using the SHA-256 hashing algorithm. The hash is updated twice. The first is with a key called s00p3rs3c3rtk3yand the second is with thestr2value*. *The WebView will then load a newly constructed URL which includes the strvalue (i.e.URL), the string “&hash” and the SHA-256 hash value.

The final constructed URL so far can be seen below:

```
http://34.94.3.143/398abac4c8/appRoot'emptystr2 value'?&hash="hash value"
```

Using a tool called BurpSuite, I can intercept the request made by the application when it is launched and observe the URL that is constructed by the *MainActivity* source code.

Looking at the host value and GET request made by the application, I can see the full URL.

```
http://35.227.24.107/3ef212b832/appRoot?&hash=61f4518d...etc
```

>

N.B. The number value in the URL (i.e. 3ef212b832) has changed due to me downloading a new version of the app.

Entering this value into the URL will still just bring me to the default WebView with a link to get the flag. I know that this link is used to get the flag somehow and by looking at the page source for the link, I can see that it uses /flagBearer as part of the URL address. This is placed right after appRoot and could be the missing str2 value.

If I add /flagBearer to where the missing str2 value should be, I have the following URL path.

```
http://35.227.24.107/3ef212b832/appRoot/flagBearer?&hash=61f4518d...etc
```

Entering this URL path into my browser presents a new error message which says “Invalid hash*”.*

This means that /flagBearer is the unknown str2 value and can be confirmed by typing other values in it’s place, which results in a Not Found error.

Despite having the correct URL path, I am stilled presented with a hash error. As seen earlier while statically analyzing the *MainActivity* source code, the str2 value (i.e. */flagBearer*) is used with the key s00p3rs3c3rtk3yto make up the full SHA-256 hash. However, since the data URL path specified in the intent filter (i.e. *http://level13.hacker101.com*) does not contain the string /flagBearer and is completely ignored by the the java subString(28) method, the str2value is left empty. This means the hash is incorrect since there is no value present in str2 (i.e. */flagBearer*).

## Get Hacktivities’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

This is where the deep links come into play. After reading an article titled “*The Zaheck of Android Deep Links!*” (see references), I learnt that if there is insufficient URL validation being carried out then I can load my own arbitrary URL.I know that no URL validation is being performed on the URL used to trigger the intent filter and launch the application’s Main Activity. This means I can provide my own URL with the /flagBearerpath attached, which will launch the Main Activity and result in the str2 value being equal to /flagBearer*. *I can accomplish this by using ADB, as seen previously above when testing the intent filter URI’s.

```
adb shell am start -W -a "android.intent.action.VIEW" -d "http://level13.hacker101.com/flagBearer" com.hacker101.level13
```

This results in the flag being presented 😄.

Another approach to solve this challenge without using the deep link is to simply create the hashyourself by combining the key s00p3rs3c3rtk3yand the /flagBearer string. I used an online tool called CyberChef to create the SHA-256 hash.

I then added this new hash to my URL path, giving me the flag.

---
