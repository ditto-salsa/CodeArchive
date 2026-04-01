.thumb
.set AffinityFunctionList, EALiterals

push {r4, r5, r14}
mov r4, r0
sub r13, #4

ldr r5, AffinityFunctionList
Loop:
	ldr r2, [r5]
	cmp r2, #0
	beq End
	
	mov r0, r4
	mov r1, r13
	bl bx_r2
	
	cmp r0, #0
	bne End
	
	add r5, r5, #4
	b Loop

End:
pop {r0, r4, r5}
pop {r2}
bx_r2:
bx r2

.align 2
EALiterals:
