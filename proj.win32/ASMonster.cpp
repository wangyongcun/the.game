#include "ASMonster.h"


CASMonster::CASMonster(void)
{
    CCSpriteFrameCache* cache = 
        CCSpriteFrameCache::sharedSpriteFrameCache();
    CCSprite::initWithSpriteFrameName("robot_idle_00.png");
    this->retain();

    char str[64] = {0};
    CCArray* animFrames = new CCArray(10);

    //Idle
    for (int i = 1; i < 10; ++i) {
        sprintf(str, "BOSS1/gongji/0100%02d.png", i);
        CCSpriteFrame* frame = cache->spriteFrameByName(str);
        animFrames->addObject(frame);
    }
    CCAnimation* idleAnimation = CCAnimation::createWithSpriteFrames(animFrames, 1.0f/12.0f);

    mIdleAction = 
        CCRepeatForever::create(CCAnimate::create(idleAnimation));
    mIdleAction->retain();
    this->setPositionX(this->getPositionX()+150);
    this->setPositionY(this->getPositionY()+150);
    

    this->runAction(mIdleAction);
}


CASMonster::~CASMonster(void)
{
}

bool CASMonster::init()
{
    ActionSprite::init();

    return true;
}
