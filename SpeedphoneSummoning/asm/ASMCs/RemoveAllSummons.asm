.include "Header.inc"
.thumb

/*
RemoveAllSummons:
		Parameters:
			None
		Returns:
			Nothing
		-- Removes all units marked as summons from RAM entirely (same as repeated DISA)
*/

push {r4, r14}

mov r4, #1
Loop:
	cmp r4, #0xC0
	bge ExitLoop
	
	mov r0, r4
	longcall GetUnit, r1
	
	// Is unit valid?
	ldr r1, [r0]
	cmp r1, #0
	beq ContinueLoop
	
	ldrb r1, [r0, #0xF]
	mov r2, #IsASummonBit
	tst r1, r2
	beq ContinueLoop
	
		longcall ClearUnit, r1
	
	ContinueLoop:
	add r4, #1
	b Loop
ExitLoop:

pop {r4}
pop {r0}
bx r0

file_uses_longcall_with r1
end_file
