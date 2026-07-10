# :game_die: DawgCTF 2021 WALKTHROUGH. This is a new experience for me. I only…

---

This is a new experience for me. I only focus on the forensic challenges.

I just download the file. it’s a pcapng file. First of all, I don’t know what is the challenge and what they mean. After some googling, I find that the flag is hidden in a packet comment.I use some random filters to find the packet comments from the pcap file. But it doesn’t work.

>

pkt_comment contains “searchString”tshark -r dump.pcapng -T fields -e pkt_comment -R pkt_comment | grep SearchString

You can see that in this case, we need to know what string format is we needed. But I don’t know the actual flag format. Then I try another method its work it

## Get BlackMamba’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

open the pcap file in the Wireshark and go to the left corner . You can see a red dot . Press it , Yes we got it

We can you another effective alternative frame to find the flag.use

>

frame.comment.contains “DawgCTF”

THANK YOU ;

---
