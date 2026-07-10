# :mag: Shell Ctf 2022 Forensics Writeup 258C9D7Dbd8

---

## [*] Hidden File

============

The attachment file is a JPG file (Hidden.jpg).

From the [file](https://www.geeksforgeeks.org/file-command-in-linux-with-examples/)command, I got a password for something.

In a lot of forensics CTFs, when you find the password directly like this, this means that there is something hidden inside this file and it needs this password to extract it.

For extraction, I used [Steghide](http://steghide.sourceforge.net/)tool with password “shell”, and we got a “Hidden Files.zip”file

By unzipping, you’ll get a three files (flag.zip “needs password” , se3cretf1l3.pdf, something.jpg)

something.jpg is a QR code image, after I scanned this QR code, it gave me a youtube link for “Never Gonna Give You Up” song (yeah, I got rickrolled XD), so this file is nothing

Now move to se3cretf1l3.pdf, it’s an one page pdf file that does not contain any important information.

It’s very obvious that this pdf file contains hidden data so you have to extract this data.

For me, I love to pass the PDFs files to [This Website](https://www.extractpdf.com/) first to extract any hidden data in images, text or fonts

Upload the PDF file and click on Text section, you’ll find the hidden key (shellctf)

Finally, use this key to unzip the flag.zip file and you’ll get the flag :)

```
Flag: shell{y0u_g07_th3_flag_N1c3!}
```

---
