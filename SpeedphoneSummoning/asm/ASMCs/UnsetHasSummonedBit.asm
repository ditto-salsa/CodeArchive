.include "Header.inc"
.thumb

/*
UnsetHasSummonedBit:
		Parameters:
			s1 - ROM unit ID of unit to unset the Has Summoned bit of
		Returns:
			Nothing
		-- Unsets the Has Summoned bit of the unit in s1
*/

push {r14}

ldr r0, =MemSlot1
ldrh r0, [r0]
longcall GetUnitStructFromEventParameter, r1

ldrb r1, [r0, #0xE]
mov r2, #HasSummonedBit
mvn r2, r2
and r1, r2
strb r1, [r0, #0xE]

pop {r0}
bx r0

file_uses_longcall_with r1
end_file
