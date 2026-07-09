# The Return of the Yeti

This SideQuest can be found here: https://tryhackme.com/room/adv3nt0fdbopsjcap

## 1. What's the name of the WiFi network in the PCAP?

This can easily be found by opening the provided .pcapng file. The SSID can be found in numerous packets:  
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Answer: `FreeWifiBFC`

## 2. What's the password to access the WiFi network?

[Hacktricks](https://book.hacktricks.xyz/generic-methodologies-and-resources/basic-forensic-methodology/pcap-inspection/wifi-pcap-analysis) has good resources that are helpful for this question. We first need to convert the .pcapng to a .pcap file that we will be able to pass to `aircrack-ng` in order to crack the password.

```bash
tshark -F pcap -r VanSpy.pcapng -w sidequest.pcap
```

The syntax for aircrack-ng can be found below, we know the BSSID from the previous question.
```bash
aircrack-ng -w /usr/share/wordlists/rockyou-75.txt -b 22:c7:12:c7:e2:35 sidequest.pcap
```
Within a few seconds we find the password:  
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Answer: `Christmas`

## 3. What suspicious tool is used by the attacker to extract a juicy file from the server?

In order to use this password to decrypt the Wi-Fi traffic you can just follow the instructions [here](https://book.hacktricks.xyz/generic-methodologies-and-resources/basic-forensic-methodology/pcap-inspection/wifi-pcap-analysis#decrypt-traffic). 

Looking through the Wi-Fi traffic, we notice TCP traffic on port 4444 and can see various requests, including one where it seems that the attacker used wget to download `mimikatz`:  
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Answer: `mimikatz`

### 4. What is the case number assigned by the CyberPolice to the issues reported by McSkidy?

Following the TCP traffic, we see that a .pfx file was created and dumped at a certain point using the mimikatz tool:  
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We also see that the attacker exfiltrated the pfx file by base64 encoding it so we can grab it too:  
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

After some research we can tell that the default password used for the pfx file when it was exported via mimikatz is: `mimikatz`

With this, we can export the key from the pfx file using openssl:

```bash
openssl pkcs12 -in file.pfx -nocerts -out key.pem -nodes
```
And then extract the private key:
```bash
openssl rsa -in key.pem -out server.key
```
We can follow [this](https://unit42.paloaltonetworks.com/wireshark-tutorial-decrypting-rdp-traffic/) tutorial to use the private key to decrypt the RDP traffic. Essentially we need to go in Wireshark into Preferences -> Protocols -> TLS -> RSA Keys list (edit) -> specify the IP address, port 3389, Protocol tpkt and add the private key. Now that the traffic is decrypted, let's export just what we need. From Wireshark, go to File - Export PDUs to File - OSI Layer 7
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Make sure to save it as .pcap and then we need to find a way to parse it. One way to do so is by using the PyRDP tool. I recommend either using a python virtual environment or even better, a new Ubuntu VM as a fresh test lab. I also recommend installing the full version in order to be able to convert captures to video.

After finishing the installation we can use `pyrdp-convert` to conver the decrypted RDP traffic into a .pyrdp file that can be interpreted by the tool:  
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can then use `pyrdp-player` and pass the resulted pyrdp file and it will start showing us what the attacker did in the RDP session. At a certain point he reads an email containing the answer we are looking for

![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Answer: `31337-0`

### 5. What is the content of the yetikey1.txt file?

We just need to keep looking at the video and towards the end, we can see the clipboard data we need:  
![image](../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Answer: `1-1f9548f131522e85ea30e801dfd9b1a4e526003f9e83301faad85e6154ef2834`
