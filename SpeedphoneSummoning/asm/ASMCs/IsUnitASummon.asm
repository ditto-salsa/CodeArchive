.include "Header.inc"
.thumb

/*
IsUnitASummon:
		Parameters:
			s1 - ROM unit ID of unit to check
		Returns:
			Non-zero if unit is a summon, 0 otherwise
*/

push {r14}

ldr r0, =MemSlot1
ldrh r0, [r0]
longcall GetUnitStructFromEventParameter, r1

ldrb r0, [r0, #0xF]
mov r1, #IsASummonBit
and r1, r0

ldr r0, =MemSlotC
str r1, [r0]

End:
pop {r0}
bx r0

file_uses_longcall_with r1
end_file
