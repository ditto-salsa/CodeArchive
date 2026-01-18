.include "Header.inc"
.thumb

push {r14}

ldr r0, =gBmSt
mov r1, #0x3D
ldrb r0, [r0, r1]
mov r1, #0b00000010
tst r0, r1
bne RetNotShown

ldr r0, =gActiveUnit
ldr r0, [r0]
ldr r1, [r0]

mov r2, #0x23
ldrb r2, [r1, r2]
mov r3, #0x80
tst r2, r3
bne RetNotShown

ldr r2, [r1, #0x28]
ldr r1, [r0, #0x4]
ldr r3, [r1, #0x28]
orr r2, r3
mov r1, #0x1
lsl r1, r1, #9
tst r1, r2
bne RetNotShown 

ldr r1, [r0, #0xC]
mov r2, #0x40
tst r1, r2
bne RetNotShown

longcall MakeTradeTargetList, r1
longcall GetSelectTargetCount, r1
cmp r0, #0
beq RetNotShown

RetEnabled:
mov r0, #MENU_ENABLED
b End

RetNotShown:
mov r0, #MENU_NOTSHOWN

End:
pop {r1}
file_uses_longcall_with r1

end_file
