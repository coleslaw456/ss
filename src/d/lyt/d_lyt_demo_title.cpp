#include "d/lyt/d_lyt_demo_title.h"

#include "d/d_fader.h"
#include "d/d_stage.h"
#include "d/d_stage_mgr.h"
#include "d/d_sys.h"
#include "d/lyt/d2d.h"
#include "toBeSorted/arc_managers/layout_arc_manager.h"

extern "C" u32 lbl_805B7120;

#define TITLE_DEMO_MAIN_ANIM_IN 0
#define TITLE_DEMO_MAIN_ANIM_OUT 1

STATE_DEFINE(dLytDemoTitleMain_c, ModeNone);
STATE_DEFINE(dLytDemoTitleMain_c, ModeIn);
STATE_DEFINE(dLytDemoTitleMain_c, ModeMove);
STATE_DEFINE(dLytDemoTitleMain_c, ModeOut);
STATE_DEFINE(dLytDemoTitleMain_c, ModeEnd);

STATE_DEFINE(dLytDemoTitle_c, None);
STATE_DEFINE(dLytDemoTitle_c, In);
STATE_DEFINE(dLytDemoTitle_c, Move);
STATE_DEFINE(dLytDemoTitle_c, Out);
STATE_DEFINE(dLytDemoTitle_c, End);

dLytDemoTitle_c *dLytDemoTitle_c::sInstance;

void dLytDemoTitleMain_c::initializeState_ModeNone() {
    return;
}

void dLytDemoTitleMain_c::executeState_ModeNone() {
    mIsAnimating = true;
    return;
}

void dLytDemoTitleMain_c::finalizeState_ModeNone() {
    return;
}

void dLytDemoTitleMain_c::initializeState_ModeIn() {
    return;
}

void dLytDemoTitleMain_c::executeState_ModeIn() {
    if (mAnmGroups[TITLE_DEMO_MAIN_ANIM_IN].isEndReached()) {
        mAnmGroups[TITLE_DEMO_MAIN_ANIM_IN].setAnimEnable(false);
        mIsAnimating = true;
    }
    return;
}

void dLytDemoTitleMain_c::finalizeState_ModeIn() {
    return;
}

void dLytDemoTitleMain_c::initializeState_ModeMove() {
    return;
}

void dLytDemoTitleMain_c::executeState_ModeMove() {
    mIsAnimating = true;
    return;
}

void dLytDemoTitleMain_c::finalizeState_ModeMove() {
    return;
}

void dLytDemoTitleMain_c::initializeState_ModeOut() {
    return;
}

void dLytDemoTitleMain_c::executeState_ModeOut() {
    if (mAnmGroups[TITLE_DEMO_MAIN_ANIM_OUT].isEndReached()) {
        mAnmGroups[TITLE_DEMO_MAIN_ANIM_OUT].setAnimEnable(false);
        mIsAnimating = true;
    }
    return;
}

void dLytDemoTitleMain_c::finalizeState_ModeOut() {
    return;
}

void dLytDemoTitleMain_c::initializeState_ModeEnd() {
    return;
}

void dLytDemoTitleMain_c::executeState_ModeEnd() {
    mIsAnimating = true;
    return;
}

void dLytDemoTitleMain_c::finalizeState_ModeEnd() {
    return;
}

dLytDemoTitleMain_c::dLytDemoTitleMain_c() : mStateMgr(*this) {}

static const d2d::LytBrlanMapping brlanMap[] = {
    { "demoTitle_00_in.brlan", "G_inOut_00"},
    {"demoTitle_00_out.brlan", "G_inOut_00"},
};

bool dLytDemoTitleMain_c::build(d2d::ResAccIf_c *resAcc) {
    mLytBase.setResAcc(resAcc);
    mLytBase.build("demoTitle_00.brlyt", nullptr);
    mLytBase.setPriority(0x86);

    for (int i = 0; i < 2; i++) {
        mAnmGroups[i].init(brlanMap[i].mFile, resAcc, mLytBase.getLayout(), brlanMap[i].mName);
        mAnmGroups[i].bind(false);
        mAnmGroups[i].setAnimEnable(false);
    }

    mAnmGroups[TITLE_DEMO_MAIN_ANIM_IN].setAnimEnable(true);
    mAnmGroups[TITLE_DEMO_MAIN_ANIM_IN].setFrame(0.0f);

    mLytBase.calc();

    mAnmGroups[TITLE_DEMO_MAIN_ANIM_IN].setAnimEnable(false);

    fn_802B09F0();

    return true;
}

bool dLytDemoTitleMain_c::execute() {
    mLytBase.getLayout()->GetRootPane()->SetInfluencedAlpha(true);
    mLytBase.getLayout()->GetRootPane()->SetAlpha(255 - dStage_c::GetInstance()->getFader().getColorFaderAlpha());

    mStateMgr.executeState();

    for (int i = 0; i < 2; i++) {
        if (mAnmGroups[i].isEnabled()) {
            mAnmGroups[i].play();
        }
    }

    mLytBase.calc();

    return true;
}

