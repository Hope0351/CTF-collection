# 🔍 Forensics CTF Writeup: PicoCTF

> **Original Source:** [Forensics CTF Writeup: PicoCTF](https://medium.com/@divyanshurds.kumar/forensics-ctf-writeup-picoctf-3cc1a13daaa7)
> **Platform:** medium.com | **Category:** `FORENSICS` | **Event:** picoCTF

---

## 📝 Full Writeup

Forensics CTF Writeup: PicoCTF[![Divyanshu Kumar](https://web.archive.org/web/20260204024235im_/https://miro.medium.com/v2/resize:fill:64:64/1*IFyJY-V_isCKrFk9mbb7qA.jpeg)

](/web/20260204024235/https://medium.com/@divyanshurds.kumar?source=post_page---byline--3cc1a13daaa7---------------------------------------)

[Divyanshu Kumar](/web/20260204024235/https://medium.com/@divyanshurds.kumar?source=post_page---byline--3cc1a13daaa7---------------------------------------)

·
Jul 12, 2025

[

](/web/20260204024235/https://medium.com/m/signin?actionUrl=https%3A%2F%2Fmedium.com%2F_%2Fvote%2Fp%2F3cc1a13daaa7&operation=register&redirect=https%3A%2F%2Fmedium.com%2F%40divyanshurds.kumar%2Fforensics-ctf-writeup-picoctf-3cc1a13daaa7&user=Divyanshu+Kumar&userId=208ddea23d88&source=---header_actions--3cc1a13daaa7---------------------clap_footer------------------)

--



## When Packets Break Your Soul (with Evidence)
## 🕵️ The Challenge
The CTF task was simple on the surface: analyze a `.pcap` file with just **22 packets**. That's supposed to be easy, right? Spoiler: it wasn't.

The hint was vague — just analyze the network capture and find something hidden. No protocol to focus on. No specific port. Just raw packets. At this point, I should’ve known this was going to be a journey through pain.

## 🔬 Phase 1: Wireshark — The Manual Madness
I opened the `.pcap` file in Wireshark like any sane forensics person would. I began clicking through each packet manually, checking payloads, trying to follow TCP streams. What I got? Noise. Junk. Absolutely no clear flag or message.

I resorted to **manually copying ASCII strings** from the packet payloads, then pasting them into a Base64 decoder online one by one. Here’s how that cycle went:

- Click packet

- Expand data

- Copy ASCII

- Paste into terminal or browser

- Run `base64 -d`

- Get garbage or `invalid input`

- Repeat 21 more times

It was hell. The kind of time-wasting that makes you question your life decisions.

A few strings decoded to gibberish, some to fragments that looked promising (`1t_w4s`, `318db22`, etc.) — but I had no full picture.

I needed to stop being a caveman.

## ⚔️ Phase 2: Automate or Die Trying
So I turned to `tshark`, the command-line alternative to Wireshark. I figured if I could extract all the TCP payloads, I might be able to automate the decoding process.

My first commands were disasters:

```
tshark -r myNetworkTraffic.pcap -T feild -e feild frame.time -e tcp.payload | sort | awk "{print $6}"
```

Yes, I misspelled `fields` twice. Yes, I was deep in the "terminal rage" zone.

After testing, re-testing, failing, tweaking — I got a working command:

```
tshark -r myNetworkTraffic.pcap -T fields -e tcp.payload | xxd -r -p | base64 -d
```

Or with more structure:

```
tshark -r myNetworkTraffic.pcap -T fields -e frame.time -e tcp.payload | sort | awk '{print $6}' | xxd -r -p | base64 -d
```

And then…

**BOOM. Payoff.**

```
picoCTF{1t_w4snt_th4t_34sy_tbh_4r_f318db22}
```

## 🧠 Lessons Learned
- **Manual decoding is pain**: Don’t do it unless you’re stuck on an island without a keyboard.

- **TShark is a savior**: Learn it early, use it often.

- **Base64 is everywhere in CTFs**: If it smells like junk, try decoding it.

- **Packet order matters**: Sorting by timestamp helped reconstruct the original message.

- **Error messages matter**: They guide you through madness.

## 💣 Real Talk: Frustration Level 9999
This CTF wasn’t technically hard — but it was a test of **grit**. It was about how long you could stay in the chair, pounding out commands, screaming internally, and still push forward.

It wasn’t elegant. It wasn’t fun. It was raw, real, annoying forensics.

But damn — when I saw that flag appear?

> 
***pure dopamine.***

## ✅ Final Thoughts
CTFs like this aren’t always glamorous. They’re dirty, they’re frustrating, they test your patience more than your tools.

But that’s exactly what makes them valuable.

**You don’t just learn commands. You learn to survive.**

**Flag:** `picoCTF{1t_w4snt_th4t_34sy_tbh_4r_f318db22}`

---

*📖 Originally published on [Medium](https://medium.com/@divyanshurds.kumar/forensics-ctf-writeup-picoctf-3cc1a13daaa7). All credit goes to the original author.*
*📂 Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of forensics CTF writeups.*
