#ifndef _HERO_H_
#define _HERO_H_

#include "ActionSprite.h"
#include "define.h"

class tinyxml2::XMLElement;

class CHero : public ActionSprite
{
public :
	CHero(tinyxml2::XMLElement* pHeroCfg,tinyxml2::XMLElement* pCfg);
	bool init();
	bool IsAlive()
	{
		return true;
	}
};

#endif