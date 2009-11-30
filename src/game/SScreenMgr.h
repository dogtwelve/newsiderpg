#ifndef _S_SCREEN_MANAGER_
#define _S_SCREEN_MANAGER_

#include "SSingleton.h"


class SScreenMgr : public SSingleton<SScreenMgr>
{
private:
	int m_nWorld_XPos;
	int m_nWorld_YPos;

public:
	inline void SetWorldPos(int nXPos, int nYPos=0)	{m_nWorld_XPos = nXPos;	m_nWorld_YPos = nYPos;}
	inline int GetWorldXPos(void)					{return m_nWorld_XPos;}
	inline int GetWorldYPos(void)					{return m_nWorld_YPos;}

	SScreenMgr(void)	{m_nWorld_XPos = 0;		m_nWorld_YPos = 0;}
	virtual ~SScreenMgr(void);
};



#endif