# :game_die: Risen Ransomware — Letsdefend Challange

---

# Risen Ransomware — Letsdefend Challange

Hello, my digital adventurers! Today, we will tackle a new LetsDefend challenge about the Risen Ransomware.

*Scenario: You are a cybersecurity analyst at a mid-sized tech company. One morning, you receive multiple reports from employees stating that they are unable to access their files. Upon investigation, you discover that all files have been encrypted and appended with a new extension. A ransom note left on the desktop demands payment in cryptocurrency to decrypt the files. The ransomware responsible for this attack is known as Risen Ransomware. Your task is to analyze the Risen Ransomware.*

To analyze this ransomware, I will use IDA, which is a powerful disassembler and debugger used for reverse engineering malware.

### Analysis

Open IDA and drag and drop the ransomware file into it.

### Question 1

*Which text file was opened by the malware after initializing a critical section?*

To find the answer, we need to consider which function can create and open files. CreateFileW serves this purpose. Malware commonly uses this function to open, create, or…

---
