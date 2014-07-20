#ifndef FSTMachine_h__
#define FSTMachine_h__
#include <define.h>

class IFSTCallback
{
public :
    virtual void OnStateTrans(int nCurStat,int nTranStat)=0;
};

class CFSTMachine
{
    struct MyStruct
    {
        int nCurState;
        int nEvent;
        bool operator ()(MyStruct left,MyStruct right)
        {
            if (left.nCurState!= right.nCurState)
            {
                return left.nCurState > right.nCurState;
            }
            else if (left.nEvent != right.nEvent)
            {
                return left.nEvent > right.nEvent;
            }
            return false;
        }
    };
public:
    CFSTMachine(IFSTCallback* pCB,int nIntStat);
    ~CFSTMachine(void);

    void InitEvent(int nCurStat,int nEvent,int nTranStat)
    {
        MyStruct st;
        st.nCurState = nCurStat;
        st.nEvent = nEvent;
        m_staMap[st]  = nTranStat;
    }

    bool OnEvent(int eEvent)
    {
        MyStruct st;
        st.nCurState = m_nCurStat;
        st.nEvent = eEvent;
        if (m_staMap.count(st))
        {
			if (m_nCurStat != m_staMap[st])
			{
				m_nCurStat = m_staMap[st];
				m_pCB->OnStateTrans(m_nCurStat,m_staMap[st]);
			}
            return true;
        }
        return false;
    }

	int GetCurStat()
	{
		return m_nCurStat;
	}

	void SetCurStat(int nStat)
	{
		m_nCurStat = nStat;
	}
private:
    tmap<MyStruct,int,MyStruct> m_staMap;
    IFSTCallback* m_pCB;
    int           m_nCurStat;

};

#endif // FSTMachine_h__