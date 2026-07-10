# :game_die: VulnCMS 1 VulnHub CTF Walkthrough for Beginners

> **Original Source:** [VulnCMS 1 VulnHub CTF Walkthrough for Beginners](https://infosecwriteups.com/vulncms-1-vulnhub-ctf-walkthrough-for-beginners-e8c3f1e544ab)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# VulnCMS 1 VulnHub CTF Walkthrough for Beginners


## Step 1: Setting Up the Machines


Before anything else, download the VulnCMS 1 machine from VulnHub [https://download.vulnhub.com/vulncms/VulnCMS.ova](https://download.vulnhub.com/vulncms/VulnCMS.ova) and import it into your virtualization software (such as VirtualBox).


Make sure both your VulnCMS machine and your Kali Linux machine are set to use a Bridged Adapter in their network settings. This ensures that both machines are on the same network and can communicate with each other.

## Step 2:Discovering the Target IP


Power on your Kali machine and open a terminal. Run the following command to scan your local network and discover live hosts:


```
sudo netdiscover
```


Look for a new IP address that belongs to the VulnCMS machine. In my case, the target IP was `192.168.105.7.` (PCS Systemtechnik GmbH)

## Step 3: Scanning the Target for Open Ports and Services


Now that you have the target machine’s IP address, it’s time to gather information about what services it is running. This step is crucial because it helps us identify potential entry points.

---

*Originally published on [Medium](https://infosecwriteups.com/vulncms-1-vulnhub-ctf-walkthrough-for-beginners-e8c3f1e544ab). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
