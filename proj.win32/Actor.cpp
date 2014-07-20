#include "Actor.h"
#include "ActionSprite.h"
#include "ASMonster.h"


CActor::CActor(std::string strName,int nFrame)
{
    m_pAS = new CASMonster();
}


CActor::~CActor(void)
{
}
