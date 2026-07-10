# :arrows_counterclockwise: DEADFACE CTF - Dead_Browse 1 Reverse Engineering Challenge Write-Up

> **Original Source:** [DEADFACE CTF - Dead_Browse 1 Reverse Engineering Challenge Write-Up](https://micro1010.medium.com/deadface-ctf-dead-browse-1-reverse-engineering-challenge-write-up-9be8a0231814)
> **Platform:** micro1010.medium.com | **Category:** `REVERSE ENGINEERING`

---

# DEADFACE CTF — Dead_Browse 1 Reverse Engineering Challenge Write-Up


Challenge Description:


DEADFACE has created a custom browser called `dead_browse` that interacts with a specific website:


Our goal is to reverse engineer the `dead_browse` binary to discover how it communicates with the server and retrieve the hidden flag.

## Step 1: Initial Reconnaissance


First after downloading the zip and extracting it, I ran file command to check the type of the binary. As we can see, it’s a 64 bit linux executable.


Then i check specifically for any strings with auth to see if the auth key is hard coded in the binary. That wasnt the case as we can see.

## Step 2: Dynamic Analysis


Running the binary directly results in an error due to my kali linux not being able to install libwebkit2gtk.


```
FROM ubuntu:22.04

RUN apt-get update && \
apt-get install -y libwebkit2gtk-4.0-37 curl && \
apt-get clean

COPY dead_browse /usr/local/bin/

CMD ["/usr/local/bin/dead_browse", "--url=http://deadbrowse.deadface.io:3000", "--auth-key=;XImq]gny9m}#OT#O*o#v#"]
```


There fore i created a dockerfile with the code above to try and run it. But it shows Error {Bad_auth_key} and that’s when i figured out that i need to get the auth_key from the binary by reverse engineering it.

## Step 3: Reverse Engineering with Ghidra


```

void FUN_00102b0c(char *param_1)

{
int iVar1;
size_t sVar2;
size_t sVar3;
long in_FS_OFFSET;
undefined8 local_56;
undefined4 local_4e;
undefined2 local_4a;
undefined8 local_48;
undefined8 local_40;
undefined8 local_38;
undefined4 local_30;
undefined local_2c;
long local_20;

local_20 = *(long *)(in_FS_OFFSET + 0x28);
local_48 = 0x5621161e143e150b;
local_40 = 0xd54144a0e462c26;
local_38 = 0x463b471620501340;
local_30 = 0x4011609;
local_2c = 0;
local_56 = 0x65726365735f796d;
local_4e = 0x656b5f74;
local_4a = 0x79;
puts("Checking user key...");
sVar2 = strlen((char *)&local_56);
sVar3 = strlen(param_1);
FUN_00102aa1(param_1,&local_56,sVar3,sVar2);
iVar1 = strcmp((char *)&local_48,param_1);
if (iVar1 == 0) {
printf("good key");
}
if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
/* WARNING: Subroutine does not return */
__stack_chk_fail();
}
return;
}


```


Analyzing the binary in Ghidra for diassembly and decompilation gave us an interesting function that is handling the auth_key processing.


- The function receives `param_1`, which is the user-provided `auth-key`.

- There are hardcoded data blocks (`local_48`, `local_40`, etc.) that collectively form the `encrypted_data`.

- There is also a hardcoded key (`local_56`, `local_4e`, `local_4a`) that we'll refer to as `key_data`.

- The function computes the lengths of the `key_data` and the user-provided `auth-key`.

- It then calls `FUN_00102aa1` to perform a transformation (XOR operation) on the `auth-key`.

- Finally, it compares the transformed `auth-key` with the `encrypted_data` using `strcmp` .


XOR Function FUN_00102aal performs an XOR operation between the user input and the key.


From the code, we can deduce:


Parameters:


- `param_1`: Pointer to the user-provided `auth-key`.

- `param_2`: Pointer to the `key_data`.

- `param_3`: Length of the `auth-key`.

- `param_4`: Length of the `key_data`.


Operation:


- The function `FUN_00102aa1` modifies the user-provided `auth-key` in place by XORing each byte with the corresponding byte from the `key_data`.

- The key is applied cyclically if the `auth-key` is longer than the `key_data`.


Comparison:


- The transformed `auth-key` is then compared to the `encrypted_data` using `strcmp`.

- If they match, the program outputs “good key”.


Objective:


Our goal is to reverse this process to find the original `auth-key` that, when XORed with the `key_data`, results in the `encrypted_data`.

## Extracting the Hardcoded Data


To reverse engineer the `auth-key`, we need to extract both the `encrypted_data` and the `key_data` from the binary.

### Encrypted Data (`encrypted_data`)


The `encrypted_data` consists of several variables:


- `local_48`: `0x5621161e143e150b`

- `local_40`: `0x0d54144a0e462c26`

- `local_38`: `0x463b471620501340`

- `local_30`: `0x04011609`

- `local_2c`: `0x00`


Combined Encrypted Data:


- We need to extract the bytes from these variables and concatenate them to form the complete `encrypted_data`.

- Since the variables are multi-byte numbers, we have to consider endianness. On little-endian systems, the least significant byte comes first.

### Key Data (`key_data`)


The `key_data` is formed by:


- `local_56`: `0x65726365735f796d`

- `local_4e`: `0x656b5f74`

- `local_4a`: `0x79`


Combined Key Data:


- Similarly, we extract the bytes from these variables and concatenate them to form the full key.

- The key is likely a string in ASCII when interpreted correctly.

## Converting Hexadecimal Values to Bytes


To work with the data in our script, we need to:


- Convert the hexadecimal values to bytes.

- Reverse the bytes if necessary (due to endianness).

- Combine the bytes to form the `encrypted_data` and `key_data`.

### Endianness Consideration


- The values in the code are stored in little-endian format.

- For example, the value `0x65726365735f796d` in little-endian corresponds to the bytes `[6d,79,5f,73,65,63,72,65]`.

- When reversed, this gives us the ASCII string `'my_secret'`.

### Extracting Encrypted Data Bytes


Let’s extract the bytes from the `encrypted_data` variables:


`local_48` (`0x5621161e143e150b`):


- Hexadecimal string: `0x5621161e143e150b`

- Remove `0x` and pad to 16 characters: `5621161e143e150b`

- Convert to bytes: `[0x56, 0x21, 0x16, 0x1e, 0x14, 0x3e, 0x15, 0x0b]`

- Reverse bytes for little-endian: `[0x0b, 0x15, 0x3e, 0x14, 0x1e, 0x16, 0x21, 0x56]`


Repeat for other variables (`local_40`, `local_38`, `local_30`, `local_2c`).

### Extracting Key Data Bytes


Similarly, extract bytes from the `key_data` variables:


`local_56` (`0x65726365735f796d`):


- Hexadecimal string: `0x65726365735f796d`

- Remove `0x` and pad: `65726365735f796d`

- Convert to bytes: `[0x65, 0x72, 0x63, 0x65, 0x73, 0x5f, 0x79, 0x6d]`

- Reverse bytes: `[0x6d, 0x79, 0x5f, 0x73, 0x65, 0x63, 0x72, 0x65]`

- This corresponds to ASCII characters: `my_secret`


`local_4e` (`0x656b5f74`):


- Hexadecimal string: `0x656b5f74`

- Remove `0x` and pad: `656b5f74`

- Convert to bytes: `[0x65, 0x6b, 0x5f, 0x74]`

- Reverse bytes: `[0x74, 0x5f, 0x6b, 0x65]`

- ASCII: `t_ke`


`local_4a` (`0x79`):


- Hexadecimal string: `0x79`

- Remove `0x`: `79`

- Convert to bytes: `[0x79]`

- ASCII: `y`


Combined Key Data Bytes:


- Concatenate the bytes: `my_secret` + `t_ke` + `y` => `my_secrett_key`

## Understanding the XOR Reversal


Since the XOR operation is its own inverse, we can reverse the transformation by applying the same XOR operation between the `encrypted_data` and the `key_data`.


Formula:


- Original Byte = Encrypted Byte XOR Key Byte


Implementation Steps:Prepare the Data:


- Ensure that both the `encrypted_data` and `key_data` are in byte arrays.

- The `key_data` may be shorter than the `encrypted_data`; we use modulo operation to cycle through the key.


Perform XOR Operation:


- For each index `i` in the range of the length of the `encrypted_data`:

- `original_byte[i] = encrypted_byte[i] ^ key_byte[i % key_length]`


Collect the Result:


- Store the `original_byte` values in a byte array.

## Reconstructing the Original `auth-key`


After performing the reversed XOR operation, the resulting byte array should represent the original `auth-key`.


Interpreting the Result:


- Convert the byte array to a string using UTF-8 decoding.

- Verify if the string makes sense (e.g., readable ASCII characters).

## Validating the Result


To ensure the correctness of our reverse-engineered `auth-key`, we can:


- Compare the length of the recovered `auth-key` with the length of the `encrypted_data`.

- Verify that the XOR of the recovered `auth-key` and the `key_data` matches the `encrypted_data`.


The final python script:


```
# Given hexadecimal values
local_48_hex = '0x5621161e143e150b'
local_40_hex = '0x0d54144a0e462c26'
local_38_hex = '0x463b471620501340'
local_30_hex = '0x04011609'
local_2c_hex = '0x00'

local_56_hex = '0x65726365735f796d'
local_4e_hex = '0x656b5f74'
local_4a_hex = '0x79'

import struct

def hex_to_bytes(hex_str, length):
# Remove '0x' and pad the hex string to the required length
hex_str = hex_str[2:].zfill(length * 2)
# Convert hex string to bytes (assuming little-endian format)
return bytes.fromhex(hex_str)[::-1]

# Extract bytes from the given values (assuming little-endian format)
local_48_bytes = hex_to_bytes(local_48_hex, 8)
local_40_bytes = hex_to_bytes(local_40_hex, 8)
local_38_bytes = hex_to_bytes(local_38_hex, 8)
local_30_bytes = hex_to_bytes(local_30_hex, 4)
local_2c_bytes = hex_to_bytes(local_2c_hex, 1)

# Combine the encrypted data bytes
encrypted_data = (
local_48_bytes +
local_40_bytes +
local_38_bytes +
local_30_bytes +
local_2c_bytes
)

# Extract bytes for the key
local_56_bytes = hex_to_bytes(local_56_hex, 8)
local_4e_bytes = hex_to_bytes(local_4e_hex, 4)
local_4a_bytes = hex_to_bytes(local_4a_hex, 1)

# Combine the key bytes
key_bytes = local_56_bytes + local_4e_bytes + local_4a_bytes

# Calculate the length of the key
key_length = len(key_bytes)

# Reverse the XOR operation to recover param_1
param_1_bytes = bytearray()

for i in range(len(encrypted_data)):
key_byte = key_bytes[i % key_length]
decrypted_byte = encrypted_data[i] ^ key_byte
param_1_bytes.append(decrypted_byte)

# Output the result
print("Recovered param_1 bytes:", param_1_bytes)
print("Recovered param_1 in hex:", param_1_bytes.hex())
```


## Conclusion


By reverse engineering the `dead_browse` binary and analyzing the XOR operation, we successfully recovered the `auth-key` needed to interact with the server and retrieve the flag.

## Lessons Learned


- Reverse Engineering Skills: Understanding how to analyze binaries and interpret assembly code is crucial.

- XOR Operations: Recognizing and reversing XOR encryption is a common task in reverse engineering challenges.

- Dynamic vs. Static Analysis: When dynamic analysis is impractical, static analysis can provide the necessary insights.

- Scripting: Writing custom scripts (in Python, for example) is invaluable for automating the reversal of encryption or encoding schemes.

## Final Notes


This challenge was an excellent exercise in reverse engineering and problem-solving. By methodically analyzing the binary and applying our knowledge of encryption techniques, we were able to uncover the necessary information to retrieve the flag without needing to execute the binary.


Feel free to use this write-up as a guide for similar challenges or to understand the steps involved in reversing a simple XOR-based encryption scheme.

---

*Originally published on [Medium](https://micro1010.medium.com/deadface-ctf-dead-browse-1-reverse-engineering-challenge-write-up-9be8a0231814). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of reverse engineering CTF writeups.*
