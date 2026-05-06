.thumb

.set CheckFlag, 0x080798F9
.set SetFlag, 0x080798E5
.set UnsetFlag, 0x08079911 // i sure hope so!

.macro blh to, reg
	ldr \reg, =\to
	mov r14, \reg
	.short 0xF800
.endm

push {r14}

mov r0, #0xA4
blh CheckFlag, r1
cmp r0, #0
beq SetPerfectLuckFlag
	mov r0, #0xA4
	blh UnsetFlag, r1
	mov r0, #0x1B
	b End
SetPerfectLuckFlag:
mov r0, #0xA4
blh SetFlag, r1
mov r0, #0x17

End:
pop {r1}
bx r1
