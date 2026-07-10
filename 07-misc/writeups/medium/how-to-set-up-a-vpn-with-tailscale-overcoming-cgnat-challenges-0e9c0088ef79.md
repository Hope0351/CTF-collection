# :game_die: How to Set Up a VPN with Tailscale: Overcoming CGNAT Challenges

> **Original Source:** [How to Set Up a VPN with Tailscale: Overcoming CGNAT Challenges](https://infosecwriteups.com/how-to-set-up-a-vpn-with-tailscale-overcoming-cgnat-challenges-0e9c0088ef79)
> **Platform:** infosecwriteups.com | **Category:** `MISC`

---

# How to Set Up a VPN with Tailscale: Overcoming CGNAT Challenges


Setting up a VPN can be a great way to secure your internet connection or access your home network remotely. However, as I discovered, it’s not always straightforward, especially when your ISP uses Carrier-Grade NAT (CGNAT). In this blog, I’ll share my journey of trying to set up a VPN, the roadblocks I hit, and how I ultimately solved the problem using Tailscale. I’ll also provide step-by-step instructions for installing and configuring Tailscale on Linux, Windows, and macOS, including how to set up an Ubuntu machine as an exit node for remote network access.

## My VPN Struggles: The CGNAT Roadblock


I initially tried setting up a VPN using WireGuard, a lightweight and efficient VPN protocol. Despite carefully configuring everything — double-checking my settings and ensuring port forwarding was correctly set up on my router — it didn’t work. I couldn’t connect to my VPN server remotely. Frustrated, I switched to OpenVPN, hoping for better results, but the same issue persisted.


After some research, I discovered the root cause: my ISP uses Carrier-Grade NAT (CGNAT). CGNAT assigns users a private IP address behind a double NAT, meaning my router wasn’t directly exposed to the public internet. This made it impossible to forward ports for external access, rendering traditional VPN setups like WireGuard and OpenVPN ineffective for remote connections.


## The Solution: Tailscale


To overcome this, I turned to Tailscale, a VPN solution that leverages the WireGuard protocol but simplifies connectivity by bypassing NAT restrictions. Tailscale creates a peer-to-peer mesh network, allowing devices to connect securely without requiring complex port forwarding or public IP addresses. It’s perfect for scenarios like mine, where CGNAT makes traditional VPN setups challenging.


Below, I’ll walk you through how to install and configure Tailscale on Linux, Windows, and macOS. I’ll also explain how I set up my Ubuntu machine as an exit node to access my home network remotely.

## Installing and Configuring Tailscale


## 1. Installing Tailscale on Linux (Ubuntu)


Here’s how to install Tailscale on an Ubuntu machine and configure it as an exit node.

### Installation Steps


- Add Tailscale’s Package Repository:
Open a terminal and add the Tailscale repository to ensure you get the latest version.


```
curl -fsSL https://pkgs.tailscale.com/stable/ubuntu/noble.noarmor.gpg | sudo tee /usr/share/keyrings/tailscale-archive-keyring.gpg >/dev/null
curl -fsSL https://pkgs.tailscale.com/stable/ubuntu/noble.tailscale-keyring.list | sudo tee /etc/apt/sources.list.d/tailscale.list
```


2. Update and Install Tailscale: Update the package list and install Tailscale.


```
sudo apt-get update
sudo apt-get install tailscale
```


3. Authenticate and Connect: Start Tailscale and authenticate your device using your Tailscale account (you’ll need to sign up at tailscale.com).


```
sudo tailscale up
```


- This will prompt you to log in via a browser. Follow the link provided, sign in, and your Ubuntu machine will join your Tailscale network.


4. Configure as an Exit Node: To use your Ubuntu machine as an exit node (allowing other devices to route traffic through it), enable the exit node feature.


```
sudo tailscale up --advertise-exit-node
```


Then, in the Tailscale admin console (accessible via login.tailscale.com), approve the exit node by navigating to the Machines tab, finding your Ubuntu machine, and enabling the “Use as exit node” option.


## Get Mihir Shah’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


5. Check Tailscale Status to View Connected Devices and Exit Nodes


```
tailscale status
```


### Using the Exit Node


Once configured, other devices in your Tailscale network can route their traffic through this Ubuntu machine to access your home network remotely. To connect, select the Ubuntu machine as the exit node in the Tailscale client on your other devices (see configuration steps for Windows/macOS below).

## 2. Installing Tailscale on Windows


### Installation Steps


- Download the Installer:
Visit the [Tailscale download page](https://tailscale.com/download/windows) and download the Windows installer.

- Run the Installer:
Double-click the downloaded `.exe` file and follow the on-screen instructions to install Tailscale.

- Sign In: Launch Tailscale from the Start menu or system tray. Click the Tailscale icon, select “Log in,” and authenticate via the browser using your Tailscale account.

- Connect to the Network:
Once logged in, your Windows machine will join your Tailscale network. You can verify connectivity in the Tailscale admin console.

- Using the Ubuntu Exit Node: To route traffic through your Ubuntu exit node:


- Right-click the Tailscale system tray icon.

- Select “Exit Nodes” and choose your Ubuntu machine from the list.

- Enable “Use exit node” to route all traffic through your Ubuntu machine, giving you access to your home network.

## 3. Installing Tailscale on macOS


### Installation Steps


- Download Tailscale:
Download Tailscale from the [Mac App Store](https://apps.apple.com/app/tailscale/id1475387142) or the [Tailscale website](https://tailscale.com/download/mac).

- Install Tailscale:
If downloaded from the website, open the `.pkg` file and drag the Tailscale app to the Applications folder.

- Sign In:
Open Tailscale from the Applications folder or menu bar. Click the Tailscale icon, select “Log in,” and authenticate via the browser.

- Connect to the Network:
Your Mac will join the Tailscale network after authentication. Check the Tailscale admin console to confirm.

- Using the Ubuntu Exit Node: To use your Ubuntu machine as an exit node:


- Click the Tailscale menu bar icon.

- Select “Exit Nodes” and choose your Ubuntu machine.

- Enable the exit node to route traffic through your home network.

## Additional Tips for Using Tailscale


- Admin Console Management: The Tailscale admin console (at [login.tailscale.com](https://login.tailscale.com/)) is where you manage devices, set permissions, and approve exit nodes. Ensure your Ubuntu machine is approved as an exit node for other devices to use it.

- Security: Tailscale uses end-to-end encryption and the WireGuard protocol, ensuring secure connections. You can further enhance security by enabling access control lists (ACLs) in the admin console to restrict which devices can connect.

- Accessing Your Home Network: With the Ubuntu machine set as an exit node, you can access resources on your home network (e.g., file servers, cameras, or other devices) as if you were physically there, even from remote locations.

- Performance: Tailscale optimizes connections using NAT traversal techniques, making it reliable even behind CGNAT. If you experience slow connections, check your Ubuntu machine’s network performance or Tailscale’s relay usage in the admin console.

## Why Tailscale Worked for Me


Tailscale solved my CGNAT problem by eliminating the need for port forwarding or a public IP address. Its peer-to-peer architecture, built on WireGuard, ensures fast and secure connections. By setting up my Ubuntu machine as an exit node, I can now connect to my home network remotely with ease — whether I’m on my Windows laptop, Mac, or another device.


If you’re struggling with traditional VPN setups due to CGNAT or complex router configurations, I highly recommend giving Tailscale a try. It’s user-friendly, secure, and works across platforms, making it an ideal solution for remote network access.

---

*Originally published on [Medium](https://infosecwriteups.com/how-to-set-up-a-vpn-with-tailscale-overcoming-cgnat-challenges-0e9c0088ef79). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of misc CTF writeups.*
