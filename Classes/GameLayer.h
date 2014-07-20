#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "cocos2d.h"
using namespace cocos2d;

#include "Hero.h"
#include "Actor.h"
class CConfigMgr;
class CUserHeroGroup;

class GameLayer : public CCLayer
{
public :
	GameLayer(CConfigMgr* theCfg);
	bool init();

	CCTMXTiledMap* mTileMap;

	void initTileMap();
	void initHero();
	
	void update(float dt);

	void updatePosition(float dt);

	void setViewpointCenter(CCPoint position);

	CCArray* mRobots;
	void initRobots();

	void reorderActors();
	void updateRobots(float dt);

	int MaxMapX() const { return m_MaxMapX; }
	void MaxMapX(int val) { m_MaxMapX = val; }
	int MaxMapY() const { return m_MaxMapY; }
	void MaxMapY(int val) { m_MaxMapY = val; }
	void onButtonA();
	
	CHero* mHero;
private:
	int m_MaxMapX;
	int m_MaxMapY;
	CConfigMgr* m_CfgMgr;
	CUserHeroGroup* m_pGroup;

	CCSprite* m_kathia;
	//void ccTouchesBegan(CCSet* pTouches, CCEvent* pEvents);
	CCSpriteBatchNode* mActorsSpriteBatchNode;


};

#endif