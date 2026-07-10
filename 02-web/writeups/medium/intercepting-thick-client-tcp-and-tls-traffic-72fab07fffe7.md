# :globe_with_meridians: Intercepting Thick Client TCP and TLS Traffic

---

# Intercepting Thick Client TCP and TLS Traffic

Intercepting and analysing the traffic is one of the important parts of the pentest, whether it’s a mobile, web or desktop application. On the web, it’s easy to intercept. In the case of mobile applications, it’s easy to intercept unless there are security mitigation implementations, but those are often bypassed. In all those cases, the web or mobile app protocol used is HTTP/s, which means we have the option to intercept easily via BurpSuite.

When it comes to a Desktop Thick client application, it’s always easy to intercept when the HTTP/S protocol is used. In some rare cases, it requires different methods, and to intercept HTTP/s, but it’s always possible as we have different tools and proxy applications like BurpSuite, ZAP available to intercept the HTTP/s traffic. In many cases, applications don’t use the HTTP protocol, instead, they use different protocols. In most cases, it’s based on a protocol or custom protocol and with TLS, which makes it hard to intercept, as there are no direct, easy solutions to intercept on TCP+TLS traffic.

We can set up the MITMProxy application, but it requires multiple setups and does not always work with non-TCP + TLS traffic.

To make things easy, similar to BurpSuite, like single click install and setup proxy, I have created InterceptSuite, which uses Socks5 proxy, with 1 click installation and easy to intercept and modify the tick client TCP, UDP, DTLS and TLS traffic with a modern GUI.

To get started, go to the InterceptSuite GitHub Repository, navigate to the release page and download the installer EXE for Windows, PKG for MacOS or RPM, Deb, and App Image file for Linux.

If not, you can directly download it from the [InterceptSuite website](http://interceptsuite.com/Download).

To test the TCP Intercept, I am using the BetaFast Vulnerable Thick Client application.

InterceptSuite make use of Socks5 Proxy; for some reason, Windows does not support Socks proxy. In order to redirect the application traffic to any proxy server, including for an unaware application, the best option is [ProxyBridge](https://interceptsuite.com/download/proxybridge), another tool I created as an open-source alternative to Proxifier with support for both TCP and UDP.

## Get Sourav Kalal’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Install and open the ProxyBridge application and navigate to the Proxy→ Proxy Settings.

Enter the interceptSuite proxy server IP and port. Default is 127.0.0.1 port 4444, select Type as SOCKS5.

We can now configure ProxyBridge to redirect traffic from specific applications, IP addresses, or ports to the proxy. To do this, navigate to Proxy → Proxy Rules.

To view the TCP data between the BetaBank application and the server, open the BetaBank application, submit your credentials, and then navigate to the proxy history in InterceptSuite.

No more complex setup, just plug in InterceptSuite and start analysing TCP and TLS traffic instantly.

---
