#ifndef _ACTION_SPRITE_H_
#define _ACTION_SPRITE_H_

#include "cocos2d.h"
using namespace cocos2d;

#include "Defines.h"
#include <string>
using namespace std;

class ActionSprite : public CCSprite
{
public :
	ActionSprite();
	virtual bool init();

	void idle();
	///Εά²½
	void run();
	void runBack();
	void walk();
	void attack();
	void hurtWithDamage(float damage);
	void knockout();
	virtual void update(float dt);

//protected :
	CCAction* mIdleAction;
	CCAction* mAttackAction;
	CCAction* mWalkAction;
	CCAction* mRunAction;
	CCAction* mHurtAction;
	CCAction* mKnockedOutAction;

	ActionState mActionState;

	CCPoint mCurDirection;
	float mWalkSpeed;
	float mRunSpeed;
	float mHitPoints;
	float mDamage;

	CCPoint mVelocity;
	CCPoint mDesiredPosition;

	float mCenterToSide;
	float mCenterToBottom;

	BoundingBox mHitBox;
	BoundingBox mAttackBox;

	BoundingBox createBoundingBoxWithOrigin(CCPoint origin, CCSize size);

	void transformBoxes();
	void setPosition(const CCPoint& pos);
};

#endif