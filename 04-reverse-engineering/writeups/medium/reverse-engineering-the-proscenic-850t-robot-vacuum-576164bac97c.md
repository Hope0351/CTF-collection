# :arrows_counterclockwise: Reverse Engineering The Proscenic 850T Robot Vacuum 576164Bac97C

> **Original Source:** [Reverse Engineering The Proscenic 850T Robot Vacuum 576164Bac97C](https://infosecwriteups.com/reverse-engineering-the-proscenic-850t-robot-vacuum-576164bac97c)
> **Platform:** infosecwriteups.com | **Category:** `REVERSE ENGINEERING`

---

What initially looked like a simple home automation project turned into a full Reverse Engineering Session: a rooted Android emulator, Frida, JNI method hooking, HTTPS traffic interception, and the discovery that behind the Proscenic brand lies the Tuya ecosystem, complete with hardcoded credentials baked into the app code.

>

This article documents the whole journey: from the original frustration to a fully local control webapp, no cloud, no proprietary app required.


## 1. The Problem: a Broken Virtual Remote


The Proscenic 850T is a mid-range robot vacuum with WiFi connectivity. The official app lets you control it remotely, set cleaning modes, schedule sessions, and use a virtual directional remote alongside the physical infrared remote.


The virtual remote’s problem is structural: every directional command (forward, backward, turn left, turn right) is processed synchronously by the robot. The app sends a command, waits for the robot to finish executing it, then unlocks the interface. The result is that to turn while moving forward, you have to wait for the robot to complete the current movement first.


For normal use this is bearable. For anyone who wants to steer the robot in real time through tight corridors or around obstacles, it’s completely unusable (*I’ll mount them on an ESP32-CAM soon*).


I actually opened a support ticket with Proscenic about this issue. Their reply was the usual:

>

“Thank you for choosing us, we’ll pass this along to the development team.”


>

…As of today, nothing has changed.


*It’s so annoying*


But there was a second reason, perhaps more important: the Cloud. The Proscenic app requires an account, sends data to the company’s servers, and stops working if the internet connection drops. I wanted full local control , no dependency on third-party servers that could change their policies, deprecate my model, or simply disappear.

## 2. Under the Hood: It’s Tuya All the Way Down


The first surprise comes immediately when inspecting the app’s network traffic. All API calls go to a1.tuyaeu.com and appeu.proscenic.com. Proscenic uses Tuya as its IoT backend, a common pattern among smart device manufacturers in this price range.


*Burp Proxy Intercept*


Tuya is a Chinese IoT platform that provides cloud infrastructure, SDKs and firmware for smart devices. Manufacturers like Proscenic buy a white-label solution, slap their brand on top, but everything underneath runs on Tuya.


This matters for two reasons:


- There is already a mature ecosystem of tools for local control of Tuya devices, the most popular being TinyTuya

- The local protocol uses AES-128 with a per-device key called the localKey


The catch is that Proscenic uses a separate Tuya OEM cloud, not the standard one. Proscenic devices don’t appear in the normal Tuya developer portal, and the app doesn’t use a Smart Life account. So we can’t retrieve the localKey through official channels, unless we disconnect the robot from the Proscenic app and re-pair it via Smart Life (which I didn’t want to do, since the Proscenic app offers more complete functionality, like generating a floor map during cleaning).

>

So to use it locally, we need to extract the localKey from the app!!


## 3. Setup: LDPlayer, Burp Suite, ADB and Frida


To reverse engineer the Android app on a Windows PC I used:


• *LDPlayer 9 — Android emulator with native root support• ADB (Android Debug Bridge) — to communicate with the emulator from Windows• Frida 17.8.3 — dynamic instrumentation framework• frida-server-17.8.3-android-x86_64 — the Frida server running inside the emulator*


- *Burp Suite — to intercept HTTPS traffic*

### 3.1 LDPlayer Configuration


*Your virtual Android friend LDPlayer*


LDPlayer has a crucial feature: under Settings → Disk → System disk setting, selecting Writable mounts the system partition in read/write mode. This eliminates all the mount -o remount,rw /system headaches that emulators like BlueStacks cause.


*LDPLayer Disk Settings*


With root enabled, pushing frida-server and installing the Burp Suite CA certificate become trivial operations.

>

*Let me know in the comments if you’d like a detailed step-by-step guide for these, if there’s enough interest I’ll write a dedicated article.*


### 3.2 Frida: Client-Server Architecture


*Your best friend for inspecting Android Apps*


Frida works in client-server mode: frida-server runs inside the Android emulator with root privileges and listens on port 27042. The client (frida-tools) runs on the Windows host and connects via ADB port forwarding:


```
adb -s emulator-555X forward tcp:27042 tcp:27042
```


Once connected, we can inspect and modify any process running on the emulator in real time, no need to modify or recompile the APK.

## 4. Extracting the localKey with Frida


*Frida Setup*

### 4.1 Class Enumeration


The first step is understanding the app’s internal structure. With Frida we can enumerate all Java classes loaded in memory by the Proscenic process:


```
Java.perform(() => {
Java.enumerateLoadedClassesSync()
.filter(c => c.toLowerCase().includes('cipher') ||
c.toLowerCase().includes('encrypt') ||
c.toLowerCase().includes('secret') ||
c.toLowerCase().includes('aes'))
.forEach(c => console.log(c));
});
```


The result immediately reveals the structure: *The app is built using the Tuya Smart App SDK, referencing the *`*thingclips*`*namespace in its source code due to *[Tuya's library restructuring](https://developer.tuya.com/en/docs/app-development/migration_guide?id=Kci3zqm3wlcut)*. At the same time, the app leverages Tuya’s OEM solutions to provide a fully customized, white-label smart home experience.*


*Thingclips Classes*


Among the interesting classes:


- com.thingclips.smart.sdk.bean.DeviceBean

### 4.2 The Breakthrough: DeviceBean


Instead of trying to intercept the encryption methods (which turn out to be implemented in native JNI code, difficult to hook), the most elegant solution is to read the already-decrypted data directly from the DeviceBean object in memory.


## Get Gianluca Palma’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Inspecting the class fields:


```
Java.perform(() => {
const DeviceBean = Java.use('com.thingclips.smart.sdk.bean.DeviceBean');
DeviceBean.class.getDeclaredFields()
.forEach(f => console.log(f.toString()));
});
```


We find exactly what we’re looking for:


```
public java.lang.String com.thingclips.smart.sdk.bean.DeviceBean.localKey
public java.lang.String com.thingclips.smart.sdk.bean.DeviceBean.devId
private java.lang.String com.thingclips.smart.sdk.bean.DeviceBean.ip
```


*DeviceBean localKey Field Objects*

### 4.3 Reading Directly from the Cache


After several Frida hooks, I found that devices are cached through [IThingHomeDataManager](https://tuya.github.io/tuya-home-android-sdk-api-reference/com/thingclips/smart/home/sdk/api/IThingHomeDataManager.html). We can read the full list and print each device’s data:


```
Java.perform(() => {
const HomeSdk = Java.use('com.thingclips.smart.home.sdk.ThingHomeSdk');
const DRB = Java.use('com.thingclips.smart.interior.device.bean.DeviceRespBean');
const dataInstance = HomeSdk.getDataInstance();
const devList = dataInstance.getDevRespBeanList();
for (let i = 0; i < devList.size(); i++) {
const d = Java.cast(devList.get(i), DRB);
console.log('name: ' + d.getName());
console.log('devId: ' + d.getDevId());
console.log('localKey: ' + d.getLocalKey());
console.log('ip: ' + d.getIp());
}
});
```


### *Finally, I successfully extracted the localKey…*


*localKey Extraction*

## 5. Bonus: Hardcoded Keys in BuildConfig


Analysing the APK with jadx (Java decompiler), inside com.app.robot.BuildConfig we find hardcoded Tuya credentials:


*Hardcoded Tuya credentials*


These are the appKey and secret used to sign calls to a1.tuyaeu.com. With Burp Suite we can intercept all API traffic to Proscenic and Tuya servers, including OTA firmware update requests.


By hooking OkHttp with Frida we can intercept Proscenic API responses in plaintext, the appeu.proscenic.com endpoints return unencrypted JSON, including the full product list with their Tuya productKey values, staging/UAT endpoint URLs and session credentials.

### 5.1 One detail worth noting: Umeng Analytics


Beyond the Tuya and Google Maps keys, the BuildConfig also contains a pair of Umeng_Appkey / Umeng_Message_Secret values. Umeng is a Chinese mobile analytics SDK widely used in Android and iOS apps, it collects usage statistics, crash reports and user session data, sending them to servers in China.


Anyone who buys a Proscenic device probably has no idea that the app is sending behavioural data to Chinese infrastructure every time it’s opened. This isn’t a backdoor, it isn’t an attack, it’s simply undisclosed third-party telemetry, an unfortunately common pattern in the consumer IoT ecosystem.

>

From a privacy standpoint, it’s worth knowing. From a security researcher’s perspective, it’s yet another reminder that decompiling the APK of a device you own is always an instructive exercise…


## 6. Local Control with TinyTuya


With devId and localKey in hand, local control is immediate. TinyTuya communicates directly with the device on port 6668 UDP/TCP using the Tuya local protocol with AES-128 encryption:


```
import tinytuya

d = tinytuya.Device(
dev_id = 'XXXXXXXXXXXXXXXXX',
address = '10.10.x.x',
local_key= '*',
version = 3.3
)

d.set_value(26, 'forward') # move forward
time.sleep(2)
d.set_value(26, 'turnright') # turn right
time.sleep(1)
d.set_value(26, 'stop') # stop
```


The most interesting finding: directional commands work in rapid sequence with no issues. The robot processes them immediately, with none of the timeouts of the official app.

>

The remote control “bug” was in the App, not in the robot.


## 7. Full Data Points Mapping


Tuya devices communicate through Data Points (DPs), key-value pairs that represent each device feature. The complete mapping for the Proscenic 850T was assembled from three sources:


- *Frida hooking of commands sent by the app during remote control use*

- By setting up a passive socket to capture real-time status updates and commands sent by the mobile app to the device, below:


```
import tinytuya
import time

d = tinytuya.Device(
dev_id="xxxxxxxxxxxxxxxxxxxxx",
address="10.10.x.x",
local_key="",
version=3.3
)
d.set_socketTimeout(5)

print("Listen...")
while True:
try:
data = d.receive()
if data:
print("Data:", data)
except Exception as e:
print("Error:", e)
time.sleep(1)
```


- *Analysis of the device model JSON retrieved from the Tuya APIs*

- *Chinese technical DP documentation found on *[GitHub](https://github.com/make-all/tuya-local/issues/3647)* issues*

### Control Data Points:


### Status Data Points:


### Accessory Reset Data Points:


## 8. The Control Webapp


The final result, built during a Python/Flask + HTML/JS session with my dear friend [Claude.AI](https://claude.ai), is a webapp that provides:


- *Directional remote control via keyboard (arrow keys) and touch*

- *Smart START/STOP: sends DP 25 = smart when the robot is idle, DP 33 = false when it’s working*

- *Cleaning mode selection with automatic Mop button lockout when the water tank isn’t installed (DP 49)*

- *Suction power control with active level highlighting*

- *Water flow control (visible only when the mop tank is detected)*

- *Accessory wear bars with one-click reset*

- *Animated fault banner for DP 11 errors*

- *Info balloon with IP, Device ID, Product Key and Serial on hover*

- *Automatic polling every 5 seconds, zero cloud dependency*


*WebApp — Finally I can move my robot freely!*

## Conclusions


This project started from a practical frustration and became a reverse engineering exercise that reveals how the consumer IoT ecosystem really works.


Key takeaways:


- Tuya is everywhere. Dozens of different brands, Proscenic, Gosund, Teckin, Merkury and many others, run on the same infrastructure. The techniques described here apply to any Tuya OEM device.

- Hardcoded credentials are the norm. AppKey, secret and staging URLs baked into the APK are practically guaranteed on any IoT mobile app. jadx is your friend.

- Frida makes Android app reverse engineering accessible. No need to modify the APK, no need for a physically rooted device. An emulator with root and frida-server is enough to inspect any app in real time.

- Local control is always achievable. If the device supports direct WiFi communication, with the right key you can eliminate the cloud dependency entirely.

---

*Originally published on [Medium](https://infosecwriteups.com/reverse-engineering-the-proscenic-850t-robot-vacuum-576164bac97c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of reverse engineering CTF writeups.*
