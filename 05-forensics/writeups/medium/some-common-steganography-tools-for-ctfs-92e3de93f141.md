# :mag: Some common Steganography tools for CTFs

---

>

ExifTool:

EXIF stands for Exchangeable Image File Format. ExifTool is used to read, write and manipulate the metadata of various file types like png, jpeg, html, txt, pdf, etc.

Let us consider an image. So the metadata of the image may comprise a bunch of information such as the camera make, file type, permissions, file size, etc.

Sometimes you can find the flag of the CTF in the metadata or sometimes you may find some hints which can lead you to the flag.

You can install ExifTool in Kali Linux by the following command.

```
sudo apt-get install libimage-exiftool-perl
```

After installation, ExifTool can be accessed using the `exiftool` command in the terminal.

*exiftool monke.jpg*

You can see in the above image that the ExifTool extracted the metadata from the “monke.jpg” image.

There are many more `options` that you can use in the ExifTool but I want to keep this blog short and concise do let me know if you want me to cover any particular tool in detail.

---
