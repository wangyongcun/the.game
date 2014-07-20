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

///��ɫѪ������==����
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
    eGroupStateBorn=1,///վ���ڳ�ʼ��λ�� ����
    eGroupStateStop,///����
    eGroupStateMF,///����ǰ
    eGroupStateRFBatt,///����ǰ,����ս��
    eGroupStateRB,///�����
};

enum eGroupEvent
{
    eGroupEventMF=1,///ǰ��
    ///eGroupEventRF,///��ǰ��
    eGroupEventRB,///�����
    eGroupEventStop,///����ֹͣ
};

///Ӣ��״̬,��actionSprite�Ķ���״̬��ͬ
enum eHeroState
{
    eHeroStateBorn=1,
    eHeroStateStop,///����λ�ã�׼������,
    eHeroStateMF,///����ǰ
    eHeroStateRF,///����ǰ
    eHeroStateRB,///����� 
    eHeroStateBatt,
};
#endif // define_h__