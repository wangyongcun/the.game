#include "FSTMachine.h"


CFSTMachine::CFSTMachine(IFSTCallback* pCB,int nIntStat):
m_pCB(pCB),
m_nCurStat(nIntStat)
{
    
}


CFSTMachine::~CFSTMachine(void)
{
}
