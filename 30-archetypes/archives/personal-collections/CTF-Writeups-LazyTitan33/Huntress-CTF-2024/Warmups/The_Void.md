# The Void



## My Solution

This was a weird one. When connecting to the port it provides it just starts printing out seemingly nothing/spaces in the terminal.

However, if we redirect the output to a file and then read the file, very carefuly, we will see the flag letters hidden one by one after an ANSI escape code that is used to format text in the terminal, specifically the blank looking part.



Here’s what each part means in 30;40m:

30: Sets the foreground text color to black.  
40: Sets the background color to black.  
m: Marks the end of the sequence.  

For instance, running this command in the terminal would make it appear invisible:  

```bash
echo -e "\033[30;40mThis text is invisible\033[0m"
```               
![image



`flag{b1370ac4fadd8c0237f8771d7d77286a}`
