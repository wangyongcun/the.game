#include "GameLayer.h"
#include "Defines.h"
#include "Robot.h"
#include "ActionSprite.h"
#include "GameScene.h"
#include "Actor.h"
#include "ConfigMgr.h"
#include "UserHeroGroup.h"


using namespace tinyxml2; 
using namespace cocos2d;

#define actor_texture "pd_sprites.plist"
#define actor_png "pd_sprites.png"




GameLayer::GameLayer(CConfigMgr* theCfg)
{
	
    m_CfgMgr = theCfg;

	CCSpriteFrameCache* cache = 
		CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(actor_texture, actor_png);

	tinyxml2::XMLElement* pMap = m_CfgMgr->GetCfgNodeByName("map");
	const char* pSzFilePng = m_CfgMgr->GetAttri(pMap,"textureFilePng");
	const char* pSzFilePList = m_CfgMgr->GetAttri(pMap,"textureFilePlist");

    cache->addSpriteFramesWithFile(pSzFilePList, pSzFilePng);
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/

	CCTexture2D *texture=CCTextureCache::sharedTextureCache()->textureForKey(actor_png);
	mActorsSpriteBatchNode=CCSpriteBatchNode::createWithTexture(texture);
	mActorsSpriteBatchNode->getTexture()->setAliasTexParameters();
	this->addChild(mActorsSpriteBatchNode, 5);

	m_pGroup = new CUserHeroGroup(m_CfgMgr/*->GetCfgNodeByName("player_heroes")*/,this);

	///m_pGroup->SetPos();
	this->scheduleUpdate();

	
    CCTexture2D *texture2=CCTextureCache::sharedTextureCache()->textureForKey(pSzFilePng);
    mActorsSpriteBatchNode=CCSpriteBatchNode::createWithTexture(texture2);
    //mActors = CCSpriteBatchNode::create("pd_sprites.png",50);
    mActorsSpriteBatchNode->getTexture()->setAliasTexParameters();
    this->addChild(mActorsSpriteBatchNode, 5);

	init();
}

bool GameLayer::init()
{
	CCLayer::init();

	mHero = new CHero(NULL,NULL);
	this->addChild(mHero);
	
	
	initTileMap();
	initHero();
    initRobots();

	m_MaxMapX = mTileMap->getMapSize().width * mTileMap->getTileSize().width;
	m_MaxMapY = 3 * mTileMap->getTileSize().height;

	m_kathia = CCSprite::create("arrow.png");
	m_kathia->retain();
	addChild(m_kathia, 3);
	m_kathia->setPosition(ccp(200,200));
	return true;
}

void GameLayer::initTileMap()
{
	mTileMap = CCTMXTiledMap::create("pd_tilemap.tmx");
	CCObject* itemLayer;
	CCARRAY_FOREACH(mTileMap->getChildren(), itemLayer)
	{
		CCTMXLayer* tmxLayer = dynamic_cast<CCTMXLayer*>(itemLayer);
		tmxLayer->getTexture()->setAliasTexParameters();
	}
	this->addChild(mTileMap, -6);
}

void GameLayer::initHero()
{
	mHero->setPosition(ccp(mHero->mCenterToSide, 360));
	mHero->mDesiredPosition = mHero->getPosition();
	mHero->idle();
}

/*void GameLayer::ccTouchesBegan(CCSet* pTouches, CCEvent* pEvents)
{
	mHero->attack();
}*/

void GameLayer::update(float dt)
{
	CCLayer::update(dt);
	m_pGroup->update(dt);
	
	reorderActors();
	this->setViewpointCenter(m_pGroup->GetViewPoint());

	///updatePosition(dt);
	//updateRobots(dt);
}

void GameLayer::updatePosition(float dt)
{
	//float posX = GetMIN(m_MaxMapX - mHero->mCenterToSide, 
	//	GetMAX(mHero->mCenterToSide, mHero->mDesiredPosition.x));
	//float posY = GetMIN(m_MaxMapY + mHero->mCenterToBottom, 
	//	GetMAX(mHero->mCenterToBottom, mHero->mDesiredPosition.y));
	//
	//CCObject* item;
	//CCARRAY_FOREACH(mRobots, item) {
	//	Robot* robot = dynamic_cast<Robot*>(item);
	//	posX = GetMIN(mTileMap->getMapSize().width * mTileMap->getTileSize().width - robot->mCenterToSide, 
	//		GetMAX(robot->mCenterToSide, robot->mDesiredPosition.x));
	//	posY = GetMIN(3 * mTileMap->getTileSize().height + robot->mCenterToBottom, 
	//		GetMAX(robot->mCenterToBottom, robot->mDesiredPosition.y));

	//	robot->setPosition(ccp(posX, posY));
	//}
	
}

