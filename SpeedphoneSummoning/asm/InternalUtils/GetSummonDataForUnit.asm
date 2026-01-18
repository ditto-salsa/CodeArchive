.include "Header.inc"
.thumb

.set SummonDataTable, EALiterals

// parameters:
// struct Unit* in r0
// returns:
// const struct SummonData* in r0

ldr r1, [r0]
ldrb r1, [r1, #4]
mov r2, #12
mul r1, r2
ldr r0, SummonDataTable
add r0, r0, r1

bx r14

end_file
