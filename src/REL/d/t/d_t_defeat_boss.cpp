#include "d/t/d_t_defeat_boss.h"
#include "d/flag/storyflag_manager.h"
#include "d/flag/sceneflag_manager.h"
#include "d/flag/dungeonflag_manager.h"
#include "common.h"

SPECIAL_ACTOR_PROFILE(TAG_DEFEAT_BOSS, dTgDefeatBoss_c, fProfile::TAG_DEFEAT_BOSS, 0x29E, 0, 0);

void dTgDefeatBoss_c::fn_494_C0() {

    mID = (fBaseID_e)0x3;
    return;

}

bool dTgDefeatBoss_c::fn_494_D0() {//checks if valid dungeion flag?

    DungeonflagManager* pDVar2;
    u16 sVar4;

    fn_494_C0();
    pDVar2 = DungeonflagManager::sInstance;
    sVar4 = pDVar2->getCounterOrFlag(mID, (u32)8);

    return sVar4 != 0;

}

bool dTgDefeatBoss_c::init() {

    u16 uVar1;
    u16 uVar2;
    u16 iVar3;
    u16 bVar4;
    u32 uVar5;
    u16 counterIdx;

    bVar4 = fn_494_D0();
    if (bVar4) {
        uVar1 = 2;
    }
    else {
        uVar5 = fn_494_360();
        var8_1 = uVar5;
        uVar2 = getSceneflag();
        if ((uVar2 & 0xffff) > 0xfe) {
            var8_1 = 0xff;
        }
        uVar5 = fn_494_380();
        var8_2 = uVar5;
        counterIdx = getStoryflag();
        iVar3 = StoryflagManager::sInstance->checkFlagValid(counterIdx);
        if (iVar3 == 0) {
            var8_2 = 0xff;
        }
        if (var8_1 == -1 && var8_2 == -1) {
            uVar1 = 2;
        }
        else {
            uVar1 = 1;
        }
    }
    return uVar1;

}

int dTgDefeatBoss_c::update() {

    StoryflagManager* pSVar1;
    bool bVar4;
    u16 uVar2;
    /*StoryFlags*/int SVar3;

    bVar4 = fn_494_D0();
    if (bVar4) {
        switch (var8_1) {
        case 0x0:
            uVar2 = getSceneflag();
            SceneflagManager::sInstance->unsetFlag
            (/*SceneflagManager::sInstance,*/ (u16)/*(param_1->base).members.roomid*/(mRoomID & 0xffff),
                (u16)(uVar2 & 0xffff));
            break;
        case 0x1:
            uVar2 = getSceneflag();
            SceneflagManager::sInstance->setFlag
            (/*SceneflagManager::sInstance,*/ (u16)/*(param_1->base).members.roomid*/mRoomID & 0xffff,
                (u16)uVar2 & 0xffff);
            break;
        }
        //pSVar1 = StoryflagManager::sInstance;
        switch (var8_2) {
        case 0x0:
            pSVar1 = StoryflagManager::sInstance;
            SVar3 = getStoryflag();
            pSVar1->unsetFlag(SVar3);
            break;
        case 0x1:
            pSVar1 = StoryflagManager::sInstance;
            SVar3 = getStoryflag();
            pSVar1->setFlag(SVar3);
            break;
        }
        fBase_c::deleteRequest();
    }

    return SUCCEEDED;
}

u16 dTgDefeatBoss_c::getSceneflag() {
    return mParams & 0xff;
}

u16 dTgDefeatBoss_c::fn_494_360() {

    return mParams >> 0x8 & 0x1;

}

u16 dTgDefeatBoss_c::getStoryflag() {
    return mParams >> 9 & 0xffff;
}

u16 dTgDefeatBoss_c::fn_494_380() {

    return (mParams >> 0x19) & 0x1;

}