void GameLayer::setViewpointCenter(CCPoint position)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = GetMAX(position.x, winSize.width / 2);
	int y = GetMAX(position.y, winSize.height / 2);

	x = GetMIN(x, (mTileMap->getMapSize().width * 
		mTileMap->getTileSize().width - winSize.width / 2));
	y = GetMIN(y, (mTileMap->getMapSize().height * 
		mTileMap->getTileSize().height - winSize.height / 2));

	CCPoint actualPosition = ccp(x, y);
	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);

	this->setPosition(viewPoint);
    //CCLOG("%f,%f",viewPoint.x,viewPoint.y);
}

void GameLayer::initRobots()
{
	int robotCount = 1;
	this->mRobots = new CCArray(robotCount);

	for (int i = 0; i < robotCount; ++i) {
		Robot* robot = new Robot();
		//mActors->addChild(robot);
		this->addChild(robot);
		mRobots->addObject(robot);

		int minX = SCREEN.width + robot->mCenterToSide;
		int maxX = mTileMap->getMapSize().width * mTileMap->getTileSize().width 
			- robot->mCenterToSide;
		int minY = robot->mCenterToBottom;
		int maxY = 3 * mTileMap->getTileSize().height + robot->mCenterToBottom;

		if (rand() % 2)
			robot->setFlipX(true);
		robot->setPosition(
			ccp(random_range(minX, maxX), random_range(minY, maxY)));
		robot->mDesiredPosition = robot->getPosition();
		robot->idle();
	}
}

void GameLayer::reorderActors()
{
	CCObject* item;
	//CCARRAY_FOREACH(mActors->getChildren(), item)
	CCARRAY_FOREACH(this->getChildren(), item) {
		CCNode *node = dynamic_cast<CCNode *>(item);
		if (node->getTag() == ACTION_SPRITE_TAG) {
			ActionSprite *sprite = dynamic_cast<ActionSprite *>(item);
			this->reorderChild(sprite, mTileMap->getMapSize().height * mTileMap->getTileSize().height 
				- sprite->getPositionY());
		}
	}
}

void GameLayer::updateRobots(float dt)
{
	//int alive = 0;
	//double distanceSQ;
	//int randomChoice = 0;

	//CCObject* item;
	//CCARRAY_FOREACH(mRobots, item) {
	//	Robot* robot = dynamic_cast<Robot*>(item);
	//	robot->update(dt);

	//	if (robot->mActionState != kActionStateKnockedOut) {
	//		++alive;
	//		robot->mNextDecisionTime -= dt;
	//		if (robot->mNextDecisionTime <= 0.0f) {
	//			distanceSQ = ccpDistanceSQ(robot->getPosition(), mHero->getPosition());
	//			if (distanceSQ <= 50*50) {
	//				robot->mNextDecisionTime = frandom_range(0.5f, 1.0f, 0.1f);
	//				randomChoice = random_range(0, 1);
	//				if (randomChoice == 0) {
	//					if (mHero->getPositionX() > robot->getPositionX()) {
	//						robot->setFlipX(false);
	//					} else {
	//						robot->setFlipX(true);
	//					}

	//					robot->attack();
	//					if (robot->mActionState == kActionStateAttack) {
	//						if (fabs(mHero->getPositionY() - robot->getPositionY()) < 10) {
	//							if (mHero->mHitBox.actual.intersectsRect(robot->mAttackBox.actual)) {
	//								mHero->hurtWithDamage(robot->mDamage);
	//							}
	//						}
	//					}
	//				} else {
	//					robot->idle();
	//				}
	//			} else if (distanceSQ <= SCREEN.width * SCREEN.width) {
	//				robot->mNextDecisionTime = frandom_range(1.0f, 1.5f, 0.1f);
	//				robot->mNextDecisionTime = random_range(5, 10) * 0.1f;
	//				randomChoice = random_range(0, 2);
	//				if (randomChoice == 0) {
	//					CCPoint moveDirection = ccpNormalize(ccpSub(mHero->getPosition(), robot->getPosition()));
	//					robot->walkWithDirection(moveDirection);
	//				} else {
	//					robot->idle();
	//				}
	//			}
	//		}
	//	}
	//}
}
void bto(cocos2d::CCSprite* pSprite,cocos2d::CCPoint endPos)
{
	pSprite->setPosition(ccp(200,200));
	pSprite->setRotation(0);
#define hight 400
#define fly_time 1
#define end_angle ((120/360.0f)*2*3.1415)
	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = pSprite->getPosition();
	bezier2.controlPoint_2 = ccp(pSprite->getPositionX()+(endPos.x-pSprite->getPositionX())*0.5, hight);
	bezier2.endPosition = endPos;
	CCActionInterval*  bezierTo1 = CCBezierTo::create(fly_time, bezier2);
	float angle = end_angle;
	CCActionInterval*  angleTo = CCRotateTo::create(fly_time,120);
	CCSpawn* pSpawn = CCSpawn::createWithTwoActions(bezierTo1,angleTo);
	pSprite->runAction(pSpawn);

}

void GameLayer::onButtonA()
{
	bto(m_kathia,ccp(800,200));
}
