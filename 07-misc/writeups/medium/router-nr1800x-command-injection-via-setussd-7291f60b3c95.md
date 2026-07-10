# :game_die: New Bug in Router NR1800X — Command injection via setUssd

---

# New Bug in Router NR1800X — Command injection via setUssd

Hi and welcome to all readers of this post.

In a [Mitre](https://cve.mitre.org/) publication, a vulnerability of a TOTOLink NR1800X router (CVE-2022–41525) version V9.1.0u.6279_B20210910 appeared, which caught my attention so I kept learning more about the vulnerability.

Vendor — [https://www.totolink.net](https://www.totolink.net/)

Wrapping up a bit more on the reported vulnerability, I proceeded to do some tests like emulating the firmware and starting my script in [Ghidra](https://ghidra-sre.org/) to identify other potentially dangerous functions (Rce / BoF).

As a result I get a large list of promising functions (strcpy / system / etc). One of them is highlighted in the image (0x0041a68c), pointing to the function that contains the vulnerability.

*Function list*

After I’ve already used [Ghidra](https://ghidra-sre.org), I continued to analyze the binary cstecgi.cgi in [IDA](https://hex-rays.com/ida-pro/). (The use of multiple tools is only for convenience).

Starting with the static analysis on the function we can quickly see the vulnerability where the v17 buffer is formatted on line 26 and then sent as a parameter by the system() function.

*Reversing in IDA*

Now to see in greater detail we are going to see the whole process of how the parameters are passed to memory, debugging the firmware in system mode.

## Get Miguel Angel Méndez Z.’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

First we put a breakpoint in the websGetVar() function that is responsible for obtaining the values sent in the request body. In this case, it validates that the value sent is ussd.

*send data via request*

Then the string is formatted with snprintf(), which is stored in buffer 0x7fff5230.

*formating string*

Here we can see how the formatted string finally looks in the buffer.

*buffer with data*

Finally, the call to the system() function is made with the stack parameters.

*call system()*

And for the execution of the command to be possible, it is necessary to identify the name setUssd that activates the action, and with this we can recreate a payload to start the telnetd service in the router.

*Request PoC*

Finally develop the exploit by concatenating two vulnerabilities. The first is a request to bypass authentication, which gets the session to be sent to the second request that exploits code execution.

*Exploit*

### Poc Video

[https://www.youtube.com/watch?v=Mcutnejlepk](https://www.youtube.com/watch?v=Mcutnejlepk)

### Conclusion

New (0Day) vulnerabilities can always be found in already analyzed systems.

### Blog

---
