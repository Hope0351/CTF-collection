# :electric_plug: Configure according to your setup

> **Original Source:** [Configure according to your setup](https://infosecwriteups.com/htb-cyber-apocalypse-ctf-2024-hardware-a45ddedae49b)
> **Platform:** infosecwriteups.com | **Category:** `HARDWARE / IoT` | **Year:** 2024

---

## Rids


>

Upon reaching the factory door, you physically open the RFID lock and find a flash memory chip inside. The chip’s package has the word W25Q128 written on it. Your task is to uncover the secret encryption keys stored within so the team can generate valid credentials to gain access to the facility.


### 💡Solution


This challenge is one of my favorites in the category. Let’s learn a bit more about this type of hardware device before we unleash some hacks on it!

### The Hardware


The W25Q128 is a very popular NOR flash memory chip manufactured by Winbond and is commonly used in various electronic devices for storing firmware, configuration data, and other types of non-volatile memory.

*W25Q128JVSIQ Winbond Memory Chip*


Memory chips such as the W25Q128 serve as essential storage components, featuring built-in memory accessible through the Serial Peripheral Interface (SPI) protocol. These chips utilize specific Instruction Sets (as we will see later in the challenge) to communicate with internal Registers, ensuring efficient data retrieval and storage management.


By adhering to JEDEC standards, manufacturers guarantee compatibility with various devices, each chip distinguished by its unique JEDEC ID for seamless integration within systems.


Let’s take care of some terminology first:


- SPI Flash: Stores data in electronic devices.

- Memory chip: Acts as the storage unit, holding data and instructions for the processor to access.

- JEDEC: Establishes industry standards for semiconductor devices to ensure compatibility and reliability.

- JEDEC ID: Unique identifier assigned to semiconductor devices, similar to a serial number.

- Instruction set: List of commands understood by a processor.

- Registers: Small, high-speed memory units within a processor used for temporary data storage, akin to sticky notes for quick access.

### The Code


For this challenge, we have only been provided with a Python script named “client.py”.


```
import socket
import json

def exchange(hex_list, value=0):

# Configure according to your setup
host = '83.136.255.150' # The server's hostname or IP address
port = 35981 # The port used by the server
cs=0 # /CS on A*BUS3 (range: A*BUS3 to A*BUS7)

usb_device_url = 'ftdi://ftdi:2232h/1'

# Convert hex list to strings and prepare the command data
command_data = {
"tool": "pyftdi",
"cs_pin": cs,
"url": usb_device_url,
"data_out": [hex(x) for x in hex_list], # Convert hex numbers to hex strings
"readlen": value
}

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
s.connect((host, port))

# Serialize data to JSON and send
s.sendall(json.dumps(command_data).encode('utf-8'))

# Receive and process response
data = b''
while True:
data += s.recv(1024)
if data.endswith(b']'):
break

response = json.loads(data.decode('utf-8'))
#print(f"Received: {response}")
return response

# Example command
jedec_id = exchange([0x9F], 3)

print(jedec_id)
```


I found this challenge tricky at first until I realised that it shouldn’t be complicated to unpick this one. Bear with me please as I explain what the script does. Understanding this client-server communication is key to solving this challenge.


## Get Abdul Issa’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


The Python script client.py appears to be a client-side program designed to interact with a server-side system, likely representing a hardware device or an emulator of such a device. The general purpose of the script seems to be to exchange data and commands with this hardware device or emulator.


Specifically, the task description mentions the discovery of a flash memory chip (W25Q128) inside an RFID lock. The script may be used to communicate with this chip or another hardware component related to the challenge.


The code seems to facilitate the exchange of commands and data between the client (our machine) and the server (representing the hardware device). It sends commands in the form of *hexadecimal *values to the server, which then processes these commands and returns responses containing information retrieved from the hardware device, potentially the *flag *we are after.

### The Key Player: JEDEC ID


By examining the source code we see an interesting command stored in the variable *jedec_id*, representing the command the script sends to the hardware device. We need to start by manipulating this.

*The jedec_id stores the command to be sent*

>

JEDEC (Joint Electron Device Engineering Council) is a standardization organization that develops standards for the microelectronics industry. In the context of flash memory chips, the JEDEC ID is a unique identifier assigned to each chip by the manufacturer according to JEDEC standards. This ID typically contains information about the chip’s manufacturer, memory capacity, and other relevant details. (source: [https://www.jedec.org](https://www.jedec.org/))


### The Command Exchange


Here’s what the example command does:


A) exchange() Function Call:
The script calls the `exchange([0x9F],3)` function with parameters:


- [0x9F]: a hex value representing the command to request the JEDEC ID of the flash memory device.

- 3: A parameter indicating the number of bytes to read in response to the command. In this case, it requests to read 3 bytes of data, which correspond to the *JEDEC ID.*B) Sending the command:
The `exchange()` function serializes the command data into JSON format and sends it to the specified host and port using a socket connection.


C) Receiving and Processing Response:
After sending the command, the script waits to receive a response from the connected device. Once the complete response is received, it decodes the JSON-formatted data and stores it in the `jedec_id` variable.


