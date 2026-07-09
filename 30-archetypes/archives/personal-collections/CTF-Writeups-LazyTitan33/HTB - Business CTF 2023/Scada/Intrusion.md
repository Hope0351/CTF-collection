### Challenge description
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We get a wireshark capture with modbus traffic. It contains `Write Multiple Registers` functions and it seems that there is a word count of 1. The unit identifier is 52. This is the modbus `slave_id`.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Looking through the capture, we can tell that there are 47 Write Multiple Registers probably each letter of the flag that we need to read via the provided client.py script. The modbus documentation helps us figure out what command we can use: https://umodbus.readthedocs.io/en/latest/client/tcp.html.

The first letter of the flag is `H` so as a proof of concept, let's use the provided script to read the first word on `starting_address` 6 which is represented by the reference number in the wireshark capture.

```python
#!/usr/bin/python3

import socket
from time import sleep
import time
from umodbus import conf
from umodbus.client import tcp

# Adjust modbus configuration
conf.SIGNED_VALUES = True

# Create a socket connection
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
sock.connect(('83.136.254.108', 38242)) # CHANGE THE IP & PORT to the dockers instance

# write your umodbus command here
command = tcp.read_holding_registers(slave_id=52, starting_address=6, quantity=1)

# Send your message to the network
output = tcp.send_message(command, sock)
print(output)

# Use sleep between messages 
time.sleep(1)

# Close the connection
sock.close()
```
Running the script, we get 72 which is indeed ASCII for H.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)  
Next instance where a register is written is on Reference Number 10. We modify our starting_address=10.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)  
84 is T  
Next instance where a register is written is on Reference Number 12. We modify our starting_address=12  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)  
66 is B  

We can carve out all the reference numbers we need to read using tshark
```bash
tshark -r network_logs.pcapng -Y "modbus.func_code == 16" -T fields -e modbus.reference_num|awk '{print $1}' ORS=' '
```
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)  

```python
#!/usr/bin/python3

import socket
from time import sleep
import time
from umodbus import conf
from umodbus.client import tcp

# Adjust modbus configuration
conf.SIGNED_VALUES = True

# Create a socket connection
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
sock.connect(('83.136.254.108', 38242)) # CHANGE THE IP & PORT to the dockers instance

register_addresses = [6, 10, 12, 21, 22, 26, 47, 53, 63, 77, 83, 86, 89, 95, 96, 104, 123, 128, 131, 134, 139, 143, 144, 145, 153, 163, 168, 173, 179, 193, 206, 210, 214, 215, 219, 221, 224, 225, 226, 231, 239, 253]

try:
    for i in register_addresses:
        try:
            command = tcp.read_holding_registers(slave_id=52, starting_address=i, quantity=1)

            # Send your message to the network
            output = tcp.send_message(command, sock)
            print(chr(output[0]), end='')

            # Use sleep between messages 
            time.sleep(1)

        except OSError:
            pass
finally:
    sock.close()
```
We can modify the script to connect to the docker instance and read all the registers and get the flag:
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

HTB{239157325_m19h7_h1dd3_53c2375!@$2609^}
