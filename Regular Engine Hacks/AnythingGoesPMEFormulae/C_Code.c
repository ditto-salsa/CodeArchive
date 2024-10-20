#include "C_Code.h" // headers 

void UnitAutolevelWExp(struct Unit* unit, const struct UnitDefinition* uDef) {
    if (uDef->autolevel) {
        int i;

        for (i = 0; i < GetUnitItemCount(unit); ++i) {
            int wType, item = unit->items[i];

            if (!(GetItemAttributes(item) & IA_REQUIRES_WEXP))
                continue;

            if (GetItemAttributes(item) & IA_WEAPON)
                if (CanUnitUseWeapon(unit, item))
                    continue;

            if (GetItemAttributes(item) & IA_STAFF)
                if (CanUnitUseStaff(unit, item))
                    continue;

            if (GetItemAttributes(item) & IA_LOCK_ANY)
                continue;

            wType = GetItemType(item);

            if (unit->ranks[wType] == 0)
                item = 0;

            if (UNIT_CATTRIBUTES(unit) & CA_PROMOTED)
                unit->ranks[wType] = 251;
            else
                unit->ranks[wType] = 181;
        }
    }
}

void ComputeBattleUnitWeaponRankBonuses(struct BattleUnit* bu) {
    if (bu->weapon) {
        int wType = GetItemType(bu->weapon);

        if (wType < 8 && bu->unit.ranks[wType] >= WPN_EXP_S) {
            bu->battleAttack += 5;
            bu->battleCritRate += 25;
        }

        else if (wType < 8 && bu->unit.ranks[wType] >= WPN_EXP_A) {
            bu->battleAttack += 4;
            bu->battleCritRate += 20;
        }

        else if (wType < 8 && bu->unit.ranks[wType] >= WPN_EXP_B) {
            bu->battleAttack += 3;
            bu->battleCritRate += 15;
        }

        else if (wType < 8 && bu->unit.ranks[wType] >= WPN_EXP_C) {
            bu->battleAttack += 2;
            bu->battleCritRate += 10;
        }

        else if (wType < 8 && bu->unit.ranks[wType] >= WPN_EXP_D) {
            bu->battleAttack += 1;
            bu->battleCritRate += 5;
        }

    }
}

void ComputeBattleUnitDodgeRate(struct BattleUnit* bu) {
    bu->battleDodgeRate = 2*(bu->unit.lck) - bu->unit.spd;
}

void ComputeBattleUnitHitRate(struct BattleUnit* bu) {
    bu->battleHitRate = (bu->unit.skl * 2) + GetItemHit(bu->weapon) + (bu->unit.lck / 2) + bu->wTriangleHitBonus;
}

void ComputeBattleUnitAvoidRate(struct BattleUnit* bu){
    bu->battleAvoidRate = Sqrt((bu->unit.spd * 3) + (bu->unit.lck * 2));
}

void ComputeBattleUnitCritRate(struct BattleUnit* bu){
    bu->battleCritRate = Sqrt(((bu->unit.skl * (bu->unit.skl / 6)) - 13)/3)*4;
}