bool dLytDemoTitleMain_c::draw() {
    mLytBase.addToDrawList();
    return true;
}

bool dLytDemoTitleMain_c::remove() {
    dStageMgr_c::GetInstance()->unsetFlags0x88a0(0xfffffffe);

    mLytBase.unbindAnims();

    for (int i = 0; i < 2; i++) {
        mAnmGroups[i].remove();
    }
    return true;
}

void dLytDemoTitleMain_c::fn_802B09F0() {
    mStateMgr.changeState(StateID_ModeNone);
    mIsAnimating = false;
    return;
}

void dLytDemoTitleMain_c::fn_802B0A50() {
    dStageMgr_c::GetInstance()->setFlags0x88a0(0x1);

    dSys_c::setClearColor(mColor(0xFF));

    mAnmGroups[TITLE_DEMO_MAIN_ANIM_IN].setAnimEnable(true);
    mAnmGroups[TITLE_DEMO_MAIN_ANIM_IN].setFrame(0.0f);
    mLytBase.calc();
    mStateMgr.changeState(StateID_ModeIn);
    mIsAnimating = false;
}

void dLytDemoTitleMain_c::fn_802B0B00() {
    mStateMgr.changeState(StateID_ModeMove);
    mIsAnimating = false;
    return;
}

void dLytDemoTitleMain_c::fn_802B0B50() {
    mAnmGroups[TITLE_DEMO_MAIN_ANIM_OUT].setAnimEnable(true);
    mAnmGroups[TITLE_DEMO_MAIN_ANIM_OUT].setFrame(0.0f);
    mLytBase.calc();
    mStateMgr.changeState(StateID_ModeOut);
    mIsAnimating = false;
    return;
}

void dLytDemoTitleMain_c::fn_802B0BD0() {
    mStateMgr.changeState(StateID_ModeEnd);
    mIsAnimating = false;
    return;
}

void dLytDemoTitle_c::initializeState_None() {
    return;
}

void dLytDemoTitle_c::executeState_None() {
    if (mIsAnimating) {
        mMain.fn_802B0A50();
        mStateMgr.changeState(StateID_In);
        mIsAnimating = false;
    }
    return;
}

void dLytDemoTitle_c::finalizeState_None() {
    return;
}

void dLytDemoTitle_c::initializeState_In() {
    return;
}

void dLytDemoTitle_c::executeState_In() {
    if (mMain.getmIsAnimating()) {
        mMain.fn_802B0B00();
        mStateMgr.changeState(StateID_Move);
    }
    return;
}

void dLytDemoTitle_c::finalizeState_In() {
    return;
}

void dLytDemoTitle_c::initializeState_Move() {
    return;
}

void dLytDemoTitle_c::executeState_Move() {
    if (mMain.getmIsAnimating() && field_0x58d) {
        mMain.fn_802B0B50();
        mStateMgr.changeState(StateID_Out);
        field_0x58d = false;
    }
    return;
}

void dLytDemoTitle_c::finalizeState_Move() {
    return;
}

void dLytDemoTitle_c::initializeState_Out() {
    return;
}

void dLytDemoTitle_c::executeState_Out() {
    if (mMain.getmIsAnimating()) {
        deleteRequest();
        mMain.fn_802B0BD0();
        mStateMgr.changeState(StateID_End);
    }

    return;
}

void dLytDemoTitle_c::finalizeState_Out() {
    return;
}

void dLytDemoTitle_c::initializeState_End() {
    return;
}

void dLytDemoTitle_c::executeState_End() {
    return;
}

void dLytDemoTitle_c::finalizeState_End() {
    return;
}

SPECIAL_BASE_PROFILE(LYT_DEMO_TITLE, dLytDemoTitle_c, fProfile::LYT_DEMO_TITLE, 0x2BA, 0);

int dLytDemoTitle_c::create() {
    sInstance = this;

    resAcc.attach(LayoutArcManager::GetInstance()->getLoadedData("DemoTitle"), "");

    mMain.build(&resAcc);
    mStateMgr.changeState(StateID_None);
    mIsAnimating = true;
    field_0x58d = false;
    return SUCCEEDED;
}

int dLytDemoTitle_c::execute() {
    if (*mStateMgr.getStateID() != StateID_None) {
        mMain.execute();
    }

    mStateMgr.executeState();

    return SUCCEEDED;
}

int dLytDemoTitle_c::draw() {
    if (*mStateMgr.getStateID() != StateID_None) {
        mMain.draw();
    }
    return SUCCEEDED;
}

int dLytDemoTitle_c::doDelete() {
    mMain.remove();
    resAcc.detach();
    sInstance = nullptr;
    return SUCCEEDED;
}
