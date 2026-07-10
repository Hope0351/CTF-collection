# :mag: Digital Forensics — Windows USB Artifacts [Insider Threat Case]

> **Original Source:** [Digital Forensics — Windows USB Artifacts [Insider Threat Case]](https://infosecwriteups.com/digital-forensics-windows-usb-artifacts-insider-threat-case-938c35a13b7e)
> **Platform:** infosecwriteups.com | **Category:** `FORENSICS`

---

# Digital Forensics — Windows USB Artifacts [Insider Threat Case]


Hey Digital Defenders! I notice this case on LinkedIn post and wanted to write about USB forensic artifacts, piecing together evidence and reconstruct the insider threat incident.


USB Insider Threat Challenge — [https://docs.google.com/forms/d/e/1FAIpQLSev_ImZUlad0d_py_dS_2YDbcmmgpZJtcPWE4AxUQitqLf1CA/viewform](https://docs.google.com/forms/d/e/1FAIpQLSev_ImZUlad0d_py_dS_2YDbcmmgpZJtcPWE4AxUQitqLf1CA/viewform)


Case Scenario : An employee used a USB stick on an unlocked company computer to steal three confidential files from the finance department (.xlsx, .docx, .pptx). After copying the files to the USB, he opened them from the flash drive to check they were copied properly.


Forensics Mindset : When a USB flash drive is connected to a Windows system, the operating system records forensic traces across multiple artifacts that tells DFIR investigator “*what”* device was used, “*when”* it was connected, “*which user”* interacted with it and “*what user*” was trying to do or performed any data exfiltration activity.

>

*USB Forensics🔍& Key Findings*


>

USB profiling is the initial investigative steps when insider threat activity involving removable media!


Three main categories, Human Interface Devices (HID), Media Transfer Protocol (MTP) Device and Mass Storage Class.

---

*Originally published on [Medium](https://infosecwriteups.com/digital-forensics-windows-usb-artifacts-insider-threat-case-938c35a13b7e). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of forensics CTF writeups.*
