# TXT Message



## My Solution

The title of the challenge immediately make me think of the DNS TXT record which I check using `dig`:  



We can see some numbers which look like octal:


```text
146 154 141 147 173 061 064 145 060 067 062 146 067 060 065 144 064 065 070 070 062 064 060 061 144 061 064 061 143 065 066 062 146 144 143 060 142 175
```

We confirm this by decoding it from octal using [Cyberchef](https://gchq.github.io/CyberChef/#recipe=From_Octal('Space')&input=MTQ2IDE1NCAxNDEgMTQ3IDE3MyAwNjEgMDY0IDE0NSAwNjAgMDY3IDA2MiAxNDYgMDY3IDA2MCAwNjUgMTQ0IDA2NCAwNjUgMDcwIDA3MCAwNjIgMDY0IDA2MCAwNjEgMTQ0IDA2MSAwNjQgMDYxIDE0MyAwNjUgMDY2IDA2MiAxNDYgMTQ0IDE0MyAwNjAgMTQyIDE3NQ):  



`flag{14e072f705d45882401d141c562fdc0b}`
