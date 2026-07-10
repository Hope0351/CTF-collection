# :globe_with_meridians: STACK the Flags (2022) CTF Write-up - PyRunner

> **Original Source:** [STACK the Flags (2022) CTF Write-up - PyRunner](https://tohyuting.medium.com/stack-the-flags-2022-ctf-write-up-pyrunner-b254cb5ad8b2)
> **Platform:** tohyuting.medium.com | **Category:** `WEB` | **Year:** 2022

---

For this web challenge, it consists of a simple webpage displaying a web server code template as shown below:


*Challenge webpage*


You might be wondering, what are those fields boxed in red? Well, user will be allowed to enter the title, host and port they wish to use for this template. These input fields will correspond to the respective fields boxed in red above. Finally, user will be allowed to run the code in the template with their desired input on the server side.


With this context in mind, the first idea that came to my mind would be a possible code injection attack to expose the flag on the server end. The next question to ask is: which field would that be?


By taking a closer look at the screenshot above, we would notice that the host and port fields are part of a comment. Hence, it might not be very feasible to use those fields for code injection.


On the other hand, title field is enclosed within a print statement. This does sounds more feasible than the other two fields discussed above. In addition, we could try to read the flag file and print the flag out! Is this too good to be true? Let us first check out the source code to determine if filtering are in place.


*Snippet of source code for challenge webpage (with list of disallowed keywords)*


As expected, some keywords were filtered off, including `;` and `\n` . Hence, we would not be able to execute multiple commands within a single line. I had initially considered adding another print statement with `;` as part of the payload in order to execute another print statement for retrieval of flag value.


However, it is possible to print more than one object with a single print statement on python. For instance: `print("Hello", "There")` would print Hello There as the result. This means that we could create the payload such that the print statement executed on the server end is: `print("Webserver:", <some_flag_value>)`


In order to find a way to retrieve the flag value, I began to look at the other source code provided, I noticed that `readflag.c` was part of the files given. The code would open the file containing the flag (found at `/root/flag` ) and read it.

*readflag.c*


However, there is one difficulty in using this file. Given that `import`, `os` , `eval` and `exec` keywords are filtered, we would not be able to import packages to help us execute `readflag.c` easily.


At this point, I decided to look back at the list of keywords filtered again. I realised that the `open` and `read` keywords were not filtered off. This meant that we could easily read the content within the flag file with `open` and `read` !


From `readflag.c` , I figured that the flag was on `/root/flag` . Hence, the final command used for the code injection is as shown:


```
", open("/root/flag","r").read())#
```


For the payload above, `open` function was used to open the file containing the flag and `r` parameter was used to indicate that the flag file was opened for reading. This was then chained with `read` to read the content of the flag file and print it out within the print statement. For clarify, the final line of code executed on the server side will be:


```
print("Webserver: ", open("/root/flag","r").read())#")
```


In this case, `#` was added at the end to comment out `")` within the original code to ensure that the code is synthetically correct. The flag obtained after running the template is as shown below.


*Output printed after running the template*Flag:


```
STF22{4ut0m4t3d_c0mm4nd_1nj3ct10n}
```

---

*Originally published on [Medium](https://tohyuting.medium.com/stack-the-flags-2022-ctf-write-up-pyrunner-b254cb5ad8b2). All credit goes to the original author.*
*Part of [CTF Collection](https://github.com/Hope0351/CTF-collection) — a curated archive of web CTF writeups.*
