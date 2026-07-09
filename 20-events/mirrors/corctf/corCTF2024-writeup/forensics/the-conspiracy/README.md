# the-conspiracy

## Description

Our intelligence team created a chat app, and secretly distributed it to the lemonthinker gang.
We've given you the application source and a capture taken by one of our agents - can you uncover
their plans?

## Attachments

[challenge.pcap](attachments/challenge.pcap)

[source.py](attachments/source.py)

## Solution

- Glancing at the provided <code>source.py</code> file gives us an idea of how this "chat app" works:
it reads a message from a CSV file, encrypts it, then sends the encrypted message and the keys over the
network in a pair of packets. The first packet contains the encrypted message, and the second packet
contains the <code>keys</code> array that was used in the encryption.

- I opened [Wireshark](https://www.wireshark.org/) with the <code>challenge.pcap</code> file and examined the TCP packets. Sure
enough, the data of each of these packets was an array of numbers representing either an encrypted
message or that message's keys. I copied the data from each TCP packet and pasted it into a text
file that you can view [here](packet_data.txt).

- Now, we need to decrypt all of the data we got from <code>challenge.pcap</code> to recover the
original messages. I wrote my own [Python script](solution.py) to reverse the actions taken by <code>source.py</code>.
My script reads two lines from [packet_data.txt](packet_data.txt) and stores them in the <code>final_message</code> and
<code>keys</code> arrays, respectively. The original message is then decrypted by performing the steps
of the source code's <code>encrypt()</code> function in reverse: first, we divide each number in
<code>final_message</code> by its corresponding number in <code>keys</code>, then we convert the
results to their ASCII characters.

- This process is repeated until all of the data from the packet capture is read. The fully decrypted
message can be found [here](decrypted_message.txt). Within that message is the flag in plaintext.

## Flag

corctf{b@53d_af_f0r_th3_w1n}
