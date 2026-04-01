.thumb
.set GetStructFromCharID_GotoAffinityGetter, EALiterals

ldr r3, GetStructFromCharID_GotoAffinityGetter
bl bx_r3
sub r1, r0, #1
mov r2, #2
lsl r2, r2, #8
orr r1, r2
mov r2, #0xE0
lsl r2, r2, #8
ldr r3, ReturnAddress
bx_r3:
bx r3

.align 2
ReturnAddress: .word 0x080A1DA5
EALiterals:
