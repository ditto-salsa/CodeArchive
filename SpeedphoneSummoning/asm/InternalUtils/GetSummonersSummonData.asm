.include "Header.inc"
.thumb

.set SummonDataTable, EALiterals

ldr r0, [r0]
ldrb r3, [r0, #4]
mov r12, r3
ldr r3, =#0xC00 // 12 * 256

ldr r0, SummonDataTable
mov r1, #0
Loop:
cmp r1, r3
bgt RetNull
ldr r2, [r0, r1]
ldrb r2, [r2]
cmp r2, r12
beq RetFound
add r1, r1, #12
b Loop

RetFound:
add r0, r0, r1
b End

RetNull:
mov r0, #0

End:
bx r14

end_file
