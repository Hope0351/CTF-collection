### Challenge description

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

For this forensics challenge, we get the following files.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Running strings on the shortcut file we can see powershell being used:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The invoice.vbs file contains what we would expect, obfuscated malicious code.

![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

The logs.zip contains evtx files. I used evtx_dump.py to convert these into readable format for linux so I can easily grep through them.

```bash
for file in ./*.evtx;do evtx_dump.py "$file" > converted/"${file%.evtx}.xml";done
```

Because we already know powershell was used, after converting all the event viewer logs, we can run strings on everything and grep for powershell:

```bash
strings *|grep powershell
```
We quickly find some interesting stuff. We see a powershell command was run with a base64 string:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Decoding that string, we can see a Google Sheets URL:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

However, we can't seem to access this URL so this is as far as we go for now:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We've collected quite a lot of information so far. Let's spawn the docker and connect to the provided IP and port using netcat. We are informed that in order to get the flag, we have to answer some questions.

Question 1:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

When we grep for powershell, we can also see this line which gives us the answer we are looking for:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Question 2:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

There are only two functions in the script. Easy answer even by trial/error. While the first one builds the payload, the second one does the deobfuscation.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Question 3:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

From our grepping we already know this... it's powershell.

Question 4:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We already found this out through our grepping. Even though we can't access the Google Sheets page, we have the URL which contains the Spreadsheet ID.

Question 5:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We have this information in the same Google Sheets URL we uncovered:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Question 6:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

To find this, we need to open the Event Viewer log where we found the powershell command that was executing the base64. We can find what file that is by adding the `-rn` flags to our grep.  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

We open this file in our file editor of choice, Sublime, and can see the EventID:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

Question 7:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

If we were to continue reading the file we just opened for Question 6, a bit further down we can see the XOR operation:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

And we finally get our flag:  
![image](../../../../../../30-archetypes/archives/personal-collections/CTF-Writeups-LazyTitan33)

HTB{GSH33ts_4nd_str4ng3_f0rmula3_byp4ss1ng_f1r3w4lls!!}


