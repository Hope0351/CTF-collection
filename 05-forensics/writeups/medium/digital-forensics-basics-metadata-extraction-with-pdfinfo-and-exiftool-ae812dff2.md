# :mag: Digital Forensics Basics: Metadata Extraction with pdfinfo and exiftool

---

# Digital Forensics Basics: Metadata Extraction with pdfinfo and exiftool

## Introduction to Digital Forensics Tools

In the field of digital forensics, collecting and analyzing data from various digital devices is crucial for uncovering valuable information. Whether it’s investigating a crime or analyzing data in a corporate environment, forensic analysts rely on various tools to extract metadata and examine digital files. In this blog, we will explore two basic yet powerful digital forensics tools: pdfinfo and exiftool. These tools help extract useful metadata, which can provide clues during an investigation.

## 1. pdfinfo

pdfinfo is a tool used to extract metadata from PDF files. It can reveal information such as the author, creation date, modification date, and other document properties.

### Key Features of pdfinfo:

- Extracts metadata from PDF files.

- Displays document properties like title, author, subject, and creation date.

- Can be used to detect inconsistencies in document metadata, which may indicate tampering.

### Example Usage:

To analyze a PDF file using pdfinfo, use the following command in your terminal:

```
pdfinfo document.pdf
```

Sample Output:

```
Title: Forensic Report
Author: John Doe
Creator: Microsoft Word
Producer: Acrobat PDFMaker 15.0 for Word
CreationDate: Wed Jul 14 11:34:52 2023
ModDate: Thu Jul 15 09:23:18 2023
Tagged: yes
Pages: 22
Encrypted: no
```

In this example, you can see information about the author, creator, and the dates of creation and modification. This data can help investigators verify the authenticity of the document or identify when and by whom it was last modified.

## 2. exiftool

exiftool is one of the most widely used tools for extracting metadata from various types of files, including images, documents, and videos. It can pull metadata from EXIF, IPTC, and XMP tags, making it invaluable for forensic investigations involving multimedia.

### Key Features of exiftool:

- Supports a wide range of file formats (images, audio, video, documents).

- Extracts and modifies metadata.

- Helps identify geolocation, timestamps, camera details, and more.

### Example Usage:

To extract metadata from an image file:

```
exiftool image.jpg
```

Sample Output:

```
File Name: image.jpg
File Size: 5.6 MB
File Type: JPEG
MIME Type: image/jpeg
Camera Model: Nikon D3500
Create Date: 2023:09:15 16:28:45
GPS Latitude: 37 deg 48' 16.80" N
GPS Longitude: 122 deg 24' 10.80" W
```

The output reveals details about the camera used, the image’s creation date, and even GPS coordinates if geotagging was enabled. For digital forensics, this information can help identify the source of the image and track down where and when it was taken.

## Conclusion

Both pdfinfo and exiftool are essential tools in the digital forensics toolkit, enabling analysts to extract valuable metadata from PDF documents and image files. These tools can provide insights into file origins, document authenticity, and much more, making them vital for any forensic investigation.

## Get Nipun Negi’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

If you’re starting in digital forensics or need reliable tools to gather metadata, mastering pdfinfo and exiftool is a great way to build foundational skills.

---
