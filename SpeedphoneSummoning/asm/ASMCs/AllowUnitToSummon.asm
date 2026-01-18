.include "Header.inc"
.thumb

/*
AllowUnitToSummon:
		Parameters:
			s1 - ROM unit ID of unit to give summon access to
		Returns:
			Nothing
		-- Sets the summoner bitflag in the unit state for the unit in s1
*/

push {r14}

ldr r0, =MemSlot1
ldrh r0, [r0]
longcall GetUnitStructFromEventParameter, r1

ldrb r1, [r0, #0xF]
mov r2, #IsASummonerBit
orr r1, r2
strb r1, [r0, #0xF]

pop {r0}
bx r0

file_uses_longcall_with r1
end_file
