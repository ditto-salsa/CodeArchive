#include "C_Code.h" // headers 

extern u8 SacredWeaponMusicItemTable[];
extern u16 SacredWeaponMusicBGMTable[];
extern u8 IgnoreSacredWeaponMusicUnitTable[];
extern s16 gBanimFactionPal[2];
extern s16 gBanimValid[2];
extern u8 ReverseModeToggle;
extern u16 ReverseModeFlag;
extern u16 DancerBGM;
extern u8 StaffCheckTable[];
extern u16 StaffBGMTable[];

//smallest function i ever did see, little me
s16 EkrCheckWeaponSieglindeSiegmund(u16 item)
{
    return SacredWeaponMusicItemTable[GetItemIndex(item)];
}

void EkrPlayMainBGM(void)
{
    int ret, songid, songid2, pid;
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

    //per chapter shenanigans
    if (gBanimFactionPal[gEkrInitialHitSide] == 0){
        //do player phase stuff
        songid = GetROMChapterStruct(gPlaySt.chapterIndex)->mapBgmIds[3];
    }

    else if (gBanimFactionPal[gEkrInitialHitSide] == 1){
        //do enemy phase stuff
        songid = GetROMChapterStruct(gPlaySt.chapterIndex)->mapBgmIds[4];
    }
    
    else {
        //do npc phase stuff
        songid = GetROMChapterStruct(gPlaySt.chapterIndex)->mapBgmIds[5];
    }

    if (ReverseModeToggle){
        if (CheckFlag(ReverseModeFlag)){
            if (gPlaySt.faction == 0){
                //do player phase stuff
                songid = GetROMChapterStruct(gPlaySt.chapterIndex)->mapBgmIds[3];
            }

            else if (gPlaySt.faction == 0x80){
                //do enemy phase stuff
                songid = GetROMChapterStruct(gPlaySt.chapterIndex)->mapBgmIds[4];
            }
    
            else {
                //do npc phase stuff
                songid = GetROMChapterStruct(gPlaySt.chapterIndex)->mapBgmIds[5];
            }
        }
    }

   
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
    if (IgnoreSacredWeaponMusicUnitTable[pid] == true) {
        ret = false;
    }

    //hilariously easy this time actually
    if (ret == true)
    {
        EfxOverrideBgm(SacredWeaponMusicBGMTable[GetItemIndex(bur->weaponBefore)], 0x100);
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
    if (UNIT_CATTRIBUTES(&bur->unit) & CA_DANCE)
    {
        if (gBattleStats.config & 0x40)
            ret = true;

        if (gBattleStats.config & 0x200)
            ret = true;
    }

    if (ret == true)
    {
        EfxOverrideBgm(DancerBGM, 0x100);
        return;
    }

    if (StaffCheckTable[GetItemIndex(bur->weaponBefore)]) {
        songid = StaffBGMTable[GetItemIndex(bur->weaponBefore)];
    }
    
    if (StaffCheckTable[GetItemIndex(bul->weaponBefore)]) {
        songid = StaffBGMTable[GetItemIndex(bul->weaponBefore)];
    }
    

    if (songid != -1)
    {
        EfxOverrideBgm(songid, 0x100);
        return;
    }
    gEkrMainBgmPlaying = false;
}