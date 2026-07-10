# :arrows_counterclockwise: Reverse Engineering WannaCry Ransomware: A Deep Dive

---

# Reverse Engineering WannaCry Ransomware: A Deep Dive

The WannaCry ransomware attack of May 2017 was a watershed moment in cybersecurity, exposing vulnerabilities in the Windows operating system that led to widespread disruption across various sectors. The malware’s ability to propagate rapidly and encrypt files while demanding ransom from users highlighted the urgent need for a robust understanding of such threats. This article delves into a detailed reverse engineering analysis of WannaCry, exploring its structure, behaviors, and methods to equip cybersecurity professionals and enthusiasts with insights into its inner workings.

## Step 1: Initial Identification of WannaCry

Upon executing the WannaCry sample in a controlled environment, several distinct characteristics become apparent:

## Key Indicators of Infection

- Desktop Alteration: WannaCry changes the infected machine’s desktop wallpaper to a message indicating compromise. This serves to intimidate and inform victims.

- User Interface: It generates a window with a countdown timer for ransom payment, urging urgency. This is often accompanied by payment buttons that direct users to Bitcoin payment instructions.

- File Encryption: The ransomware encrypts files on the host, appending the `.WNCRY` extension to each encrypted file. This renders the files inaccessible without the decryption key.

- Malicious Artifacts: It drops an executable named `@WanaDecryptor@` and a text file labeled `@Please_Read_Me@`, which contain ransom instructions.

## Step 2: PE Analysis

To further analyze WannaCry, we need to examine its Portable Executable (PE) structure.

## Initial Checks

- PE Header: Open the sample in a PE analysis tool (like PE Explorer). Confirm the presence of a DOS header. This indicates we are working with a PE file.

- String Analysis: Utilize tools like FLOSS to extract strings. Look for indications of functionality, such as:

- Base64-encoded strings, hinting at obfuscation methods.

- File paths with token replacements, suggesting attempts to manipulate system files discreetly.

## Key Findings

- Obfuscation Techniques: The presence of base64 strings may indicate that critical functions and communications are hidden from static analysis, complicating detection.

- Dynamic Linking: Identify dynamic link libraries (DLLs) used, particularly those associated with networking, as they provide clues about the malware’s capabilities.

## Step 3: Networking and Propagation Analysis

WannaCry employs complex networking mechanisms to spread across systems.

## Propagation Mechanism

- Exploitation of Vulnerabilities: It uses the EternalBlue exploit, targeting vulnerabilities in Microsoft’s Server Message Block (SMB) protocol. This is pivotal for its self-replication.

- Scanning for Targets: Once executed, WannaCry scans local networks for vulnerable devices, attempting to exploit them without user interaction.

## Get Itz.sanskarr’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

## Observing Network Behavior

- Network Traffic Capture: Use Wireshark to monitor traffic. Look for:

- Connections made on port 445 (SMB).

- Attempts to reach external IPs for command and control.

## Self-Replication:

- WannaCry’s ability to replicate itself allows it to spread like a worm, making it particularly damaging in networked environments.

## Step 4: Persistence Mechanism

To ensure ongoing operation, WannaCry incorporates various persistence techniques.

## Analysis of Persistence

- Service Creation: The malware creates a service with a randomly generated name using Windows APIs (e.g., `CreateServiceA`). This enables it to restart automatically after a system reboot.

- Hiding Artifacts: By using the `attrib +h` command, WannaCry hides its operational files, making detection difficult for traditional security software.

## Key Points to Investigate

- Service Attributes: Analyze the service created by WannaCry for unusual attributes or behaviors.

- File System Examination: Check for hidden files and folders where the malware may store its components.

## Step 5: Kill Switch Analysis

One of the more fascinating aspects of WannaCry is its built-in kill switch mechanism.

## Understanding the Kill Switch

- Connection Check: Upon execution, WannaCry attempts to connect to a specific URL. If the connection is successful, it refrains from executing its encryption routine; if unsuccessful, it proceeds to encrypt files.

## Debugging the Kill Switch

- Setting Breakpoints: Using a debugger like x64dbg, set breakpoints at the API calls associated with the kill switch URL.

- Flow Control: Analyze how WannaCry decides whether to execute or halt based on the success of the connection.

## Understanding Zero Flag (ZF) Manipulation

The Zero Flag (ZF) in x64dbg indicates the success or failure of operations. Here’s how it affects WannaCry’s execution:

- Flow Control: If the connection to the URL is successful, ZF will be set. WannaCry will skip the encryption routine.

- Forcing Execution: To manipulate this behavior, change the ZF value:

- Use the debugger to inspect the register state. If ZF indicates success, modify it to force the ransomware to execute its payload, even if it detects a successful connection.

## Manual Manipulation

- Redirecting Execution: By altering the ZF during execution, redirect the flow to the encryption code. This allows you to observe the encryption routine in action.

- Outcome Observation: After bypassing the kill switch, note how WannaCry begins encrypting files across the system.

## Conclusion: Key Takeaways

Analyzing WannaCry provides essential insights into modern ransomware design. Its propagation methods, persistence mechanisms, and kill switch highlight significant challenges in cybersecurity.

---
