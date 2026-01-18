.include "Header.inc"
.thumb

.set GetSummonersSummonData, EALiterals

push {r14}

ldrb r1, [r0, #0xF]

mov r2, #0x20
tst r1, r2
bne EraseUnit

mov r2, #0x80
tst r1, r2
bne IsASummon

ldrb r1, [r0, #0xB]
mov r2, #0xC0
tst r1, r2
beq KeepUnitButDead // when unit is blue

EraseUnit:
mov r1, #0
str r1, [r0]

End:
pop {r0}
bx r0

IsASummon:
push {r0}
longcall GetSummonersSummonData, r2, poolLiteral=False
cmp r0, #0
beq SkipEventCall
ldr r0, [r0, #8]
cmp r0, #0
beq SkipEventCall
mov r1, #0
longcall CallEvent, r2
mov r1, #1 // Z = 0 for event called, Z = 1 for branches to SkipEventCall
SkipEventCall:
pop {r0}
beq EraseUnit // if event call was skipped erase the unit
ldrb r1, [r0, #0xF] // set bit 0x20 of byte 0xF of unit struct to denote to not call the event again
mov r2, #0x20
orr r1, r2
strb r1, [r0, #0xF]
b End

KeepUnitButDead:
ldr r1, [r0, #0xC]
mov r2, #0b00000101
orr r1, r2
str r1, [r0, #0xC]
longcall InitUnitSupports, r2
b End

file_uses_longcall_with r2
end_file
