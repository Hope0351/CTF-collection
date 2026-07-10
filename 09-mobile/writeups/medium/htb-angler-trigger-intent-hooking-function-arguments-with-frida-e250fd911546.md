# :mobile_phone: HTB | Angler — trigger intent & hooking function arguments with Frida

> **Original Source:** [HTB | Angler — trigger intent & hooking function arguments with Frida](https://infosecwriteups.com/htb-angler-trigger-intent-hooking-function-arguments-with-frida-e250fd911546)
> **Platform:** infosecwriteups.com | **Category:** `MOBILE`

---

# HTB | Angler — trigger intent & hooking function arguments with Frida


You can find the machine [here](https://app.hackthebox.com/challenges/Angler/)


You can watch the video walkthrough [here](https://youtu.be/mkYSboMeyGc).


Skill Learned


- Learn how to trigger BATTERY_LOW events.

- Become more experienced in hooking function arguments with Frida.

## Enumeration


## Running the application


*application*


From the application, it looks like it is a one-page app, and 100% maybe indicating battery (?)

## Triggering LOW_Battery Intent


On analysing the code via jadax we can see registered event “android.intent.action.BATTERY_LOW”


But to invoke this intent, we have broadcast the data along with it.

>

*Android has *[intent action](http://developer.android.com/guide/topics/security/permissions.html)* for broadcast receiver. *[BroadCast receiver](http://developer.android.com/reference/android/content/BroadcastReceiver.html#)* will be trigger when it listen any action which registered within it.*


To call this Intent, we will use `adb`


```
PS D:\htb\Angler> adb shell am broadcast -a "android.intent.action.BATTERY_LOW" --es "Is_on" "yes"
```


where,


- am: for activity manager

- broadcast: for sending a broadcast message

- a: for intent action

- es: for an extra of type string.


This will trigger the intent and display the screen below


We can see a toast `Look me inside` (logs ?)


Let’s go to logcat and see the logs for `com.example.angler` and we can see `I am not here, I am there` (there means code ?)


## Decompiling the library


On checking the code, we found the native library being loaded


```
static {
System.loadLibrary("angler");
}
```


- This is a static block, executed when the class is loaded.

- `System.loadLibrary("angler")` loads a native shared library (e.g., `libangler.so` on Linux, `angler.dll` on Windows, or `libangler.dylib` on macOS).

- The name passed does not include the `lib` prefix or file extension; the JVM handles that based on the OS.


We found the `libangler.so` in Resources/lib/x86_64/


We can disassemble this library file using a tool called Ghidra. We have to mind that about the architecture of the device, the app is installed when we disassemble it. Then we discover where that method is implemented.


## Get anuragtaparia’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


We can see that `getInfo()` is calling two functions `illusion` and `ne`


illusion


In this, we can see the initial value of the flag (which is obvious since it is called first)


ne


In the below code, there is a string that was discovered before in the logcat, and there is another string which says `You found the flag`. These two strings are returned after strcmp. We can try to hook this up with Frida and see the copied string


## Exploitation using Frida


Our next step is to figure out what the strings are being compared in the above code.


In order to achieve this, we need to hook on strcmp function, but there are two challenges here:


- One, we need to make sure the strcmp is the actual name of the function being imported.

- Two which is the main problem here is how we can hook into a native method that is not being declared in the Java Code.


To solve the first challenge, we can simply list the exports and the imports of the shared object.


```
[Android Emulator 5554::Angler ]-> Module.enumerateExports("libangler.so")
```


```
[Android Emulator 5554::Angler ]-> Module.enumerateImports("libangler.so")
```


but the above output is so big that I was unable to get the full content. We can use below JS for copying the content into a text file


```
//for Export
// Enumerate the exports of libangler.so module and print the JSON
Module.enumerateExports("libangler.so", {
onMatch: function (exp) {
// Directly print the export details in JSON format
console.log(
JSON.stringify({
name: exp.name,
address: exp.address.toString(),
type: exp.type,
})
);
},
onComplete: function () {
console.log("Enumeration Complete");
},
});
```


```
//for Imports
// Enumerate the Import of libangler.so module and print the JSON
Module.enumerateImports("libangler.so", {
onMatch: function (exp) {
// Directly print the export details in JSON format
console.log(
JSON.stringify({
name: exp.name,
address: exp.address.toString(),
type: exp.type,
})
);
},
onComplete: function () {
console.log("Enumeration Complete");
},
});
```


Run the below command to extract the information


```
PS D:\htb\Angler> frida -U Angler -l .\Module_exports.js | tee output_export.json
PS D:\htb\Angler> frida -U Angler -l .\Module_imports.js | tee output_import.json
```


We found `strcmp` in Imports


```
{"name":"strcmp","address":"0x793e9a463820","type":"function"}
```


Now all that is left is to figure out a way to hook and monitor the native library methods.


Since we found the imported `strcmp` address in `libangler.so`, and the flag is being passed as the second argument (`args[1]`) to `strcmp`


Let’s write a Frida script that hooks that specific import, logs only when `strcmp` is called from `libangler.so`, and prints the second argument, which should be the flag.


```
// Replace this with the exact import address of strcmp in your lib
var strcmpAddr = ptr("0x793e9a463820");
Interceptor.attach(strcmpAddr, {
onEnter: function (args) {
try {
var str1 = Memory.readUtf8String(args[0]);
var str2 = Memory.readUtf8String(args[1]);
console.log("[*] strcmp called");
console.log(" Arg1: " + str1);
console.log(" Arg2: " + str2); // ← Likely the flag
} catch (err) {
console.log("Error reading strcmp args:", err);
}
}
});
```


Now we need to run the Frida, and then we need to trigger the broadcast receiver that will trigger getInfo(), that will trigger ne(), that will trigger strcmp.


```
//run Frida
PS D:\htb\Angler> frida -U Angler -l .\flag_script.js
```


```
//trigger the broadcast
PS D:\Andriod_Studio\testapp> adb shell am broadcast -a "android.intent.action.BATTERY_LOW" --es "Is_on" "yes"
Broadcasting: Intent { act=android.intent.action.BATTERY_LOW flg=0x400000 (has extras) }
Broadcast completed: result=0
PS D:\Andriod_Studio\testapp>
```


And we got the flag (need to [convert](https://www.rapidtables.com/convert/number/hex-to-ascii.html) the hexadecimal to text)


---

*Originally published on [Medium](https://infosecwriteups.com/htb-angler-trigger-intent-hooking-function-arguments-with-frida-e250fd911546). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of mobile CTF writeups.*
