#include "ActionSprite.h"
#include "Defines.h"
#include "GameLogic.h"
#include "GameLayer.h"
#include "HudLayer.h"

ActionSprite::ActionSprite():
	mWalkSpeed(80.0f)
{
	CCSprite::initWithSpriteFrameName("hero_idle_00.png");
	mHitBox.actual = CCRectZero;
	mHitBox.original = CCRectZero;
	mAttackBox.actual = CCRectZero;
	mAttackBox.original = CCRectZero;
	init();
}

bool ActionSprite::init()
{
	this->setTag(ACTION_SPRITE_TAG);
	CCSprite::init();

	return true;
}

void ActionSprite::idle()
{
	if (mActionState != kActionStateIdle) {
		this->stopAllActions();
		this->runAction(mIdleAction);
		mActionState = kActionStateIdle;
		mVelocity = CCPointZero;
	}
}

void ActionSprite::attack()
{
	if (mActionState == kActionStateIdle || 
		mActionState == kActionStateAttack || 
		mActionState == kActionStateWalk) {
		this->stopAllActions();
		this->runAction(mAttackAction);
		mActionState = kActionStateAttack;
	}
}

void ActionSprite::hurtWithDamage(float damage)
{
	if (mActionState != kActionStateKnockedOut) {
		this->stopAllActions();
		this->runAction(mHurtAction);
		mActionState = kActionStateHurt;
		mHitPoints -= damage;

		if (mHitPoints <= 0.0f) {
			this->knockout();
		}
	}
}

void ActionSprite::knockout()
{
	this->stopAllActions();
	this->runAction(mKnockedOutAction);
	mHitPoints = 0.0f;
	mActionState = kActionStateKnockedOut;
}

void ActionSprite::walk()
{
	//HudLayer* pHuderLayer = static_cast<HudLayer*>(CGameLogic::GetInstance()->HudLayer());
	//mCurDirection = pHuderLayer->mJoystick->getVelocity();
	mCurDirection = ccp(1.0,0);
	if (mActionState != kActionStateWalk) {
		this->stopAllActions();
		this->runAction(mWalkAction);
		mActionState = kActionStateWalk;
		mVelocity = ccp(mCurDirection.x * mWalkSpeed, mCurDirection.y * mWalkSpeed);
		if (mVelocity.x >= 0)
			this->setFlipX(false);
		else
			this->setFlipX(true);
	}
}

void ActionSprite::run()
{
	///HudLayer* pHuderLayer = static_cast<HudLayer*>(CGameLogic::GetInstance()->HudLayer());
	mCurDirection = ccp(1.0,0);

	if (mActionState != kActionStateRun) {
		this->stopAllActions();
		this->runAction(mRunAction);
		mActionState = kActionStateRun;
		mVelocity = ccp(mCurDirection.x * mRunSpeed, mCurDirection.y * mRunSpeed);
		if (mVelocity.x >= 0)
			this->setFlipX(false);
		else
			this->setFlipX(true);
	}
}

void ActionSprite::runBack()
{
	mCurDirection = ccp(-1.0,0);
	if (mActionState != kActionStateRun) {
		this->stopAllActions();
		this->runAction(mRunAction);
		mActionState = kActionStateRun;
		mVelocity = ccp(mCurDirection.x * mWalkSpeed*1.5, mCurDirection.y * mWalkSpeed*1.5);
		if (mVelocity.x >= 0)
			this->setFlipX(false);
		else
			this->setFlipX(true);
	}
}

void ActionSprite::update(float dt)
{
	switch (mActionState)
	{
	default:
		break;
	}

	if (mActionState == kActionStateWalk||kActionStateRun == mActionState) {
		mDesiredPosition = ccpAdd(this->getPosition(), 
			ccpMult(mVelocity, dt));

		GameLayer* pLayer = static_cast<GameLayer*>(CGameLogic::GetInstance()->Layer());

		float posX = GetMIN(pLayer->MaxMapX() - this->mCenterToSide, 
			GetMAX(this->mCenterToSide, this->mDesiredPosition.x));
		float posY = GetMIN(pLayer->MaxMapY() + this->mCenterToBottom, 
			GetMAX(this->mCenterToBottom, this->mDesiredPosition.y));

		this->setPosition(ccp(posX, posY));
	}

	CCSprite::update(dt);
}

BoundingBox ActionSprite::createBoundingBoxWithOrigin(CCPoint origin, CCSize size)
{
	BoundingBox bBox;
	bBox.original.origin = origin;
	bBox.original.size = size;
	bBox.actual.origin = ccpAdd(this->getPosition(), 
		ccp(bBox.original.origin.x, bBox.original.origin.y));
	bBox.actual.size = size;

	return bBox;
}

void ActionSprite::transformBoxes()
{
	float xfactor = (this->isFlipX() ? -1 : 1);
	float xfactor2 = (this->isFlipX() ? 1 : 0);
	float yfactor = (this->isFlipY() ? -1 : 1);
	float yfactor2 = (this->isFlipY() ? 1 : 0);

	mHitBox.actual.origin = ccpAdd(this->getPosition(), 
		ccp(mHitBox.original.origin.x * xfactor - 
			mHitBox.original.size.width * xfactor2, 
		mHitBox.original.origin.y * yfactor - 
			mHitBox.original.size.height * yfactor2));
	mHitBox.actual.size = CCSizeMake(
		mHitBox.original.size.width, 
		mHitBox.original.size.height);

	mAttackBox.actual.origin = ccpAdd(this->getPosition(), 
		ccp(mAttackBox.original.origin.x * xfactor - 
			mAttackBox.original.size.width * xfactor2, 
		mAttackBox.original.origin.y * yfactor - 
			mAttackBox.original.size.height * yfactor2));
	mAttackBox.actual.size = CCSizeMake(
		mAttackBox.original.size.width, 
		mAttackBox.original.size.height);
}

void ActionSprite::setPosition(const CCPoint& pos)
{
	CCSprite::setPosition(pos);
	this->transformBoxes();
}