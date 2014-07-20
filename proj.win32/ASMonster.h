#ifndef ASMonster_h__
#define ASMonster_h__
#include "ActionSprite.h"

class CASMonster: public ActionSprite
{
public:
    CASMonster(void);
    ~CASMonster(void);
public:
    bool init();
};

#endif // ASMonster_h__