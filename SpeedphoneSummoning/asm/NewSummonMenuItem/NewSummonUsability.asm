.include "Header.inc"
.thumb

/*
	Instead of doing whatever the hell vanilla does for summoning usability, we rewrite it almost entirely.
	
	Checking for:
	If IsASummonerBit is set in RAM unit state
	If there is an existing unit which is this unit's summon
	If HasSummonedBit is set in RAM unit state
	Other vanilla checks such as target list etc
*/

.set GetSummonDataForUnit, EALiterals

push {r4, r14}

ldr r0, =gActiveUnit
ldr r4, [r0]

// Check for IsASummonerBit
ldrb r1, [r4, #0xF]
mov r2, #IsASummonerBit
tst r1, r2
beq RetNotShown

// Check for cantoing
ldrb r1, [r4, #0xC]
// "mov r2, #0x40" // IsASummonerBit is 0x40 as well so no need to re-assign r2
tst r1, r2
bne RetNotShown

// Check for cannot summon ever bit
ldr r1, [r4]
mov r3, #0x23
ldrb r3, [r1, r3]
tst r3, r2 // r2 = 0x40 at this point
bne RetNotShown

// check if has summoned bit is set
ldrb r1, [r4, #0xE]
mov r2, #HasSummonedBit
tst r1, r2
bne RetNotShown

mov r0, r4
longcall GetSummonDataForUnit, r1, poolLiteral=False
ldr r0, [r0]
cmp r0, #0
beq RetNotShown
ldrb r0, [r0]
longcall GetUnitStructFromEventParameter, r1
cmp r0, #0
bne RetNotShown

mov r0, r4
longcall MakeTargetListForSummon, r1
longcall GetSelectTargetCount, r1
cmp r0, #0
beq RetNotShown

mov r0, #MENU_ENABLED
b End

RetNotShown:
mov r0, #MENU_NOTSHOWN

End:
pop {r4}
pop {r1}
file_uses_longcall_with r1 // i love saving 1 instruction by having this follow a pop {r1} for the end
end_file
