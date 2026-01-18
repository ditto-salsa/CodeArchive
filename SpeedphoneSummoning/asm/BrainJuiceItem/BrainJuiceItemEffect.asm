.include "Header.inc"
.thumb

.set BrainJuicePopupScr, EALiterals

ldr r0, =gActiveUnit
ldr r0, [r0]
push {r0}
ldrb r1, [r0, #0xF]
mov r2, #0x40
orr r1, r2
strb r1, [r0, #0xF]

longcall SetPopupUnit, r2

sub r13, #8
str r6, [r13, #4] // r6 has the proc passed in from the weird jump table hell function
mov r0, #4 // pal base
str r0, [r13]
ldr r0, BrainJuicePopupScr
mov r1, #120
mov r2, #1
mov r3, #0b1001
lsl r3, r3, #6 // 0x240
longcall NewPopupCore, r12, poolLiteral=True, regType=Hi
add r13, #8

ldr r0, =gActionData
ldrb r1, [r0, #0x12]
pop {r0}
longcall UnitUpdateUsedItem, r2

ldr r0, =#0x0802FF77
bx r0

file_uses_longcall_with r2
file_uses_longcall_with r12
end_file
