#ifndef define_h__
#define define_h__
#include <string>
#include <map>
#include <vector>

using namespace std;
#define  OP_NEW new
#define  OP_DEL delete

#define  GROUP_PLAYER_NUM 4
#define  HERO_STATE_NUM 4
//////type define
#define  tstring std::string
#define  tmap std::map

///<state id ="1" name="stand" frameNamePrefix="datoujiguai/yidong/0100" frameNum ="10" frameSpeed="1.0" moveSpeed="0.0">
typedef struct stHeroState
{
    int         ID;
    tstring     Name;
    tstring     FrameNamePrefix;
    int         FrameNum;
    float       FrameSpeed;
    float       MoveSpeed;
}STHeroState;

typedef struct stHeroCfg
{
    STHeroState stStates[HERO_STATE_NUM];
}STHeroCfg;

typedef struct stUserGroupCfg
{
    STHeroCfg arrHero[GROUP_PLAYER_NUM];
}STUserGroupCfg;

///红色血条的人==敌人
typedef struct stRedActorCfg
{
}STRedActorCfg;

typedef struct stScenceCfg
{
    STRedActorCfg  stRedActor;
    STUserGroupCfg stGroup;
}STScenceCfg;

enum eGroupState
{
    eGroupStateBorn=1,///站立在初始化位置 不动
    eGroupStateStop,///不动
    eGroupStateMF,///走向前
    eGroupStateRFBatt,///跑向前,加入战斗
    eGroupStateRB,///跑向后
};

enum eGroupEvent
{
    eGroupEventMF=1,///前移
    ///eGroupEventRF,///向前跑
    eGroupEventRB,///向后跑
    eGroupEventStop,///队伍停止
};

///英雄状态,和actionSprite的动画状态不同
enum eHeroState
{
    eHeroStateBorn=1,
    eHeroStateStop,///调整位置，准备行走,
    eHeroStateMF,///走向前
    eHeroStateRF,///跑向前
    eHeroStateRB,///跑向后 
    eHeroStateBatt,
};
#endif // define_h__