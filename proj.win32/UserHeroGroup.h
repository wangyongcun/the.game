#ifndef UserHeroGroup_h__
#define UserHeroGroup_h__
#include <vector>
#include "define.h"
#include "FSTMachine.h"
#include "cocos2d.h"
using namespace cocos2d;

class CConfigMgr;
namespace tinyxml2
{
	class XMLElement;
}
class CHero;
using namespace std;

namespace cocos2d
{
	class CCLayer;
}


class CUserHeroGroup:public IFSTCallback
{
public:
    CUserHeroGroup(void* pCfg,cocos2d::CCLayer* pLayer);
    ~CUserHeroGroup(void);

    void AdjustGroup();
	
    void OnGroupEvent(eGroupEvent eEvent);

	void update(float dt);
	
	void Stop();

	void RunBack();

	void Walk();

	cocos2d::CCPoint GetViewPoint();

    virtual void OnStateTrans(int nCurStat,int nTranStat);
	tinyxml2::XMLElement* GetTempletCfg(const char* szName);
private:
    eGroupState m_nState;
    CFSTMachine* m_pFST;
	vector<CHero*> m_vHeros;
	CConfigMgr* pCfgMgr;

	///检查英雄间距离的时间间隔
	float m_fCheckDistance;
	///英雄间的最长和最短距离
	int	  m_nMaxDistance;
	int	  m_nMinDistance;
	float  m_fCfgAdjustGroupTime;
};


#endif // UserHeroGroup_h__