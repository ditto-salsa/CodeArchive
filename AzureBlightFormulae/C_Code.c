#include "C_Code.h" // headers 


//Crackhead Crit formula (I'm going to have to explain this one ingame aren't I?)
void ComputeBattleUnitCritRate(struct BattleUnit* bu) {
    //Don't allow critting if skill < 11, and if it's less than 11, let them crit if they have a weapon with crit.
    if (bu->unit.skl < 11 && GetItemCrit(bu->weapon) == 0)
        bu->battleCritRate = 0;
    
    else if (bu->unit.skl < 11)
        bu->battleCritRate = 0;

    else
        bu->battleCritRate = ((bu->unit.skl - 10) / 2) + 5 + GetItemCrit(bu->weapon);

    if (bu->battleCritRate < 0)
        bu->battleCritRate = 0;
    
    if (UNIT_CATTRIBUTES(&bu->unit) & CA_CRITBONUS)
        bu->battleCritRate += 15;
}

void ComputeBattleUnitEffectiveCritRate(struct BattleUnit* attacker, struct BattleUnit* defender) {
    int item, i;

    attacker->battleEffectiveCritRate = attacker->battleCritRate - defender->battleDodgeRate;

    if (GetItemIndex(attacker->weapon) == ITEM_MONSTER_STONE)
        attacker->battleEffectiveCritRate = 0;

    if (attacker->battleEffectiveCritRate < 25)
        attacker->battleEffectiveCritRate = 0;

    if (attacker->battleEffectiveCritRate > 100 || GetItemCrit(attacker->weapon) == 254 || attacker->unit.statusIndex == UNIT_STATUS_BERSERK)
        attacker->battleEffectiveCritRate = 100;

    for (i = 0; (i < UNIT_ITEM_COUNT) && (item = defender->unit.items[i]); ++i) {
        if (GetItemAttributes(item) & IA_NEGATE_CRIT) {
            attacker->battleEffectiveCritRate = 0;
            break;
        }
    }
}

void ComputeBattleUnitStatusBonuses(struct BattleUnit* bu) {
    switch (bu->unit.statusIndex) {

    case UNIT_STATUS_ATTACK:
        bu->battleAttack += 10;
        break;

    case UNIT_STATUS_DEFENSE:
        bu->battleDefense += 10;
        break;

    case UNIT_STATUS_CRIT:
        bu->battleCritRate += 10;
        break;

    case UNIT_STATUS_AVOID:
        bu->battleAvoidRate += 10;
        break;

    case UNIT_STATUS_BERSERK:
        bu->battleAttack += 10;
        //bu->battleCritRate = 100; (this needs to be done to battleEffectiveCritRate)
        //bu->battleHitRate = 50; (this needs to be done to battleEffectiveHitRate) 

    case UNIT_STATUS_SLEEP:
        bu->battleSpeed = 0;
        //bu->battleAvoidRate = 0; (this needs to be done to battleEffectiveHitRate)

    } // switch (bu->unit.statusIndex)
}

void ComputeBattleUnitEffectiveHitRate(struct BattleUnit* attacker, struct BattleUnit* defender) {
    attacker->battleEffectiveHitRate = attacker->battleHitRate - defender->battleAvoidRate;

    if (attacker->unit.statusIndex == UNIT_STATUS_BERSERK)
        attacker->battleEffectiveHitRate = 50;

    if (attacker->battleEffectiveHitRate > 100 || defender->unit.statusIndex == UNIT_STATUS_SLEEP)
        attacker->battleEffectiveHitRate = 100;

    if (attacker->battleEffectiveHitRate < 0)
        attacker->battleEffectiveHitRate = 0;
}

void ComputeBattleUnitHitRate(struct BattleUnit* bu) {
    bu->battleHitRate = (bu->unit.skl * 2) + GetItemHit(bu->weapon) + (bu->unit.lck) + bu->wTriangleHitBonus;
}

void ComputeBattleUnitAvoidRate(struct BattleUnit* bu) {
    bu->battleAvoidRate = bu->terrainAvoid + (bu->unit.lck);

    if (bu->battleAvoidRate < 0)
        bu->battleAvoidRate = 0;
}