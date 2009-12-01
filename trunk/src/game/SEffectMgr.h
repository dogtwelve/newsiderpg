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

	//	TODO ���� private �ε� �ӽ÷� ��ߵǼ� gfield ���� �׳� �޴´�.
	ASprite*		m_ShadowAs;	//	�׸���
	ASprite*		m_DebuffAs;	//	�����


};



#endif