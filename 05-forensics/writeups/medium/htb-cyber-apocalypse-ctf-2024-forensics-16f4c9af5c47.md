# :mag: Load the pcap file

---

## Phreaky

>

In the shadowed realm where the Phreaks hold sway, A mole lurks within, leading them astray. Sending keys to the Talents, so sly and so slick, A network packet capture must reveal the trick. Through data and bytes, the sleuth seeks the sign, Decrypting messages, crossing the line. The traitor unveiled, with nowhere to hide, Betrayal confirmed, they’d no longer abide.

File: phreaky.pcap

### 💡Solution

We know the drill by now. We begin with a High-level analysis of the packet capture before a deep dive low-level analysis.

The TCP traffic contains Mail (SMTP) and Web (HTTP) traffic. Paying attention to the challenge description there was a hint about decrypting messages. So, we investigate the SMTP traffic further as it is clear-text.

We use *Analyze → Follow → TCP Stream:SMTP data*

This looked promising. Now we know where the gold is, let’s narrow down our network traffic and inspect SMTP data only using a filter:

```
(smtp) && (data-text-lines)
```

*Filter SMTP data*

Focusing on the length of the packet (1500+) and the data contained within it, we see quite a few packets containing ZIP archive attachments and the associated password.

If you want to filter out those 15 messages you can refine your Wireshark filter and use the following:

```
(data-text-lines) && (smtp contains "Password")
```

*Filtering by SMTP packets with the text “Password”*

Now we have 15 messages to extract, save as ZIP archives and unzip with a password, we still need a way to only export the attachment data and passwords to an external file or CyberChef for further processing.

There are three methods to achieve that task:

- Use Tshark command-line packet analyzer

- Use Python’s Scapy module to manipulate the pcap

- Use Network Miner tool

Tshark would usually do the job well, I had some partial success and have abandoned this due to time constraints. Copy/pasting can be quick and dirty as we only have 15 packets. However, we wanted a repeatable method we could use in future CTFs. This leaves us with Python and Network Minerner.

### Method 1: Using Network Miner

Network Miner is a network forensic analysis tool used to extract useful information from captured network traffic. It’s primarily designed to parse PCAP files and display information such as hosts, files, emails, and other data transferred over the network.

Our task was made very easy using this method. It involved three steps.

Step 1: Load the PCAP into Network Miner

*Network Miner examining the phreaky.pcap file*Step 2: Export the email messages using Outlook or other mail apps

*Network Miner examining the 15 mail attachments*Step 3: Export the EML file to disk or open it with your mail application

*Email file opened in Outlook*

*Unzip the attachment using the password from the same data packet*

Extract the ZIP file using the associated password found in the same packet. On this occasion for the first ZIP file, the password was: “*S3W8yzixNoL8*”.

A quick and neat way to dump only the passwords for easier processing can be achieved using our trusty Tshark:

*Tshark: Display all passwords in the SMTP data packets*

Once you have extracted files from all ZIP archives, you should end up with 15 files that seem to be part of a PDF file split into multiple parts.

*PDF file split into 15 parts*

### Method 2: Using Python and Scapy

Scapy is a powerful interactive packet manipulation program and library.
It allows you to forge or decode packets of a wide number of protocols, send them on the wire, capture them, match requests and replies, and much more. Scapy can also be used for analyzing packet captures in various ways.

The following script will help us extract the data we need from the SMTP traffic. I’ve used `ipython3`(Interactive Python) for this task:

```
from scapy.all import *

# Load the pcap file
packets = rdpcap("phreaky.pcap")

# Filter SMTP packets containing the word "Password"
filtered_packets = [pkt for pkt in packets if TCP in pkt and Raw in pkt and b"Password" in pkt[Raw].load]

# Extract data from filtered packets
email_content = []
for pkt in filtered_packets:
email_content.append(pkt[Raw].load)

# Print extracted email content
for idx, content in enumerate(email_content, start=1):
print(f"Packet {idx}:\n{content.decode('utf-8')}\n{'='*50}\n")
```

*Using Scapy modules in an Interactive Python session*

Now we have the data and the password, we turn to our trusty CyberChef tool to transform our data into ZIP files and extract them with their associated passwords. Yes, I have done this 15 times on CyberChef but with relative ease and much faster this time. I could have programmed it all in Python but that would have taken me much longer. If you are good at programming this part, please get in touch :)

*CyberChef extracting the contents of the ZIP archive*

We have 15 partial PDF files in one folder now. To merge them, I’ve overcomplicated things by trying to use PDF tools. However, I found the simplest solution you could have for this from a previous CTF solution. It’s the “KeepIt Simple Stupid (KISS)”principle.

```
$ ls | sort -V

phreaks_plan.pdf.part1
phreaks_plan.pdf.part2
phreaks_plan.pdf.part3
phreaks_plan.pdf.part4
phreaks_plan.pdf.part5
phreaks_plan.pdf.part6
phreaks_plan.pdf.part7
phreaks_plan.pdf.part8
phreaks_plan.pdf.part9
phreaks_plan.pdf.part10
phreaks_plan.pdf.part11
phreaks_plan.pdf.part12
phreaks_plan.pdf.part13
phreaks_plan.pdf.part14
phreaks_plan.pdf.part15
```

Ready for the magical and simple command to merge them all? Behold!

```
cat $(ls phreaks_plan.pdf.part* | sort -V) > phreaks_plan.pdf
```

Verify we have the final PDF file:

```
$ ls -l
total 64
-rw-r--r-- 1 cybersecmav cybersecmav 3302 Mar 19 12:46 phreaks_plan.pdf
```

Let’s open it. It’s time for the big reveal folks. I don’t know about you but I’m getting excited already :)

*Merged PDFs amounted to 2-page PDF file*

Alright, I couldn’t help but tease you and drag it out a bit. Now, the flag:

*The flag is found on page 2 of the PDF*

---
