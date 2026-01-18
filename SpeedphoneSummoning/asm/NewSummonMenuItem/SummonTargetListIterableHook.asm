.include "Header.inc"
.thumb

/*
	Hooks in at 0x25C70, we're changing the line
	`if (!CanUnitCrossTerrain(gSubjectUnit, gBmMapTerrain[y][x])){`
	into doing basically the same thing as CanUnitCrossTerrain but with only a class ID
	
	registers set up for us is r0 = gSubjectUnit. we finish some operations we overwrite to get the value of r1 to be gBmMapTerrain[y][x] first
*/

.set GetSummonDataForUnit, EALiterals

// Finish overwritten operations on r1
add r1, r1, r4
ldrb r1, [r1]
push {r1}

longcall GetSummonDataForUnit, r1, poolLiteral=False

ldr r0, [r0] // const struct SummonData* -> const struct UnitDefinition*
ldrb r0, [r0, #0x01] // UnitDefinition->classIndex

longcall GetClassData, r1

ldr r0, [r0, #0x38]
pop {r1}

ldrsb r1, [r0, r1] // r0 = GetClassData(GetSummonDataForUnit(gSubjectUnit)->uDef.classIndex)->pMovCostTable[0]
cmp r1, #0
bgt RetTrue
RetFalse:
mov r0, #0
b End
RetTrue:
mov r0, #1

End:
ldr r1, =0x08025C7B
file_uses_longcall_with r1

end_file
