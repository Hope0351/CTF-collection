### Challenge Description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We get a wireshark capture for this challenge. The capture contains modbus traffic with multiple `Write Multiple Registers` functions. The `Reference Numbers` look to be decimals:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We can use the syntax below with tshark to carve all of them out:

```bash
tshark -r tower_logs.pcapng -Y "modbus" -T fields -e modbus.reference_num|grep .|awk '{print $1}' ORS=' '
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

After converting from Decimal using Cyberchef, we get the flag:

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

HTB{m0d8u5_724ff1c_15_un3nc2yp73d!@^}
