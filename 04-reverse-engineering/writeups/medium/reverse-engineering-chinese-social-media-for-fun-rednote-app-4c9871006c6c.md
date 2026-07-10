# :arrows_counterclockwise: Reverse Engineering Chinese Social Media for Fun (REDNote App)

> **Original Source:** [Reverse Engineering Chinese Social Media for Fun (REDNote App)](https://infosecwriteups.com/reverse-engineering-chinese-social-media-for-fun-rednote-app-4c9871006c6c)
> **Platform:** infosecwriteups.com | **Category:** `REVERSE ENGINEERING`

---

# Reverse Engineering Chinese Social Media for Fun (REDNote App)


*Reverse Engineering — REDnote Android*


I’ve taken some time to perform this analysis since there was some expressions on social-media about the Data Privacy concerns of the REDNote (小红书) app.


Its no surprise that this would be a concern of people across the world given the “location of management” and the lack of immediate translation into certain features of the app at the early date of some TikTok users migrating.


*REMnux: A Linux Toolkit for Malware Analysis*


The analysis environment I’m using is the REMnux Malware Analysis OS within VMWare Workstation. I’m hopefully looking forward to using this for more analysis activities, but, here we are today.


Since my main mobile operating system (OS) is Android, I am paying attention to the Android Application (APK) file for the REDNote (小红书) app.

### Finding APK Files


I mainly use [APKPure](https://apkpure.com/rednote/com.xingin.xhs) or [APKMirror](https://www.apkmirror.com/apk/%E8%A1%8C%E5%90%9F%E4%BF%A1%E6%81%AF%E7%A7%91%E6%8A%80%E4%B8%8A%E6%B5%B7%E6%9C%89%E9%99%90%E5%85%AC%E5%8F%B8/%E5%B0%8F%E7%BA%A2%E4%B9%A6-%E4%BD%A0%E7%9A%84%E7%94%9F%E6%B4%BB%E6%8C%87%E5%8D%97/%E5%B0%8F%E7%BA%A2%E4%B9%A6-%E4%BD%A0%E7%9A%84%E7%94%9F%E6%B4%BB%E6%8C%87%E5%8D%97-8-59-1-release/) for finding APKs. Don’t expect to find “game hacks” and “jailbroken apps” there. To my knowledge, these platforms distribute normal APK copies.

### Let’s Start The Analysis


- “APK files are basically ZIP files”, said some stranger on the…

---

*Originally published on [Medium](https://infosecwriteups.com/reverse-engineering-chinese-social-media-for-fun-rednote-app-4c9871006c6c). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of reverse engineering CTF writeups.*
