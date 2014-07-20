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
	//����xml���ݴ�������  
	string xmlFile_path = "player-templet.xml";  
	//����ļ���ϵͳ�ľ���·��  
	string xmlfilepath = CCFileUtils::sharedFileUtils()->fullPathForFilename(xmlFile_path.c_str());  
	//��ȡ���ֽ�������ȡʧ����Ϊ0  
	unsigned long len = 0;  
	//��ȡ������  
	unsigned char *data =CCFileUtils::sharedFileUtils()->getFileData(xmlfilepath.c_str(), "r", &len);  
	//��ȡ����XML�ļ�  
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
