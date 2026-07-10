# :game_die: Devel writeup | Hack the box. Devel

---

# Devel writeup | Hack the box

*Devel*

This Devel machine is relatively simple, demonstrates the security risks associated with some default program configurations. It is a beginner-level machine which can be completed using publicly available exploits.

The below are the command which we will used in our nmap scan:-

*command*

Nmap scan result which we get after full scan

*nmap_scan*

Now from above scan we notice that two ports are open 21,80.Ftp have anonymous login enable and also have some files one of them is welcome.png, So now we go to our web browser using assigned ip on port 80, and then we saw image there we save the image.

*saving image*

When we are saving image in our local machine we notice that it has name of welcome.png and ftp service have also same file name on nmap scan. This creates doubt in our mind that http is uploading file from ftp service.

*image_name*

So we have anonymous login enable in ftp Service.To clear the doubt in our mind we have create a file test.txt and send to ftp files.

*sending _ftp*

And then traverse the file name on the web browser

*Traversing*

Now this confirmed us that http is using ftp files, So now we have to know that what technology the website is using from wappalyzer we come to know it’s uing Microsoft ASP.NET.

*wappalyzer*

So we search for Microsoft ASP.NET extension on Google.

*google_search*

From result we came to knew that it is using aspx extension.

From now onwards there are two methods to solve this box:-1 Manual method (netcat).2 Automatics method (metasploit).

First we will look at manual method, then we will look at automatic method.

## Get Hanzala Ghayas Abbasi’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

So,we create a payload using windows/shell_reverse_tcp, which creates a reverse shell when executed.

*msfvenom_payload*

Now sending payload to vulnerable machine using ftp service.

*sending_payload*

We are listening on port 4444.

*netcat_listening*

Now Traversing to our payload on the web browser, So it connect back to our machine.

*rev.aspx*

It gives us shell of low Privilege.

*low_level_user*

Now we have to escalate privilege. It’s time for Enumeration, So first we do is type systeminfo command on the shell.

*systeminfo*

Now information we get from systeminfo, we can used that to look for kernel exploit. We search on google[Windows 7 Enterperise build 7600 x86 exploit](https://www.google.com/search?q=Windows+7+Enterperise+build+7600+x86+exploit&rlz=1C1CHBF_enPK1012PK1012&oq=Windows+7+Enterperise+build+7600+x86+exploit&aqs=chrome..69i57.235j0j7&sourceid=chrome&ie=UTF-8), So we get the exploit.

*exploit*

Using EDB-ID, we download exploit from searchsploit.

*searchsploit*

Now we enable our python server, So vulnerable machine downloads exploit from our machine.

*Python_sever*

Downloading exploit from our machine using certutil from vulnerable machine.

*downlaod_exploit*Flag 1:

*Flag:1*Flag 2:

*Flag:2*

Now we have done our exploitation through manual method, now it times for exploitations through second method.

---
