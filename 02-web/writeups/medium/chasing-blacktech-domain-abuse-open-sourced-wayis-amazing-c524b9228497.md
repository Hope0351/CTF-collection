# :globe_with_meridians: Chasing BlackTech’s Domain Abuse: Open sourced way is amazing!

---

# Chasing BlackTech’s Domain Abuse: Open sourced way is amazing!

Hello, I am morimolymoly.

I analyzed domain abuse by BlackTech which actively attacking Japan, Taiwan, US, Singapore, Hong Kong.

I read[TrendMicro’s article](https://blog.trendmicro.co.jp/archives/15393) about BlackTech.

BlackTech used itaiwans[.]com for C2.

I searched this domain on VirusTotal and got [result](https://www.virustotal.com/gui/domain/itaiwans.com/relations).

*sub domains*

I could obtain some subdomains.

Domains which marked malicious is well-known and not interested for me so I looked at library[.]itaiwans[.]com and got [result](https://www.virustotal.com/gui/domain/library.itaiwans.com/relations).

*suspicious urls*

As we can see, hxxp://library[.]itaiwans[.]com/logo[.]png seems really good and BlackTech is reusing this domain for years!

*malware?*

And I could also got one [Malware sample](https://www.virustotal.com/gui/file/47ec90f43990c19c62317839168e34637be57d77bcd8d4adadf02963a93b5808)(47ec90f43990c19c62317839168e34637be57d77bcd8d4adadf02963a93b5808).

*IconDown*

Yeah, it is IconDown!

*DIEstackstrings*

IconDown fetches encrypted file from C2 server, and use RC4 to decrypt payload and deploy it into %APPDATA%\Microsoft\Windows\Start Menu\Programs\Startup\slui.exe

*encrypted payload is embedded*

*deploy*

*cmd.exe /c to executeIconDown’s main routine*

---
