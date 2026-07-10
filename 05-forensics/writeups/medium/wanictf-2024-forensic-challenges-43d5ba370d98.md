# :mag: WaniCTF 2024: Forensic Challenges

---

# WaniCTF 2024: Forensic Challenges

Hello readers, I hope you guys are doing good. So recently I have participated the WaniCTF. Solved challenges of web, crypto, forensics and pwn. However, I have solved all the forensics challenges. These challenges were from easy to hard level. In this write-up we will know how to solve the forensics challenges. Before starting kudos to all the CTF challenge creators of WaniCTF

So……

>

Challenge 1
Title: tiny_usb
Level: Beginner
Description: What a small usb!
File: [https://mega.nz/file/k45VkYKI#33g2zbFOa5zU14DGXxvK6vOfmEhHcIJwU_6DMgWycps](https://mega.nz/file/k45VkYKI#33g2zbFOa5zU14DGXxvK6vOfmEhHcIJwU_6DMgWycps)

So, initially we unzipped the files and there is an iso file. ISO file is basically an disc image file, so to open this iso file we need to mount it to our system.

Mounting this will be easy in windows system.

Now if we click on the file we can see an option “Mount” over the tool bar. Just click it and the iso file will be mounted on our system.

As soon as you mount it the image file named FLAG.PNG is available to us.

>

FLAG: FLAG{hey_i_just_bought_a_usb}

— — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

>

Challenge 2
Title: codebreaker
Level: Beginner
Description: I, the codebreaker, have broken the QR code!
File: [https://mega.nz/file/UtYHhaxJ#3QT-j2cGTOPQTtuJReQ81iARL2vn3ZjGEtPj5jX7ngo](https://mega.nz/file/UtYHhaxJ#3QT-j2cGTOPQTtuJReQ81iARL2vn3ZjGEtPj5jX7ngo)

This challenge is termed as beginner but me along with many players faced many troubles while solving this challenge. To be very honest this should be medium or hard level challenge.

Coming back to the challenge. After unzipping the files, we got a broken qr code.

Now the thing is we can solve this qr code in 2 ways.

1st way to build from scratch using [QrazyBox](https://merri.cx/qrazybox/). Which is hectic and very time taking.

2nd way is to remove the X mark. Going for the technicalities, any qr code gets scanned with the top 3 boxes. So somehow we need to take that X mark out of the qr code.

I tried many tools to get that X mark out of the qr code but failed. After around 6 hours, my teammate suggested me that “ what if we can remove the pixel of the X mark”. I thought for a bit and tried to remove the pixel for X mark.

I tried many tools but there was one tool which came in handy and it was gimp tool. I used the online version and removed the X mark from the qr code.

As you can see in the screen shot the three boxes are now clearly visible. So, we can scan it now. Once we scan it we have our flag.

>

Flag: FLAG{How_scan-dalous}

— — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — -

>

Challenge 3
Title: I_wanna_be_a_streamer
Level: Easy
Description: Sorry Mom, I’ll work as a streamer.
Watch my stream once in a while.
(H.264 is used for video encoding.)
File: [https://mega.nz/file/shggwQSQ#PT2oak5qAJ7suRtRqCM6k9gN5lCPctPfVYPIqOV0rIA](https://mega.nz/file/shggwQSQ#PT2oak5qAJ7suRtRqCM6k9gN5lCPctPfVYPIqOV0rIA)

Upon unzipping the file, we got a pcap file. So, I tried it open that pcap file network miner as well as the wireshark. From the initial reading on description indicates that we need to watch a video to get the flag. But the real question is how we will get a video from the RTP streams? I spent around 3 hours busting my head to get this file. I had tcp stream, RTP, RSTP streams which I had no idea what that was about, later after reading about them then I got to know that RTP is Real-Time Transport Protocol. However, after knowing what RTP is, I had no lead.

Then I left it and went for lunch. After coming back I read the description once again. “H.264 is used for video encoding”, hmm h264 this is a encoding type which I have seen last in Adobe Premiere Pro when rendering any video files. I thought there might be some connection over here with it. So, I started to search for H.264 encoding and specifically searched for “H.264 decryption from RTP in wireshark”.

Which gave me tons of resources.

These three resources gave me an idea what I needed to do. However, one thing which went over sight was this GitHub repository. Which should a technique to get the h264 video file from the RTP protocols in wireshark.

I followed the instructions written in the repository. Basically this github repo is a plugin of wireshark, which allows user to extract h264 file from rtp packets.

*Decrypted packets*

Once you extract the file it will be stored in a extension of 264 file. Which we need to convert into MP4.

>

FLAG: FLAG{Th4nk_y0u_f0r_W4tching}

Honestly, this was challenge which pushed my limits, and the moment I solved this challenge. I was all pumped up to write about this in my write-up.

## Get Sidharth Panda’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

— — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

>

Challenge 4
Title: Surveillance_of_sus
Level: Normal
Description: A PC is showing suspicious activity, possibly controlled by a malicious individual.
It seems a cache file from this PC has been retrieved. Please investigate it!
File: [https://mega.nz/file/csQ0gSYL#CCxt_mMuG4zye8KMK0LgSCL-9PkQ3iRCgQOsTkkpBiI](https://mega.nz/file/csQ0gSYL#CCxt_mMuG4zye8KMK0LgSCL-9PkQ3iRCgQOsTkkpBiI)

As mentioned in the description we got a bin file, which I took into my linux machine to analyze it.

Now the thing is what to do with this bin file. So, let us start with basics, knowing about the file. I used file command and the exiftool command to know about the file. The exiftool command working at its best, gave me a error “Unknown file type”. Initially my thought was this will be basic magic bytes manipulation. But it was something new.

When I used hexeditor to get the hex of this file. I got RDP8bmp on file headers. I literally had no idea what that is, I checked all the list of file signatures.

But I got not a single lead from there. Out of frustration, I just searched “rdp cache”.

Where I read the following.

*The RDP caching mechanism reduces the amount of data that needs to be sent to an RDP client. It does this by caching those parts of the screen that haven’t changed since the display was last refreshed.*

Okay!!! So, it is a caching mechanism which reduces the amount of data that needs to be sent. So, in there the data would be reduced too.

On further exploring this topic I came across the above article, which helped me to get the flag. It literally had all the tools which came useful to solve this challenge.

To understand it in laymen language, The file which is given to us is bin file which has multiple bmp files. BMP files are one kind of image files. Caching through rdp is a mechanism which compresses all the bmp files and stores it in one bin file.

>

FLAG: FLAG{RDP_is_useful_yipeee}

— — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

>

Challenge 5
Title: tiny_10px
Level: Normal
Description: What a small world!
File: [https://mega.nz/file/t1QCGKQD#5rB4b-4uwaKbTeVxjgzvXRFoS2WwEkziCKVy3pAyd-0](https://mega.nz/file/t1QCGKQD#5rB4b-4uwaKbTeVxjgzvXRFoS2WwEkziCKVy3pAyd-0)

This was another nightmare for me and took me hours to understand what to do. If you open this file then it will have very tini tiny image of literally 10 pixels. Initially I thought I would increase the size of the image through any image resizer, then will look into the file using [fotoforensics](https://fotoforensics.com/)or [forensically](https://29a.ch/photo-forensics/#forensic-magnifier)

But that wasn’t the case. While digging the internet to understand what to do. I came across this file.

So, Basically we had to change the image’s height and width in the hex format to get the hidden data. Well this looks pretty easy trust me it isn’t.

I changed the bytes from ff c0 00 11 08 00 0a 00 0a to ff c0 00 11 08 01 40 01 40 and got the flag.

If you zoom in and see the contents carefully, we will get the flag

>

FLAG: FLAG{b1g_en0ugh}

— — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — -

>

Challenge 6
Title: mem_search
Level: Hard
Description: I found an unknown file, and upon opening it, it caused some strange behavior, so I took a memory dump!
How was the attack carried out?
The memory dump is large, and you can download it from the following URL (it will be 2GB when extracted).
Note: There are two flags in the file. The flag that starts with FLAG{H is not the correct answer. Please submit the flag that starts with FLAG{D.
File: [https://mega.nz/file/9wZTUQCa#OqVpt800mr0BirZgNdlsdZIOuahLGtjH3pF54Hz375U](https://mega.nz/file/9wZTUQCa#OqVpt800mr0BirZgNdlsdZIOuahLGtjH3pF54Hz375U)

This is challenge is mentioned as hard challenge but it was one of the easiest challenge. So, from description we know what we have to do. Since it is memory dump. I used volatility3 to analyze the memory dump. As per the description we need to look for the file, which indicates we need to use filescan plugin.

I found two files, which could be suspicious. One was echo.txt and another was read_this_as_admin.download.

I took virtual address of both the files and downloaded it in my system.

I checked both the files one by one.

Oh okay!!! So, this is a rabbit hole file. Let’s check the other file.

yesss.. the powershell script with an encrypted command, let us decipher it.

With the help of cy[berchef](https://gchq.github.io/CyberChef/)I decoded the encrypted command at it. It was base64 encoded so pretty easy to decode.

Once decoded we can check the command and there it was another encrypted text but in two parts.

>

FLAG: FLAG{Dayum_this_is_secret_file}

One resource which will be helpful to you guys for volatility.

And done. Successfully completed all the challenges of forensics.

Conclusion

All the challenges were great, especially then one with RTP protocols, It really pushed me to get the flag. Once again kudos to all CTF challenge developers.

This is it for this write-up, we’ll meet in another one. Till then keep hacking, be safe and keep learning.

---
