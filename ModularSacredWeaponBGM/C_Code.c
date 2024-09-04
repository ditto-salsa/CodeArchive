#include "C_Code.h" // headers 

#define IsPointer 0x8000000

extern u8 ForceBattleMusicItemTable[];
extern u8 ForceBattleMusicBGMTable[];
extern u8 IgnoreForceBattleMusicUnitTable[];
extern s16 gBanimFactionPal[2];
extern s16 gBanimValid[2];

//smallest function i ever did see, little me
s16 EkrCheckWeaponSieglindeSiegmund(u16 item)
{
    return ForceBattleMusicItemTable[GetItemIndex(item)];
}



void EkrPlayMainBGM(void)
{
    int ret, songid, songid2, pid, staff_type;
    struct BattleUnit * bu, * bul, * bur, ** pbul, ** pbur;

    pbul = &gpEkrBattleUnitLeft;
    pbur = &gpEkrBattleUnitRight;

    bul = *pbul;
    bur = *pbur;

    if (gBmSt.gameStateBits & BM_FLAG_5)
    {
        gEkrMainBgmPlaying = 0;
        return;
    }

    gEkrMainBgmPlaying = 1;

    songid = gBanimFactionPal[gEkrInitialHitSide] != 1 ? 0x19 : 0x1A;

    if (GetBattleAnimArenaFlag() == 1)
    {
        Sound_SetDefaultMaxNumChannels();
        EfxOverrideBgm(0x39, 0x100);
        return;
    }

    if (GetBanimLinkArenaFlag() == 1)
    {
        EfxOverrideBgm(0x39, 0x100);
        return;
    }

    if (gEkrDistanceType == EKR_DISTANCE_PROMOTION)
    {
        EfxOverrideBgm(0x23, 0x100);
        return;
    }

    //again not too bad? thanks vesly for listening to my stupidness
    ret = false;
    if (EkrCheckWeaponSieglindeSiegmund(bur->weaponBefore) == true)
        ret = true;

    if (!EkrCheckAttackRound(1))
        ret = false;

    if (gBanimValid[POS_L] == false)
        ret = false;

    pid = UNIT_CHAR_ID(&bul->unit);
    if (IgnoreForceBattleMusicUnitTable[pid] == true) {
        ret = false;
    }

    //hilariously easy this time actually
    if (ret == true)
    {
        EfxOverrideBgm(ForceBattleMusicBGMTable[GetItemIndex(bur->weaponBefore)], 0x100);
        return;
    }

    if (pid == CHARACTER_FOMORTIIS)
    {
        if (CheckFlag82() == true)
        {
            EfxOverrideBgm(0x55, 0x100);
            return;
        }
        SetFlag82();
    }

    songid2 = GetBanimBossBGM(&bul->unit);

    if (UNIT_FACTION(GetUnitFromCharId(UNIT_CHAR_ID(&bul->unit))) == FACTION_BLUE)
        songid2 = -1;

    if (gBanimValid[POS_L] == false)
        songid2 = -1;

    if (songid2 != -1)
    {
        EfxOverrideBgm(songid2, 0x100);
        return;
    }

    ret = false;
    if (UNIT_CLASS_ID(&bur->unit) == CLASS_DANCER)
    {
        if (gBattleStats.config & 0x40)
            ret = true;

        if (gBattleStats.config & 0x200)
            ret = true;
    }

    if (ret == true)
    {
        EfxOverrideBgm(0x20, 0x100);
        return;
    }

    if (EfxCheckRetaliation(POS_L) == true)
        staff_type = EfxCheckStaffType(gBattleActor.weaponBefore);
    else if (EfxCheckRetaliation(POS_R) == true)
        staff_type = EfxCheckStaffType(gBattleTarget.weaponBefore);
    else
        staff_type = 0;


    switch (staff_type) {
    case 2:
        songid = 0x22;
        break;

    case 1:
        songid = 0x21;
        break;

    default:
        break;
    }

    if (songid != -1)
    {
        EfxOverrideBgm(songid, 0x100);
        return;
    }
    gEkrMainBgmPlaying = false;
}