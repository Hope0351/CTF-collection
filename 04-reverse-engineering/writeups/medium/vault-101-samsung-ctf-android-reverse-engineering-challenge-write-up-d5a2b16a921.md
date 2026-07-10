# :arrows_counterclockwise: Vault 101 Samsung Ctf Android Reverse Engineering Challenge Write Up D5A2B16A921

> **Original Source:** [Vault 101 Samsung Ctf Android Reverse Engineering Challenge Write Up D5A2B16A921](https://infosecwriteups.com/vault-101-samsung-ctf-android-reverse-engineering-challenge-write-up-d5a2b16a9212)
> **Platform:** infosecwriteups.com | **Category:** `REVERSE ENGINEERING`

---

## Background


Without wasting much of your time and rushing towards *good stuff,* here’s some basic info. about Samsung’s virtual CTF event “Hacker’s Playground 2020”.

>

Challenge : Find the password.


File given : Vault101–1.1-release.apk


Obfuscation Level = High


Number of Solves = 15


Now the good stuff.

## Application Analysis


In the challenge we get one apk file which you can download from [HERE](https://github.com/FrigidSec/CTFWriteups/blob/master/SCTF/Vault101/_docs/challengeApp/Vault101-1.1-release.apk).


As the first step of our static analysis process we will de-compile the application using JADX. you can do this via tool on your computer or you can use any of the [web-based services](http://www.javadecompilers.com/apk) available.


After we get the Decompiled version of the application let’s start.

### Finding Main class


You might generally see something like this when the application is de-compiled, so we will follow the most common location for main activity.


And we have something promising here. Let’s open MainActivity.java and check.


In the above code we can see that this prominent part of code is responsible for showing GOOD or BAD message:

>

boolean a2 = *this*.s.a(*this*.p.getText().toString());


Toast toast = new Toast(*this*);


toast.setView(getLayoutInflater().inflate(a2 ? R.layout.toast_success_layout : R.layout.toast_fail_layout, (ViewGroup) findViewById(R.id.custom_toast_container)));


So now we know that we need to get “true” Boolean from “s.a()” function to get GOOD toast.


Also notice that “s.a” is actually “public volatile b.c.a.b” so we need to navigate to this class which will be available in respective folders , so let’s go there :


Let’s have a look at a.java in the same package:


Now this class is highly obfuscated and we just see that this is sending some gibberish data to `c.java's d() function`


Tracing all the classes in similar manner we get the following information

>

`1. c.java is performing some kind of string manipulation`


`2. a.java is sending encoded function names to call and getting result from c.java`


`3. we need to reconstruct function names by reversing the gibberish names via c.d()`


## Understanding Encryption and De-Obfuscation


Let’s have a look at c.java


We don’t need to reverse it as this is the function used to normalise the function calls.


So check this I implemented the same function in my java program :


```
public static int *INTGET*=1;

public static char a(char c, int i) {
return (char) (c & ((1 << i) ^ 65535));
}
public static char b(char c, int i) {
return (char) (c | (1 << i));
}
public static char c(char c, int i) {
return (char) ((c & (1 << i)) >> i);
}
public static String d(CharSequence charSequence, int i) {
StringBuilder sb = new StringBuilder();
if (i == 0) {
return sb.toString();
}
for (int i2 = 0; i2 < charSequence.length(); i2++) {
char charAt = charSequence.charAt(i2);
char c = (char) (i >> (i2 % 4));
int i3 = i2 % 3;
if (i3 == 0) {
for (int i4 = 0; i4 < 8; i4 += 2) {
char c2 = (char) (*c*(charAt, i4) ^ *c*(c, i4));
if (c2 == 0) {
charAt = *a*(charAt, i4);
} else if (c2 == 1) {
charAt = *b*(charAt, i4);
}
}
} else if (i3 == 1) {
for (int i5 = 1; i5 < 8; i5 += 2) {
char c3 = (char) (*c*(charAt, i5) ^ *c*(c, i5));
if (c3 == 0) {
charAt = *a*(charAt, i5);
} else if (c3 == 1) {
charAt = *b*(charAt, i5);
}
}
} else if (i3 == 2) {
for (int i6 = 0; i6 < 8; i6++) {
char c4 = (char) (*c*(charAt, i6) ^ *c*(c, i6));
if (c4 == 0) {
charAt = *a*(charAt, i6);
} else if (c4 == 1) {
charAt = *b*(charAt, i6);
}
}
}
sb.append((char) (charAt ^ *INTGET*));
}
return sb.toString();
}
```


Now if we will pass the arguments to the function we will see that they are being converted into android keywords.


## Get Saket Upadhyay’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


For example :


This is in a.java :

---

*Originally published on [Medium](https://infosecwriteups.com/vault-101-samsung-ctf-android-reverse-engineering-challenge-write-up-d5a2b16a9212). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of reverse engineering CTF writeups.*
