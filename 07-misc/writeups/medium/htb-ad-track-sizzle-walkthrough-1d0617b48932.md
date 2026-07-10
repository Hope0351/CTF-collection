# :game_die: [HTB](https://hacktheboxltd.sjv.io/19ZM06) AD Track: Sizzle Walkthrough

---

# [HTB](https://hacktheboxltd.sjv.io/19ZM06) AD Track: Sizzle Walkthrough

Hello Everyone! Here’s my writeup for the machine Sizzle.

Let’s perform a quick port scan of the target.

Command: nmap -p- <target-ip>

>

-p-: Scan all 65535 ports

<target-ip>: Replace with the given IP address of the target machine

*Port scan output*

Save the obtained output to a file.

We will now filter this output to ensure that we only have the ports through some bash scripting.

Command: cat Open_Ports| grep open | cut -d “ “ -f 1 | cut -d “/” -f 1 > list_open_ports

Let’s understand the logic behind above command.

First we read the output of the file using cat command, pass this as input using pipe and grep the input to filter out only lines that contain the word ‘open’.

Next we pass this as input using pipe and divide it into columns with cut and space as the delimiter and select just the first column.

Finally, we pass this as input using pipe and divide it into columns with cut using slash as a delimiter and select just the first column.

Our filtered output should now only have the open ports.

Let’s now perform an aggressive scan on these ports.

---
