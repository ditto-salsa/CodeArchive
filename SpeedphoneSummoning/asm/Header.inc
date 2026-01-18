// Functions
.set MemCpy, 0x08014C39

.set CheckFlag, 0x08083DA9

.set GetUnitStructFromEventParameter, 0x0800BC51
.set GetUnit, 0x08019431
.set ClearUnit, 0x080177F5
.set LoadUnit, 0x08017AC5

.set InitUnitSupports, 0x080283E1 

.set GetClassData, 0x08019445

.set GetSelectTargetCount, 0x0804FD29

.set SummonSelection_OnSelect, 0x080244D9
.set MakeTargetListForSummon, 0x08025CA5

.set MakeTradeTargetList, 0x080252D1

.set UnitUpdateUsedItem, 0x08018995

.set StartHelpBox, 0x08088DE1

.set GetStringFromIndex, 0x0800A241
.set Text_DrawString, 0x08004005
.set PutText, 0x08003E71
.set BG_GetMapBuffer, 0x08001C4D

.set CallEvent, 0x0800D07D

.set NewPopupCore, 0x08011491
.set SetPopupUnit, 0x08011451

// State bits
.set HasSummonedBit, 0x10
.set IsASummonerBit, 0x40
.set IsASummonBit, 0x80

// RAM Addresses
.set gEventSlots, 0x030004B8
.set MemSlot1, 0x030004BC
.set MemSlotC, 0x030004E8
.set gActiveUnit, 0x03004E50
.set gPlaySt, 0x0202BCF0
.set gActionData, 0x0203A958
.set gBmSt, 0x0202BCB0
.set gUnitDef1, 0x03001C38

// Menu Usability return enums
.set MENU_ENABLED, 1
.set MENU_DISABLED, 2
.set MENU_NOTSHOWN, 3

// Other Constants
.set SizeOfStructUnitDef, 0x14

// Macros
.macro longcall to, reg, poolLiteral=True, regType=Lo
	.if \regType==Lo
		.if \poolLiteral==True
			ldr \reg, =\to
		.else
			ldr \reg, \to
		.endif
	.else
		push {r0}
		.if \poolLiteral==True
			ldr r0, =\to
		.else
			ldr r0, \to
		.endif
		mov \reg, r0
		pop {r0}
	.endif
	bl longcall_trampoline_\reg
.endm

.macro file_uses_longcall_with reg
	longcall_trampoline_\reg:
	bx \reg
.endm

.macro end_file
	.align
	.pool
	EALiterals:
.endm
