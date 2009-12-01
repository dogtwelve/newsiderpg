#ifndef _S_EFFECT_MANAGER_
#define _S_EFFECT_MANAGER_

#include "SSingleton.h"
#include "SUtil.h"

class SEffectMgr : public SSingleton<SEffectMgr>
{
private:

public:

	SEffectMgr(void)			{}
	virtual ~SEffectMgr(void)	{}

	inline ASprite* GetShadowAs(void)	{return m_ShadowAs;}
	inline ASprite* GetDebuffAs(void)	{return m_DebuffAs;}

	//	TODO 원래 private 인데 임시로 써야되서 gfield 에서 그냥 받는다.
	ASprite*		m_ShadowAs;	//	그림자
	ASprite*		m_DebuffAs;	//	디버프


};



#endif