#ifndef Actor_h__
#define Actor_h__

#include <string>
using namespace std;

class ActionSprite;
class CActor
{
public:
    CActor(std::string strName,int nFrame);
    ~CActor(void);
public:
    ActionSprite* m_pAS;
};

#endif // Actor_h__