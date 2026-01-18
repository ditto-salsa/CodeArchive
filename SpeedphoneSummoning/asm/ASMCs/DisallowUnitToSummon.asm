.include "Header.inc"
.thumb

/*
DisallowUnitToSummon:
		Parameters:
			s1 - ROM unit ID of unit to remove summon access from
		Returns:
			Nothing
		-- Removes the summoner bitflag in the unit state from the unit in s1
*/

push {r14}

ldr r0, =MemSlot1
ldrh r0, [r0]
longcall GetUnitStructFromEventParameter, r1

ldrb r1, [r0, #0xF]
mov r2, #IsASummonerBit
mvn r2, r2
and r1, r2
strb r1, [r0, #0xF]

pop {r0}
bx r0

file_uses_longcall_with r1
end_file
