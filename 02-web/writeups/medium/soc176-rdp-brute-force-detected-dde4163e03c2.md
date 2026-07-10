# :globe_with_meridians: SOC176 — RDP Brute Force Detected

---

# SOC176 — RDP Brute Force Detected

In this writeup, I will investigate one of the alerts on Letsdefend, “SOC176 — RDP Brute Force Detected”.

This alert is about a brute force attack on the rdp service. Let’s investigate

## Detection

We have following artifacts:

Source_IP Address : 218.92.0.56

Destination_IP Address : 172.16.17.148

Hostname : Matthew

Protocol : RDP

Knowing these, we can create a playbook and continue to investigation.

We choose “external” because looking up this source_IP reveals that it belongs to an external source. I will show you in the next step.

## Analysis

### VirusTotal

### AbuseIPDB

---
