# :mag: How the Forensics Team Collects Evidence?

> **Original Source:** [How the Forensics Team Collects Evidence?](https://infosecwriteups.com/how-the-forensics-team-collects-evidence-21e950f2c4b9)
> **Platform:** infosecwriteups.com | **Category:** `FORENSICS`

---

# How the Forensics Team Collects Evidence?


Hello Hackers, I am back with my new blog on How the Forensics Team Collects Evidence after any Cyber Crime or Digital Crime. Sounds like a cool job right?? Yes, it is a cool job but you have to be very stable and knowledgeable as this evidence may lead to someone's entire life in prison.


So, without any Complexity Let’s get Started…

>

👉🏿 PROMOTION — MY YOUTUBE CHANNEL [LINK](https://youtube.com/@securedsyntax)


*Collecting Evidence*


Let’s first check what Google says about digital Forensics:-

>

Google — “A branch of forensic science that focuses on identifying, acquiring, processing, analysing, and reporting on data stored electronically”


In Digital Forensics, there are different steps to follow and things you need to take care of. Digital Forensics starts with data acquisition, which means collecting data.


Let’s consider a scenario where you are at a crime scene. You discover a suspected system involved in an event, currently running and connected to the network. Would you turn OFF the system?


Some might say NO, and others might say Yes. However, the correct answer to this question depends on the company or department’s Incident Response Policy and Procedures. Also, If we turn OFF the system we will lose the Computer’s Memory and some Volatile Data such as logged-in users, TCP Connections, and the Running Processes.


So, It is good practice to extract the volatile data first before turning OFF the System.


But Now there is another problem here. How we should Turn OFF the System?


Gracefully??????

*Graceful shutdown*


or Forcefully??????????

*ForceFul shutdown*


Jokes apart😂……


Forceful shutdown means just yanking the power cord. So, let’s analyze both the methods of shutting down the system.


I. Graceful Shutdown —
It ensures that the system remains in a consistent state by storing information on disks, notifying users and services, etc. However, criminals sometimes may have installed the rootkit, to destroy the evidence. Criminals program these rootkits in that way if they receive any graceful shutdown command then the program will completely wipe out the data or evidence. (a fine example of a genius plan).


II. Forceful Shutdown —
If we Turn OFF the system forcefully just by yanking the power cord. It will avoid the loss of evidence caused by the rootkit. But, it can lose data on the cache(not written on disk), and leave the system in an inconsistent state, but you will still lose the volatile data.

>

NOTE- As per Forensics you should always go with the forceful shutdown, and record all activities.


I hope you’ll get a firm understanding of this topic. So, let’s do some practical thing in which I will take a USB drive and consider it as evidence found at a crime scene. And, I will teach you how to extract the evidence from this USB Drive.


So, the main goal of Data acquisition is to extract and preserve the data. Preserving data means the evidence should be on the original device and all the tests and techniques should be performed on the copy of the evidence. The data should be consistent from the time it gets collected to the time it gets to the court.


Let’s see how we can create a copy of the suspected device (USB Drive in this case). But if you are thinking of copying the evidence like we copy other files from the USB drive to our Computer using copy and paste. So, let me tell you...YOU ARE ABSOLUTELY WRONG.


Because the normal copy command will only copy the content, not the Empty or Deleted Data.


So to create an entire bit-by-bit image of USB-Drive, we’ll use one of the best tools of Digital Forensics,[FTK Imager.](https://accessdata-ftk-imager.software.informer.com/3.1/)


## Get Rajneesh Kumar Arya’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Here’s what it will look like.


*FTK Imager Interface*


Now, to create a copy image of the USB Drive, first you need to plug in the USB Drive. Navigate to File >> Create Disk Image…


*Create Disk Image... Option*


After clicking on Create Disk Image… you need to select the source evidence type which will be Physical Drive in the case of USB. Select Physical Drive and click Next >.

*Please Select the Source Evidence Type*


Now select your USB Drive and click on Finish.

*Select Drive*


Now, we need to select the Destination to store the Image file. Click Add and select the Raw(dd).

*Select Image Type*


Now, we need to fill in the details of evidence such as evidence number, Unique Description, Examiner Name, etc. And then click Next >.

*Evidence Item Information*


The new window will pop up and ask for the Image Destination Folder. Click Browse


*Select Image Destination*


Select your desired location, I am selecting Desktop for simplicity.


*Browse For Folder*


In the Image Filename, just put your desired name to the file. Like *FTK Imager Demo* (in my case), Click Finish.


Now, Click on Start, and the process will start. See the screenshot below.


After the process is complete the image file will be successfully stored in the given location now close all the windows. Now, to check what the image file is extracted you need to again navigate to File >> Add Evidence Item…


*Add Evidence Item…*


In the source type, Select Image File, and then click Next >.


It will then ask for the file location. So, click Browse… and select the file where you set the location to save the evidence file (Desktop, in my case). Click Finish and the evidence file will be imported.


Now the image file is successfully loaded, and you can click on +, open the branch of files and the file which has cross in it are the deleted files which are extracted by FTK Imager.


I hope you’ve learned something new and interesting. Now, before ending this blog. A quick promotion “If you find my blogs or video content on Youtube helpful then please consider a subscribe”.


Till then KEEP LEARNING, KEEP EXPLORING, and most importantly DO HACKING…..

---

*Originally published on [Medium](https://infosecwriteups.com/how-the-forensics-team-collects-evidence-21e950f2c4b9). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of forensics CTF writeups.*
