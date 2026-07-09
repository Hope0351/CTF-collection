# Free Range Packets


Attachment: [freeRangePackets.pcapng](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

## Writeup

Based on the challenge description, I knew I had to carve out the btl2cap field from the capture file. With tshark and some further grepping and cutting I can eventually cleanly get the flag out.

```bash
tshark -r freeRangePackets.pcapng -Y 'btl2cap.payload' -T fields -e btl2cap.payload 2>/dev/null|grep -v '09ff01065c'|cut -c 7-|cut -c 1-2|xxd -r -p
```




flag{b5be72ab7e0254c056ffb57a0db124ce}
