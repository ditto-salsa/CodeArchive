.include "Header.inc"
.thumb

ldr r0, [r4]
mov r1, #0x23
ldrb r2, [r0, r1]
mov r1, #0x40
tst r1, r2
bne RetFalse

ldrb r1, [r4, #0xF]
mov r2, #0xC0 // IsASummon|IsASummoner
tst r2, r1
bne RetFalse

mov r0, #1
b End

RetFalse:
mov r0, #0

End:
pop {r4, r5}
pop {r1}
bx r1

end_file