D) Printing the JEDEC ID:
Finally, the script prints the received JEDEC ID to the console.


To find more on SPI Flash Memory chips and JEDEC commands, I have scoured the Internet and found limited resources containing the full set of commands without having to pay for the standard documentation by JEDEC.


Below are some of the more useful resources I found to understand SPI Flash memory and JEDEC ID a bit better:


I was able to arrive at the following conclusions on how to manipulate the *jedec_id* variable:


- exchange():function will be called with the following parameters:
`exchange([instruction value in hex],length in bytes)`.

- [0x9F]: Read JEDEC ID instruction to electronically determine the
identity of the device.

- [0x03]: Read Data instruction allows one or more data bytes to be sequentially read from the memory.

>

Example: `exchange([0x03], 0x00, 0x00x, 0x03], 16)` requests to read 16 bytes of data starting from address 0x000000.


>

In case you are wondering why I have not simply used `exchange([0x03], 16)` instead of `exchange([0x03], 0x00, 0x00x, 0x03], 16)` that is a good question!


The JEDEC ID command usually requires a sequence of bytes to be sent to the flash memory chip to retrieve the device information. While some chips may accept a single-byte command for JEDEC ID, others may expect additional bytes for the command to be properly interpreted.


By sending `[0x03, 0x00, 0x00, 0x00]`instead of just `[0x03]`, we ensure that we are providing a complete command sequence that is more likely to be compatible with a wider range of SPI flash memory chips.

### And The Execution!


Armed with all that information, and after boring you with all the theory about memory chips and instructions, the time has come to put that knowledge to good use.


I have commented out the original *jedec_id *command and added a modified instruction with a Read Data instruction to grab 16 bytes from the memory.


*Modified jedec_id command to read 16 bytes*


Let’s test our script now and see if the command works.

>

Note: You need to ensure that your remote service for the CTF challenge should be running first before you fire up the client.py script and attempt to connect.
You also need to modify the IP and Port details in the script accordingly.


```
$ python3 client.py

[72, 84, 66, 123, 109, 51, 109, 48, 50, 49, 51, 53, 95, 53, 55, 48]
```


### The Ta-daa Moment: The Flag!


Let’s decode that output which looks like Decimal to ASCII


*CyberChef decoding 16 bytes of data receivedWhad’ya Know?* We’ve managed to retrieve a part of the flag. It looks like we’re heading in the right direction. Let’s bump up the value from 16 bytes to something a bit bigger. I settled on 49 after a few tries.


```
$ python3 client.py

[72, 84, 66, 123, 109, 51, 109, 48, 50, 49, 51, 53, 95, 53, 55, 48, 50, 51, 95, 53, 51, 99, 50, 51, 55, 53, 95, 102, 48, 50, 95, 51, 118, 51, 50, 121, 48, 110, 51, 95, 55, 48, 95, 53, 51, 51, 33, 64, 125]
```


Let’s decode it with our trusty CyberChef:


*CyberChef decoding 50 bytes retrieved from the device*


Bingo! We have now retrieved 49 bytes of data which contained the full flag.


You didn’t think we’d leave it at that without being a *Maverick* about it, did you? Suppose we have to perform this activity a few times and we want a Linux command to do this for us so we can add this script to our CTF arsenal. Here’s how we can achieve this.


First, save the output to a text file named *data.txt* after removing the enclosing brackets `[]`.


```
$ cat data.txt

72, 84, 66, 123, 109, 51, 109, 48, 50, 49, 51, 53, 95, 53, 55, 48, 50, 51, 95, 53, 51, 99, 50, 51, 55, 53, 95, 102, 48, 50, 95, 51, 118, 51, 50, 121, 48, 110, 51, 95, 55, 48, 95, 53, 51, 51, 33, 64, 125
```


Now we can convert the decimal values to ASCII characters with the following command:


```
$ cat data.txt | tr -d ',' | tr " " "\n" | awk '{printf "%c",$1}'

HTB{m3m02135_57023_53c2375_f02_3v32y0n3_70_533!@}
```


>

Remember to keep it sexy, keep it Linux :)


>

Flag: HTB{m3m02135_57023_53c2375_f02_3v32y0n3_70_533!@}

---

*Originally published on [Medium](https://infosecwriteups.com/htb-cyber-apocalypse-ctf-2024-hardware-a45ddedae49b). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of hardware / iot CTF writeups.*
