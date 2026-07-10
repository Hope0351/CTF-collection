# :mag: HTTP Based Python Trojan for Remote System Forensics and Privilege Transfer

> **Original Source:** [HTTP Based Python Trojan for Remote System Forensics and Privilege Transfer](https://infosecwriteups.com/python-http-based-trojan-for-remote-system-forensics-and-privilege-transfer-ae128891b4de)
> **Platform:** infosecwriteups.com | **Category:** `FORENSICS`

---

# HTTP Based Python Trojan for Remote System Forensics and Privilege Transfer


*Source: [https://gotowebsecurity.com/ethical-hacking-course-trojans-lab-session/](https://gotowebsecurity.com/ethical-hacking-course-trojans-lab-session/)*

## Overview


In this article, we will be building a python based trojan that does the following:


- Download remotely unrelated code to the trojan and run it

- Update code downloaded in (1)

- Update itself

- Rerun itself (immune to any signal except SIGKILL)

- Acquire and transfer root privileges (and thus do about anything on the target machine)

- Send data over HTTP to the attacker


And we begin with a simple assumption: the target executes some code that is beneficial to it. It might be anything like a python package serving to do some task the user thinks is worth doing.


Source code: [Github](https://github.com/NimishMishra/networking/tree/master/remote_system_forensics)

## Introduction


Trojans are powerful because they look nice and are one of the foremost candidates of evading suspicion. Once run, they get about their malicious intent while looking perfectly fine to the attacker. More so, since targets (especially developers) are *usually *not suspicious of grabbing open-source/packages code and running it. It might be a good entry point for our exploit.

## The ‘good’ code


The good code is simple. It does what the target intends it to do. It might range across a variety of things and span a whole package; the bigger the codebase, the subtler it is to spot activity. We’ll skip that part and write a simple code that prints something.

*The good code with somewhat bad intents.*


To the target, this script should do what it is meant to (as in printing a simple line in our case) and exit peacefully. Apart from it, the main stuff here is the other stuff. The script builds a directory (in the normal case, you would want the working directory to be somewhere hidden. I’ll skip that for conciseness and obviousness of doing so) `downloaded``, switches to it, and makes a cURL request (read more about cURL [here](https://curl.haxx.se/docs/)) to some server at `http://192.168.43.38:9000/downloader.py` and downloads the content returned to a python script `downloader.py` . It then fires the command `python3 downloader.py` and peacefully exits. Since `Popen` was used, the child process (running `downloader.py`) disassociates from the parent (`good.py`)on the parent’s exit and associates with the `init`. So effectively, it becomes a separate process. The function `run_command()` is the python equivalent of a shell. It runs the specified command and returns the output from `STDOUT` or what you would have received had you used a shell.


Now is the time to configure this `http://192.168.43.38:9000.`

## Server end


The idea is to build a server that automatically pushes code to the remote end. It will be later used to update code in real-time, transfer files, commands, and a lot more. All we need to do is to configure a HTTP server capable of handling `POST` and `GET`.

*basic HTTP server skeleton in setup_server.py*


A `HTTPServer` in python runs on two pieces of information: where to put it up and what to do on interaction. The former part is handled by `('192.168.43.38', 9000)` which serves to bind the server to port `9000` of the machine and`192.168.43.38` is the local IP. The latter part is handled by a separate class extending `BaseHTTPRequestHandler` that defines functionality for `POST` and `GET`. The `_set_response()` function serves to send mandatory `HTTP` header information (header, code 200 representing success, and end header representing the end of header). Since we shall be dealing with text data, setting the `Content-type` to `text/html` is fine. Now to add the two main functions.

*GET.py*


A `GET` request, amongst other things, contains a path to get. In this case, it would be of the form `filepath` in `http://192.168.43.38:9000/filepath` . It might be empty (analogous to the *home *page of a website you visit) or it contains something (analogous to further pages you visit from the home page). In our case, we wish to return the list of files available in the server when a `GET` is made to our *home, *i.e. `http://192.168.43.38:9000/` and return the contents of the file when a specific file is requested, as in `http://192.168.43.38:9000/downloader.py` . The technique is to distinguish the two cases, open the file in the latter case, craft a response, and `wfile.write()` that sends the response.


A `POST` request contains data that must be handled.

*POST.py*


This gets the length from the HTTP header, extracts the data using `rfile.read()` , and stores to a file. The split using `SPLIT` is just a convenient way of handling newlines (for me! I am just never able to preserve newlines in data sent over a network. To a file, it looks like a huge single line data. To overcome this, I replace `\n` at the target end with a `SPLIT` which is then replaced back at the server end). Finally, we send a `POST OK` using `wfile.write().`


Now we move on to crafting other stuff. First, `downloader.py`

## Stage I execution


Our good code serves to load a simple `downloader.py` to a specified directory and execute it. Now it is mainly up to `downloader.py` to handle everything else. As a starter, we want a way for `downloader.py` to handle these things:


- Know when files at the server end have been updated.

- Know when code for `downloader.py` itself has been updated.

- Evade all signals possible (not even a simple `kill PID` should terminate it).

- Download updated files from the server end and execute them.

- Hide itself (too large a subtopic and thus not dealt here).

- Schedule itself (related to `cron` and not covered here) and build kernel persistence.


For the first two, the following code is sufficient.

*downloader.py*


There might be several ways to check status. I settled with creating a special file `status.txt` having binary digits on two separate lines. The first line has a 0/1 that denotes whether the files on the server have been updated (or if the attacker wants to rerun certain programs), and the second line has a 0/1 that denotes whether `downloader.py` has itself to be updated. Quite intuitively, we download the `status.txt` and analyse the flags. If we obtain a 1 in the first line, we move on to fetching and downloading files (since updating `downloader.py` too involves the same operations, the second flag is not checked here). When data is retrieved, we delete `status.txt` since it is no longer needed.


The third requirement is dealt with simply like the following.

*Handling signals and termination*


Any of the following signals received causes a re-downloading of the `downloader.py` and a re-run as a new process. Only `SIGKILL` which can’t be ignored kills the process.


The fourth and the main part goes as such.

*Fetching files*


Recall from the discussion on `GET` that a request of the form `http://192.168.43.38:9000` returns a list of files hosted in the server. We obtain that list and run a loop (ignoring `status.txt` as it has already been downloaded and analysed). Should we obtain `downloader.py` (i.e. it is available on the server) and `data[1] == 1` (it needs to be updated), we fire `refresh_downloader()` that refreshes the `downloader.py` by re-downloading it, running a new process, and exiting the current process. If this is not the case, we simply create a list of files to be downloaded that are handled in the next snippet.

*Download files*


Simply create cURL requests to the respective URL and download the files. Once downloaded, `run_scripts()` runs all files in the working directory except `downloader.py` (that results in a fork bomb as long as `status.txt` has a 1 in its first line: the flag indicating to keep downloading and refreshing files) and `setup_server.py` (that contains the script of the server as discussed before). [ You shouldn’t keep `setup_server.py` on the server itself but then I was lazy enough not to fix that :)].


## Get Nimish Mishra’s stories in your inbox


Join Medium for free to get updates from this writer.


Remember me for faster sign in


Here’s the complete code for `downloader.py`

*Complete downloader.py. The commented line ‘command_list.append(“sudo”) is added for privilege transfer later.*


That’s pretty much it!

## Sample run

---

*Originally published on [Medium](https://infosecwriteups.com/python-http-based-trojan-for-remote-system-forensics-and-privilege-transfer-ae128891b4de). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of forensics CTF writeups.*
