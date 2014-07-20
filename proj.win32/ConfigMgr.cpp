#include "ConfigMgr.h"
using namespace tinyxml2; 

CConfigMgr::CConfigMgr(void)
{
}


CConfigMgr::~CConfigMgr(void)
{
}

tinyxml2::XMLElement* CConfigMgr::GetCfgNodeByName( const char* strNodeName )
{
	tinyxml2::XMLElement *ani_node=doc->RootElement();   
	tinyxml2::XMLElement *common_node=ani_node->FirstChildElement(); 
	while (common_node != NULL)
	{
		///common_node->Value();
		///const XMLAttribute *attribute = common_node->FirstAttribute();
		///CCLOG("%s,%s",attribute->Value(),common_node->Value() );
		if (common_node->Value()  == string(strNodeName))
		{
			return common_node;
		}
		common_node = common_node->NextSiblingElement();
	}
	return NULL;
}

bool CConfigMgr::LoadScenceCfg( const char* szPath )
{
	//根据xml数据创建动画  
	string xmlFile_path = "player-templet.xml";  
	//获得文件在系统的绝对路径  
	string xmlfilepath = CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlFile_path.c_str());  
	//读取的字节数，读取失败则为0  
	unsigned long len = 0;  
	//读取的内容  
	unsigned char *data =CCFileUtils::sharedFileUtils()->getFileData(xmlfilepath.c_str(), "r", &len);  
	//读取动作XML文件  
	doc=new tinyxml2::XMLDocument();  
	XMLError err = doc->Parse((char*)data, len);  
	tinyxml2::XMLElement *ani_node=doc->RootElement();   
	tinyxml2::XMLElement *common_node=ani_node->FirstChildElement(); 
	while (common_node != NULL)
	{
		const XMLAttribute *attribute = common_node->FirstAttribute();
		CCLOG("%s",attribute->Value() );
		if (string(attribute->Value()) == string("actionSpriteTemplets"))
		{
			tinyxml2::XMLElement *templet_node  = common_node->FirstChildElement();
			while (templet_node)
			{
				CCLOG("%s",templet_node->FirstAttribute()->Value());
				m_mapHeroCfg[templet_node->FirstAttribute()->Value()] = templet_node;
				templet_node = templet_node->NextSiblingElement();
			}  
		}
		common_node = common_node->NextSiblingElement();
	}
	return false;
}

const char* CConfigMgr::GetAttri( tinyxml2::XMLElement *common_node,const char* szAttri )
{
	const tinyxml2::XMLAttribute *attribute = common_node->FirstAttribute();
	while (attribute)
	{
		if (attribute->Name()==string(szAttri))
		{
			return attribute->Value();
		}
		attribute = attribute->Next();
	}

	return NULL;
}
