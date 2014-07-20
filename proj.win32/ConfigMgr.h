#ifndef ConfigMgr_h__
#define ConfigMgr_h__
#include "../cocos2dx/support/tinyxml2/tinyxml2.h"
#include "../cocos2dx/platform/CCFileUtils.h"
#include <string>
#include "../cocos2dx/platform/CCCommon.h"

using namespace std;

using namespace cocos2d;

///using namespace tinyxml2; 

class CConfigMgr
{
public:
    CConfigMgr(void);
    ~CConfigMgr(void);

    bool LoadScenceCfg(const char* szPath);

	const char* GetAttri(tinyxml2::XMLElement *common_node,const char* szAttri);

    tinyxml2::XMLElement* GetCfgNodeByName(const char* strNodeName);
    
public:
    tinyxml2::XMLDocument* doc;
	 map<string,tinyxml2::XMLElement*> m_mapHeroCfg;
};

#endif // ConfigMgr_h__
