.thumb

// this is just some modified code that was being hooked into DisplaySupportList that is needed to be changed mildly

mov r1, #2
lsl r1, r1, #8
orr r1, r0
mov r0, r5
mov r2, #0xA0
lsl r2, r2, #7
ldr r3, ReturnAddress
bx r3

.align 2
ReturnAddress: .word 0x08087711
