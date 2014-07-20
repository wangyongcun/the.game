#ifndef GameLogic_h__
#define GameLogic_h__
namespace cocos2d
{
	class CCLayer;
}
class CGameLogic
{
public:
	CGameLogic(void);
	~CGameLogic(void);
	static CGameLogic* GetInstance()
	{
		if (g_Instance==0)
		{
			g_Instance = new CGameLogic();
		}

		return g_Instance;
	}
	cocos2d::CCLayer* Layer() const { return m_pLayer; }
	void Layer(cocos2d::CCLayer* val) { m_pLayer = val; }
	cocos2d::CCLayer* HudLayer() const { return m_pmHudLayer; }
	void HudLayer(cocos2d::CCLayer* val) { m_pmHudLayer = val; }

private:
	cocos2d::CCLayer* m_pLayer;
	cocos2d::CCLayer* m_pmHudLayer;
	static CGameLogic* g_Instance;
};

#endif // GameLogic_h__

