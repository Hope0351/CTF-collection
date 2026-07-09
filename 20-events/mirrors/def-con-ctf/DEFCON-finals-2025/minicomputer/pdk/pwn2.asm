.pdk13

; once we are here we have bypassed the checks so we can operate freely
nop

; 0xd7100
mov a, 0x00
mov.io 0, a
mov a, 0x70
mov.io 1, a
sub a, 0x63
mov.io 2, a
mov a, 0x00
mov.io 16, a

mov.io a, 24
mov.io a, 25
mov.io a, 26
mov.io a, 27
mov a, 0
reset