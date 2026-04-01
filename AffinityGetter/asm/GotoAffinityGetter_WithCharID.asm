.thumb

.set GetUnitStructFromEventParameter, 0x0800BC51
.set GetCharacterData, 0x08019465

.set AffinityGetter, EALiterals

push {r4, r14}
mov r4, r0 // char ID in r4

ldr r1, =GetUnitStructFromEventParameter
bl bx_r1
cmp r0, #0
bne GotoAffinityGetter

ReadFromCharData:
mov r0, r4
ldr r1, =GetCharacterData
bl bx_r1
ldrb r0, [r0, #0x9] // just read from the character data directly if there is no unit loaded as nothing can modify a non-existent character
b End

GotoAffinityGetter:
ldr r1, AffinityGetter
bl bx_r1

End:
pop {r4}
pop {r1}
bx_r1:
bx r1

.align 2
.pool
EALiterals:
