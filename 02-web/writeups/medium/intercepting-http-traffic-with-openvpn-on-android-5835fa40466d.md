# :globe_with_meridians: Intercepting HTTP traffic with OpenVPN on AndroidSummary

---

# Intercepting HTTP traffic with OpenVPN on AndroidSummary

In this article, we’ll show you how you can intercept the HTTP traffic on Android. Our method is based on a VPN tunnel approach.

Disclaimer

This article is for informational and educational purposes only, and for those who’re willing and curious to know and learn about Security and Penetration Testing. The content may not be used for illegal purposes. If you’re ready to learn something new for the good, then read on.

Details

Intercepting HTTP traffic with Burp proxy in Android apps is not as easy as in traditional browser web applications. Intercepting HTTP traffic in traditional web applications is as simple as configuring the browser with a proxy server. Android (and iOS) apps do not have a proxy server configuration. This makes it difficult to redirect HTTP traffic to proxy servers like Burp Suite. It’s difficult, but not impossible. In general, there are three ways to redirect traffic from your mobile app to your proxy server. Jeroen Beckers has written an excellent article explaining all three methods for iOS ([https://blog.nviso.eu/2020/06/12/intercepting-flutter-traffic-on-ios](https://blog.nviso.eu/2020/06/12/intercepting-flutter-traffic-on-ios)/).

This article describes how to use a VPN connection between your mobile app and the attacking (pentester) machine. In addition, we will show how to transfer the Burp proxy server certificate to the mobile device and to configure Burp proxy for mobile device traffic interception.

The POC consists of 1 mobile device and Kali Linux: the victim (Samsung J3) and an attacker machine (Kali Linux 2022.3).

Victim:

— Samsung J3 (Android 5.1, not rooted)
— IP-Address: 192.168.43.136

Attacker (for Burp proxy):
— Kali Linux
— IP-Address: 192.168.43.136

The following sections show you how to install an OpenVPN server on your Kali machine, how to install an OpenVPN client on your mobile device, how to import a burp proxy certificate, and how to intercept HTTP traffic using burp proxy.

Prepare the PoC environment

Before we start our PoC, let me first show you the PoC requirments. In order to perform the steps, you have to:
- use a physical mobile device (Android Virtual Device is not possible)
- enable the Android Developer Options
- establish TCP connectivity between Kali attacker machine and mobile device (f.e. both are connected to the same Wifi network or connected via USB)

In this PoC we will use a USB connection to establish TCP connectivity with our Kali host. You can also use WiFi instead of using a USB connection. In that case, both your mobile device and your Kali Linux system must be connected to the same WiFi network. If you choose to use a WiFi network, you can skip this section and continue from step 7.

1. Performed on 192.168.43.1 (victim, Samsung J3).

Enable the Developer options on our mobile device.

Go to "Settings"
Tap "About device" or "About phone"
Tap “Software information”
Tap “Build number” seven times. ...
Optional Enter your pattern, PIN or password to enable the Developer options menu.
The "Developer options" menu will now appear in your Settings menu.

[https://www.samsung.com/uk/support/mobile-devices/how-do-i-turn-on-the-developer-options-menu-on-my-samsung-galaxy-device/](https://www.samsung.com/uk/support/mobile-devices/how-do-i-turn-on-the-developer-options-menu-on-my-samsung-galaxy-device/)

Note: these steps are specific for the Samsung J3 device. Check your vendor site for your instructions.

2. Performed on 192.162.43.1 (victim, Samsung J3).

Enable USB-Debugging option in Developer Options.

Ensure the Developer options switch (located in the upper-right) is turned on Switch on icon.

Tap USB debugging switch to turn it on.

[https://www.youtube.com/watch?v=-SpUm2_eliA](https://www.youtube.com/watch?v=-SpUm2_eliA)

3. Performed on 192.162.43.1 (victim, Samsung J3).

Connect the mobile device to a free USB port of your Kali attacker machine. Choose Linux as target device to connect to.

4. Performed on 192.168.43.136 (attacker machine, Kali Linux).

If not done yet, install Android Debug Bridge tool. Open a Bash terminal tab and execute:

```
sudo apt install android-tools-adb
```

5. Performed on 192.168.43.136 (attacker machine, Kali Linux).

Use adb to list the available devices. You should see the Samsung J3 device.

```
adb devices
```

6. Performed on 192.168.43.136 (attacker machine, Kali Linux).

Use adb to test shell access to the mobile device. Try to use ping to test connectivity with our Kali attacking (pentesting) machine and the Internet.

```
adb shell
```

```
ping -c 2 192.168.43.136
```

Summary
We have our victim device (Samsung J3) connected over USB to our Kali machine. This device has TCP connectivity to our Kali attacker machine.

PoC install OpenVPN server

We have all requirements in place to setup a VPN between our Kali pen testing machine and our mobile device.

7. Performed on 192.168.43.136 (attacker machine, Kali Linux).

Install OpenVPN server. We will use Jeroen Beckers's installation script.

```
wget https://git.io/vpn -O openvpn-install.sh
sed -i "$(($(grep -ni "debian is too old" openvpn-install.sh | cut -d : -f 1)+1))d" ./openvpn-install.sh
chmod +x openvpn-install.sh
sudo ./openvpn-install.sh
```

8. Performed on 192.168.43.136 (attacker machine, Kali Linux).

OpenVPN installation script wizard: Select the network device that is connected to the Internet.

9. Performed on 192.168.43.136 (attacker machine, Kali Linux).

OpenVPN installation script wizard: Type the ip-address on which the VPN should be terminated on. In our case it is ip-address 192.168.43.136.

10. Performed on 192.168.43.136 (attacker machine, Kali Linux).

OpenVPN installation script wizard: Select UDP as preferred protocol.

11. Performed on 192.168.43.136 (attacker machine, Kali Linux).

OpenVPN installation script wizard: We will use the default settings for the next options. Press ENTER for the port specification, system resolvers and client name. Press any key to continue …

We have our VPN server installed. Our client profile is stored at /root/client.ovpn.

12. Performed on 192.168.43.136 (attacker machine, Kali Linux).

## Get Nol White Hat’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Start the OpenVPN service

```
sudo service openvpn start
```

Our OpenVPN server is now up-and-running. It’s time to install the OpenVPN client software on our mobile device.

PoC install OpenVPN client

In the next sections, we will copy files from the Kali Linux machine to your mobile device. It concerns the following files:

- client.ovpn (OpenVPN profile)
- openvpn-connect-3-3-0.apk (OpenVPN client software)
- cert-pro.cer (Burp Suite server certificate)

The steps in the next sections are based on using a USB connection between your mobile device and your Kali Linux system. As already mentioned, no USB connection is required. It is also possible to use a shared WiFi network. When using a WifI network, the necessary files can be copied to the mobile device by placing the files in the /tmp directory on the Kali Linux system and serving this directory through a temporary http server (*python3 -m http.server 80 — directory /tmp*). The required files can then be downloaded from the mobile device using an existing web browser.

*Samsung J3 with access to http://192.168.43.136*

13. Performed on 192.168.43.136 (attacker machine, Kali Linux).

Use adb to copy the profile file client.ovpn to the sdcard of our Android device.

```
sudo cp /root/client.ovpn /tmp
adb push /tmp/client.ovpn /sdcard/Download/client.ovpn
```

14. Performed on 192.168.43.136 (attacker machine, Kali Linux).

Download the OpenVPN client *.apk installation package. Open a web browser (Firefox) and navigate to: [https://openvpn-connect.en.softonic.com/android](https://openvpn-connect.en.softonic.com/android). Click on the green [Download] button.

*Source: [https://openvpn.net/community-downloads/](https://openvpn.net/community-downloads/)*

Move the downloaded apk file to /tmp.

```
mv ~/Downloads/openvpn-connect-3–3–0.apk /tmp
```

15. Performed on 192.168.43.136 (attacker machine, Kali Linux).

Use adb to install openvpn-connect-3–3–0.apk on our Android device.

```
adb install /tmp/openvpn-connect-3–3–0.apk
```

16. Performed on 192.168.43.1 (victim, Samsung J3).

Open the built-in file explorer app and browse to /sdcard/Downloads/client.ovpn.

Tap on client.ovpn and install the OpenVPN profile. Continue the installation steps.

*click on [Agree]Click on [OK]Click on [Add]We have a succesful VPN tunnel between the mobile device and Kali Linux*

We have a succesful VPN tunnel between are mobile device and Kali attacker machine. From now on, we are able to intercept traffic from the Android device. We still have to import Burp proxy server certificate in order to use Burp proxy for HTTPS interception.

PoC install Burp server certificate

17. Performed on 192.168.43.136 (attacker machine, Kali Linux).

Start Burp Community edition. Leave the default proxy settings (127.0.0.1:8080).

*Click Next to start Burp listening on TCP port 8080.*

18. Performed on 192.168.43.136 (attacker machine, Kali Linux).

Use wget to download the Burp server certificate. Important: the certificate file needs the *.cer extention.

```
wget http://127.0.0.1:8080/cert -O /tmp/cert-pro.cer
```

19. Performed on 192.168.43.136 (attacker machine, Kali Linux).

Use adb to copy the Burp certificate (cert-pro.cer) to the sdcard of our Android device.

```
adb push /tmp/cert-pro.cer sdcard/Download/cert-pro.cer
```

20. Performed on 192.168.43.1 (victim, Samsung J3).

Install the Burp certicate on our mobile device.

Open the built-in file explorer app and browse to /sdcard/Downloads/cert-pro.cer. Check if “Used for VPN and apps” is selected. Tap on cert-pro.cer and import the server certificate.

21. Performed on 192.168.43.136 (attacker machine, Kali Linux).

Configure Burp proxy to listen to all interfaces. Go to proxy > Options > select the interface > [Edit] > on tab Binding; choose for “alle interfaces”. Click [OK]

22. Performed on 192.168.43.136 (attacker machine, Kali Linux).

Configure Burp proxy to use ‘invisible proxying’. Go to proxy > Options > select the interface > [Edit] > on tab Request Handling; choose for “Support invisible proxying ”. Click [OK].

23. Performed on 192.168.43.136 (attacker machine, Kali Linux).

Configure iptables to redirect the incoming traffic on ports 80 and 443 to Burp proxy that listens on port 8080.

```
sudo iptables -A PREROUTING -t nat -i tun0 -p tcp --dport 80 -j REDIRECT --to-port 8080
sudo iptables -A PREROUTING -t nat -i tun0 -p tcp --dport 443 -j REDIRECT --to-port 8080
```

PoC use mobile app to intercept the traffic

24. Performed on 192.168.43.1 (victim, Samsung J3).

You are now ready to intercept HTTP traffic from your mobile app. For demonstration purposes we will use the Radio10 app owned by the Dutch company Talpa. You can use any other app that communicates HTTP over TCP ports 80 or 443. You are not allowed to use this app for an actual pen test or any (other) way of misusing it. Please first consult Talpa regarding their bug bounty program and responsible disclosure.

As you can see, we catched the traffic form the mobile app. The User-Agent is recognized as okhttp/4.4.1.

That was it! I hope you liked it. In my next blog, I’ll show you some interesting stuff you can do with Burp Suite.

Credits
- Jeroen Beckers for his excellent OpenVPN installation script.

---
