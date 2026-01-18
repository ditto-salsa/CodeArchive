.include "Header.inc"
.thumb

.set GetSummonDataForUnit, EALiterals

push {r14}
ldr r0, =gActiveUnit
ldr r0, [r0]
longcall GetSummonDataForUnit, r2, poolLiteral=False
ldr r0, [r0, #4]
cmp r0, #0
beq End
mov r1, #1
longcall CallEvent, r2
End:
pop {r0}
bx r0

file_uses_longcall_with r2
end_file
