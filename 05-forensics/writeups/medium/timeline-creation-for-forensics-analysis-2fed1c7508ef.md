# :mag: Timeline Creation For Forensics Analysis 2Fed1C7508Ef

> **Original Source:** [Timeline Creation For Forensics Analysis 2Fed1C7508Ef](https://infosecwriteups.com/timeline-creation-for-forensics-analysis-2fed1c7508ef)
> **Platform:** infosecwriteups.com | **Category:** `FORENSICS`

---

## Introduction


The idea behind timeline analysis is to list out the events that happened in your system in chronological order. This will help you to analyze the events and their consequences.


For example,


If a hacker hacks into your PC through a malicious MS word. Then, creates a new user and enables RDP on your machine for later access.


Then the events will look similar to the below:


MS word opened -> Macro execution -> TCP connection established -> new user created -> RDP enabled


## Get @fuffsec’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Hence, we need the events in order to recognize the pattern and come to conclusion.

### Event Types


You may want the following events in your timeline for analysis.


- System events

- File activity

- Browser activity

- Application activity

- Logs and Events

### Approaches for event collection


- Automatically gather everything (Super timeline)

- Gather specific event types

### Temporal Proximity


It is a very important concept used in the analysis. It means closeness in time. Sometimes, we need to find different events at the closest time. The closer, the better.

### Timestamp Types


- 64-bit Filetime

- 32-bit Unix time format

- string-based format

- systemtime

### Expected Timeline components


We might need some components for the successful analysis of the timeline. Some of them are,


- Timestamp

- Source

- Source type

- Description

- Type

---

*Originally published on [Medium](https://infosecwriteups.com/timeline-creation-for-forensics-analysis-2fed1c7508ef). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of forensics CTF writeups.*
