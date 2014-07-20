#include "UserHeroGroup.h"
#include "../cocos2dx/platform/CCFileUtils.h"
#include "../cocos2dx/support/tinyxml2/tinyxml2.h"
#include <string>
#include "../cocos2dx/platform/CCCommon.h"
#include "ConfigMgr.h"
#include "Hero.h"
#include "GameLayer.h"
#include "GameLogic.h"
#include "HudLayer.h"
using namespace tinyxml2; 
using namespace cocos2d;

 ///tinyxml2::XMLDocument* doc;


CUserHeroGroup::CUserHeroGroup(void* pCfg,cocos2d::CCLayer* pLayer):
m_fCheckDistance(0)
{
    m_pFST = OP_NEW CFSTMachine(this,eGroupStateBorn);

    m_pFST->InitEvent(eGroupStateBorn,eGroupEventMF,eGroupStateMF);
	m_pFST->InitEvent(eGroupStateStop,eGroupEventMF,eGroupStateMF);
	m_pFST->InitEvent(eGroupStateRB,eGroupEventMF,eGroupStateMF);

	m_pFST->InitEvent(eGroupStateMF,eGroupEventStop,eGroupStateStop);
	m_pFST->InitEvent(eGroupStateRB,eGroupEventStop,eGroupStateStop);
	m_pFST->InitEvent(eGroupStateBorn,eGroupEventStop,eGroupStateStop);

	///m_pFST->InitEvent(eGroupStateMF,eGroupEventRB,eGroupStateRB);
	m_pFST->InitEvent(eGroupStateStop,eGroupEventRB,eGroupStateRB);

    m_pFST->InitEvent(eGroupStateRFBatt,eGroupEventRB,eGroupStateRB);

	pCfgMgr = static_cast<CConfigMgr*> (pCfg);
	tinyxml2::XMLElement* pEle = pCfgMgr->GetCfgNodeByName("player_heroes");
	m_nMaxDistance = atoi(pEle->Attribute("max-distance"));
	m_nMinDistance = atoi(pEle->Attribute("min-distance"));
	m_fCfgAdjustGroupTime = atoi(pEle->Attribute("check-adjust-group-delta"))/1000.f;
	tinyxml2::XMLElement *HeroNode=pEle->FirstChildElement(); 
	int i=0;
	while (HeroNode != NULL)
	{
		tinyxml2::XMLElement* pTempletNode = GetTempletCfg(HeroNode->Attribute("heroName"));
		CHero* pHero = new CHero(HeroNode,pTempletNode);
		if (i==0)
		{
			cocos2d::ccColor3B color;
			color.r = 255;
			color.g = 200;
			pHero->setColor(color);
			pHero->setOpacity(150);
		}

		if (i==2)
		{
			pHero->setOpacity(100);
		}

		pHero->setPosition(ccp(atoi(HeroNode->Attribute("posX")),atoi(HeroNode->Attribute("posY"))));
		pHero->idle();
		pHero->attack();
		m_vHeros.push_back(pHero);
		HeroNode = HeroNode->NextSiblingElement();
		pLayer->addChild(pHero);
		i++;
	}	
}

CUserHeroGroup::~CUserHeroGroup(void)
{
    OP_DEL(m_pFST);
}

void CUserHeroGroup::update(float dt)
{
	HudLayer* pHuderLayer = static_cast<HudLayer*>(CGameLogic::GetInstance()->HudLayer());
	CCPoint velocity = pHuderLayer->mJoystick->getVelocity();

	if (velocity.x > 0.4f ) 
	{
		m_pFST->OnEvent(eGroupEventMF);
	} 
	else if (velocity.x < -0.4f) 
	{
		m_pFST->OnEvent(eGroupEventRB);
	}
	else 
	{
		m_pFST->OnEvent(eGroupEventStop);
	}

	if (m_pFST->GetCurStat() == eGroupStateMF)
	{
		m_fCheckDistance += dt;
		if (m_fCheckDistance >= m_fCfgAdjustGroupTime)
		{
			AdjustGroup();
			m_fCheckDistance -= m_fCfgAdjustGroupTime;
		}
	}
	else if (m_pFST->GetCurStat() == eGroupStateRB)
	{

	}
	else
	{

	}

	for (size_t i=0;i<m_vHeros.size();++i)
	{
		m_vHeros[i]->update(dt);
	}
	
}

