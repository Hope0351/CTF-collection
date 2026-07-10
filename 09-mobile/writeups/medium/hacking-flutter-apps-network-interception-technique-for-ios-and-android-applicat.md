# :mobile_phone: Hacking Flutter Apps, network interception technique for iOS and Android applications

> **Original Source:** [Hacking Flutter Apps, network interception technique for iOS and Android applications](https://infosecwriteups.com/hacking-flutter-apps-network-interception-technique-for-ios-and-android-applications-4f79d065fb29)
> **Platform:** infosecwriteups.com | **Category:** `MOBILE`

---

# Hacking Flutter Apps, network interception technique for iOS and Android applications


Hello F.R.I.E.N.D.S, my name is Suprit aka s3ctat0r. Today we are going to learn to capture the traffic from cross platform applications which is useful for both iOS and Android apps.


Let’s learn about Flutter framework and why it is been used by the developers?


Flutter is an open-source UI framework by Google used for building natively compiled applications for mobile (iOS & Android), web, and desktop from a single codebase.


1.Cross-Platform Development — Write once, deploy on multiple platforms.
2.Fast Performance — Uses Dart and compiles to native ARM code for smooth execution.
3.Hot Reload — Instantly reflects changes in the app without restarting.
4.Rich UI Components — Comes with Material and Cupertino widgets for a native feel.
5.Strong Community & Google Support — Backed by an active developer ecosystem.


In short, flutter is a powerful and flexible framework that enables developers to build high-performance, visually appealing applications across multiple platforms with minimal effort. Its efficiency, ease of use, and cost-effectiveness make it a preferred choice for startups, enterprises, and developers worldwide.


Are pen-tester or security researchers able to capture the traffic using convectional method, which is used for Native mobile applications?


The answer is NO, because Flutter is proxy unaware. Let’s understand why?


1.Proxy Avoidance (`findProxy = "DIRECT";`) forces all network traffic to go directly to the server, securing the system wide proxy settings.


2.Certificate Pinning (`badCertificateCallback`) verifies server certificates against predefined SHA256 fingerprints, preventing MITM attacks even if a system proxy tries to inject a fake certificate.


3.`HttpOverrides.global = SecureHttpOverrides();` applies these settings to all HTTP requests in the app.


Bypass these security mechanisms to capture the communication between the mobile application and the server.


Step 1: Setting up Open VPN configuration
a. `wget https://git.io/vpn` `-O openvpn-install.sh`


b.`sed` `-i "$(($(grep -ni "debian is too old" openvpn-install.sh | cut -d : -f 1)+1))d"` `./openvpn-install.sh`


c. `chmod` `+x openvpn-install.sh`


d. `sudo` `./openvpn-install.sh`


## Get Suprit Pandurangi’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


And set the configurations as shown below


Step 2. Navigate to the generated Open VPN file and set all the required W/R permissions as shown in the below screenshot. And share this file on the mobile device.


Step 3. Now install this VPN profile on the mobile device. And connect with the host.


Step 4. Let’s configure the proxy tool, here I have used Burp suite. Navigate to Proxy settings and set the interface to wildcard or else, you can also set the host’s IP address and port 8080. Remember to Turn on “Support invisible proxying”


Step 5. Now let’s configure iptables with tunnel interface to capture the mobile device traffic as shown below.


a.`sudo` `iptables -t nat -A PREROUTING -i tun0 -p tcp --dport 80 -j REDIRECT --to-port 8080`


b. `sudo` `iptables -t nat -A PREROUTING -i tun0 -p tcp --dport 443 -j REDIRECT --to-port 8080`


c. `sudo` `iptables -t nat -A POSTROUTING -s 192.168.2.0/24` `-o eth0 -j MASQUERADE`


Step 6. Boom, we are able to capture the traffic successfully from mobile application.


Congratulations :) you got the traffic, right?


Special thanks to my friend/mentor Abhishek Rajak for his invaluable support and insights into the Flutter framework.


References: [Intercepting Flutter traffic on iOS — NVISO Labs](https://blog.nviso.eu/2020/06/12/intercepting-flutter-traffic-on-ios/)


NOTE: This method will work for both flutter based iOS and Android applications.


How this bypass can be restricted? — for Developers


- Enforce VPN/Proxy detection checks in the application as shown below.


2. Use Direct socket connections as shown in the below code snippet.


I hope you have enjoyed the blog, and this might be helpful for you.


Happy Hacking :D

---

*Originally published on [Medium](https://infosecwriteups.com/hacking-flutter-apps-network-interception-technique-for-ios-and-android-applications-4f79d065fb29). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of mobile CTF writeups.*
