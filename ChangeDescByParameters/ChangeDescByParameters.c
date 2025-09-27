#include "ChangeDescByParameters.h"

// for shits and giggles, do this transformation:
// c ? true : v into (1-!!c)*v + !!c
//(1-!!c) is 1 for c=0 and 0 otherwise, so (1-!!c)v is either v or 0. then when you add !!c at the end that becomes v+0 or 0+1)

u8 DoesUnitHaveItem(struct Unit* unit, int itemID){
    int found = FALSE;
    int i = 0;
    while (i < 5 || found == FALSE){
        if ((unit->items[i] & 0xFF) == itemID){
            found = TRUE;
        }
    }
    return found;
}

extern struct DescParams UnitDescParams[];

void HbPopulate_SSCharacter(struct HelpBoxProc* proc)
{   
    int midDesc = 0;

    int index = 0;
    for ( ; ; index++) { if ((UnitDescParams[index].unitID == gStatScreen.unit->pCharacterData->number) || UnitDescParams[index].unitID == 0) break; }

    switch (UnitDescParams[index].unitID){
        case 0:
            midDesc = gStatScreen.unit->pCharacterData->descTextId;
            break;

        default:
            if (gStatScreen.unit->pClassData->number == UnitDescParams[index].classID || UnitDescParams[index].classID == 0){
                if (DoesUnitHaveItem(gStatScreen.unit,UnitDescParams[index].itemID) || UnitDescParams[index].itemID == 0){
                    if (UNIT_FACTION(gStatScreen.unit) == UnitDescParams[index].allegiance || UnitDescParams[index].allegiance == 0xFF){
                        if (gPlaySt.chapterIndex == UnitDescParams[index].chapterID || UnitDescParams[index].chapterID == 0xFF){
                            if (UnitDescParams[index].func == 0 ? true : UnitDescParams[index].func(gStatScreen.unit)){
                                if (CheckFlag(UnitDescParams[index].flagID) || UnitDescParams[index].flagID == 0){
                                    midDesc = UnitDescParams[index].textID;
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            midDesc = gStatScreen.unit->pCharacterData->descTextId;
    }

    if (midDesc)
        proc->mid = midDesc;
    else
        proc->mid = NoMessagesForMenuItemID;
        
    return;
}

extern struct DescParams ClassDescParams[];

void HbPopulate_SSClass(struct HelpBoxProc* proc)
{
    int midDesc = 0;

    int index = 0;
    for ( ; ; index++) { if ((ClassDescParams[index].classID == gStatScreen.unit->pClassData->number) || ClassDescParams[index].classID == 0) break; }

    switch (ClassDescParams[index].classID){
        case 0:
            midDesc = gStatScreen.unit->pClassData->descTextId;
            break;

        default:
            if (gStatScreen.unit->pCharacterData->number == ClassDescParams[index].unitID || ClassDescParams[index].unitID == 0){
                if (DoesUnitHaveItem(gStatScreen.unit,UnitDescParams[index].itemID) || UnitDescParams[index].itemID == 0){
                    if (UNIT_FACTION(gStatScreen.unit) == ClassDescParams[index].allegiance || ClassDescParams[index].allegiance == 0xFF){
                        if (gPlaySt.chapterIndex == ClassDescParams[index].chapterID || ClassDescParams[index].chapterID == 0xFF){
                            if (ClassDescParams[index].func == 0 ? true : ClassDescParams[index].func(gStatScreen.unit)){
                                if (CheckFlag(ClassDescParams[index].flagID) || ClassDescParams[index].flagID == 0){
                                    midDesc = ClassDescParams[index].textID;
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            midDesc = gStatScreen.unit->pCharacterData->descTextId;
    }

    if (midDesc)
        proc->mid = midDesc;
    else
        proc->mid = NoMessagesForMenuItemID;
        
    return;
}

extern struct DescParams ItemDescParams[];

void HbPopulate_SSItem(struct HelpBoxProc* proc)
{
    int item = gStatScreen.unit->items[proc->info->mid];

    proc->item = item;

    int index = 0;
    for ( ; ; index++) { if (DoesUnitHaveItem(gStatScreen.unit,ItemDescParams[index].itemID) || ItemDescParams[index].itemID == 0) break; }

    switch (ItemDescParams[index].classID){
        case 0:
            proc->mid  = GetItemDescId(item);
            break;

        default:
            if (gStatScreen.unit->pClassData->number == ItemDescParams[index].classID || ItemDescParams[index].classID == 0){
                if (gStatScreen.unit->pCharacterData->number == ItemDescParams[index].unitID || ItemDescParams[index].unitID == 0){
                    if (UNIT_FACTION(gStatScreen.unit) == ItemDescParams[index].allegiance || ItemDescParams[index].allegiance == 0xFF){
                        if (gPlaySt.chapterIndex == ItemDescParams[index].chapterID || ItemDescParams[index].chapterID == 0xFF){
                            if (ItemDescParams[index].func == 0 ? true : ItemDescParams[index].func(gStatScreen.unit)){
                                if (CheckFlag(ItemDescParams[index].flagID) || ItemDescParams[index].flagID == 0){
                                    proc->mid = ItemDescParams[index].textID;
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            proc->mid  = GetItemDescId(item);
    }

    
    
}