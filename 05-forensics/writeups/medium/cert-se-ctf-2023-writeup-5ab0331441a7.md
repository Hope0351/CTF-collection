# :mag: Cert-se CTF 2023 Writeup. Writeup of Cert-se 2023 CTF. Somewhat…

---

Link to challenge: [https://cert.se/2023/09/cert-se-ctf2023.html](https://cert.se/2023/09/cert-se-ctf2023.html)

As what seems to be a tradition CERT-SE did a CTF challenge, where they released zip file containing a pcap file and a worddocument of format odt.
For those who are new with CTF or just do not know what a pcap file is.

A pcap file is a file containing networkpackets, basically network traffic that have been captured in a file format, most common tools to use to view these files is Wireshark, which we will use today.

To make it a bit easier for you and me, i will describe as good as i can how i found the flags but i will also record a video and upload to my [youtube](https://www.youtube.com/channel/UCOeDRQk-TVC3rxXpiuH_aZA),( h[ttps://www.youtube.com/channel/UCOeDRQk-TVC3rxXpiuH_aZA](https://www.youtube.com/channel/UCOeDRQk-TVC3rxXpiuH_aZA)) something is just easier to show then type. I will showcase the flags i found, because the competetion finished 31th of October 2023 and i publish this 2th of November 2023.

But to continue, description of the challenge:

```
<scenario>
CERT-SE has come across files from a previously unknown fictional hacker
group. In these files there's "flags" hidden.
Can you find all the flags?
</scenario>
```

We are looking for text strings that is in the format: CTF[xxxxxxxxxx]

So before i dived into the pcap file i investigated the .odt file named: “*CERT-SE_CTF2023 — CompetenceLateRoadThink.odt*”. Already in the filename there is something that stands out, i did sadly not solve or gotten the hint if there was one.

First flag:
The first image is kind of a logo of CertSE, this one contained the first flag, with the help of Steganography, they have hidden the flag in the image, with the tool [Stegsolve](https://wiki.bi0s.in/steganography/stegsolve/), where i found the flag in the image layers.

*Stegsolve Random Colour Map 3, Flag displayed*

Flag: CTF [SNEAKY]

Second flag:
At the end of the document there was a puzzle, rebus.
“CTF[☔-ra+💿d=i+⛺t=d]”
So with some puzzle solving, my notes:
“rain” — “ra” = in
cd but replace d with i (d=i) = cd
“tent” but replace (t=d) = dent

Flag: CTF[INCIDENT]

Third flag:
Still in the document i checked the properties of the document, check for authors or something else, and of course i found “something” else.

*Properties of worddocument with flag as a value*

Flag: CTF[WILLIAM]

After a few hours of scratching my head for the riddles and texts in the document. I got to the pcap file.

Fourth flag:
When checking the protocols that was present, i saw we had a FTP, which means no encryption. So filtered out the traffic that was “FTP,FTP-DATA”
There was a directory listening with the flag in a filename:

Flag: CTF[HUNTER2]

Fifth flag:
So for the fifth and last flag i could find. There was some IRC chats about a breach and someone logging on to servers. And even files being sent, an audio file as well, that could have been a red herring or a flag, but the fifth flag i found was an image.
In the traffic and chats they have found out that a server was breached and someone had exfiltrated data from the systems. I was able to find the data and it was a privatekey and certificate, with the help of them i could filter out some of the https-traffic. When i added the certificate to wireshark it decodes the traffic and then i found a png file with the flag written in it.

*Flag of secret.png*

Flag: CTF[GALOIS]

After that i spent a few hours more to analyse the audiofile, which according to me was a Rick-n-roll in 8-bit song. Found some noises and tried to check the waves and stuff but no luck.
In the document there was a poem of William Shakespear, a lot of references to Hitchhikers guide to the galaxy, Moss from IT Crowd, DR Who, Douglas Adams. Even in the flags there is references to the people in the texts.

[Galois](https://en.wikipedia.org/wiki/Galois/Counter_Mode) for an example is a mode of operations in Cryptography.
Some references to William Shakespear was the speech from Henry V, St Crispin’s Day.

But overall even if i lost some sanity of listening to rick-n-roll on repeat for some hours and trying to figure out if there was something hidden in a image of gray slate (Swedish word is “skiffer” = Ciphers).

But i really enjoyed it and is looking forward to next years CTF from Cert SE.

Have you solved the 2 flags i could not found? Please let me know so i can sleep well at night! If you enjoyed the content consider a clap or even buy me a coffe!

Check out my youtube if you like more videos instead, content will come very soon if not already uploaded!

UPDATE!

A guy named Cyberhot found the last 2 flags,

1 in the rockimage as I suspected and at a certain frequency he found a flag in the sound file as well. The rock one I did notice but did not follow through.

The soundfile I add the tools to my knowledgebase.

Check him out here https://youtu.be/oFdY9hnn6KM?si=N9N5tfX-3p3gGxMN

---