void CUserHeroGroup::Stop()
{
	for (size_t i=0;i<m_vHeros.size();++i)
	{
		m_vHeros[i]->idle();
	}
}


void CUserHeroGroup::Walk()
{
	for (size_t i=0;i<m_vHeros.size();++i)
	{
		m_vHeros[i]->walk();
	}
}

void CUserHeroGroup::RunBack()
{
	for (size_t i=0;i<m_vHeros.size();++i)
	{
		m_vHeros[i]->runBack();
	}
}

void CUserHeroGroup::OnGroupEvent( eGroupEvent eEvent )
{
	m_pFST->OnEvent(eEvent);
	return;
	if (eGroupEventMF == eEvent)
	{
		m_vHeros[0]->walk();
	}
}

tinyxml2::XMLElement* CUserHeroGroup::GetTempletCfg( const char* szName )
{
	tinyxml2::XMLElement* pEle = pCfgMgr->GetCfgNodeByName("actionSpriteTemplets");

	tinyxml2::XMLElement *pTempletCfg=pEle->FirstChildElement();

	while (pTempletCfg != NULL)
	{
		if (pTempletCfg->Attribute("heroName") == string(szName))
		{
			return pTempletCfg;
		}
		pTempletCfg = pTempletCfg->NextSiblingElement();
	}

	return NULL;
}

int GetDitance(CHero* pHero1,CHero* pHero2)
{
	return pHero1->getPositionX() - pHero2->getPositionX();
}

///根据英雄和前面英雄的距离调整英雄【跑 走 停】状态 

void CUserHeroGroup::AdjustGroup( )
{
	//最后一个位置是猪脚  最前面一个位置是领跑者,id大的在前面
	/*
		<hero heroName="hero1" speed="60" posX="150" posY ="30">
		</hero>
		<hero heroName="hero2" speed="80" posX="300" posY ="40">
		</hero>
		<hero heroName="hero3" speed="100" posX="400" posY ="40">
	*/
#define  nLastFollow 0
	int nCurBase = m_vHeros.size()-1;
	int nFollow = nCurBase-1;
	while (nFollow >=nLastFollow && nCurBase>=nLastFollow)
	{
		if (! m_vHeros[nCurBase]->IsAlive())
		{
			nCurBase--;
			nFollow = nCurBase -1;
			continue;
		}

		while (nFollow >= nLastFollow && ! m_vHeros[nFollow]->IsAlive())
		{
			nFollow -= 1;
		}

		if (nFollow < nLastFollow)
		{
			break;
		}

		{
			if (GetDitance(m_vHeros[nCurBase],m_vHeros[nFollow]) <= m_nMinDistance )
			{
				m_vHeros[nFollow]->idle();///距离太远，前面的人停一下
				CCLOG("idle");
			}
			else if (GetDitance(m_vHeros[nCurBase],m_vHeros[nFollow]) >= m_nMaxDistance )
			{
				m_vHeros[nFollow]->run();///距离太近，前面的人妖跑步
				CCLOG("run");
			}
			else 
			{
				m_vHeros[nFollow]->walk();
				CCLOG("walk");
			}
		}

		nCurBase--;
		nFollow = nCurBase-1;
	}
}

void CUserHeroGroup::OnStateTrans( int nCurStat,int nTranStat )
{
	/*
	enum eGroupState
	{
	eGroupStateBorn=1,///站立在初始化位置 不动
	eGroupStateStop,///不动
	eGroupStateMF,///走向前
	eGroupStateRFBatt,///跑向前,加入战斗
	eGroupStateRB,///跑向后
	};
	*/
	switch (nTranStat)
	{
	case eGroupStateBorn:
	case eGroupStateStop:
		{
			CCLOG("eGroupStateStop");
			Stop();
			break;
		}
	case eGroupStateMF:
		{
			CCLOG("eGroupStateMF");
			Walk();
			break;
		}
	case  eGroupStateRB:
		{
			CCLOG("eGroupStateRB");
			RunBack();
			break;
		}
	default:
		break;
	}
}

cocos2d::CCPoint CUserHeroGroup::GetViewPoint()
{
	return m_vHeros[m_vHeros.size()-1]->getPosition();
}
