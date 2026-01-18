.include "Header.inc"
.thumb

.set GetSummonDataForUnit, EALiterals

push {r4, r5, r14}

ldr r0, =gActiveUnit
ldr r4, [r0]
mov r0, r4
longcall GetSummonDataForUnit, r3, poolLiteral=False

ldr r0, [r0]
ldr r5, =gUnitDef1
mov r1, r5
mov r2, #SizeOfStructUnitDef
longcall MemCpy, r3

ldrb r0, [r4, #0x8]
lsl r0, r0, #3

ldrb r1, [r5, #0x3]
mov r2, #0b00000111
and r1, r2

orr r0, r1
strb r0, [r5, #0x3]

ldr r3, =gActionData
// byte 0x4 - YY XXXXXX
ldrb r2, [r3, #0x13]
mov r1, #0b00111111
and r2, r1
ldrb r1, [r3, #0x14]
lsl r0, r1, #6
orr r0, r2
strb r0, [r5, #0x4]
// byte 0x5 - 0000YYYY
ldrb r0, [r3, #0x14]
lsr r0, r0, #2
mov r1, #0b00001111
and r0, r1
strb r0, [r5, #0x5]

mov r0, r5
longcall LoadUnit, r3

mov r1, #0xFF
strb r1, [r0, #0x9]

mov r1, #0x80
strb r1, [r0, #0xF]

pop {r4, r5}
pop {r0}
bx r0

file_uses_longcall_with r3
end_file
