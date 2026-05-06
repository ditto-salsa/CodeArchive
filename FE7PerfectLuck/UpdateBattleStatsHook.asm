.thumb

.set CheckFlag, 0x080798F9

.macro blh to, reg
	ldr \reg, =\to
	mov r14, \reg
	.short 0xF800
.endm

// r2 = gBattleStats
// r3 has attacker, r1 has defender but we don't care about them lwk
// r0 is hook reg

push {r4, r5, r6, r7, r14}
mov r0, r8
push {r0}

mov r8, r2

mov r4, r3

mov r2, #0x64
ldrh r5, [r4, r2]
mov r2, #0x6A
ldrh r6, [r4, r2]
mov r2, #0x6C
ldrh r7, [r4, r2]

mov r0, #0xA4
blh CheckFlag, r1
cmp r0, #0
beq Apply
	ldrb r0, [r4, #0xB]
	mov r1, #0x80
	tst r0, r1
	bne EnemyPerfectLuck

PlayerNPCPerfectLuck:
.irp reg, r5, r6, r7
	cmp \reg, #0
	ble 0f
		mov \reg, #100
	0:
.endr
b Apply

EnemyPerfectLuck:
.irp reg, r5, r6, r7
	cmp \reg, #100
	bge 0f
		mov \reg, #0
	0:
.endr

Apply:
mov r0, r8
strh r5, [r0, #0xA]
strh r6, [r0, #0xC]
strh r7, [r0, #0xE]

End:
pop {r0}
mov r8, r0
pop {r4, r5, r6, r7}
pop {r0}
bx r0

.align
.pool
