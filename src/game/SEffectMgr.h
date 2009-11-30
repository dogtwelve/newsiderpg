#ifndef _S_EFFECT_MANAGER_
#define _S_EFFECT_MANAGER_

#include "SSingleton.h"
#include "SUtil.h"

class SEffectMgr : public SSingleton<SEffectMgr>
{
private:
	ASPriteInstance*		m_ShedowIns;
public:

	SEffectMgr(void)			{}
	virtual ~SEffectMgr(void)	{}
};



#endif